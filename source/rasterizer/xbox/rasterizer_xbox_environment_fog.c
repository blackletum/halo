/*
RASTERIZER_XBOX_ENVIRONMENT_FOG.C

symbols in this file:
00154FD0 01b0:
	_D3DDevice_SetRenderState (0000)
00155180 0050:
	_D3DDevice_SetTextureStageState (0000)
001551D0 0020:
	_IDirect3DDevice8_Clear@28 (0000)
001551F0 0220:
	_IDirect3DDevice8_SetRenderState@12 (0000)
00155410 0050:
	_rasterizer_environment_fog_screen_initialize (0000)
00155460 0010:
	_rasterizer_environment_fog_screen_window_begin (0000)
00155470 0010:
	_rasterizer_environment_fog_screen_window_end (0000)
00155480 0020:
	_rasterizer_environment_fog_screen_dispose (0000)
001554A0 0060:
	_IDirect3DDevice8_SetTextureStageState@16 (0000)
00155500 0010:
	_IDirect3DDevice8_SetVertexShaderConstant@16 (0000)
00155510 0110:
	__rasterizer_environment_fog_draw (0000)
00155620 0010:
	__rasterizer_environment_fog_end (0000)
00155630 0090:
	__rasterizer_environment_fog_screen_wind_get_vector (0000)
001556C0 0010:
	_IDirect3DDevice8_SetVertexData2s@16 (0000)
001556D0 0010:
	_IDirect3DDevice8_Begin@8 (0000)
001556E0 0010:
	_IDirect3DDevice8_End@4 (0000)
001556F0 0120:
	_rasterizer_environment_fog_screen_model_submit (0000)
00155810 0010:
	_rasterizer_environment_fog_screen_model_end (0000)
00155820 0020:
	_set_real_vector4d (0000)
00155840 0020:
	_local_random_boolean (0000)
00155860 0200:
	_code_00155860 (0000)
00155A60 01f0:
	_code_00155a60 (0000)
00155C50 0490:
	__rasterizer_environment_fog_begin (0000)
001560E0 0f40:
	__rasterizer_environment_fog_screen_begin (0000)
00157020 0150:
	__rasterizer_environment_fog_screen_draw (0000)
00157170 05c0:
	__rasterizer_environment_fog_screen_end (0000)
00157730 0110:
	_rasterizer_environment_fog_screen_model_begin (0000)
002901A0 0055:
	??_C@_0FF@JIPOFCBH@?$CD?$CD?$CD?5ERROR?5failed?5to?5allocate?5opa@ (0000)
002901F8 0041:
	??_C@_0EB@OOILAKOF@c?3?2halo?2SOURCE?2rasterizer?2xbox?2r@ (0000)
0029023C 000c:
	??_C@_0M@OAKCKJA@wind_vector?$AA@ (0000)
00290248 0030:
	??_C@_0DA@PEPFBGPF@window_index?$DO?$DN0?5?$CG?$CG?5window_index?$DM@ (0000)
00290278 0046:
	??_C@_0EG@PBACNIHN@?$CD?$CD?$CD?5ERROR?5too?5many?5opaque?5model?5@ (0000)
002902C0 0038:
	??_C@_0DI@GACGFDCH@global_window_parameters?4fog?4pla@ (0000)
002902F8 0005:
	??_C@_04HHNJMEDN@wind?$AA@ (0000)
00290300 0007:
	??_C@_06LPLGMLP@screen?$AA@ (0000)
00290308 003c:
	??_C@_0DM@CFLNMCBJ@?$CD?$CD?$CD?5WARNING?5camera?5went?5below?5at@ (0000)
00290344 003f:
	??_C@_0DP@KPFLLAEK@global_window_parameters?4fog?4atm@ (0000)
00290384 0039:
	??_C@_0DJ@CNJHFAAL@?$CD?$CD?$CD?5ERROR?5rasterizer_environment@ (0000)
002903C0 009a:
	??_C@_0JK@EAHMKECF@IDirect3DDevice8_SetVertexShader@ (0000)
0029045C 001a:
	??_C@_0BK@IAKEGGKH@screen?9?$DOfar_density?$CB?$DN0?40f?$AA@ (0000)
00290478 0008:
	__real@4008000000000000 (0000)
00290480 0042:
	??_C@_0EC@CKGOBHKE@animation_index?$DO?$DN0?5?$CG?$CG?5animation_@ (0000)
002904C4 0017:
	??_C@_0BH@BCIACAND@?7animation_time?$DN?$CFf?$FL?$CFx?$FN?$AA@ (0000)
002904DC 000a:
	??_C@_09JNBHCJGN@?7t?$DN?$CFf?$FL?$CFx?$FN?$AA@ (0000)
002904E8 000e:
	??_C@_0O@FOFAKLHF@?7phase?$DN?$CFf?$FL?$CFx?$FN?$AA@ (0000)
002904F8 000f:
	??_C@_0P@LFFOAOAL@?7period?$DN?$CFf?$FL?$CFx?$FN?$AA@ (0000)
00290508 000d:
	??_C@_0N@JJBOONHP@?7time?$DN?$CFf?$FL?$CFx?$FN?$AA@ (0000)
00290518 000a:
	??_C@_09GPFGOPA@?7index?$DN?$CFd?$AA@ (0000)
00290528 0041:
	??_C@_0EB@PFJAKMLE@?$CD?$CD?$CD?5ERROR?5fog?5screen?5animation?5i@ (0000)
0029056C 002e:
	??_C@_0CO@OOBJIBPD@bitmap_group?5?$CG?$CG?5bitmap_group?9?$DObi@ (0000)
002905A0 0058:
	??_C@_0FI@CKDGFCNH@?$CD?$CD?$CD?5ERROR?5fog_screen?3?5base?5z?5fai@ (0000)
002905F8 001b:
	??_C@_0BL@EJOACEHM@local_fog_eye_density?$DO0?40f?$AA@ (0000)
00290614 0013:
	??_C@_0BD@GHKLOPND@pass?$DN?$DN0?5?$HM?$HM?5pass?$DN?$DN1?$AA@ (0000)
00290628 0062:
	??_C@_0GC@LABECMII@global_window_parameters?4window_@ (0000)
0029068C 0024:
	??_C@_0CE@NMGKCFDJ@global_window_parameters?4fog?4scr@ (0000)
002906B0 0027:
	??_C@_0CH@FMEAHMPL@local_fog_pass?$DN?$DN0?5?$HM?$HM?5local_fog_p@ (0000)
0030CEFA 0001:
	_data_0030cefa (0000)
00465AD0 0002:
	_bss_00465ad0 (0000)
00465AD4 0004:
	_bss_00465ad4 (0000)
00465AD8 00d0:
	_bss_00465ad8 (0000)
00465BA8 0001:
	_bss_00465ba8 (0000)
00465BA9 0001:
	_bss_00465ba9 (0000)
00465BAC 0008:
	_bss_00465bac (0000)
00465BB4 0030:
	_bss_00465bb4 (0000)
00465BE4 0004:
	_local_fog_eye_density (0000)
00465BE8 0002:
	_local_fog_pass (0000)
00465BF0 0130:
	_bss_00465bf0 (0000)
00465D20 0004:
	_bss_00465d20 (0000)
00465D24 0004:
	_bss_00465d24 (0000)
00465D28 0004:
	_bss_00465d28 (0000)
00465D30 0020:
	_bss_00465d30 (0000)
00465D50 0002:
	_bss_00465d50 (0000)
00465D52 0001:
	_bss_00465d52 (0000)
00465D54 0004:
	_bss_00465d54 (0000)
00465D58 0001:
	_bss_00465d58 (0000)
00465D5C 0004:
	_bss_00465d5c (0000)
00465D60 0004:
	_bss_00465d60 (0000)
00465D64 0001:
	_bss_00465d64 (0000)
*/

/* ---------- headers */

#include "cseries.h"
#include "cseries_windows.h"
#include "errors.h"

// normalize2d was not an inline function when this file was compiled
#define normalize2d normalize2d_inline
#include "real_math.h"
#undef normalize2d
#include "tag_groups.h"
#include "game_globals.h"
#include "bitmaps/bitmap_group.h"
#include "scenario/fog_definitions.h"
#include "shaders/shader_definitions.h"
// rasterizer.h defines global_frame_parameters instead of declaring it
#define global_frame_parameters global_frame_parameters_unused
#include "rasterizer.h"
#undef global_frame_parameters
#include "rasterizer_geometry.h"
#include "shaders.h"
#include "xbox/rasterizer_xbox.h"

/* ---------- constants */

enum
{
	_vertex_shader_model_fog_screen = 5,
	_vertex_shader_environment_fog = 6,
	_vertex_shader_environment_fog_screen = 8,
	_vertex_shader_fog_screen = 38,
};

enum
{
	_fog_screen_no_environment_multipass_bit = 0,
	_fog_screen_no_model_multipass_bit,
	_fog_screen_no_texture_based_falloff_bit,
};

enum
{
	_render_fog_is_water_bit = 0,
	_render_fog_atmosphere_dominant_bit,
};

enum
{
	_render_fog_runtime_use_screen_external_intensity_bit = 0,
};

enum
{
	MAXIMUM_FOG_SCREEN_LAYERS = 4,
	MAXIMUM_OPAQUE_MODEL_GROUPS = 128,
	MAXIMUM_CAMERA_BELOW_FOG_PLANE_WARNINGS = 20,
};

/* ---------- macros */

#define DOT_PRODUCT3D(a, b) ((a).n[0]*(b).n[0] + (a).n[1]*(b).n[1] + (a).n[2]*(b).n[2])

/* ---------- structures */

struct fog_screen_wind
{
	real_vector2d direction;
	real velocity;
	real_vector2d target_direction;
	real target_velocity;
	real time;
	real period;
};

struct fog_screen_window
{
	short base_layer_index;
	word pad;
	real rotation;
	real base_z;
	real_vector2d layer_offsets[MAXIMUM_FOG_SCREEN_LAYERS];
	struct fog_screen_wind wind;
};

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


/* ---------- prototypes */

real normalize2d(real_vector2d *v);

void *shader_get_and_verify_type(struct shader const *shader, short type);
void rasterizer_set_pixel_shader(D3DPIXELSHADERDEF *pixel_shader);
void rasterizer_set_vertex_shader_permutation(short vertex_shader, short vertex_type, short permutation);
boolean rasterizer_set_texture_direct(short stage, long bitmap_group_index, short bitmap_index);
void rasterizer_draw_dynamic_triangles_static_vertices(long dynamic_triangle_buffer_index, long first_triangle_index, long triangle_count, struct vertex_buffer const *vertex_buffer);
long rasterizer_frame_statistics_count_dynamic_vertices(long dynamic_triangle_buffer_index, long first_triangle_index, long triangle_count);
unsigned long real_rgb_color_to_pixel32(real_rgb_color const *color);
unsigned long real_a_rgb_color_to_pixel32(real alpha, real_rgb_color const *color);
unsigned long real_alpha_intensity_to_pixel32(real alpha, real intensity);

void *rasterizer_set_texture(short stage, short type, short usage, long bitmap_group_index, short bitmap_index);
void rasterizer_set_model_skinning(struct render_skinning const *skinning);
short rasterizer_transparent_geometry_get_primary_vertex_type(struct transparent_geometry_group const *group);
void rasterizer_transparent_geometry_group_draw__internal(struct transparent_geometry_group const *group, boolean unknown);
long rasterizer_frame_statistics_count_static_vertices(struct triangle_buffer const *triangle_buffer, struct vertex_buffer const *vertex_buffer);
boolean rasterizer_water_get_visibility_for_window(void);

void rasterizer_environment_fog_screen_wind_get_vector(short window_index, real dt, real_vector3d *wind_vector);

static boolean code_00155860(void);
static void code_00155a60(struct fog_screen const *screen, struct fog_screen_wind *wind);

/* ---------- globals */

extern struct rasterizer_frame_begin_parameters global_frame_parameters;
extern struct rasterizer_window_begin_parameters global_window_parameters;
extern struct game_globals_rasterizer_data *global_rasterizer_data;
extern D3DPIXELSHADERDEF pixel_shader;
extern real_matrix4x3 const *global_identity4x3;

boolean data_0030cefa= TRUE; // first time

static short bss_00465ad0; // local node matrix count
static real_matrix4x3 const *bss_00465ad4; // local node matrices
static real_matrix4x3 bss_00465ad8[MAXIMUM_WINDOWS]; // previous camera matrices
static boolean bss_00465ba8; // multipass models
static boolean bss_00465ba9; // multipass environment
static short bss_00465bac[MAXIMUM_FOG_SCREEN_LAYERS]; // animation indices
static real_rgb_color bss_00465bb4[MAXIMUM_FOG_SCREEN_LAYERS]; // layer colors
static real local_fog_eye_density;
static short local_fog_pass;
static struct fog_screen_window bss_00465bf0[MAXIMUM_WINDOWS]; // windows
static struct transparent_geometry_group *bss_00465d20; // opaque model groups
static long bss_00465d24; // opaque model group count
static boolean bss_00465d28[MAXIMUM_WINDOWS]; // window visible
static __int64 bss_00465d30[MAXIMUM_WINDOWS]; // window frame index
static short bss_00465d50; // camera below fog plane warning count
static boolean bss_00465d52; // animation index error reported
static struct rasterizer_model_begin_parameters const *bss_00465d54; // model parameters
static boolean bss_00465d58; // model nodes valid
static struct render_lighting const *bss_00465d5c; // lighting
static struct render_animation const *bss_00465d60; // animation
static boolean bss_00465d64; // too many opaque models reported

/* ---------- private code */

__inline real_vector4d *set_real_vector4d(
	real_vector4d *v,
	real i,
	real j,
	real k,
	real l)
{
	v->i= i;
	v->j= j;
	v->k= k;
	v->l= l;

	return v;
}

__inline boolean local_random_boolean(
	void)
{
	return seed_random(get_global_local_random_seed_address())>0x8000;
}

static boolean code_00155860(
	void)
{
	short window_index= global_window_parameters.window_index;

	if (window_index>=0 && window_index<MAXIMUM_WINDOWS)
	{
		bss_00465d28[window_index]= FALSE;

		if (rasterizer_globals.frame_index!=bss_00465d30[window_index])
		{
			struct fog_screen const *screen;

			match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment_fog.c", 92, global_window_parameters.fog.planar_maximum_depth!=0.0f);

			if (!rasterizer_debug_options.drawing_mode &&
				rasterizer_debug_options.draw_environment_fog_screen &&
				global_window_parameters.rasterizer_target==_rasterizer_target_render_primary &&
				(screen= global_window_parameters.fog.screen)!=NULL &&
				screen->layer_count>0 &&
				screen->map.index!=NONE &&
				screen->far_distance!=0.f &&
				screen->far_density!=0.f &&
				(!TEST_FLAG(global_window_parameters.fog.runtime_flags, _render_fog_runtime_use_screen_external_intensity_bit) || global_window_parameters.fog.screen_external_intensity>0.f))
			{
				real planar_maximum_depth= global_window_parameters.fog.planar_maximum_depth;
				real eye_distance_to_fog_plane= DOT_PRODUCT3D(global_window_parameters.camera.position, global_window_parameters.fog.plane.n) - global_window_parameters.fog.plane.d;
				real start_distance= screen->start_distance_from_fog_plane;

				if (start_distance==-planar_maximum_depth)
				{
					start_distance= _real_epsilon - planar_maximum_depth;
				}

				if (TEST_FLAG(global_window_parameters.fog.runtime_flags, _render_fog_runtime_use_screen_external_intensity_bit))
				{
					local_fog_eye_density= global_window_parameters.fog.screen_external_intensity;
				}
				else
				{
					real density= (eye_distance_to_fog_plane - start_distance)/(-planar_maximum_depth - start_distance);
					local_fog_eye_density= PIN(density, 0.f, 1.f);
				}

				if (local_fog_eye_density>0.f)
				{
					bss_00465d28[window_index]= TRUE;
				}
			}
		}

		return bss_00465d28[window_index];
	}

	return FALSE;
}

// TODO: stack slots of perpendicular_weight and perpendicular_scale are swapped
static void code_00155a60(
	struct fog_screen const *screen,
	struct fog_screen_wind *wind)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment_fog.c", 163, screen);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment_fog.c", 164, wind);

	if (screen->wind_velocity_upper_bound>0.f)
	{
		scale_vector2d(&wind->direction, 1.f - screen->wind_acceleration_weight, &wind->direction);
		point_from_line2d((real_point2d *)&wind->direction, &wind->target_direction, screen->wind_acceleration_weight, (real_point2d *)&wind->direction);
		if (normalize2d(&wind->direction)==0.f)
		{
			set_real_vector2d(&wind->direction, 1.f, 0.f);
		}

		scalars_interpolate(wind->velocity, wind->target_velocity, screen->wind_acceleration_weight, &wind->velocity);

		if (global_frame_parameters.game_time_sec - wind->time>=wind->period)
		{
			real_vector2d perpendicular;
			real perpendicular_scale;
			real perpendicular_weight= real_local_random();

			perpendicular_weight= (real)pow(perpendicular_weight, 1.f - screen->wind_perpendicular_weight);
			perpendicular_scale= local_random_boolean() ? -1.f : 1.f;

			perpendicular2d(&wind->direction, &perpendicular);
			scale_vector2d(&perpendicular, perpendicular_scale*perpendicular_weight, &perpendicular);
			point_from_line2d((real_point2d *)&perpendicular, &wind->direction, 1.f - perpendicular_weight, (real_point2d *)&wind->target_direction);
			if (normalize2d(&wind->target_direction)==0.f)
			{
				set_real_vector2d(&wind->target_direction, 1.f, 0.f);
			}

			wind->target_velocity= real_local_random_range(screen->wind_velocity_lower_bound, screen->wind_velocity_upper_bound);
			wind->time= global_frame_parameters.game_time_sec;
			wind->period= real_local_random_range(screen->wind_period_lower_bound, screen->wind_period_upper_bound);
		}
	}

	return;
}

/* ---------- public code */

boolean rasterizer_environment_fog_screen_initialize(
	void)
{
	boolean success= TRUE;

	bss_00465d20= match_malloc("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment_fog.c", 248, MAXIMUM_OPAQUE_MODEL_GROUPS*sizeof(struct transparent_geometry_group));
	bss_00465d24= 0;

	if (!bss_00465d20)
	{
		error(_error_silent, "### ERROR failed to allocate opaque model geometry buffer for environment fog screen");
		success= FALSE;
	}

	return success;
}

void rasterizer_environment_fog_screen_window_begin(
	void)
{
	bss_00465d24 = 0;

	return;
}

void rasterizer_environment_fog_screen_window_end(
	void)
{
	return;
}

void rasterizer_environment_fog_screen_dispose(
	void)
{
	if (bss_00465d20)
	{
		match_free("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment_fog.c", 279, bss_00465d20);
	}

	return;
}

void _rasterizer_environment_fog_begin(
	void)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment_fog.c", 290, global_window_parameters.fog.atmospheric_maximum_distance>0.0f);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment_fog.c", 291, global_window_parameters.fog.planar_maximum_distance>0.0f);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment_fog.c", 292, global_window_parameters.fog.planar_maximum_depth>0.0f);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment_fog.c", 293, global_d3d_device);

	rasterizer_profile_begin(_rasterizer_profile_environment_fog);

	if (!rasterizer_debug_options.drawing_mode && rasterizer_debug_options.draw_environment_fog)
	{
		real eye_distance_to_fog_plane= DOT_PRODUCT3D(global_window_parameters.camera.position, global_window_parameters.fog.plane.n) - global_window_parameters.fog.plane.d;
		real atmospheric_eye_density= PIN(eye_distance_to_fog_plane/global_window_parameters.fog.atmospheric_maximum_distance, 0.f, 1.f);
		real planar_eye_density= PIN(-eye_distance_to_fog_plane/global_window_parameters.fog.planar_maximum_depth, 0.f, 1.f);

		if (TEST_FLAG(global_window_parameters.fog.fog_definition_flags, _render_fog_atmosphere_dominant_bit))
		{
			atmospheric_eye_density= 1.f;

			if (eye_distance_to_fog_plane<-0.3f && bss_00465d50<MAXIMUM_CAMERA_BELOW_FOG_PLANE_WARNINGS)
			{
				error(_error_silent, "### WARNING camera went below atmosphere-dominant fog plane");
				bss_00465d50++;
			}
		}

		rasterizer_set_texture_direct(0, global_rasterizer_data->atmospheric_fog_density.index, 0);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);
		rasterizer_set_texture_direct(1, global_rasterizer_data->planar_fog_density.index, 0);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);

		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_CCW);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED|D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_BLUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHABLENDENABLE, TRUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_SRCBLEND, D3DBLEND_ONE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_BLENDOP, D3DBLENDOP_ADD);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHATESTENABLE, TRUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHAREF, 0);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZENABLE, D3DZB_TRUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZFUNC, D3DCMP_EQUAL);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZWRITEENABLE, FALSE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZBIAS, 0);

		memset(&pixel_shader, 0, sizeof(pixel_shader));
		pixel_shader.PSTextureModes= 0x21;
		pixel_shader.PSCombinerCount= 0x11002;
		pixel_shader.PSConstant0[0]= real_alpha_intensity_to_pixel32(global_window_parameters.fog.atmospheric_maximum_density*atmospheric_eye_density, global_window_parameters.fog.atmospheric_maximum_density);
		pixel_shader.PSConstant1[0]= real_alpha_intensity_to_pixel32(global_window_parameters.fog.planar_maximum_density*planar_eye_density, (1.f - planar_eye_density)*global_window_parameters.fog.planar_maximum_density);
		pixel_shader.PSAlphaInputs[0]= 0x2191209;
		pixel_shader.PSAlphaOutputs[0]= 0xc00;
		pixel_shader.PSRGBInputs[0]= 0x11180118;
		pixel_shader.PSRGBOutputs[0]= 0x48;
		pixel_shader.PSConstant0[1]= real_a_rgb_color_to_pixel32(atmospheric_eye_density, &global_window_parameters.fog.atmospheric_color);
		pixel_shader.PSConstant1[1]= real_rgb_color_to_pixel32(&global_window_parameters.fog.planar_color);
		pixel_shader.PSAlphaInputs[1]= 0x283c311c;
		pixel_shader.PSAlphaOutputs[1]= 0xcd;
		pixel_shader.PSRGBInputs[1]= 0x108021c;
		pixel_shader.PSRGBOutputs[1]= 0xcd;
		pixel_shader.PSFinalCombinerInputsABCD= 0xc3d000f;
		pixel_shader.PSFinalCombinerInputsEFG= 0xd243c00;
		rasterizer_set_pixel_shader(&pixel_shader);
	}

	return;
}

void _rasterizer_environment_fog_draw(
	struct shader const *shader,
	short shader_permutation_index,
	long dynamic_triangle_buffer_index,
	long first_triangle_index,
	long triangle_count,
	struct vertex_buffer const *vertex_buffer)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment_fog.c", 423, global_d3d_device);

	if (!rasterizer_debug_options.drawing_mode && rasterizer_debug_options.draw_environment_fog)
	{
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment_fog.c", 430, shader);
		shader_get_and_verify_type(shader, _shader_type_environment);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment_fog.c", 435, vertex_buffer);

		rasterizer_set_vertex_shader_permutation(_vertex_shader_environment_fog, vertex_buffer->type, shader_get_vertex_shader_permutation(shader));
		rasterizer_draw_dynamic_triangles_static_vertices(dynamic_triangle_buffer_index, first_triangle_index, triangle_count, vertex_buffer);

		if (rasterizer_debug_options.statistics_mode==_rasterizer_statistics_mode_geometry)
		{
			rasterizer_frame_statistics.fog.primitives++;
			rasterizer_frame_statistics.fog.triangles+= triangle_count;
			rasterizer_frame_statistics.fog.vertices+= rasterizer_frame_statistics_count_dynamic_vertices(dynamic_triangle_buffer_index, first_triangle_index, triangle_count);
		}
	}

	return;
}

void _rasterizer_environment_fog_end(
	void)
{
	rasterizer_profile_end(_rasterizer_profile_environment_fog);

	return;
}

void _rasterizer_environment_fog_screen_wind_get_vector(
	short window_index,
	real dt,
	real_vector3d *wind_vector)
{
	struct fog_screen_wind *wind= &bss_00465bf0[window_index].wind;

	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment_fog.c", 484, window_index>=0 && window_index<MAXIMUM_WINDOWS);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment_fog.c", 485, wind_vector);

	wind_vector->i= wind->velocity*wind->direction.i*dt;
	wind_vector->j= wind->direction.j*wind->velocity*dt;
	wind_vector->k= 0.f;

	return;
}

// TODO: stack slot and esi/edi register allocation differences
void _rasterizer_environment_fog_screen_begin(
	short pass)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment_fog.c", 499, pass==0 || pass==1);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment_fog.c", 500, global_d3d_device);

	local_fog_pass= pass;
	if (!pass)
	{
		rasterizer_profile_begin(_rasterizer_profile_environment_fog_screen);
	}

	if (code_00155860())
	{
		struct fog_screen_window *window= &bss_00465bf0[global_window_parameters.window_index];
		struct fog_screen const *screen= global_window_parameters.fog.screen;
		boolean success;

		match_vassert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment_fog.c", 514, local_fog_eye_density>0.0f, "local_fog_eye_density>0.0f");

		if (!pass)
		{
			real_matrix4x3 *previous_world_to_view= &bss_00465ad8[global_window_parameters.window_index];
			real_matrix4x3 matrix;
			real_vector4d vsh_constants__texanim[VSH_CONSTANTS__TEXANIM_COUNT];
			real_vector4d vsh_constants__screenproj[VSH_CONSTANTS__SCREENPROJ_COUNT];
			real layer_spacing, one_over_depth_range, aspect_ratio, zoom, cosine, sine;
			short layer_index;

			{
				real_matrix4x3 wind_matrix= *global_identity4x3;
				real_vector3d wind_vector;

				if (data_0030cefa)
				{
					short window_index;

					tag_get(BITMAP_GROUP_TAG, screen->map.index);
					for (window_index= 0; window_index<MAXIMUM_WINDOWS; window_index++)
					{
						memset(&bss_00465bf0[window_index], 0, sizeof(struct fog_screen_window));
						for (layer_index= 0; layer_index<screen->layer_count; layer_index++)
						{
							real j= real_local_random();
							set_real_vector2d(&bss_00465bf0[window_index].layer_offsets[layer_index], real_local_random(), j);
						}
						memcpy(&bss_00465ad8[window_index], &global_window_parameters.camera, sizeof(real_matrix4x3));
					}
					data_0030cefa= FALSE;
				}

				code_00155a60(screen, &window->wind);
				rasterizer_environment_fog_screen_wind_get_vector(global_window_parameters.window_index, global_frame_parameters.dt, &wind_vector);
				wind_matrix.position.x= wind_vector.i;
				wind_matrix.position.y= wind_vector.j;

				matrix4x3_inverse(previous_world_to_view, &matrix);
				matrix4x3_multiply(&wind_matrix, &matrix, &matrix);
				matrix4x3_multiply(&global_window_parameters.frustum.world_to_view, &matrix, &matrix);
				memcpy(&bss_00465ad8[global_window_parameters.window_index], &global_window_parameters.frustum.world_to_view, sizeof(real_matrix4x3));
			}

			layer_spacing= (screen->far_distance - screen->near_distance)/screen->layer_count;
			one_over_depth_range= 1.f/(screen->far_distance - screen->near_distance);

			{
				short height= global_window_parameters.camera.viewport_bounds.y1 - global_window_parameters.camera.viewport_bounds.y0;
				short width= global_window_parameters.camera.viewport_bounds.x1 - global_window_parameters.camera.viewport_bounds.x0;
				real one_over_width, one_over_height;
				real_vector3d forward;

				aspect_ratio= (real)height/width;
				zoom= screen->map_scale*0.5f/((real)tan(global_window_parameters.camera.vertical_field_of_view*0.5f)*screen->far_distance*aspect_ratio);

				one_over_width= 1.f/width;
				set_real_vector4d(&vsh_constants__screenproj[0], 2.f*one_over_width, 0.f, 0.f, -1.f - one_over_width);
				one_over_height= 1.f/height;
				set_real_vector4d(&vsh_constants__screenproj[1], 0.f, -2.f*one_over_height, 0.f, one_over_height + 1.f);
				set_real_vector4d(&vsh_constants__screenproj[2], 0.f, 0.f, 0.f, 0.5f);
				set_real_vector4d(&vsh_constants__screenproj[3], 0.f, 0.f, 0.f, 1.f);
				set_real_vector4d(&vsh_constants__screenproj[4], 0.f, 0.f, 0.f, 1.f);

				set_real_vector3d(&forward, 1.f, 0.f, 0.f);
				matrix4x3_transform_normal(&matrix, &forward, &forward);
				window->rotation-= -(real)atan2(forward.j, forward.i)*screen->rotation_multiplier;
				cosine= (real)cos(window->rotation);
				sine= (real)sin(window->rotation);
			}

			if (screen->far_distance - screen->near_distance>0.01f)
			{
				short offset;

				window->base_z-= screen->zoom_multiplier/layer_spacing*matrix.position.z;
				offset= (short)fast_ftol((real)floor(window->base_z));
				if (offset>0)
				{
					real j= real_local_random();
					set_real_vector2d(&window->layer_offsets[(short)((word)(window->base_layer_index - 1)%screen->layer_count)], real_local_random(), j);
				}
				else if (offset<0)
				{
					real j= real_local_random();
					set_real_vector2d(&window->layer_offsets[window->base_layer_index], real_local_random(), j);
				}

				window->base_layer_index= (word)(window->base_layer_index - offset)%screen->layer_count;
				window->base_z-= offset;

				if (window->base_z<0.f || window->base_z>=1.f)
				{
					error(_error_silent, "### ERROR fog_screen: base z failure (near=%f, far=%f, z=%f, offset=%d) -- tell Bernie!", screen->near_distance, screen->far_distance, window->base_z, offset);
					return;
				}
			}

			{
				real animation_times[MAXIMUM_FOG_SCREEN_LAYERS];

				for (layer_index= 0; layer_index<screen->layer_count; layer_index++)
				{
					real phases[MAXIMUM_FOG_SCREEN_LAYERS]= { 0.f, 0.7135f, 0.3422f, 0.5798f };
					struct bitmap_group const *bitmap_group= tag_get(BITMAP_GROUP_TAG, screen->map.index);

					match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment_fog.c", 653, bitmap_group && bitmap_group->bitmaps.count>0);

					if (screen->animation_period>0.f)
					{
						real t= bitmap_group->bitmaps.count*phases[layer_index] + global_frame_parameters.game_time_sec/screen->animation_period;
						real animation_time;
						short animation_index;

						animation_times[layer_index]= animation_time= PIN(t - floor(t), 0.f, 1.f);
						animation_index= (short)(fast_ftol((real)floor(t))%bitmap_group->bitmaps.count);
						if (animation_index<0)
						{
							if (!bss_00465d52)
							{
								error(_error_silent, "### ERROR fog screen animation index is invalid -- tell Bernie!!");
								error(_error_silent, "\tindex=%d", animation_index);
								error(_error_silent, "\ttime=%f[%x]", global_frame_parameters.game_time_sec, *(long *)&global_frame_parameters.game_time_sec);
								error(_error_silent, "\tperiod=%f[%x]", screen->animation_period, *(long *)&screen->animation_period);
								error(_error_silent, "\tphase=%f[%x]", phases[layer_index], *(long *)&phases[layer_index]);
								error(_error_silent, "\tt=%f[%x]", t, *(long *)&t);
								error(_error_silent, "\tanimation_time=%f[%x]", animation_time, *(long *)&animation_times[layer_index]);
								bss_00465d52= TRUE;
							}
							animation_index= 0;
						}

						match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment_fog.c", 682, animation_index>=0 && animation_index<bitmap_group->bitmaps.count);
						bss_00465bac[layer_index]= animation_index;
					}
					else
					{
						animation_times[layer_index]= 0.f;
						bss_00465bac[layer_index]= layer_index%bitmap_group->bitmaps.count;
					}
				}

				for (layer_index= 0; layer_index<screen->layer_count; layer_index++)
				{
					short offset_index= (short)((word)(window->base_layer_index + layer_index)%screen->layer_count);
					real z= (layer_index + window->base_z)*layer_spacing + screen->near_distance;
					real t= (z - screen->near_distance)*one_over_depth_range;
					real density= (real)pow(1.0 - pow(fabs(t + t - 1.f), 3.0), 2.0)*(local_fog_eye_density*screen->far_density);
					real scale= screen->map_scale/screen->far_distance*z;
					real_point3d point;
					real_vector2d *offset= &window->layer_offsets[offset_index];
					real_rgb_color *color= &bss_00465bb4[layer_index];
					real scale_cosine, scale_sine;

					set_real_point3d(&point, 0.f, 0.f, -z);
					matrix4x3_transform_point(&matrix, &point, &point);
					offset->i-= (point.y*sine + point.x*cosine)*screen->strafing_multiplier*zoom;
					offset->j-= (point.y*cosine - point.x*sine)*screen->strafing_multiplier*zoom;

					if (screen->animation_period!=0.f)
					{
						real animation_time= animation_times[offset_index];
						real one_minus_animation_time= 1.f - animation_time;

						color->red= one_minus_animation_time*one_minus_animation_time*density;
						color->green= 2.f*animation_time*one_minus_animation_time*density;
						color->blue= animation_time*animation_time*density;
					}
					else
					{
						color->red= 0.f;
						color->green= density;
						color->blue= 0.f;
					}

					scale_cosine= scale*cosine;
					scale_sine= scale*sine;
					set_real_vector4d(&vsh_constants__texanim[2*layer_index], scale_cosine*0.5f, scale_sine*aspect_ratio*0.5f, 0.f, offset->i);
					set_real_vector4d(&vsh_constants__texanim[2*layer_index+1], scale_sine*-0.5f, scale_cosine*aspect_ratio*0.5f, 0.f, offset->j);
				}
			}

			IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, VSH_CONSTANTS__TEXANIM_OFFSET, vsh_constants__texanim, VSH_CONSTANTS__TEXANIM_COUNT);
			IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, VSH_CONSTANTS__SCREENPROJ_OFFSET, vsh_constants__screenproj, VSH_CONSTANTS__SCREENPROJ_COUNT);

			if (screen->near_density==screen->far_density)
			{
				bss_00465ba9= FALSE;
				bss_00465ba8= FALSE;
				return;
			}

			bss_00465ba9= !TEST_FLAG(global_window_parameters.fog.screen->flags, _fog_screen_no_environment_multipass_bit);
			bss_00465ba8= !TEST_FLAG(global_window_parameters.fog.screen->flags, _fog_screen_no_model_multipass_bit) && bss_00465d24>0;
		}

		if (bss_00465ba9 || bss_00465ba8)
		{
			boolean clear_z= !pass &&
				(!TEST_FLAG(screen->flags, _fog_screen_no_environment_multipass_bit) || !TEST_FLAG(screen->flags, _fog_screen_no_model_multipass_bit)) &&
				(TEST_FLAG(screen->flags, _fog_screen_no_environment_multipass_bit) ||
				(TEST_FLAG(screen->flags, _fog_screen_no_model_multipass_bit) && bss_00465d24>0) ||
				(rasterizer_water_get_visibility_for_window() && rasterizer_debug_options.draw_water));

			IDirect3DDevice8_Clear(global_d3d_device, 0, NULL, (clear_z ? D3DCLEAR_ZBUFFER : 0)|D3DCLEAR_TARGET_A, 0, 1.f, 0);
			success= TRUE;

			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_CCW);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_ALPHA);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHABLENDENABLE, FALSE);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHATESTENABLE, FALSE);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZENABLE, D3DZB_TRUE);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZFUNC, pass ? D3DCMP_EQUAL : D3DCMP_LESSEQUAL);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZWRITEENABLE, !pass);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZBIAS, 0);

			if (!pass)
			{
				real one_over_depth_range= 1.f/(screen->far_distance - screen->near_distance);
				real_vector4d vsh_constants__texscale_0[1];
				real_vector4d vsh_constants__texscale_1[VSH_CONSTANTS__TEXSCALE_COUNT-1];

				set_real_vector4d(&vsh_constants__texscale_1[0], 0.f, 0.f, 0.f, 0.f);
				set_real_vector4d(&vsh_constants__texscale_1[1], 0.f, 0.f, 0.f, 0.f);
				set_real_vector4d(&vsh_constants__texscale_0[0],
					global_window_parameters.camera.forward.i*one_over_depth_range,
					global_window_parameters.camera.forward.j*one_over_depth_range,
					global_window_parameters.camera.forward.k*one_over_depth_range,
					-(DOT_PRODUCT3D(global_window_parameters.camera.position, global_window_parameters.camera.forward) + screen->near_distance)*one_over_depth_range);
				D3DCALL(success, IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, VSH_CONSTANTS__TEXSCALE_OFFSET, vsh_constants__texscale_0, 1));
			}

			memset(&pixel_shader, 0, sizeof(pixel_shader));
			if (TEST_FLAG(global_window_parameters.fog.screen->flags, _fog_screen_no_texture_based_falloff_bit))
			{
				pixel_shader.PSCombinerCount= PS_COMBINERCOUNT(1, 0);
				pixel_shader.PSFinalCombinerInputsEFG= 0x3300;
			}
			else
			{
				rasterizer_set_texture_direct(0, global_rasterizer_data->planar_fog_density.index, 0);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);

				match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment_fog.c", 856, screen->far_density!=0.0f);

				pixel_shader.PSTextureModes= PS_TEXTUREMODES(PS_TEXTUREMODES_PROJECT2D, PS_TEXTUREMODES_NONE, PS_TEXTUREMODES_NONE, PS_TEXTUREMODES_NONE);
				pixel_shader.PSCombinerCount= PS_COMBINERCOUNT(1, 0);
				pixel_shader.PSConstant0[0]= real_alpha_to_pixel32(screen->near_density/screen->far_density);
				pixel_shader.PSAlphaInputs[0]= 0x28110820;
				pixel_shader.PSAlphaOutputs[0]= 0xc00;
				pixel_shader.PSFinalCombinerInputsEFG= 0x3c00;
			}
			rasterizer_set_pixel_shader(&pixel_shader);

			if (bss_00465ba8)
			{
				short group_index;

				for (group_index= 0; group_index<bss_00465d24; group_index++)
				{
					struct transparent_geometry_group *group= &bss_00465d20[group_index];
					struct render_skinning skinning;

					switch (group->shader->base.type)
					{
					case _shader_type_model:
						{
							struct shader_model const *shader_model= shader_get_and_verify_type(group->shader, _shader_type_model);

							if (!TEST_FLAG(shader_model->model.flags, _shader_model_not_alpha_tested_bit))
							{
								real_vector4d vsh_constants__texscale_1[VSH_CONSTANTS__TEXSCALE_COUNT-1];

								IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_PSTEXTUREMODES, PS_TEXTUREMODES(PS_TEXTUREMODES_PROJECT2D, PS_TEXTUREMODES_PROJECT2D, PS_TEXTUREMODES_NONE, PS_TEXTUREMODES_NONE));
								IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_ALPHAKILL, D3DTALPHAKILL_ENABLE);
								rasterizer_set_texture(1, 0, 1, shader_model->model.base_map.index, group->shader_permutation_index);
								IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_ADDRESSU, D3DTADDRESS_WRAP);
								IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP);
								IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
								IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
								IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);

								set_real_vector4d(&vsh_constants__texscale_1[0], shader_model->model.map_scale.i*group->model_base_map_scale.i, 0.f, 0.f, 0.f);
								set_real_vector4d(&vsh_constants__texscale_1[1], 0.f, shader_model->model.map_scale.j*group->model_base_map_scale.j, 0.f, 0.f);
								D3DCALL(success, IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, VSH_CONSTANTS__TEXSCALE_OFFSET+1, vsh_constants__texscale_1, VSH_CONSTANTS__TEXSCALE_COUNT-1));
								break;
							}
						}
					case _shader_type_environment:
					case _shader_type_transparent_glass:
						IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_PSTEXTUREMODES, PS_TEXTUREMODES(PS_TEXTUREMODES_PROJECT2D, PS_TEXTUREMODES_NONE, PS_TEXTUREMODES_NONE, PS_TEXTUREMODES_NONE));
						IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_ALPHAKILL, D3DTALPHAKILL_DISABLE);
						break;
					}

					rasterizer_set_vertex_shader_permutation(_vertex_shader_model_fog_screen, rasterizer_transparent_geometry_get_primary_vertex_type(group), 0);

					if (group->node_matrices && group->node_matrix_count)
					{
						skinning.node_matrix_count= group->node_matrix_count;
						skinning.node_matrices= group->node_matrices;
					}
					else
					{
						skinning.node_matrix_count= 1;
						skinning.node_matrices= global_identity4x3;
					}
					rasterizer_set_model_skinning(&skinning);

					if (success)
					{
						rasterizer_transparent_geometry_group_draw__internal(group, FALSE);

						if (rasterizer_debug_options.statistics_mode==_rasterizer_statistics_mode_geometry)
						{
							rasterizer_frame_statistics.model_fog_screen.primitives++;
							rasterizer_frame_statistics.model_fog_screen.triangles+= group->triangle_count;
							rasterizer_frame_statistics.model_fog_screen.vertices+= rasterizer_frame_statistics_count_static_vertices(group->triangle_buffer, group->vertex_buffers);
						}
					}
				}

				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_ALPHAKILL, D3DTALPHAKILL_DISABLE);

				if (!success)
				{
					error(_error_silent, "### ERROR rasterizer_environment_fog_screen_begin failed");
				}
			}
		}
	}

	return;
}

void _rasterizer_environment_fog_screen_draw(
	struct shader const *shader,
	short shader_permutation_index,
	long dynamic_triangle_buffer_index,
	long first_triangle_index,
	long triangle_count,
	struct vertex_buffer const *vertex_buffer)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment_fog.c", 988, global_d3d_device);

	if (code_00155860())
	{

		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment_fog.c", 992, local_fog_pass==0 || local_fog_pass==1);

		if (bss_00465ba9)
		{
			match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment_fog.c", 996, global_window_parameters.fog.screen);
			match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment_fog.c", 997, global_window_parameters.window_index>=0 && global_window_parameters.window_index<MAXIMUM_WINDOWS);

			rasterizer_set_vertex_shader_permutation(_vertex_shader_environment_fog_screen, vertex_buffer->type, shader_get_vertex_shader_permutation(shader));
			rasterizer_draw_dynamic_triangles_static_vertices(dynamic_triangle_buffer_index, first_triangle_index, triangle_count, vertex_buffer);

			if (rasterizer_debug_options.statistics_mode==_rasterizer_statistics_mode_geometry)
			{
				rasterizer_frame_statistics.fog_screen.primitives++;
				rasterizer_frame_statistics.fog_screen.triangles+= triangle_count;
				rasterizer_frame_statistics.fog_screen.vertices+= rasterizer_frame_statistics_count_dynamic_vertices(dynamic_triangle_buffer_index, first_triangle_index, triangle_count);
			}
		}
	}

	return;
}

void _rasterizer_environment_fog_screen_end(
	void)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment_fog.c", 1036, global_d3d_device);

	if (code_00155860())
	{
		struct fog_screen const *screen= global_window_parameters.fog.screen;
		struct fog_screen_window *window= &bss_00465bf0[global_window_parameters.window_index];
		boolean multipass= bss_00465ba9 || bss_00465ba8;
		short stage;

		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment_fog.c", 1045, local_fog_pass==0 || local_fog_pass==1);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment_fog.c", 1047, global_window_parameters.fog.screen);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment_fog.c", 1048, global_window_parameters.window_index>=0 && global_window_parameters.window_index<MAXIMUM_WINDOWS);

		for (stage= 0; stage<screen->layer_count; stage++)
		{
			rasterizer_set_texture_direct(stage, screen->map.index, bss_00465bac[(short)((word)(stage + window->base_layer_index)%screen->layer_count)]);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, stage, D3DTSS_ADDRESSU, D3DTADDRESS_WRAP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, stage, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, stage, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, stage, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, stage, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);
		}

		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_CCW);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_COLORWRITEENABLE, (!local_fog_pass && multipass) ? D3DCOLORWRITEENABLE_ALPHA : D3DCOLORWRITEENABLE_RED|D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_BLUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHABLENDENABLE, TRUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_SRCBLEND, multipass ? D3DBLEND_INVDESTALPHA : D3DBLEND_ONE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_DESTBLEND, multipass ? D3DBLEND_ONE : D3DBLEND_SRCALPHA);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_BLENDOP, D3DBLENDOP_ADD);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHATESTENABLE, FALSE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZENABLE, D3DZB_FALSE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZBIAS, 0);

		rasterizer_set_vertex_shader_permutation(_vertex_shader_fog_screen, 8, 0);

		memset(&pixel_shader, 0, sizeof(pixel_shader));
		pixel_shader.PSTextureModes= PS_TEXTUREMODES(
			PS_TEXTUREMODES_PROJECT2D,
			screen->layer_count>1 ? PS_TEXTUREMODES_PROJECT2D : PS_TEXTUREMODES_NONE,
			screen->layer_count>2 ? PS_TEXTUREMODES_PROJECT2D : PS_TEXTUREMODES_NONE,
			screen->layer_count>3 ? PS_TEXTUREMODES_PROJECT2D : PS_TEXTUREMODES_NONE);
		pixel_shader.PSCombinerCount= PS_COMBINERCOUNT(4, PS_COMBINERCOUNT_UNIQUE_C0|PS_COMBINERCOUNT_UNIQUE_C1);

		pixel_shader.PSConstant0[0]= real_rgb_color_to_pixel32(&bss_00465bb4[0]);
		pixel_shader.PSConstant1[0]= real_rgb_color_to_pixel32(&bss_00465bb4[1]);
		pixel_shader.PSRGBInputs[0]= 0x8010902;
		pixel_shader.PSRGBOutputs[0]= 0x3089;

		pixel_shader.PSConstant0[1]= real_rgb_color_to_pixel32(&bss_00465bb4[2]);
		pixel_shader.PSConstant1[1]= real_rgb_color_to_pixel32(&bss_00465bb4[3]);
		pixel_shader.PSAlphaInputs[1]= PS_COMBINERINPUTS(0x28, screen->layer_count>1 ? 0x29 : 0x20, 0, 0);
		pixel_shader.PSAlphaOutputs[1]= 0xc0;
		pixel_shader.PSRGBInputs[1]= 0xa010b02;
		pixel_shader.PSRGBOutputs[1]= 0x30ab;

		pixel_shader.PSAlphaInputs[2]= PS_COMBINERINPUTS(screen->layer_count>2 ? 0x2a : 0x20, screen->layer_count>3 ? 0x2b : 0x20, 0, 0);
		pixel_shader.PSAlphaOutputs[2]= 0xd0;
		pixel_shader.PSRGBInputs[2]= PS_COMBINERINPUTS(screen->layer_count>2 ? 0x2a : 0x20, screen->layer_count>3 ? 0x0b : 0, screen->layer_count>2 ? 0x0a : 0, 0x20);
		pixel_shader.PSRGBOutputs[2]= 0xc00;

		pixel_shader.PSAlphaInputs[3]= 0x1c1d0000;
		pixel_shader.PSAlphaOutputs[3]= 0xc0;
		pixel_shader.PSRGBInputs[3]= PS_COMBINERINPUTS(screen->layer_count>1 ? 0x29 : 0x20, 0x0c, screen->layer_count>1 ? 0x09 : 0, 0x20);
		pixel_shader.PSRGBOutputs[3]= 0xc00;

		pixel_shader.PSFinalCombinerConstant0= screen->color ? screen->color : real_rgb_color_to_pixel32(&global_window_parameters.fog.planar_color);
		pixel_shader.PSFinalCombinerInputsABCD= 0x8010f00;
		pixel_shader.PSFinalCombinerInputsEFG= 0xc011c00;
		rasterizer_set_pixel_shader(&pixel_shader);

		IDirect3DDevice8_Begin(global_d3d_device, D3DPT_TRIANGLEFAN);
		IDirect3DDevice8_SetVertexData2s(global_d3d_device, D3DVSDE_SPECULAR, -1, 1);
		IDirect3DDevice8_SetVertexData2s(global_d3d_device, D3DVSDE_POSITION, -1, 1);
		IDirect3DDevice8_SetVertexData2s(global_d3d_device, D3DVSDE_SPECULAR, 1, 1);
		IDirect3DDevice8_SetVertexData2s(global_d3d_device, D3DVSDE_POSITION, 1, 1);
		IDirect3DDevice8_SetVertexData2s(global_d3d_device, D3DVSDE_SPECULAR, 1, -1);
		IDirect3DDevice8_SetVertexData2s(global_d3d_device, D3DVSDE_POSITION, 1, -1);
		IDirect3DDevice8_SetVertexData2s(global_d3d_device, D3DVSDE_SPECULAR, -1, -1);
		IDirect3DDevice8_SetVertexData2s(global_d3d_device, D3DVSDE_POSITION, -1, -1);
		IDirect3DDevice8_End(global_d3d_device);

		if (!local_fog_pass && multipass)
		{
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED|D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_BLUE);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_SRCBLEND, D3DBLEND_INVDESTALPHA);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_DESTBLEND, D3DBLEND_ONE);

			memset(&pixel_shader, 0, sizeof(pixel_shader));
			pixel_shader.PSCombinerCount= PS_COMBINERCOUNT(1, 0);
			rasterizer_set_pixel_shader(&pixel_shader);

			IDirect3DDevice8_Begin(global_d3d_device, D3DPT_TRIANGLEFAN);
			IDirect3DDevice8_SetVertexData2s(global_d3d_device, D3DVSDE_SPECULAR, -1, 1);
			IDirect3DDevice8_SetVertexData2s(global_d3d_device, D3DVSDE_POSITION, -1, 1);
			IDirect3DDevice8_SetVertexData2s(global_d3d_device, D3DVSDE_SPECULAR, 1, 1);
			IDirect3DDevice8_SetVertexData2s(global_d3d_device, D3DVSDE_POSITION, 1, 1);
			IDirect3DDevice8_SetVertexData2s(global_d3d_device, D3DVSDE_SPECULAR, 1, -1);
			IDirect3DDevice8_SetVertexData2s(global_d3d_device, D3DVSDE_POSITION, 1, -1);
			IDirect3DDevice8_SetVertexData2s(global_d3d_device, D3DVSDE_SPECULAR, -1, -1);
			IDirect3DDevice8_SetVertexData2s(global_d3d_device, D3DVSDE_POSITION, -1, -1);
			IDirect3DDevice8_End(global_d3d_device);
		}
	}

	if (local_fog_pass)
	{
		rasterizer_profile_end(_rasterizer_profile_environment_fog_screen);
	}

	return;
}

boolean rasterizer_environment_fog_screen_model_begin(
	struct rasterizer_model_begin_parameters const *parameters)
{
	boolean result= FALSE;

	if (rasterizer_debug_options.draw_environment_fog_screen &&
		!rasterizer_debug_options.drawing_mode &&
		code_00155860())
	{
		struct fog_screen const *screen= global_window_parameters.fog.screen;
		real_vector3d camera_to_centroid;

		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment_fog.c", 1177, parameters);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_environment_fog.c", 1178, screen);

		camera_to_centroid.i= parameters->centroid.x - global_window_parameters.camera.position.x;
		camera_to_centroid.j= parameters->centroid.y - global_window_parameters.camera.position.y;
		camera_to_centroid.k= parameters->centroid.z - global_window_parameters.camera.position.z;

		if (DOT_PRODUCT3D(global_window_parameters.camera.forward, camera_to_centroid)<screen->far_distance)
		{
			bss_00465d54= parameters;
			bss_00465d58= FALSE;
			result= TRUE;

			if (rasterizer_debug_options.statistics_mode==_rasterizer_statistics_mode_geometry)
			{
				rasterizer_frame_statistics.fog_screen_model_count++;
			}
		}
	}

	return result;
}

// TODO: model_parameters is reloaded before the skinning allocation
void rasterizer_environment_fog_screen_model_submit(
	struct shader const *shader,
	short shader_permutation_index,
	struct triangle_buffer const *triangle_buffer,
	long dynamic_triangle_buffer_index,
	long triangle_count,
	struct vertex_buffer const *vertex_buffer,
	long dynamic_vertex_buffer_index)
{
	if (rasterizer_debug_options.draw_environment_fog_screen && !rasterizer_debug_options.drawing_mode)
	{
		if (bss_00465d24<MAXIMUM_OPAQUE_MODEL_GROUPS)
		{
			struct transparent_geometry_group *group= &bss_00465d20[bss_00465d24++];

			group->shader= shader;
			group->triangle_buffer= triangle_buffer;
			group->shader_permutation_index= shader_permutation_index;
			group->dynamic_triangle_buffer_index= dynamic_triangle_buffer_index;
			group->vertex_buffers= vertex_buffer;
			group->triangle_count= triangle_count;
			group->first_triangle_index= 0;
			group->dynamic_vertex_buffer_index= dynamic_vertex_buffer_index;
			group->model_base_map_scale= bss_00465d54->base_map_scale;

			if (!bss_00465d58)
			{
				bss_00465ad4= rasterizer_memory_alloc_const(bss_00465d54->skinning.node_matrices, bss_00465d54->skinning.node_matrix_count*sizeof(real_matrix4x3));
				bss_00465ad0= bss_00465d54->skinning.node_matrix_count;
				bss_00465d58= TRUE;
			}

			group->node_matrices= bss_00465ad4;
			group->node_matrix_count= bss_00465ad0;
			group->lighting= bss_00465d5c;
			group->animation= bss_00465d60;
		}
		else if (!bss_00465d64)
		{
			error(_error_silent, "### ERROR too many opaque model groups obscuring fog screen (max=#%d)", MAXIMUM_OPAQUE_MODEL_GROUPS);
			bss_00465d64= TRUE;
		}
	}

	return;
}

void rasterizer_environment_fog_screen_model_end(
	void)
{
	bss_00465d54= NULL;

	return;
}
