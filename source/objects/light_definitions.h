/*
LIGHT_DEFINITIONS.H

header included in hcex build.
*/

#ifndef __LIGHT_DEFINITIONS_H
#define __LIGHT_DEFINITIONS_H
#pragma once

/* ---------- headers */

#include "math/real_math.h"
#include "tag_files/tag_groups.h"

/* ---------- constants */

enum
{
	LIGHT_DEFINITION_TAG = 'ligh',
	LIGHT_DEFINITION_VERSION = 3,
	LENS_FLARE_DEFINITION_TAG = 'lens',
};

enum
{
	_lens_flare_sun_bit = 0,
	NUMBER_OF_LENS_FLARE_FLAGS
};

enum
{
	_lens_flare_occlusion_offset_direction_toward_viewer = 0,
	_lens_flare_occlusion_offset_direction_marker_forward,
	_lens_flare_occlusion_offset_direction_none,
	NUMBER_OF_LENS_FLARE_OCCLUSION_OFFSET_DIRECTIONS
};

enum
{
	_lens_flare_corona_rotation_function_none = 0,
	_lens_flare_corona_rotation_function_eye_in_light_space,
	_lens_flare_corona_rotation_function_light_in_eye_space,
	_lens_flare_corona_rotation_function_eye_to_light_in_light_space,
	_lens_flare_corona_rotation_function_eye_to_light_in_eye_space,
	NUMBER_OF_LENS_FLARE_CORONA_ROTATION_FUNCTIONS
};

enum
{
	_lens_flare_scale_function_none = 0,
	_lens_flare_scale_function_non_local_incident_angle,
	_lens_flare_scale_function_local_incident_angle,
	_lens_flare_scale_function_viewer_angle,
	NUMBER_OF_LENS_FLARE_SCALE_FUNCTIONS
};

enum
{
	_lens_flare_reflection_rotate_from_center_of_screen_bit = 0,
	_lens_flare_reflection_radius_not_scaled_by_distance_bit,
	_lens_flare_reflection_radius_scaled_by_occlusion_bit,
	_lens_flare_reflection_zbuffer_bit,
	NUMBER_OF_LENS_FLARE_REFLECTION_FLAGS
};

/* ---------- macros */

/* ---------- structures */

struct point_light_geometry_parameters
{
	real radius; // 0x0
	real radius_modifier_lower_bound; // 0x4
	real radius_modifier_upper_bound; // 0x8
	real falloff_angle; // 0xC
	real cutoff_angle; // 0x10
	real lens_flare_radius; // 0x14
	real runtime_cosine_falloff_angle; // 0x18
	real runtime_cosine_cutoff_angle; // 0x1C
	real specular_radius_multiplier; // 0x20
	real runtime_sine_cutoff_angle; // 0x24
	long unused[2]; // 0x28
}; // 0x30

struct point_light_color_parameters
{
	unsigned long interpolation_flags; // 0x0
	real_argb_color lower_bound; // 0x4
	real_argb_color upper_bound; // 0x14
	long unused[3]; // 0x24
}; // 0x30

struct point_light_gel_parameters
{
	struct tag_reference map; // 0x0
	word pad0; // 0x10
	short texture_animation_function; // 0x12
	real texture_animation_rate; // 0x14
	struct tag_reference secondary_map; // 0x18
	word pad1; // 0x28
	short yaw_function; // 0x2A
	real yaw_period; // 0x2C
	word pad2; // 0x30
	short roll_function; // 0x32
	real roll_period; // 0x34
	word pad3; // 0x38
	short pitch_function; // 0x3A
	real pitch_period; // 0x3C
	long unused[2]; // 0x40
}; // 0x48

struct point_light_lens_flare_parameters
{
	struct tag_reference reference; // 0x0
	long unused[6]; // 0x10
}; // 0x28

struct point_light_radiosity_parameters
{
	real intensity; // 0x0
	real_rgb_color color; // 0x4
	long unused[4]; // 0x10
}; // 0x20

struct point_light_effect_parameters
{
	real duration; // 0x0
	word pad; // 0x4
	short falloff_function; // 0x6
	real unused[2]; // 0x8
}; // 0x10

struct point_light_definition
{
	unsigned long flags; // 0x0
	struct point_light_geometry_parameters geometry; // 0x4
	struct point_light_color_parameters color; // 0x34
	struct point_light_gel_parameters gel; // 0x64
	struct point_light_lens_flare_parameters lens_flare; // 0xAC
	struct point_light_radiosity_parameters radiosity; // 0xD4
	struct point_light_effect_parameters effect; // 0xF4
	long unused[23]; // 0x104
}; // 0x160

struct lens_flare_reflection
{
	word flags; // 0x0
	short type; // 0x2
	short bitmap_index; // 0x4
	word pad; // 0x6
	long unused1[5]; // 0x8
	real offset; // 0x1C
	real rotation_offset; // 0x20
	long unused2[1]; // 0x24
	real radius_lower_bounds; // 0x28
	real radius_upper_bounds; // 0x2C
	short radius_scale_function; // 0x30
	word radius_pad; // 0x32
	real brightness_lower_bounds; // 0x34
	real brightness_upper_bounds; // 0x38
	short brightness_scale_function; // 0x3C
	word brightness_pad; // 0x3E
	real_argb_color tint_color; // 0x40
	real_argb_color animation_color_lower_bound; // 0x50
	real_argb_color animation_color_upper_bound; // 0x60
	word animation_flags; // 0x70
	short animation_function; // 0x72
	real animation_period; // 0x74
	real animation_phase; // 0x78
	long unused3[1]; // 0x7C
}; // 0x80

struct lens_flare_definition
{
	real falloff_angle; // 0x0
	real cutoff_angle; // 0x4
	real runtime_cosine_falloff_angle; // 0x8
	real runtime_cosine_cutoff_angle; // 0xC
	real occlusion_radius; // 0x10
	short occlusion_offset_direction; // 0x14
	word occlusion_pad; // 0x16
	real near_fade_distance; // 0x18
	real far_fade_distance; // 0x1C
	struct tag_reference primary_map; // 0x20
	word flags; // 0x30
	word pad; // 0x32
	long unused1[19]; // 0x34
	short corona_rotation_function; // 0x80
	word corona_rotation_pad; // 0x82
	real corona_rotation_function_scale; // 0x84
	long unused2[6]; // 0x88
	real_vector2d corona_radius_scale; // 0xA0
	long unused3[7]; // 0xA8
	struct tag_block reflections; // 0xC4
	long unused4[8]; // 0xD0
}; // 0xF0

/* ---------- prototypes/LIGHT_DEFINITIONS.C */

/* ---------- globals */

/* ---------- public code */

#endif // __LIGHT_DEFINITIONS_H
