/*
RASTERIZER_XBOX_WIDGETS.C

symbols in this file:
00169EF0 01b0:
	_D3DDevice_SetRenderState (0000)
0016A0A0 0050:
	_D3DDevice_SetTextureStageState (0000)
0016A0F0 01c0:
	_rasterizer_widget_project_billboard (0000)
0016A2B0 0220:
	_IDirect3DDevice8_SetRenderState@12 (0000)
0016A4D0 0060:
	_IDirect3DDevice8_SetTextureStageState@16 (0000)
0016A530 0010:
	_IDirect3DDevice8_SetVertexShaderConstant@16 (0000)
0016A540 0010:
	_IDirect3DDevice8_BeginVisibilityTest@4 (0000)
0016A550 0010:
	_IDirect3DDevice8_EndVisibilityTest@8 (0000)
0016A560 0010:
	_IDirect3DDevice8_GetVisibilityTestResult@16 (0000)
0016A570 0020:
	_IDirect3DDevice8_SetVertexData2f@16 (0000)
0016A590 0030:
	_IDirect3DDevice8_SetVertexData4f@24 (0000)
0016A5C0 0010:
	_IDirect3DDevice8_SetVertexData2s@16 (0000)
0016A5D0 0010:
	_IDirect3DDevice8_SetVertexDataColor@12 (0000)
0016A5E0 0010:
	_IDirect3DDevice8_Begin@8 (0000)
0016A5F0 0010:
	_IDirect3DDevice8_End@4 (0000)
0016A600 0010:
	__rasterizer_widget_end (0000)
0016A610 00d0:
	__rasterizer_widget_get_occlusion_test_result (0000)
0016A6E0 0170:
	__rasterizer_widget_submit (0000)
0016A850 0480:
	__rasterizer_widget_begin (0000)
0016ACD0 00c0:
	__rasterizer_widget_set_texture (0000)
0016AD90 0040:
	__rasterizer_widget_set_tint_factor (0000)
0016ADD0 0040:
	__rasterizer_widget_set_zbuffer_enable (0000)
0016AE10 0210:
	__rasterizer_widget_draw_sprite2d (0000)
0016B020 0240:
	__rasterizer_widget_draw_sprite3d (0000)
0016B260 0280:
	__rasterizer_widget_submit_occlusion_test (0000)
0029CCB8 003d:
	??_C@_0DN@BOAOHHMH@?$CD?$CD?$CD?5ERROR?5rasterizer_widget_get_@ (0000)
0029CCF8 0026:
	??_C@_0CG@BMNNONEP@?$CIocclusion_test_result?$CG0x8000000@ (0000)
0029CD20 0039:
	??_C@_0DJ@CJFIOLEN@c?3?2halo?2SOURCE?2rasterizer?2xbox?2r@ (0000)
0029CD5C 0022:
	??_C@_0CC@GCBGNNKG@?$CD?$CD?$CD?5ERROR?5unsupported?5widget?5typ@ (0000)
0029CD80 0045:
	??_C@_0EF@KIEIHHAH@fabs?$CIcos_theta?$CKcos_theta?5?$CL?5sin_t@ (0000)
0029CDC8 0039:
	??_C@_0DJ@DLLMHNIO@?$CD?$CD?$CD?5ERROR?5rasterizer_widget_subm@ (0000)
0029CE04 0004:
	__real@c6fffe00 (0000)
004662EA 0001:
	?warned@?1??_rasterizer_widget_submit@@9@9 (0000)

notes:
	_code_00169ef0 .. _code_0016a5f0 (except _rasterizer_widget_project_billboard) are the out-of-line
	copies of the d3d8.h D3DINLINE wrappers the compiler emits for this unit
	(D3DDevice_SetRenderState, D3DDevice_SetTextureStageState,
	IDirect3DDevice8_SetRenderState, ...); they are not written by hand.
*/

/* ---------- headers */

#include "cseries.h"
#include "cseries_windows.h"
#include "errors.h"
#include "real_math.h"
#include "integer_math.h"
#include "rasterizer.h"
#include "rasterizer_widgets.h"
#include "xbox/rasterizer_xbox.h"
#include "tag_files/tag_groups.h"
#include "game/game_globals.h"

/* ---------- constants */

enum
{
	_widget_type_sprite= 5,
	_widget_type_occlusion_test,
};

enum
{
	_widget_flag_zbuffer_enable_bit= 0,
	_widget_flag_zbuffer_write_enable_bit,
};

/* ---------- macros */

/* ---------- structures */

/* ---------- prototypes */

struct transparent_geometry_group *rasterizer_transparent_geometry_new_group(void);
void rasterizer_spin_begin(long type);
void rasterizer_spin_end(void);
void rasterizer_set_vertex_shader_permutation(long vertex_shader_index, long vertex_type, long permutation);
void rasterizer_set_pixel_shader(D3DPIXELSHADERDEF *definition);
boolean rasterizer_set_texture_non_blocking(short stage_index, short bitmap_type, short usage, long bitmap_group_index, short sequence_index);
boolean rasterizer_set_texture_direct_non_blocking(short stage_index, long bitmap_group_index, short sequence_index);

void rasterizer_widget_set_tint_factor(real tint_factor);

static boolean rasterizer_widget_project_billboard(real_point3d const *point, real radius, real_point3d *projected_center, real_vector2d *projected_axes);

/* ---------- globals */

extern struct rasterizer_window_begin_parameters global_window_parameters;
extern struct game_globals_rasterizer_data *global_rasterizer_data;
extern D3DPIXELSHADERDEF pixel_shader;

/* ---------- private code */

// rasterizer_widget_project_billboard
// TODO: the w (projection column 3) products are evaluated in a different order (target z,y,x)
static boolean rasterizer_widget_project_billboard(
	real_point3d const *point,
	real radius,
	real_point3d *projected_center,
	real_vector2d *projected_axes)
{
	boolean result= FALSE;

	if (radius>0.f)
	{
		short width= global_window_parameters.camera.viewport_bounds.x1 - global_window_parameters.camera.viewport_bounds.x0;
		short height= global_window_parameters.camera.viewport_bounds.y1 - global_window_parameters.camera.viewport_bounds.y0;
		real (*projection)[4]= global_window_parameters.frustum.projection_matrix;
		real_point3d p_view;
		real x, y, z;
		real axis_x, axis_y;

		matrix4x3_transform_point(&global_window_parameters.frustum.world_to_view, point, &p_view);
		x= projection[0][0]*p_view.x + projection[1][0]*p_view.y + projection[2][0]*p_view.z + projection[3][0];
		y= projection[0][1]*p_view.x + projection[1][1]*p_view.y + projection[2][1]*p_view.z + projection[3][1];
		z= projection[0][2]*p_view.x + projection[1][2]*p_view.y + projection[2][2]*p_view.z + projection[3][2];
		axis_x= projection[0][0]*radius;
		axis_y= projection[1][1]*radius;

		if (z>0.f)
		{
			real one_over_w= 1.f/(projection[0][3]*p_view.x + projection[1][3]*p_view.y + projection[2][3]*p_view.z + projection[3][3]);

			projected_center->x= (((x*one_over_w + 1.f)*width) - 1.f)*0.5f;
			projected_center->y= (((1.f - y*one_over_w)*height) - 1.f)*0.5f;
			projected_center->z= MIN(1.f, z*one_over_w);
			projected_axes->i= 0.5f*axis_x*one_over_w*width;
			projected_axes->j= 0.5f*axis_y*one_over_w*height;
			result= TRUE;
		}
	}

	return result;
}

/* ---------- public code */

void _rasterizer_widget_submit(
	long object_index,
	long widget_index,
	real_point3d const *centroid,
	void (*render_proc)(long object_index, long widget_index))
{
	static boolean warned= FALSE;

	if (render_proc)
	{
		struct transparent_geometry_group *group= rasterizer_transparent_geometry_new_group();

		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_widgets.c", 88, centroid);

		if (group)
		{
			real_plane3d zero_plane;
			real_vector3d camera_to_centroid;

			zero_plane.n.i= 0.f;
			zero_plane.n.j= 0.f;
			zero_plane.n.k= 0.f;
			zero_plane.d= 0.f;

			camera_to_centroid.i= centroid->x - global_window_parameters.camera.position.x;
			camera_to_centroid.j= centroid->y - global_window_parameters.camera.position.y;
			camera_to_centroid.k= centroid->z - global_window_parameters.camera.position.z;

			group->geometry_flags= 0;
			group->object_index= 0;
			group->source_object_index= 0;
			group->shader= NULL;
			group->shader_permutation_index= 0;
			group->effect.type= 0;
			group->dynamic_triangle_buffer_index= NONE;
			group->triangle_buffer= (struct triangle_buffer const *)render_proc;
			group->first_triangle_index= object_index;
			group->triangle_count= widget_index;
			group->dynamic_vertex_buffer_index= NONE;
			group->vertex_buffers= NULL;
			group->lightmap= NULL;
			group->z_sort= -(global_window_parameters.camera.forward.i*camera_to_centroid.i + global_window_parameters.camera.forward.j*camera_to_centroid.j + global_window_parameters.camera.forward.k*camera_to_centroid.k);
			group->centroid= *centroid;
			group->plane= zero_plane;
			group->model_base_map_scale.j= 1.f;
			group->model_base_map_scale.i= 1.f;
			group->prev_group_presorted_index= NONE;
			group->next_group_presorted_index= NONE;
			group->active_camouflage_transparent_source_object_index= 0;
			group->cortana_hack= FALSE;
			group->node_matrices= NULL;
			group->node_matrix_count= 0;
			group->lighting= NULL;
			group->animation= NULL;
		}
		else if (!warned)
		{
			error(2, "### ERROR too many transparent geometry groups");
			warned= TRUE;
		}
	}
}

// TODO: register allocation/scheduling of the viewport width/height computation and the flags&1 temp differ
void _rasterizer_widget_begin(
	short type,
	word flags)
{
	real vsh_constants__screenproj[5][4];
	real one_over_width, one_over_height;
	short height, width;

	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_widgets.c", 154, global_d3d_device);

	switch (type)
	{
	case _widget_type_sprite:
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_CCW);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED|D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_BLUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHABLENDENABLE, TRUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_DESTBLEND, D3DBLEND_ONE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_BLENDOP, D3DBLENDOP_ADD);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHATESTENABLE, FALSE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZENABLE, TEST_FLAG(flags, _widget_flag_zbuffer_enable_bit));
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZWRITEENABLE, TEST_FLAG(flags, _widget_flag_zbuffer_write_enable_bit));
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZBIAS, 0);
		rasterizer_widget_set_tint_factor(1.f);
		rasterizer_set_vertex_shader_permutation(56, 6, 0);

		width= global_window_parameters.camera.viewport_bounds.x1 - global_window_parameters.camera.viewport_bounds.x0;
		height= global_window_parameters.camera.viewport_bounds.y1 - global_window_parameters.camera.viewport_bounds.y0;
		one_over_width= 1.f/width;
		vsh_constants__screenproj[0][0]= one_over_width + one_over_width;
		vsh_constants__screenproj[0][1]= 0.f;
		vsh_constants__screenproj[0][2]= 0.f;
		vsh_constants__screenproj[0][3]= -1.f - one_over_width;
		one_over_height= 1.f/height;
		vsh_constants__screenproj[1][0]= 0.f;
		vsh_constants__screenproj[1][1]= -2.f*one_over_height;
		vsh_constants__screenproj[1][2]= 0.f;
		vsh_constants__screenproj[1][3]= one_over_height + 1.f;
		vsh_constants__screenproj[2][0]= 0.f;
		vsh_constants__screenproj[2][1]= 0.f;
		vsh_constants__screenproj[2][2]= 1.f;
		vsh_constants__screenproj[2][3]= 0.f;
		vsh_constants__screenproj[3][0]= 0.f;
		vsh_constants__screenproj[3][1]= 0.f;
		vsh_constants__screenproj[3][2]= 0.f;
		vsh_constants__screenproj[3][3]= 1.f;
		vsh_constants__screenproj[4][0]= 0.f;
		vsh_constants__screenproj[4][1]= 0.f;
		vsh_constants__screenproj[4][2]= 0.f;
		vsh_constants__screenproj[4][3]= 1.f;
		IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, -68, vsh_constants__screenproj, 5);

		memset(&pixel_shader, 0, sizeof(pixel_shader));
		pixel_shader.PSTextureModes= 1;
		pixel_shader.PSCombinerCount= 3;
		pixel_shader.PSRGBInputs[0]= 0x08080000;
		pixel_shader.PSRGBOutputs[0]= 0xc0;
		pixel_shader.PSRGBInputs[1]= 0x0c0c0000;
		pixel_shader.PSRGBOutputs[1]= 0xd0;
		pixel_shader.PSRGBInputs[2]= 0x04082415;
		pixel_shader.PSRGBOutputs[2]= 0x45;
		pixel_shader.PSFinalCombinerInputsABCD= 0x050f0004;
		pixel_shader.PSFinalCombinerInputsEFG= 0x0c0d1400;
		rasterizer_set_pixel_shader(&pixel_shader);
		break;
	case _widget_type_occlusion_test:
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_CCW);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_COLORWRITEENABLE, rasterizer_debug_options.lens_flare_occlusion_debug ? D3DCOLORWRITEENABLE_RED|D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_BLUE : 0);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHABLENDENABLE, FALSE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHATESTENABLE, FALSE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZENABLE, TRUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZWRITEENABLE, rasterizer_debug_options.lens_flare_occlusion_debug);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZBIAS, *(DWORD *)&rasterizer_debug_options.zbias);
		rasterizer_set_vertex_shader_permutation(56, 6, 0);

		width= global_window_parameters.camera.viewport_bounds.x1 - global_window_parameters.camera.viewport_bounds.x0;
		height= global_window_parameters.camera.viewport_bounds.y1 - global_window_parameters.camera.viewport_bounds.y0;
		one_over_width= 1.f/width;
		vsh_constants__screenproj[0][0]= one_over_width + one_over_width;
		vsh_constants__screenproj[0][1]= 0.f;
		vsh_constants__screenproj[0][2]= 0.f;
		vsh_constants__screenproj[0][3]= -1.f - one_over_width;
		one_over_height= 1.f/height;
		vsh_constants__screenproj[1][0]= 0.f;
		vsh_constants__screenproj[1][1]= -2.f*one_over_height;
		vsh_constants__screenproj[1][2]= 0.f;
		vsh_constants__screenproj[1][3]= one_over_height + 1.f;
		vsh_constants__screenproj[2][0]= 0.f;
		vsh_constants__screenproj[2][1]= 0.f;
		vsh_constants__screenproj[2][2]= 1.f;
		vsh_constants__screenproj[2][3]= 0.f;
		vsh_constants__screenproj[3][0]= 0.f;
		vsh_constants__screenproj[3][1]= 0.f;
		vsh_constants__screenproj[3][2]= 0.f;
		vsh_constants__screenproj[3][3]= 1.f;
		vsh_constants__screenproj[4][0]= 0.f;
		vsh_constants__screenproj[4][1]= 0.f;
		vsh_constants__screenproj[4][2]= 0.f;
		vsh_constants__screenproj[4][3]= 1.f;
		IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, -68, vsh_constants__screenproj, 5);

		memset(&pixel_shader, 0, sizeof(pixel_shader));
		pixel_shader.PSCombinerCount= 1;
		pixel_shader.PSFinalCombinerInputsABCD= 0x20;
		rasterizer_set_pixel_shader(&pixel_shader);
		break;
	default:
		match_vassert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_widgets.c", 266, FALSE, "### ERROR unsupported widget type");
	}
}

boolean _rasterizer_widget_set_texture(
	short stage_index,
	long bitmap_group_index,
	short sequence_index)
{
	boolean success;

	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_widgets.c", 285, global_d3d_device);

	if (bitmap_group_index!=NONE)
	{
		success= rasterizer_set_texture_non_blocking(stage_index, 0, 1, bitmap_group_index, sequence_index);
	}
	else
	{
		success= rasterizer_set_texture_direct_non_blocking(stage_index, global_rasterizer_data->glow.index, sequence_index);
	}

	if (!success)
	{
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSU, D3DTADDRESS_BORDER);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSV, D3DTADDRESS_BORDER);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);
	}

	return success;
}

void _rasterizer_widget_set_tint_factor(
	real tint_factor)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_widgets.c", 318, global_d3d_device);

	IDirect3DDevice8_SetVertexData2f(global_d3d_device, D3DVSDE_TEXCOORD1, tint_factor, 0.f);
}

void _rasterizer_widget_set_zbuffer_enable(
	boolean zbuffer_enable)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_widgets.c", 334, global_d3d_device);

	IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZENABLE, zbuffer_enable);
}

void _rasterizer_widget_draw_sprite2d(
	real_point2d const *point,
	real radius,
	real_vector2d const *scale,
	real_vector2d const *texture_scale,
	real rotation,
	pixel32 color)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_widgets.c", 356, point);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_widgets.c", 357, global_d3d_device);

	if (radius>0.f)
	{
		real a, b;
		real scale_x, scale_y;
		short u, v;

		if (rotation!=0.f)
		{
			real cos_theta= (real)cos(rotation);
			real sin_theta= (real)sin(rotation);

			match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_widgets.c", 369, fabs(cos_theta*cos_theta + sin_theta*sin_theta - 1.0f)<_real_epsilon);

			a= cos_theta - sin_theta;
			b= sin_theta + cos_theta;
		}
		else
		{
			b= 1.f;
			a= 1.f;
		}

		if (scale)
		{
			scale_x= scale->i;
			scale_y= scale->j;
		}
		else
		{
			scale_y= 1.f;
			scale_x= 1.f;
		}

		u= texture_scale ? (short)texture_scale->i : 1;
		v= texture_scale ? (short)texture_scale->j : 1;

		IDirect3DDevice8_Begin(global_d3d_device, D3DPT_TRIANGLEFAN);
		IDirect3DDevice8_SetVertexDataColor(global_d3d_device, D3DVSDE_TEXCOORD0, color);
		IDirect3DDevice8_SetVertexData2s(global_d3d_device, D3DVSDE_SPECULAR, 0, 0);
		IDirect3DDevice8_SetVertexData2f(global_d3d_device, D3DVSDE_POSITION, point->x - a*scale_x, point->y - b*scale_y);
		IDirect3DDevice8_SetVertexData2s(global_d3d_device, D3DVSDE_SPECULAR, u, 0);
		IDirect3DDevice8_SetVertexData2f(global_d3d_device, D3DVSDE_POSITION, b*scale_x + point->x, point->y - a*scale_y);
		IDirect3DDevice8_SetVertexData2s(global_d3d_device, D3DVSDE_SPECULAR, u, v);
		IDirect3DDevice8_SetVertexData2f(global_d3d_device, D3DVSDE_POSITION, a*scale_x + point->x, b*scale_y + point->y);
		IDirect3DDevice8_SetVertexData2s(global_d3d_device, D3DVSDE_SPECULAR, 0, v);
		IDirect3DDevice8_SetVertexData2f(global_d3d_device, D3DVSDE_POSITION, point->x - b*scale_x, a*scale_y + point->y);
		IDirect3DDevice8_End(global_d3d_device);
	}
}

void _rasterizer_widget_draw_sprite3d(
	real_point3d const *point,
	real radius,
	real_vector2d const *scale,
	real rotation,
	pixel32 color)
{
	real_point3d projected_center;
	real_vector2d projected_axes;

	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_widgets.c", 425, point);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_widgets.c", 426, global_d3d_device);

	if (radius>0.f && rasterizer_widget_project_billboard(point, radius, &projected_center, &projected_axes))
	{
		real axis_x, axis_y;
		real scale_x, scale_y;

		if (rotation!=0.f)
		{
			real theta= rotation*0.017453292f;
			real cos_theta= (real)cos(theta);
			real sin_theta= (real)sin(theta);

			match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_widgets.c", 437, fabs(cos_theta*cos_theta + sin_theta*sin_theta - 1.0f)<_real_epsilon);

			axis_x= projected_axes.i*cos_theta - projected_axes.j*sin_theta;
			axis_y= projected_axes.i*sin_theta + projected_axes.j*cos_theta;
		}
		else
		{
			axis_x= projected_axes.i;
			axis_y= projected_axes.j;
		}

		if (scale)
		{
			scale_x= scale->i;
			scale_y= scale->j;
		}
		else
		{
			scale_y= 1.f;
			scale_x= 1.f;
		}

		IDirect3DDevice8_Begin(global_d3d_device, D3DPT_TRIANGLEFAN);
		IDirect3DDevice8_SetVertexDataColor(global_d3d_device, D3DVSDE_TEXCOORD0, color);
		IDirect3DDevice8_SetVertexData2s(global_d3d_device, D3DVSDE_SPECULAR, 0, 0);
		IDirect3DDevice8_SetVertexData4f(global_d3d_device, D3DVSDE_POSITION, projected_center.x - scale_x*axis_x, projected_center.y - scale_y*axis_y, projected_center.z, 1.f);
		IDirect3DDevice8_SetVertexData2s(global_d3d_device, D3DVSDE_SPECULAR, 1, 0);
		IDirect3DDevice8_SetVertexData4f(global_d3d_device, D3DVSDE_POSITION, scale_x*axis_y + projected_center.x, projected_center.y - scale_y*axis_x, projected_center.z, 1.f);
		IDirect3DDevice8_SetVertexData2s(global_d3d_device, D3DVSDE_SPECULAR, 1, 1);
		IDirect3DDevice8_SetVertexData4f(global_d3d_device, D3DVSDE_POSITION, scale_x*axis_x + projected_center.x, scale_y*axis_y + projected_center.y, projected_center.z, 1.f);
		IDirect3DDevice8_SetVertexData2s(global_d3d_device, D3DVSDE_SPECULAR, 0, 1);
		IDirect3DDevice8_SetVertexData4f(global_d3d_device, D3DVSDE_POSITION, projected_center.x - scale_x*axis_y, scale_y*axis_x + projected_center.y, projected_center.z, 1.f);
		IDirect3DDevice8_End(global_d3d_device);
	}
}

void _rasterizer_widget_end(
	void)
{
	return;
}

long _rasterizer_widget_submit_occlusion_test(
	real_point3d const *point,
	real radius,
	long index)
{
	long pixel_count;

	if (rasterizer_debug_options.lens_flare_occlusion_enabled)
	{
		boolean success= TRUE;
		real_point3d projected_center;
		real_vector2d projected_axes;

		if (rasterizer_widget_project_billboard(point, radius, &projected_center, &projected_axes))
		{
			short x0, y0, x1, y1;

			projected_axes.i= MAX(1.f, projected_axes.i);
			projected_axes.j= MAX(1.f, projected_axes.j);

			x0= (short)fast_ftol((real)floor(PIN(projected_center.x - projected_axes.i, -32767.f, 32767.f)));
			y0= (short)fast_ftol((real)floor(PIN(projected_center.y - projected_axes.j, -32767.f, 32767.f)));
			x1= (short)fast_ftol((real)floor(PIN(projected_center.x + projected_axes.i, -32767.f, 32767.f)));
			y1= (short)fast_ftol((real)floor(PIN(projected_center.y + projected_axes.j, -32767.f, 32767.f)));

			pixel_count= MAX(0, (x1 - x0)*(y1 - y0));
			if (pixel_count>0)
			{
				IDirect3DDevice8_BeginVisibilityTest(global_d3d_device);
				IDirect3DDevice8_Begin(global_d3d_device, D3DPT_TRIANGLEFAN);
				IDirect3DDevice8_SetVertexData4f(global_d3d_device, D3DVSDE_POSITION, (real)x0, (real)y0, projected_center.z, 1.f);
				IDirect3DDevice8_SetVertexData4f(global_d3d_device, D3DVSDE_POSITION, (real)x1, (real)y0, projected_center.z, 1.f);
				IDirect3DDevice8_SetVertexData4f(global_d3d_device, D3DVSDE_POSITION, (real)x1, (real)y1, projected_center.z, 1.f);
				IDirect3DDevice8_SetVertexData4f(global_d3d_device, D3DVSDE_POSITION, (real)x0, (real)y1, projected_center.z, 1.f);
				IDirect3DDevice8_End(global_d3d_device);
				D3DCALL(success, IDirect3DDevice8_EndVisibilityTest(global_d3d_device, index));
			}
		}
		else
		{
			pixel_count= 0;
		}

		if (!success)
		{
			error(2, "### ERROR rasterizer_widget_submit_occlusion_test failed");
		}
	}
	else
	{
		pixel_count= 1;
	}

	return pixel_count;
}

long _rasterizer_widget_get_occlusion_test_result(
	long index)
{
	long occlusion_test_result= NONE;

	if (rasterizer_debug_options.lens_flare_occlusion_enabled)
	{
		boolean success= TRUE;
		ULONGLONG timestamp;
		HRESULT hr;

		hr= IDirect3DDevice8_GetVisibilityTestResult(global_d3d_device, index, &occlusion_test_result, &timestamp);
		if (hr==D3DERR_TESTINCOMPLETE)
		{
			rasterizer_spin_begin(26);
			do
			{
				hr= IDirect3DDevice8_GetVisibilityTestResult(global_d3d_device, index, &occlusion_test_result, &timestamp);
			}
			while (hr==D3DERR_TESTINCOMPLETE);
			rasterizer_spin_end();
		}
		D3DCALL(success, hr);

		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_widgets.c", 574, (occlusion_test_result&0x80000000)==0);

		if (!success)
		{
			error(2, "### ERROR rasterizer_widget_get_occlusion_test_result failed");
		}
	}
	else
	{
		occlusion_test_result= 1;
	}

	return occlusion_test_result;
}
