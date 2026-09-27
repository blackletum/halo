/*
SHADER_DEFINITIONS.H

header included in hcex build.
*/

#ifndef __SHADER_DEFINITIONS_H
#define __SHADER_DEFINITIONS_H
#pragma once

/* ---------- headers */

#include "real_math.h"
#include "tag_groups.h"

/* ---------- constants */

// the xbox build has no transparent_chicago_extended shader type
enum
{
	_shader_type_screen = 0,
	_shader_type_effect,
	_shader_type_decal,
	_shader_type_environment,
	_shader_type_model,
	_shader_type_transparent_generic,
	_shader_type_transparent_chicago,
	_shader_type_transparent_water,
	_shader_type_transparent_glass,
	_shader_type_transparent_meter,
	_shader_type_transparent_plasma,
	NUMBER_OF_SHADER_TYPES
};

enum
{
	_shader_model_detail_after_reflection_bit = 0,
	_shader_model_two_sided_bit,
	_shader_model_not_alpha_tested_bit,
	_shader_model_alpha_blended_decal_bit,
	_shader_model_true_atmospheric_fog_bit,
	_shader_model_nocull_two_sided_bit,
	NUMBER_OF_SHADER_MODEL_FLAGS
};

enum
{
	_shader_transparent_water_base_map_alpha_modulates_reflection_bit = 0,
	_shader_transparent_water_base_map_color_modulates_background_bit,
	_shader_transparent_water_atmospheric_fog_bit,
	_shader_transparent_water_draw_before_fog_bit,
	NUMBER_OF_SHADER_TRANSPARENT_WATER_FLAGS
};

/* ---------- macros */

/* ---------- structures */

struct shader_radiosity_properties
{
	word flags;
	short detail_level;
	real power;
	real_rgb_color color;
	real_rgb_color tint_color;
};

struct shader_physics_properties
{
	word flags;
	short material_type;
};

struct _shader
{
	struct shader_radiosity_properties radiosity;
	struct shader_physics_properties physics;
	short type;
	word pad;
};

struct shader
{
	struct _shader base;
};

struct shader_texture_animation
{
	short u_source;
	short u_function;
	real u_period;
	real u_phase;
	real u_scale;
	short v_source;
	short v_function;
	real v_period;
	real v_phase;
	real v_scale;
	short r_source;
	short r_function;
	real r_period;
	real r_phase;
	real r_scale;
	real_point2d r_center;
};

/* ---------- effect */

struct _shader_effect
{
	word flags;
	short framebuffer_blend_function;
	short framebuffer_fade_mode;
	word primary_map_flags;
	long unused1[7];
	struct tag_reference secondary_map;
	short secondary_map_anchor;
	word secondary_map_flags;
	struct shader_texture_animation secondary_map_animation;
	real secondary_map_radius;
	real zsprite_radius_scale;
	long unused2[5];
};

struct shader_effect
{
	struct _shader shader;
	struct _shader_effect effect;
};

/* ---------- decal */

struct _shader_decal
{
	word flags;
	short type;
	short framebuffer_blend_function;
	word pad1;
	long unused1[5];
	struct tag_reference map;
	long unused2[5];
};

struct shader_decal
{
	struct _shader shader;
	struct _shader_decal decal;
};

/* ---------- environment */

struct shader_environment_diffuse_properties
{
	word flags;
	short type;
	long unused1[6];
	struct tag_reference base_map;
	long unused2[6];
	short detail_map_function;
	short detail_pad;
	real primary_detail_map_scale;
	struct tag_reference primary_detail_map;
	real secondary_detail_map_scale;
	struct tag_reference secondary_detail_map;
	long unused3[6];
	short micro_detail_map_function;
	short micro_detail_pad;
	real micro_detail_map_scale;
	struct tag_reference micro_detail_map;
	real_rgb_color material_color;
	long unused4[3];
	real bump_map_scale;
	struct tag_reference bump_map;
	real_vector2d runtime_bump_map_scale;
	long unused5[4];
	short u_animation_function;
	short u_animation_pad;
	real u_animation_period;
	real u_animation_scale;
	short v_animation_function;
	short v_animation_pad;
	real v_animation_period;
	real v_animation_scale;
	long unused6[6];
};

struct shader_environment_self_illumination_properties
{
	word flags;
	short type;
	long unused1[6];
	real_rgb_color primary_on_color;
	real_rgb_color primary_off_color;
	short primary_animation_function;
	short primary_animation_pad;
	real primary_animation_period;
	real primary_animation_phase;
	long unused2[6];
	real_rgb_color secondary_on_color;
	real_rgb_color secondary_off_color;
	short secondary_animation_function;
	short secondary_animation_pad;
	real secondary_animation_period;
	real secondary_animation_phase;
	long unused3[6];
	real_rgb_color plasma_on_color;
	real_rgb_color plasma_off_color;
	short plasma_animation_function;
	short plasma_animation_pad;
	real plasma_animation_period;
	real plasma_animation_phase;
	long unused4[6];
	real map_scale;
	struct tag_reference map;
	long unused5[6];
};

struct shader_environment_specular_properties
{
	word flags;
	short type;
	long unused1[4];
	real brightness;
	long unused2[5];
	real_rgb_color view_perpendicular_color;
	real_rgb_color view_parallel_color;
	long unused3[4];
};

struct shader_environment_reflection_properties
{
	word flags;
	short type;
	real lightmap_brightness_scale;
	long unused1[7];
	real view_perpendicular_brightness;
	real view_parallel_brightness;
	long unused2[4];
	real mirror_index_of_refraction;
	real mirror_depth;
	long unused3[4];
	struct tag_reference map;
	long unused4[4];
};

struct _shader_environment
{
	word flags;
	short type;
	real lens_flare_spacing;
	struct tag_reference lens_flare;
	long unused[11];
	struct shader_environment_diffuse_properties diffuse;
	struct shader_environment_self_illumination_properties self_illumination;
	struct shader_environment_specular_properties specular;
	struct shader_environment_reflection_properties reflection;
};

struct shader_environment
{
	struct _shader shader;
	struct _shader_environment environment;
};

/* ---------- model */

struct _shader_model
{
	word flags;
	short type;
	long unused1[3];
	real translucency;
	long unused2[4];
	short diffuse_change_color_source;
	short pad;
	long unused3[7];
	word self_illumination_flags;
	word self_illumination_pad;
	short self_illumination_color_source;
	short self_illumination_animation_function;
	real self_illumination_animation_period;
	real_rgb_color self_illumination_animation_color_lower_bound;
	real_rgb_color self_illumination_animation_color_upper_bound;
	long unused4[3];
	real_vector2d map_scale;
	struct tag_reference base_map;
	long unused5[2];
	struct tag_reference multipurpose_map;
	long unused6[2];
	short detail_function;
	short detail_mask;
	real detail_map_scale;
	struct tag_reference detail_map;
	real detail_map_v_scale;
	long unused7[3];
	struct shader_texture_animation animation;
	long unused8[2];
	real reflection_falloff_distance;
	real reflection_cutoff_distance;
	real_argb_color reflection_view_perpendicular_color;
	real_argb_color reflection_view_parallel_color;
	struct tag_reference reflection_map;
	long unused9[4];
	real reflection_bump_map_scale;
	struct tag_reference reflection_bump_map;
	long unused10[8];
};

struct shader_model
{
	struct _shader shader;
	struct _shader_model model;
};

/* ---------- transparent_generic */

struct shader_transparent_generic_map
{
	word flags;
	short pad;
	real u_scale;
	real v_scale;
	real u_offset;
	real v_offset;
	real rotation;
	real mipmap_bias;
	struct tag_reference map;
	struct shader_texture_animation animation;
};

struct shader_transparent_generic_stage
{
	word flags;
	short pad;
	short color0_source;
	short color0_animation_function;
	real color0_animation_period;
	real_argb_color color0_animation_lower_bound;
	real_argb_color color0_animation_upper_bound;
	real_argb_color color1;

	short color_input_A;
	short color_input_A_mapping;
	short color_input_B;
	short color_input_B_mapping;
	short color_input_C;
	short color_input_C_mapping;
	short color_input_D;
	short color_input_D_mapping;

	short color_output_AB;
	short color_output_AB_function;
	short color_output_CD;
	short color_output_CD_function;
	short color_output_AB_CD_mux_sum;
	short color_output_mapping;

	short alpha_input_A;
	short alpha_input_A_mapping;
	short alpha_input_B;
	short alpha_input_B_mapping;
	short alpha_input_C;
	short alpha_input_C_mapping;
	short alpha_input_D;
	short alpha_input_D_mapping;

	short alpha_output_AB;
	short alpha_output_CD;
	short alpha_output_AB_CD_mux_sum;
	short alpha_output_mapping;
};

struct _shader_transparent_generic
{
	byte numeric_counter_limit;
	byte flags;
	short type;
	short framebuffer_blend_function;
	short framebuffer_fade_mode;
	short framebuffer_fade_source;
	short framebuffer_fade_unused;
	real lens_flare_spacing;
	struct tag_reference lens_flare;
	struct tag_block extra_layers;
	struct tag_block maps; // struct shader_transparent_generic_map
	struct tag_block stages; // struct shader_transparent_generic_stage
};

struct shader_transparent_generic
{
	struct _shader shader;
	struct _shader_transparent_generic generic;
};

/* ---------- transparent_chicago */

struct shader_transparent_chicago_map
{
	word flags;
	short type;
	long unused1[10];
	short color_function;
	short alpha_function;
	long unused2[9];
	real_vector2d scale;
	real_vector2d offset;
	real rotation;
	real mipmap_bias;
	struct tag_reference map;
	long unused3[10];
	struct shader_texture_animation animation;
};

struct _shader_transparent_chicago
{
	byte numeric_counter_limit;
	byte flags;
	short type;
	short framebuffer_blend_function;
	short framebuffer_fade_mode;
	short framebuffer_fade_source;
	short framebuffer_fade_unused;
	real lens_flare_spacing;
	struct tag_reference lens_flare;
	struct tag_block extra_layers;
	struct tag_block maps; // struct shader_transparent_chicago_map
	long extra_flags;
	long unused[2];
};

struct shader_transparent_chicago
{
	struct _shader shader;
	struct _shader_transparent_chicago chicago;
};

/* ---------- transparent_water */

struct shader_transparent_water_ripple
{
	word flags;
	short type;
	real contibution_factor;
	long unused1[8];
	real animation_angle;
	real animation_velocity;
	real_vector2d map_offset;
	short map_repeats;
	short map_index;
	long unused2[4];
};

struct _shader_transparent_water
{
	word flags;
	short type;
	long unused1[8];
	struct tag_reference base_map;
	long unused2[4];
	real_argb_color view_perpendicular_tint_color;
	real_argb_color view_parallel_tint_color;
	long unused3[4];
	struct tag_reference reflection_map;
	long unused4[4];
	real ripple_animation_angle;
	real ripple_animation_velocity;
	real ripple_scale;
	struct tag_reference ripple_maps;
	short ripple_mipmap_levels;
	short pad2;
	real ripple_mipmap_fade_factor;
	real ripple_mipmap_lod_bias;
	long unused5[16];
	struct tag_block ripples; // struct shader_transparent_water_ripple
	long unused6[4];
};

struct shader_transparent_water
{
	struct _shader shader;
	struct _shader_transparent_water water;
};

/* ---------- transparent_plasma */

struct _shader_transparent_plasma
{
	word flags;
	short type;
	short intensity_source;
	word intensity_pad;
	real intensity_exponent;
	short offset_source;
	word offset_pad;
	real offset_amount;
	real offset_exponent;
	long unused1[8];
	real_argb_color view_perpendicular_color;
	real_argb_color view_parallel_color;
	short tint_color_source;
	word tint_color_pad;
	long unused2[8];
	short thickness;
	word pad;
	long unused3[4];
	real mipmap_lod_bias;
	long primary_noise_map_animation_unused;
	real primary_noise_map_animation_period;
	real_vector3d primary_noise_map_animation_direction;
	real primary_noise_map_scale;
	struct tag_reference primary_noise_map;
	long unused4[8];
	long secondary_noise_map_animation_unused;
	real secondary_noise_map_animation_period;
	real_vector3d secondary_noise_map_animation_direction;
	real secondary_noise_map_scale;
	struct tag_reference secondary_noise_map;
	long unused5[8];
};

struct shader_transparent_plasma
{
	struct _shader shader;
	struct _shader_transparent_plasma plasma;
};

/* ---------- prototypes/SHADER_DEFINITIONS.C */

/* ---------- globals */

/* ---------- public code */

#endif // __SHADER_DEFINITIONS_H
