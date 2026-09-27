/*
RASTERIZER_LIGHTS.C

symbols in this file:
00170840 0030:
	_screenshot_in_progress (0000)
00170870 0040:
	_lens_flare_submit_parameters_get (0000)
001708B0 00f0:
	_lens_flare_occlusion_test_results_get (0000)
001709A0 0030:
	_rasterizer_lights_reset_for_new_map (0000)
001709D0 0130:
	_rasterizer_lights_begin_for_new_frame (0000)
00170B00 0010:
	_rasterizer_lights_begin (0000)
00170B10 0150:
	_rasterizer_light_submit (0000)
00170C60 0010:
	_rasterizer_lights_end (0000)
00170C70 0250:
	_lens_flare_evaluate_corona_rotation_function (0000)
00170EC0 0290:
	_rasterizer_lens_flare_submit (0000)
00171150 0190:
	_rasterizer_lens_flare_submit_for_cluster (0000)
001712E0 0190:
	_rasterizer_lens_flares_submit_occlusion_tests (0000)
00171470 08c0:
	_rasterizer_lens_flares_draw (0000)
0029E6A4 003f:
	??_C@_0DP@MMPMMAFC@lens_flare_index?$DO?$DN0?5?$CG?$CG?5lens_flar@ (0000)
0029E6E4 002e:
	??_C@_0CO@MGBADAON@c?3?2halo?2SOURCE?2rasterizer?2raster@ (0000)
0029E718 0063:
	??_C@_0GD@JPCGFHAO@lens_flare_parameters?9?$DOlight_ind@ (0000)
0029E780 0082:
	??_C@_0IC@IBFAKJOH@structure_lens_flare_index?$DO?$DN0?5?$CG?$CG@ (0000)
0029E804 0016:
	??_C@_0BG@JFBJFIEK@lens_flare_parameters?$AA@ (0000)
0029E81C 002e:
	??_C@_0CO@FCEOCGFK@?$CD?$CD?$CD?5ERROR?5too?5many?5lights?5submit@ (0000)
0029E84C 003f:
	??_C@_0DP@CJDDDBGK@parameters?9?$DOcolor?4blue?5?$DO?$DN0?40f?5?$CG?$CG@ (0000)
0029E88C 003f:
	??_C@_0DP@IFBCMKNP@parameters?9?$DOcolor?4green?$DO?$DN0?40f?5?$CG?$CG@ (0000)
0029E8CC 003d:
	??_C@_0DN@IFBOCEFD@parameters?9?$DOcolor?4red?5?$DO?$DN0?40f?5?$CG?$CG?5@ (0000)
0029E90C 003a:
	??_C@_0DK@NODNGFKL@?$CD?$CD?$CD?5ERROR?5unsupported?5lens?5flare@ (0000)
0029E948 0032:
	??_C@_0DC@BJJPKDMH@?$CD?$CD?$CD?5ERROR?5too?5many?5lens?5flares?5s@ (0000)
0029E980 004d:
	??_C@_0EN@OMGAKMEG@parameters?9?$DOlight_index?$DO?$DN0?5?$CG?$CG?5pa@ (0000)
0029E9D0 0065:
	??_C@_0GF@CKCJNIMD@structure_lens_flare_index?$DO?$DN0?5?$CG?$CG@ (0000)
0029EA38 005b:
	??_C@_0FL@ECFOOILG@parameters?9?$DOlens_flare_index?$DO?$DN0?5@ (0000)
0029EA98 006b:
	??_C@_0GL@HCLLBKGN@?$CIparameters?9?$DOcompressed_window_i@ (0000)
0029EB04 0017:
	??_C@_0BH@FDNIDAHL@parameters?9?$DOdefinition?$AA@ (0000)
0029EB1C 003c:
	??_C@_0DM@DJHNIOGP@?$CD?$CD?$CD?5ERROR?5unsupported?5lens?5flare@ (0000)
0029EB58 003b:
	??_C@_0DL@EPCOBKHO@animation_color?4blue?5?$DO?$DN0?40f?5?$CG?$CG?5a@ (0000)
0029EB94 003b:
	??_C@_0DL@CLPEFPIB@animation_color?4green?$DO?$DN0?40f?5?$CG?$CG?5a@ (0000)
0029EBD0 0039:
	??_C@_0DJ@NIJDHHFP@animation_color?4red?5?$DO?$DN0?40f?5?$CG?$CG?5an@ (0000)
0029EC0C 003b:
	??_C@_0DL@HIJLAENC@animation_color?4alpha?$DO?$DN0?40f?5?$CG?$CG?5a@ (0000)
0029EC48 0023:
	??_C@_0CD@LGKNCBJE@reflection?9?$DOanimation_period?$CB?$DN0?4@ (0000)
0029EC6C 0004:
	__real@42652ee1 (0000)
00466B80 51725:
	_local_lens_flare_occlusion_test_results2 (0000)
	_local_lens_flare_occlusion_test_results (40008)
	_local_lens_flare_parameters (47720)
	_local_lens_flare_count (51720)
	?warned@?1??rasterizer_lens_flare_submit@@9@9 (51724)
*/

/* ---------- headers */

#include "cseries.h"
#include "cseries_windows.h"
#include "errors.h"
#include "real_math.h"
#include "bitmaps.h"
#include "periodic_functions.h"
#include "tag_groups.h"
#include "rasterizer.h"
#include "xbox/rasterizer_xbox.h"
#include "render.h"
#include "scenario.h"
#include "structure_bsp_definitions.h"
#include "light_definitions.h"

/* ---------- constants */

enum
{
	_lens_flare_parameters_light_index_structure_bit = 15,
	_lens_flare_parameters_light_index_mask = 0x7fff,

	_lens_flare_window_index_first_person_bit = 7,
	_lens_flare_window_index_mask = ~FLAG(_lens_flare_window_index_first_person_bit),
};

enum
{
	_rasterizer_widget_lens_flare = 5,
	_rasterizer_widget_lens_flare_occlusion = 6,
};

/* ---------- macros */

/* ---------- structures */

struct lens_flare_occlusion_test_results
{
	short light_identifier;
	byte data[MAXIMUM_LENS_FLARES_PER_LIGHT][MAXIMUM_WINDOWS];
};

/* ---------- prototypes */

void rasterizer_profile_begin(short profile);
void rasterizer_profile_end(short profile);

void rasterizer_widget_begin(short widget_type, boolean occlusion);
boolean rasterizer_widget_set_texture(short stage, long bitmap_index, short sequence_index);
void rasterizer_widget_set_tint_factor(real tint_factor);
void rasterizer_widget_draw_sprite3d(real_point3d const *point, real radius, real_vector2d const *scale, real rotation, unsigned long color);
long rasterizer_widget_submit_occlusion_test(real_point3d const *point, real radius, long lens_flare_index);
void rasterizer_widget_end(void);
long rasterizer_widget_get_occlusion_test_result(long lens_flare_index);

void rasterizer_set_stencil_mode(short mode);
void rasterizer_sun_glow_draw(struct rasterizer_lens_flare_submit_parameters const *parameters);

real_vector3d uncompress_int32_to_real_vector3d(unsigned long compressed);
unsigned long compress_real_vector3d_to_int32_clamp(real_vector3d const *vector);
real uncompress_int8_to_real(byte compressed);
byte compress_real_to_int8(real value);
unsigned long real_argb_color_to_pixel32(real_argb_color const *color);

static boolean screenshot_in_progress(void);
static struct rasterizer_lens_flare_submit_parameters *lens_flare_submit_parameters_get(short lens_flare_index);
static byte *lens_flare_occlusion_test_results_get(struct rasterizer_lens_flare_submit_parameters const *lens_flare_parameters);
static real lens_flare_evaluate_corona_rotation_function(short function, struct rasterizer_lens_flare_submit_parameters const *lens_flare_parameters);

void rasterizer_lens_flare_submit(struct rasterizer_lens_flare_submit_parameters const *parameters);

/* ---------- globals */

extern short global_screenshot_count;
extern short global_screenshot_size;
extern struct rasterizer_window_begin_parameters global_window_parameters;

static struct rasterizer_lens_flare_submit_parameters local_lens_flare_parameters[MAXIMUM_LENS_FLARES_PER_FRAME];
static struct lens_flare_occlusion_test_results local_lens_flare_occlusion_test_results[MAXIMUM_LIGHTS_PER_MAP];
static byte local_lens_flare_occlusion_test_results2[MAXIMUM_LENS_FLARE_MARKERS_PER_STRUCTURE+MAXIMUM_QUEUED_LENS_FLARES][MAXIMUM_WINDOWS];
static long local_lens_flare_count;

/* ---------- public code */

static boolean screenshot_in_progress(
	void)
{
	return global_screenshot_count>1 || (global_screenshot_count==1 && global_screenshot_size>1);
}

static struct rasterizer_lens_flare_submit_parameters *lens_flare_submit_parameters_get(
	short lens_flare_index)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_lights.c", 67, lens_flare_index>=0 && lens_flare_index<local_lens_flare_count);
	return &local_lens_flare_parameters[lens_flare_index];
}

static byte *lens_flare_occlusion_test_results_get(
	struct rasterizer_lens_flare_submit_parameters const *lens_flare_parameters)
{
	byte *result;

	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_lights.c", 76, lens_flare_parameters);

	if (TEST_FLAG((word)lens_flare_parameters->light_index, _lens_flare_parameters_light_index_structure_bit))
	{
		long window_index= lens_flare_parameters->compressed_window_index&_lens_flare_window_index_mask;
		long structure_lens_flare_index= (((word)lens_flare_parameters->light_index&_lens_flare_parameters_light_index_mask)<<16) | lens_flare_parameters->lens_flare_index;

		match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_lights.c", 87, window_index>=0 && window_index<MAXIMUM_WINDOWS);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_lights.c", 88, structure_lens_flare_index>=0 && structure_lens_flare_index<(MAXIMUM_LENS_FLARE_MARKERS_PER_STRUCTURE+MAXIMUM_QUEUED_LENS_FLARES));
		result= &local_lens_flare_occlusion_test_results2[structure_lens_flare_index][window_index];
	}
	else
	{
		match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_lights.c", 94, lens_flare_parameters->light_index>=0 && lens_flare_parameters->light_index<MAXIMUM_LIGHTS_PER_MAP);
		result= &local_lens_flare_occlusion_test_results[lens_flare_parameters->light_index].data[lens_flare_parameters->lens_flare_index][lens_flare_parameters->compressed_window_index&_lens_flare_window_index_mask];
	}

	return result;
}

// TODO: fmul operand order in the negated dot products
static real lens_flare_evaluate_corona_rotation_function(
	short function,
	struct rasterizer_lens_flare_submit_parameters const *lens_flare_parameters)
{
	real x= 1.0f;
	real y= 0.0f;
	real rotation= 0.0f;
	real_vector3d forward_vector;
	real_vector3d direction_vector;
	real_vector3d vector;

	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_lights.c", 118, lens_flare_parameters);
	direction_vector= uncompress_int32_to_real_vector3d(lens_flare_parameters->compressed_direction);

	switch (function)
	{
	case _lens_flare_corona_rotation_function_eye_in_light_space:
		cross_product3d(&direction_vector, &global_window_parameters.frustum.view_to_world.forward, &forward_vector);
		cross_product3d(&forward_vector, &direction_vector, &forward_vector);
		vector= global_window_parameters.camera.forward;
		y= dot_product3d(&forward_vector, &vector);
		x= -dot_product3d(&vector, &direction_vector);
		break;
	case _lens_flare_corona_rotation_function_light_in_eye_space:
		vector.i= -direction_vector.i;
		vector.j= -direction_vector.j;
		vector.k= -direction_vector.k;
		y= dot_product3d(&global_window_parameters.frustum.view_to_world.forward, &vector);
		x= -dot_product3d(&global_window_parameters.frustum.view_to_world.up, &vector);
		break;
	case _lens_flare_corona_rotation_function_eye_to_light_in_light_space:
		cross_product3d(&direction_vector, &global_window_parameters.frustum.view_to_world.forward, &forward_vector);
		cross_product3d(&forward_vector, &direction_vector, &forward_vector);
		vector_from_points3d(&global_window_parameters.camera.position, &lens_flare_parameters->position, &vector);
		y= dot_product3d(&forward_vector, &vector);
		x= -dot_product3d(&vector, &direction_vector);
		break;
	case _lens_flare_corona_rotation_function_eye_to_light_in_eye_space:
		vector_from_points3d(&global_window_parameters.camera.position, &lens_flare_parameters->position, &vector);
		y= dot_product3d(&global_window_parameters.frustum.view_to_world.forward, &vector);
		x= -dot_product3d(&global_window_parameters.frustum.view_to_world.up, &vector);
		break;
	default:
		match_vassert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_lights.c", 151, FALSE, "### ERROR unsupported lens flare corona rotation function");
	case _lens_flare_corona_rotation_function_none:
		break;
	}

	if (function!=_lens_flare_corona_rotation_function_none && y!=0.0f)
	{
		rotation= arctangent(y, x)*(1.0f/(2.0f*_pi));
	}

	return rotation;
}

void rasterizer_lights_reset_for_new_map(
	void)
{
	memset(local_lens_flare_occlusion_test_results, 0, sizeof(local_lens_flare_occlusion_test_results)+sizeof(struct lens_flare_occlusion_test_results));
	memset(local_lens_flare_occlusion_test_results2, 0, sizeof(local_lens_flare_occlusion_test_results2));
	local_lens_flare_count= 0;

	return;
}

// TODO: occlusion pixel count is cached across the widget call instead of being reloaded
void rasterizer_lights_begin_for_new_frame(
	void)
{
	rasterizer_profile_begin(_rasterizer_profile_lens_flare_occlusion_query);

	if (rasterizer_debug_options.draw_lens_flares && !screenshot_in_progress())
	{
		short lens_flare_index;

		for (lens_flare_index= 0; lens_flare_index<local_lens_flare_count; lens_flare_index++)
		{
			struct rasterizer_lens_flare_submit_parameters *lens_flare_parameters= lens_flare_submit_parameters_get(lens_flare_index);
			byte *occlusion_test_result= lens_flare_occlusion_test_results_get(lens_flare_parameters);
			byte new_result= 0;

			if (lens_flare_parameters->internal__occlusion_pixels>0)
			{
				long result= (rasterizer_widget_get_occlusion_test_result(lens_flare_index)*255 + (lens_flare_parameters->internal__occlusion_pixels>>1))/lens_flare_parameters->internal__occlusion_pixels;

				new_result= result<255 ? (byte)result : 255;
			}

			if (!new_result)
			{
				*occlusion_test_result= 0;
			}
			else if (new_result>*occlusion_test_result)
			{
				*occlusion_test_result= (3*(*occlusion_test_result) + new_result)/4;
			}
			else if (new_result<*occlusion_test_result)
			{
				*occlusion_test_result= ((*occlusion_test_result) + new_result)/2;
			}
		}

		local_lens_flare_count= 0;
	}

	rasterizer_profile_end(_rasterizer_profile_lens_flare_occlusion_query);

	return;
}

void rasterizer_lights_begin(
	void)
{
	rasterizer_lights.light_count= 0;

	return;
}

long rasterizer_light_submit(
	struct rasterizer_light_submit_parameters const *parameters)
{
	long light_index= NONE;

	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_lights.c", 240, parameters);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_lights.c", 241, parameters->color.red >=0.0f && parameters->color.red <=1.0f);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_lights.c", 242, parameters->color.green>=0.0f && parameters->color.green<=1.0f);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_lights.c", 243, parameters->color.blue >=0.0f && parameters->color.blue <=1.0f);

	if (rasterizer_lights.light_count<MAXIMUM_LIGHTS_PER_WINDOW)
	{
		light_index= rasterizer_lights.light_count++;
		rasterizer_lights.lights[light_index]= *parameters;

		if (rasterizer_debug_options.statistics_mode==_rasterizer_statistics_mode_geometry)
		{
			rasterizer_frame_statistics.dynamic_light_count++;
		}
	}
	else
	{
		error(_error_silent, "### ERROR too many lights submitted to window");
	}

	return light_index;
}

void rasterizer_lens_flare_submit(
	struct rasterizer_lens_flare_submit_parameters const *parameters)
{
	static boolean warned= FALSE;

	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_lights.c", 266, parameters);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_lights.c", 267, parameters->definition);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_lights.c", 268, (parameters->compressed_window_index&_lens_flare_window_index_mask)==global_window_parameters.window_index);

	if (rasterizer_debug_options.draw_lens_flares && !screenshot_in_progress() && !global_window_parameters.rasterizer_target)
	{
		if (local_lens_flare_count<MAXIMUM_LENS_FLARES_PER_FRAME)
		{
			real_vector3d eye_to_light;

			vector_from_points3d(&global_window_parameters.camera.position, &parameters->position, &eye_to_light);
			if ((parameters->definition->far_fade_distance==0.0f || dot_product3d(&global_window_parameters.camera.forward, &eye_to_light)<parameters->definition->far_fade_distance) &&
				(parameters->compressed_light_color&0xff000000)>0)
			{
				struct rasterizer_lens_flare_submit_parameters *lens_flare_parameters= lens_flare_submit_parameters_get((short)local_lens_flare_count++);

				memcpy(lens_flare_parameters, parameters, sizeof(struct rasterizer_lens_flare_submit_parameters));

				if (parameters->light_identifier==NONE)
				{
					if (parameters->light_index==NONE)
					{
						lens_flare_parameters->light_index= FLAG(_lens_flare_parameters_light_index_structure_bit);
						match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_lights.c", 310, parameters->lens_flare_index>=0 && parameters->lens_flare_index<MAXIMUM_QUEUED_LENS_FLARES);
					}
					else
					{
						long structure_lens_flare_index= (parameters->light_index<<16) | parameters->lens_flare_index;

						match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_lights.c", 321, structure_lens_flare_index>=0 && structure_lens_flare_index<MAXIMUM_LENS_FLARE_MARKERS_PER_STRUCTURE);
						lens_flare_parameters->lens_flare_index= (short)(structure_lens_flare_index+MAXIMUM_QUEUED_LENS_FLARES);
						lens_flare_parameters->light_index= (short)(structure_lens_flare_index>>16) | FLAG(_lens_flare_parameters_light_index_structure_bit);
					}
				}
				else
				{
					struct lens_flare_occlusion_test_results *results= &local_lens_flare_occlusion_test_results[lens_flare_parameters->light_index];

					match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_lights.c", 338, parameters->light_index>=0 && parameters->light_index<MAXIMUM_LIGHTS_PER_MAP);
					if (parameters->light_identifier!=results->light_identifier)
					{
						memset(results->data, 0, sizeof(results->data));
						results->light_identifier= lens_flare_parameters->light_identifier;
					}
				}

				if (rasterizer_debug_options.statistics_mode==_rasterizer_statistics_mode_geometry)
				{
					rasterizer_frame_statistics.lens_flare_count++;
				}
			}
		}
		else if (!warned)
		{
			error(_error_silent, "### ERROR too many lens flares submitted to frame");
			warned= TRUE;
		}
	}

	return;
}

// TODO: marker direction byte loads are scheduled differently
void rasterizer_lens_flare_submit_for_cluster(
	short cluster_index)
{
	if (rasterizer_debug_options.draw_lens_flares && !screenshot_in_progress())
	{
		struct structure_bsp *structure_bsp= global_structure_bsp_get();
		struct structure_cluster *cluster= TAG_BLOCK_GET_ELEMENT(&structure_bsp->clusters, cluster_index, struct structure_cluster);
		long marker_index;

		for (marker_index= 0; marker_index<cluster->lens_flare_marker_count; marker_index++)
		{
			long lens_flare_marker_index= cluster->first_lens_flare_marker_index+marker_index;
			struct structure_lens_flare_marker *marker= TAG_BLOCK_GET_ELEMENT(&structure_bsp->lens_flare_markers, lens_flare_marker_index, struct structure_lens_flare_marker);
			struct structure_lens_flare *lens_flare= TAG_BLOCK_GET_ELEMENT(&structure_bsp->lens_flares, marker->lens_flare_index, struct structure_lens_flare);
			struct rasterizer_lens_flare_submit_parameters parameters;
			real_vector3d up;
			real_vector3d direction;

			set_real_vector3d(&direction, marker->i_direction/127.f, marker->j_direction/127.f, marker->k_direction/127.f);
			perpendicular3d(&direction, &up);
			normalize3d(&direction);
			normalize3d(&up);

			parameters.compressed_direction= compress_real_vector3d_to_int32_clamp(&direction);
			parameters.compressed_up= compress_real_vector3d_to_int32_clamp(&up);
			parameters.definition= tag_get(LENS_FLARE_DEFINITION_TAG, lens_flare->lens_flare.index);
			parameters.position= marker->position;
			parameters.compressed_light_color= 0xffffffff;
			parameters.light_identifier= NONE;
			parameters.light_index= (short)(lens_flare_marker_index>>16);
			parameters.lens_flare_index= (short)lens_flare_marker_index;
			parameters.compressed_light_scale= 0;
			parameters.compressed_window_index= (byte)render.window_index;
			rasterizer_lens_flare_submit(&parameters);
		}
	}

	return;
}

void rasterizer_lights_end(
	void)
{
	return;
}

// TODO: position copy load/store scheduling differs
void rasterizer_lens_flares_submit_occlusion_tests(
	void)
{
	rasterizer_profile_begin(_rasterizer_profile_lens_flare_occlusion_submit);

	if (rasterizer_debug_options.draw_lens_flares && !screenshot_in_progress())
	{
		short lens_flare_index= 0;

		if (!global_window_parameters.rasterizer_target && local_lens_flare_count>0)
		{
			rasterizer_widget_begin(_rasterizer_widget_lens_flare_occlusion, TRUE);

			for (lens_flare_index= 0; lens_flare_index<local_lens_flare_count; lens_flare_index++)
			{
				struct rasterizer_lens_flare_submit_parameters *lens_flare_parameters= lens_flare_submit_parameters_get(lens_flare_index);
				struct lens_flare_definition *definition= lens_flare_parameters->definition;
				real_vector3d direction;
				real_point3d point;

				direction= uncompress_int32_to_real_vector3d(lens_flare_parameters->compressed_direction);

				if ((lens_flare_parameters->compressed_window_index&_lens_flare_window_index_mask)==global_window_parameters.window_index)
				{
					real occlusion_radius= definition->occlusion_radius;

					switch (definition->occlusion_offset_direction)
					{
					case _lens_flare_occlusion_offset_direction_toward_viewer:
						point_from_line3d(&lens_flare_parameters->position, &global_window_parameters.camera.forward, -definition->occlusion_radius, &point);
						break;
					case _lens_flare_occlusion_offset_direction_marker_forward:
						point_from_line3d(&lens_flare_parameters->position, &direction, definition->occlusion_radius*1.4142135f, &point);
						break;
					case _lens_flare_occlusion_offset_direction_none:
						point= lens_flare_parameters->position;
						break;
					default:
						match_vassert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_lights.c", 482, FALSE, "### ERROR unsupported lens flare occlusion offset direction");
					}

					lens_flare_parameters->internal__occlusion_pixels= rasterizer_widget_submit_occlusion_test(&point, occlusion_radius, lens_flare_index);
				}
			}

			rasterizer_widget_end();
		}
	}

	rasterizer_profile_end(_rasterizer_profile_lens_flare_occlusion_submit);

	return;
}

static __inline real interpolate_real(
	real lower,
	real upper,
	real t)
{
	return (upper-lower)*t + lower;
}

// TODO: fmul operand order in dot products, some instruction scheduling, global_frame_parameters reloc (tentative definition in rasterizer.h)
void rasterizer_lens_flares_draw(
	void)
{
	real brightness;
	real_vector3d eye_to_corona_vector;
	real distance;
	struct lens_flare_definition *definition;
	real rotation;
	real occlusion;
	short reflection_index;
	real_argb_color animation_color;
	real_vector3d corona_axis;
	real_argb_color tint_color;
	real tint_factor;
	real_vector3d direction;
	real_point3d corona_position;
	short lens_flare_index;
	real light_scale;
	real scale_functions[NUMBER_OF_LENS_FLARE_SCALE_FUNCTIONS];
	real_vector2d scale;
	real corona_rotation;
	real screen_angle;
	real_point3d point;
	real angle_scale;
	real angle_offset;

	rasterizer_profile_begin(_rasterizer_profile_lens_flares);

	if (rasterizer_debug_options.draw_lens_flares && !global_window_parameters.rasterizer_target && local_lens_flare_count>0)
	{
		rasterizer_widget_begin(_rasterizer_widget_lens_flare, FALSE);

		for (lens_flare_index= 0; lens_flare_index<local_lens_flare_count; lens_flare_index++)
		{
			struct rasterizer_lens_flare_submit_parameters *lens_flare_parameters= lens_flare_submit_parameters_get(lens_flare_index);
			byte *occlusion_test_result= lens_flare_occlusion_test_results_get(lens_flare_parameters);

			direction= uncompress_int32_to_real_vector3d(lens_flare_parameters->compressed_direction);

			if ((lens_flare_parameters->compressed_window_index&_lens_flare_window_index_mask)==global_window_parameters.window_index)
			{
				definition= lens_flare_parameters->definition;

				if (lens_flare_parameters->internal__occlusion_pixels>0 && (lens_flare_parameters->compressed_light_color>>24)>0 && definition->reflections.count>0)
				{
					corona_position= lens_flare_parameters->position;
					vector_from_points3d(&global_window_parameters.camera.position, &corona_position, &eye_to_corona_vector);
					distance= dot_product3d(&eye_to_corona_vector, &global_window_parameters.camera.forward);
					scale_vector3d(&global_window_parameters.camera.forward, distance, &corona_axis);
					corona_axis.i-= eye_to_corona_vector.i;
					corona_axis.j-= eye_to_corona_vector.j;
					corona_axis.k-= eye_to_corona_vector.k;
					corona_axis.i+= corona_axis.i;
					corona_axis.j+= corona_axis.j;
					corona_axis.k+= corona_axis.k;

					occlusion= (real)*occlusion_test_result/255.f;

					if (definition->far_fade_distance>0.0f)
					{
						brightness= PIN((distance - definition->far_fade_distance)/(definition->near_fade_distance - definition->far_fade_distance), 0.0f, 1.0f);
					}
					else
					{
						brightness= 1.0f;
					}

					brightness= uncompress_int8_to_real(lens_flare_parameters->compressed_light_color>>24)*(occlusion*brightness);
					corona_rotation= lens_flare_evaluate_corona_rotation_function(definition->corona_rotation_function, lens_flare_parameters)*definition->corona_rotation_function_scale;
					screen_angle= arctangent(
						dot_product3d(&global_window_parameters.frustum.view_to_world.forward, &eye_to_corona_vector),
						dot_product3d(&global_window_parameters.frustum.view_to_world.left, &eye_to_corona_vector))*57.29578f;

					angle_scale= 1.0f/(definition->runtime_cosine_falloff_angle - definition->runtime_cosine_cutoff_angle);
					angle_offset= -(angle_scale*definition->runtime_cosine_cutoff_angle);
					normalize3d(&eye_to_corona_vector);

					scale_functions[_lens_flare_scale_function_none]= 1.0f;
					scale_functions[_lens_flare_scale_function_non_local_incident_angle]= PIN(angle_offset - dot_product3d(&global_window_parameters.camera.forward, &direction)*angle_scale, 0.0f, 1.0f);
					scale_functions[_lens_flare_scale_function_local_incident_angle]= PIN(angle_offset - dot_product3d(&direction, &eye_to_corona_vector)*angle_scale, 0.0f, 1.0f);
					scale_functions[_lens_flare_scale_function_viewer_angle]= PIN(dot_product3d(&global_window_parameters.camera.forward, &eye_to_corona_vector)*angle_scale + angle_offset, 0.0f, 1.0f);

					if (brightness>0.0f)
					{
						light_scale= uncompress_int8_to_real(lens_flare_parameters->compressed_light_scale);

						for (reflection_index= 0; reflection_index<definition->reflections.count; reflection_index++)
						{
							struct lens_flare_reflection *reflection= TAG_BLOCK_GET_ELEMENT(&definition->reflections, reflection_index, struct lens_flare_reflection);
							real reflection_brightness;

							reflection_brightness= interpolate_real(reflection->brightness_lower_bounds, reflection->brightness_upper_bounds, light_scale)*
								scale_functions[reflection->brightness_scale_function]*brightness;

							if (!reflection_index)
							{
								brightness= reflection_brightness;
							}

							if (reflection_brightness>0.0f)
							{
								unsigned long color;
								real radius;

								radius= interpolate_real(reflection->radius_lower_bounds, reflection->radius_upper_bounds, light_scale);

								if (reflection->tint_color.alpha==0.0f &&
									reflection->tint_color.red==0.0f &&
									reflection->tint_color.green==0.0f &&
									reflection->tint_color.blue==0.0f)
								{
									color= (lens_flare_parameters->compressed_light_color&0x00ffffff) | (compress_real_to_int8(reflection_brightness)<<24);
									tint_factor= 1.0f;
								}
								else
								{
									tint_color.rgb= reflection->tint_color.rgb;
									tint_color.alpha= reflection_brightness;

									if (reflection->animation_function>1)
									{
										real t;

										match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_lights.c", 651, reflection->animation_period!=0.0f);
										t= periodic_function_evaluate(reflection->animation_function, (global_frame_parameters.game_time_sec + reflection->animation_phase)/reflection->animation_period);
										rgb_colors_interpolate(&animation_color.rgb, reflection->animation_flags&3, &reflection->animation_color_lower_bound.rgb, &reflection->animation_color_upper_bound.rgb, t);
										scalars_interpolate(reflection->animation_color_lower_bound.alpha, reflection->animation_color_upper_bound.alpha, t, &animation_color.alpha);
										match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_lights.c", 667, animation_color.alpha>=0.0f && animation_color.alpha<=1.0f);
										match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_lights.c", 668, animation_color.red >=0.0f && animation_color.red <=1.0f);
										match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_lights.c", 669, animation_color.green>=0.0f && animation_color.green<=1.0f);
										match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_lights.c", 670, animation_color.blue >=0.0f && animation_color.blue <=1.0f);
										tint_color.alpha*= animation_color.alpha;
										tint_color.red*= animation_color.red;
										tint_color.green*= animation_color.green;
										tint_color.blue*= animation_color.blue;
									}

									color= real_argb_color_to_pixel32(&tint_color);
									tint_factor= reflection->tint_color.alpha;
								}

								if (!reflection_index)
								{
									rotation= corona_rotation + reflection->rotation_offset;
									scale= definition->corona_radius_scale;
								}
								else
								{
									rotation= reflection->rotation_offset;
									scale.i= 1.0f;
									scale.j= 1.0f;
								}

								if (TEST_FLAG(reflection->flags, _lens_flare_reflection_rotate_from_center_of_screen_bit))
								{
									rotation+= screen_angle;
								}
								if (TEST_FLAG(reflection->flags, _lens_flare_reflection_radius_scaled_by_occlusion_bit))
								{
									radius= (occlusion + 1.0f)*radius*0.5f;
								}
								if (TEST_FLAG(reflection->flags, _lens_flare_reflection_radius_not_scaled_by_distance_bit))
								{
									radius*= distance;
								}

								point_from_line3d(&corona_position, &corona_axis, reflection->offset, &point);

								if (rasterizer_widget_set_texture(0, definition->primary_map.index, reflection->bitmap_index))
								{
									break;
								}

								rasterizer_widget_set_tint_factor(tint_factor);
								if (TEST_FLAG(reflection->flags, _lens_flare_reflection_zbuffer_bit) &&
									TEST_FLAG(lens_flare_parameters->compressed_window_index, _lens_flare_window_index_first_person_bit))
								{
									rasterizer_set_stencil_mode(_rasterizer_stencil_mode_reject);
								}
								else
								{
									rasterizer_set_stencil_mode(_rasterizer_stencil_mode_none);
								}
								rasterizer_widget_draw_sprite3d(&point, radius, &scale, DEGREES_TO_RADIANS(rotation), color);
							}
						}
					}
				}
			}
		}

		rasterizer_set_stencil_mode(_rasterizer_stencil_mode_none);
		rasterizer_widget_end();

		if (rasterizer_debug_options.lens_flare_sun_glow_enabled)
		{
			for (lens_flare_index= 0; lens_flare_index<local_lens_flare_count; lens_flare_index++)
			{
				struct rasterizer_lens_flare_submit_parameters *lens_flare_parameters= lens_flare_submit_parameters_get(lens_flare_index);

				if (lens_flare_parameters->internal__occlusion_pixels>0 &&
					(lens_flare_parameters->compressed_window_index&_lens_flare_window_index_mask)==global_window_parameters.window_index &&
					(lens_flare_parameters->definition->occlusion_radius==50.0f || TEST_FLAG(lens_flare_parameters->definition->flags, _lens_flare_sun_bit)))
				{
					rasterizer_sun_glow_draw(lens_flare_parameters);
				}
			}
		}
	}

	rasterizer_profile_end(_rasterizer_profile_lens_flares);

	return;
}
