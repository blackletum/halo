/*
RASTERIZER.H

header included in hcex build.
*/

#ifndef __RASTERIZER_H
#define __RASTERIZER_H
#pragma once

/* ---------- headers */

#include "real_math.h"
#include "render_cameras.h"
#include "render/render.h"

/* ---------- constants */

enum
{
	MAXIMUM_WINDOWS = 4,
	MAXIMUM_LENS_FLARES_PER_FRAME = 1024,
	MAXIMUM_LIGHTS_PER_WINDOW = 128,
};

enum
{
	RASTERIZER_MEMORY_POOL_SIZE = 0x18000,
	RASTERIZER_MAXIMUM_TRIANGLES_PER_TRIANGLE_BUFFER = 24576,
	RASTERIZER_MAXIMUM_DEBUG_PRIMITIVES = 131072,
	RASTERIZER_MAXIMUM_DEBUG_VERTICES = 393216,
	RASTERIZER_MAXIMUM_TRANSPARENT_GEOMETRY_GROUPS = 384,
	RASTERIZER_MAXIMUM_TRANSPARENT_GEOMETRY_GROUPS2 = 32,
	RASTERIZER_MAXIMUM_DYNAMIC_TRIANGLES = 32768,
	RASTERIZER_MAXIMUM_DYNAMIC_TRIANGLE_BUFFERS = 1024,
	RASTERIZER_MAXIMUM_DYNAMIC_UNLIT_VERTICES = 8192,
	RASTERIZER_MAXIMUM_DYNAMIC_LIT_VERTICES = 2,
	RASTERIZER_MAXIMUM_DYNAMIC_SCREEN_VERTICES = 16384,
	RASTERIZER_MAXIMUM_DYNAMIC_MODEL_VERTICES = 2048,
	RASTERIZER_MAXIMUM_DYNAMIC_MODEL_PROCESSED_VERTICES = 8192,
	RASTERIZER_MAXIMUM_DYNAMIC_VERTEX_BUFFERS = 1024,
	RASTERIZER_MAXIMUM_DETAIL_OBJECTS_PER_FRAME = 4096,
	RASTERIZER_NODES_PER_MODEL_VERTEX = 2,
	RASTERIZER_MAXIMUM_NODES_PER_MODEL = 44,
	RASTERIZER_MAXIMUM_NEARBY_OPAQUE_MODEL_GEOMETRY_GROUPS_THAT_MIGHT_OBSCURE_THE_ENVIRONMENT_FOG_SCREEN_EFFECT = 1
};

enum
{
	NUMBER_OF_DYNAMIC_SCREEN_GEOMETRY_MAPS = 3,
};

enum
{
	_rasterizer_statistics_mode_none = 0,
	_rasterizer_statistics_mode_general,
	_rasterizer_statistics_mode_geometry,
	_rasterizer_statistics_mode_profile,
	_rasterizer_statistics_mode_memory,
	NUMBER_OF_RASTERIZER_STATISTICS_MODES
};

enum
{
	_rasterizer_geometry_no_sort_bit = 0,
	_rasterizer_geometry_no_queue_bit,
	_rasterizer_geometry_no_fog_bit,
	_rasterizer_geometry_no_zbuffer_bit,
	_rasterizer_geometry_sky_bit,
	_rasterizer_geometry_viewspace_bit,
	_rasterizer_geometry_atmospheric_fog_but_no_planar_fog_bit,
	_rasterizer_geometry_first_person_bit,
	_rasterizer_geometry_parts_define_local_nodes_bit,
	NUMBER_OF_RASTERIZER_GEOMETRY_FLAGS
};

enum
{
	_rasterizer_profile_clear = 0,
	_rasterizer_profile_model_sky,
	_rasterizer_profile_models,
	_rasterizer_profile_environment_lightmaps,
	_rasterizer_profile_environment_shadows,
	_rasterizer_profile_environment_diffuse_lights,
	_rasterizer_profile_environment_decals_light,
	_rasterizer_profile_environment_decals_alpha_tested,
	_rasterizer_profile_environment_textures,
	_rasterizer_profile_environment_decals_primary,
	_rasterizer_profile_environment_decals_secondary,
	_rasterizer_profile_environment_specular_lights,
	_rasterizer_profile_environment_specular_lightmaps,
	_rasterizer_profile_environment_reflection_lightmap_masks,
	_rasterizer_profile_environment_reflection_mirrors,
	_rasterizer_profile_environment_reflections,
	_rasterizer_profile_environment_transparents,
	_rasterizer_profile_environment_fog,
	_rasterizer_profile_environment_fog_screen,
	_rasterizer_profile_water,
	_rasterizer_profile_environment_decals_water,
	_rasterizer_profile_detail_objects,
	_rasterizer_profile_queued_transparents,
	_rasterizer_profile_lens_flare_occlusion_submit,
	_rasterizer_profile_lens_flare_occlusion_query,
	_rasterizer_profile_lens_flares,
	_rasterizer_profile_screen_effect,
	_rasterizer_profile_hud,
	_rasterizer_profile_screen_flash,
	NUMBER_OF_RASTERIZER_PROFILES,
};

enum
{
	_rasterizer_lock_none = 0,
	_rasterizer_lock_texture_changed,
	_rasterizer_lock_vertexbuffer_new,
	_rasterizer_lock_detail_objects,
	_rasterizer_lock_decal_update,
	_rasterizer_lock_decal_vertices,
	_rasterizer_lock_bink,
	_rasterizer_lock_ui,
	_rasterizer_lock_cinematics,
	_rasterizer_lock_koth,
	_rasterizer_lock_hud,
	_rasterizer_lock_flag,
	_rasterizer_lock_lightning,
	_rasterizer_lock_debug,
	_rasterizer_lock_text,
	_rasterizer_lock_contrail,
	_rasterizer_lock_sprite,
	_rasterizer_lock_bsp_switch
};


/* ---------- macros */

/* ---------- structures */

struct rasterizer_frame_begin_parameters
{
	real game_time_sec;
	real dt;
};

struct rasterizer_window_begin_parameters
{
	short rasterizer_target;
	short window_index;
	boolean has_mirror;
	boolean suppress_clear;
	struct render_camera camera;
	struct render_frustum frustum;
	struct render_fog fog;
	struct render_screen_flash screen_flash;
	struct render_screen_effect screen_effect;
};

struct rasterizer_global_defaults
{
	real z_near; // 0x0
	real z_far; // 0x4
	real z_near_first_person; // 0x8
	real z_far_first_person; // 0xC
};

struct rasterizer_debug_options_struct
{
	boolean fps_accumulation; // 0x0
	short statistics_mode; // 0x2
	short drawing_mode; // 0x4
	boolean wireframe_enabled; // 0x6
	boolean debug_model_vertices_enabled; // 0x7
	short debug_model_lod; // 0x8
	boolean debug_transparent_geometry_enabled; // 0xA
	boolean debug_meter_shader_enabled; // 0xB
	boolean draw_models; // 0xC
	boolean draw_model_transparent_geometry; // 0xD
	boolean draw_first_person_weapon_first; // 0xE
	boolean stencil_mask_enabled; // 0xF
	boolean draw_environment; // 0x10
	boolean draw_environment_lightmaps; // 0x11
	boolean draw_environment_shadows; // 0x12
	boolean draw_environment_diffuse_lights; // 0x13
	boolean draw_environment_textures; // 0x14
	boolean draw_environment_decals; // 0x15
	boolean draw_environment_specular_lights; // 0x16
	boolean draw_environment_specular_lightmaps; // 0x17
	boolean draw_environment_reflection_lightmap_masks; // 0x18
	boolean draw_environment_reflection_mirrors; // 0x19
	boolean draw_environment_reflections; // 0x1A
	boolean draw_environment_transparent_geometry; // 0x1B
	boolean draw_environment_fog; // 0x1C
	boolean draw_environment_fog_screen; // 0x1D
	boolean draw_water; // 0x1E
	boolean draw_lens_flares; // 0x1F
	boolean draw_dynamic_unlit_geometry; // 0x20
	boolean draw_dynamic_lit_geometry; // 0x21
	boolean draw_dynamic_screen_geometry; // 0x22
	boolean draw_hud_motion_sensor; // 0x23
	boolean draw_detail_objects; // 0x24
	boolean draw_debug_geometry; // 0x25
	boolean debug_geometry_multipass; // 0x26
	boolean fog_atmospheric_enabled; // 0x27
	boolean fog_planar_enabled; // 0x28
	boolean bump_mapping_enabled; // 0x29
	real lightmap_ambient; // 0x2C
	short lightmap_mode; // 0x30
	short pad3; // 0x32, debug texture mode (mode%1000, bitmap index = mode/1000)
	boolean lightmap_incident_radiosity_enabled; // 0x34
	boolean lightmap_filtering_enabled; // 0x35
	real model_lighting_ambient; // 0x38
	boolean environment_alpha_testing_enabled; // 0x3C
	boolean environment_specular_mask_enabled; // 0x3D
	boolean shadow_convolution_enabled; // 0x3E
	boolean shadow_debug_enabled; // 0x3F
	boolean water_mipmapping_enabled; // 0x40
	boolean active_camouflage_enabled; // 0x41
	boolean active_camouflage_multipass_enabled; // 0x42
	boolean plasma_energy_enabled; // 0x43
	boolean lens_flare_occlusion_enabled; // 0x44
	boolean lens_flare_occlusion_debug; // 0x45
	boolean lens_flare_sun_glow_enabled; // 0x46
	boolean screen_flash_enabled; // 0x47
	boolean screen_effects_enabled; // 0x48
	boolean DXTC_noise_enabled; // 0x49
	boolean soft_filter_enabled; // 0x4A
	boolean secondary_render_target_debug_enabled; // 0x4B
	boolean profile_log_enabled; // 0x4C
	real detail_object_screen_facing_offset_multiplier; // 0x50
	long zbias; // 0x54
	real zoffset; // 0x58
	boolean force_all_player_views_to_default_player; // 0x5C
	boolean safe_frame_bounds_adjust_enabled; // 0x5D
	short freeze_flying_camera; // 0x5E
	boolean zsprite_enabled; // 0x60
	boolean filthy_decal_fog_hack_enabled; // 0x61
	boolean smart_states_enabled; // 0x62
	boolean splitscreen_VB_optimization_enabled; // 0x63
	boolean profile_print_locks; // 0x64
	real profile_objectlock_time; // 0x68
	real pad3_scale; // 0x6C, debug texture scale
	real f[6]; // 0x70
	boolean transparent_pixel_counter_enabled; // 0x88
	boolean transparent_pixel_counter; // 0x89
	word pad; // 0x8A
};

struct rasterizer_geometry_statistics
{
	long vertices; // 0x0
	long triangles; // 0x4
	long primitives; // 0x8
};

struct rasterizer_transparent_geometry_statistics
{
	long vertices; // 0x0
	long triangles; // 0x4
	long triangles_maximum; // 0x8
	long primitives; // 0xC
};

struct rasterizer_frame_statistics
{
	real fps; // 0x0
	short fps_sample_count; // 0x4
	short pad; // 0x6
	real fps_average; // 0x8
	real fps_min; // 0xC
	real fps_max; // 0x10

	long permutation_counts[4]; // 0x14, fogged, normal, fast, scenery

	struct rasterizer_geometry_statistics lightmaps; // 0x24
	long shadow_count; // 0x30
	struct rasterizer_geometry_statistics shadows; // 0x34
	struct rasterizer_geometry_statistics lights; // 0x40
	struct rasterizer_geometry_statistics decals; // 0x4C
	long decal_shader_count; // 0x58
	long decal_texture_count; // 0x5C
	struct rasterizer_geometry_statistics textures; // 0x60
	struct rasterizer_geometry_statistics lights_specular; // 0x6C
	struct rasterizer_geometry_statistics lightmaps_specular; // 0x78
	struct rasterizer_geometry_statistics lightmaps_reflection_mask; // 0x84
	struct rasterizer_geometry_statistics reflections; // 0x90
	struct rasterizer_transparent_geometry_statistics transparent; // 0x9C
	struct rasterizer_geometry_statistics fog; // 0xAC
	struct rasterizer_geometry_statistics fog_screen; // 0xB8
	long fog_screen_model_count; // 0xC4
	struct rasterizer_geometry_statistics model_fog_screen; // 0xC8

	long model_count; // 0xD4
	struct rasterizer_geometry_statistics models_solid; // 0xD8
	struct rasterizer_transparent_geometry_statistics models_transparent; // 0xE4
	long model_shadow_count; // 0xF4
	struct rasterizer_geometry_statistics model_shadows; // 0xF8

	long dynamic_geometry_count; // 0x104
	long dynamic_geometry_triangles; // 0x108
	long dynamic_geometry_maximum_triangles; // 0x10C
	long dynamic_geometry_vertices; // 0x110
	long unknown114[7]; // 0x114

	long dynamic_vertex_count; // 0x130
	long dynamic_vertex_buffer_count; // 0x134
	long dynamic_triangle_count; // 0x138
	long dynamic_triangle_buffer_count; // 0x13C
	long debug_primitive_count; // 0x140
	long unknown144; // 0x144
	long dynamic_light_count; // 0x148
	long lens_flare_count; // 0x14C

	long skinning_total; // 0x150, bytes of skinning constants
	long lighting_total; // 0x154, bytes of lighting constants
	long vertex_shader_total; // 0x158, bytes of vertex shader microcode
	long pushbuffer_size; // 0x15C
	long skinning_count; // 0x160
	long lighting_count; // 0x164
	long vertex_shader_count; // 0x168
	long unknown16c; // 0x16C
};

struct rasterizer_model_begin_parameters
{
	unsigned long geometry_flags; // 0x0
	unsigned long unique_id; // 0x4
	struct render_skinning skinning; // 0x8
	struct render_lighting lighting; // 0x10
	struct render_animation animation; // 0x84
	struct render_model_effect effect; // 0x8C
	real_point3d centroid; // 0xB4
	real radius; // 0xC0
	real_vector2d base_map_scale; // 0xC4
};

struct transparent_geometry_group
{
	unsigned long geometry_flags; // 0x0
	long object_index; // 0x4
	long source_object_index; // 0x8
	struct shader const *shader; // 0xC
	short shader_permutation_index; // 0x10
	word pad; // 0x12
	struct render_model_effect effect; // 0x14
	real_vector2d model_base_map_scale; // 0x3C
	long dynamic_triangle_buffer_index; // 0x44
	struct triangle_buffer const *triangle_buffer; // 0x48
	long first_triangle_index; // 0x4C
	long triangle_count; // 0x50
	long dynamic_vertex_buffer_index; // 0x54
	struct vertex_buffer const *vertex_buffers; // 0x58
	struct bitmap_data const *lightmap; // 0x5C
	real_matrix4x3 const *node_matrices; // 0x60
	short node_matrix_count; // 0x64
	word pad1; // 0x66
	struct render_lighting const *lighting; // 0x68
	struct render_animation const *animation; // 0x6C
	real z_sort; // 0x70
	real_point3d centroid; // 0x74
	real_plane3d plane; // 0x80
	long sorted_index; // 0x90
	short prev_group_presorted_index; // 0x94
	short next_group_presorted_index; // 0x96
	long active_camouflage_transparent_source_object_index; // 0x98
	boolean sort_last; // 0x9C
	boolean cortana_hack; // 0x9D
	word pad2; // 0x9E
};

struct rasterizer_screen_effect_parameters
{
	short convolution_extra_passes; // 0x0
	short convolution_type; // 0x2
	real convolution_radius; // 0x4
	struct bitmap_data *convolution_mask; // 0x8
	real filter_light_enhancement_intensity; // 0xC
	real filter_desaturation_intensity; // 0x10
	real_rgb_color filter_desaturation_tint; // 0x14
	boolean filter_desaturation_is_additive; // 0x20
	boolean filter_light_enhancement_uses_convolution_mask; // 0x21
	boolean filter_desaturation_uses_convolution_mask; // 0x22
	boolean video_on; // 0x23
	short video_overbright_mode; // 0x24
	struct bitmap_data *video_scanline_map; // 0x28
	real video_noise_intensity; // 0x2C
	real video_noise_map_scale; // 0x30
	struct bitmap_data *video_noise_map; // 0x34
};

struct rasterizer_meter_parameters
{
	pixel32 gradient_min_color; // 0x0
	pixel32 gradient_max_color; // 0x4
	pixel32 background_color; // 0x8
	pixel32 flash_color; // 0xC
	boolean flash_color_is_negative; // 0x10
	boolean tint_mode_2; // 0x11
	pixel32 tint_color; // 0x14
	real gradient; // 0x18
};

struct rasterizer_dynamic_screen_geometry_parameters
{
	struct rasterizer_meter_parameters *meter_parameters; // 0x0
	real_vector2d *offset; // 0x4
	boolean map_anchor_screen[NUMBER_OF_DYNAMIC_SCREEN_GEOMETRY_MAPS]; // 0x8
	struct bitmap_data *map[NUMBER_OF_DYNAMIC_SCREEN_GEOMETRY_MAPS]; // 0xC
	boolean map_wrapped[NUMBER_OF_DYNAMIC_SCREEN_GEOMETRY_MAPS]; // 0x18
	real_point2d *map_offset[NUMBER_OF_DYNAMIC_SCREEN_GEOMETRY_MAPS]; // 0x1C
	real_vector2d map_scale[NUMBER_OF_DYNAMIC_SCREEN_GEOMETRY_MAPS]; // 0x28
	real_vector2d map_texture_scale[NUMBER_OF_DYNAMIC_SCREEN_GEOMETRY_MAPS]; // 0x40
	real_rgb_color *map_tint[NUMBER_OF_DYNAMIC_SCREEN_GEOMETRY_MAPS]; // 0x58
	real_argb_color plasma_fade; // 0x64
	boolean doing_plasma_effect; // 0x74
	real *map_fade[NUMBER_OF_DYNAMIC_SCREEN_GEOMETRY_MAPS]; // 0x78
	short map0_to_1_blend_function; // 0x84
	short map1_to_2_blend_function; // 0x86
	short framebuffer_blend_function; // 0x88
	boolean point_sampled; // 0x8A
};

struct rasterizer_light_submit_parameters
{
	struct point_light_definition *definition; // 0x0
	real_point3d position; // 0x4
	real_vector3d forward; // 0x10
	real_vector3d up; // 0x1C
	real_rgb_color color; // 0x28
	real radius; // 0x34
};

struct rasterizer_lights
{
	long light_count; // 0x0
	struct rasterizer_light_submit_parameters lights[MAXIMUM_LIGHTS_PER_WINDOW]; // 0x4
	long fixed_function_d3d_light_count; // 0x1C04
};

struct rasterizer_lens_flare_submit_parameters
{
	struct lens_flare_definition *definition; // 0x0
	real_point3d position; // 0x4
	unsigned long compressed_direction; // 0x10
	unsigned long compressed_up; // 0x14
	unsigned long compressed_light_color; // 0x18
	short light_identifier; // 0x1C
	short light_index; // 0x1E
	short lens_flare_index; // 0x20
	byte compressed_window_index; // 0x22
	byte compressed_light_scale; // 0x23
	long internal__occlusion_pixels; // 0x24
};

/* ---------- prototypes/RASTERIZER.C */

boolean rasterizer_initialize(void);

void rasterizer_frame_begin(const struct rasterizer_frame_begin_parameters *parameters);
boolean rasterizer_windows_begin(void);
void rasterizer_window_begin(const struct rasterizer_window_begin_parameters *parameters);

void rasterizer_window_end(void);
void rasterizer_windows_end(void);
void rasterizer_frame_end(void);

void rasterizer_present(struct bitmap_data *screenshot_bitmap, const point2d *screenshot_index);
void rasterizer_dispose(void);

void rasterizer_decals_update_function_pointers(void);

/* ---------- prototypes/RASTERIZER_XBOX_HARDWARE_BITMAPS.C */

boolean rasterizer_bitmap_new(struct bitmap_data *bitmap);
void rasterizer_bitmap_delete(struct bitmap_data *bitmap);
void rasterizer_bitmap_changed(struct bitmap_data *bitmap);

/* ---------- prototypes/RASTERIZER_TEXT.C */

void rasterizer_draw_string(union rectangle2d const *bounds, union rectangle2d const *clip, union point2d *cursor_reference, short height_adjust, char const *string);

/* ---------- prototypes/RASTERIZER_MEMORY_POOL.C */

boolean rasterizer_memory_pool_initialize(void);
void rasterizer_memory_pool_begin(void);
void *rasterizer_memory_alloc(const void *src, unsigned long size);
const void *rasterizer_memory_alloc_const(const void *src, unsigned long size);
void rasterizer_memory_pool_end(void);
void rasterizer_memory_pool_dispose(void);

/* ---------- prototypes/RASTERIZER_LIGHTS.C */

void rasterizer_lights_reset_for_new_map(void);

/* ---------- prototypes/RASTERIZER_TEXT.C */

void rasterizer_text_cache_flush(void);

/* ---------- globals */

struct rasterizer_globals_struct
{
	boolean active;
	short current_lock_operation;
	rectangle2d screen_bounds;
	rectangle2d frame_bounds;
	__int64 frame_index;
	byte __unknown20[0x18];
	short push_buffer_size; // 0x38, kilobytes
	short push_buffer_kickoff_size; // 0x3A, kilobytes
	boolean use_floating_point_zbuffer; // 0x3C
	byte __unknown3d[3];
	short refresh_rate; // 0x40
	real z_near; // 0x44
	real z_far; // 0x48
	real z_near_first_person; // 0x4C
	real z_far_first_person; // 0x50
	void *default_2d_hardware_format; // 0x54
	void *default_3d_hardware_format; // 0x58
	void *default_cm_hardware_format; // 0x5C
	short lightmap_mode; // 0x60
	byte __unknown62[6]; // 0x62
};

extern struct rasterizer_globals_struct rasterizer_globals;
extern struct rasterizer_debug_options_struct rasterizer_debug_options;
extern struct rasterizer_frame_statistics rasterizer_frame_statistics;
extern struct rasterizer_lights rasterizer_lights;

extern real_argb_color *global_rasterizer_model_ambient_reflection_tint;

/* comm. not sure where this should be */
struct rasterizer_frame_begin_parameters global_frame_parameters;

/* ---------- public code */

#endif // __RASTERIZER_H
