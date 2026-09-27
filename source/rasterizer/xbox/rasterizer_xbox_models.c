/*
RASTERIZER_XBOX_MODELS.C

symbols in this file:
0015A150 01b0:
	_D3DDevice_SetRenderState (0000)
0015A300 0050:
	_D3DDevice_SetTextureStageState (0000)
0015A350 03f0:
	_code_0015a350 (0000)
0015A740 0220:
	_IDirect3DDevice8_SetRenderState@12 (0000)
0015A960 0060:
	_IDirect3DDevice8_SetTextureStageState@16 (0000)
0015A9C0 0010:
	_IDirect3DDevice8_SetVertexShaderConstant@16 (0000)
0015A9D0 0040:
	__rasterizer_models_begin (0000)
0015AA10 0080:
	__rasterizer_model_end (0000)
0015AA90 0030:
	__rasterizer_models_end (0000)
0015AAC0 0040:
	_rasterizer_model_ambient_reflection_tint (0000)
0015AB00 0c20:
	_rasterizer_model_draw_environment_shader (0000)
0015B720 01c0:
	__rasterizer_model_begin (0000)
0015B8E0 0510:
	__rasterizer_model_transparent_geometry_submit (0000)
0015BDF0 1430:
	__rasterizer_model_draw (0000)
00291818 0042:
	??_C@_0EC@KBJMJLJB@detail_mask?$DO?$DN0?5?$CG?$CG?5detail_mask?$DMNU@ (0000)
00291860 004e:
	??_C@_0EO@GAMPAHAK@detail_function?$DO?$DN0?5?$CG?$CG?5detail_fun@ (0000)
002918B0 0038:
	??_C@_0DI@FGKEFDJL@c?3?2halo?2SOURCE?2rasterizer?2xbox?2r@ (0000)
002918E8 0011:
	??_C@_0BB@BMPHCOIP@local_parameters?$AA@ (0000)
002918FC 002f:
	??_C@_0CP@IHIFHMCH@cc0_error?4blue?5?$DO?$DN0?40f?5?$CG?$CG?5cc0_err@ (0000)
0029192C 002f:
	??_C@_0CP@KGDHFBB@cc0_error?4green?$DO?$DN0?40f?5?$CG?$CG?5cc0_err@ (0000)
0029195C 002d:
	??_C@_0CN@LKMEOKHH@cc0_error?4red?5?$DO?$DN0?40f?5?$CG?$CG?5cc0_erro@ (0000)
0029198C 0023:
	??_C@_0CD@OECGPNGC@cc1?4blue?5?$DO?$DN0?40f?5?$CG?$CG?5cc1?4blue?5?$DM?$DN1?4@ (0000)
002919B0 0023:
	??_C@_0CD@DFKMLKHD@cc1?4green?$DO?$DN0?40f?5?$CG?$CG?5cc1?4green?$DM?$DN1?4@ (0000)
002919D4 0021:
	??_C@_0CB@CPJFGMCD@cc1?4red?5?$DO?$DN0?40f?5?$CG?$CG?5cc1?4red?5?$DM?$DN1?40f@ (0000)
002919F8 0023:
	??_C@_0CD@EPNLIMOH@cc0?4blue?5?$DO?$DN0?40f?5?$CG?$CG?5cc0?4blue?5?$DM?$DN1?4@ (0000)
00291A1C 0023:
	??_C@_0CD@JOFBMLPG@cc0?4green?$DO?$DN0?40f?5?$CG?$CG?5cc0?4green?$DM?$DN1?4@ (0000)
00291A40 0021:
	??_C@_0CB@PMOEFNHH@cc0?4red?5?$DO?$DN0?40f?5?$CG?$CG?5cc0?4red?5?$DM?$DN1?40f@ (0000)
00291A68 0074:
	??_C@_0HE@IBEOFMMD@global_window_parameters?4fog?4atm@ (0000)
00291ADC 0039:
	??_C@_0DJ@MAOJHDPF@group?9?$DOactive_camouflage_transpa@ (0000)
00291B18 0030:
	??_C@_0DA@GOHJDLCN@local_parameters?9?$DOeffect?4source_@ (0000)
00291B48 0032:
	??_C@_0DC@CEHNCDIC@shader_type_is_valid_for_model?$CIs@ (0000)
00291B7C 003b:
	??_C@_0DL@NALNBEEB@?$CD?$CD?$CD?5ERROR?5model?5effect?5type?5?$CD?$CFd?5@ (0000)
00291BB8 0045:
	??_C@_0EF@FGOGCHIG@diffuse_change_color?4blue?5?$DO?$DN0?40f@ (0000)
00291C00 0045:
	??_C@_0EF@PPFPLJEH@diffuse_change_color?4green?$DO?$DN0?40f@ (0000)
00291C48 0043:
	??_C@_0ED@PEIKOPIA@diffuse_change_color?4red?5?$DO?$DN0?40f?5@ (0000)
00291C8C 003b:
	??_C@_0DL@BIOGNNCB@external_color?9?$DOblue?5?$DO?$DN0?40f?5?$CG?$CG?5e@ (0000)
00291CC8 003b:
	??_C@_0DL@HMDMJINO@external_color?9?$DOgreen?$DO?$DN0?40f?5?$CG?$CG?5e@ (0000)
00291D04 0039:
	??_C@_0DJ@CNNDHOMN@external_color?9?$DOred?5?$DO?$DN0?40f?5?$CG?$CG?5ex@ (0000)
00291D40 004b:
	??_C@_0EL@GNHHGHCF@self_illumination_color?4blue?5?$DO?$DN0@ (0000)
00291D90 004b:
	??_C@_0EL@HBGILNPJ@self_illumination_color?4green?$DO?$DN0@ (0000)
00291DE0 0049:
	??_C@_0EJ@FOGGPAPE@self_illumination_color?4red?5?$DO?$DN0?4@ (0000)
00291E2C 003d:
	??_C@_0DN@HPMCIMLL@shader_model?9?$DOmodel?4self_illumin@ (0000)
00291E6C 0038:
	??_C@_0DI@PCENFHCM@local_model_effect_type?$DN?$DN_render@ (0000)
00291EA4 0026:
	??_C@_0CG@IGIAPBFN@shader?9?$DObase?4type?$DN?$DN_shader_type_@ (0000)
0030CEFB 0001:
	_local_pixel_shader_dirty_flag (0000)
00465D68 00be:
	_bss_00465d68 (0000)
	_bss_00465d6c (0000)
	_bss_00465d70 (0000)
	_bss_00465d74 (0000)
	_local_group (0000)
	_local_parameters (0000)
	_local_parameters_queued_flag (0000)
	_local_model_effect_type (0000)
	_local_sky_flag (0000)
	_local_planar_fog_flag (0000)
	_local_environment_fog_screen_flag (0000)
	_local_do_not_change_z_stencil_states (0000)
00465E26 0001:
	?warned@?1??_rasterizer_model_transparent_geometry_submit@@9@9 (0000)
*/

/* ---------- headers */

#include "cseries.h"
#include "cseries_windows.h"
#include "errors.h"
// these are called out of line in this file (inline budget of _rasterizer_model_draw)
#define subtract_vectors3d subtract_vectors3d_inline
#define point_from_line3d point_from_line3d_inline
#define plane3d_distance_to_point plane3d_distance_to_point_inline
#include "real_math.h"
#undef subtract_vectors3d
#undef point_from_line3d
#undef plane3d_distance_to_point
#include "tag_groups.h"
#include "shaders/shader_definitions.h"
#include "rasterizer.h"
#include "rasterizer_geometry.h"
#include "render.h"
#include "periodic_functions.h"
#include "xbox/rasterizer_xbox.h"

/* ---------- constants */

enum
{
	NUMBER_OF_SHADER_MODEL_DETAIL_FUNCTIONS = 3,
	NUMBER_OF_SHADER_MODEL_DETAIL_MASKS = 9,
};

enum
{
	_model_geometry_do_not_draw_bit = 1,
	_model_geometry_first_person_bit = 7,
};

/* ---------- structures */

struct render_sort_filth
{
	short *prev_group_presorted_index_reference;
	short *next_group_presorted_index_reference;
	short group_index;
	short next_part_index;
	short part_index;
	word pad;
};

/* ---------- prototypes */

real_vector3d *subtract_vectors3d(real_vector3d const *a, real_vector3d const *b, real_vector3d *result);
real_point3d *point_from_line3d(real_point3d const *point, real_vector3d const *vector, real t, real_point3d *result);
real plane3d_distance_to_point(real_plane3d const *plane, real_point3d const *point);

void rasterizer_set_stencil_mode(short mode);
void rasterizer_set_frustum_z(real z_near, real z_far);
void rasterizer_set_model_skinning(struct render_skinning const *skinning);
void rasterizer_set_model_lighting(struct render_lighting const *lighting);
boolean rasterizer_environment_fog_screen_model_begin(struct rasterizer_model_begin_parameters const *parameters);
void rasterizer_environment_fog_screen_model_end(void);

void *shader_get_and_verify_type(struct shader const *shader, short type);
boolean shader_type_is_valid_for_model(short shader_type);
boolean shader_is_decal(struct shader const *shader);

struct transparent_geometry_group *rasterizer_transparent_geometry_new_group(void);
struct transparent_geometry_group *rasterizer_transparent_geometry_new_group2(void);
short rasterizer_transparent_geometry_get_group_presorted_index(struct transparent_geometry_group const *group);
void rasterizer_transparent_geometry_groups_begin(void);
void rasterizer_transparent_geometry_group_draw(struct transparent_geometry_group const *group, boolean unknown);
void rasterizer_transparent_geometry_groups_end(void);
void *rasterizer_set_texture(short stage, short type, short usage, long bitmap_group_index, short bitmap_index);
short rasterizer_dynamic_vertices_get_type(long dynamic_vertex_buffer_index);
void rasterizer_set_vertex_shader_permutation(short vertex_shader, short vertex_type, short permutation);
void rasterizer_set_pixel_shader(D3DPIXELSHADERDEF *pixel_shader);
void rasterizer_draw(struct triangle_buffer const *triangle_buffer, long dynamic_triangle_buffer_index, long first_triangle_index, long triangle_count, struct vertex_buffer const *vertex_buffer, long dynamic_vertex_buffer_index);
unsigned long real_argb_color_to_pixel32(real_argb_color const *color);
unsigned long real_rgb_color_to_pixel32(real_rgb_color const *color);
long rasterizer_frame_statistics_count_static_vertices(struct triangle_buffer const *triangle_buffer, struct vertex_buffer const *vertex_buffer);
struct transparent_geometry_group *rasterizer_model_transparent_geometry_submit(struct shader const *shader, short shader_permutation_index, struct triangle_buffer const *triangle_buffer, long dynamic_triangle_buffer_index, long triangle_count, struct vertex_buffer const *vertex_buffer, long dynamic_vertex_buffer_index, real_point3d const *centroid, struct render_sort_filth *sort_filth);
struct transparent_geometry_group *_rasterizer_model_transparent_geometry_submit(struct shader const *shader, short shader_permutation_index, struct triangle_buffer const *triangle_buffer, long dynamic_triangle_buffer_index, long triangle_count, struct vertex_buffer const *vertex_buffer, long dynamic_vertex_buffer_index, real_point3d const *centroid, struct render_sort_filth *sort_filth);
void rasterizer_environment_fog_screen_model_submit(struct shader const *shader, short shader_permutation_index, struct triangle_buffer const *triangle_buffer, long dynamic_triangle_buffer_index, long triangle_count, struct vertex_buffer const *vertex_buffer, long dynamic_vertex_buffer_index);
void rasterizer_active_camouflage_set_visibility(boolean visible);
void SetRenderStateSmart(D3DRENDERSTATETYPE state, unsigned long value);
void SetTextureStageStateSmart(unsigned long stage, D3DTEXTURESTAGESTATETYPE type, unsigned long value);
void shader_texture_animation_evaluate(struct shader_texture_animation const *texture_animation, struct render_animation const *render_animation, real u_scale, real v_scale, real u_offset, real v_offset, real r_offset, real time_value, real_vector4d *u_transform_reference, real_vector4d *v_transform_reference);

/* ---------- globals */

extern struct rasterizer_window_begin_parameters global_window_parameters;
extern boolean rasterizer_model_cortana_hack;
extern D3DPIXELSHADERDEF pixel_shader;

// names unknown (not present in hcex); copies of the queued model parameters for transparent geometry
static struct render_animation const *bss_00465d68;
static struct render_lighting const *bss_00465d6c;
static short bss_00465d70;
static real_matrix4x3 const *bss_00465d74;
static struct transparent_geometry_group local_group; // used when drawing transparent geometry immediately
static struct rasterizer_model_begin_parameters const *local_parameters;
static boolean local_parameters_queued_flag;
static boolean local_pixel_shader_dirty_flag = TRUE;
static short local_model_effect_type;
static boolean local_sky_flag;
static boolean local_planar_fog_flag;
static boolean local_environment_fog_screen_flag;
static boolean local_do_not_change_z_stencil_states;

/* ---------- private code */

static void code_0015a350(
	unsigned long constant0_1,
	short detail_function,
	short detail_mask,
	unsigned long constant0_2,
	unsigned long final_constant0,
	unsigned long constant0_5,
	unsigned long constant1_5,
	boolean detail_after_reflection,
	boolean no_fog)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 106, detail_function>=0 && detail_function<NUMBER_OF_SHADER_MODEL_DETAIL_FUNCTIONS);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 107, detail_mask>=0 && detail_mask<NUMBER_OF_SHADER_MODEL_DETAIL_MASKS);

	{
		long detail_mask_inputs[NUMBER_OF_SHADER_MODEL_DETAIL_MASKS] = { 0x20, 0x2d, 0x0d, 0x3c, 0x1c, 0x39, 0x19, 0x3a, 0x1a };
		long detail_function_inputs[NUMBER_OF_SHADER_MODEL_DETAIL_FUNCTIONS] = { 0xa0, 0x20, 0xa0 };
		long mask;

		pixel_shader.PSConstant0[2] = constant0_2;
		mask = detail_mask_inputs[detail_mask];
		pixel_shader.PSConstant0[1] = constant0_1;
		pixel_shader.PSRGBInputs[3] = ((((detail_function_inputs[detail_function] | ((mask^0x20)<<8))<<8) | mask)<<8) | 0x09;
	}

	if (detail_after_reflection)
	{
		long inputs[NUMBER_OF_SHADER_MODEL_DETAIL_FUNCTIONS] = { 0x0c090c09, 0x0c090000, 0x0c204920 };

		pixel_shader.PSRGBInputs[6] = 0x08040b1d;
		pixel_shader.PSRGBOutputs[6] = 0x00000c00;
		pixel_shader.PSRGBInputs[7] = inputs[detail_function];
		pixel_shader.PSRGBOutputs[7] = 0x00000c00;
	}
	else
	{
		long inputs[NUMBER_OF_SHADER_MODEL_DETAIL_FUNCTIONS] = { 0x08090809, 0x08090000, 0x08204920 };

		pixel_shader.PSRGBInputs[6] = inputs[detail_function];
		pixel_shader.PSRGBOutputs[6] = 0x00000800;
		pixel_shader.PSRGBInputs[7] = 0x08040b1d;
		pixel_shader.PSRGBOutputs[7] = 0x00000c00;
	}

	if (no_fog)
	{
		pixel_shader.PSFinalCombinerInputsABCD = 0x330c0300;
		pixel_shader.PSFinalCombinerInputsEFG = 0x00001800;
	}
	else
	{
		pixel_shader.PSConstant0[5] = constant0_5;
		pixel_shader.PSConstant1[5] = constant1_5;
		pixel_shader.PSFinalCombinerConstant0 = final_constant0;
		pixel_shader.PSFinalCombinerConstant1 = constant1_5;
		pixel_shader.PSFinalCombinerInputsABCD = 0x340f010d;
		pixel_shader.PSFinalCombinerInputsEFG = 0x0c111800;
	}

	if (local_pixel_shader_dirty_flag)
	{
		pixel_shader.PSTextureModes = 0x00018421;
		pixel_shader.PSCombinerCount = 0x00011008;
		pixel_shader.PSConstant0[0] = 0x00ff0000;
		pixel_shader.PSConstant1[0] = 0x0000ff00;
		pixel_shader.PSAlphaInputs[0] = 0x0a200000;
		pixel_shader.PSAlphaOutputs[0] = 0x000000c0;
		pixel_shader.PSRGBInputs[0] = 0x0a020a01;
		pixel_shader.PSRGBOutputs[0] = 0x000030cd;
		pixel_shader.PSAlphaInputs[1] = 0x1c200000;
		pixel_shader.PSAlphaOutputs[1] = 0x00000090;
		pixel_shader.PSRGBInputs[1] = 0x04200c01;
		pixel_shader.PSRGBOutputs[1] = 0x00000400;
		pixel_shader.PSAlphaInputs[2] = 0x0c200d15;
		pixel_shader.PSAlphaOutputs[2] = 0x000000cd;
		pixel_shader.PSRGBInputs[2] = 0x3c201c01;
		pixel_shader.PSRGBOutputs[2] = 0x00000c00;
		pixel_shader.PSRGBOutputs[3] = 0x00000900;
		pixel_shader.PSRGBInputs[4] = 0x0b05040c;
		pixel_shader.PSRGBOutputs[4] = 0x000000b4;
		pixel_shader.PSRGBInputs[5] = 0x022014e1;
		pixel_shader.PSRGBOutputs[5] = 0x00000d00;
		rasterizer_set_pixel_shader(&pixel_shader);
		local_pixel_shader_dirty_flag = FALSE;
	}
	else
	{
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_PSCONSTANT0_1, pixel_shader.PSConstant0[1]);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_PSCONSTANT0_2, pixel_shader.PSConstant0[2]);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_PSCONSTANT0_5, pixel_shader.PSConstant0[5]);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_PSCONSTANT1_5, pixel_shader.PSConstant1[5]);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_PSRGBINPUTS3, pixel_shader.PSRGBInputs[3]);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_PSRGBINPUTS6, pixel_shader.PSRGBInputs[6]);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_PSRGBOUTPUTS6, pixel_shader.PSRGBOutputs[6]);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_PSRGBINPUTS7, pixel_shader.PSRGBInputs[7]);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_PSRGBOUTPUTS7, pixel_shader.PSRGBOutputs[7]);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_PSFINALCOMBINERCONSTANT0, pixel_shader.PSFinalCombinerConstant0);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_PSFINALCOMBINERCONSTANT1, pixel_shader.PSFinalCombinerConstant1);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_PSFINALCOMBINERINPUTSABCD, pixel_shader.PSFinalCombinerInputsABCD);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_PSFINALCOMBINERINPUTSEFG, pixel_shader.PSFinalCombinerInputsEFG);

		if (rasterizer_debug_options.statistics_mode==_rasterizer_statistics_mode_geometry)
		{
			rasterizer_frame_statistics.pushbuffer_size += 44;
		}
	}

	return;
}


/* ---------- public code */

void _rasterizer_models_begin(
	boolean sky)
{
	if (rasterizer_debug_options.draw_models)
	{
		local_pixel_shader_dirty_flag = TRUE;
		local_sky_flag = sky;

		if (sky)
		{
			rasterizer_profile_begin(_rasterizer_profile_model_sky);
		}
		else
		{
			rasterizer_profile_begin(_rasterizer_profile_models);
		}
	}

	return;
}

void _rasterizer_model_begin(
	struct rasterizer_model_begin_parameters const *parameters,
	boolean do_not_change_z_stencil_states)
{
	if (rasterizer_debug_options.draw_models)
	{
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 587, parameters);

		if (TEST_FLAG(parameters->geometry_flags, _model_geometry_first_person_bit) && !do_not_change_z_stencil_states)
		{
			rasterizer_set_stencil_mode(_rasterizer_stencil_mode_write);
			rasterizer_set_frustum_z(rasterizer_globals.z_near_first_person, rasterizer_globals.z_far_first_person);
		}

		local_parameters = parameters;
		local_parameters_queued_flag = FALSE;
		local_do_not_change_z_stencil_states = do_not_change_z_stencil_states;

		if (rasterizer_debug_options.active_camouflage_enabled &&
			global_window_parameters.rasterizer_target==0 &&
			parameters->effect.type==_render_model_effect_type_active_camouflage &&
			parameters->effect.intensity>0.f)
		{
			local_model_effect_type = _render_model_effect_type_active_camouflage;
		}
		else if (parameters->effect.type==_render_model_effect_type_transparent_zbuffered)
		{
			local_model_effect_type = _render_model_effect_type_transparent_zbuffered;
		}
		else
		{
			long skinning_total = rasterizer_frame_statistics.skinning_total;
			long lighting_total;
			long skinning_count;

			rasterizer_set_model_skinning(&parameters->skinning);
			skinning_count = rasterizer_frame_statistics.skinning_total-skinning_total;
			lighting_total = rasterizer_frame_statistics.lighting_total;
			rasterizer_set_model_lighting(&parameters->lighting);
			rasterizer_frame_statistics.skinning_count += skinning_count;
			rasterizer_frame_statistics.lighting_count += rasterizer_frame_statistics.lighting_total-lighting_total;
			local_model_effect_type = _render_model_effect_type_none;
		}

		local_planar_fog_flag = global_window_parameters.fog.planar_mode &&
			!TEST_FLAG(parameters->geometry_flags, 2) &&
			(!TEST_FLAG(parameters->geometry_flags, 6) || dot_product3d(&global_window_parameters.fog.plane.n, (real_vector3d const *)&global_window_parameters.camera.position)-global_window_parameters.fog.plane.d<0.f);

		if (!local_sky_flag && rasterizer_environment_fog_screen_model_begin(parameters))
		{
			local_environment_fog_screen_flag = TRUE;
		}
		else
		{
			local_environment_fog_screen_flag = FALSE;
		}

		if (rasterizer_debug_options.statistics_mode==_rasterizer_statistics_mode_geometry)
		{
			rasterizer_frame_statistics.model_count++;
		}
	}

	return;
}

// TODO: register allocation differs (alpha test enable value, detail map scale copy)
void rasterizer_model_draw_environment_shader(
	struct shader const *shader,
	short shader_permutation_index,
	struct triangle_buffer const *triangle_buffer,
	long dynamic_triangle_buffer_index,
	long triangle_count,
	struct vertex_buffer const *vertex_buffer,
	long dynamic_vertex_buffer_index)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 245, global_d3d_device);

	if (rasterizer_debug_options.draw_models)
	{
		struct shader_environment const *shader_environment;
		real_vector3d camera_to_centroid;
		short permutation;
		float vsh_constants__texscale[12];
		float vsh_constants__effect[8];
		real_argb_color perpendicular_color;
		real_argb_color parallel_color;
		unsigned long cc0_pixel;
		unsigned long cc0_error_pixel;
		unsigned long cc1_pixel;

		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 251, local_parameters);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 252, shader);

		shader_environment = shader_get_and_verify_type(shader, _shader_type_environment);
		vector_from_points3d(&global_window_parameters.camera.position, &local_parameters->centroid, &camera_to_centroid);

		if (TEST_FLAG(local_parameters->geometry_flags, 3))
		{
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZENABLE, D3DZB_FALSE);
		}
		else
		{
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZENABLE, D3DZB_TRUE);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZWRITEENABLE, TRUE);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		}

		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZBIAS, 0);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_CCW);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_BLUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHABLENDENABLE, FALSE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_BLENDOP, D3DBLENDOP_ADD);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHATESTENABLE, TEST_FLAG(shader_environment->environment.flags, 0));
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHAREF, 127);

		rasterizer_set_texture(0, 0, 1, shader_environment->environment.diffuse.base_map.index, shader_permutation_index);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSU, D3DTADDRESS_WRAP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);

		rasterizer_set_texture(1, 0, 2, shader_environment->environment.diffuse.primary_detail_map.index, shader_permutation_index);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_ADDRESSU, D3DTADDRESS_WRAP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);

		rasterizer_set_texture(2, 0, 1, TEST_FLAG(shader_environment->environment.flags, 0) ? shader_environment->environment.diffuse.bump_map.index : NONE, shader_permutation_index);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_ADDRESSU, D3DTADDRESS_WRAP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);

		rasterizer_set_texture(3, 2, 0, shader_environment->environment.reflection.map.index, shader_permutation_index);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_ADDRESSW, D3DTADDRESS_CLAMP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);

		if (TEST_FLAG(shader_environment->environment.flags, 2))
		{
			permutation = 2;
		}
		else if (local_planar_fog_flag)
		{
			permutation = 0;
		}
		else if (local_parameters->lighting.point_light_count>0)
		{
			permutation = 1;
		}
		else if (shader_environment->environment.reflection.map.index==NONE && local_parameters->skinning.node_matrix_count<=1)
		{
			permutation = 3;
		}
		else
		{
			permutation = 2;
		}

		rasterizer_set_vertex_shader_permutation(10, vertex_buffer ? vertex_buffer->type : rasterizer_dynamic_vertices_get_type(dynamic_vertex_buffer_index), permutation);

		if (rasterizer_debug_options.statistics_mode>=1)
		{
			rasterizer_frame_statistics.permutation_counts[permutation] += vertex_buffer->count;
		}

		perpendicular_color.alpha = shader_environment->environment.reflection.view_perpendicular_brightness*local_parameters->lighting.reflection_tint_color.alpha;
		perpendicular_color.red = shader_environment->environment.specular.view_perpendicular_color.red*local_parameters->lighting.reflection_tint_color.red;
		perpendicular_color.green = shader_environment->environment.specular.view_perpendicular_color.green*local_parameters->lighting.reflection_tint_color.green;
		perpendicular_color.blue = shader_environment->environment.specular.view_perpendicular_color.blue*local_parameters->lighting.reflection_tint_color.blue;
		parallel_color.alpha = shader_environment->environment.reflection.view_parallel_brightness*local_parameters->lighting.reflection_tint_color.alpha;
		parallel_color.red = shader_environment->environment.specular.view_parallel_color.red*local_parameters->lighting.reflection_tint_color.red;
		parallel_color.green = shader_environment->environment.specular.view_parallel_color.green*local_parameters->lighting.reflection_tint_color.green;
		parallel_color.blue = shader_environment->environment.specular.view_parallel_color.blue*local_parameters->lighting.reflection_tint_color.blue;

		vsh_constants__texscale[0] = shader_environment->environment.diffuse.primary_detail_map_scale;
		vsh_constants__texscale[1] = shader_environment->environment.diffuse.primary_detail_map_scale;
		vsh_constants__texscale[2] = 1.f;
		vsh_constants__texscale[3] = 1.f;
		vsh_constants__texscale[4] = local_parameters->base_map_scale.i;
		vsh_constants__texscale[5] = 0.f;
		vsh_constants__texscale[6] = 0.f;
		vsh_constants__texscale[7] = 0.f;
		vsh_constants__texscale[8] = 0.f;
		vsh_constants__texscale[9] = local_parameters->base_map_scale.j;
		vsh_constants__texscale[10] = 0.f;
		vsh_constants__texscale[11] = 0.f;

		vsh_constants__effect[0] = perpendicular_color.red-parallel_color.red;
		vsh_constants__effect[1] = perpendicular_color.green-parallel_color.green;
		vsh_constants__effect[2] = perpendicular_color.blue-parallel_color.blue;
		vsh_constants__effect[3] = perpendicular_color.alpha-parallel_color.alpha;
		vsh_constants__effect[4] = parallel_color.red;
		vsh_constants__effect[5] = parallel_color.green;
		vsh_constants__effect[6] = parallel_color.blue;
		vsh_constants__effect[7] = parallel_color.alpha;

		IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, VSH_CONSTANTS__TEXSCALE_OFFSET, vsh_constants__texscale, VSH_CONSTANTS__TEXSCALE_COUNT);
		IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, VSH_CONSTANTS__EFFECT_OFFSET, vsh_constants__effect, VSH_CONSTANTS__EFFECT_COUNT);

		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 436, global_window_parameters.fog.atmospheric_maximum_distance>global_window_parameters.fog.atmospheric_minimum_distance);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 437, global_window_parameters.fog.atmospheric_maximum_distance>0.0f);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 438, global_window_parameters.fog.planar_maximum_distance>0.0f);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 439, global_window_parameters.fog.planar_maximum_depth>0.0f);

		if (rasterizer_debug_options.draw_environment_fog && !TEST_FLAG(local_parameters->geometry_flags, 2))
		{
			real planar_fog_density = PIN((dot_product3d((real_vector3d const *)&global_window_parameters.camera.position, &global_window_parameters.fog.plane.n)-global_window_parameters.fog.plane.d)/global_window_parameters.fog.atmospheric_maximum_distance, 0.f, 1.f);
			real atmospheric_fog_density = PIN((dot_product3d(&camera_to_centroid, &global_window_parameters.camera.forward)-global_window_parameters.fog.atmospheric_minimum_distance)/(global_window_parameters.fog.atmospheric_maximum_distance-global_window_parameters.fog.atmospheric_minimum_distance), 0.f, 1.f)*global_window_parameters.fog.atmospheric_maximum_density;
			real_argb_color cc0;
			real_rgb_color cc0_error;
			real_rgb_color cc1;

			if (TEST_FLAG(global_window_parameters.fog.fog_definition_flags, 1))
			{
				planar_fog_density = 1.f;
			}

			cc0.alpha = 1.f-atmospheric_fog_density;
			cc0.red = global_window_parameters.fog.planar_color.red-(global_window_parameters.fog.planar_color.red*planar_fog_density+(1.f-planar_fog_density)*global_window_parameters.fog.atmospheric_color.red)*atmospheric_fog_density;
			cc0.green = global_window_parameters.fog.planar_color.green-(global_window_parameters.fog.planar_color.green*planar_fog_density+(1.f-planar_fog_density)*global_window_parameters.fog.atmospheric_color.green)*atmospheric_fog_density;
			cc0.blue = global_window_parameters.fog.planar_color.blue-(global_window_parameters.fog.planar_color.blue*planar_fog_density+(1.f-planar_fog_density)*global_window_parameters.fog.atmospheric_color.blue)*atmospheric_fog_density;

			cc0_error.red = PIN(-cc0.red, 0.f, 1.f);
			cc0_error.green = PIN(-cc0.green, 0.f, 1.f);
			cc0_error.blue = PIN(-cc0.blue, 0.f, 1.f);
			cc0.red = PIN(cc0.red, 0.f, 1.f);
			cc0.green = PIN(cc0.green, 0.f, 1.f);
			cc0.blue = PIN(cc0.blue, 0.f, 1.f);

			cc1.red = global_window_parameters.fog.atmospheric_color.red*atmospheric_fog_density;
			cc1.green = global_window_parameters.fog.atmospheric_color.green*atmospheric_fog_density;
			cc1.blue = global_window_parameters.fog.atmospheric_color.blue*atmospheric_fog_density;

			match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 478, cc0.red >=0.0f && cc0.red <=1.0f);
			match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 479, cc0.green>=0.0f && cc0.green<=1.0f);
			match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 480, cc0.blue >=0.0f && cc0.blue <=1.0f);
			match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 481, cc1.red >=0.0f && cc1.red <=1.0f);
			match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 482, cc1.green>=0.0f && cc1.green<=1.0f);
			match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 483, cc1.blue >=0.0f && cc1.blue <=1.0f);
			match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 484, cc0_error.red >=0.0f && cc0_error.red <=1.0f);
			match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 485, cc0_error.green>=0.0f && cc0_error.green<=1.0f);
			match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 486, cc0_error.blue >=0.0f && cc0_error.blue <=1.0f);

			cc0_pixel = real_argb_color_to_pixel32(&cc0);
			cc0_error_pixel = real_rgb_color_to_pixel32(&cc0_error);
			cc1_pixel = real_rgb_color_to_pixel32(&cc1);
		}
		else
		{
			cc0_pixel = cc0_error_pixel = cc1_pixel = 0xff000000;
		}

		code_0015a350(0, shader_environment->environment.diffuse.detail_map_function, 0, 0xffffffff, cc0_pixel, cc0_error_pixel, cc1_pixel, FALSE, TEST_FLAG(shader_environment->environment.flags, 2));

		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_CCW);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_PSRGBINPUTS0, 0xa021819);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_PSRGBOUTPUTS0, 0x20cd);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_PSFINALCOMBINERINPUTSEFG, 0xc111a00);
		rasterizer_draw(triangle_buffer, dynamic_triangle_buffer_index, 0, triangle_count, vertex_buffer, dynamic_vertex_buffer_index);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_PSRGBINPUTS0, 0xa020a01);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_PSRGBOUTPUTS0, 0x30cd);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_PSFINALCOMBINERINPUTSEFG, 0xc111800);

		if (rasterizer_debug_options.statistics_mode==_rasterizer_statistics_mode_geometry)
		{
			rasterizer_frame_statistics.pushbuffer_size += 24;
			rasterizer_frame_statistics.models_solid.primitives++;
			rasterizer_frame_statistics.models_solid.triangles += triangle_count;
			rasterizer_frame_statistics.models_solid.vertices += rasterizer_frame_statistics_count_static_vertices(triangle_buffer, vertex_buffer);
		}
	}

	return;
}

// TODO: plasma modifier intensity source access, stack slot sharing of seed/random phase, some scheduling
void _rasterizer_model_draw(
	struct shader const *shader,
	short shader_permutation_index,
	struct triangle_buffer const *triangle_buffer,
	long dynamic_triangle_buffer_index,
	long triangle_count,
	struct vertex_buffer const *vertex_buffer,
	long dynamic_vertex_buffer_index)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 671, global_d3d_device);

	if (rasterizer_debug_options.draw_models)
	{
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 675, local_parameters);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 676, shader);

		if (local_parameters->effect.modifier_shader)
		{
			struct shader const *modifier_shader = local_parameters->effect.modifier_shader;
			short intensity_source;

			if (modifier_shader->base.type!=_shader_type_transparent_plasma ||
				(intensity_source = ((struct shader_transparent_plasma *)shader_get_and_verify_type(modifier_shader, _shader_type_transparent_plasma))->plasma.intensity_source)<1 ||
				intensity_source>4 ||
				!local_parameters->effect.modifier_animation.values ||
				local_parameters->effect.modifier_animation.values[intensity_source-1]!=0.f)
			{
				struct transparent_geometry_group *group = _rasterizer_model_transparent_geometry_submit(local_parameters->effect.modifier_shader, shader_permutation_index, triangle_buffer, dynamic_triangle_buffer_index, triangle_count, vertex_buffer, dynamic_vertex_buffer_index, &local_parameters->centroid, NULL);

				if (group)
				{
					group->animation = rasterizer_memory_alloc(&local_parameters->effect.modifier_animation, sizeof(struct render_animation));
				}
			}
		}

		if (local_model_effect_type==_render_model_effect_type_active_camouflage)
		{
			match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 729, shader->base.type==_shader_type_model);
			rasterizer_model_transparent_geometry_submit(shader, shader_permutation_index, triangle_buffer, dynamic_triangle_buffer_index, triangle_count, vertex_buffer, dynamic_vertex_buffer_index, &local_parameters->centroid, NULL);
			rasterizer_active_camouflage_set_visibility(TRUE);
		}
		else if (local_model_effect_type==_render_model_effect_type_none)
		{
			if (shader->base.type==_shader_type_environment)
			{
				rasterizer_model_draw_environment_shader(shader, shader_permutation_index, triangle_buffer, dynamic_triangle_buffer_index, triangle_count, vertex_buffer, dynamic_vertex_buffer_index);
			}
			else
			{
				struct shader_model const *shader_model = shader_get_and_verify_type(shader, _shader_type_model);
				boolean alpha_blended = TEST_FLAG(shader_model->model.flags, 3);
				real distance;
				real reflection_scale;
				short permutation;
				unsigned long seed;
				long vertex_shader_count;
				real random_phase;
				real_rgb_color self_illumination_color;
				real_rgb_color diffuse_change_color;
				float vsh_constants__texscale[12];
				float vsh_constants__effect[8];
				unsigned long cc0_pixel;
				unsigned long cc0_error_pixel;
				unsigned long cc1_pixel;

				match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 771, local_model_effect_type==_render_model_effect_type_none);

				{
					real_vector3d camera_to_centroid;

					vector_from_points3d(&global_window_parameters.camera.position, &local_parameters->centroid, &camera_to_centroid);
					distance = dot_product3d(&camera_to_centroid, &global_window_parameters.camera.forward);
				}

				if (shader_model->model.reflection_cutoff_distance==0.f)
				{
					reflection_scale = 1.f;
				}
				else
				{
					reflection_scale = PIN((distance-shader_model->model.reflection_cutoff_distance)/(shader_model->model.reflection_falloff_distance-shader_model->model.reflection_cutoff_distance), 0.f, 1.f);
				}

				if (TEST_FLAG(local_parameters->geometry_flags, 3))
				{
					IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZENABLE, D3DZB_FALSE);
					IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZBIAS, 0);
				}
				else
				{
					IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZENABLE, D3DZB_TRUE);
					IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZWRITEENABLE, !alpha_blended);
					IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
					IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZBIAS, alpha_blended ? rasterizer_debug_options.zbias : 0);
				}

				IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_CCW);
				IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_BLUE);
				IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHABLENDENABLE, alpha_blended);
				IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
				IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_BLENDOP, D3DBLENDOP_ADD);
				IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHATESTENABLE, !alpha_blended && !TEST_FLAG(shader_model->model.flags, 2));
				IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHAREF, 127);

				rasterizer_set_texture(0, 0, 1, shader_model->model.base_map.index, shader_permutation_index);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSU, D3DTADDRESS_WRAP);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);

				rasterizer_set_texture(1, 0, 2, shader_model->model.detail_map.index, shader_permutation_index);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_ADDRESSU, D3DTADDRESS_WRAP);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);

				rasterizer_set_texture(2, 0, 1, shader_model->model.multipurpose_map.index, shader_permutation_index);
				SetTextureStageStateSmart(2, D3DTSS_ADDRESSU, D3DTADDRESS_WRAP);
				SetTextureStageStateSmart(2, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP);
				SetTextureStageStateSmart(2, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
				SetTextureStageStateSmart(2, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
				SetTextureStageStateSmart(2, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);

				rasterizer_set_texture(3, 2, 0, shader_model->model.reflection_map.index, shader_permutation_index);
				SetTextureStageStateSmart(3, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
				SetTextureStageStateSmart(3, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
				SetTextureStageStateSmart(3, D3DTSS_ADDRESSW, D3DTADDRESS_CLAMP);
				SetTextureStageStateSmart(3, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
				SetTextureStageStateSmart(3, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
				SetTextureStageStateSmart(3, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);

				seed = local_parameters->unique_id;
				random_phase = TEST_FLAG(shader_model->model.self_illumination_flags, 0) ? 0.f : real_seed_random(&seed);

				match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 864, shader_model->model.self_illumination_animation_period!=0.0f);
				{
					real_vector3d self_illumination_delta;

					subtract_vectors3d((real_vector3d const *)&shader_model->model.self_illumination_animation_color_upper_bound, (real_vector3d const *)&shader_model->model.self_illumination_animation_color_lower_bound, &self_illumination_delta);
					point_from_line3d((real_point3d const *)&shader_model->model.self_illumination_animation_color_lower_bound, &self_illumination_delta,
						periodic_function_evaluate(shader_model->model.self_illumination_animation_function, global_frame_parameters.game_time_sec/shader_model->model.self_illumination_animation_period+random_phase),
						(real_point3d *)&self_illumination_color);
				}

				match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 876, self_illumination_color.red >=0.0f && self_illumination_color.red <=1.0f);
				match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 877, self_illumination_color.green>=0.0f && self_illumination_color.green<=1.0f);
				match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 878, self_illumination_color.blue >=0.0f && self_illumination_color.blue <=1.0f);

				if (shader_model->model.self_illumination_color_source>0 && shader_model->model.self_illumination_color_source<5)
				{
					real_rgb_color const *external_color = &local_parameters->animation.colors[shader_model->model.self_illumination_color_source-1];

					match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 887, external_color->red >=0.0f && external_color->red <=1.0f);
					match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 888, external_color->green>=0.0f && external_color->green<=1.0f);
					match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 889, external_color->blue >=0.0f && external_color->blue <=1.0f);
					self_illumination_color.red *= external_color->red;
					self_illumination_color.green *= external_color->green;
					self_illumination_color.blue *= external_color->blue;
				}

				if (shader_model->model.diffuse_change_color_source>0 && shader_model->model.diffuse_change_color_source<5)
				{
					diffuse_change_color = local_parameters->animation.colors[shader_model->model.diffuse_change_color_source-1];
					match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 904, diffuse_change_color.red >=0.0f && diffuse_change_color.red <=1.0f);
					match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 905, diffuse_change_color.green>=0.0f && diffuse_change_color.green<=1.0f);
					match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 906, diffuse_change_color.blue >=0.0f && diffuse_change_color.blue <=1.0f);
				}
				else
				{
					diffuse_change_color = *global_real_rgb_white;
				}

				vertex_shader_count = rasterizer_frame_statistics.vertex_shader_total;

				if (TEST_FLAG(shader_model->model.flags, 4))
				{
					permutation = 2;
				}
				else if (local_planar_fog_flag)
				{
					permutation = 0;
				}
				else if (local_parameters->lighting.point_light_count>0)
				{
					permutation = 1;
				}
				else if (local_parameters->skinning.node_matrix_count<=1 &&
					(shader_model->model.multipurpose_map.index==NONE ||
					(shader_model->model.detail_mask==0 &&
					self_illumination_color.red==0.f && self_illumination_color.green==0.f && self_illumination_color.blue==0.f &&
					diffuse_change_color.red==1.f && diffuse_change_color.green==1.f && diffuse_change_color.blue==1.f)) &&
					(shader_model->model.reflection_map.index==NONE || reflection_scale<=0.f))
				{
					permutation = 3;
				}
				else
				{
					permutation = 2;
				}

				rasterizer_set_vertex_shader_permutation(10, vertex_buffer ? vertex_buffer->type : rasterizer_dynamic_vertices_get_type(dynamic_vertex_buffer_index), permutation);

				if (rasterizer_debug_options.statistics_mode>=1)
				{
					rasterizer_frame_statistics.vertex_shader_count += rasterizer_frame_statistics.vertex_shader_total-vertex_shader_count;
					rasterizer_frame_statistics.permutation_counts[permutation] += vertex_buffer->count;
				}

				{
					real_argb_color perpendicular_color;
					real_argb_color parallel_color;

					perpendicular_color.alpha = reflection_scale*shader_model->model.reflection_view_perpendicular_color.alpha*local_parameters->lighting.reflection_tint_color.alpha;
					perpendicular_color.red = shader_model->model.reflection_view_perpendicular_color.red*local_parameters->lighting.reflection_tint_color.red;
					perpendicular_color.green = shader_model->model.reflection_view_perpendicular_color.green*local_parameters->lighting.reflection_tint_color.green;
					perpendicular_color.blue = shader_model->model.reflection_view_perpendicular_color.blue*local_parameters->lighting.reflection_tint_color.blue;
					parallel_color.alpha = reflection_scale*shader_model->model.reflection_view_parallel_color.alpha*local_parameters->lighting.reflection_tint_color.alpha;
					parallel_color.red = shader_model->model.reflection_view_parallel_color.red*local_parameters->lighting.reflection_tint_color.red;
					parallel_color.green = shader_model->model.reflection_view_parallel_color.green*local_parameters->lighting.reflection_tint_color.green;
					parallel_color.blue = shader_model->model.reflection_view_parallel_color.blue*local_parameters->lighting.reflection_tint_color.blue;

					vsh_constants__texscale[0] = shader_model->model.detail_map_scale;
					vsh_constants__texscale[1] = shader_model->model.detail_map_scale*shader_model->model.detail_map_v_scale;
					vsh_constants__texscale[2] = 1.f;
					vsh_constants__texscale[3] = 1.f;
					vsh_constants__texscale[4] = 1.f;
					vsh_constants__texscale[5] = 0.f;
					vsh_constants__texscale[6] = 0.f;
					vsh_constants__texscale[7] = 0.f;
					vsh_constants__texscale[8] = 0.f;
					vsh_constants__texscale[9] = 1.f;
					vsh_constants__texscale[10] = 0.f;
					vsh_constants__texscale[11] = 0.f;

					vsh_constants__effect[0] = perpendicular_color.red-parallel_color.red;
					vsh_constants__effect[1] = perpendicular_color.green-parallel_color.green;
					vsh_constants__effect[2] = perpendicular_color.blue-parallel_color.blue;
					vsh_constants__effect[3] = perpendicular_color.alpha-parallel_color.alpha;
					vsh_constants__effect[4] = parallel_color.red;
					vsh_constants__effect[5] = parallel_color.green;
					vsh_constants__effect[6] = parallel_color.blue;
					vsh_constants__effect[7] = parallel_color.alpha;
				}

				shader_texture_animation_evaluate(&shader_model->model.animation, &local_parameters->animation,
					local_parameters->base_map_scale.i*shader_model->model.map_scale.i, local_parameters->base_map_scale.j*shader_model->model.map_scale.j,
					0.f, 0.f, 0.f, global_frame_parameters.game_time_sec,
					(real_vector4d *)&vsh_constants__texscale[4], (real_vector4d *)&vsh_constants__texscale[8]);
				vsh_constants__texscale[10] = shader_model->model.translucency;

				IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, VSH_CONSTANTS__TEXSCALE_OFFSET, vsh_constants__texscale, VSH_CONSTANTS__TEXSCALE_COUNT);
				IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, VSH_CONSTANTS__EFFECT_OFFSET, vsh_constants__effect, VSH_CONSTANTS__EFFECT_COUNT);

				if (global_rasterizer_model_ambient_reflection_tint &&
					(global_rasterizer_model_ambient_reflection_tint->alpha>0.f ||
					global_rasterizer_model_ambient_reflection_tint->red>0.f ||
					global_rasterizer_model_ambient_reflection_tint->green>0.f ||
					global_rasterizer_model_ambient_reflection_tint->blue>0.f))
				{
					vsh_constants__effect[0] = 0.f;
					vsh_constants__effect[1] = 0.f;
					vsh_constants__effect[2] = 0.f;
					vsh_constants__effect[3] = 0.f;
					vsh_constants__effect[4] = global_rasterizer_model_ambient_reflection_tint->alpha;
					vsh_constants__effect[5] = global_rasterizer_model_ambient_reflection_tint->red;
					vsh_constants__effect[6] = global_rasterizer_model_ambient_reflection_tint->green;
					vsh_constants__effect[7] = global_rasterizer_model_ambient_reflection_tint->blue;
					IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, VSH_CONSTANTS__EFFECT_OFFSET, vsh_constants__effect, VSH_CONSTANTS__EFFECT_COUNT);
				}

				match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 1074, global_window_parameters.fog.atmospheric_maximum_distance>global_window_parameters.fog.atmospheric_minimum_distance);
				match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 1075, global_window_parameters.fog.atmospheric_maximum_distance>0.0f);
				match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 1076, global_window_parameters.fog.planar_maximum_distance>0.0f);
				match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 1077, global_window_parameters.fog.planar_maximum_depth>0.0f);

				if (rasterizer_debug_options.draw_environment_fog && !TEST_FLAG(local_parameters->geometry_flags, 2))
				{
					real planar_fog_density = plane3d_distance_to_point(&global_window_parameters.fog.plane, &global_window_parameters.camera.position)/global_window_parameters.fog.atmospheric_maximum_distance;
					real atmospheric_fog_density = PIN((distance-global_window_parameters.fog.atmospheric_minimum_distance)/(global_window_parameters.fog.atmospheric_maximum_distance-global_window_parameters.fog.atmospheric_minimum_distance), 0.f, 1.f)*global_window_parameters.fog.atmospheric_maximum_density;
					real_argb_color cc0;
					real_rgb_color cc0_error;
					real_rgb_color cc1;

					planar_fog_density = PIN(planar_fog_density, 0.f, 1.f);
					if (TEST_FLAG(global_window_parameters.fog.fog_definition_flags, 1))
					{
						planar_fog_density = 1.f;
					}

					cc0.alpha = 1.f-atmospheric_fog_density;
					cc0.red = global_window_parameters.fog.planar_color.red-(planar_fog_density*global_window_parameters.fog.planar_color.red+(1.f-planar_fog_density)*global_window_parameters.fog.atmospheric_color.red)*atmospheric_fog_density;
					cc0.green = global_window_parameters.fog.planar_color.green-(planar_fog_density*global_window_parameters.fog.planar_color.green+(1.f-planar_fog_density)*global_window_parameters.fog.atmospheric_color.green)*atmospheric_fog_density;
					cc0.blue = global_window_parameters.fog.planar_color.blue-(planar_fog_density*global_window_parameters.fog.planar_color.blue+(1.f-planar_fog_density)*global_window_parameters.fog.atmospheric_color.blue)*atmospheric_fog_density;

					cc0_error.red = PIN(-cc0.red, 0.f, 1.f);
					cc0_error.green = PIN(-cc0.green, 0.f, 1.f);
					cc0_error.blue = PIN(-cc0.blue, 0.f, 1.f);
					cc0.red = PIN(cc0.red, 0.f, 1.f);
					cc0.green = PIN(cc0.green, 0.f, 1.f);
					cc0.blue = PIN(cc0.blue, 0.f, 1.f);

					cc1.red = global_window_parameters.fog.atmospheric_color.red*atmospheric_fog_density;
					cc1.green = global_window_parameters.fog.atmospheric_color.green*atmospheric_fog_density;
					cc1.blue = global_window_parameters.fog.atmospheric_color.blue*atmospheric_fog_density;

					match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 1115, cc0.red >=0.0f && cc0.red <=1.0f);
					match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 1116, cc0.green>=0.0f && cc0.green<=1.0f);
					match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 1117, cc0.blue >=0.0f && cc0.blue <=1.0f);
					match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 1118, cc1.red >=0.0f && cc1.red <=1.0f);
					match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 1119, cc1.green>=0.0f && cc1.green<=1.0f);
					match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 1120, cc1.blue >=0.0f && cc1.blue <=1.0f);
					match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 1121, cc0_error.red >=0.0f && cc0_error.red <=1.0f);
					match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 1122, cc0_error.green>=0.0f && cc0_error.green<=1.0f);
					match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 1123, cc0_error.blue >=0.0f && cc0_error.blue <=1.0f);

					cc0_pixel = real_argb_color_to_pixel32(&cc0);
					cc0_error_pixel = real_rgb_color_to_pixel32(&cc0_error);
					cc1_pixel = real_rgb_color_to_pixel32(&cc1);
				}
				else
				{
					cc0_pixel = cc0_error_pixel = cc1_pixel = 0xff000000;
				}

				code_0015a350(real_rgb_color_to_pixel32(&self_illumination_color), shader_model->model.detail_function, shader_model->model.detail_mask, real_rgb_color_to_pixel32(&diffuse_change_color), cc0_pixel, cc0_error_pixel, cc1_pixel, TEST_FLAG(shader_model->model.flags, 0), TEST_FLAG(shader_model->model.flags, 4));

				IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_CCW);
				rasterizer_draw(triangle_buffer, dynamic_triangle_buffer_index, 0, triangle_count, vertex_buffer, dynamic_vertex_buffer_index);

				if (rasterizer_debug_options.statistics_mode==_rasterizer_statistics_mode_geometry)
				{
					rasterizer_frame_statistics.models_solid.primitives++;
					rasterizer_frame_statistics.models_solid.triangles += triangle_count;
					rasterizer_frame_statistics.models_solid.vertices += rasterizer_frame_statistics_count_static_vertices(triangle_buffer, vertex_buffer);
				}

				if (TEST_FLAG(shader_model->model.flags, 1))
				{
					vsh_constants__texscale[0] = shader_model->model.detail_map_scale;
					vsh_constants__texscale[1] = shader_model->model.detail_map_scale*shader_model->model.detail_map_v_scale;
					vsh_constants__texscale[2] = 1.f;
					vsh_constants__texscale[3] = -1.f;
					vsh_constants__texscale[4] = 1.f;
					vsh_constants__texscale[5] = 0.f;
					vsh_constants__texscale[6] = 0.f;
					vsh_constants__texscale[7] = 0.f;
					vsh_constants__texscale[8] = 0.f;
					vsh_constants__texscale[9] = 1.f;
					vsh_constants__texscale[10] = 0.f;
					vsh_constants__texscale[11] = 0.f;

					shader_texture_animation_evaluate(&shader_model->model.animation, &local_parameters->animation,
						local_parameters->base_map_scale.i*shader_model->model.map_scale.i, local_parameters->base_map_scale.j*shader_model->model.map_scale.j,
						0.f, 0.f, 0.f, global_frame_parameters.game_time_sec,
						(real_vector4d *)&vsh_constants__texscale[4], (real_vector4d *)&vsh_constants__texscale[8]);
					vsh_constants__texscale[10] = shader_model->model.translucency;

					IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, VSH_CONSTANTS__TEXSCALE_OFFSET, vsh_constants__texscale, VSH_CONSTANTS__TEXSCALE_COUNT);
					SetRenderStateSmart(D3DRS_CULLMODE, D3DCULL_CW);
					rasterizer_draw(triangle_buffer, dynamic_triangle_buffer_index, 0, triangle_count, vertex_buffer, dynamic_vertex_buffer_index);

					if (rasterizer_debug_options.statistics_mode==_rasterizer_statistics_mode_geometry)
					{
						rasterizer_frame_statistics.models_solid.primitives++;
						rasterizer_frame_statistics.models_solid.triangles += triangle_count;
						rasterizer_frame_statistics.models_solid.vertices += rasterizer_frame_statistics_count_static_vertices(triangle_buffer, vertex_buffer);
					}
				}
			}

			if (local_environment_fog_screen_flag)
			{
				rasterizer_environment_fog_screen_model_submit(shader, shader_permutation_index, triangle_buffer, dynamic_triangle_buffer_index, triangle_count, vertex_buffer, dynamic_vertex_buffer_index);
			}
		}
		else
		{
			error(_error_silent, "### ERROR model effect type #%d can't render opaque shader", local_model_effect_type);
		}
	}

	return;
}

// TODO: esi/edi swapped for the 0/NONE constants in the group setup; MSVC register choice here depends on the TU's symbol table (adding unrelated declarations flips it), not on the types
struct transparent_geometry_group *_rasterizer_model_transparent_geometry_submit(
	struct shader const *shader,
	short shader_permutation_index,
	struct triangle_buffer const *triangle_buffer,
	long dynamic_triangle_buffer_index,
	long triangle_count,
	struct vertex_buffer const *vertex_buffer,
	long dynamic_vertex_buffer_index,
	real_point3d const *centroid,
	struct render_sort_filth *sort_filth)
{
	static boolean warned = FALSE;
	struct transparent_geometry_group *result = NULL;

	if (rasterizer_debug_options.draw_models && rasterizer_debug_options.draw_model_transparent_geometry)
	{
		boolean hidden = shader && shader->base.type==_shader_type_model && TEST_FLAG(((struct shader_model *)shader_get_and_verify_type(shader, _shader_type_model))->model.flags, 3);
		boolean normal = local_model_effect_type!=_render_model_effect_type_active_camouflage ||
			(shader && shader->base.type==_shader_type_model && ((struct shader_model *)shader_get_and_verify_type(shader, _shader_type_model))->model.flags);

		if (!hidden)
		{
			struct transparent_geometry_group *group;
			unsigned long geometry_flags;

			match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 1301, shader);
			match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 1302, shader_type_is_valid_for_model(shader->base.type));
			match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 1303, centroid);
			match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 1304, local_parameters);

			geometry_flags = local_parameters->geometry_flags;

			if (normal)
			{
				if (shader_is_decal(shader))
				{
					geometry_flags |= 3;
				}
			}

			if (normal && TEST_FLAG(geometry_flags, _model_geometry_do_not_draw_bit))
			{
				group = &local_group;
				group->sorted_index = NONE;
			}
			else
			{
				if (local_model_effect_type==_render_model_effect_type_active_camouflage && shader->base.type!=_shader_type_model)
				{
					group = rasterizer_transparent_geometry_new_group2();
				}
				else
				{
					group = result = rasterizer_transparent_geometry_new_group();
				}

				if (sort_filth)
				{
					sort_filth->group_index = rasterizer_transparent_geometry_get_group_presorted_index(group);
					sort_filth->prev_group_presorted_index_reference = &group->prev_group_presorted_index;
					sort_filth->next_group_presorted_index_reference = &group->next_group_presorted_index;
				}
			}

			if (group)
			{
				real_plane3d zero_plane = { 0.f, 0.f, 0.f, 0.f };
				real_vector3d vector;

				group->geometry_flags = geometry_flags;
				group->object_index = local_parameters->unique_id;

				if (local_parameters->effect.type==_render_model_effect_type_none)
				{
					group->source_object_index = 0;
					group->centroid = *centroid;
				}
				else
				{
					match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 1356, local_parameters->effect.source_object_index!=0);
					group->source_object_index = local_parameters->effect.source_object_index;
					group->centroid = local_parameters->effect.source_object_centroid;
				}

				group->shader_permutation_index = shader_permutation_index;
				group->shader = shader;
				group->effect = local_parameters->effect;
				group->dynamic_triangle_buffer_index = dynamic_triangle_buffer_index;
				group->triangle_buffer = triangle_buffer;
				group->triangle_count = triangle_count;
				group->dynamic_vertex_buffer_index = dynamic_vertex_buffer_index;
				group->vertex_buffers = vertex_buffer;
				group->first_triangle_index = 0;
				group->lightmap = 0;
				vector_from_points3d(&global_window_parameters.camera.position, &group->centroid, &vector);
				group->z_sort = -dot_product3d(&vector, &global_window_parameters.camera.forward);
				group->plane = zero_plane;
				group->model_base_map_scale = local_parameters->base_map_scale;
				group->prev_group_presorted_index = NONE;
				group->next_group_presorted_index = NONE;

				if (local_model_effect_type==_render_model_effect_type_active_camouflage && shader->base.type!=_shader_type_model)
				{
					group->active_camouflage_transparent_source_object_index = local_parameters->effect.source_object_index;
					match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 1389, group->active_camouflage_transparent_source_object_index);
				}
				else
				{
					group->active_camouflage_transparent_source_object_index = 0;
				}

				group->cortana_hack = rasterizer_model_cortana_hack;

				if (TEST_FLAG(geometry_flags, _model_geometry_do_not_draw_bit))
				{
					group->node_matrices = local_parameters->skinning.node_matrices;
					group->node_matrix_count = local_parameters->skinning.node_matrix_count;
					group->lighting = &local_parameters->lighting;
					group->animation = &local_parameters->animation;
					rasterizer_transparent_geometry_groups_begin();
					rasterizer_transparent_geometry_group_draw(group, FALSE);
					rasterizer_transparent_geometry_groups_end();
					local_pixel_shader_dirty_flag = TRUE;
				}
				else
				{
					if (!local_parameters_queued_flag)
					{
						bss_00465d74 = rasterizer_memory_alloc_const(local_parameters->skinning.node_matrices, local_parameters->skinning.node_matrix_count*sizeof(real_matrix4x3));
						bss_00465d70 = local_parameters->skinning.node_matrix_count;
						bss_00465d6c = rasterizer_memory_alloc_const(&local_parameters->lighting, sizeof(struct render_lighting));
						bss_00465d68 = rasterizer_memory_alloc_const(&local_parameters->animation, sizeof(struct render_animation));
						local_parameters_queued_flag = TRUE;
					}

					group->node_matrices = bss_00465d74;
					group->node_matrix_count = bss_00465d70;
					group->lighting = bss_00465d6c;
					group->animation = bss_00465d68;
				}

				if (rasterizer_debug_options.statistics_mode==_rasterizer_statistics_mode_geometry)
				{
					rasterizer_frame_statistics.models_transparent.primitives++;
					rasterizer_frame_statistics.models_transparent.triangles += triangle_count;
					if (triangle_count>rasterizer_frame_statistics.models_transparent.triangles_maximum)
					{
						rasterizer_frame_statistics.models_transparent.triangles_maximum = triangle_count;
					}
					rasterizer_frame_statistics.models_transparent.vertices += rasterizer_frame_statistics_count_static_vertices(triangle_buffer, vertex_buffer);
				}
			}
			else if (!warned)
			{
				error(_error_silent, "### ERROR too many transparent geometry groups");
				warned = TRUE;
			}
		}
		else
		{
			if (sort_filth)
			{
				sort_filth->group_index = NONE;
				sort_filth->prev_group_presorted_index_reference = NULL;
				sort_filth->next_group_presorted_index_reference = NULL;
			}
		}
	}

	return result;
}

void _rasterizer_model_end(
	void)
{
	if (rasterizer_debug_options.draw_models)
	{
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_models.c", 1491, local_parameters);

		if (local_environment_fog_screen_flag)
		{
			rasterizer_environment_fog_screen_model_end();
		}

		if (TEST_FLAG(local_parameters->geometry_flags, _model_geometry_first_person_bit) && !local_do_not_change_z_stencil_states)
		{
			rasterizer_set_stencil_mode(_rasterizer_stencil_mode_reject);
			rasterizer_set_frustum_z(0.f, 0.f);
		}

		local_parameters = NULL;
	}

	return;
}

void _rasterizer_models_end(
	void)
{
	if (rasterizer_debug_options.draw_models)
	{
		if (local_sky_flag)
		{
			rasterizer_profile_end(_rasterizer_profile_model_sky);
		}
		else
		{
			rasterizer_profile_end(_rasterizer_profile_models);
		}
	}

	return;
}

void rasterizer_model_ambient_reflection_tint(
	real alpha,
	real red,
	real green,
	real blue)
{
	if (global_rasterizer_model_ambient_reflection_tint)
	{
		global_rasterizer_model_ambient_reflection_tint->alpha = alpha;
		global_rasterizer_model_ambient_reflection_tint->red = red;
		global_rasterizer_model_ambient_reflection_tint->green = green;
		global_rasterizer_model_ambient_reflection_tint->blue = blue;
	}

	return;
}
