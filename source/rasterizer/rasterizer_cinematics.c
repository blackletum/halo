/*
RASTERIZER_CINEMATICS.C

symbols in this file:
0016D140 0020:
	_rasterizer_screen_effects_time (0000)
0016D160 0040:
	_rasterizer_screen_effects_initialize (0000)
0016D1A0 0030:
	_rasterizer_screen_effects_initialize_for_new_map (0000)
0016D1D0 0010:
	_rasterizer_screen_effects_dispose_from_old_map (0000)
0016D1E0 0010:
	_rasterizer_screen_effects_dispose (0000)
0016D1F0 0030:
	_rasterizer_script_screen_effect_set_value (0000)
0016D220 0030:
	_rasterizer_script_screen_effect_get_value (0000)
0016D250 0040:
	_rasterizer_screen_effect_start (0000)
0016D290 0070:
	_rasterizer_screen_effect_set_convolution (0000)
0016D300 0070:
	_rasterizer_screen_effect_set_filter (0000)
0016D370 0020:
	_rasterizer_screen_effect_set_filter_desaturation_tint (0000)
0016D390 0120:
	_rasterizer_screen_effect_set_video (0000)
0016D4B0 0010:
	_rasterizer_screen_effect_stop (0000)
0016D4C0 0250:
	_rasterizer_screen_effect_get_cinematic_parameters (0000)
0016D710 0020:
	_rasterizer_set_near_clip_distance (0000)
0016D730 0030:
	_rasterizer_get_near_clip_distance (0000)
0029D844 0020:
	??_C@_0CA@HAHKAAEK@cinematic_screen_effect_globals?$AA@ (0000)
0029D864 0032:
	??_C@_0DC@FCKAGPCD@c?3?2halo?2SOURCE?2rasterizer?2raster@ (0000)
0029D898 0014:
	??_C@_0BE@COKLOHBN@screen?5effect?5filth?$AA@ (0000)
0029D8B0 004a:
	??_C@_0EK@IJBENNIM@?$CD?$CD?$CD?5ERROR?5cinematics?5failed?5to?5s@ (0000)
0029D900 008d:
	??_C@_0IN@PCKCIAIJ@?$CD?$CD?$CD?5FATAL_ERROR?5screen?5effects?5c@ (0000)
004662F4 0004:
	_cinematic_screen_effect_globals (0000)
*/

/* ---------- headers */

#include "cseries.h"
#include "errors.h"
#include "real_math.h"
#include "bitmaps.h"
#include "bitmaps/bitmap_group.h"
#include "tag_files/tag_groups.h"
#include "game.h"
#include "game_globals.h"
#include "game_state.h"
#include "rasterizer.h"
#include "rasterizer_cinematics.h"

/* ---------- constants */

enum
{
	NUMBER_OF_SCRIPT_SCREEN_EFFECT_VALUES= 4
};

/* ---------- macros */

/* ---------- structures */

struct cinematic_screen_effect_globals
{
	struct rasterizer_screen_effect_parameters parameters;
	boolean has_control;
	boolean initialized;
	real convolution_radius[2];
	real convolution_time[2];
	real filter_light_enhancement_intensity[2];
	real filter_desaturation_intensity[2];
	real filter_time[2];
	real script_values[NUMBER_OF_SCRIPT_SCREEN_EFFECT_VALUES];
	real near_clip_distance;
};

/* ---------- prototypes */

short main_get_window_count(void);


/* ---------- globals */

extern struct game_globals_rasterizer_data *global_rasterizer_data;
extern const struct rasterizer_global_defaults rasterizer_global_defaults;

static struct cinematic_screen_effect_globals *cinematic_screen_effect_globals;

/* ---------- private code */

static real rasterizer_screen_effects_time(
	void)
{
	return (real)game_time_get()*(1.f/30.f);
}

/* ---------- public code */

void rasterizer_screen_effects_initialize(
	void)
{
	cinematic_screen_effect_globals= game_state_malloc("screen effect filth", NULL, sizeof(struct cinematic_screen_effect_globals));
	match_vassert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_cinematics.c", 54, cinematic_screen_effect_globals, "cinematic_screen_effect_globals");

	return;
}

void rasterizer_screen_effects_initialize_for_new_map(
	void)
{
	if (cinematic_screen_effect_globals)
	{
		memset(cinematic_screen_effect_globals, 0, sizeof(struct cinematic_screen_effect_globals));
		cinematic_screen_effect_globals->script_values[0]= 1.f;
		cinematic_screen_effect_globals->script_values[1]= 1.f;
		cinematic_screen_effect_globals->script_values[2]= 1.f;
		cinematic_screen_effect_globals->script_values[3]= 1.f;
	}

	return;
}

void rasterizer_screen_effects_dispose_from_old_map(
	void)
{
	return;
}

void rasterizer_screen_effects_dispose(
	void)
{
	return;
}

void rasterizer_script_screen_effect_set_value(
	short index,
	real value)
{
	if (cinematic_screen_effect_globals && index>=0 && index<NUMBER_OF_SCRIPT_SCREEN_EFFECT_VALUES)
	{
		cinematic_screen_effect_globals->script_values[index]= value;
	}

	return;
}

real rasterizer_script_screen_effect_get_value(
	short index)
{
	real value= 0.f;

	if (cinematic_screen_effect_globals && index>=0 && index<NUMBER_OF_SCRIPT_SCREEN_EFFECT_VALUES)
	{
		value= cinematic_screen_effect_globals->script_values[index];
	}

	return value;
}

void rasterizer_screen_effect_start(
	boolean reset)
{
	if (cinematic_screen_effect_globals)
	{
		if (reset || !cinematic_screen_effect_globals->initialized)
		{
			memset(&cinematic_screen_effect_globals->parameters, 0, sizeof(struct rasterizer_screen_effect_parameters));
			cinematic_screen_effect_globals->initialized= TRUE;
		}
		cinematic_screen_effect_globals->has_control= TRUE;
	}

	return;
}

void rasterizer_screen_effect_set_convolution(
	short extra_passes,
	short type,
	real radius_from,
	real radius_to,
	real time)
{
	if (cinematic_screen_effect_globals)
	{
		cinematic_screen_effect_globals->parameters.video_on= FALSE;
		cinematic_screen_effect_globals->parameters.video_overbright_mode= 0;
		cinematic_screen_effect_globals->parameters.video_scanline_map= NULL;
		cinematic_screen_effect_globals->parameters.video_noise_intensity= 0.f;
		cinematic_screen_effect_globals->parameters.video_noise_map_scale= 0.f;
		cinematic_screen_effect_globals->parameters.video_noise_map= NULL;
		cinematic_screen_effect_globals->parameters.convolution_extra_passes= extra_passes;
		cinematic_screen_effect_globals->parameters.convolution_type= type;
		cinematic_screen_effect_globals->convolution_radius[0]= radius_from;
		cinematic_screen_effect_globals->convolution_radius[1]= radius_to;
		cinematic_screen_effect_globals->convolution_time[0]= rasterizer_screen_effects_time();
		cinematic_screen_effect_globals->convolution_time[1]= cinematic_screen_effect_globals->convolution_time[0]+time;
	}

	return;
}

void rasterizer_screen_effect_set_filter(
	real light_enhancement_from,
	real light_enhancement_to,
	real desaturation_from,
	real desaturation_to,
	boolean desaturation_is_additive,
	real time)
{
	if (cinematic_screen_effect_globals)
	{
		cinematic_screen_effect_globals->parameters.video_on= FALSE;
		cinematic_screen_effect_globals->parameters.video_overbright_mode= 0;
		cinematic_screen_effect_globals->parameters.video_scanline_map= NULL;
		cinematic_screen_effect_globals->parameters.video_noise_intensity= 0.f;
		cinematic_screen_effect_globals->parameters.video_noise_map_scale= 0.f;
		cinematic_screen_effect_globals->parameters.video_noise_map= NULL;
		cinematic_screen_effect_globals->filter_light_enhancement_intensity[0]= light_enhancement_from;
		cinematic_screen_effect_globals->filter_light_enhancement_intensity[1]= light_enhancement_to;
		cinematic_screen_effect_globals->filter_desaturation_intensity[0]= desaturation_from;
		cinematic_screen_effect_globals->filter_desaturation_intensity[1]= desaturation_to;
		cinematic_screen_effect_globals->filter_time[0]= rasterizer_screen_effects_time();
		cinematic_screen_effect_globals->filter_time[1]= cinematic_screen_effect_globals->filter_time[0]+time;
		cinematic_screen_effect_globals->parameters.filter_desaturation_is_additive= desaturation_is_additive;
		cinematic_screen_effect_globals->parameters.filter_light_enhancement_uses_convolution_mask= FALSE;
		cinematic_screen_effect_globals->parameters.filter_desaturation_uses_convolution_mask= FALSE;
	}

	return;
}

void rasterizer_screen_effect_set_filter_desaturation_tint(
	real_rgb_color tint)
{
	if (cinematic_screen_effect_globals)
	{
		real_rgb_color *desaturation_tint= &cinematic_screen_effect_globals->parameters.filter_desaturation_tint;

		desaturation_tint->red= tint.red;
		desaturation_tint->green= tint.green;
		desaturation_tint->blue= tint.blue;
	}

	return;
}

void rasterizer_screen_effect_set_video(
	short overbright_mode,
	real noise_intensity)
{
	if (cinematic_screen_effect_globals)
	{
		match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_cinematics.c", 225, global_rasterizer_data);

		if (global_rasterizer_data->screen_effect_video_scanline_map.index!=NONE &&
			global_rasterizer_data->screen_effect_video_noise_map.index!=NONE)
		{
			memset(&cinematic_screen_effect_globals->parameters, 0, sizeof(struct rasterizer_screen_effect_parameters));
			cinematic_screen_effect_globals->convolution_radius[0]= 0.f;
			cinematic_screen_effect_globals->convolution_radius[1]= 0.f;
			cinematic_screen_effect_globals->convolution_time[0]= 0.f;
			cinematic_screen_effect_globals->convolution_time[1]= 0.f;
			cinematic_screen_effect_globals->filter_light_enhancement_intensity[0]= 0.f;
			cinematic_screen_effect_globals->filter_light_enhancement_intensity[1]= 0.f;
			cinematic_screen_effect_globals->filter_desaturation_intensity[0]= 0.f;
			cinematic_screen_effect_globals->filter_desaturation_intensity[1]= 0.f;
			cinematic_screen_effect_globals->filter_time[0]= 0.f;
			cinematic_screen_effect_globals->filter_time[1]= 0.f;
			cinematic_screen_effect_globals->parameters.video_on= TRUE;
			cinematic_screen_effect_globals->parameters.video_overbright_mode= overbright_mode;

			cinematic_screen_effect_globals->parameters.video_scanline_map= TAG_BLOCK_GET_ELEMENT(
				&((struct bitmap_group *)tag_get(BITMAP_GROUP_TAG, global_rasterizer_data->screen_effect_video_scanline_map.index))->bitmaps,
				0, struct bitmap_data);
			cinematic_screen_effect_globals->parameters.video_noise_intensity= noise_intensity;
			cinematic_screen_effect_globals->parameters.video_noise_map_scale= 1.f;

			cinematic_screen_effect_globals->parameters.video_noise_map= TAG_BLOCK_GET_ELEMENT(
				&((struct bitmap_group *)tag_get(BITMAP_GROUP_TAG, global_rasterizer_data->screen_effect_video_noise_map.index))->bitmaps,
				0, struct bitmap_data);
		}
		else
		{
			error(_error_silent, "### ERROR cinematics failed to set video mode; global bitmaps are not set");
		}
	}

	return;
}

void rasterizer_screen_effect_stop(
	void)
{
	if (cinematic_screen_effect_globals)
	{
		cinematic_screen_effect_globals->has_control= FALSE;
	}

	return;
}

struct rasterizer_screen_effect_parameters *rasterizer_screen_effect_get_cinematic_parameters(
	struct rasterizer_screen_effect_parameters *parameters)
{
	if (cinematic_screen_effect_globals && cinematic_screen_effect_globals->has_control)
	{
		real convolution_t;
		real filter_t;

		if (cinematic_screen_effect_globals->convolution_time[1]!=cinematic_screen_effect_globals->convolution_time[0])
		{
			convolution_t= PIN((rasterizer_screen_effects_time()-cinematic_screen_effect_globals->convolution_time[0])/(cinematic_screen_effect_globals->convolution_time[1]-cinematic_screen_effect_globals->convolution_time[0]), 0.f, 1.f);
		}
		else
		{
			convolution_t= 1.f;
		}

		if (cinematic_screen_effect_globals->filter_time[1]!=cinematic_screen_effect_globals->filter_time[0])
		{
			filter_t= PIN((rasterizer_screen_effects_time()-cinematic_screen_effect_globals->filter_time[0])/(cinematic_screen_effect_globals->filter_time[1]-cinematic_screen_effect_globals->filter_time[0]), 0.f, 1.f);
		}
		else
		{
			filter_t= 1.f;
		}

		scalars_interpolate(cinematic_screen_effect_globals->convolution_radius[0], cinematic_screen_effect_globals->convolution_radius[1], convolution_t,
			&cinematic_screen_effect_globals->parameters.convolution_radius);
		scalars_interpolate_and_clamp_0_to_1(cinematic_screen_effect_globals->filter_light_enhancement_intensity[0], cinematic_screen_effect_globals->filter_light_enhancement_intensity[1], filter_t,
			&cinematic_screen_effect_globals->parameters.filter_light_enhancement_intensity);
		scalars_interpolate_and_clamp_0_to_1(cinematic_screen_effect_globals->filter_desaturation_intensity[0], cinematic_screen_effect_globals->filter_desaturation_intensity[1], filter_t,
			&cinematic_screen_effect_globals->parameters.filter_desaturation_intensity);

		if (!memcmp(&cinematic_screen_effect_globals->parameters.filter_desaturation_tint, global_real_rgb_black, sizeof(real_rgb_color)))
		{
			cinematic_screen_effect_globals->parameters.filter_desaturation_tint= *global_real_rgb_green;
		}

		if (cinematic_screen_effect_globals->parameters.convolution_radius<=_real_epsilon)
		{
			cinematic_screen_effect_globals->parameters.convolution_radius= 0.f;
			cinematic_screen_effect_globals->parameters.convolution_type= 0;
			cinematic_screen_effect_globals->parameters.convolution_extra_passes= 0;
		}
		else
		{
			match_vassert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_cinematics.c", 336, main_get_window_count()<=1,
				"### FATAL_ERROR screen effects can't use convolution when main_get_window_count>1\r\nmaybe you forgot to turn off the cinematic screen effect?");
		}

		if (cinematic_screen_effect_globals->parameters.filter_light_enhancement_intensity<=_real_epsilon &&
			cinematic_screen_effect_globals->parameters.filter_desaturation_intensity<=_real_epsilon &&
			filter_t>=1.f)
		{
			cinematic_screen_effect_globals->parameters.filter_light_enhancement_intensity= 0.f;
			cinematic_screen_effect_globals->parameters.filter_desaturation_intensity= 0.f;
		}

		parameters= &cinematic_screen_effect_globals->parameters;
	}

	return parameters;
}

void rasterizer_set_near_clip_distance(
	real near_clip_distance)
{
	if (cinematic_screen_effect_globals)
	{
		cinematic_screen_effect_globals->near_clip_distance= near_clip_distance;
	}

	return;
}

real rasterizer_get_near_clip_distance(
	void)
{
	real near_clip_distance= rasterizer_global_defaults.z_near;

	if (cinematic_screen_effect_globals && cinematic_screen_effect_globals->near_clip_distance>0.f)
	{
		near_clip_distance= cinematic_screen_effect_globals->near_clip_distance;
	}

	return near_clip_distance;
}
