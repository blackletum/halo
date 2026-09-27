/*
RASTERIZER_XBOX.H
*/

#ifndef __RASTERIZER_XBOX_H
#define __RASTERIZER_XBOX_H
#pragma once

/* ---------- headers */

#include "math/real_math.h"

/* ---------- constants */

enum
{
	NUMBER_OF_VERTEX_SHADERS= 67
};

enum
{
	_rasterizer_target_render_primary= 0,
	_rasterizer_target_render_secondary,
	_rasterizer_target_shadow_primary,
	_rasterizer_target_shadow_secondary,
	_rasterizer_target_sun_glow_primary,
	_rasterizer_target_sun_glow_secondary,
	_rasterizer_target_water,
	_rasterizer_target_render_primary_copy,
	NUMBER_OF_RASTERIZER_TARGETS
};

enum
{
	_rasterizer_stencil_mode_none= 0,
	_rasterizer_stencil_mode_write,
	_rasterizer_stencil_mode_reject,
	_rasterizer_stencil_mode_reject_invert,
	_rasterizer_stencil_mode_write_alpha_tested_decal,
	_rasterizer_stencil_mode_reject_alpha_tested_decal,
	NUMBER_OF_RASTERIZER_STENCIL_MODES
};

// vertex shader constant registers (xbox register file is -96..95)
enum
{
	VSH_CONSTANTS__TEXSCALE_OFFSET= -84,
	VSH_CONSTANTS__TEXSCALE_COUNT= 3,
	VSH_CONSTANTS__POINTLIGHT_OFFSET= -81,
	VSH_CONSTANTS__POINTLIGHT_COUNT= 5,
	VSH_CONSTANTS__TEXANIM_OFFSET= -81,
	VSH_CONSTANTS__TEXANIM_COUNT= 8,
	VSH_CONSTANTS__SHADOW_OFFSET= -81,
	VSH_CONSTANTS__SHADOW_COUNT= 5,
	VSH_CONSTANTS__EFFECT_OFFSET= -81,
	VSH_CONSTANTS__EFFECT_COUNT= 2,
	VSH_CONSTANTS__SCREENPROJ_OFFSET= -68,
	VSH_CONSTANTS__SCREENPROJ_COUNT= 5
};

/* ---------- macros */

// original name unknown
#define D3DCALL(success, call) { HRESULT result = (call); (success) = (success) && SUCCEEDED(result); if (!(success)) rasterizer_error(result, #call); }

/* ---------- structures */

struct vertex_shader_table_entry
{
	DWORD const *declaration; // 0x0
	DWORD const *code; // 0x4
	DWORD handle; // 0x8
	long size; // 0xC
};

struct rasterizer_point_light_constants
{
	real_point3d position; // 0x0
	real inverse_radius_squared; // 0xC
	real_vector3d forward; // 0x10
	real spot_falloff_coefficient_A; // 0x1C
	real_rgb_color color; // 0x20
	real spot_falloff_coefficient_B; // 0x2C
};

struct rasterizer_distant_light_constants
{
	real_vector3d forward; // 0x0
	real pad0; // 0xC
	real_rgb_color color; // 0x10
	real pad1; // 0x1C
};

// vertex shader constant block uploaded by rasterizer_set_model_lighting()
struct rasterizer_model_lighting_constants
{
	struct rasterizer_point_light_constants point_lights[2]; // 0x0, MAXIMUM_RENDERED_POINT_LIGHTS
	struct rasterizer_distant_light_constants distant_lights[2]; // 0x60, MAXIMUM_RENDERED_DISTANT_LIGHTS
	real_rgb_color ambient; // 0xA0
	real pad; // 0xAC
};

/* ---------- prototypes/RASTERIZER_XBOX.C */

boolean rasterizer_preinitialize__fill_you_up_with_the_devils_cock(void);


/* ---------- prototypes/RASTERIZER_XBOX_ERRORS.C */

void rasterizer_error(HRESULT hr, char const *format, ...);

/* ---------- prototypes/RASTERIZER_SWIZZLE.C */

void rasterizer_xbox_bitmap_swizzle2d_byte(void *destination, void const *source, short width, short height);
void rasterizer_xbox_bitmap_swizzle2d_word(void *destination, void const *source, short width, short height);
void rasterizer_xbox_bitmap_swizzle2d_long(void *destination, void const *source, short width, short height);
void rasterizer_xbox_bitmap_swizzle3d_byte(void *destination, void const *source, short width, short height, short depth);
void rasterizer_xbox_bitmap_swizzle3d_word(void *destination, void const *source, short width, short height, short depth);
void rasterizer_xbox_bitmap_swizzle3d_long(void *destination, void const *source, short width, short height, short depth);
short rasterizer_xbox_bitmap_get_max_mipmap_count(struct bitmap_data const *bitmap);
void rasterizer_xbox_bitmap_swizzle(struct bitmap_data *bitmap);
long rasterizer_xbox_bitmap_get_pixel_data_size(struct bitmap_data const *bitmap);
boolean rasterizer_xbox_bitmap_rebuild_hardware_format(struct bitmap_data *bitmap);

/* ---------- prototypes/RASTERIZER_XBOX_PROFILE.C */

void rasterizer_profile_begin(short profile);

void rasterizer_profile_end(short profile);

/* ---------- globals */

extern IDirect3DDevice8 *global_d3d_device;

/* ---------- public code */

#endif // __RASTERIZER_XBOX_H
