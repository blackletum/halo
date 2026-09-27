/*
RASTERIZER_XBOX_ACTIVE_CAMOUFLAGE.C

symbols in this file:
001488C0 0070:
	_real_alpha_to_pixel32 (0000)
00148930 01b0:
	_D3DDevice_SetRenderState (0000)
00148AE0 0050:
	_D3DDevice_SetTextureStageState (0000)
00148B30 0020:
	_rasterizer_active_camouflage_set_visibility (0000)
00148B50 0220:
	_IDirect3DDevice8_SetRenderState@12 (0000)
00148D70 0060:
	_IDirect3DDevice8_SetTextureStageState@16 (0000)
00148DD0 0010:
	_IDirect3DDevice8_SetVertexShaderConstant@16 (0000)
00148DE0 0010:
	_IDirect3DDevice8_SetVertexData2s@16 (0000)
00148DF0 0010:
	_IDirect3DDevice8_Begin@8 (0000)
00148E00 0010:
	_IDirect3DDevice8_End@4 (0000)
00148E10 0340:
	_rasterizer_active_camouflage_cache_primary_render_target (0000)
00149150 07e0:
	_rasterizer_active_camouflage_draw (0000)
0028DA50 004e:
	??_C@_0EO@HDJOIPE@global_window_parameters?4rasteri@ (0000)
0028DAA0 0043:
	??_C@_0ED@HJIAGIIM@c?3?2halo?2SOURCE?2rasterizer?2xbox?2r@ (0000)
0028DAE8 0045:
	??_C@_0EF@JPIBDDAJ@?$CBTEST_FLAG?$CIgroup?9?$DOgeometry_flags@ (0000)
0028DB30 002a:
	??_C@_0CK@KJCGLLHP@local_active_camouflage_debug_ca@ (0000)
0028DB5C 001e:
	??_C@_0BO@PEAJKHII@group?9?$DOeffect?4intensity?$DM?$DN1?40f?$AA@ (0000)
0028DB7C 001d:
	??_C@_0BN@DOLIELKA@group?9?$DOeffect?4intensity?$DO0?40f?$AA@ (0000)
0028DBA0 0040:
	??_C@_0EA@OILAHNPH@group?9?$DOeffect?4type?$DN?$DN_render_mode@ (0000)
0028DBE0 000e:
	??_C@_0O@KHNLKNGC@group?9?$DOshader?$AA@ (0000)
0045E8E0 0006:
	_local_active_camouflage_visibility_flag (0000)
	_local_active_camouflage_debug_cached_flag (0001)
	_local_active_camouflage_debug_cache_count (0004)
*/

/* ---------- headers */

#include "cseries.h"
#include "cseries_windows.h"
#include "errors.h"
#include "real_math.h"
#include "tag_groups.h"
#include "game_globals.h"
#include "render.h"
#include "rasterizer.h"
#include "xbox/rasterizer_xbox.h"
#include "shaders/shader_definitions.h"
#include "shaders/shaders.h"

/* ---------- constants */

enum
{
	_active_camouflage_tint_edge_density_bit= 0,
};

/* ---------- prototypes */

void *shader_get_and_verify_type(struct shader const *shader, short type);

short rasterizer_transparent_geometry_get_primary_vertex_type(struct transparent_geometry_group const *group);
void rasterizer_transparent_geometry_group_draw__internal(struct transparent_geometry_group const *group, boolean has_lightmap);
void *rasterizer_set_texture(short stage, short type, short usage, long bitmap_group_index, short bitmap_index);
boolean rasterizer_set_texture_direct(short stage, long bitmap_group_index, short bitmap_index);
void rasterizer_set_stencil_mode(short stencil_mode);
void rasterizer_set_frustum_z(real z_near, real z_far);
void rasterizer_set_target(short target, short mipmap_index, unsigned long background_color, boolean clear, boolean zbuffer);
void *rasterizer_set_target_as_texture(short stage, short target, short max_mipmap);
void rasterizer_secondary_render_target_debug(rectangle2d const *bounds);
void rasterizer_set_vertex_shader_permutation(short vertex_shader, short permutation, short type);
void rasterizer_set_pixel_shader(D3DPIXELSHADERDEF *pixel_shader_definition);
void SetRenderStateSmart(D3DRENDERSTATETYPE state, unsigned long value);

void rasterizer_profile_enable(boolean enable);
void rasterizer_models_begin(boolean sky);
void rasterizer_model_begin(struct rasterizer_model_begin_parameters const *parameters, boolean do_not_change_z_stencil_states);
void rasterizer_model_draw(struct shader const *shader, short shader_permutation_index, struct triangle_buffer const *triangle_buffer, long dynamic_triangle_buffer_index, long triangle_count, struct vertex_buffer const *vertex_buffer, long dynamic_vertex_buffer_index);
void rasterizer_model_end(void);
void rasterizer_models_end(void);

__inline unsigned long real_alpha_to_pixel32(
	real alpha)
{
	real scale= 255.f;
	long result;

	match_assert("..\\bitmaps\\bitmaps_inlines.h", 291, alpha>=0.0f && alpha<=1.0f);

	__asm
	{
		fld alpha
		fld scale
		fmulp st(1), st
		fistp result
		shl result, 24
	}

	return result;
}

/* ---------- globals */

extern struct rasterizer_window_begin_parameters global_window_parameters;
extern struct game_globals_rasterizer_data *global_rasterizer_data;
extern D3DPIXELSHADERDEF pixel_shader;

static boolean local_active_camouflage_visibility_flag;
static boolean local_active_camouflage_debug_cached_flag;
static short local_active_camouflage_debug_cache_count;

/* ---------- public code */

void rasterizer_active_camouflage_set_visibility(
	boolean visible)
{
	local_active_camouflage_visibility_flag= visible;
	if (!visible)
	{
		local_active_camouflage_debug_cache_count= 0;
		local_active_camouflage_debug_cached_flag= FALSE;
	}
}

void rasterizer_active_camouflage_cache_primary_render_target(
	void)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_active_camouflage.c", 41, global_d3d_device);

	if (rasterizer_debug_options.active_camouflage_enabled && local_active_camouflage_visibility_flag)
	{
		rectangle2d bounds;

		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_active_camouflage.c", 46, global_window_parameters.rasterizer_target==_rasterizer_target_render_primary);

		rasterizer_set_target_as_texture(0, _rasterizer_target_render_primary, 0);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MIPFILTER, D3DTEXF_POINT);

		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_CCW);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_BLUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHABLENDENABLE, FALSE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHATESTENABLE, FALSE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZENABLE, D3DZB_FALSE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZBIAS, 0);

		rasterizer_set_vertex_shader_permutation(4, 8, 0);
		{
			real vertex_constants[5][4]=
			{
				{ 1.f/160.f, 0.f, 0.f, -1.003125f },
				{ 0.f, -1.f/120.f, 0.f, 1.0041667f },
				{ 0.f, 0.f, 0.f, 0.5f },
				{ 0.f, 0.f, 0.f, 1.f },
				{ 1.f, 1.f, 0.f, 1.f },
			};

			IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, -68, vertex_constants, 5);
		}

		csmemset(&pixel_shader, 0, sizeof(pixel_shader));
		pixel_shader.PSTextureModes= 1;
		pixel_shader.PSCombinerCount= 1;
		pixel_shader.PSFinalCombinerInputsABCD= 8;
		rasterizer_set_pixel_shader(&pixel_shader);

		rasterizer_set_target(_rasterizer_target_render_secondary, 0, 0, FALSE, FALSE);
		rasterizer_set_stencil_mode(_rasterizer_stencil_mode_none);

		IDirect3DDevice8_Begin(global_d3d_device, D3DPT_TRIANGLEFAN);
		IDirect3DDevice8_SetVertexData2s(global_d3d_device, 4, global_window_parameters.camera.viewport_bounds.x0, global_window_parameters.camera.viewport_bounds.y1);
		IDirect3DDevice8_SetVertexData2s(global_d3d_device, 0, 0, 0);
		IDirect3DDevice8_SetVertexData2s(global_d3d_device, 4, global_window_parameters.camera.viewport_bounds.x1, global_window_parameters.camera.viewport_bounds.y1);
		IDirect3DDevice8_SetVertexData2s(global_d3d_device, 0, 320, 0);
		IDirect3DDevice8_SetVertexData2s(global_d3d_device, 4, global_window_parameters.camera.viewport_bounds.x1, global_window_parameters.camera.viewport_bounds.y0);
		IDirect3DDevice8_SetVertexData2s(global_d3d_device, 0, 320, 240);
		IDirect3DDevice8_SetVertexData2s(global_d3d_device, 4, global_window_parameters.camera.viewport_bounds.x0, global_window_parameters.camera.viewport_bounds.y0);
		IDirect3DDevice8_SetVertexData2s(global_d3d_device, 0, 0, 240);
		IDirect3DDevice8_End(global_d3d_device);

		rasterizer_set_target(global_window_parameters.rasterizer_target, 0, 0, FALSE, TRUE);
		rasterizer_set_stencil_mode(_rasterizer_stencil_mode_reject);

		bounds.x0= 512;
		bounds.x1= 640;
		bounds.y0= 32*(3*local_active_camouflage_debug_cache_count+3);
		bounds.y1= 32*(3*local_active_camouflage_debug_cache_count+6);
		rasterizer_secondary_render_target_debug(&bounds);
		local_active_camouflage_debug_cache_count++;

		if (!rasterizer_debug_options.active_camouflage_multipass_enabled)
		{
			local_active_camouflage_visibility_flag= FALSE;
		}
		local_active_camouflage_debug_cached_flag= TRUE;
	}
}

// TODO: instruction scheduling differs around the shader_texture_animation_evaluate constant setup and
// the active camouflage parameter interpolation (x87 operand order)
void rasterizer_active_camouflage_draw(
	struct transparent_geometry_group const *group)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_active_camouflage.c", 152, group);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_active_camouflage.c", 153, group->shader);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_active_camouflage.c", 154, group->effect.type==_render_model_effect_type_active_camouflage);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_active_camouflage.c", 155, group->effect.intensity>0.0f);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_active_camouflage.c", 156, group->effect.intensity<=1.0f);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_active_camouflage.c", 157, global_d3d_device);

	if (rasterizer_debug_options.active_camouflage_enabled && global_window_parameters.rasterizer_target==_rasterizer_target_render_primary)
	{
		struct shader_model const *model= shader_get_and_verify_type(group->shader, _shader_type_model);
		real_vector4d vertex_constants[3];

		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_active_camouflage.c", 164, local_active_camouflage_debug_cached_flag);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_active_camouflage.c", 165, !TEST_FLAG(group->geometry_flags, _rasterizer_geometry_no_queue_bit));

		if (TEST_FLAG(group->geometry_flags, _rasterizer_geometry_first_person_bit))
		{
			rasterizer_set_frustum_z(rasterizer_globals.z_near_first_person, rasterizer_globals.z_far_first_person);
		}

		if (group->effect.intensity==1.f)
		{
			rasterizer_set_texture(0, 0, 1, model->model.base_map.index, group->shader_permutation_index);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSU, D3DTADDRESS_WRAP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);

			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, TEST_FLAG(model->model.flags, _shader_model_two_sided_bit) ? D3DCULL_NONE : D3DCULL_CCW);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_COLORWRITEENABLE, 0);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHABLENDENABLE, FALSE);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHATESTENABLE, TRUE);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHAREF, 127);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZENABLE, D3DZB_TRUE);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZWRITEENABLE, TRUE);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZBIAS, 0);

			rasterizer_set_vertex_shader_permutation(13, rasterizer_transparent_geometry_get_primary_vertex_type(group), 0);

			vertex_constants[0].j= model->model.detail_map_v_scale*model->model.detail_map_scale;
			vertex_constants[0].i= model->model.detail_map_scale;
			vertex_constants[0].k= 1.f;
			vertex_constants[0].l= 1.f;
			vertex_constants[1].i= 1.f;
			vertex_constants[1].j= 0.f;
			vertex_constants[1].k= 0.f;
			vertex_constants[1].l= 0.f;
			vertex_constants[2].i= 0.f;
			vertex_constants[2].j= 1.f;
			vertex_constants[2].k= 0.f;
			vertex_constants[2].l= 0.f;
			shader_texture_animation_evaluate(&model->model.animation, group->animation,
				model->model.map_scale.i*group->model_base_map_scale.i, model->model.map_scale.j*group->model_base_map_scale.j,
				0.f, 0.f, 0.f, global_frame_parameters.game_time_sec,
				&vertex_constants[1], &vertex_constants[2]);
			IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, -84, vertex_constants, 3);

			csmemset(&pixel_shader, 0, sizeof(pixel_shader));
			pixel_shader.PSTextureModes= 1;
			pixel_shader.PSCombinerCount= 1;
			pixel_shader.PSFinalCombinerInputsEFG= 0x1800;
			rasterizer_set_pixel_shader(&pixel_shader);

			rasterizer_transparent_geometry_group_draw__internal(group, FALSE);
		}
		else
		{
			struct rasterizer_model_begin_parameters parameters;

			parameters.geometry_flags= group->geometry_flags & FLAG(_rasterizer_geometry_first_person_bit);
			parameters.skinning.node_matrices= group->node_matrices;
			parameters.skinning.node_matrix_count= group->node_matrix_count;
			parameters.centroid= group->centroid;
			csmemset(&parameters.effect, 0, sizeof(parameters.effect));
			parameters.base_map_scale= group->model_base_map_scale;

			if (group->lighting)
			{
				csmemcpy(&parameters.lighting, group->lighting, sizeof(parameters.lighting));
			}
			else
			{
				csmemset(&parameters.lighting, 0, sizeof(parameters.lighting));
			}

			if (group->animation)
			{
				parameters.animation= *group->animation;
			}
			else
			{
				csmemset(&parameters.animation, 0, sizeof(parameters.animation));
			}

			rasterizer_profile_enable(FALSE);
			rasterizer_models_begin(FALSE);
			rasterizer_model_begin(&parameters, TRUE);
			rasterizer_model_draw(group->shader, group->shader_permutation_index, group->triangle_buffer, group->dynamic_triangle_buffer_index,
				group->triangle_count, group->vertex_buffers, group->dynamic_vertex_buffer_index);
			rasterizer_model_end();
			rasterizer_models_end();
			rasterizer_profile_enable(TRUE);
		}

		rasterizer_set_texture_direct(0, global_rasterizer_data->active_camouflage_distortion.index, 0);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);

		rasterizer_set_target_as_texture(2, _rasterizer_target_render_secondary, 0);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_MIPFILTER, D3DTEXF_POINT);

		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, TEST_FLAG(model->model.flags, _shader_model_two_sided_bit) ? D3DCULL_NONE : D3DCULL_CCW);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_BLUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHATESTENABLE, FALSE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZENABLE, D3DZB_TRUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZWRITEENABLE, FALSE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZFUNC, D3DCMP_EQUAL);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZBIAS, 0);

		if (group->effect.intensity<1.f)
		{
			SetRenderStateSmart(D3DRS_ALPHABLENDENABLE, TRUE);
			SetRenderStateSmart(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			SetRenderStateSmart(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			SetRenderStateSmart(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		}
		else
		{
			SetRenderStateSmart(D3DRS_ALPHABLENDENABLE, FALSE);
		}

		rasterizer_set_vertex_shader_permutation(64, rasterizer_transparent_geometry_get_primary_vertex_type(group), 0);

		{
			real inverse_parameter= 1.f-group->effect.parameter;
			real refraction_amount, distance_falloff;
			real_rgb_color tint_color;

			refraction_amount= inverse_parameter*global_rasterizer_data->active_camouflage_refraction_amount + global_rasterizer_data->active_camouflage_hyper_stealth_refraction_amount*group->effect.parameter;
			distance_falloff= inverse_parameter*global_rasterizer_data->active_camouflage_distance_falloff + global_rasterizer_data->active_camouflage_hyper_stealth_distance_falloff*group->effect.parameter;
			tint_color.red= inverse_parameter*global_rasterizer_data->active_camouflage_tint_color.red + global_rasterizer_data->active_camouflage_hyper_stealth_tint_color.red*group->effect.parameter;
			tint_color.green= inverse_parameter*global_rasterizer_data->active_camouflage_tint_color.green + global_rasterizer_data->active_camouflage_hyper_stealth_tint_color.green*group->effect.parameter;
			tint_color.blue= inverse_parameter*global_rasterizer_data->active_camouflage_tint_color.blue + global_rasterizer_data->active_camouflage_hyper_stealth_tint_color.blue*group->effect.parameter;

			vertex_constants[0].i= refraction_amount*group->effect.intensity;
			vertex_constants[0].j= distance_falloff;
			vertex_constants[0].k= 320.f;
			vertex_constants[0].l= 240.f;
			vertex_constants[1].i= 0.f;
			vertex_constants[1].j= 0.f;
			vertex_constants[1].k= 0.f;
			vertex_constants[1].l= 0.f;
			vertex_constants[2].i= tint_color.red;
			vertex_constants[2].j= tint_color.green;
			vertex_constants[2].k= tint_color.blue;
			vertex_constants[2].l= 0.f;
		}
		IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, -84, vertex_constants, 3);

		csmemset(&pixel_shader, 0, sizeof(pixel_shader));
		pixel_shader.PSTextureModes= 0x2623;
		pixel_shader.PSInputTexture= 0;
		pixel_shader.PSDotMapping= 0x11;
		pixel_shader.PSCombinerCount= 2;
		pixel_shader.PSRGBInputs[0]= TEST_FLAG(global_rasterizer_data->active_camouflage_flags, _active_camouflage_tint_edge_density_bit) ? 0x38201804 : 0x04200000;
		pixel_shader.PSRGBOutputs[0]= 0xc00;
		pixel_shader.PSRGBInputs[1]= 0x3420140c;
		pixel_shader.PSRGBOutputs[1]= 0xc00;
		pixel_shader.PSFinalCombinerConstant0= real_alpha_to_pixel32(group->effect.intensity);
		pixel_shader.PSFinalCombinerInputsABCD= 0x0a0c0000;
		pixel_shader.PSFinalCombinerInputsEFG= 0x1100;
		rasterizer_set_pixel_shader(&pixel_shader);

		rasterizer_transparent_geometry_group_draw__internal(group, FALSE);

		if (TEST_FLAG(group->geometry_flags, _rasterizer_geometry_first_person_bit))
		{
			rasterizer_set_frustum_z(0.f, 0.f);
		}
	}
}
