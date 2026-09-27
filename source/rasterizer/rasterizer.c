/*
RASTERIZER.C

symbols in this file:
0016BFE0 0040:
	_rasterizer_initialize (0000)
0016C020 0010:
	_rasterizer_reset_state (0000)
0016C030 00e0:
	_rasterizer_frame_begin (0000)
0016C110 0010:
	_rasterizer_windows_begin (0000)
0016C120 0010:
	_rasterizer_window_begin (0000)
0016C130 0010:
	_rasterizer_window_get_fog (0000)
0016C140 0010:
	_rasterizer_window_set_fog (0000)
0016C150 0010:
	_rasterizer_window_end (0000)
0016C160 0010:
	_rasterizer_windows_end (0000)
0016C170 0010:
	_rasterizer_frame_end (0000)
0016C180 0010:
	_rasterizer_present (0000)
0016C190 0010:
	_rasterizer_dispose (0000)
0016C1A0 0010:
	_rasterizer_set_vblank_callback (0000)
0016C1B0 0010:
	_rasterizer_profile_enable (0000)
0016C1C0 0010:
	_rasterizer_dynamic_triangles_new (0000)
0016C1D0 0010:
	_rasterizer_dynamic_triangles_lock (0000)
0016C1E0 0010:
	_rasterizer_dynamic_triangles_unlock (0000)
0016C1F0 0010:
	_rasterizer_dynamic_triangles_delete (0000)
0016C200 0010:
	_rasterizer_dynamic_vertices_new (0000)
0016C210 0010:
	_rasterizer_dynamic_vertices_get_type (0000)
0016C220 0010:
	_rasterizer_dynamic_vertices_lock (0000)
0016C230 0010:
	_rasterizer_dynamic_vertices_unlock (0000)
0016C240 0010:
	_rasterizer_dynamic_vertices_delete (0000)
0016C250 0010:
	_rasterizer_debug_immediate_begin (0000)
0016C260 0010:
	_rasterizer_debug_immediate_line (0000)
0016C270 0010:
	_rasterizer_debug_immediate_triangle (0000)
0016C280 0010:
	_rasterizer_debug_immediate_end (0000)
0016C290 0010:
	_rasterizer_debug_immediate_begin_screenspace (0000)
0016C2A0 0010:
	_rasterizer_debug_immediate_line_screenspace (0000)
0016C2B0 0010:
	_rasterizer_debug_immediate_linestrip_screenspace (0000)
0016C2C0 0010:
	_rasterizer_debug_immediate_end_screenspace (0000)
0016C2D0 0010:
	_rasterizer_decals_initialize (0000)
0016C2E0 0010:
	_rasterizer_decals_update_function_pointers (0000)
0016C2F0 0010:
	_rasterizer_decals_initialize_for_new_map (0000)
0016C300 0010:
	_rasterizer_decals_dispose_from_old_map (0000)
0016C310 0010:
	_rasterizer_decals_flush (0000)
0016C320 0010:
	_rasterizer_decals_dispose (0000)
0016C330 0010:
	_rasterizer_decal_vertices_new (0000)
0016C340 0010:
	_rasterizer_decal_vertices_lock (0000)
0016C350 0010:
	_rasterizer_decal_vertices_unlock (0000)
0016C360 0010:
	_rasterizer_decal_vertices_delete (0000)
0016C370 0010:
	_rasterizer_decals_begin (0000)
0016C380 0010:
	_rasterizer_decals_draw (0000)
0016C390 0010:
	_rasterizer_decals_end (0000)
0016C3A0 0010:
	_rasterizer_detail_objects_begin (0000)
0016C3B0 0010:
	_rasterizer_detail_objects_rebuild_vertices (0000)
0016C3C0 0010:
	_rasterizer_detail_objects_draw (0000)
0016C3D0 0010:
	_rasterizer_detail_objects_end (0000)
0016C3E0 0010:
	_rasterizer_screen_effect (0000)
0016C3F0 0010:
	_rasterizer_screen_flash (0000)
0016C400 0010:
	_rasterizer_model_begin (0000)
0016C410 0010:
	_rasterizer_model_draw (0000)
0016C420 0010:
	_rasterizer_model_transparent_geometry_submit (0000)
0016C430 0010:
	_rasterizer_model_end (0000)
0016C440 0010:
	_rasterizer_models_end (0000)
0016C450 0010:
	_rasterizer_environment_lightmaps_begin (0000)
0016C460 0010:
	_rasterizer_environment_lightmap_begin (0000)
0016C470 0010:
	_rasterizer_environment_lightmap_draw (0000)
0016C480 0010:
	_rasterizer_environment_lightmap_end (0000)
0016C490 0010:
	_rasterizer_environment_lightmaps_end (0000)
0016C4A0 0010:
	_rasterizer_environment_diffuse_lights_begin (0000)
0016C4B0 0010:
	_rasterizer_environment_diffuse_light_begin (0000)
0016C4C0 0010:
	_rasterizer_environment_diffuse_light_draw (0000)
0016C4D0 0010:
	_rasterizer_environment_diffuse_light_end (0000)
0016C4E0 0010:
	_rasterizer_environment_diffuse_lights_end (0000)
0016C4F0 0010:
	_rasterizer_environment_shadows_begin (0000)
0016C500 0010:
	_rasterizer_environment_shadow_begin (0000)
0016C510 0010:
	_rasterizer_environment_shadow_model_begin (0000)
0016C520 0010:
	_rasterizer_environment_shadow_model_draw (0000)
0016C530 0010:
	_rasterizer_environment_shadow_model_end (0000)
0016C540 0010:
	_rasterizer_environment_shadow_draw (0000)
0016C550 0010:
	_rasterizer_environment_shadow_end (0000)
0016C560 0010:
	_rasterizer_environment_shadows_end (0000)
0016C570 0010:
	_rasterizer_environment_diffuse_textures_begin (0000)
0016C580 0010:
	_rasterizer_environment_diffuse_texture_draw (0000)
0016C590 0010:
	_rasterizer_environment_diffuse_textures_end (0000)
0016C5A0 0010:
	_rasterizer_environment_specular_lights_begin (0000)
0016C5B0 0010:
	_rasterizer_environment_specular_light_begin (0000)
0016C5C0 0010:
	_rasterizer_environment_specular_light_draw (0000)
0016C5D0 0010:
	_rasterizer_environment_specular_light_end (0000)
0016C5E0 0010:
	_rasterizer_environment_specular_lights_end (0000)
0016C5F0 0010:
	_rasterizer_environment_specular_lightmaps_begin (0000)
0016C600 0010:
	_rasterizer_environment_specular_lightmap_begin (0000)
0016C610 0010:
	_rasterizer_environment_specular_lightmap_draw (0000)
0016C620 0010:
	_rasterizer_environment_specular_lightmap_end (0000)
0016C630 0010:
	_rasterizer_environment_specular_lightmaps_end (0000)
0016C640 0010:
	_rasterizer_environment_reflection_lightmap_masks_begin (0000)
0016C650 0010:
	_rasterizer_environment_reflection_lightmap_mask_begin (0000)
0016C660 0010:
	_rasterizer_environment_reflection_lightmap_mask_draw (0000)
0016C670 0010:
	_rasterizer_environment_reflection_lightmap_mask_end (0000)
0016C680 0010:
	_rasterizer_environment_reflection_lightmap_masks_end (0000)
0016C690 0010:
	_rasterizer_environment_reflection_mirrors_begin (0000)
0016C6A0 0010:
	_rasterizer_environment_reflection_mirror_draw (0000)
0016C6B0 0010:
	_rasterizer_environment_reflection_mirrors_end (0000)
0016C6C0 0010:
	_rasterizer_environment_reflections_begin (0000)
0016C6D0 0010:
	_rasterizer_environment_reflection_draw (0000)
0016C6E0 0010:
	_rasterizer_environment_reflections_end (0000)
0016C6F0 0010:
	_rasterizer_environment_transparent_geometry_begin (0000)
0016C700 0010:
	_rasterizer_environment_transparent_geometry_submit (0000)
0016C710 0010:
	_rasterizer_environment_transparent_geometry_end (0000)
0016C720 0010:
	_rasterizer_environment_fog_begin (0000)
0016C730 0010:
	_rasterizer_environment_fog_draw (0000)
0016C740 0010:
	_rasterizer_environment_fog_end (0000)
0016C750 0010:
	_rasterizer_environment_fog_screen_wind_get_vector (0000)
0016C760 0010:
	_rasterizer_environment_fog_screen_begin (0000)
0016C770 0010:
	_rasterizer_environment_fog_screen_draw (0000)
0016C780 0010:
	_rasterizer_environment_fog_screen_end (0000)
0016C790 0010:
	_rasterizer_hud_begin (0000)
0016C7A0 0010:
	_rasterizer_hud_end (0000)
0016C7B0 0010:
	_rasterizer_dynamic_unlit_geometry_draw (0000)
0016C7C0 0010:
	_rasterizer_dynamic_lit_geometry_draw (0000)
0016C7D0 0010:
	_rasterizer_dynamic_screen_geometry_draw (0000)
0016C7E0 0010:
	_rasterizer_dynamic_screen_geometry_add_multitexture_params_to_base (0000)
0016C7F0 0010:
	_rasterizer_psuedo_dynamic_screen_quad_draw (0000)
0016C800 0010:
	_rasterizer_widget_submit (0000)
0016C810 0010:
	_rasterizer_widget_begin (0000)
0016C820 0010:
	_rasterizer_widget_set_texture (0000)
0016C830 0010:
	_rasterizer_widget_set_tint_factor (0000)
0016C840 0010:
	_rasterizer_widget_set_zbuffer_enable (0000)
0016C850 0010:
	_rasterizer_widget_draw_sprite2d (0000)
0016C860 0010:
	_rasterizer_widget_draw_sprite3d (0000)
0016C870 0010:
	_rasterizer_widget_end (0000)
0016C880 0010:
	_rasterizer_widget_submit_occlusion_test (0000)
0016C890 0010:
	_rasterizer_widget_get_occlusion_test_result (0000)
0016C8A0 0010:
	_rasterizer_hud_motion_sensor_blip_begin (0000)
0016C8B0 0010:
	_rasterizer_hud_motion_sensor_blip_draw (0000)
0016C8C0 0010:
	_rasterizer_hud_motion_sensor_blip_end (0000)
0016C8D0 00d0:
	_rasterizer_debug_immediate_point (0000)
0016C9A0 0050:
	_rasterizer_debug_immediate_vector (0000)
0016C9F0 0110:
	_rasterizer_models_begin (0000)
0016CB00 0640:
	_rasterizer_debug_model_vertices (0000)
0029D6DC 0010:
	_rasterizer_global_defaults (0000)
0029D6EC 0030:
	??_C@_0DA@KMFNEIAD@global_rasterizer_model_ambient_@ (0000)
0029D71C 0027:
	??_C@_0CH@FLEENNB@c?3?2halo?2SOURCE?2rasterizer?2raster@ (0000)
0029D744 0029:
	??_C@_0CJ@KNCEBLOJ@rasterizer?5model?5ambient?5reflect@ (0000)
0029D770 0004:
	__real@461c4000 (0000)
0029D774 0004:
	??_C@_03LDNPNKDL@?6V?$DN?$AA@ (0000)
0029D778 0005:
	??_C@_04PEOOHEKN@?$CFd?$CFc?$AA@ (0000)
0029D780 0003:
	??_C@_02BFBNNIBM@I?$DN?$AA@ (0000)
0029D784 0029:
	??_C@_0CJ@NGJFILME@node_weight0?$DO?$DN0?40f?5?$CG?$CG?5node_weigh@ (0000)
0029D7B0 0028:
	??_C@_0CI@MOEBMMIG@node_index1?$DMskinning?9?$DOnode_matri@ (0000)
0029D7D8 0028:
	??_C@_0CI@PCCBCPIO@node_index0?$DMskinning?9?$DOnode_matri@ (0000)
0029D800 0044:
	??_C@_0EE@KEGACHLN@part?9?$DOtriangle_buffer?4type?$DN?$DN_tri@ (0000)
0030D3D8 00f4:
	_rasterizer_globals (0000)
	_rasterizer_debug_options (0068)
004662EC 0008:
	_bss_004662ec (0000)
	_global_rasterizer_model_ambient_reflection_tint (0004)
*/

/* ---------- headers */

#include "cseries.h"
#include "real_math.h"
#include "rasterizer.h"
#include "collisions.h"
#include "collision_usage.h"
#include "game_state.h"
#include "models/model_definitions.h"
#include "render/render.h"
#include "render/render_debug.h"
#include "tag_files/tag_groups.h"

/* ---------- constants */

enum
{
	MAXIMUM_DEBUG_MODEL_VERTICES = 2048,
	MAXIMUM_DEBUG_MODEL_VERTEX_INDICES = 12,
};

/* ---------- macros */

/* ---------- structures */

struct debug_model_vertex
{
	real_point3d position;
	short triangle_indices[MAXIMUM_DEBUG_MODEL_VERTEX_INDICES];
	short vertex_indices[MAXIMUM_DEBUG_MODEL_VERTEX_INDICES];
	byte triangle_index_count;
	byte vertex_index_count;
	word pad;
};

/* ---------- prototypes */

boolean _rasterizer_initialize(void);
void _rasterizer_reset_state(void);
void _rasterizer_frame_begin(const struct rasterizer_frame_begin_parameters *parameters);
boolean _rasterizer_windows_begin(void);
void _rasterizer_window_begin(const struct rasterizer_window_begin_parameters *parameters);
void _rasterizer_window_get_fog(struct render_fog *fog);
void _rasterizer_window_set_fog(struct render_fog const *fog);
void _rasterizer_window_end(void);
void _rasterizer_windows_end(void);
void _rasterizer_frame_end(void);
void _rasterizer_present(struct bitmap_data *screenshot_bitmap, const point2d *screenshot_index);
void _rasterizer_dispose(void);
void _rasterizer_set_vblank_callback(void (*callback)(unsigned long));
void _rasterizer_profile_enable(boolean enable);
long _rasterizer_dynamic_triangles_new(long count);
void *_rasterizer_dynamic_triangles_lock(long dynamic_triangle_buffer_index);
void _rasterizer_dynamic_triangles_unlock(long dynamic_triangle_buffer_index);
void _rasterizer_dynamic_triangles_delete(long dynamic_triangle_buffer_index);
long _rasterizer_dynamic_vertices_new(short type, long count);
short _rasterizer_dynamic_vertices_get_type(long dynamic_vertex_buffer_index);
void *_rasterizer_dynamic_vertices_lock(long dynamic_vertex_buffer_index);
void _rasterizer_dynamic_vertices_unlock(long dynamic_vertex_buffer_index);
void _rasterizer_dynamic_vertices_delete(long dynamic_vertex_buffer_index);
void _rasterizer_debug_immediate_begin(void);
void _rasterizer_debug_immediate_line(real_point3d const *p0, real_point3d const *p1, real_rgb_color const *color0, real_rgb_color const *color1);
void _rasterizer_debug_immediate_triangle(real_point3d const *p0, real_point3d const *p1, real_point3d const *p2, real_rgb_color const *color0, real_rgb_color const *color1, real_rgb_color const *color2);
void _rasterizer_debug_immediate_end(void);
void _rasterizer_debug_immediate_begin_screenspace(void);
void _rasterizer_debug_immediate_line_screenspace(point2d const *p0, point2d const *p1, real_rgb_color const *color0, real_rgb_color const *color1);
void _rasterizer_debug_immediate_linestrip_screenspace(point2d const *points, short point_count, real_rgb_color const *color);
void _rasterizer_debug_immediate_end_screenspace(void);
void _rasterizer_decals_initialize(void);
void _rasterizer_decals_update_function_pointers(void);
void _rasterizer_decals_initialize_for_new_map(void);
void _rasterizer_decals_dispose_from_old_map(void);
void _rasterizer_decals_flush(void);
void _rasterizer_decals_dispose(void);
long _rasterizer_decal_vertices_new(long cache_size);
void *_rasterizer_decal_vertices_lock(long cache_index, long cache_size);
void _rasterizer_decal_vertices_unlock(void);
void _rasterizer_decal_vertices_delete(long cache_index);
void _rasterizer_decals_begin(short layer);
void _rasterizer_decals_draw(short cluster_index);
void _rasterizer_decals_end(void);
void _rasterizer_detail_objects_begin(void);
void _rasterizer_detail_objects_rebuild_vertices(struct detail_object_view_data const *detail_object_view_data);
void _rasterizer_detail_objects_draw(struct detail_object_view_data const *detail_object_view_data);
void _rasterizer_detail_objects_end(void);
void _rasterizer_screen_effect(struct rasterizer_screen_effect_parameters const *parameters);
void _rasterizer_screen_flash(void);
void _rasterizer_models_begin(boolean sky);
void _rasterizer_model_begin(struct rasterizer_model_begin_parameters const *parameters);
void _rasterizer_model_draw(struct shader const *shader, short shader_permutation_index, struct triangle_buffer const *triangle_buffer, long dynamic_triangle_buffer_index, long triangle_count, struct vertex_buffer const *vertex_buffer, long dynamic_vertex_buffer_index);
void _rasterizer_model_transparent_geometry_submit(struct shader const *shader, short shader_permutation_index, struct triangle_buffer const *triangle_buffer, long dynamic_triangle_buffer_index, long triangle_count, struct vertex_buffer const *vertex_buffer, long dynamic_vertex_buffer_index, real_point3d const *centroid, struct render_sort_filth *sort_filth);
void _rasterizer_model_end(void);
void _rasterizer_models_end(void);
void _rasterizer_environment_lightmaps_begin(void);
void _rasterizer_environment_lightmap_begin(struct bitmap_data const *lightmap);
void _rasterizer_environment_lightmap_draw(struct shader const *shader, short shader_permutation_index, long dynamic_triangle_buffer_index, long first_triangle_index, long triangle_count, struct vertex_buffer const *vertex_buffer);
void _rasterizer_environment_lightmap_end(void);
void _rasterizer_environment_lightmaps_end(void);
void _rasterizer_environment_diffuse_lights_begin(void);
void _rasterizer_environment_diffuse_light_begin(long light_index);
void _rasterizer_environment_diffuse_light_draw(struct shader const *shader, short shader_permutation_index, long dynamic_triangle_buffer_index, long first_triangle_index, long triangle_count, struct vertex_buffer const *vertex_buffer);
void _rasterizer_environment_diffuse_light_end(void);
void _rasterizer_environment_diffuse_lights_end(void);
void _rasterizer_environment_shadows_begin(void);
boolean _rasterizer_environment_shadow_begin(long object_index, real_matrix4x3 const *shadow_matrix, real_rgb_color const *light_color, real object_bounding_radius, real *shadow_volume_bounding_radius);
void _rasterizer_environment_shadow_model_begin(struct rasterizer_model_begin_parameters const *parameters);
void _rasterizer_environment_shadow_model_draw(struct shader const *shader, short shader_permutation_index, struct triangle_buffer const *triangle_buffer, struct vertex_buffer const *vertex_buffer);
void _rasterizer_environment_shadow_model_end(void);
void _rasterizer_environment_shadow_draw(struct shader const *shader, short shader_permutation_index, long dynamic_triangle_buffer_index, long first_triangle_index, long triangle_count, struct vertex_buffer const *vertex_buffer);
void _rasterizer_environment_shadow_end(void);
void _rasterizer_environment_shadows_end(void);
void _rasterizer_environment_diffuse_textures_begin(void);
void _rasterizer_environment_diffuse_texture_draw(struct shader const *shader, short shader_permutation_index, long dynamic_triangle_buffer_index, long first_triangle_index, long triangle_count, struct vertex_buffer const *vertex_buffer);
void _rasterizer_environment_diffuse_textures_end(void);
void _rasterizer_environment_specular_lights_begin(void);
void _rasterizer_environment_specular_light_begin(long light_index);
void _rasterizer_environment_specular_light_draw(struct shader const *shader, short shader_permutation_index, long dynamic_triangle_buffer_index, long first_triangle_index, long triangle_count, struct vertex_buffer const *vertex_buffer);
void _rasterizer_environment_specular_light_end(void);
void _rasterizer_environment_specular_lights_end(void);
void _rasterizer_environment_specular_lightmaps_begin(void);
void _rasterizer_environment_specular_lightmap_begin(struct bitmap_data const *lightmap);
void _rasterizer_environment_specular_lightmap_draw(struct shader const *shader, short shader_permutation_index, long dynamic_triangle_buffer_index, long first_triangle_index, long triangle_count, struct vertex_buffer const *vertex_buffer);
void _rasterizer_environment_specular_lightmap_end(void);
void _rasterizer_environment_specular_lightmaps_end(void);
void _rasterizer_environment_reflection_lightmap_masks_begin(void);
void _rasterizer_environment_reflection_lightmap_mask_begin(struct bitmap_data const *lightmap);
void _rasterizer_environment_reflection_lightmap_mask_draw(struct shader const *shader, short shader_permutation_index, long dynamic_triangle_buffer_index, long first_triangle_index, long triangle_count, struct vertex_buffer const *vertex_buffer);
void _rasterizer_environment_reflection_lightmap_mask_end(void);
void _rasterizer_environment_reflection_lightmap_masks_end(void);
void _rasterizer_environment_reflection_mirrors_begin(void);
void _rasterizer_environment_reflection_mirror_draw(struct shader const *shader, short shader_permutation_index, long dynamic_triangle_buffer_index, long first_triangle_index, long triangle_count, struct vertex_buffer const *vertex_buffer);
void _rasterizer_environment_reflection_mirrors_end(void);
void _rasterizer_environment_reflections_begin(void);
void _rasterizer_environment_reflection_draw(struct shader const *shader, short shader_permutation_index, long dynamic_triangle_buffer_index, long first_triangle_index, long triangle_count, struct vertex_buffer const *vertex_buffer);
void _rasterizer_environment_reflections_end(void);
void _rasterizer_environment_transparent_geometry_begin(void);
void _rasterizer_environment_transparent_geometry_submit(struct shader const *shader, short shader_permutation_index, struct bitmap_data const *lightmap, long dynamic_triangle_buffer_index, long first_triangle_index, long triangle_count, struct vertex_buffer const *vertex_buffers, real_point3d const *centroid, real_plane3d const *plane, real_vector3d const *normal, struct render_lighting const *lighting, unsigned long geometry_flags);
void _rasterizer_environment_transparent_geometry_end(void);
void _rasterizer_environment_fog_begin(void);
void _rasterizer_environment_fog_draw(struct shader const *shader, short shader_permutation_index, long dynamic_triangle_buffer_index, long first_triangle_index, long triangle_count, struct vertex_buffer const *vertex_buffer);
void _rasterizer_environment_fog_end(void);
void _rasterizer_environment_fog_screen_wind_get_vector(short window_index, real dt, real_vector3d *wind_vector);
void _rasterizer_environment_fog_screen_begin(short pass);
void _rasterizer_environment_fog_screen_draw(struct shader const *shader, short shader_permutation_index, long dynamic_triangle_buffer_index, long first_triangle_index, long triangle_count, struct vertex_buffer const *vertex_buffer);
void _rasterizer_environment_fog_screen_end(void);
void _rasterizer_hud_begin(void);
void _rasterizer_hud_end(void);
void _rasterizer_dynamic_unlit_geometry_draw(struct shader const *shader, struct bitmap_data const *primary_map, struct render_animation const *animation, long dynamic_triangle_buffer_index, long dynamic_vertex_buffer_index, long triangle_count, real_point3d const *centroid, unsigned long geometry_flags);
void _rasterizer_dynamic_lit_geometry_draw(struct shader const *shader, struct bitmap_data const *primary_map, struct render_animation const *animation, struct render_lighting const *lighting, long dynamic_triangle_buffer_index, long dynamic_vertex_buffer_index, long triangle_count, real_point3d const *centroid, unsigned long geometry_flags);
void _rasterizer_dynamic_screen_geometry_draw(struct rasterizer_dynamic_screen_geometry_parameters const *parameters, long dynamic_triangle_buffer_index, long dynamic_vertex_buffer_index, long triangle_count);
void _rasterizer_dynamic_screen_geometry_add_multitexture_params_to_base(struct rasterizer_dynamic_screen_geometry_parameters *base, struct rasterizer_dynamic_screen_geometry_parameters const *multitexture_parameters);
void _rasterizer_psuedo_dynamic_screen_quad_draw(struct rasterizer_dynamic_screen_geometry_parameters const *parameters, struct dynamic_screen_vertex *vertices);
void _rasterizer_widget_submit(long object_index, long widget_index, real_point3d const *centroid, void (*render_proc)(long object_index, long widget_index));
void _rasterizer_widget_begin(short type, word flags);
boolean _rasterizer_widget_set_texture(short stage_index, long bitmap_group_index, short sequence_index);
void _rasterizer_widget_set_tint_factor(real tint_factor);
void _rasterizer_widget_set_zbuffer_enable(boolean zbuffer_enable);
void _rasterizer_widget_draw_sprite2d(real_point2d const *point, real radius, real_vector2d const *scale, real rotation, unsigned long color);
void _rasterizer_widget_draw_sprite3d(real_point3d const *point, real radius, real_vector2d const *scale, real rotation, unsigned long color);
void _rasterizer_widget_end(void);
long _rasterizer_widget_submit_occlusion_test(real_point3d const *point, real radius, long index);
long _rasterizer_widget_get_occlusion_test_result(long index);
void _rasterizer_hud_motion_sensor_blip_begin(void);
void _rasterizer_hud_motion_sensor_blip_draw(real_point2d const *blip_position, real fade, real radius, real_rgb_color const *blip_color, boolean custom);
void _rasterizer_hud_motion_sensor_blip_end(real_point2d const *center_point, real theta);

real_vector3d uncompress_int32_to_real_vector3d(unsigned long compressed);

/* ---------- globals */

extern struct rasterizer_window_begin_parameters global_window_parameters;

const struct rasterizer_global_defaults rasterizer_global_defaults=
{
	0.0625f,
	1024.f,
	0.01171875f,
	1024.f
};

struct rasterizer_globals_struct rasterizer_globals=
{
	FALSE,
	0,
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	0,
	{0},
	768,
	0,
	FALSE,
	{TRUE},
	0,
	0.0625f,
	1024.f,
	0.01171875f,
	1024.f
};

struct rasterizer_debug_options_struct rasterizer_debug_options=
{
	FALSE, // fps_accumulation
	0, // statistics_mode
	0, // drawing_mode
	FALSE, // wireframe_enabled
	FALSE, // debug_model_vertices_enabled
	NONE, // debug_model_lod
	FALSE, // debug_transparent_geometry_enabled
	FALSE, // debug_meter_shader_enabled
	TRUE, // draw_models
	TRUE, // draw_model_transparent_geometry
	TRUE, // draw_first_person_weapon_first
	TRUE, // stencil_mask_enabled
	2, // draw_environment
	TRUE, // draw_environment_lightmaps
	TRUE, // draw_environment_shadows
	TRUE, // draw_environment_diffuse_lights
	TRUE, // draw_environment_textures
	TRUE, // draw_environment_decals
	TRUE, // draw_environment_specular_lights
	TRUE, // draw_environment_specular_lightmaps
	TRUE, // draw_environment_reflection_lightmap_masks
	TRUE, // draw_environment_reflection_mirrors
	TRUE, // draw_environment_reflections
	TRUE, // draw_environment_transparent_geometry
	TRUE, // draw_environment_fog
	TRUE, // draw_environment_fog_screen
	TRUE, // draw_water
	TRUE, // draw_lens_flares
	TRUE, // draw_dynamic_unlit_geometry
	TRUE, // draw_dynamic_lit_geometry
	TRUE, // draw_dynamic_screen_geometry
	TRUE, // draw_hud_motion_sensor
	TRUE, // draw_detail_objects
	TRUE, // draw_debug_geometry
	FALSE, // debug_geometry_multipass
	TRUE, // fog_atmospheric_enabled
	TRUE, // fog_planar_enabled
	TRUE, // bump_mapping_enabled
	1.f, // lightmap_ambient
	0, // lightmap_mode
	0, // pad3
	TRUE, // lightmap_incident_radiosity_enabled
	TRUE, // lightmap_filtering_enabled
	0.f, // model_lighting_ambient
	TRUE, // environment_alpha_testing_enabled
	TRUE, // environment_specular_mask_enabled
	TRUE, // shadow_convolution_enabled
	FALSE, // shadow_debug_enabled
	FALSE, // water_mipmapping_enabled
	TRUE, // active_camouflage_enabled
	TRUE, // active_camouflage_multipass_enabled
	TRUE, // plasma_energy_enabled
	TRUE, // lens_flare_occlusion_enabled
	FALSE, // lens_flare_occlusion_debug
	TRUE, // lens_flare_sun_glow_enabled
	TRUE, // screen_flash_enabled
	TRUE, // screen_effects_enabled
	FALSE, // DXTC_noise_enabled
	FALSE, // soft_filter_enabled
	FALSE, // secondary_render_target_debug_enabled
	FALSE, // profile_log_enabled
	0.4f, // detail_object_screen_facing_offset_multiplier
	8, // zbias
	0.00390625f, // zoffset
	FALSE, // force_all_player_views_to_default_player
	FALSE, // safe_frame_bounds_adjust_enabled
	0, // freeze_flying_camera
	TRUE, // zsprite_enabled
	TRUE, // filthy_decal_fog_hack_enabled
	TRUE, // smart_states_enabled
	FALSE, // splitscreen_VB_optimization_enabled
	FALSE, // profile_print_locks
	0.f, // profile_objectlock_time
	1.f, // pad3_scale
};

static long bss_004662ec;
real_argb_color *global_rasterizer_model_ambient_reflection_tint= NULL;

/* ---------- public code */

boolean rasterizer_initialize(
	void)
{
	global_rasterizer_model_ambient_reflection_tint= game_state_malloc("rasterizer model ambient reflection tint", NULL, sizeof(real_argb_color));
	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer.c", 289, global_rasterizer_model_ambient_reflection_tint);

	return _rasterizer_initialize();
}

void rasterizer_reset_state(
	void)
{
	_rasterizer_reset_state();
}

void rasterizer_frame_begin(
	const struct rasterizer_frame_begin_parameters *parameters)
{
	if (rasterizer_debug_options.draw_environment<=TRUE)
	{
		rasterizer_debug_options.draw_environment_fog_screen=
			rasterizer_debug_options.draw_environment_lightmaps=
			rasterizer_debug_options.draw_environment_diffuse_lights=
			rasterizer_debug_options.draw_environment_shadows=
			rasterizer_debug_options.draw_environment_textures=
			rasterizer_debug_options.draw_environment_decals=
			rasterizer_debug_options.draw_environment_specular_lights=
			rasterizer_debug_options.draw_environment_specular_lightmaps=
			rasterizer_debug_options.draw_environment_reflection_lightmap_masks=
			rasterizer_debug_options.draw_environment_reflection_mirrors=
			rasterizer_debug_options.draw_environment_reflections=
			rasterizer_debug_options.draw_environment_transparent_geometry=
			rasterizer_debug_options.draw_environment_fog=
			rasterizer_debug_options.draw_environment;
		rasterizer_debug_options.draw_environment= 2;
	}

	if (rasterizer_globals.z_near==0.f) rasterizer_globals.z_near= rasterizer_global_defaults.z_near;
	if (rasterizer_globals.z_far==0.f) rasterizer_globals.z_far= rasterizer_global_defaults.z_far;
	if (rasterizer_globals.z_near_first_person==0.f) rasterizer_globals.z_near_first_person= rasterizer_global_defaults.z_near_first_person;
	if (rasterizer_globals.z_far_first_person==0.f) rasterizer_globals.z_far_first_person= rasterizer_global_defaults.z_far_first_person;

	_rasterizer_frame_begin(parameters);
}

boolean rasterizer_windows_begin(
	void)
{
	return _rasterizer_windows_begin();
}

void rasterizer_window_begin(
	const struct rasterizer_window_begin_parameters *parameters)
{
	_rasterizer_window_begin(parameters);
}

void rasterizer_window_get_fog(
	struct render_fog *fog)
{
	_rasterizer_window_get_fog(fog);
}

void rasterizer_window_set_fog(
	struct render_fog const *fog)
{
	_rasterizer_window_set_fog(fog);
}

void rasterizer_window_end(
	void)
{
	_rasterizer_window_end();
}

void rasterizer_windows_end(
	void)
{
	_rasterizer_windows_end();
}

void rasterizer_frame_end(
	void)
{
	_rasterizer_frame_end();
}

void rasterizer_present(
	struct bitmap_data *screenshot_bitmap,
	const point2d *screenshot_index)
{
	_rasterizer_present(screenshot_bitmap, screenshot_index);
}

void rasterizer_dispose(
	void)
{
	_rasterizer_dispose();
}

void rasterizer_set_vblank_callback(
	void (*callback)(unsigned long))
{
	_rasterizer_set_vblank_callback(callback);
}

void rasterizer_profile_enable(
	boolean enable)
{
	_rasterizer_profile_enable(enable);
}

long rasterizer_dynamic_triangles_new(
	long count)
{
	return _rasterizer_dynamic_triangles_new(count);
}

void *rasterizer_dynamic_triangles_lock(
	long dynamic_triangle_buffer_index)
{
	return _rasterizer_dynamic_triangles_lock(dynamic_triangle_buffer_index);
}

void rasterizer_dynamic_triangles_unlock(
	long dynamic_triangle_buffer_index)
{
	_rasterizer_dynamic_triangles_unlock(dynamic_triangle_buffer_index);
}

void rasterizer_dynamic_triangles_delete(
	long dynamic_triangle_buffer_index)
{
	_rasterizer_dynamic_triangles_delete(dynamic_triangle_buffer_index);
}

long rasterizer_dynamic_vertices_new(
	short type,
	long count)
{
	return _rasterizer_dynamic_vertices_new(type, count);
}

short rasterizer_dynamic_vertices_get_type(
	long dynamic_vertex_buffer_index)
{
	return _rasterizer_dynamic_vertices_get_type(dynamic_vertex_buffer_index);
}

void *rasterizer_dynamic_vertices_lock(
	long dynamic_vertex_buffer_index)
{
	return _rasterizer_dynamic_vertices_lock(dynamic_vertex_buffer_index);
}

void rasterizer_dynamic_vertices_unlock(
	long dynamic_vertex_buffer_index)
{
	_rasterizer_dynamic_vertices_unlock(dynamic_vertex_buffer_index);
}

void rasterizer_dynamic_vertices_delete(
	long dynamic_vertex_buffer_index)
{
	_rasterizer_dynamic_vertices_delete(dynamic_vertex_buffer_index);
}

void rasterizer_debug_immediate_begin(
	void)
{
	_rasterizer_debug_immediate_begin();
}

void rasterizer_debug_immediate_point(
	real_point3d const *p,
	real size,
	real_rgb_color const *color)
{
	real_point3d p0;
	real_point3d p1;

	size*= 0.5f;

	set_real_point3d(&p0, p->x-size, p->y, p->z);
	set_real_point3d(&p1, p->x+size, p->y, p->z);
	_rasterizer_debug_immediate_line(&p0, &p1, color, color);

	set_real_point3d(&p0, p->x, p->y-size, p->z);
	set_real_point3d(&p1, p->x, p->y+size, p->z);
	_rasterizer_debug_immediate_line(&p0, &p1, color, color);

	set_real_point3d(&p0, p->x, p->y, p->z-size);
	set_real_point3d(&p1, p->x, p->y, p->z+size);
	_rasterizer_debug_immediate_line(&p0, &p1, color, color);
}

void rasterizer_debug_immediate_vector(
	real_point3d const *p,
	real_vector3d const *v,
	real size,
	real_rgb_color const *color)
{
	real_point3d q;

	point_from_line3d(p, v, size, &q);
	_rasterizer_debug_immediate_line(p, &q, color, color);
}

void rasterizer_debug_immediate_line(
	real_point3d const *p0,
	real_point3d const *p1,
	real_rgb_color const *color0,
	real_rgb_color const *color1)
{
	_rasterizer_debug_immediate_line(p0, p1, color0, color1);
}

void rasterizer_debug_immediate_triangle(
	real_point3d const *p0,
	real_point3d const *p1,
	real_point3d const *p2,
	real_rgb_color const *color0,
	real_rgb_color const *color1,
	real_rgb_color const *color2)
{
	_rasterizer_debug_immediate_triangle(p0, p1, p2, color0, color1, color2);
}

void rasterizer_debug_immediate_end(
	void)
{
	_rasterizer_debug_immediate_end();
}

void rasterizer_debug_immediate_begin_screenspace(
	void)
{
	_rasterizer_debug_immediate_begin_screenspace();
}

void rasterizer_debug_immediate_line_screenspace(
	point2d const *p0,
	point2d const *p1,
	real_rgb_color const *color0,
	real_rgb_color const *color1)
{
	_rasterizer_debug_immediate_line_screenspace(p0, p1, color0, color1);
}

void rasterizer_debug_immediate_linestrip_screenspace(
	point2d const *points,
	short point_count,
	real_rgb_color const *color)
{
	_rasterizer_debug_immediate_linestrip_screenspace(points, point_count, color);
}

void rasterizer_debug_immediate_end_screenspace(
	void)
{
	_rasterizer_debug_immediate_end_screenspace();
}

void rasterizer_decals_initialize(
	void)
{
	_rasterizer_decals_initialize();
}

void rasterizer_decals_update_function_pointers(
	void)
{
	_rasterizer_decals_update_function_pointers();
}

void rasterizer_decals_initialize_for_new_map(
	void)
{
	_rasterizer_decals_initialize_for_new_map();
}

void rasterizer_decals_dispose_from_old_map(
	void)
{
	_rasterizer_decals_dispose_from_old_map();
}

void rasterizer_decals_flush(
	void)
{
	_rasterizer_decals_flush();
}

void rasterizer_decals_dispose(
	void)
{
	_rasterizer_decals_dispose();
}

long rasterizer_decal_vertices_new(
	long cache_size)
{
	return _rasterizer_decal_vertices_new(cache_size);
}

void *rasterizer_decal_vertices_lock(
	long cache_index,
	long cache_size)
{
	return _rasterizer_decal_vertices_lock(cache_index, cache_size);
}

void rasterizer_decal_vertices_unlock(
	void)
{
	_rasterizer_decal_vertices_unlock();
}

void rasterizer_decal_vertices_delete(
	long cache_index)
{
	_rasterizer_decal_vertices_delete(cache_index);
}

void rasterizer_decals_begin(
	short layer)
{
	_rasterizer_decals_begin(layer);
}

void rasterizer_decals_draw(
	short cluster_index)
{
	_rasterizer_decals_draw(cluster_index);
}

void rasterizer_decals_end(
	void)
{
	_rasterizer_decals_end();
}

void rasterizer_detail_objects_begin(
	void)
{
	_rasterizer_detail_objects_begin();
}

void rasterizer_detail_objects_rebuild_vertices(
	struct detail_object_view_data const *detail_object_view_data)
{
	_rasterizer_detail_objects_rebuild_vertices(detail_object_view_data);
}

void rasterizer_detail_objects_draw(
	struct detail_object_view_data const *detail_object_view_data)
{
	_rasterizer_detail_objects_draw(detail_object_view_data);
}

void rasterizer_detail_objects_end(
	void)
{
	_rasterizer_detail_objects_end();
}

void rasterizer_screen_effect(
	struct rasterizer_screen_effect_parameters const *parameters)
{
	_rasterizer_screen_effect(parameters);
}

void rasterizer_screen_flash(
	void)
{
	_rasterizer_screen_flash();
}

void rasterizer_models_begin(
	boolean sky)
{
	if (!sky)
	{
		real_vector3d vector;
		struct collision_result collision;

		match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer.c", 740, global_current_collision_user_depth < MAXIMUM_COLLISION_USER_STACK_DEPTH);
		global_current_collision_users[global_current_collision_user_depth++]= _collision_user_debugging;

		scale_vector3d(&global_window_parameters.camera.forward, 10000.f, &vector);
		if (collision_test_vector(0xfff80, &global_window_parameters.camera.position, &vector, render.local_player_index, &collision))
		{
			bss_004662ec= collision.object_index;
		}

		match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer.c", 756, global_current_collision_user_depth > 1);
		--global_current_collision_user_depth;
	}
	else
	{
		bss_004662ec= NONE;
	}

	_rasterizer_models_begin(sky);
}

void rasterizer_model_begin(
	struct rasterizer_model_begin_parameters const *parameters)
{
	_rasterizer_model_begin(parameters);
}

void rasterizer_model_draw(
	struct shader const *shader,
	short shader_permutation_index,
	struct triangle_buffer const *triangle_buffer,
	long dynamic_triangle_buffer_index,
	long triangle_count,
	struct vertex_buffer const *vertex_buffer,
	long dynamic_vertex_buffer_index)
{
	_rasterizer_model_draw(shader, shader_permutation_index, triangle_buffer, dynamic_triangle_buffer_index, triangle_count, vertex_buffer, dynamic_vertex_buffer_index);
}

void rasterizer_model_transparent_geometry_submit(
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
	_rasterizer_model_transparent_geometry_submit(shader, shader_permutation_index, triangle_buffer, dynamic_triangle_buffer_index, triangle_count, vertex_buffer, dynamic_vertex_buffer_index, centroid, sort_filth);
}

void rasterizer_model_end(
	void)
{
	_rasterizer_model_end();
}

void rasterizer_models_end(
	void)
{
	_rasterizer_models_end();
}

// TODO: uncompress_int32_to_real_vector3d argument pushes are scheduled after the zero initializers
void rasterizer_debug_model_vertices(
	long target_object_index,
	struct render_skinning const *skinning,
	struct gbxmodel_geometry_part const *part)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer.c", 830, part);

	if (rasterizer_debug_options.debug_model_vertices_enabled && target_object_index==bss_004662ec)
	{
		struct debug_model_vertex vertices[MAXIMUM_DEBUG_MODEL_VERTICES];
		long vertex_count= 0;
		long best_vertex_index= NONE;
		real best_distance;
		short triangle_index;
		long vertex_index;

		match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer.c", 857, part->triangle_buffer.type==_triangle_buffer_type_precompiled_strip);

		for (triangle_index= 0; triangle_index<part->triangle_buffer.count+2; triangle_index++)
		{
			word model_vertex_index= ((word *)part->triangles.address)[triangle_index];
			struct model_vertex_compressed const *vertex= (struct model_vertex_compressed *)part->compressed_vertices.address + model_vertex_index;
			short node_index0= (char)vertex->nodes[0]/3;
			real node_weight0= vertex->weights[0]/32767.f;
			short node_index1= (char)vertex->nodes[1]/3;
			real node_weight1= 1.f-node_weight0;
			real_point3d point0= {0.f, 0.f, 0.f};
			real_vector3d normal0= {0.f, 0.f, 0.f};
			real_point3d point1= {0.f, 0.f, 0.f};
			real_vector3d normal1= {0.f, 0.f, 0.f};
			real_vector3d vertex_normal= uncompress_int32_to_real_vector3d(vertex->normal);
			real_point3d point;
			real_vector3d normal;

			match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer.c", 878, node_index0<skinning->node_matrix_count);
			match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer.c", 879, node_index1<skinning->node_matrix_count);
			match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer.c", 880, node_weight0>=0.0f && node_weight0<=1.0f);

			if (node_index0>=0)
			{
				matrix4x3_transform_point(&skinning->node_matrices[node_index0], &vertex->position, &point0);
				matrix4x3_transform_vector(&skinning->node_matrices[node_index0], &vertex_normal, &normal0);
			}
			if (node_index1>=0)
			{
				matrix4x3_transform_point(&skinning->node_matrices[node_index1], &vertex->position, &point1);
				matrix4x3_transform_vector(&skinning->node_matrices[node_index1], &vertex_normal, &normal1);
			}

			set_real_point3d(&point,
				node_weight0*point0.x + node_weight1*point1.x,
				node_weight0*point0.y + node_weight1*point1.y,
				node_weight0*point0.z + node_weight1*point1.z);
			set_real_vector3d(&normal,
				node_weight0*normal0.i + node_weight1*normal1.i,
				node_weight0*normal0.j + node_weight1*normal1.j,
				node_weight0*normal0.k + node_weight1*normal1.k);
			normalize3d(&normal);

			for (vertex_index= 0; vertex_index<vertex_count; vertex_index++)
			{
				struct debug_model_vertex *debug_vertex= &vertices[vertex_index];

				if (point.x==debug_vertex->position.x && point.y==debug_vertex->position.y && point.z==debug_vertex->position.z)
				{
					short index;

					if (debug_vertex->triangle_index_count<MAXIMUM_DEBUG_MODEL_VERTEX_INDICES)
					{
						for (index= 0; index<debug_vertex->triangle_index_count && debug_vertex->triangle_indices[index]!=triangle_index; index++)
							;
						if (index==debug_vertex->triangle_index_count)
						{
							debug_vertex->triangle_indices[debug_vertex->triangle_index_count++]= triangle_index;
						}
					}
					if (debug_vertex->vertex_index_count<MAXIMUM_DEBUG_MODEL_VERTEX_INDICES)
					{
						for (index= 0; index<debug_vertex->vertex_index_count && debug_vertex->vertex_indices[index]!=model_vertex_index; index++)
							;
						if (index==debug_vertex->vertex_index_count)
						{
							debug_vertex->vertex_indices[debug_vertex->vertex_index_count++]= model_vertex_index;
						}
					}
					break;
				}
			}

			if (vertex_index==vertex_count && vertex_count<MAXIMUM_DEBUG_MODEL_VERTICES)
			{
				struct debug_model_vertex *debug_vertex= &vertices[vertex_count];
				real_vector3d direction;
				real distance;

				debug_vertex->position= point;
				debug_vertex->triangle_indices[0]= triangle_index;
				debug_vertex->vertex_indices[0]= model_vertex_index;
				debug_vertex->triangle_index_count= 1;
				debug_vertex->vertex_index_count= 1;

				vector_from_points3d(&global_window_parameters.camera.position, &point, &direction);
				normalize3d(&direction);
				distance= dot_product3d(&global_window_parameters.camera.forward, &direction);
				if (dot_product3d(&normal, &direction)<0.f && best_distance<distance || best_distance==-1.f)
				{
					best_vertex_index= vertex_index;
					best_distance= distance;
				}
				vertex_count++;
			}
		}

		for (vertex_index= 0; vertex_index<vertex_count; vertex_index++)
		{
			struct debug_model_vertex *debug_vertex= &vertices[vertex_index];

			if (vertex_index==best_vertex_index)
			{
				short index;

				csstrcpy(temporary, "I=");
				for (index= 0; index<debug_vertex->triangle_index_count; index++)
				{
					char string[256];

					sprintf(string, "%d%c", debug_vertex->triangle_indices[index], index==debug_vertex->triangle_index_count-1 ? ' ' : ',');
					csstrcat(temporary, string);
				}
				csstrcat(temporary, "\nV=");
				for (index= 0; index<debug_vertex->vertex_index_count; index++)
				{
					char string[256];

					sprintf(string, "%d%c", debug_vertex->vertex_indices[index], index==debug_vertex->vertex_index_count-1 ? ' ' : ',');
					csstrcat(temporary, string);
				}
				render_debug_point(FALSE, &debug_vertex->position, 0.03125f, global_real_argb_red);
				render_debug_string_at_point(FALSE, &debug_vertex->position, temporary, global_real_argb_yellow);
			}
			else
			{
				render_debug_point(FALSE, &debug_vertex->position, 0.03125f, global_real_argb_white);
			}
		}
	}
}

void rasterizer_environment_lightmaps_begin(
	void)
{
	_rasterizer_environment_lightmaps_begin();
}

void rasterizer_environment_lightmap_begin(
	struct bitmap_data const *lightmap)
{
	_rasterizer_environment_lightmap_begin(lightmap);
}

void rasterizer_environment_lightmap_draw(
	struct shader const *shader,
	short shader_permutation_index,
	long dynamic_triangle_buffer_index,
	long first_triangle_index,
	long triangle_count,
	struct vertex_buffer const *vertex_buffer)
{
	_rasterizer_environment_lightmap_draw(shader, shader_permutation_index, dynamic_triangle_buffer_index, first_triangle_index, triangle_count, vertex_buffer);
}

void rasterizer_environment_lightmap_end(
	void)
{
	_rasterizer_environment_lightmap_end();
}

void rasterizer_environment_lightmaps_end(
	void)
{
	_rasterizer_environment_lightmaps_end();
}

void rasterizer_environment_diffuse_lights_begin(
	void)
{
	_rasterizer_environment_diffuse_lights_begin();
}

void rasterizer_environment_diffuse_light_begin(
	long light_index)
{
	_rasterizer_environment_diffuse_light_begin(light_index);
}

void rasterizer_environment_diffuse_light_draw(
	struct shader const *shader,
	short shader_permutation_index,
	long dynamic_triangle_buffer_index,
	long first_triangle_index,
	long triangle_count,
	struct vertex_buffer const *vertex_buffer)
{
	_rasterizer_environment_diffuse_light_draw(shader, shader_permutation_index, dynamic_triangle_buffer_index, first_triangle_index, triangle_count, vertex_buffer);
}

void rasterizer_environment_diffuse_light_end(
	void)
{
	_rasterizer_environment_diffuse_light_end();
}

void rasterizer_environment_diffuse_lights_end(
	void)
{
	_rasterizer_environment_diffuse_lights_end();
}

void rasterizer_environment_shadows_begin(
	void)
{
	_rasterizer_environment_shadows_begin();
}

boolean rasterizer_environment_shadow_begin(
	long object_index,
	real_matrix4x3 const *shadow_matrix,
	real_rgb_color const *light_color,
	real object_bounding_radius,
	real *shadow_volume_bounding_radius)
{
	return _rasterizer_environment_shadow_begin(object_index, shadow_matrix, light_color, object_bounding_radius, shadow_volume_bounding_radius);
}

void rasterizer_environment_shadow_model_begin(
	struct rasterizer_model_begin_parameters const *parameters)
{
	_rasterizer_environment_shadow_model_begin(parameters);
}

void rasterizer_environment_shadow_model_draw(
	struct shader const *shader,
	short shader_permutation_index,
	struct triangle_buffer const *triangle_buffer,
	struct vertex_buffer const *vertex_buffer)
{
	_rasterizer_environment_shadow_model_draw(shader, shader_permutation_index, triangle_buffer, vertex_buffer);
}

void rasterizer_environment_shadow_model_end(
	void)
{
	_rasterizer_environment_shadow_model_end();
}

void rasterizer_environment_shadow_draw(
	struct shader const *shader,
	short shader_permutation_index,
	long dynamic_triangle_buffer_index,
	long first_triangle_index,
	long triangle_count,
	struct vertex_buffer const *vertex_buffer)
{
	_rasterizer_environment_shadow_draw(shader, shader_permutation_index, dynamic_triangle_buffer_index, first_triangle_index, triangle_count, vertex_buffer);
}

void rasterizer_environment_shadow_end(
	void)
{
	_rasterizer_environment_shadow_end();
}

void rasterizer_environment_shadows_end(
	void)
{
	_rasterizer_environment_shadows_end();
}

void rasterizer_environment_diffuse_textures_begin(
	void)
{
	_rasterizer_environment_diffuse_textures_begin();
}

void rasterizer_environment_diffuse_texture_draw(
	struct shader const *shader,
	short shader_permutation_index,
	long dynamic_triangle_buffer_index,
	long first_triangle_index,
	long triangle_count,
	struct vertex_buffer const *vertex_buffer)
{
	_rasterizer_environment_diffuse_texture_draw(shader, shader_permutation_index, dynamic_triangle_buffer_index, first_triangle_index, triangle_count, vertex_buffer);
}

void rasterizer_environment_diffuse_textures_end(
	void)
{
	_rasterizer_environment_diffuse_textures_end();
}

void rasterizer_environment_specular_lights_begin(
	void)
{
	_rasterizer_environment_specular_lights_begin();
}

void rasterizer_environment_specular_light_begin(
	long light_index)
{
	_rasterizer_environment_specular_light_begin(light_index);
}

void rasterizer_environment_specular_light_draw(
	struct shader const *shader,
	short shader_permutation_index,
	long dynamic_triangle_buffer_index,
	long first_triangle_index,
	long triangle_count,
	struct vertex_buffer const *vertex_buffer)
{
	_rasterizer_environment_specular_light_draw(shader, shader_permutation_index, dynamic_triangle_buffer_index, first_triangle_index, triangle_count, vertex_buffer);
}

void rasterizer_environment_specular_light_end(
	void)
{
	_rasterizer_environment_specular_light_end();
}

void rasterizer_environment_specular_lights_end(
	void)
{
	_rasterizer_environment_specular_lights_end();
}

void rasterizer_environment_specular_lightmaps_begin(
	void)
{
	_rasterizer_environment_specular_lightmaps_begin();
}

void rasterizer_environment_specular_lightmap_begin(
	struct bitmap_data const *lightmap)
{
	_rasterizer_environment_specular_lightmap_begin(lightmap);
}

void rasterizer_environment_specular_lightmap_draw(
	struct shader const *shader,
	short shader_permutation_index,
	long dynamic_triangle_buffer_index,
	long first_triangle_index,
	long triangle_count,
	struct vertex_buffer const *vertex_buffer)
{
	_rasterizer_environment_specular_lightmap_draw(shader, shader_permutation_index, dynamic_triangle_buffer_index, first_triangle_index, triangle_count, vertex_buffer);
}

void rasterizer_environment_specular_lightmap_end(
	void)
{
	_rasterizer_environment_specular_lightmap_end();
}

void rasterizer_environment_specular_lightmaps_end(
	void)
{
	_rasterizer_environment_specular_lightmaps_end();
}

void rasterizer_environment_reflection_lightmap_masks_begin(
	void)
{
	_rasterizer_environment_reflection_lightmap_masks_begin();
}

void rasterizer_environment_reflection_lightmap_mask_begin(
	struct bitmap_data const *lightmap)
{
	_rasterizer_environment_reflection_lightmap_mask_begin(lightmap);
}

void rasterizer_environment_reflection_lightmap_mask_draw(
	struct shader const *shader,
	short shader_permutation_index,
	long dynamic_triangle_buffer_index,
	long first_triangle_index,
	long triangle_count,
	struct vertex_buffer const *vertex_buffer)
{
	_rasterizer_environment_reflection_lightmap_mask_draw(shader, shader_permutation_index, dynamic_triangle_buffer_index, first_triangle_index, triangle_count, vertex_buffer);
}

void rasterizer_environment_reflection_lightmap_mask_end(
	void)
{
	_rasterizer_environment_reflection_lightmap_mask_end();
}

void rasterizer_environment_reflection_lightmap_masks_end(
	void)
{
	_rasterizer_environment_reflection_lightmap_masks_end();
}

void rasterizer_environment_reflection_mirrors_begin(
	void)
{
	_rasterizer_environment_reflection_mirrors_begin();
}

void rasterizer_environment_reflection_mirror_draw(
	struct shader const *shader,
	short shader_permutation_index,
	long dynamic_triangle_buffer_index,
	long first_triangle_index,
	long triangle_count,
	struct vertex_buffer const *vertex_buffer)
{
	_rasterizer_environment_reflection_mirror_draw(shader, shader_permutation_index, dynamic_triangle_buffer_index, first_triangle_index, triangle_count, vertex_buffer);
}

void rasterizer_environment_reflection_mirrors_end(
	void)
{
	_rasterizer_environment_reflection_mirrors_end();
}

void rasterizer_environment_reflections_begin(
	void)
{
	_rasterizer_environment_reflections_begin();
}

void rasterizer_environment_reflection_draw(
	struct shader const *shader,
	short shader_permutation_index,
	long dynamic_triangle_buffer_index,
	long first_triangle_index,
	long triangle_count,
	struct vertex_buffer const *vertex_buffer)
{
	_rasterizer_environment_reflection_draw(shader, shader_permutation_index, dynamic_triangle_buffer_index, first_triangle_index, triangle_count, vertex_buffer);
}

void rasterizer_environment_reflections_end(
	void)
{
	_rasterizer_environment_reflections_end();
}

void rasterizer_environment_transparent_geometry_begin(
	void)
{
	_rasterizer_environment_transparent_geometry_begin();
}

void rasterizer_environment_transparent_geometry_submit(
	struct shader const *shader,
	short shader_permutation_index,
	struct bitmap_data const *lightmap,
	long dynamic_triangle_buffer_index,
	long first_triangle_index,
	long triangle_count,
	struct vertex_buffer const *vertex_buffers,
	real_point3d const *centroid,
	real_plane3d const *plane,
	real_vector3d const *normal,
	struct render_lighting const *lighting,
	unsigned long geometry_flags)
{
	_rasterizer_environment_transparent_geometry_submit(shader, shader_permutation_index, lightmap, dynamic_triangle_buffer_index, first_triangle_index, triangle_count, vertex_buffers, centroid, plane, normal, lighting, geometry_flags);
}

void rasterizer_environment_transparent_geometry_end(
	void)
{
	_rasterizer_environment_transparent_geometry_end();
}

void rasterizer_environment_fog_begin(
	void)
{
	_rasterizer_environment_fog_begin();
}

void rasterizer_environment_fog_draw(
	struct shader const *shader,
	short shader_permutation_index,
	long dynamic_triangle_buffer_index,
	long first_triangle_index,
	long triangle_count,
	struct vertex_buffer const *vertex_buffer)
{
	_rasterizer_environment_fog_draw(shader, shader_permutation_index, dynamic_triangle_buffer_index, first_triangle_index, triangle_count, vertex_buffer);
}

void rasterizer_environment_fog_end(
	void)
{
	_rasterizer_environment_fog_end();
}

void rasterizer_environment_fog_screen_wind_get_vector(
	short window_index,
	real dt,
	real_vector3d *wind_vector)
{
	_rasterizer_environment_fog_screen_wind_get_vector(window_index, dt, wind_vector);
}

void rasterizer_environment_fog_screen_begin(
	short pass)
{
	_rasterizer_environment_fog_screen_begin(pass);
}

void rasterizer_environment_fog_screen_draw(
	struct shader const *shader,
	short shader_permutation_index,
	long dynamic_triangle_buffer_index,
	long first_triangle_index,
	long triangle_count,
	struct vertex_buffer const *vertex_buffer)
{
	_rasterizer_environment_fog_screen_draw(shader, shader_permutation_index, dynamic_triangle_buffer_index, first_triangle_index, triangle_count, vertex_buffer);
}

void rasterizer_environment_fog_screen_end(
	void)
{
	_rasterizer_environment_fog_screen_end();
}

void rasterizer_hud_begin(
	void)
{
	_rasterizer_hud_begin();
}

void rasterizer_hud_end(
	void)
{
	_rasterizer_hud_end();
}

void rasterizer_dynamic_unlit_geometry_draw(
	struct shader const *shader,
	struct bitmap_data const *primary_map,
	struct render_animation const *animation,
	long dynamic_triangle_buffer_index,
	long dynamic_vertex_buffer_index,
	long triangle_count,
	real_point3d const *centroid,
	unsigned long geometry_flags)
{
	_rasterizer_dynamic_unlit_geometry_draw(shader, primary_map, animation, dynamic_triangle_buffer_index, dynamic_vertex_buffer_index, triangle_count, centroid, geometry_flags);
}

void rasterizer_dynamic_lit_geometry_draw(
	struct shader const *shader,
	struct bitmap_data const *primary_map,
	struct render_animation const *animation,
	struct render_lighting const *lighting,
	long dynamic_triangle_buffer_index,
	long dynamic_vertex_buffer_index,
	long triangle_count,
	real_point3d const *centroid,
	unsigned long geometry_flags)
{
	_rasterizer_dynamic_lit_geometry_draw(shader, primary_map, animation, lighting, dynamic_triangle_buffer_index, dynamic_vertex_buffer_index, triangle_count, centroid, geometry_flags);
}

void rasterizer_dynamic_screen_geometry_draw(
	struct rasterizer_dynamic_screen_geometry_parameters const *parameters,
	long dynamic_triangle_buffer_index,
	long dynamic_vertex_buffer_index,
	long triangle_count)
{
	_rasterizer_dynamic_screen_geometry_draw(parameters, dynamic_triangle_buffer_index, dynamic_vertex_buffer_index, triangle_count);
}

void rasterizer_dynamic_screen_geometry_add_multitexture_params_to_base(
	struct rasterizer_dynamic_screen_geometry_parameters *base,
	struct rasterizer_dynamic_screen_geometry_parameters const *multitexture_parameters)
{
	_rasterizer_dynamic_screen_geometry_add_multitexture_params_to_base(base, multitexture_parameters);
}

void rasterizer_psuedo_dynamic_screen_quad_draw(
	struct rasterizer_dynamic_screen_geometry_parameters const *parameters,
	struct dynamic_screen_vertex *vertices)
{
	_rasterizer_psuedo_dynamic_screen_quad_draw(parameters, vertices);
}

void rasterizer_widget_submit(
	long object_index,
	long widget_index,
	real_point3d const *centroid,
	void (*render_proc)(long object_index, long widget_index))
{
	_rasterizer_widget_submit(object_index, widget_index, centroid, render_proc);
}

void rasterizer_widget_begin(
	short type,
	word flags)
{
	_rasterizer_widget_begin(type, flags);
}

boolean rasterizer_widget_set_texture(
	short stage_index,
	long bitmap_group_index,
	short sequence_index)
{
	return _rasterizer_widget_set_texture(stage_index, bitmap_group_index, sequence_index);
}

void rasterizer_widget_set_tint_factor(
	real tint_factor)
{
	_rasterizer_widget_set_tint_factor(tint_factor);
}

void rasterizer_widget_set_zbuffer_enable(
	boolean zbuffer_enable)
{
	_rasterizer_widget_set_zbuffer_enable(zbuffer_enable);
}

void rasterizer_widget_draw_sprite2d(
	real_point2d const *point,
	real radius,
	real_vector2d const *scale,
	real rotation,
	unsigned long color)
{
	_rasterizer_widget_draw_sprite2d(point, radius, scale, rotation, color);
}

void rasterizer_widget_draw_sprite3d(
	real_point3d const *point,
	real radius,
	real_vector2d const *scale,
	real rotation,
	unsigned long color)
{
	_rasterizer_widget_draw_sprite3d(point, radius, scale, rotation, color);
}

void rasterizer_widget_end(
	void)
{
	_rasterizer_widget_end();
}

long rasterizer_widget_submit_occlusion_test(
	real_point3d const *point,
	real radius,
	long index)
{
	return _rasterizer_widget_submit_occlusion_test(point, radius, index);
}

long rasterizer_widget_get_occlusion_test_result(
	long index)
{
	return _rasterizer_widget_get_occlusion_test_result(index);
}

void rasterizer_hud_motion_sensor_blip_begin(
	void)
{
	_rasterizer_hud_motion_sensor_blip_begin();
}

void rasterizer_hud_motion_sensor_blip_draw(
	real_point2d const *blip_position,
	real fade,
	real radius,
	real_rgb_color const *blip_color,
	boolean custom)
{
	_rasterizer_hud_motion_sensor_blip_draw(blip_position, fade, radius, blip_color, custom);
}

void rasterizer_hud_motion_sensor_blip_end(
	real_point2d const *center_point,
	real theta)
{
	_rasterizer_hud_motion_sensor_blip_end(center_point, theta);
}

/* ---------- private code */
