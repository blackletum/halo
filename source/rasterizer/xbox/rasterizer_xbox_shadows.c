/*
RASTERIZER_XBOX_SHADOWS.C

symbols in this file:
00161950 01b0:
	_D3DDevice_SetRenderState (0000)
00161B00 0050:
	_D3DDevice_SetTextureStageState (0000)
00161B50 0220:
	_IDirect3DDevice8_SetRenderState@12 (0000)
00161D70 0010:
	__rasterizer_environment_shadows_begin (0000)
00161D80 0060:
	_IDirect3DDevice8_SetTextureStageState@16 (0000)
00161DE0 0010:
	_IDirect3DDevice8_SetVertexShaderConstant@16 (0000)
00161DF0 00a0:
	__rasterizer_environment_shadow_model_begin (0000)
00161E90 0010:
	__rasterizer_environment_shadow_model_end (0000)
00161EA0 0020:
	_IDirect3DDevice8_SetVertexData2f@16 (0000)
00161EC0 0010:
	_IDirect3DDevice8_SetVertexData2s@16 (0000)
00161ED0 0010:
	_IDirect3DDevice8_Begin@8 (0000)
00161EE0 0010:
	_IDirect3DDevice8_End@4 (0000)
00161EF0 0080:
	__rasterizer_environment_shadow_end (0000)
00161F70 0010:
	__rasterizer_environment_shadows_end (0000)
00161F80 0300:
	_rasterizer_shadow_convolve (0000)
00162280 03b0:
	__rasterizer_environment_shadow_begin (0000)
00162630 02b0:
	__rasterizer_environment_shadow_model_draw (0000)
001628E0 05c0:
	__rasterizer_environment_shadow_draw (0000)
002929E0 0039:
	??_C@_0DJ@KIPLBCDL@c?3?2halo?2SOURCE?2rasterizer?2xbox?2r@ (0000)
00292A1C 0027:
	??_C@_0CH@OGPNPLFF@?$CD?$CD?$CD?5WARNING?5empty?5shadow?5has?5bee@ (0000)
00292A44 001c:
	??_C@_0BM@OJNHCFOK@object_bounding_radius?$DO0?40f?$AA@ (0000)
00292A60 0037:
	??_C@_0DH@LMLPNHOO@shadow_color?9?$DOblue?5?$DO?$DN0?40f?5?$CG?$CG?5sha@ (0000)
00292A98 0037:
	??_C@_0DH@OODBCLKP@shadow_color?9?$DOgreen?$DO?$DN0?40f?5?$CG?$CG?5sha@ (0000)
00292AD0 0035:
	??_C@_0DF@OLKILINN@shadow_color?9?$DOred?5?$DO?$DN0?40f?5?$CG?$CG?5shad@ (0000)
00292B08 000d:
	??_C@_0N@NKBPFDCL@shadow_color?$AA@ (0000)
00292B18 000e:
	??_C@_0O@MDCFBAFA@shadow_matrix?$AA@ (0000)
0030CF84 0001:
	_shadow_restored (0000)
0046628C 000c:
	_local_shadow_color (0000)
00466298 0004:
	_bss_00466298 (0000)
0046629C 0034:
	_bss_0046629c (0000)
004662D0 0004:
	_local_parameters (0000)
004662D4 0001:
	_shadow_setup (0000)
004662D5 0001:
	_shadow_used (0000)
*/

/* ---------- headers */

#include "cseries.h"
#include "cseries_windows.h"
#include "errors.h"
#include "real_math.h"
#include "tag_groups.h"
#include "game_globals.h"
#include "rasterizer.h"
#include "rasterizer_geometry.h"
#include "shaders/shader_definitions.h"
#include "shaders.h"
#include "xbox/rasterizer_xbox.h"

/* ---------- constants */

enum
{
	_vertex_shader_shadow_convolve = 0x26,
	_vertex_shader_shadow_model = 0x27,
	_vertex_shader_shadow_environment = 0x1d,
};

/* ---------- prototypes */

void *shader_get_and_verify_type(struct shader const *shader, short type);

void rasterizer_set_target(short target, short mipmap_index, unsigned long background_color, boolean clear, boolean zbuffer);
void *rasterizer_set_target_as_texture(short stage, short target, short max_mipmap);
void rasterizer_set_stencil_mode(short stencil_mode);
void rasterizer_set_pixel_shader(D3DPIXELSHADERDEF *pixel_shader);
void rasterizer_set_vertex_shader_permutation(short vertex_shader, short vertex_type, short permutation);
void rasterizer_set_model_skinning(struct render_skinning const *skinning);
boolean rasterizer_set_texture_direct(short stage, long bitmap_group_index, short bitmap_index);
void *rasterizer_set_texture(short stage, short type, short usage, long bitmap_group_index, short bitmap_index);
void rasterizer_draw_static_triangles_static_vertices(struct triangle_buffer const *triangle_buffer, long first_triangle_index, long triangle_count, struct vertex_buffer const *vertex_buffer);
void rasterizer_draw_dynamic_triangles_static_vertices(long dynamic_triangle_buffer_index, long first_triangle_index, long triangle_count, struct vertex_buffer const *vertex_buffer);
long rasterizer_frame_statistics_count_static_vertices(struct triangle_buffer const *triangle_buffer, struct vertex_buffer const *vertex_buffer);
long rasterizer_frame_statistics_count_dynamic_vertices(long dynamic_triangle_buffer_index, long first_triangle_index, long triangle_count);
unsigned long real_rgb_color_to_pixel32(real_rgb_color const *color);

static void rasterizer_shadow_convolve(void);

/* ---------- globals */

extern struct rasterizer_window_begin_parameters global_window_parameters;
extern struct game_globals_rasterizer_data *global_rasterizer_data;
extern D3DPIXELSHADERDEF pixel_shader;

static struct rasterizer_model_begin_parameters const *local_parameters;
static real_rgb_color local_shadow_color;
static real bss_00466298; // object_bounding_radius (no known name)
static real_matrix4x3 bss_0046629c; // shadow_matrix (no known name)
static boolean shadow_setup;
static boolean shadow_used;
static boolean shadow_restored= TRUE;

/* ---------- private code */

static void rasterizer_shadow_convolve(
	void)
{
	real vsh_constants__texanim[VSH_CONSTANTS__TEXANIM_COUNT][4];

	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_shadows.c", 31, global_d3d_device);

	if (rasterizer_debug_options.draw_environment_shadows &&
		rasterizer_debug_options.shadow_convolution_enabled)
	{
		short stage;

		for (stage= 0; stage<4; stage++)
		{
			rasterizer_set_target_as_texture(stage, _rasterizer_target_shadow_primary, 0);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, stage, D3DTSS_ADDRESSU, D3DTADDRESS_BORDER);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, stage, D3DTSS_ADDRESSV, D3DTADDRESS_BORDER);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, stage, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, stage, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, stage, D3DTSS_MIPFILTER, D3DTEXF_POINT);
		}

		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_CCW);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED|D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_BLUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHABLENDENABLE, FALSE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHATESTENABLE, FALSE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZENABLE, D3DZB_FALSE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZBIAS, 0);

		rasterizer_set_vertex_shader_permutation(_vertex_shader_shadow_convolve, _rasterizer_vertex_type_dynamic_screen, 0);
		vsh_constants__texanim[0][0]= 1.0f;
		vsh_constants__texanim[0][1]= 0.0f;
		vsh_constants__texanim[0][2]= 0.0f;
		vsh_constants__texanim[0][3]= -0.00390625f;
		vsh_constants__texanim[1][0]= 0.0f;
		vsh_constants__texanim[1][1]= 1.0f;
		vsh_constants__texanim[1][2]= 0.0f;
		vsh_constants__texanim[1][3]= -0.00390625f;
		vsh_constants__texanim[2][0]= 1.0f;
		vsh_constants__texanim[2][1]= 0.0f;
		vsh_constants__texanim[2][2]= 0.0f;
		vsh_constants__texanim[2][3]= 0.00390625f;
		vsh_constants__texanim[3][0]= 0.0f;
		vsh_constants__texanim[3][1]= 1.0f;
		vsh_constants__texanim[3][2]= 0.0f;
		vsh_constants__texanim[3][3]= 0.00390625f;
		vsh_constants__texanim[4][0]= 1.0f;
		vsh_constants__texanim[4][1]= 0.0f;
		vsh_constants__texanim[4][2]= 0.0f;
		vsh_constants__texanim[4][3]= -0.00390625f;
		vsh_constants__texanim[5][0]= 0.0f;
		vsh_constants__texanim[5][1]= 1.0f;
		vsh_constants__texanim[5][2]= 0.0f;
		vsh_constants__texanim[5][3]= 0.00390625f;
		vsh_constants__texanim[6][0]= 1.0f;
		vsh_constants__texanim[6][1]= 0.0f;
		vsh_constants__texanim[6][2]= 0.0f;
		vsh_constants__texanim[6][3]= 0.00390625f;
		vsh_constants__texanim[7][0]= 0.0f;
		vsh_constants__texanim[7][1]= 1.0f;
		vsh_constants__texanim[7][2]= 0.0f;
		vsh_constants__texanim[7][3]= -0.00390625f;
		IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, VSH_CONSTANTS__TEXANIM_OFFSET, vsh_constants__texanim, VSH_CONSTANTS__TEXANIM_COUNT);

		csmemset(&pixel_shader, 0, sizeof(pixel_shader));
		pixel_shader.PSTextureModes= 0x8421;
		pixel_shader.PSCombinerCount= 0x1;
		pixel_shader.PSAlphaInputs[0]= 0x8a009a0;
		pixel_shader.PSAlphaOutputs[0]= 0x30c00;
		pixel_shader.PSRGBInputs[0]= 0xaa00ba0;
		pixel_shader.PSRGBOutputs[0]= 0x30c00;
		pixel_shader.PSFinalCombinerInputsABCD= 0xc20001c;
		rasterizer_set_pixel_shader(&pixel_shader);

		rasterizer_set_target(_rasterizer_target_shadow_secondary, 0, 0, FALSE, FALSE);

		IDirect3DDevice8_Begin(global_d3d_device, D3DPT_TRIANGLEFAN);
		IDirect3DDevice8_SetVertexData2s(global_d3d_device, 4, 0, 0);
		IDirect3DDevice8_SetVertexData2f(global_d3d_device, D3DVSDE_POSITION, -1.0078125f, 1.0078125f);
		IDirect3DDevice8_SetVertexData2s(global_d3d_device, 4, 1, 0);
		IDirect3DDevice8_SetVertexData2f(global_d3d_device, D3DVSDE_POSITION, 0.9921875f, 1.0078125f);
		IDirect3DDevice8_SetVertexData2s(global_d3d_device, 4, 1, 1);
		IDirect3DDevice8_SetVertexData2f(global_d3d_device, D3DVSDE_POSITION, 0.9921875f, -0.9921875f);
		IDirect3DDevice8_SetVertexData2s(global_d3d_device, 4, 0, 1);
		IDirect3DDevice8_SetVertexData2f(global_d3d_device, D3DVSDE_POSITION, -1.0078125f, -0.9921875f);
		IDirect3DDevice8_End(global_d3d_device);
	}
}

/* ---------- public code */

void _rasterizer_environment_shadows_begin(
	void)
{
	rasterizer_profile_begin(_rasterizer_profile_environment_shadows);
}

// TODO: operand order of the position.i*left.i term in vsh_constants__screenproj[1][3] is swapped
boolean _rasterizer_environment_shadow_begin(
	long object_index,
	real_matrix4x3 const *shadow_matrix,
	real_rgb_color const *shadow_color,
	real object_bounding_radius,
	real *shadow_volume_bounding_radius)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_shadows.c", 147, global_d3d_device);

	if (global_window_parameters.rasterizer_target==_rasterizer_target_render_primary &&
		rasterizer_debug_options.draw_environment_shadows)
	{
		real vsh_constants__screenproj[VSH_CONSTANTS__SCREENPROJ_COUNT][4];
		real inverse_radius;

		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_shadows.c", 153, shadow_matrix);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_shadows.c", 154, shadow_color);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_shadows.c", 155, shadow_color->red >=0.0f && shadow_color->red <=1.0f);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_shadows.c", 156, shadow_color->green>=0.0f && shadow_color->green<=1.0f);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_shadows.c", 157, shadow_color->blue >=0.0f && shadow_color->blue <=1.0f);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_shadows.c", 158, object_bounding_radius>0.0f);

		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_CCW);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED|D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_BLUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHABLENDENABLE, FALSE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHATESTENABLE, TRUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHAREF, 0x7f);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZENABLE, D3DZB_FALSE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZBIAS, 0);

		csmemset(&pixel_shader, 0, sizeof(pixel_shader));
		pixel_shader.PSTextureModes= 0x1;
		pixel_shader.PSCombinerCount= 0x1;
		pixel_shader.PSFinalCombinerInputsABCD= 0x20;
		pixel_shader.PSFinalCombinerInputsEFG= 0x1800;
		rasterizer_set_pixel_shader(&pixel_shader);

		inverse_radius= 1.0f/object_bounding_radius;
		vsh_constants__screenproj[0][0]= inverse_radius*shadow_matrix->forward.i;
		vsh_constants__screenproj[0][1]= inverse_radius*shadow_matrix->forward.j;
		vsh_constants__screenproj[0][2]= inverse_radius*shadow_matrix->forward.k;
		vsh_constants__screenproj[0][3]= -dot_product3d(&shadow_matrix->forward, (real_vector3d const *)&shadow_matrix->position)*inverse_radius;
		vsh_constants__screenproj[1][0]= inverse_radius*shadow_matrix->left.i;
		vsh_constants__screenproj[1][1]= inverse_radius*shadow_matrix->left.j;
		vsh_constants__screenproj[1][2]= inverse_radius*shadow_matrix->left.k;
		vsh_constants__screenproj[1][3]= -inverse_radius*dot_product3d(&shadow_matrix->left, (real_vector3d const *)&shadow_matrix->position);
		vsh_constants__screenproj[2][0]= 0.0f;
		vsh_constants__screenproj[2][1]= 0.0f;
		vsh_constants__screenproj[2][2]= 0.0f;
		vsh_constants__screenproj[2][3]= 0.5f;
		vsh_constants__screenproj[3][0]= 0.0f;
		vsh_constants__screenproj[3][1]= 0.0f;
		vsh_constants__screenproj[3][2]= 0.0f;
		vsh_constants__screenproj[3][3]= 1.0f;
		vsh_constants__screenproj[4][0]= 0.0f;
		vsh_constants__screenproj[4][1]= 0.0f;
		vsh_constants__screenproj[4][2]= 0.0f;
		vsh_constants__screenproj[4][3]= 0.0f;
		IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, VSH_CONSTANTS__SCREENPROJ_OFFSET, vsh_constants__screenproj, VSH_CONSTANTS__SCREENPROJ_COUNT);

		rasterizer_set_target(_rasterizer_target_shadow_primary, 0, rasterizer_debug_options.shadow_debug_enabled ? 0x88888888 : 0, TRUE, FALSE);
		rasterizer_set_stencil_mode(_rasterizer_stencil_mode_none);

		bss_0046629c= *shadow_matrix;
		local_shadow_color= *shadow_color;
		bss_00466298= object_bounding_radius;
		if (shadow_volume_bounding_radius)
		{
			*shadow_volume_bounding_radius= object_bounding_radius;
		}

		local_parameters= NULL;
		shadow_setup= FALSE;
		shadow_used= FALSE;
		shadow_restored= FALSE;

		if (rasterizer_debug_options.statistics_mode==2)
		{
			rasterizer_frame_statistics.shadow_count++;
		}
	}

	return TRUE;
}

void _rasterizer_environment_shadow_model_begin(
	struct rasterizer_model_begin_parameters const *parameters)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_shadows.c", 239, global_d3d_device);

	if (global_window_parameters.rasterizer_target==_rasterizer_target_render_primary &&
		rasterizer_debug_options.draw_environment_shadows)
	{
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_shadows.c", 245, parameters);

		rasterizer_set_model_skinning(&parameters->skinning);
		local_parameters= parameters;
		shadow_used= TRUE;

		if (rasterizer_debug_options.statistics_mode==2)
		{
			rasterizer_frame_statistics.model_shadow_count++;
		}
	}
}

// TODO: scheduling of the vsh_constants__texscale[0][0] store / global_frame_parameters is a common symbol here
void _rasterizer_environment_shadow_model_draw(
	struct shader const *shader,
	short shader_permutation_index,
	struct triangle_buffer const *triangle_buffer,
	struct vertex_buffer const *vertex_buffer)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_shadows.c", 274, global_d3d_device);

	if (global_window_parameters.rasterizer_target==_rasterizer_target_render_primary &&
		rasterizer_debug_options.draw_environment_shadows)
	{
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_shadows.c", 280, shader);

		if (shader->base.type==_shader_type_model)
		{
			struct shader_model const *shader_model= shader_get_and_verify_type(shader, _shader_type_model);
			real vsh_constants__texscale[VSH_CONSTANTS__TEXSCALE_COUNT][4];

			match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_shadows.c", 286, vertex_buffer);
			match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_shadows.c", 287, triangle_buffer);
			match_vassert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_shadows.c", 288, local_parameters, "local_parameters");

			if (TEST_FLAG(shader_model->model.flags, _shader_model_two_sided_bit))
			{
				IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_NONE);
			}
			else
			{
				IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_CCW);
			}
			rasterizer_set_vertex_shader_permutation(_vertex_shader_shadow_model, vertex_buffer->type, 0);

			if (TEST_FLAG(shader_model->model.flags, _shader_model_not_alpha_tested_bit))
			{
				IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_PSTEXTUREMODES, 0);
			}
			else
			{
				IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_PSTEXTUREMODES, 1);
				rasterizer_set_texture(0, 0, 1, shader_model->model.base_map.index, shader_permutation_index);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSU, D3DTADDRESS_WRAP);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);
			}

			vsh_constants__texscale[0][0]= shader_model->model.detail_map_scale;
			vsh_constants__texscale[0][1]= shader_model->model.detail_map_v_scale*shader_model->model.detail_map_scale;
			vsh_constants__texscale[0][2]= 1.0f;
			vsh_constants__texscale[0][3]= 1.0f;
			vsh_constants__texscale[1][0]= 1.0f;
			vsh_constants__texscale[1][1]= 0.0f;
			vsh_constants__texscale[1][2]= 0.0f;
			vsh_constants__texscale[1][3]= 0.0f;
			vsh_constants__texscale[2][0]= 0.0f;
			vsh_constants__texscale[2][1]= 1.0f;
			vsh_constants__texscale[2][2]= 0.0f;
			vsh_constants__texscale[2][3]= 0.0f;
			shader_texture_animation_evaluate(&shader_model->model.animation, &local_parameters->animation,
				local_parameters->base_map_scale.i*shader_model->model.map_scale.i,
				local_parameters->base_map_scale.j*shader_model->model.map_scale.j,
				0.0f, 0.0f, 0.0f, global_frame_parameters.game_time_sec,
				(real_vector4d *)vsh_constants__texscale[1], (real_vector4d *)vsh_constants__texscale[2]);
			IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, VSH_CONSTANTS__TEXSCALE_OFFSET, vsh_constants__texscale, VSH_CONSTANTS__TEXSCALE_COUNT);

			rasterizer_draw_static_triangles_static_vertices(triangle_buffer, 0, triangle_buffer->count, vertex_buffer);

			if (rasterizer_debug_options.statistics_mode==2)
			{
				rasterizer_frame_statistics.model_shadows.primitives++;
				rasterizer_frame_statistics.model_shadows.triangles+= triangle_buffer->count;
				rasterizer_frame_statistics.model_shadows.vertices+= rasterizer_frame_statistics_count_static_vertices(triangle_buffer, vertex_buffer);
			}
		}
	}
}

void _rasterizer_environment_shadow_model_end(
	void)
{
	local_parameters= NULL;
}

void _rasterizer_environment_shadow_draw(
	struct shader const *shader,
	short shader_permutation_index,
	long dynamic_triangle_buffer_index,
	long first_triangle_index,
	long triangle_count,
	struct vertex_buffer const *vertex_buffer)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_shadows.c", 404, global_d3d_device);

	if (global_window_parameters.rasterizer_target==_rasterizer_target_render_primary &&
		rasterizer_debug_options.draw_environment_shadows)
	{
		if (!shadow_setup)
		{
			real vsh_constants__shadow[VSH_CONSTANTS__SHADOW_COUNT][4];
			real inverse_radius, z_scale, w_scale, distance;

			if (rasterizer_debug_options.shadow_convolution_enabled)
			{
				rasterizer_shadow_convolve();
			}

			rasterizer_set_target_as_texture(0, rasterizer_debug_options.shadow_convolution_enabled ? _rasterizer_target_shadow_secondary : _rasterizer_target_shadow_primary, 0);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSU, D3DTADDRESS_BORDER);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSV, D3DTADDRESS_BORDER);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);

			rasterizer_set_texture_direct(1, global_rasterizer_data->linear_corner_fade.index, 0);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);

			rasterizer_set_texture_direct(2, global_rasterizer_data->vector_normalization.index, 0);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_ADDRESSW, D3DTADDRESS_CLAMP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);

			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_CCW);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_ALL);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHABLENDENABLE, TRUE);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_SRCBLEND, D3DBLEND_ZERO);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_BLENDOP, D3DBLENDOP_ADD);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHATESTENABLE, TRUE);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHAREF, 0);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZENABLE, D3DZB_TRUE);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZFUNC, D3DCMP_EQUAL);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZWRITEENABLE, FALSE);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZBIAS, 0);

			csmemset(&pixel_shader, 0, sizeof(pixel_shader));
			pixel_shader.PSTextureModes= 0x21;
			pixel_shader.PSCombinerCount= 0x4;
			pixel_shader.PSConstant0[0]= real_rgb_color_to_pixel32(&local_shadow_color);
			pixel_shader.PSConstant1[0]= 0xffffff;
			pixel_shader.PSRGBInputs[0]= 0x14200000;
			pixel_shader.PSRGBOutputs[0]= 0xc0;
			pixel_shader.PSRGBInputs[1]= 0x290c0821;
			pixel_shader.PSRGBOutputs[1]= 0xcd;
			pixel_shader.PSRGBInputs[2]= 0x2c200c2d;
			pixel_shader.PSRGBOutputs[2]= 0xc00;
			pixel_shader.PSRGBInputs[3]= 0x2c020000;
			pixel_shader.PSRGBOutputs[3]= 0x20d0;
			pixel_shader.PSFinalCombinerInputsABCD= 0x2c;
			pixel_shader.PSFinalCombinerInputsEFG= 0xd00;
			if (rasterizer_debug_options.shadow_debug_enabled)
			{
				pixel_shader.PSFinalCombinerInputsABCD= 0xc;
				IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHATESTENABLE, FALSE);
			}
			rasterizer_set_pixel_shader(&pixel_shader);

			rasterizer_set_vertex_shader_permutation(_vertex_shader_shadow_environment, vertex_buffer->type, shader_get_vertex_shader_permutation(shader));

			inverse_radius= 1.0f/bss_00466298;
			z_scale= 1.0f/(bss_00466298*4.0f);
			w_scale= 1.0f/(bss_00466298*0.5f);
			vsh_constants__shadow[0][0]= bss_0046629c.forward.i*inverse_radius*0.5f;
			vsh_constants__shadow[0][1]= bss_0046629c.forward.j*inverse_radius*0.5f;
			vsh_constants__shadow[0][2]= bss_0046629c.forward.k*inverse_radius*0.5f;
			vsh_constants__shadow[0][3]= (1.0f - dot_product3d((real_vector3d const *)&bss_0046629c.position, &bss_0046629c.forward)*inverse_radius)*0.5f;
			vsh_constants__shadow[1][0]= bss_0046629c.left.i*inverse_radius*-0.5f;
			vsh_constants__shadow[1][1]= bss_0046629c.left.j*inverse_radius*-0.5f;
			vsh_constants__shadow[1][2]= bss_0046629c.left.k*inverse_radius*-0.5f;
			vsh_constants__shadow[1][3]= (dot_product3d((real_vector3d const *)&bss_0046629c.position, &bss_0046629c.left)*inverse_radius + 1.0f)*0.5f;
			vsh_constants__shadow[2][0]= bss_0046629c.up.i*z_scale;
			vsh_constants__shadow[2][1]= bss_0046629c.up.j*z_scale;
			vsh_constants__shadow[2][2]= bss_0046629c.up.k*z_scale;
			distance= dot_product3d((real_vector3d const *)&bss_0046629c.position, &bss_0046629c.up);
			vsh_constants__shadow[2][3]= -distance*z_scale;
			vsh_constants__shadow[4][0]= bss_0046629c.up.i;
			vsh_constants__shadow[4][1]= bss_0046629c.up.j;
			vsh_constants__shadow[4][2]= bss_0046629c.up.k;
			vsh_constants__shadow[4][3]= 0.0f;
			vsh_constants__shadow[3][0]= -bss_0046629c.up.i*w_scale;
			vsh_constants__shadow[3][1]= -bss_0046629c.up.j*w_scale;
			vsh_constants__shadow[3][2]= -bss_0046629c.up.k*w_scale;
			vsh_constants__shadow[3][3]= distance*w_scale;
			IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, VSH_CONSTANTS__SHADOW_OFFSET, vsh_constants__shadow, VSH_CONSTANTS__SHADOW_COUNT);

			if (!shadow_restored)
			{
				rasterizer_set_target(global_window_parameters.rasterizer_target, 0, 0, FALSE, TRUE);
				shadow_restored= TRUE;
			}

			shadow_setup= TRUE;
		}

		rasterizer_set_stencil_mode(_rasterizer_stencil_mode_reject);
		rasterizer_draw_dynamic_triangles_static_vertices(dynamic_triangle_buffer_index, first_triangle_index, triangle_count, vertex_buffer);

		if (rasterizer_debug_options.statistics_mode==2)
		{
			rasterizer_frame_statistics.shadows.primitives++;
			rasterizer_frame_statistics.shadows.triangles+= triangle_count;
			rasterizer_frame_statistics.shadows.vertices+= rasterizer_frame_statistics_count_dynamic_vertices(dynamic_triangle_buffer_index, first_triangle_index, triangle_count);
		}
	}
}

void _rasterizer_environment_shadow_end(
	void)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_shadows.c", 563, global_d3d_device);

	if (global_window_parameters.rasterizer_target==_rasterizer_target_render_primary &&
		rasterizer_debug_options.draw_environment_shadows)
	{
		if (!shadow_used)
		{
			error(_error_silent, "### WARNING empty shadow has been cast");
		}

		if (!shadow_restored)
		{
			rasterizer_set_target(global_window_parameters.rasterizer_target, 0, 0, FALSE, TRUE);
			shadow_restored= TRUE;
		}
	}
}

void _rasterizer_environment_shadows_end(
	void)
{
	rasterizer_profile_end(_rasterizer_profile_environment_shadows);
}
