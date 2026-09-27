/*
RASTERIZER_XBOX_ENVIRONMENT.C
*/

/* ---------- headers */

#include "cseries.h"
#include "cseries_windows.h"
#include "errors.h"
#include "real_math.h"
#include "periodic_functions.h"
#include "tag_groups.h"
#include "game_globals.h"
#include "rasterizer.h"
#include "rasterizer_geometry.h"
#include "render_cameras.h"
#include "xbox/rasterizer_xbox.h"
#include "shaders/shader_definitions.h"
#include "objects/light_definitions.h"

/* ---------- constants */

enum
{
	_shader_environment_reflection_dynamic_mirror_bit = 0,
};

enum
{
	_shader_environment_reflection_type_bumped_cube_map = 0,
	_shader_environment_reflection_type_flat_cube_map,
	_shader_environment_reflection_type_bumped_radiance,
	NUMBER_OF_SHADER_ENVIRONMENT_REFLECTION_TYPES
};

enum
{
	_shader_environment_alpha_tested_bit = 0,
	_shader_environment_bump_map_is_specular_mask_bit,
};

enum
{
	_shader_environment_self_illumination_unfiltered_bit = 0,
};

enum
{
	NUMBER_OF_DEBUG_TEXTURE_MODES = 51,
};

enum
{
	_shader_environment_type_normal = 0,
	_shader_environment_type_blended,
	_shader_environment_type_blended_base_specular,
};

enum
{
	_shader_environment_diffuse_rescale_detail_maps_bit = 0,
};

enum
{
	_shader_environment_specular_overbright_bit = 0,
	_shader_environment_specular_extra_shiny_bit,
	_shader_environment_specular_lightmap_is_specular_bit,
};

enum
{
	_detail_function_double_biased_multiply = 0,
	_detail_function_multiply,
	_detail_function_double_biased_add,
};


/* ---------- macros */

#define TWO_PI (2.f*_pi)

#define DRAWING_MODE_DRAWS_TEXTURES(mode) \
	((mode)==0 || (mode)==1 || (mode)==3 || (mode)==4 || (mode)==7 || (mode)==5 || (mode)==8)

#define DRAWING_MODE_DRAWS_LIGHTMAPS(mode) \
	((mode)==0 || (mode)==2 || (mode)==6 || (mode)==3 || (mode)==4 || (mode)==7 || (mode)==5 || (mode)==8)

/* ---------- structures */

struct rasterizer_debug_texture_mode
{
	short vertex_shader_permutation;
	long final_combiner_inputs;
};

/* ---------- prototypes */

void SetTextureStageStateSmart(unsigned long stage, D3DTEXTURESTAGESTATETYPE type, unsigned long value);

boolean shader_type_is_valid_for_environment(short shader_type);
boolean shader_is_decal(struct shader *shader);
void *rasterizer_set_target_as_texture(short stage, short target, short max_mipmap);
unsigned long real_a_rgb_color_to_pixel32(real alpha, real_rgb_color const *color);
void rasterizer_water_set_visibility_for_window(boolean visible);
struct transparent_geometry_group *rasterizer_transparent_geometry_new_group(void);
void rasterizer_transparent_geometry_group_draw(struct transparent_geometry_group const *group, boolean unknown);
void rasterizer_transparent_geometry_set_group_pending_status(struct transparent_geometry_group *group, boolean pending);

static void rasterizer_environment_specular_spot_light_begin(long light_index);
real real_rgb_color_brightness(real_rgb_color const *color);

void *shader_get_and_verify_type(struct shader const *shader, short type);
short shader_get_vertex_shader_permutation(struct shader const *shader);
void shader_environment_texture_animation_evaluate(struct shader const *shader, real time_value, real *u_offset, real *v_offset);

void rasterizer_set_vertex_shader_permutation(short vertex_shader, short vertex_type, short permutation);
void rasterizer_set_pixel_shader(D3DPIXELSHADERDEF *pixel_shader);
point2d const *rasterizer_set_texture(short stage, short type, short usage, long bitmap_group_index, short bitmap_index);
void rasterizer_draw_dynamic_triangles_static_vertices(long dynamic_triangle_buffer_index, long first_triangle_index, long triangle_count, struct vertex_buffer const *vertex_buffer);
void rasterizer_draw_dynamic_triangles_static_vertices2(long dynamic_triangle_buffer_index, long first_triangle_index, long triangle_count, struct vertex_buffer const *vertex_buffer0, struct vertex_buffer const *vertex_buffer1);
long rasterizer_frame_statistics_count_dynamic_vertices(long dynamic_triangle_buffer_index, long first_triangle_index, long triangle_count);
unsigned long real_rgb_color_to_pixel32(real_rgb_color const *color);
unsigned long real_alpha_to_pixel32(real alpha);

void rasterizer_set_stencil_mode(short mode);
void rasterizer_transparent_geometry_groups_begin(void);
void rasterizer_transparent_geometry_groups_end(void);
boolean rasterizer_set_texture_direct(short stage, long bitmap_group_index, short sequence_index);
boolean rasterizer_set_texture_bitmap_data(short stage, struct bitmap_data *bitmap);

/* ---------- globals */

extern struct game_globals_rasterizer_data *global_rasterizer_data;
extern struct rasterizer_frame_begin_parameters global_frame_parameters;
extern D3DPIXELSHADERDEF pixel_shader;
extern struct rasterizer_window_begin_parameters global_window_parameters;

static real_rgb_color local_lightmap_ambient_color;
static boolean local_lightmap_has_no_data;
static real specular_light_brightness;
static short specular_light_vertex_shader_permutation_index = NONE;

/* ---------- public code */

// comm. _code_0014fcc0, _code_0014fe70, _code_0014fec0, _code_001500e0, _code_001500f0 and
// _code_00150150 are unreferenced out-of-line copies of the xdk D3DDevice_*/IDirect3DDevice8_*
// inline functions (register calling convention); not reproduced here.

void _rasterizer_environment_lightmaps_begin(
	void)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 17, global_d3d_device);

	rasterizer_profile_begin(3);

	if (DRAWING_MODE_DRAWS_LIGHTMAPS(rasterizer_debug_options.drawing_mode) &&
		rasterizer_debug_options.draw_environment_lightmaps)
	{
		rasterizer_set_texture_direct(3, global_rasterizer_data->vector_normalization.index, 0);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_ADDRESSW, D3DTADDRESS_CLAMP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_CCW);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_ALL);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHABLENDENABLE, FALSE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHAREF, 127);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZENABLE, D3DZB_TRUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZWRITEENABLE, TRUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZBIAS, 0);
	}
}

void _rasterizer_environment_lightmap_begin(
	struct bitmap_data *lightmap)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 68, global_d3d_device);

	if (DRAWING_MODE_DRAWS_LIGHTMAPS(rasterizer_debug_options.drawing_mode) &&
		rasterizer_debug_options.draw_environment_lightmaps)
	{
		if (lightmap)
		{
			rasterizer_set_texture_bitmap_data(2, lightmap);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_MAGFILTER, rasterizer_debug_options.lightmap_filtering_enabled ? D3DTEXF_LINEAR : D3DTEXF_POINT);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_MINFILTER, rasterizer_debug_options.lightmap_filtering_enabled ? D3DTEXF_LINEAR : D3DTEXF_POINT);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_MIPFILTER, rasterizer_debug_options.lightmap_filtering_enabled ? D3DTEXF_LINEAR : D3DTEXF_POINT);
			local_lightmap_has_no_data = FALSE;
		}
		else
		{
			IDirect3DDevice8_SetTexture(global_d3d_device, 2, NULL);
			local_lightmap_has_no_data = TRUE;
		}

		if (rasterizer_globals.lightmap_mode > 0)
		{
			if (rasterizer_globals.lightmap_mode == 2)
			{
				local_lightmap_ambient_color.red =
				local_lightmap_ambient_color.green =
				local_lightmap_ambient_color.blue = rasterizer_debug_options.lightmap_ambient;
			}
			else
			{
				unsigned long seed = (unsigned long)lightmap;

				local_lightmap_ambient_color.red = real_seed_random(&seed);
				local_lightmap_ambient_color.green = real_seed_random(&seed);
				local_lightmap_ambient_color.blue = real_seed_random(&seed);
			}
		}
	}
}

// TODO: debug texture table initializer store order/register allocation and some stack slots differ (~88%)
void _rasterizer_environment_lightmap_draw(
	struct shader const *shader,
	short bitmap_index,
	long dynamic_triangle_buffer_index,
	long first_triangle_index,
	long triangle_count,
	struct vertex_buffer const *vertex_buffers)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 135, global_d3d_device);

	if (rasterizer_debug_options.drawing_mode==9)
	{
		if (vertex_buffers->type==_rasterizer_vertex_type_environment_compressed)
		{
			struct rasterizer_debug_texture_mode debug_texture_modes[NUMBER_OF_DEBUG_TEXTURE_MODES] =
			{
				{ 0, 8 },
				{ 0, 9 },
				{ 0, 10 },
				{ 0, 11 },
				{ 1, 8 },
				{ 1, 9 },
				{ 1, 10 },
				{ 1, 20 },
				{ 1, 11 },
				{ NONE, NONE },
				{ 0, 4 },
				{ 0, 5 },
				{ 1, 4 },
				{ 1, 5 },
				{ 2, 4 },
				{ 2, 5 },
				{ 3, 4 },
				{ NONE, NONE },
				{ NONE, NONE },
				{ NONE, NONE },
				{ 5, 5 },
				{ 2, 20 },
				{ 2, 21 },
				{ 2, 19 },
				{ NONE, NONE },
				{ NONE, NONE },
				{ NONE, NONE },
				{ NONE, NONE },
				{ NONE, NONE },
				{ NONE, NONE },
				{ 2, 8 },
				{ 2, 9 },
				{ 2, 10 },
				{ 2, 11 },
				{ NONE, NONE },
				{ NONE, NONE },
				{ NONE, NONE },
				{ NONE, NONE },
				{ NONE, NONE },
				{ NONE, NONE },
				{ 3, 5 },
				{ 4, 4 },
				{ 4, 5 },
				{ 5, 4 },
				{ NONE, NONE },
				{ NONE, NONE },
				{ NONE, NONE },
				{ NONE, NONE },
				{ NONE, NONE },
				{ NONE, NONE },
				{ 3, 12 },
			};
			short debug_texture_mode = rasterizer_debug_options.pad3%1000;
			short debug_bitmap_index = rasterizer_debug_options.pad3/1000;

			if (debug_texture_mode>=0 && debug_texture_mode<NUMBER_OF_DEBUG_TEXTURE_MODES &&
				debug_texture_modes[debug_texture_mode].vertex_shader_permutation!=NONE)
			{
				boolean test_texture = debug_texture_mode==NUMBER_OF_DEBUG_TEXTURE_MODES-1;

				if (test_texture && global_rasterizer_data->test[3].index!=NONE)
				{
					rasterizer_set_texture_direct(0, global_rasterizer_data->test[3].index, 0);
					IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSU, D3DTADDRESS_WRAP);
					IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP);
				}
				else
				{
					rasterizer_set_texture_direct(0, global_rasterizer_data->vector_normalization.index, debug_bitmap_index);
					IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
					IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
					IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSW, D3DTADDRESS_CLAMP);
				}
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);
				rasterizer_set_texture_direct(1, global_rasterizer_data->vector_normalization.index, debug_bitmap_index);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_ADDRESSW, D3DTADDRESS_CLAMP);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);
				rasterizer_set_texture_direct(2, global_rasterizer_data->vector_normalization.index, debug_bitmap_index);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_ADDRESSW, D3DTADDRESS_CLAMP);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);
				rasterizer_set_texture_direct(3, global_rasterizer_data->vector_normalization.index, debug_bitmap_index);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_ADDRESSW, D3DTADDRESS_CLAMP);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);
				IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_CCW);
				IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_BLUE);
				IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHABLENDENABLE, FALSE);
				IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHATESTENABLE, FALSE);
				IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZENABLE, D3DZB_TRUE);
				IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
				IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZWRITEENABLE, TRUE);
				IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZBIAS, 0);

				rasterizer_set_vertex_shader_permutation(37, vertex_buffers->type, debug_texture_modes[debug_texture_mode].vertex_shader_permutation);

				csmemset(&pixel_shader, 0, sizeof(pixel_shader));
				pixel_shader.PSTextureModes = (test_texture ? 0x1 : 0x3) | 0x18c60;

				if (test_texture)
				{
					real vsh_constants[VSH_CONSTANTS__TEXSCALE_COUNT][4];

					vsh_constants[0][0] = rasterizer_debug_options.pad3_scale;
					vsh_constants[0][1] = 1.f;
					vsh_constants[0][2] = 1.f;
					vsh_constants[0][3] = 1.f;
					vsh_constants[1][0] = 1.f;
					vsh_constants[1][1] = 0.f;
					vsh_constants[1][2] = 0.f;
					vsh_constants[1][3] = 0.f;
					vsh_constants[2][0] = 0.f;
					vsh_constants[2][1] = 1.f;
					vsh_constants[2][2] = 0.f;
					vsh_constants[2][3] = 0.f;
					IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, VSH_CONSTANTS__TEXSCALE_OFFSET, vsh_constants, VSH_CONSTANTS__TEXSCALE_COUNT);

					pixel_shader.PSCombinerCount = 3;
					pixel_shader.PSConstant0[0] = 0xff0000;
					pixel_shader.PSConstant1[0] = 0xff;
					pixel_shader.PSRGBInputs[0] = 0x4849484a;
					pixel_shader.PSRGBOutputs[0] = 0x30cd;
					pixel_shader.PSRGBInputs[1] = 0xc0c0d0d;
					pixel_shader.PSRGBOutputs[1] = 0xcd;
					pixel_shader.PSRGBInputs[2] = 0xc010d02;
					pixel_shader.PSRGBOutputs[2] = 0xc00;
					pixel_shader.PSFinalCombinerInputsABCD = debug_texture_modes[debug_texture_mode].final_combiner_inputs | 0x18200000;
				}
				else
				{
					pixel_shader.PSCombinerCount = 1;
					pixel_shader.PSFinalCombinerInputsABCD = debug_texture_modes[debug_texture_mode].final_combiner_inputs;
				}

				rasterizer_set_pixel_shader(&pixel_shader);
				rasterizer_draw_dynamic_triangles_static_vertices2(dynamic_triangle_buffer_index, first_triangle_index, triangle_count, &vertex_buffers[0], &vertex_buffers[!local_lightmap_has_no_data]);
			}
		}
	}
	else if (DRAWING_MODE_DRAWS_LIGHTMAPS(rasterizer_debug_options.drawing_mode) &&
		rasterizer_debug_options.draw_environment_lightmaps)
	{
		struct shader_environment *shader_environment;

		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 347, shader);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 348, vertex_buffers);

		shader_environment = shader_get_and_verify_type(shader, _shader_type_environment);
		rasterizer_set_vertex_shader_permutation(16, vertex_buffers->type, shader_get_vertex_shader_permutation(shader));

		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHATESTENABLE, TEST_FLAG(shader_environment->environment.flags, _shader_environment_alpha_tested_bit) && rasterizer_debug_options.environment_alpha_testing_enabled);

		rasterizer_set_texture(0, 0, 3, TEST_FLAG(shader_environment->environment.flags, _shader_environment_bump_map_is_specular_mask_bit) ? NONE : shader_environment->environment.diffuse.bump_map.index, bitmap_index);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSU, D3DTADDRESS_WRAP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);
		rasterizer_set_texture(1, 0, 0, shader_environment->environment.self_illumination.map.index, bitmap_index);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_ADDRESSU, D3DTADDRESS_WRAP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);

		if (TEST_FLAG(shader_environment->environment.self_illumination.flags, _shader_environment_self_illumination_unfiltered_bit))
		{
			SetTextureStageStateSmart(1, D3DTSS_MAGFILTER, D3DTEXF_POINT);
			SetTextureStageStateSmart(1, D3DTSS_MINFILTER, D3DTEXF_POINT);
			SetTextureStageStateSmart(1, D3DTSS_MIPFILTER, D3DTEXF_POINT);
		}
		else
		{
			SetTextureStageStateSmart(1, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
			SetTextureStageStateSmart(1, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
			SetTextureStageStateSmart(1, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);
		}

		{
			real vsh_constants[VSH_CONSTANTS__TEXSCALE_COUNT][4];

			vsh_constants[0][0] = shader_environment->environment.diffuse.runtime_bump_map_scale.i;
			vsh_constants[0][1] = shader_environment->environment.diffuse.runtime_bump_map_scale.j;
			vsh_constants[0][2] = shader_environment->environment.self_illumination.map_scale;
			vsh_constants[0][3] = 1.f;
			vsh_constants[1][0] = 1.f;
			vsh_constants[1][1] = 0.f;
			vsh_constants[1][2] = 0.f;
			vsh_constants[1][3] = 0.f;
			vsh_constants[2][0] = 0.f;
			vsh_constants[2][1] = 1.f;
			vsh_constants[2][2] = 0.f;
			vsh_constants[2][3] = 0.f;
			shader_environment_texture_animation_evaluate(shader, global_frame_parameters.game_time_sec, &vsh_constants[1][3], &vsh_constants[2][3]);
			IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, VSH_CONSTANTS__TEXSCALE_OFFSET, vsh_constants, VSH_CONSTANTS__TEXSCALE_COUNT);
		}

		if (shader_environment->environment.self_illumination.map.index==NONE)
		{
			csmemset(&pixel_shader, 0, sizeof(pixel_shader));
			pixel_shader.PSCombinerCount = 2;
			pixel_shader.PSRGBOutputs[0] = 0x208c;
			pixel_shader.PSAlphaInputs[1] = 0x34201408;
			pixel_shader.PSAlphaOutputs[1] = 0xc00;
			pixel_shader.PSFinalCombinerInputsABCD = 0xa0f000c;
			pixel_shader.PSFinalCombinerInputsEFG = 0x1c011800;
			pixel_shader.PSTextureModes = (!local_lightmap_has_no_data << 10) | 0x18001;
			pixel_shader.PSRGBInputs[0] = rasterizer_debug_options.lightmap_incident_radiosity_enabled ? 0x484b0a01 : 0x20200000;
		}
		else
		{
			struct shader_environment_self_illumination_properties const *illumination = &shader_environment->environment.self_illumination;
			real primary_animation;
			real secondary_animation;
			real plasma_animation;
			real_rgb_color primary_color;
			real_rgb_color secondary_color;
			real_rgb_color plasma_on_color;
			real_rgb_color plasma_off_color;

			match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 448, illumination->primary_animation_period!=0.0f);
			match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 449, illumination->secondary_animation_period!=0.0f);
			match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 450, illumination->plasma_animation_period!=0.0f);

			primary_animation = periodic_function_evaluate(illumination->primary_animation_function, (global_frame_parameters.game_time_sec+illumination->primary_animation_phase)/illumination->primary_animation_period);
			secondary_animation = periodic_function_evaluate(illumination->secondary_animation_function, (global_frame_parameters.game_time_sec+illumination->secondary_animation_phase)/illumination->secondary_animation_period);
			plasma_animation = periodic_function_evaluate(illumination->plasma_animation_function, (global_frame_parameters.game_time_sec+illumination->plasma_animation_phase)/illumination->plasma_animation_period);

			scale_vector3d((real_vector3d const *)&illumination->primary_off_color, 1.f-primary_animation, (real_vector3d *)&primary_color);
			scale_vector3d((real_vector3d const *)&illumination->secondary_off_color, 1.f-secondary_animation, (real_vector3d *)&secondary_color);
			point_from_line3d((real_point3d const *)&primary_color, (real_vector3d const *)&illumination->primary_on_color, primary_animation, (real_point3d *)&primary_color);
			point_from_line3d((real_point3d const *)&secondary_color, (real_vector3d const *)&illumination->secondary_on_color, secondary_animation, (real_point3d *)&secondary_color);
			scale_vector3d((real_vector3d const *)&illumination->plasma_on_color, 1.f, (real_vector3d *)&plasma_on_color);
			scale_vector3d((real_vector3d const *)&illumination->plasma_off_color, 1.f, (real_vector3d *)&plasma_off_color);

			csmemset(&pixel_shader, 0, sizeof(pixel_shader));
			pixel_shader.PSAlphaOutputs[0] = 0xc00;
			pixel_shader.PSRGBOutputs[0] = 0xc00;
			pixel_shader.PSAlphaOutputs[4] = 0xc00;
			pixel_shader.PSRGBOutputs[4] = 0xc00;
			pixel_shader.PSRGBOutputs[5] = 0xc00;
			pixel_shader.PSTextureModes = (!local_lightmap_has_no_data << 10) | 0x18021;
			pixel_shader.PSCombinerCount = 0x11106;
			pixel_shader.PSAlphaInputs[0] = 0x1120b920;
			pixel_shader.PSRGBInputs[0] = 0x1920b120;
			pixel_shader.PSAlphaInputs[1] = 0xdcdccccc;
			pixel_shader.PSAlphaOutputs[1] = 0x24c00;
			pixel_shader.PSRGBInputs[1] = rasterizer_debug_options.lightmap_incident_radiosity_enabled ? 0x484b0a01 : 0x20200000;
			pixel_shader.PSRGBOutputs[1] = 0x2080;
			pixel_shader.PSConstant0[2] = 0xff0000;
			pixel_shader.PSConstant1[2] = 0xff00;
			pixel_shader.PSAlphaInputs[2] = 0x1c1c0920;
			pixel_shader.PSAlphaOutputs[2] = 0xc9;
			pixel_shader.PSRGBInputs[2] = 0x9010902;
			pixel_shader.PSRGBOutputs[2] = 0x30cd;
			pixel_shader.PSAlphaInputs[3] = 0x5c5c;
			pixel_shader.PSAlphaOutputs[3] = 0x4c00;
			pixel_shader.PSRGBInputs[3] = 0xc010d02;
			pixel_shader.PSRGBOutputs[3] = 0xd00;
			pixel_shader.PSAlphaInputs[4] = 0x34201408;
			pixel_shader.PSRGBInputs[4] = 0x11c0220;
			pixel_shader.PSRGBInputs[5] = 0xc190d20;
			pixel_shader.PSFinalCombinerInputsABCD = 0xa0f000c;
			pixel_shader.PSFinalCombinerInputsEFG = 0x1c011800;
			pixel_shader.PSConstant0[0] = real_alpha_to_pixel32(plasma_animation);
			pixel_shader.PSConstant0[3] = real_rgb_color_to_pixel32(&primary_color);
			pixel_shader.PSConstant1[3] = real_rgb_color_to_pixel32(&secondary_color);
			pixel_shader.PSConstant0[4] = real_rgb_color_to_pixel32(&plasma_on_color);
			pixel_shader.PSConstant1[4] = real_rgb_color_to_pixel32(&plasma_off_color);
		}

		pixel_shader.PSFinalCombinerConstant0 = real_rgb_color_to_pixel32(&shader_environment->environment.diffuse.material_color);

		if (rasterizer_globals.lightmap_mode==1)
		{
			real debug_constants[4][4];

			debug_constants[0][0] = 0.5f;
			debug_constants[0][1] = 0.6f;
			debug_constants[0][2] = 0.6f;
			debug_constants[0][3] = 1.f;
			debug_constants[1][0] = 0.f;
			debug_constants[1][1] = 0.f;
			debug_constants[1][2] = 1.f;
			debug_constants[1][3] = 0.1f;
			debug_constants[2][0] = 0.9f;
			debug_constants[2][1] = 0.9f;
			debug_constants[2][2] = 0.8f;
			debug_constants[2][3] = 0.f;
			debug_constants[3][0] = 0.1f;
			debug_constants[3][1] = 0.1f;
			debug_constants[3][2] = 0.3f;
			debug_constants[3][3] = 0.f;
			IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, VSH_CONSTANTS__POINTLIGHT_OFFSET, debug_constants, 4);
			pixel_shader.PSFinalCombinerInputsABCD = 0x2004000c;
		}
		else if (rasterizer_globals.lightmap_mode==2 || rasterizer_globals.lightmap_mode==3)
		{
			pixel_shader.PSFinalCombinerConstant1 = real_rgb_color_to_pixel32(&local_lightmap_ambient_color);
			pixel_shader.PSFinalCombinerInputsABCD = 0x2002000c;
		}

		switch (rasterizer_debug_options.drawing_mode)
		{
		case 0:
			break;
		case 2:
		case 4:
		case 5:
			pixel_shader.PSCombinerCount = 1;
			pixel_shader.PSAlphaInputs[0] = 0;
			pixel_shader.PSAlphaOutputs[0] = 0;
			pixel_shader.PSRGBInputs[0] = 0;
			pixel_shader.PSRGBOutputs[0] = 0;
			pixel_shader.PSFinalCombinerInputsABCD = 0x8;
			break;
		case 3:
			pixel_shader.PSCombinerCount = 1;
			pixel_shader.PSAlphaInputs[0] = 0;
			pixel_shader.PSAlphaOutputs[0] = 0;
			pixel_shader.PSRGBInputs[0] = 0;
			pixel_shader.PSRGBOutputs[0] = 0;
			pixel_shader.PSFinalCombinerInputsABCD = 0x20;
			break;
		case 6:
		case 7:
		case 8:
			pixel_shader.PSCombinerCount = 1;
			pixel_shader.PSAlphaInputs[0] = 0x48402020;
			pixel_shader.PSAlphaOutputs[0] = 0x20d00;
			pixel_shader.PSRGBInputs[0] = 0;
			pixel_shader.PSRGBOutputs[0] = 0;
			pixel_shader.PSFinalCombinerInputsABCD = 0x1d;
			break;
		default:
			match_vassert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 575, FALSE, "### ERROR unsupported drawing mode in environment lightmap pass");
		}

		rasterizer_set_pixel_shader(&pixel_shader);
		rasterizer_draw_dynamic_triangles_static_vertices2(dynamic_triangle_buffer_index, first_triangle_index, triangle_count, &vertex_buffers[0], &vertex_buffers[!local_lightmap_has_no_data]);

		if (rasterizer_debug_options.statistics_mode==2)
		{
			rasterizer_frame_statistics.lightmaps.primitives++;
			rasterizer_frame_statistics.lightmaps.triangles += triangle_count;
			rasterizer_frame_statistics.lightmaps.vertices += rasterizer_frame_statistics_count_dynamic_vertices(dynamic_triangle_buffer_index, first_triangle_index, triangle_count);
		}
	}
}

void _rasterizer_environment_lightmap_end(
	void)
{
}

void _rasterizer_environment_lightmaps_end(
	void)
{
	rasterizer_profile_end(3);
}

void _rasterizer_environment_diffuse_lights_begin(
	void)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 627, global_d3d_device);

	rasterizer_profile_begin(5);

	if (rasterizer_debug_options.drawing_mode==0 &&
		rasterizer_debug_options.draw_environment_diffuse_lights)
	{
		rasterizer_set_texture_direct(2, global_rasterizer_data->distance_attenuation.index, 0);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_ADDRESSU, D3DTADDRESS_BORDER);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_ADDRESSV, D3DTADDRESS_BORDER);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_ADDRESSW, D3DTADDRESS_BORDER);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_MINFILTER, D3DTEXF_POINT);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_MIPFILTER, D3DTEXF_POINT);
		rasterizer_set_texture_direct(3, global_rasterizer_data->vector_normalization.index, 0);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_ADDRESSW, D3DTADDRESS_CLAMP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_MINFILTER, D3DTEXF_POINT);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_MIPFILTER, D3DTEXF_POINT);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_CCW);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_BLUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHABLENDENABLE, TRUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_SRCBLEND, D3DBLEND_ONE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_DESTBLEND, D3DBLEND_ONE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_BLENDOP, D3DBLENDOP_ADD);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHATESTENABLE, TRUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHAREF, 0);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZENABLE, D3DZB_TRUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZFUNC, D3DCMP_EQUAL);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZWRITEENABLE, FALSE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZBIAS, 0);

		csmemset(&pixel_shader, 0, sizeof(pixel_shader));
		pixel_shader.PSTextureModes = 0x18861;
		pixel_shader.PSCombinerCount = 4;
		pixel_shader.PSAlphaInputs[0] = 0x4b204b20;
		pixel_shader.PSAlphaOutputs[0] = 0x20c00;
		pixel_shader.PSRGBInputs[0] = 0x90a484b;
		pixel_shader.PSRGBOutputs[0] = 0x10cd;
		pixel_shader.PSRGBInputs[1] = 0xc0d0000;
		pixel_shader.PSRGBOutputs[1] = 0xc0;
		pixel_shader.PSRGBInputs[2] = 0xc1c0000;
		pixel_shader.PSRGBOutputs[2] = 0xc0;
		pixel_shader.PSRGBInputs[3] = 0xc010c01;
		pixel_shader.PSRGBOutputs[3] = 0x10cd;
		pixel_shader.PSFinalCombinerInputsABCD = 0xc010000;
		pixel_shader.PSFinalCombinerInputsEFG = 0xd00;
		rasterizer_set_pixel_shader(&pixel_shader);
	}
}

void _rasterizer_environment_diffuse_light_begin(
	long light_index)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 723, global_d3d_device);

	if (rasterizer_debug_options.drawing_mode==0 &&
		rasterizer_debug_options.draw_environment_diffuse_lights)
	{
		struct rasterizer_light_submit_parameters *light;
		real_matrix3x3 basis;
		real yaw, pitch, roll;

		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 729, light_index>=0 && light_index<rasterizer_lights.light_count);
		light = &rasterizer_lights.lights[light_index];
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 732, light->radius>0.0f);

		rasterizer_set_texture(1, 2, 1, light->definition->gel.map.index, 0);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_ADDRESSW, D3DTADDRESS_CLAMP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);

		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 748, light->definition->gel.yaw_period>0.0f);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 749, light->definition->gel.pitch_period>0.0f);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 750, light->definition->gel.roll_period>0.0f);

		yaw = periodic_function_evaluate(light->definition->gel.yaw_function, global_frame_parameters.game_time_sec/light->definition->gel.yaw_period)*TWO_PI;
		pitch = periodic_function_evaluate(light->definition->gel.pitch_function, global_frame_parameters.game_time_sec/light->definition->gel.pitch_period)*TWO_PI;
		roll = periodic_function_evaluate(light->definition->gel.roll_function, global_frame_parameters.game_time_sec/light->definition->gel.roll_period)*TWO_PI;

		{
			real_matrix4x3 matrix;

			matrix4x3_rotation_from_angles(&matrix, yaw, pitch, roll);
			matrix4x3_transform_normal(&matrix, &light->forward, &basis.forward);
			matrix4x3_transform_normal(&matrix, &light->up, &basis.up);
			cross_product3d(&basis.forward, &basis.up, &basis.left);
			normalize3d(&basis.left);
		}

		{
			real vsh_constants[VSH_CONSTANTS__POINTLIGHT_COUNT][4];

			vsh_constants[0][0] = light->position.x;
			vsh_constants[0][1] = light->position.y;
			vsh_constants[0][2] = light->position.z;
			vsh_constants[0][3] = 0.5f/light->radius;
			vsh_constants[1][0] = -basis.forward.i;
			vsh_constants[1][1] = -basis.forward.j;
			vsh_constants[1][2] = -basis.forward.k;
			vsh_constants[1][3] = 1.f;
			vsh_constants[2][0] = -basis.left.i;
			vsh_constants[2][1] = -basis.left.j;
			vsh_constants[2][2] = -basis.left.k;
			vsh_constants[2][3] = 1.f;
			vsh_constants[3][0] = -basis.up.i;
			vsh_constants[3][1] = -basis.up.j;
			vsh_constants[3][2] = -basis.up.k;
			vsh_constants[3][3] = 1.f;
			vsh_constants[4][0] = 0.f;
			vsh_constants[4][1] = 0.f;
			vsh_constants[4][2] = 0.f;
			vsh_constants[4][3] = 1.f;
			IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, VSH_CONSTANTS__POINTLIGHT_OFFSET, vsh_constants, VSH_CONSTANTS__POINTLIGHT_COUNT);
		}

		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_PSCONSTANT0_0, real_rgb_color_to_pixel32(&light->color));
	}
}

// TODO: one store to vsh_constants[0][0] is scheduled one instruction early (~99%)
void _rasterizer_environment_diffuse_light_draw(
	struct shader const *shader,
	short bitmap_index,
	long dynamic_triangle_buffer_index,
	long first_triangle_index,
	long triangle_count,
	struct vertex_buffer const *vertex_buffer)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 819, global_d3d_device);

	if (rasterizer_debug_options.drawing_mode==0 &&
		rasterizer_debug_options.draw_environment_diffuse_lights)
	{
		real vsh_constants[VSH_CONSTANTS__TEXSCALE_COUNT][4];
		struct shader_environment *shader_environment;

		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 826, shader);
		shader_environment = shader_get_and_verify_type(shader, _shader_type_environment);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 831, vertex_buffer);

		rasterizer_set_vertex_shader_permutation(49, vertex_buffer->type, shader_get_vertex_shader_permutation(shader));
		rasterizer_set_texture(0, 0, 3, TEST_FLAG(shader_environment->environment.flags, _shader_environment_bump_map_is_specular_mask_bit) ? NONE : shader_environment->environment.diffuse.bump_map.index, bitmap_index);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSU, D3DTADDRESS_WRAP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);

		vsh_constants[0][0] = shader_environment->environment.diffuse.runtime_bump_map_scale.i;
		vsh_constants[0][1] = shader_environment->environment.diffuse.runtime_bump_map_scale.j;
		vsh_constants[0][2] = 1.f;
		vsh_constants[0][3] = 1.f;
		vsh_constants[1][0] = 1.f;
		vsh_constants[1][1] = 0.f;
		vsh_constants[1][2] = 0.f;
		vsh_constants[1][3] = 0.f;
		vsh_constants[2][0] = 0.f;
		vsh_constants[2][1] = 1.f;
		vsh_constants[2][2] = 0.f;
		vsh_constants[2][3] = 0.f;
		shader_environment_texture_animation_evaluate(shader, global_frame_parameters.game_time_sec, &vsh_constants[1][3], &vsh_constants[2][3]);
		IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, VSH_CONSTANTS__TEXSCALE_OFFSET, vsh_constants, VSH_CONSTANTS__TEXSCALE_COUNT);

		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_PSFINALCOMBINERCONSTANT0, real_rgb_color_to_pixel32(&shader_environment->environment.diffuse.material_color));

		rasterizer_draw_dynamic_triangles_static_vertices(dynamic_triangle_buffer_index, first_triangle_index, triangle_count, vertex_buffer);

		if (rasterizer_debug_options.statistics_mode==2)
		{
			rasterizer_frame_statistics.lights.primitives++;
			rasterizer_frame_statistics.lights.triangles += triangle_count;
			rasterizer_frame_statistics.lights.vertices += rasterizer_frame_statistics_count_dynamic_vertices(dynamic_triangle_buffer_index, first_triangle_index, triangle_count);
		}
	}
}

void _rasterizer_environment_diffuse_light_end(
	void)
{
}

void _rasterizer_environment_diffuse_lights_end(
	void)
{
	rasterizer_profile_end(5);
}

void _rasterizer_environment_diffuse_textures_begin(
	void)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 921, global_d3d_device);

	rasterizer_profile_begin(8);

	if (DRAWING_MODE_DRAWS_TEXTURES(rasterizer_debug_options.drawing_mode) &&
		rasterizer_debug_options.draw_environment_textures)
	{
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_CCW);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_COLORWRITEENABLE, rasterizer_debug_options.environment_specular_mask_enabled ? D3DCOLORWRITEENABLE_ALL : D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_BLUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHABLENDENABLE, TRUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_SRCBLEND, rasterizer_debug_options.drawing_mode==1 ? D3DBLEND_ONE : D3DBLEND_DESTCOLOR);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_DESTBLEND, rasterizer_debug_options.drawing_mode==1 ? D3DBLEND_ONE : D3DBLEND_ZERO);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_BLENDOP, D3DBLENDOP_ADD);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHATESTENABLE, FALSE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZENABLE, rasterizer_debug_options.drawing_mode==1 ? D3DZB_FALSE : D3DZB_TRUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZFUNC, D3DCMP_EQUAL);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZWRITEENABLE, FALSE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZBIAS, 0);
		rasterizer_set_stencil_mode(5);
	}
}

// TODO: vsh_constants stores scheduled slightly differently (~95%)
void _rasterizer_environment_diffuse_texture_draw(
	struct shader const *shader,
	short bitmap_index,
	long dynamic_triangle_buffer_index,
	long first_triangle_index,
	long triangle_count,
	struct vertex_buffer const *vertex_buffer)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 968, global_d3d_device);

	if (DRAWING_MODE_DRAWS_TEXTURES(rasterizer_debug_options.drawing_mode) &&
		rasterizer_debug_options.draw_environment_textures)
	{
		struct shader_environment *shader_environment;
		point2d base_map_size;
		point2d primary_detail_map_size;
		point2d secondary_detail_map_size;
		point2d micro_detail_map_size;
		real_vector2d primary_detail_map_scale;
		real_vector2d secondary_detail_map_scale;
		real_vector2d micro_detail_map_scale;
		real vsh_constants[VSH_CONSTANTS__TEXSCALE_COUNT][4];

		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 981, shader);
		shader_environment = shader_get_and_verify_type(shader, _shader_type_environment);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 995, vertex_buffer);

		rasterizer_set_vertex_shader_permutation(40, vertex_buffer->type, shader_get_vertex_shader_permutation(shader));

		base_map_size = *rasterizer_set_texture(0, 0, 1, shader_environment->environment.diffuse.base_map.index, bitmap_index);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSU, D3DTADDRESS_WRAP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);
		primary_detail_map_size = *rasterizer_set_texture(1, 0, 2, shader_environment->environment.diffuse.primary_detail_map.index, bitmap_index);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_ADDRESSU, D3DTADDRESS_WRAP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);
		secondary_detail_map_size = *rasterizer_set_texture(2, 0, 2, shader_environment->environment.diffuse.secondary_detail_map.index, bitmap_index);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_ADDRESSU, D3DTADDRESS_WRAP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);
		micro_detail_map_size = *rasterizer_set_texture(3, 0, 2, shader_environment->environment.diffuse.micro_detail_map.index, bitmap_index);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_ADDRESSU, D3DTADDRESS_WRAP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);

		if (TEST_FLAG(shader_environment->environment.diffuse.flags, _shader_environment_diffuse_rescale_detail_maps_bit))
		{
			primary_detail_map_scale.i = (real)base_map_size.x/(real)primary_detail_map_size.x;
			primary_detail_map_scale.j = (real)base_map_size.y/(real)primary_detail_map_size.y;
			secondary_detail_map_scale.i = (real)base_map_size.x/(real)secondary_detail_map_size.x;
			secondary_detail_map_scale.j = (real)base_map_size.y/(real)secondary_detail_map_size.y;
			micro_detail_map_scale.i = (real)base_map_size.x/(real)micro_detail_map_size.x;
			micro_detail_map_scale.j = (real)base_map_size.y/(real)micro_detail_map_size.y;
		}
		else
		{
			primary_detail_map_scale.i = primary_detail_map_scale.j = secondary_detail_map_scale.i = secondary_detail_map_scale.j = micro_detail_map_scale.i = micro_detail_map_scale.j = 1.f;
		}

		vsh_constants[0][0] = primary_detail_map_scale.i*shader_environment->environment.diffuse.primary_detail_map_scale;
		vsh_constants[0][1] = primary_detail_map_scale.j*shader_environment->environment.diffuse.primary_detail_map_scale;
		vsh_constants[1][0] = 1.f;
		vsh_constants[1][1] = 0.f;
		vsh_constants[1][3] = 0.f;
		vsh_constants[2][0] = 0.f;
		vsh_constants[2][1] = 1.f;
		vsh_constants[2][3] = 0.f;
		vsh_constants[0][2] = secondary_detail_map_scale.i*shader_environment->environment.diffuse.secondary_detail_map_scale;
		vsh_constants[0][3] = secondary_detail_map_scale.j*shader_environment->environment.diffuse.secondary_detail_map_scale;
		vsh_constants[1][2] = micro_detail_map_scale.i*shader_environment->environment.diffuse.micro_detail_map_scale;
		vsh_constants[2][2] = micro_detail_map_scale.j*shader_environment->environment.diffuse.micro_detail_map_scale;
		shader_environment_texture_animation_evaluate(shader, global_frame_parameters.game_time_sec, &vsh_constants[1][3], &vsh_constants[2][3]);
		IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, VSH_CONSTANTS__TEXSCALE_OFFSET, vsh_constants, VSH_CONSTANTS__TEXSCALE_COUNT);

		csmemset(&pixel_shader, 0, sizeof(pixel_shader));
		pixel_shader.PSTextureModes = 0x8421;
		pixel_shader.PSCombinerCount = 3;

		switch (shader_environment->environment.type)
		{
		case _shader_environment_type_normal:
			pixel_shader.PSAlphaInputs[0] = 0x3a1a1a19;
			pixel_shader.PSRGBInputs[0] = 0x3a0a1a09;
			pixel_shader.PSAlphaInputs[1] = 0x181c0000;
			pixel_shader.PSAlphaOutputs[1] = 0xc0;
			pixel_shader.PSAlphaOutputs[0] = 0xc00;
			pixel_shader.PSRGBOutputs[0] = 0xc00;
			break;
		case _shader_environment_type_blended:
			pixel_shader.PSAlphaInputs[0] = 0x381a1819;
			pixel_shader.PSRGBInputs[0] = 0x380a1809;
			pixel_shader.PSAlphaOutputs[1] = 0;
			pixel_shader.PSAlphaOutputs[0] = 0xc00;
			pixel_shader.PSRGBOutputs[0] = 0xc00;
			break;
		case _shader_environment_type_blended_base_specular:
			pixel_shader.PSAlphaInputs[0] = 0x18200000;
			pixel_shader.PSAlphaOutputs[0] = 0xc0;
			pixel_shader.PSRGBInputs[0] = 0x380a1809;
			pixel_shader.PSAlphaOutputs[1] = 0;
			pixel_shader.PSRGBOutputs[0] = 0xc00;
			break;
		default:
			match_vassert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 1145, FALSE, "### ERROR unsupported environment shader type");
		}

		switch (shader_environment->environment.diffuse.detail_map_function)
		{
		case _detail_function_double_biased_multiply:
			pixel_shader.PSRGBInputs[1] = 0x80c080c;
			pixel_shader.PSRGBOutputs[1] = 0xc00;
			break;
		case _detail_function_multiply:
			pixel_shader.PSRGBInputs[1] = 0x80c0000;
			pixel_shader.PSRGBOutputs[1] = 0xc00;
			break;
		case _detail_function_double_biased_add:
			pixel_shader.PSRGBInputs[1] = 0x8204c20;
			pixel_shader.PSRGBOutputs[1] = 0xc00;
			break;
		default:
			match_vassert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 1163, FALSE, "### ERROR unsupported environment shader detail function");
		}

		pixel_shader.PSAlphaInputs[2] = 0x1c1b0000;
		pixel_shader.PSAlphaOutputs[2] = 0xc0;

		switch (shader_environment->environment.diffuse.micro_detail_map_function)
		{
		case _detail_function_double_biased_multiply:
			pixel_shader.PSRGBInputs[2] = 0xc0b0c0b;
			pixel_shader.PSRGBOutputs[2] = 0xc00;
			break;
		case _detail_function_multiply:
			pixel_shader.PSRGBInputs[2] = 0xc0b0000;
			pixel_shader.PSRGBOutputs[2] = 0xc00;
			break;
		case _detail_function_double_biased_add:
			pixel_shader.PSRGBInputs[2] = 0xc204b20;
			pixel_shader.PSRGBOutputs[2] = 0xc00;
			break;
		default:
			match_vassert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 1184, FALSE, "### ERROR unsupported environment shader detail function");
		}

		pixel_shader.PSFinalCombinerInputsEFG = 0x1c00;

		switch (rasterizer_debug_options.drawing_mode)
		{
		case 0:
		case 5:
		case 8:
			pixel_shader.PSFinalCombinerInputsABCD = 0xc;
			break;
		case 1:
			pixel_shader.PSFinalCombinerConstant0 = real_alpha_to_pixel32(0.33f);
			pixel_shader.PSFinalCombinerInputsABCD = 0xc110000;
			break;
		case 3:
		case 4:
		case 7:
			pixel_shader.PSFinalCombinerInputsABCD = 0x1c;
			break;
		default:
			match_vassert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 1206, FALSE, "### ERROR unsupported drawing mode in environment texture pass");
		}

		rasterizer_set_pixel_shader(&pixel_shader);
		rasterizer_draw_dynamic_triangles_static_vertices(dynamic_triangle_buffer_index, first_triangle_index, triangle_count, vertex_buffer);

		if (rasterizer_debug_options.statistics_mode==2)
		{
			rasterizer_frame_statistics.textures.primitives++;
			rasterizer_frame_statistics.textures.triangles += triangle_count;
			rasterizer_frame_statistics.textures.vertices += rasterizer_frame_statistics_count_dynamic_vertices(dynamic_triangle_buffer_index, first_triangle_index, triangle_count);
		}
	}
}

void _rasterizer_environment_diffuse_textures_end(
	void)
{
	rasterizer_set_stencil_mode(2);
	rasterizer_profile_end(8);
}

void _rasterizer_environment_specular_lights_begin(
	void)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 1253, global_d3d_device);

	rasterizer_profile_begin(11);

	if (rasterizer_debug_options.drawing_mode==0 &&
		rasterizer_debug_options.draw_environment_specular_lights)
	{
		rasterizer_set_texture_direct(2, global_rasterizer_data->vector_normalization.index, 0);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_ADDRESSW, D3DTADDRESS_CLAMP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);
		rasterizer_set_texture_direct(3, global_rasterizer_data->vector_normalization.index, 0);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_ADDRESSW, D3DTADDRESS_CLAMP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_CCW);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_BLUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHABLENDENABLE, TRUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_SRCBLEND, D3DBLEND_DESTALPHA);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_DESTBLEND, D3DBLEND_ONE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_BLENDOP, D3DBLENDOP_ADD);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHATESTENABLE, TRUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHAREF, 0);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZENABLE, D3DZB_TRUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZFUNC, D3DCMP_EQUAL);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZWRITEENABLE, FALSE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZBIAS, 0);
	}
}

// TODO: original copies light->forward/up through pointer temporaries (inlined helper?) and reloads light->definition (~89%)
static void rasterizer_environment_specular_spot_light_begin(
	long light_index)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 1311, global_d3d_device);

	if (rasterizer_debug_options.drawing_mode==0 &&
		rasterizer_debug_options.draw_environment_specular_lights)
	{
		struct rasterizer_light_submit_parameters *light;
		long gel_bitmap_index;
		real_matrix4x3 basis;
		real radius;
		real falloff_radius;
		real falloff_scale;
		real vsh_constants[VSH_CONSTANTS__POINTLIGHT_COUNT][4];

		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 1317, light_index>=0 && light_index<rasterizer_lights.light_count);
		light = &rasterizer_lights.lights[light_index];
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 1320, light->radius>0.0f);

		gel_bitmap_index = light->definition->gel.map.index;
		if (gel_bitmap_index==NONE)
		{
			gel_bitmap_index = light->definition->gel.secondary_map.index;
		}

		{
			real_vector3d const *forward = &light->forward;
			real_vector3d const *up = &light->up;

			basis.forward = *forward;
			cross_product3d(forward, up, &basis.left);
			basis.up = *up;
			normalize3d(&basis.left);
		}

		radius = light->definition->geometry.specular_radius_multiplier*light->radius;
		falloff_radius = 0.5f*radius;
		falloff_scale = 1.f/(radius-falloff_radius);

		vsh_constants[0][0] = light->position.x;
		vsh_constants[0][1] = light->position.y;
		vsh_constants[0][2] = light->position.z;
		vsh_constants[0][3] = 0.5f/radius;
		vsh_constants[1][0] = -basis.forward.i;
		vsh_constants[1][1] = -basis.forward.j;
		vsh_constants[1][2] = -basis.forward.k;
		vsh_constants[1][3] = 1.f;
		vsh_constants[2][0] = -basis.left.i;
		vsh_constants[2][1] = -basis.left.j;
		vsh_constants[2][2] = -basis.left.k;
		vsh_constants[2][3] = 1.f;
		vsh_constants[3][0] = -basis.up.i;
		vsh_constants[3][1] = -basis.up.j;
		vsh_constants[3][2] = -basis.up.k;
		vsh_constants[3][3] = 1.f;
		vsh_constants[4][0] = basis.forward.i*falloff_scale;
		vsh_constants[4][1] = basis.forward.j*falloff_scale;
		vsh_constants[4][2] = basis.forward.k*falloff_scale;
		vsh_constants[4][3] = -(falloff_radius*falloff_scale);
		IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, VSH_CONSTANTS__POINTLIGHT_OFFSET, vsh_constants, VSH_CONSTANTS__POINTLIGHT_COUNT);

		rasterizer_set_texture(1, 2, 1, gel_bitmap_index, 0);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_ADDRESSW, D3DTADDRESS_CLAMP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);

		csmemset(&pixel_shader, 0, sizeof(pixel_shader));
		pixel_shader.PSTextureModes = 0x18c61;
		pixel_shader.PSCombinerCount = 0x11006;
		pixel_shader.PSConstant0[0] = 0xff;
		pixel_shader.PSAlphaInputs[0] = 0x4b204b20;
		pixel_shader.PSAlphaOutputs[0] = 0x20400;
		pixel_shader.PSRGBInputs[0] = 0x484a0000;
		pixel_shader.PSRGBOutputs[0] = 0x20c0;
		pixel_shader.PSConstant0[1] = 0xff;
		pixel_shader.PSAlphaInputs[1] = 0x4a204a20;
		pixel_shader.PSAlphaOutputs[1] = 0x20500;
		pixel_shader.PSRGBInputs[1] = 0x48cc8a40;
		pixel_shader.PSRGBOutputs[1] = 0x10d00;
		pixel_shader.PSAlphaInputs[2] = 0x2c120c11;
		pixel_shader.PSAlphaOutputs[2] = 0xc00;
		pixel_shader.PSRGBInputs[2] = 0xcd4b0809;
		pixel_shader.PSRGBOutputs[2] = 0x20d0;
		pixel_shader.PSAlphaInputs[3] = 0xd0d1415;
		pixel_shader.PSAlphaOutputs[3] = 0xd5;
		pixel_shader.PSRGBInputs[3] = 0x2c020c01;
		pixel_shader.PSRGBOutputs[3] = 0xc00;
		pixel_shader.PSAlphaInputs[4] = 0x1d1d151c;
		pixel_shader.PSAlphaOutputs[4] = 0xd5;
		pixel_shader.PSRGBInputs[4] = 0xc091c09;
		pixel_shader.PSRGBOutputs[4] = 0x110cd;
		pixel_shader.PSAlphaInputs[5] = 0x1d1d0000;
		pixel_shader.PSAlphaOutputs[5] = 0xd0;
		pixel_shader.PSRGBInputs[5] = 0xc150d1d;
		pixel_shader.PSRGBOutputs[5] = 0x10cd;
		pixel_shader.PSFinalCombinerInputsABCD = 0xc0f0000;
		pixel_shader.PSFinalCombinerInputsEFG = 0x1d330d00;
		rasterizer_set_pixel_shader(&pixel_shader);
	}
}

void _rasterizer_environment_specular_light_begin(
	long light_index)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 1472, global_d3d_device);

	if (rasterizer_debug_options.drawing_mode==0 &&
		rasterizer_debug_options.draw_environment_specular_lights)
	{
		struct rasterizer_light_submit_parameters *light;

		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 1478, light_index>=0 && light_index<rasterizer_lights.light_count);
		light = &rasterizer_lights.lights[light_index];
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 1481, light->radius);

		if (light->definition->geometry.runtime_cosine_falloff_angle!=-1.f &&
			(light->definition->gel.map.index!=NONE || light->definition->gel.secondary_map.index!=NONE))
		{
			specular_light_vertex_shader_permutation_index = 1;
			specular_light_brightness = real_rgb_color_brightness(&light->color);
			rasterizer_environment_specular_spot_light_begin(light_index);
		}
		else
		{
			real vsh_constants[VSH_CONSTANTS__POINTLIGHT_COUNT][4];
			real inverse_radius;

			specular_light_vertex_shader_permutation_index = 0;
			specular_light_brightness = real_rgb_color_brightness(&light->color);
			inverse_radius = 1.f/(light->definition->geometry.specular_radius_multiplier*light->radius);

			vsh_constants[0][0] = light->position.x;
			vsh_constants[0][1] = light->position.y;
			vsh_constants[0][2] = light->position.z;
			vsh_constants[0][3] = 0.5f*inverse_radius;
			vsh_constants[1][0] = 0.f;
			vsh_constants[1][1] = 0.f;
			vsh_constants[1][2] = 0.f;
			vsh_constants[1][3] = 1.f;
			vsh_constants[2][0] = 0.f;
			vsh_constants[2][1] = 0.f;
			vsh_constants[2][2] = 0.f;
			vsh_constants[2][3] = 1.f;
			vsh_constants[3][0] = 0.f;
			vsh_constants[3][1] = 0.f;
			vsh_constants[3][2] = 0.f;
			vsh_constants[3][3] = 1.f;
			vsh_constants[4][0] = 0.f;
			vsh_constants[4][1] = 0.f;
			vsh_constants[4][2] = 0.f;
			vsh_constants[4][3] = 1.f;
			IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, VSH_CONSTANTS__POINTLIGHT_OFFSET, vsh_constants, VSH_CONSTANTS__POINTLIGHT_COUNT);

			rasterizer_set_texture_direct(1, global_rasterizer_data->distance_attenuation.index, 0);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_ADDRESSU, D3DTADDRESS_BORDER);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_ADDRESSV, D3DTADDRESS_BORDER);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_ADDRESSW, D3DTADDRESS_BORDER);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);

			csmemset(&pixel_shader, 0, sizeof(pixel_shader));
			pixel_shader.PSTextureModes = 0x18c41;
			pixel_shader.PSCombinerCount = 0x11006;
			pixel_shader.PSConstant0[0] = 0xff;
			pixel_shader.PSAlphaInputs[0] = 0x4b204b20;
			pixel_shader.PSAlphaOutputs[0] = 0x20400;
			pixel_shader.PSConstant0[1] = 0xff;
			pixel_shader.PSRGBInputs[0] = 0x484a0000;
			pixel_shader.PSRGBOutputs[0] = 0x20c0;
			pixel_shader.PSAlphaInputs[1] = 0x4a204a20;
			pixel_shader.PSAlphaOutputs[1] = 0x20500;
			pixel_shader.PSRGBInputs[1] = 0x48cc8a40;
			pixel_shader.PSRGBOutputs[1] = 0x10d00;
			pixel_shader.PSAlphaInputs[2] = 0x2c120c11;
			pixel_shader.PSAlphaOutputs[2] = 0xc00;
			pixel_shader.PSRGBInputs[2] = 0xcd4b0809;
			pixel_shader.PSRGBOutputs[2] = 0x20d0;
			pixel_shader.PSAlphaInputs[3] = 0xd0d1415;
			pixel_shader.PSAlphaOutputs[3] = 0xd5;
			pixel_shader.PSRGBInputs[3] = 0x2c020c01;
			pixel_shader.PSRGBOutputs[3] = 0xc00;
			pixel_shader.PSAlphaInputs[4] = 0x1d1d151c;
			pixel_shader.PSAlphaOutputs[4] = 0xd5;
			pixel_shader.PSRGBInputs[4] = 0xc091c09;
			pixel_shader.PSRGBOutputs[4] = 0x110cd;
			pixel_shader.PSAlphaInputs[5] = 0x1d1d0000;
			pixel_shader.PSAlphaOutputs[5] = 0xd0;
			pixel_shader.PSRGBInputs[5] = 0xc150d1d;
			pixel_shader.PSRGBOutputs[5] = 0x10cd;
			pixel_shader.PSFinalCombinerInputsABCD = 0xc0f0000;
			pixel_shader.PSFinalCombinerInputsEFG = 0x1d200d00;
			rasterizer_set_pixel_shader(&pixel_shader);
		}
	}
}

void _rasterizer_environment_specular_light_draw(
	struct shader const *shader,
	short bitmap_index,
	long dynamic_triangle_buffer_index,
	long first_triangle_index,
	long triangle_count,
	struct vertex_buffer const *vertex_buffer)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 1632, global_d3d_device);

	if (rasterizer_debug_options.drawing_mode==0 &&
		rasterizer_debug_options.draw_environment_specular_lights)
	{
		struct shader_environment *shader_environment;

		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 1639, shader);
		shader_environment = shader_get_and_verify_type(shader, _shader_type_environment);

		if (shader_environment->environment.specular.brightness>0.f && specular_light_brightness>0.f)
		{
			real vsh_constants[VSH_CONSTANTS__TEXSCALE_COUNT][4];

			match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 1645, vertex_buffer);

			rasterizer_set_vertex_shader_permutation(21, vertex_buffer->type, specular_light_vertex_shader_permutation_index);
			rasterizer_set_texture(0, 0, 3, shader_environment->environment.diffuse.bump_map.index, bitmap_index);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSU, D3DTADDRESS_WRAP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);

			vsh_constants[0][0] = shader_environment->environment.diffuse.runtime_bump_map_scale.i;
			vsh_constants[0][1] = shader_environment->environment.diffuse.runtime_bump_map_scale.j;
			vsh_constants[0][2] = 1.f;
			vsh_constants[0][3] = 1.f;
			vsh_constants[1][0] = 1.f;
			vsh_constants[1][1] = 0.f;
			vsh_constants[1][2] = 0.f;
			vsh_constants[1][3] = 0.f;
			vsh_constants[2][0] = 0.f;
			vsh_constants[2][1] = 1.f;
			vsh_constants[2][2] = 0.f;
			vsh_constants[2][3] = 0.f;
			shader_environment_texture_animation_evaluate(shader, global_frame_parameters.game_time_sec, &vsh_constants[1][3], &vsh_constants[2][3]);
			IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, VSH_CONSTANTS__TEXSCALE_OFFSET, vsh_constants, VSH_CONSTANTS__TEXSCALE_COUNT);

			pixel_shader.PSConstant0[2] = real_alpha_to_pixel32(specular_light_brightness*shader_environment->environment.specular.brightness);
			pixel_shader.PSConstant1[2] = real_alpha_to_pixel32(specular_light_brightness*shader_environment->environment.specular.brightness);
			pixel_shader.PSConstant0[3] = real_rgb_color_to_pixel32(&shader_environment->environment.specular.view_perpendicular_color);
			pixel_shader.PSConstant1[3] = real_rgb_color_to_pixel32(&shader_environment->environment.specular.view_parallel_color);

			if (TEST_FLAG(shader_environment->environment.flags, _shader_environment_bump_map_is_specular_mask_bit))
			{
				pixel_shader.PSRGBInputs[0] = 0x14a0000;
				pixel_shader.PSRGBInputs[1] = 0x1cc8a40;
				pixel_shader.PSRGBOutputs[2] = 0x20d9;
			}
			else
			{
				pixel_shader.PSRGBInputs[0] = 0x484a0000;
				pixel_shader.PSRGBInputs[1] = 0x48cc8a40;
				pixel_shader.PSRGBOutputs[2] = 0x20d0;
			}

			pixel_shader.PSRGBOutputs[4] = TEST_FLAG(shader_environment->environment.specular.flags, _shader_environment_specular_overbright_bit) ? 0x210cd : 0x110cd;

			if (TEST_FLAG(shader_environment->environment.specular.flags, _shader_environment_specular_extra_shiny_bit))
			{
				pixel_shader.PSCombinerCount = 0x11008;
				pixel_shader.PSAlphaInputs[6] = 0x1d1d0000;
				pixel_shader.PSAlphaOutputs[6] = 0xd0;
				pixel_shader.PSAlphaInputs[7] = 0x1d1d0000;
				pixel_shader.PSAlphaOutputs[7] = 0xd0;
			}
			else
			{
				pixel_shader.PSCombinerCount = 0x11006;
				pixel_shader.PSAlphaInputs[6] = 0;
				pixel_shader.PSAlphaOutputs[6] = 0;
				pixel_shader.PSAlphaInputs[7] = 0;
				pixel_shader.PSAlphaOutputs[7] = 0;
			}

			rasterizer_set_pixel_shader(&pixel_shader);
			rasterizer_draw_dynamic_triangles_static_vertices(dynamic_triangle_buffer_index, first_triangle_index, triangle_count, vertex_buffer);

			if (rasterizer_debug_options.statistics_mode==2)
			{
				rasterizer_frame_statistics.lights_specular.primitives++;
				rasterizer_frame_statistics.lights_specular.triangles += triangle_count;
				rasterizer_frame_statistics.lights_specular.vertices += rasterizer_frame_statistics_count_dynamic_vertices(dynamic_triangle_buffer_index, first_triangle_index, triangle_count);
			}
		}
	}
}

void _rasterizer_environment_specular_light_end(
	void)
{
}

void _rasterizer_environment_specular_lights_end(
	void)
{
	rasterizer_profile_end(11);
}

void _rasterizer_environment_specular_lightmaps_begin(
	void)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 1785, global_d3d_device);

	rasterizer_profile_begin(12);

	if (rasterizer_debug_options.drawing_mode==0 &&
		rasterizer_debug_options.draw_environment_specular_lightmaps &&
		rasterizer_globals.lightmap_mode==0)
	{
		rasterizer_set_texture_direct(2, global_rasterizer_data->vector_normalization.index, 0);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_ADDRESSW, D3DTADDRESS_CLAMP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);
		rasterizer_set_texture_direct(3, global_rasterizer_data->vector_normalization.index, 0);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_ADDRESSW, D3DTADDRESS_CLAMP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_CCW);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_BLUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHABLENDENABLE, TRUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_SRCBLEND, D3DBLEND_DESTALPHA);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_DESTBLEND, D3DBLEND_ONE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_BLENDOP, D3DBLENDOP_ADD);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHATESTENABLE, TRUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHAREF, 0);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZENABLE, D3DZB_TRUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZFUNC, D3DCMP_EQUAL);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZWRITEENABLE, FALSE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZBIAS, 0);

		csmemset(&pixel_shader, 0, sizeof(pixel_shader));
		pixel_shader.PSTextureModes = 0x18c21;
		pixel_shader.PSCombinerCount = 0x11006;
		pixel_shader.PSConstant0[0] = 0x800000ff;
		pixel_shader.PSAlphaInputs[0] = 0x4b204b20;
		pixel_shader.PSAlphaOutputs[0] = 0x20400;
		pixel_shader.PSRGBInputs[0] = 0x484a0911;
		pixel_shader.PSRGBOutputs[0] = 0x30c9;
		pixel_shader.PSConstant0[1] = 0xff;
		pixel_shader.PSAlphaInputs[1] = 0x4a204a20;
		pixel_shader.PSAlphaOutputs[1] = 0x20500;
		pixel_shader.PSRGBInputs[1] = 0x48cc8a40;
		pixel_shader.PSRGBOutputs[1] = 0x10d00;
		pixel_shader.PSAlphaInputs[2] = 0x2c120c11;
		pixel_shader.PSAlphaOutputs[2] = 0xc00;
		pixel_shader.PSRGBInputs[2] = 0xcd4b0809;
		pixel_shader.PSRGBOutputs[2] = 0x20d0;
		pixel_shader.PSAlphaInputs[3] = 0xd0d1415;
		pixel_shader.PSAlphaOutputs[3] = 0xd5;
		pixel_shader.PSRGBInputs[3] = 0x2c020c01;
		pixel_shader.PSRGBOutputs[3] = 0xc00;
		pixel_shader.PSAlphaInputs[4] = 0x1d1d151c;
		pixel_shader.PSAlphaOutputs[4] = 0xd5;
		pixel_shader.PSRGBInputs[4] = 0xc091c09;
		pixel_shader.PSRGBOutputs[4] = 0x110cd;
		pixel_shader.PSAlphaInputs[5] = 0x1d1d0000;
		pixel_shader.PSAlphaOutputs[5] = 0xd0;
		pixel_shader.PSRGBInputs[5] = 0xc150d1d;
		pixel_shader.PSRGBOutputs[5] = 0x10cd;
		pixel_shader.PSFinalCombinerConstant0 = 0x80000000;
		pixel_shader.PSFinalCombinerInputsABCD = 0xc0f0000;
		pixel_shader.PSFinalCombinerInputsEFG = 0x1d110d00;
		rasterizer_set_pixel_shader(&pixel_shader);
	}
}

void _rasterizer_environment_specular_lightmap_begin(
	struct bitmap_data *lightmap)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 1874, global_d3d_device);

	if (rasterizer_debug_options.drawing_mode==0 &&
		rasterizer_debug_options.draw_environment_specular_lightmaps)
	{
		if (lightmap)
		{
			rasterizer_set_texture_bitmap_data(1, lightmap);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MAGFILTER, rasterizer_debug_options.lightmap_filtering_enabled ? D3DTEXF_LINEAR : D3DTEXF_POINT);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MINFILTER, rasterizer_debug_options.lightmap_filtering_enabled ? D3DTEXF_LINEAR : D3DTEXF_POINT);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MIPFILTER, rasterizer_debug_options.lightmap_filtering_enabled ? D3DTEXF_LINEAR : D3DTEXF_POINT);
			local_lightmap_has_no_data = FALSE;
		}
		else
		{
			local_lightmap_has_no_data = TRUE;
		}
	}
}

void _rasterizer_environment_specular_lightmap_draw(
	struct shader const *shader,
	short bitmap_index,
	long dynamic_triangle_buffer_index,
	long first_triangle_index,
	long triangle_count,
	struct vertex_buffer const *vertex_buffers)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 1915, global_d3d_device);

	if (rasterizer_debug_options.drawing_mode==0 &&
		rasterizer_debug_options.draw_environment_specular_lightmaps &&
		rasterizer_globals.lightmap_mode==0 &&
		!local_lightmap_has_no_data)
	{
		struct shader_environment *shader_environment;

		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 1924, shader);
		shader_environment = shader_get_and_verify_type(shader, _shader_type_environment);

		if (shader_environment->environment.specular.brightness>0.f &&
			TEST_FLAG(shader_environment->environment.specular.flags, _shader_environment_specular_lightmap_is_specular_bit))
		{
			real vsh_constants[VSH_CONSTANTS__TEXSCALE_COUNT][4];

			rasterizer_set_vertex_shader_permutation(21, vertex_buffers->type, 2);
			rasterizer_set_texture(0, 0, 3, shader_environment->environment.diffuse.bump_map.index, bitmap_index);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSU, D3DTADDRESS_WRAP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);

			vsh_constants[0][0] = shader_environment->environment.diffuse.runtime_bump_map_scale.i;
			vsh_constants[0][1] = shader_environment->environment.diffuse.runtime_bump_map_scale.j;
			vsh_constants[0][2] = 1.f;
			vsh_constants[0][3] = 1.f;
			vsh_constants[1][0] = 1.f;
			vsh_constants[1][1] = 0.f;
			vsh_constants[1][2] = 0.f;
			vsh_constants[1][3] = 0.f;
			vsh_constants[2][0] = 0.f;
			vsh_constants[2][1] = 1.f;
			vsh_constants[2][2] = 0.f;
			vsh_constants[2][3] = 0.f;
			shader_environment_texture_animation_evaluate(shader, global_frame_parameters.game_time_sec, &vsh_constants[1][3], &vsh_constants[2][3]);
			IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, VSH_CONSTANTS__TEXSCALE_OFFSET, vsh_constants, VSH_CONSTANTS__TEXSCALE_COUNT);

			pixel_shader.PSConstant0[2] = real_alpha_to_pixel32(shader_environment->environment.specular.brightness);
			pixel_shader.PSConstant1[2] = real_alpha_to_pixel32(shader_environment->environment.specular.brightness);
			pixel_shader.PSConstant0[3] = real_rgb_color_to_pixel32(&shader_environment->environment.specular.view_perpendicular_color);
			pixel_shader.PSConstant1[3] = real_rgb_color_to_pixel32(&shader_environment->environment.specular.view_parallel_color);

			if (TEST_FLAG(shader_environment->environment.flags, _shader_environment_bump_map_is_specular_mask_bit))
			{
				pixel_shader.PSRGBInputs[0] = 0x14a0911;
				pixel_shader.PSRGBInputs[1] = 0x1cc8a40;
				pixel_shader.PSRGBOutputs[2] = 0x20d9;
			}
			else
			{
				pixel_shader.PSRGBInputs[0] = 0x484a0911;
				pixel_shader.PSRGBInputs[1] = 0x48cc8a40;
				pixel_shader.PSRGBOutputs[2] = 0x20d0;
			}

			pixel_shader.PSRGBOutputs[4] = TEST_FLAG(shader_environment->environment.specular.flags, _shader_environment_specular_overbright_bit) ? 0x210cd : 0x110cd;

			if (TEST_FLAG(shader_environment->environment.specular.flags, _shader_environment_specular_extra_shiny_bit))
			{
				pixel_shader.PSCombinerCount = 0x11008;
				pixel_shader.PSAlphaInputs[6] = 0x1d1d0000;
				pixel_shader.PSAlphaOutputs[6] = 0xd0;
				pixel_shader.PSAlphaInputs[7] = 0x1d1d0000;
				pixel_shader.PSAlphaOutputs[7] = 0xd0;
			}
			else
			{
				pixel_shader.PSCombinerCount = 0x11006;
				pixel_shader.PSAlphaInputs[6] = 0;
				pixel_shader.PSAlphaOutputs[6] = 0;
				pixel_shader.PSAlphaInputs[7] = 0;
				pixel_shader.PSAlphaOutputs[7] = 0;
			}

			rasterizer_set_pixel_shader(&pixel_shader);
			rasterizer_draw_dynamic_triangles_static_vertices2(dynamic_triangle_buffer_index, first_triangle_index, triangle_count, &vertex_buffers[0], &vertex_buffers[1]);

			if (rasterizer_debug_options.statistics_mode==2)
			{
				rasterizer_frame_statistics.lightmaps_specular.primitives++;
				rasterizer_frame_statistics.lightmaps_specular.triangles += triangle_count;
				rasterizer_frame_statistics.lightmaps_specular.vertices += rasterizer_frame_statistics_count_dynamic_vertices(dynamic_triangle_buffer_index, first_triangle_index, triangle_count);
			}
		}
	}
}

void _rasterizer_environment_specular_lightmap_end(
	void)
{
}

void _rasterizer_environment_specular_lightmaps_end(
	void)
{
	rasterizer_profile_end(12);
}

void _rasterizer_environment_reflection_lightmap_masks_begin(
	void)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 2069, global_d3d_device);

	rasterizer_profile_begin(13);

	if (rasterizer_debug_options.drawing_mode==0 &&
		rasterizer_debug_options.draw_environment_reflection_lightmap_masks &&
		rasterizer_debug_options.draw_environment_reflections &&
		rasterizer_globals.lightmap_mode==0)
	{
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_CCW);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_ALPHA);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHABLENDENABLE, TRUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_SRCBLEND, D3DBLEND_DESTALPHA);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_DESTBLEND, D3DBLEND_ZERO);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_BLENDOP, D3DBLENDOP_ADD);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHATESTENABLE, FALSE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZENABLE, D3DZB_TRUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZFUNC, D3DCMP_EQUAL);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZWRITEENABLE, FALSE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZBIAS, 0);

		csmemset(&pixel_shader, 0, sizeof(pixel_shader));
		pixel_shader.PSTextureModes = 0x1;
		pixel_shader.PSCombinerCount = 0x2;
		pixel_shader.PSConstant0[0] = 0x80b050;
		pixel_shader.PSRGBInputs[0] = 0x8010000;
		pixel_shader.PSRGBOutputs[0] = 0x20c0;
		pixel_shader.PSAlphaInputs[1] = 0x2c120c20;
		pixel_shader.PSAlphaOutputs[1] = 0xc00;
		pixel_shader.PSFinalCombinerInputsABCD = 0;
		pixel_shader.PSFinalCombinerInputsEFG = 0x1c00;
		rasterizer_set_pixel_shader(&pixel_shader);
	}
}

void _rasterizer_environment_reflection_lightmap_mask_begin(
	struct bitmap_data *lightmap)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 2120, global_d3d_device);

	if (rasterizer_debug_options.drawing_mode==0 &&
		rasterizer_debug_options.draw_environment_reflection_lightmap_masks &&
		rasterizer_debug_options.draw_environment_reflections &&
		rasterizer_globals.lightmap_mode==0)
	{
		if (lightmap)
		{
			rasterizer_set_texture_bitmap_data(0, lightmap);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MAGFILTER, rasterizer_debug_options.lightmap_filtering_enabled ? D3DTEXF_LINEAR : D3DTEXF_POINT);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MINFILTER, rasterizer_debug_options.lightmap_filtering_enabled ? D3DTEXF_LINEAR : D3DTEXF_POINT);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MIPFILTER, rasterizer_debug_options.lightmap_filtering_enabled ? D3DTEXF_LINEAR : D3DTEXF_POINT);
			local_lightmap_has_no_data = FALSE;
		}
		else
		{
			local_lightmap_has_no_data = TRUE;
		}
	}
}

void _rasterizer_environment_reflection_lightmap_mask_draw(
	struct shader const *shader,
	long unused,
	long dynamic_triangle_buffer_index,
	long first_triangle_index,
	long triangle_count,
	struct vertex_buffer const *vertex_buffers)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 2163, global_d3d_device);

	if (rasterizer_debug_options.drawing_mode==0 &&
		rasterizer_debug_options.draw_environment_reflection_lightmap_masks &&
		rasterizer_debug_options.draw_environment_reflections &&
		rasterizer_globals.lightmap_mode==0 &&
		!local_lightmap_has_no_data)
	{
		struct shader_environment *shader_environment;

		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 2173, shader);
		shader_environment = shader_get_and_verify_type(shader, _shader_type_environment);

		if ((shader_environment->environment.reflection.view_perpendicular_brightness>0.f || shader_environment->environment.reflection.view_parallel_brightness>0.f) &&
			shader_environment->environment.reflection.lightmap_brightness_scale<1.f)
		{
			real vsh_constants[VSH_CONSTANTS__TEXSCALE_COUNT][4];

			rasterizer_set_vertex_shader_permutation(58, vertex_buffers->type, 0);

			vsh_constants[0][0] = shader_environment->environment.diffuse.runtime_bump_map_scale.i;
			vsh_constants[0][1] = shader_environment->environment.diffuse.runtime_bump_map_scale.j;
			vsh_constants[0][2] = 1.f;
			vsh_constants[0][3] = 1.f;
			vsh_constants[1][0] = 1.f;
			vsh_constants[1][1] = 0.f;
			vsh_constants[1][2] = 0.f;
			vsh_constants[1][3] = 0.f;
			vsh_constants[2][0] = 0.f;
			vsh_constants[2][1] = 1.f;
			vsh_constants[2][2] = 0.f;
			vsh_constants[2][3] = 0.f;
			shader_environment_texture_animation_evaluate(shader, global_frame_parameters.game_time_sec, &vsh_constants[1][3], &vsh_constants[2][3]);
			IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, VSH_CONSTANTS__TEXSCALE_OFFSET, vsh_constants, VSH_CONSTANTS__TEXSCALE_COUNT);

			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_PSCONSTANT1_0, real_alpha_to_pixel32(shader_environment->environment.reflection.lightmap_brightness_scale));

			rasterizer_draw_dynamic_triangles_static_vertices2(dynamic_triangle_buffer_index, first_triangle_index, triangle_count, &vertex_buffers[0], &vertex_buffers[1]);

			if (rasterizer_debug_options.statistics_mode==2)
			{
				rasterizer_frame_statistics.lightmaps_reflection_mask.primitives++;
				rasterizer_frame_statistics.lightmaps_reflection_mask.triangles += triangle_count;
				rasterizer_frame_statistics.lightmaps_reflection_mask.vertices += rasterizer_frame_statistics_count_dynamic_vertices(dynamic_triangle_buffer_index, first_triangle_index, triangle_count);
			}
		}
	}
}

void _rasterizer_environment_reflection_lightmap_mask_end(
	void)
{
}

void _rasterizer_environment_reflection_lightmap_masks_end(
	void)
{
	rasterizer_profile_end(13);
}

void _rasterizer_environment_reflection_mirrors_begin(
	void)
{
	rasterizer_profile_begin(14);
}

void _rasterizer_environment_reflection_mirror_draw(
	struct shader const *shader,
	short bitmap_index,
	long dynamic_triangle_buffer_index,
	long first_triangle_index,
	long triangle_count,
	struct vertex_buffer const *vertex_buffer)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 2271, global_d3d_device);

	if (rasterizer_debug_options.drawing_mode==0 &&
		rasterizer_debug_options.draw_environment_reflection_mirrors &&
		global_window_parameters.has_mirror &&
		global_window_parameters.rasterizer_target==_rasterizer_target_render_primary)
	{
		struct shader_environment *shader_environment;

		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 2280, shader);
		shader_environment = shader_get_and_verify_type(shader, _shader_type_environment);

		if (TEST_FLAG(shader_environment->environment.reflection.flags, _shader_environment_reflection_dynamic_mirror_bit) &&
			(shader_environment->environment.reflection.view_perpendicular_brightness>0.f || shader_environment->environment.reflection.view_parallel_brightness>0.f))
		{
			real vsh_constants[VSH_CONSTANTS__TEXSCALE_COUNT][4];

			match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 2287, vertex_buffer);

			rasterizer_set_texture(0, 0, 3, shader_environment->environment.diffuse.bump_map.index, bitmap_index);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSU, D3DTADDRESS_WRAP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);
			rasterizer_set_texture_direct(1, global_rasterizer_data->vector_normalization.index, 0);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_ADDRESSW, D3DTADDRESS_CLAMP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MINFILTER, D3DTEXF_POINT);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MIPFILTER, D3DTEXF_POINT);
			rasterizer_set_texture_direct(2, global_rasterizer_data->vector_normalization.index, 0);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_ADDRESSW, D3DTADDRESS_CLAMP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_MINFILTER, D3DTEXF_POINT);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_MIPFILTER, D3DTEXF_POINT);
			rasterizer_set_target_as_texture(3, _rasterizer_target_render_secondary, 0);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_CCW);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_BLUE);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHABLENDENABLE, TRUE);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_SRCBLEND, D3DBLEND_DESTALPHA);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_DESTBLEND, D3DBLEND_ONE);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_BLENDOP, D3DBLENDOP_ADD);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHATESTENABLE, FALSE);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZENABLE, D3DZB_TRUE);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZFUNC, D3DCMP_EQUAL);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZWRITEENABLE, FALSE);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZBIAS, 0);

			rasterizer_set_vertex_shader_permutation(51, vertex_buffer->type, 0);

			vsh_constants[0][0] = shader_environment->environment.diffuse.runtime_bump_map_scale.i;
			vsh_constants[0][1] = shader_environment->environment.diffuse.runtime_bump_map_scale.j;
			vsh_constants[0][2] = 320.f;
			vsh_constants[0][3] = 240.f;
			vsh_constants[1][0] = 1.f;
			vsh_constants[1][1] = 0.f;
			vsh_constants[1][2] = 0.f;
			vsh_constants[1][3] = 0.f;
			vsh_constants[2][0] = 0.f;
			vsh_constants[2][1] = 1.f;
			vsh_constants[2][2] = 0.f;
			vsh_constants[2][3] = 0.f;
			shader_environment_texture_animation_evaluate(shader, global_frame_parameters.game_time_sec, &vsh_constants[1][3], &vsh_constants[2][3]);
			IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, VSH_CONSTANTS__TEXSCALE_OFFSET, vsh_constants, VSH_CONSTANTS__TEXSCALE_COUNT);

			csmemset(&pixel_shader, 0, sizeof(pixel_shader));
			pixel_shader.PSTextureModes = 0x8c61;
			pixel_shader.PSCombinerCount = 0x11005;

			if (shader_environment->environment.diffuse.bump_map.index==NONE)
			{
				real_rgb_color flat_normal_color;

				flat_normal_color.red = PIN(0.5f - global_window_parameters.camera.forward.i*0.5f, 0.f, 1.f);
				flat_normal_color.green = PIN(0.5f - global_window_parameters.camera.forward.j*0.5f, 0.f, 1.f);
				flat_normal_color.blue = PIN(0.5f - global_window_parameters.camera.forward.k*0.5f, 0.f, 1.f);
				pixel_shader.PSConstant0[0] = real_rgb_color_to_pixel32(&flat_normal_color);
				pixel_shader.PSRGBInputs[0] = 0x4a410b0b;
			}
			else
			{
				pixel_shader.PSRGBInputs[0] = 0x49480b0b;
			}

			pixel_shader.PSRGBOutputs[0] = 0x20cd;
			pixel_shader.PSRGBInputs[1] = 0xc0c0d0d;
			pixel_shader.PSRGBOutputs[1] = 0xcd;
			pixel_shader.PSRGBInputs[2] = 0xc0c0d0d;
			pixel_shader.PSRGBOutputs[2] = 0xd;
			pixel_shader.PSConstant0[3] = real_a_rgb_color_to_pixel32(shader_environment->environment.reflection.view_perpendicular_brightness, &shader_environment->environment.specular.view_perpendicular_color);
			pixel_shader.PSConstant1[3] = real_a_rgb_color_to_pixel32(shader_environment->environment.reflection.view_parallel_brightness, &shader_environment->environment.specular.view_parallel_color);
			pixel_shader.PSAlphaOutputs[3] = 0xc00;
			pixel_shader.PSRGBOutputs[3] = 0xc00;
			pixel_shader.PSRGBOutputs[4] = 0xc00;
			pixel_shader.PSAlphaInputs[3] = 0x2c120c11;
			pixel_shader.PSRGBInputs[3] = 0x2c020c01;
			pixel_shader.PSRGBInputs[4] = 0x2c0d0c0b;
			pixel_shader.PSFinalCombinerInputsABCD = 0xc0f0000;
			pixel_shader.PSFinalCombinerInputsEFG = ((TEST_FLAG(shader_environment->environment.flags, _shader_environment_bump_map_is_specular_mask_bit) ? 0x08 : 0x20) | 0x1c00) << 16;
			rasterizer_set_pixel_shader(&pixel_shader);

			rasterizer_draw_dynamic_triangles_static_vertices(dynamic_triangle_buffer_index, first_triangle_index, triangle_count, vertex_buffer);

			if (rasterizer_debug_options.statistics_mode==2)
			{
				rasterizer_frame_statistics.reflections.primitives++;
				rasterizer_frame_statistics.reflections.triangles += triangle_count;
				rasterizer_frame_statistics.reflections.vertices += rasterizer_frame_statistics_count_dynamic_vertices(dynamic_triangle_buffer_index, first_triangle_index, triangle_count);
			}
		}
	}
}

void _rasterizer_environment_reflection_mirrors_end(
	void)
{
	rasterizer_profile_end(14);
}

void _rasterizer_environment_reflections_begin(
	void)
{
	rasterizer_profile_begin(15);
}

void _rasterizer_environment_reflection_draw(
	struct shader const *shader,
	short bitmap_index,
	long dynamic_triangle_buffer_index,
	long first_triangle_index,
	long triangle_count,
	struct vertex_buffer const *vertex_buffers)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 2462, global_d3d_device);

	if (rasterizer_debug_options.drawing_mode==0 &&
		rasterizer_debug_options.draw_environment_reflections)
	{
		struct shader_environment *shader_environment;
		short reflection_type;

		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 2470, shader);
		shader_environment = shader_get_and_verify_type(shader, _shader_type_environment);

		reflection_type = shader_environment->environment.reflection.type;
		if (reflection_type==_shader_environment_reflection_type_bumped_cube_map ||
			reflection_type==_shader_environment_reflection_type_bumped_radiance)
		{
			if (TEST_FLAG(shader_environment->environment.flags, _shader_environment_bump_map_is_specular_mask_bit))
			{
				reflection_type = _shader_environment_reflection_type_flat_cube_map;
			}
			if (shader_environment->environment.diffuse.bump_map.index==NONE)
			{
				reflection_type = _shader_environment_reflection_type_flat_cube_map;
			}
		}

		if ((shader_environment->environment.reflection.view_perpendicular_brightness>0.f || shader_environment->environment.reflection.view_parallel_brightness>0.f) &&
			shader_environment->environment.reflection.map.index!=NONE)
		{
			real vsh_constants[VSH_CONSTANTS__TEXSCALE_COUNT][4];

			match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 2495, vertex_buffers);
			match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 2496, reflection_type>=0 && reflection_type<NUMBER_OF_SHADER_ENVIRONMENT_REFLECTION_TYPES);

			rasterizer_set_texture(0, 0, 3, shader_environment->environment.diffuse.bump_map.index, bitmap_index);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSU, D3DTADDRESS_WRAP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);
			rasterizer_set_texture_direct(1, global_rasterizer_data->vector_normalization.index, 0);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_ADDRESSW, D3DTADDRESS_CLAMP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MINFILTER, D3DTEXF_POINT);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MIPFILTER, D3DTEXF_POINT);
			rasterizer_set_texture_direct(2, global_rasterizer_data->vector_normalization.index, 0);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_ADDRESSW, D3DTADDRESS_CLAMP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_MINFILTER, D3DTEXF_POINT);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_MIPFILTER, D3DTEXF_POINT);
			rasterizer_set_texture(3, 2, 0, shader_environment->environment.reflection.map.index, bitmap_index);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_ADDRESSW, D3DTADDRESS_CLAMP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_CCW);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_BLUE);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHABLENDENABLE, TRUE);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_SRCBLEND, D3DBLEND_DESTALPHA);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_DESTBLEND, D3DBLEND_ONE);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_BLENDOP, D3DBLENDOP_ADD);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHATESTENABLE, FALSE);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZENABLE, D3DZB_TRUE);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZFUNC, D3DCMP_EQUAL);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZWRITEENABLE, FALSE);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZBIAS, 0);

			rasterizer_set_vertex_shader_permutation(42, vertex_buffers->type, reflection_type);

			vsh_constants[0][0] = shader_environment->environment.diffuse.runtime_bump_map_scale.i;
			vsh_constants[0][1] = shader_environment->environment.diffuse.runtime_bump_map_scale.j;
			vsh_constants[0][2] = 320.f;
			vsh_constants[0][3] = 240.f;
			vsh_constants[1][0] = 1.f;
			vsh_constants[1][1] = 0.f;
			vsh_constants[1][2] = 0.f;
			vsh_constants[1][3] = 0.f;
			vsh_constants[2][0] = 0.f;
			vsh_constants[2][1] = 1.f;
			vsh_constants[2][2] = 0.f;
			vsh_constants[2][3] = 0.f;
			shader_environment_texture_animation_evaluate(shader, global_frame_parameters.game_time_sec, &vsh_constants[1][3], &vsh_constants[2][3]);
			IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, VSH_CONSTANTS__TEXSCALE_OFFSET, vsh_constants, VSH_CONSTANTS__TEXSCALE_COUNT);

			csmemset(&pixel_shader, 0, sizeof(pixel_shader));

			switch (reflection_type)
			{
			case _shader_environment_reflection_type_bumped_cube_map:
			case _shader_environment_reflection_type_bumped_radiance:
				pixel_shader.PSTextureModes = 0x62e21;
				pixel_shader.PSInputTexture = 0;
				pixel_shader.PSDotMapping = 0x111;
				break;
			case _shader_environment_reflection_type_flat_cube_map:
				pixel_shader.PSTextureModes = 0x18c61;
				break;
			default:
				match_vassert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 2592, FALSE, "### ERROR unsupported reflection type");
			}

			pixel_shader.PSCombinerCount = 0x11005;

			if (reflection_type==_shader_environment_reflection_type_bumped_cube_map ||
				reflection_type==_shader_environment_reflection_type_bumped_radiance ||
				shader_environment->environment.diffuse.bump_map.index==NONE)
			{
				real_rgb_color flat_normal_color;

				flat_normal_color.red = PIN(0.5f - global_window_parameters.camera.forward.i*0.5f, 0.f, 1.f);
				flat_normal_color.green = PIN(0.5f - global_window_parameters.camera.forward.j*0.5f, 0.f, 1.f);
				flat_normal_color.blue = PIN(0.5f - global_window_parameters.camera.forward.k*0.5f, 0.f, 1.f);
				pixel_shader.PSConstant0[0] = real_rgb_color_to_pixel32(&flat_normal_color);
				pixel_shader.PSRGBInputs[0] = 0x4a410b0b;
			}
			else
			{
				pixel_shader.PSRGBInputs[0] = 0x49480b0b;
			}

			pixel_shader.PSRGBInputs[1] = 0xc0c0d0d;
			pixel_shader.PSRGBInputs[2] = 0xc0c0d0d;
			pixel_shader.PSRGBOutputs[0] = 0x20cd;
			pixel_shader.PSRGBOutputs[1] = 0xcd;
			pixel_shader.PSRGBOutputs[2] = 0xd;
			pixel_shader.PSConstant0[3] = real_a_rgb_color_to_pixel32(shader_environment->environment.reflection.view_perpendicular_brightness, &shader_environment->environment.specular.view_perpendicular_color);
			pixel_shader.PSConstant1[3] = real_a_rgb_color_to_pixel32(shader_environment->environment.reflection.view_parallel_brightness, &shader_environment->environment.specular.view_parallel_color);
			pixel_shader.PSAlphaInputs[3] = 0x2c120c11;
			pixel_shader.PSAlphaOutputs[3] = 0xc00;
			pixel_shader.PSRGBInputs[3] = 0x2c020c01;
			pixel_shader.PSRGBOutputs[3] = 0xc00;
			pixel_shader.PSRGBInputs[4] = 0x2c0d0c0b;
			pixel_shader.PSRGBOutputs[4] = 0xc00;
			pixel_shader.PSFinalCombinerInputsABCD = 0xc0f0000;
			pixel_shader.PSFinalCombinerInputsEFG = ((TEST_FLAG(shader_environment->environment.flags, _shader_environment_bump_map_is_specular_mask_bit) ? 0x08 : 0x20) | 0x1c00) << 16;
			rasterizer_set_pixel_shader(&pixel_shader);

			rasterizer_draw_dynamic_triangles_static_vertices2(dynamic_triangle_buffer_index, first_triangle_index, triangle_count, &vertex_buffers[0], &vertex_buffers[(rasterizer_globals.lightmap_mode!=0 && reflection_type==_shader_environment_reflection_type_bumped_radiance) ? 1 : 0]);

			if (rasterizer_debug_options.statistics_mode==2)
			{
				rasterizer_frame_statistics.reflections.primitives++;
				rasterizer_frame_statistics.reflections.triangles += triangle_count;
				rasterizer_frame_statistics.reflections.vertices += rasterizer_frame_statistics_count_dynamic_vertices(dynamic_triangle_buffer_index, first_triangle_index, triangle_count);
			}
		}
	}
}

void _rasterizer_environment_reflections_end(
	void)
{
	rasterizer_profile_end(15);
}

void _rasterizer_environment_transparent_geometry_begin(
	void)
{
	rasterizer_profile_begin(16);
	rasterizer_transparent_geometry_groups_begin();
}

void _rasterizer_environment_transparent_geometry_submit(
	struct shader const *shader,
	short shader_permutation_index,
	long lightmap,
	long dynamic_triangle_buffer_index,
	long first_triangle_index,
	long triangle_count,
	struct vertex_buffer const *vertex_buffers,
	real_point3d const *centroid,
	real_plane3d const *plane,
	long unused,
	void const *lighting,
	unsigned long geometry_flags)
{
	static struct transparent_geometry_group local_group;
	static boolean warned= FALSE;

	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 2699, global_d3d_device);

	if (rasterizer_debug_options.draw_environment_transparent_geometry)
	{
		struct transparent_geometry_group *group;
		real_vector3d camera_to_centroid;
		real_plane3d default_plane;
		unsigned long no_queue;

		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 2706, shader);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 2707, shader->base.type!=_shader_type_environment);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 2708, shader_type_is_valid_for_environment(shader->base.type));
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 2709, centroid);

		vector_from_points3d(&global_window_parameters.camera.position, centroid, &camera_to_centroid);

		if (plane)
		{
			SET_FLAG(geometry_flags, _rasterizer_geometry_no_sort_bit, TRUE);
		}
		if (shader_is_decal((struct shader *)shader))
		{
			geometry_flags |= FLAG(_rasterizer_geometry_no_sort_bit) | FLAG(_rasterizer_geometry_no_queue_bit) | FLAG(_rasterizer_geometry_no_fog_bit);
		}

		no_queue = geometry_flags & FLAG(_rasterizer_geometry_no_queue_bit);
		if (no_queue)
		{
			group = &local_group;
			group->sorted_index = NONE;
		}
		else
		{
			group = rasterizer_transparent_geometry_new_group();
		}

		if (group)
		{
			group->geometry_flags = geometry_flags;
			group->shader = shader;
			group->shader_permutation_index = shader_permutation_index;
			group->dynamic_triangle_buffer_index = dynamic_triangle_buffer_index;
			group->first_triangle_index = first_triangle_index;
			group->triangle_count = triangle_count;
			group->vertex_buffers = vertex_buffers;
			group->lightmap = (struct bitmap_data const *)lightmap;
			group->object_index = 0;
			group->source_object_index = 0;
			group->effect.type = 0;
			group->triangle_buffer = NULL;
			group->dynamic_vertex_buffer_index = NONE;
			default_plane.n.i = 0.f;
			default_plane.n.j = 0.f;
			default_plane.n.k = 0.f;
			default_plane.d = 0.f;
			group->z_sort = -dot_product3d(&global_window_parameters.camera.forward, &camera_to_centroid);
			group->centroid = *centroid;
			group->plane = plane ? *plane : default_plane;
			group->prev_group_presorted_index = NONE;
			group->next_group_presorted_index = NONE;
			group->model_base_map_scale.j = 1.f;
			group->model_base_map_scale.i = 1.f;
			group->active_camouflage_transparent_source_object_index = 0;
			group->cortana_hack = FALSE;
			group->node_matrices = NULL;
			group->node_matrix_count = 0;
			group->lighting = rasterizer_memory_alloc_const(lighting, 0x74);
			group->animation = NULL;

			if (shader->base.type==_shader_type_transparent_water)
			{
				rasterizer_water_set_visibility_for_window(TRUE);
			}

			if (shader->base.type==_shader_type_transparent_water &&
				TEST_FLAG(((struct shader_transparent_water *)shader_get_and_verify_type(shader, _shader_type_transparent_water))->water.flags, _shader_transparent_water_draw_before_fog_bit))
			{
				match_vassert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment.c", 2782, !no_queue, "!TEST_FLAG(geometry_flags, _rasterizer_geometry_no_queue_bit)");
				SET_FLAG(group->geometry_flags, _rasterizer_geometry_no_queue_bit, TRUE);
				rasterizer_transparent_geometry_group_draw(group, FALSE);
				rasterizer_transparent_geometry_set_group_pending_status(group, TRUE);
				SET_FLAG(group->geometry_flags, _rasterizer_geometry_no_queue_bit, FALSE);
			}
			else if (no_queue)
			{
				rasterizer_transparent_geometry_group_draw(group, FALSE);
			}

			if (rasterizer_debug_options.statistics_mode==2)
			{
				rasterizer_frame_statistics.transparent.primitives++;
				rasterizer_frame_statistics.transparent.triangles += triangle_count;
				if (triangle_count>rasterizer_frame_statistics.transparent.triangles_maximum)
				{
					rasterizer_frame_statistics.transparent.triangles_maximum = triangle_count;
				}
				rasterizer_frame_statistics.transparent.vertices += rasterizer_frame_statistics_count_dynamic_vertices(dynamic_triangle_buffer_index, first_triangle_index, triangle_count);
			}
		}
		else if (!warned)
		{
			error(_error_silent, "### ERROR too many transparent geometry groups");
			warned = TRUE;
		}
	}
}

void _rasterizer_environment_transparent_geometry_end(
	void)
{
	rasterizer_transparent_geometry_groups_end();
	rasterizer_profile_end(16);
}
