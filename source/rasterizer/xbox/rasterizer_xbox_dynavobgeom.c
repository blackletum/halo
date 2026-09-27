/*
RASTERIZER_XBOX_DYNAVOBGEOM.C

symbols in this file:
0014E840 01b0:
	_D3DDevice_SetRenderState (0000)
0014E9F0 0050:
	_D3DDevice_SetTextureStageState (0000)
0014EA40 0010:
	__rasterizer_hud_begin (0000)
0014EA50 0010:
	__rasterizer_hud_end (0000)
0014EA60 0010:
	__rasterizer_dynamic_lit_geometry_draw (0000)
0014EA70 0100:
	__rasterizer_dynamic_screen_geometry_add_multitexture_params_to_base (0000)
0014EB70 0220:
	_IDirect3DDevice8_SetRenderState@12 (0000)
0014ED90 0030:
	__rasterizer_dynamic_screen_geometry_draw (0000)
0014EDC0 0060:
	_IDirect3DDevice8_SetTextureStageState@16 (0000)
0014EE20 0010:
	_IDirect3DDevice8_SetVertexShaderConstant@16 (0000)
0014EE30 0020:
	_IDirect3DDevice8_SetVertexData2f@16 (0000)
0014EE50 0010:
	_IDirect3DDevice8_SetVertexDataColor@12 (0000)
0014EE60 0010:
	_IDirect3DDevice8_Begin@8 (0000)
0014EE70 0010:
	_IDirect3DDevice8_End@4 (0000)
0014EE80 0270:
	__rasterizer_dynamic_unlit_geometry_draw (0000)
0014F0F0 0040:
	_code_0014f0f0 (0000)
0014F130 0b90:
	__rasterizer_psuedo_dynamic_screen_quad_draw (0000)
0028FBDC 0010:
	??_C@_0BA@KKBHHCGF@multitex_params?$AA@ (0000)
0028FBEC 0005:
	??_C@_04BHIIPFEC@base?$AA@ (0000)
0028FBF4 003d:
	??_C@_0DN@KLLFPFFH@c?3?2halo?2SOURCE?2rasterizer?2xbox?2r@ (0000)
0028FC34 003e:
	??_C@_0DO@GMEFDNIN@_rasterizer_dynamic_screen_geome@ (0000)
0028FC74 002f:
	??_C@_0CP@PIDBCAKH@?$CD?$CD?$CD?5ERROR?5too?5many?5transparent?5g@ (0000)
0028FCA4 0009:
	??_C@_08JOJIKHG@centroid?$AA@ (0000)
0028FCB0 0027:
	??_C@_0CH@DLHDBKLI@shader?9?$DObase?4type?$DN?$DN_shader_type_@ (0000)
0028FCD8 0069:
	??_C@_0GJ@OKAOIPGM@?$CBTEST_FLAG?$CIgeometry_flags?0?5_rast@ (0000)
0028FD44 0016:
	??_C@_0BG@MMAGMAFI@meter?9?$DOgradient?$DN?$DN1?40f?$AA@ (0000)
0028FD5C 0013:
	??_C@_0BD@BMLFIAIE@meter?9?$DOtint_mode_2?$AA@ (0000)
0028FD70 0035:
	??_C@_0DF@MDAHAMMD@?$CBparameters?9?$DOmap?$FL1?$FN?5?$HM?$HM?5?$CBparamete@ (0000)
0028FDA8 002a:
	??_C@_0CK@NCHEDINN@?$CBparameters?9?$DOmap?$FL2?$FN?5?$HM?$HM?5parameter@ (0000)
0028FDD4 0013:
	??_C@_0BD@LBFDNODJ@parameters?9?$DOmap?$FL0?$FN?$AA@ (0000)
00465A16 0001:
	?warned@?1??_rasterizer_dynamic_unlit_geometry_draw@@9@9 (0000)
*/

/* ---------- headers */

#include "cseries.h"
#include "cseries_windows.h"
#include "errors.h"
#include "real_math.h"
#include "rasterizer.h"
#include "rasterizer_geometry.h"
#include "shaders/shader_definitions.h"
#include "xbox/rasterizer_xbox.h"

/*
the _code_0014e840 .. _code_0014ee70 symbols above are uninlined copies of d3d8.h
__forceinline functions emitted by the compiler (D3DDevice_SetRenderState,
D3DDevice_SetTextureStageState, IDirect3DDevice8_SetRenderState, _SetTextureStageState,
_SetVertexShaderConstant, _SetVertexData2f, _SetVertexDataColor, _Begin, _End)
*/

/* ---------- constants */

enum
{
	NUMBER_OF_PSUEDO_DYNAMIC_SCREEN_QUAD_VERTICES = 4
};

/* ---------- macros */

/* ---------- structures */

/* ---------- prototypes */

struct transparent_geometry_group *rasterizer_transparent_geometry_new_group(void);
void *shader_get_and_verify_type(struct shader const *shader, short type);
long rasterizer_frame_statistics_count_dynamic_vertices(long dynamic_triangle_buffer_index, long first_triangle_index, long triangle_count);

void rasterizer_set_framebuffer_blend_function(short framebuffer_blend_function);
boolean rasterizer_set_texture_bitmap_data(short stage, struct bitmap_data const *bitmap);
void rasterizer_set_vertex_shader_permutation(long vertex_shader, long vertex_type, long permutation);
void rasterizer_set_pixel_shader(D3DPIXELSHADERDEF *definition);

pixel32 real_alpha_to_pixel32(real alpha);
pixel32 real_argb_color_to_pixel32(real_argb_color const *color);

static __forceinline void code_0014f0f0(struct dynamic_screen_vertex const *vertex);

/* ---------- globals */

extern struct rasterizer_window_begin_parameters global_window_parameters;
extern D3DPIXELSHADERDEF pixel_shader;

/* ---------- public code */

void _rasterizer_hud_begin(
	void)
{
	rasterizer_profile_begin(_rasterizer_profile_hud);
}

void _rasterizer_hud_end(
	void)
{
	rasterizer_profile_end(_rasterizer_profile_hud);
}

void _rasterizer_dynamic_unlit_geometry_draw(
	struct shader const *shader,
	struct bitmap_data const *primary_map,
	struct render_animation const *animation,
	long dynamic_triangle_buffer_index,
	long dynamic_vertex_buffer_index,
	long triangle_count,
	real_point3d const *centroid,
	unsigned long geometry_flags)
{
	static boolean warned= FALSE;

	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_dynavobgeom.c", 38, global_d3d_device);

	if (rasterizer_debug_options.draw_dynamic_unlit_geometry)
	{
		struct transparent_geometry_group *group;
		real_vector3d camera_to_centroid;

		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_dynavobgeom.c", 42, !TEST_FLAG(geometry_flags, _rasterizer_geometry_viewspace_bit) || shader->base.type==_shader_type_effect);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_dynavobgeom.c", 44, shader->base.type==_shader_type_effect);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_dynavobgeom.c", 52, centroid);

		vector_from_points3d(&global_window_parameters.camera.position, centroid, &camera_to_centroid);

		group= rasterizer_transparent_geometry_new_group();
		if (group)
		{
			real_plane3d plane= {0.f, 0.f, 0.f, 0.f};

			group->geometry_flags= geometry_flags;
			group->object_index= 0;
			group->source_object_index= 0;
			group->shader= shader;
			group->shader_permutation_index= 0;
			group->effect.type= 0;
			group->dynamic_triangle_buffer_index= dynamic_triangle_buffer_index;
			group->triangle_buffer= NULL;
			group->first_triangle_index= 0;
			group->triangle_count= triangle_count;
			group->dynamic_vertex_buffer_index= dynamic_vertex_buffer_index;
			group->vertex_buffers= NULL;
			group->lightmap= primary_map;
			group->z_sort= -dot_product3d(&global_window_parameters.camera.forward, &camera_to_centroid);
			group->centroid= *centroid;
			group->plane= plane;
			group->model_base_map_scale.j= 1.f;
			group->model_base_map_scale.i= 1.f;
			group->prev_group_presorted_index= NONE;
			group->next_group_presorted_index= NONE;
			group->active_camouflage_transparent_source_object_index= 0;
			group->cortana_hack= FALSE;

			if (shader->base.type==_shader_type_effect)
			{
				struct shader_effect *effect= shader_get_and_verify_type(shader, _shader_type_effect);

				if (TEST_FLAG(effect->effect.flags, 0))
				{
					group->z_sort+= 0.25f;
				}
			}

			group->node_matrices= NULL;
			group->node_matrix_count= 0;
			group->lighting= NULL;
			group->animation= NULL;

			if (rasterizer_debug_options.statistics_mode==_rasterizer_statistics_mode_geometry)
			{
				rasterizer_frame_statistics.dynamic_geometry_count++;
				rasterizer_frame_statistics.dynamic_geometry_triangles+= triangle_count;
				if (triangle_count>rasterizer_frame_statistics.dynamic_geometry_maximum_triangles)
				{
					rasterizer_frame_statistics.dynamic_geometry_maximum_triangles= triangle_count;
				}
				rasterizer_frame_statistics.dynamic_geometry_vertices+= rasterizer_frame_statistics_count_dynamic_vertices(dynamic_triangle_buffer_index, 0, triangle_count);
			}
		}
		else if (!warned)
		{
			error(_error_silent, "### ERROR too many transparent geometry groups");
			warned= TRUE;
		}
	}
}

void _rasterizer_dynamic_lit_geometry_draw(
	struct shader const *shader,
	struct bitmap_data const *primary_map,
	struct render_animation const *animation,
	struct render_lighting const *lighting,
	long dynamic_triangle_buffer_index,
	long dynamic_vertex_buffer_index,
	long triangle_count,
	real_point3d const *centroid,
	unsigned long geometry_flags)
{
	return;
}

void _rasterizer_dynamic_screen_geometry_add_multitexture_params_to_base(
	struct rasterizer_dynamic_screen_geometry_parameters *base,
	struct rasterizer_dynamic_screen_geometry_parameters const *multitex_params)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_dynavobgeom.c", 220, base);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_dynavobgeom.c", 221, multitex_params);

	base->offset= multitex_params->offset;
	base->map_anchor_screen[1]= multitex_params->map_anchor_screen[1];
	base->map_anchor_screen[2]= multitex_params->map_anchor_screen[2];
	base->map[1]= multitex_params->map[1];
	base->map[2]= multitex_params->map[2];
	base->map_wrapped[1]= multitex_params->map_wrapped[1];
	base->map_wrapped[2]= multitex_params->map_wrapped[2];
	base->map_offset[1]= multitex_params->map_offset[1];
	base->map_offset[2]= multitex_params->map_offset[2];
	base->map_scale[1]= multitex_params->map_scale[1];
	base->map_scale[2]= multitex_params->map_scale[2];
	base->map_texture_scale[1]= multitex_params->map_texture_scale[1];
	base->map_texture_scale[2]= multitex_params->map_texture_scale[2];
	base->map_tint[1]= multitex_params->map_tint[1];
	base->map_tint[2]= multitex_params->map_tint[2];
	base->map_fade[1]= multitex_params->map_fade[1];
	base->map_fade[2]= multitex_params->map_fade[2];
	base->map0_to_1_blend_function= multitex_params->map0_to_1_blend_function;
	base->map1_to_2_blend_function= multitex_params->map1_to_2_blend_function;
}

void _rasterizer_dynamic_screen_geometry_draw(
	struct rasterizer_dynamic_screen_geometry_parameters const *parameters,
	long dynamic_triangle_buffer_index,
	long dynamic_vertex_buffer_index,
	long triangle_count)
{
	match_vassert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_dynavobgeom.c", 255, FALSE, "_rasterizer_dynamic_screen_geometry_draw not supported no mo'");
}

/* ---------- private code */

static __forceinline void code_0014f0f0(
	struct dynamic_screen_vertex const *vertex)
{
	IDirect3DDevice8_SetVertexDataColor(global_d3d_device, D3DVSDE_TEXCOORD0, vertex->color);
	IDirect3DDevice8_SetVertexData2f(global_d3d_device, D3DVSDE_SPECULAR, vertex->texcoord.x, vertex->texcoord.y);
	IDirect3DDevice8_SetVertexData2f(global_d3d_device, D3DVSDE_POSITION, vertex->position.x, vertex->position.y);
}

/* ---------- public code */

void _rasterizer_psuedo_dynamic_screen_quad_draw(
	struct rasterizer_dynamic_screen_geometry_parameters const *parameters,
	struct dynamic_screen_vertex *vertices)
{
	short stage= 0;

	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_dynavobgeom.c", 756, global_d3d_device);

	if (rasterizer_debug_options.draw_dynamic_screen_geometry && !global_window_parameters.rasterizer_target)
	{
		struct rasterizer_meter_parameters const *meter;
		short vertex_index;
		short width, height;
		real_vector2d offset;

		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_dynavobgeom.c", 761, parameters);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_dynavobgeom.c", 763, parameters->map[0]);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_dynavobgeom.c", 765, !parameters->map[2] || parameters->map[1]);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_dynavobgeom.c", 767, !parameters->map[1] || !parameters->meter_parameters);

		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_NONE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED|D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_BLUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHABLENDENABLE, TRUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHATESTENABLE, FALSE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZENABLE, D3DZB_FALSE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZBIAS, 0);
		rasterizer_set_framebuffer_blend_function(parameters->framebuffer_blend_function);

		width= global_window_parameters.camera.viewport_bounds.x1-global_window_parameters.camera.viewport_bounds.x0;
		height= global_window_parameters.camera.viewport_bounds.y1-global_window_parameters.camera.viewport_bounds.y0;
		offset.i= parameters->offset ? 2.f*parameters->offset->i/width : 0.f;
		offset.j= parameters->offset ? -2.f*parameters->offset->j/height : 0.f;

		{
			real inverse_width= 1.f/width;
			real inverse_height;
			real_vector4d position_constants[5];
			real_vector4d texture_constants[6];

			position_constants[0].i= 2.f*inverse_width;
			position_constants[0].j= 0.f;
			position_constants[0].k= 0.f;
			position_constants[0].l= offset.i-(inverse_width+1.f);
			inverse_height= 1.f/height;
			position_constants[1].i= 0.f;
			position_constants[1].j= -2.f*inverse_height;
			position_constants[1].k= 0.f;
			position_constants[1].l= inverse_height+offset.j+1.f;
			position_constants[2].i= 0.f;
			position_constants[2].j= 0.f;
			position_constants[2].k= 0.f;
			position_constants[2].l= 0.5f;
			position_constants[3].i= 0.f;
			position_constants[3].j= 0.f;
			position_constants[3].k= 0.f;
			position_constants[3].l= 1.f;
			position_constants[4].i= parameters->map_texture_scale[0].i;
			position_constants[4].j= parameters->map_texture_scale[0].j;
			position_constants[4].k= 0.f;
			position_constants[4].l= 1.f;

			texture_constants[0].i= parameters->map_texture_scale[1].i;
			texture_constants[0].j= parameters->map_texture_scale[1].j;
			texture_constants[0].k= parameters->map_texture_scale[2].i;
			texture_constants[0].l= parameters->map_texture_scale[2].j;
			texture_constants[1].i= parameters->map_anchor_screen[0] ? 1.f : 0.f;
			texture_constants[1].j= parameters->map_anchor_screen[0] ? 0.f : 1.f;
			texture_constants[1].k= parameters->map_anchor_screen[1] ? 1.f : 0.f;
			texture_constants[1].l= parameters->map_anchor_screen[1] ? 0.f : 1.f;
			texture_constants[2].i= parameters->map_anchor_screen[2] ? 1.f : 0.f;
			texture_constants[2].j= parameters->map_anchor_screen[2] ? 0.f : 1.f;
			texture_constants[2].k= parameters->map_offset[0] ? parameters->map_offset[0]->x : 0.f;
			texture_constants[2].l= parameters->map_offset[0] ? parameters->map_offset[0]->y : 0.f;
			texture_constants[3].i= parameters->map_offset[1] ? parameters->map_offset[1]->x : 0.f;
			texture_constants[3].j= parameters->map_offset[1] ? parameters->map_offset[1]->y : 0.f;
			texture_constants[3].k= parameters->map_offset[2] ? parameters->map_offset[2]->x : 0.f;
			texture_constants[3].l= parameters->map_offset[2] ? parameters->map_offset[2]->y : 0.f;
			texture_constants[4].i= parameters->map_scale[0].i;
			texture_constants[4].j= parameters->map_scale[0].j;
			texture_constants[4].k= parameters->map_scale[1].i;
			texture_constants[4].l= parameters->map_scale[1].j;
			texture_constants[5].i= parameters->map_scale[2].i;
			texture_constants[5].j= parameters->map_scale[2].j;
			texture_constants[5].k= 0.f;
			texture_constants[5].l= 0.f;

			IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, -68, position_constants, 5);
			IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, -63, texture_constants, 6);
		}

		for (stage= 0; stage<NUMBER_OF_DYNAMIC_SCREEN_GEOMETRY_MAPS; stage++)
		{
			if (!parameters->map[stage])
			{
				break;
			}

			rasterizer_set_texture_bitmap_data(stage, parameters->map[stage]);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, stage, D3DTSS_ADDRESSU, parameters->map_wrapped[stage] ? D3DTADDRESS_WRAP : D3DTADDRESS_CLAMP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, stage, D3DTSS_ADDRESSV, parameters->map_wrapped[stage] ? D3DTADDRESS_WRAP : D3DTADDRESS_CLAMP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, stage, D3DTSS_MAGFILTER, parameters->point_sampled ? D3DTEXF_POINT : D3DTEXF_LINEAR);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, stage, D3DTSS_MINFILTER, parameters->point_sampled ? D3DTEXF_POINT : D3DTEXF_LINEAR);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, stage, D3DTSS_MIPFILTER, parameters->point_sampled ? D3DTEXF_POINT : D3DTEXF_LINEAR);
		}

		rasterizer_set_vertex_shader_permutation(4, 8, 1);

		meter= parameters->meter_parameters;
		if (meter)
		{
			real gradient;

			match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_dynavobgeom.c", 886, meter->tint_mode_2);
			match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_dynavobgeom.c", 887, meter->gradient==1.0f);

			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHABLENDENABLE, TRUE);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_SRCBLEND, D3DBLEND_CONSTANTCOLOR);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_DESTBLEND, D3DBLEND_SRCALPHA);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_BLENDCOLOR, meter->tint_color);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_BLENDOP, D3DBLENDOP_ADD);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ALPHAKILL, D3DTALPHAKILL_ENABLE);

			csmemset(&pixel_shader, 0, sizeof(pixel_shader));
			pixel_shader.PSTextureModes= 1;
			pixel_shader.PSCombinerCount= 0x11104;

			pixel_shader.PSConstant0[0]= meter->gradient_min_color;
			gradient= MAX(meter->gradient*8.f, 1.f);
			pixel_shader.PSConstant1[0]= (meter->gradient_max_color&0x00ffffff) | real_alpha_to_pixel32(1.f/gradient);
			pixel_shader.PSAlphaInputs[0]= 0x12081208;
			pixel_shader.PSRGBInputs[0]= 0x1120e820;
			pixel_shader.PSAlphaOutputs[0]= 0x20c00;
			pixel_shader.PSRGBOutputs[0]= 0x20c00;

			pixel_shader.PSConstant0[1]= meter->gradient_min_color;
			pixel_shader.PSConstant1[1]= meter->gradient_max_color;
			pixel_shader.PSAlphaInputs[1]= 0x6c200000;
			pixel_shader.PSAlphaOutputs[1]= 0xc0;
			pixel_shader.PSRGBInputs[1]= 0x3c011c02;
			pixel_shader.PSRGBOutputs[1]= 0xc00;

			pixel_shader.PSConstant0[2]= meter->gradient_min_color;
			pixel_shader.PSConstant1[2]= meter->flash_color;
			pixel_shader.PSAlphaInputs[2]= 0x0820b220;
			pixel_shader.PSAlphaOutputs[2]= 0xc00;
			pixel_shader.PSRGBInputs[2]= (meter->flash_color_is_negative ? 0xe2 : 0x02) | 0x0c201c00;
			pixel_shader.PSRGBOutputs[2]= 0xc00;

			pixel_shader.PSConstant0[3]= meter->background_color;
			pixel_shader.PSConstant1[3]= meter->tint_color;
			pixel_shader.PSAlphaInputs[3]= 0x12201120;
			pixel_shader.PSAlphaOutputs[3]= 0x4c00;
			pixel_shader.PSRGBInputs[3]= 0x0c200120;
			pixel_shader.PSRGBOutputs[3]= 0x4c00;

			pixel_shader.PSFinalCombinerInputsABCD= 0x0c180000;
			pixel_shader.PSFinalCombinerInputsEFG= 0x1c00;
		}
		else if (parameters->map[0])
		{
			real_argb_color colors[NUMBER_OF_DYNAMIC_SCREEN_GEOMETRY_MAPS];
			short combiner_count;

			csmemset(&pixel_shader, 0, sizeof(pixel_shader));
			pixel_shader.PSTextureModes= PS_TEXTUREMODES(parameters->map[0] ? PS_TEXTUREMODES_PROJECT2D : PS_TEXTUREMODES_NONE, parameters->map[1] ? PS_TEXTUREMODES_PROJECT2D : PS_TEXTUREMODES_NONE, parameters->map[2] ? PS_TEXTUREMODES_PROJECT2D : PS_TEXTUREMODES_NONE, PS_TEXTUREMODES_NONE);

			colors[0].rgb= *(parameters->map_tint[0] ? parameters->map_tint[0] : global_real_rgb_white);
			colors[1].rgb= *(parameters->map_tint[1] ? parameters->map_tint[1] : global_real_rgb_white);
			colors[2].rgb= *(parameters->map_tint[2] ? parameters->map_tint[2] : global_real_rgb_white);
			colors[0].alpha= parameters->map_fade[0] ? *parameters->map_fade[0] : 1.f;
			colors[1].alpha= parameters->map_fade[1] ? *parameters->map_fade[1] : 1.f;
			colors[2].alpha= parameters->map_fade[2] ? *parameters->map_fade[2] : 1.f;

			pixel_shader.PSConstant0[0]= real_argb_color_to_pixel32(&colors[0]);
			pixel_shader.PSConstant1[0]= real_argb_color_to_pixel32(&colors[1]);
			pixel_shader.PSConstant0[1]= real_argb_color_to_pixel32(&colors[2]);
			pixel_shader.PSConstant0[4]= real_argb_color_to_pixel32(&parameters->plasma_fade);
			pixel_shader.PSConstant0[5]= real_argb_color_to_pixel32(&parameters->plasma_fade);
			pixel_shader.PSConstant0[6]= real_argb_color_to_pixel32(&parameters->plasma_fade);
			pixel_shader.PSConstant0[7]= real_argb_color_to_pixel32(&parameters->plasma_fade);

			pixel_shader.PSRGBOutputs[0]= 0x89;
			pixel_shader.PSAlphaOutputs[0]= 0x89;
			pixel_shader.PSRGBInputs[0]= 0x08010902;
			pixel_shader.PSAlphaInputs[0]= 0x18111912;
			pixel_shader.PSRGBInputs[1]= 0x0a010804;
			pixel_shader.PSRGBOutputs[1]= 0xac;
			pixel_shader.PSAlphaInputs[1]= 0x1a111814;
			pixel_shader.PSAlphaOutputs[1]= 0xac;
			combiner_count= 2;

			if (parameters->map[1])
			{
				switch (parameters->map0_to_1_blend_function)
				{
				case 0:
					pixel_shader.PSRGBInputs[combiner_count]= 0x0c200920;
					pixel_shader.PSAlphaInputs[combiner_count]= 0x1c201920;
					pixel_shader.PSAlphaOutputs[combiner_count]= 0xc00;
					pixel_shader.PSRGBOutputs[combiner_count]= 0xc00;
					break;
				case 1:
					pixel_shader.PSRGBInputs[combiner_count]= 0x0c090000;
					pixel_shader.PSRGBOutputs[combiner_count]= 0xc0;
					pixel_shader.PSAlphaInputs[combiner_count]= 0x1c190000;
					pixel_shader.PSAlphaOutputs[combiner_count]= 0xc0;
					break;
				case 2:
					pixel_shader.PSRGBInputs[combiner_count]= 0x0c20e920;
					pixel_shader.PSAlphaInputs[combiner_count]= 0x1c20f920;
					pixel_shader.PSAlphaOutputs[combiner_count]= 0xc00;
					pixel_shader.PSRGBOutputs[combiner_count]= 0xc00;
					break;
				case 3:
					pixel_shader.PSRGBInputs[combiner_count]= 0x0c090000;
					pixel_shader.PSRGBOutputs[combiner_count]= 0x100c0;
					pixel_shader.PSAlphaInputs[combiner_count]= 0x1c190000;
					pixel_shader.PSAlphaOutputs[combiner_count]= 0x100c0;
					break;
				case 4:
					pixel_shader.PSRGBInputs[combiner_count]= 0x0c090000;
					pixel_shader.PSRGBOutputs[combiner_count]= 0x20c0;
					pixel_shader.PSAlphaInputs[combiner_count]= 0x1c190000;
					pixel_shader.PSAlphaOutputs[combiner_count]= 0xc0;
					break;
				case 5:
					pixel_shader.PSAlphaInputs[2]= 0x0820a920;
					pixel_shader.PSRGBInputs[2]= 0x1920b820;
					pixel_shader.PSAlphaInputs[3]= 0x1c1c0c0c;
					pixel_shader.PSAlphaOutputs[3]= 0x24c00;
					pixel_shader.PSRGBInputs[3]= 0;
					pixel_shader.PSRGBOutputs[3]= 0;
					pixel_shader.PSAlphaInputs[4]= 0x5c5c;
					pixel_shader.PSAlphaOutputs[4]= 0x4d00;
					pixel_shader.PSRGBInputs[4]= 0;
					pixel_shader.PSRGBOutputs[4]= 0;
					combiner_count= 5;
					pixel_shader.PSAlphaInputs[5]= 0;
					pixel_shader.PSAlphaOutputs[5]= 0xc00;
					pixel_shader.PSRGBInputs[5]= 0x1ca01da0;
					pixel_shader.PSRGBOutputs[5]= 0xc00;
					pixel_shader.PSAlphaOutputs[2]= 0xc00;
					pixel_shader.PSRGBOutputs[2]= 0xc00;
					break;
				}
				combiner_count++;
			}

			if (parameters->map[2])
			{
				switch (parameters->map1_to_2_blend_function)
				{
				case 0:
					if (parameters->map0_to_1_blend_function==5)
					{
						pixel_shader.PSRGBInputs[combiner_count]= (parameters->doing_plasma_effect ? 0x04 : 0x20) | 0x0c010a00;
					}
					else
					{
						pixel_shader.PSRGBInputs[combiner_count]= 0x0c200a20;
					}
					pixel_shader.PSRGBOutputs[combiner_count]= 0xc00;
					pixel_shader.PSAlphaInputs[combiner_count]= 0x1c201a20;
					pixel_shader.PSAlphaOutputs[combiner_count]= 0xc00;
					break;
				case 1:
					pixel_shader.PSRGBInputs[combiner_count]= 0x0c0a0000;
					pixel_shader.PSRGBOutputs[combiner_count]= 0xc0;
					pixel_shader.PSAlphaInputs[combiner_count]= 0x1c1a0000;
					pixel_shader.PSAlphaOutputs[combiner_count]= 0xc0;
					break;
				case 2:
					pixel_shader.PSRGBInputs[combiner_count]= 0x0c20ea20;
					pixel_shader.PSRGBOutputs[combiner_count]= 0xc00;
					pixel_shader.PSAlphaInputs[combiner_count]= 0x1c20fa20;
					pixel_shader.PSAlphaOutputs[combiner_count]= 0xc00;
					break;
				case 3:
					pixel_shader.PSRGBInputs[combiner_count]= 0x0c0a0000;
					pixel_shader.PSRGBOutputs[combiner_count]= 0x100c0;
					pixel_shader.PSAlphaInputs[combiner_count]= 0x1c1a0000;
					pixel_shader.PSAlphaOutputs[combiner_count]= 0x100c0;
					break;
				case 4:
					pixel_shader.PSRGBInputs[combiner_count]= 0x0c0a0000;
					pixel_shader.PSRGBOutputs[combiner_count]= 0x20c0;
					pixel_shader.PSAlphaInputs[combiner_count]= 0x1c1a0000;
					pixel_shader.PSAlphaOutputs[combiner_count]= 0xc0;
					break;
				}
				combiner_count++;
			}

			pixel_shader.PSCombinerCount= combiner_count | 0x11100;
			pixel_shader.PSFinalCombinerInputsABCD= 0x0c;
			pixel_shader.PSFinalCombinerInputsEFG= 0x1c00;
		}

		rasterizer_set_pixel_shader(&pixel_shader);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_CCW);
		rasterizer_set_vertex_shader_permutation(4, 8, 1);

		IDirect3DDevice8_Begin(global_d3d_device, D3DPT_TRIANGLEFAN);
		for (vertex_index= 0; vertex_index<NUMBER_OF_PSUEDO_DYNAMIC_SCREEN_QUAD_VERTICES; vertex_index++)
		{
			code_0014f0f0(&vertices[vertex_index]);
		}
		IDirect3DDevice8_End(global_d3d_device);

		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ALPHAKILL, D3DTALPHAKILL_DISABLE);
	}
}
