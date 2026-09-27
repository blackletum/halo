/*
RASTERIZER_XBOX_TRANSPARENT_GEOMETRY.C
*/

/* ---------- headers */

#include "cseries.h"
#include "cseries_windows.h"
#include "errors.h"
#include "real_math.h"
#include "rasterizer.h"
#include "rasterizer_geometry.h"
#include "xbox/rasterizer_xbox.h"
#include "tag_groups.h"
#include "hud_definitions.h"
#include "hud.h"
#include "draw_string.h"

/* ---------- constants */

enum
{
	RASTERIZER_TRANSPARENT_GEOMETRY_TEXCOORD_STREAM_SIZE = 0x2000,
	RASTERIZER_STATIC_BUFFER_USAGE = D3DUSAGE_WRITEONLY,
	RASTERIZER_STATIC_BUFFER_POOL = D3DPOOL_MANAGED,
	RASTERIZER_TRANSPARENT_GEOMETRY_VISIBILITY_TEST_INDEX = 0xFFF
};

/* ---------- structures */

// global_window_parameters is a struct rasterizer_window_begin_parameters

/* ---------- prototypes */

void rasterizer_draw_dynamic_vertices(long first_primitive_index, long primitive_count, long dynamic_vertex_buffer_index, short vertices_per_primitive);
void rasterizer_draw_dynamic_triangles_dynamic_vertices(long dynamic_triangle_buffer_index, long first_triangle_index, long triangle_count, long dynamic_vertex_buffer_index);
void rasterizer_draw_dynamic_triangles_static_vertices(long dynamic_triangle_buffer_index, long first_triangle_index, long triangle_count, struct vertex_buffer const *vertex_buffer);
void rasterizer_draw_dynamic_triangles_static_vertices2(long dynamic_triangle_buffer_index, long first_triangle_index, long triangle_count, struct vertex_buffer const *vertex_buffer0, struct vertex_buffer const *vertex_buffer1);
void rasterizer_draw_static_triangles_dynamic_vertices(struct triangle_buffer const *triangle_buffer, long first_triangle_index, long triangle_count, long dynamic_vertex_buffer_index);
void rasterizer_draw_static_triangles_static_vertices(struct triangle_buffer const *triangle_buffer, long first_triangle_index, long triangle_count, struct vertex_buffer const *vertex_buffer);

short main_get_window_count(void);
void draw_string_set_format(short style, short justification, unsigned long flags);
void draw_string_set_font(long font_index);
void rasterizer_set_stencil_mode(short stencil_mode);

real_vector4d *subtract_vectors4d(real_vector4d const *a, real_vector4d const *b, real_vector4d *result);
real_vector4d *offset_vector4d(real_vector4d const *a, real_vector4d const *vector, real scale, real_vector4d *result);

/* ---------- globals */

extern struct rasterizer_window_begin_parameters global_window_parameters;

static long local_last_source_object_index;
static IDirect3DVertexBuffer8 *rasterizer_xbox_transparent_geometry_texcoord_stream;
static boolean __test_no_more_active_camo;
static unsigned long bss_004662e4; // pixel counter total

/* ---------- public code */

void rasterizer_transparent_geometry_groups_begin(
	void)
{
	local_last_source_object_index= 0;
	__test_no_more_active_camo= FALSE;

	if (rasterizer_debug_options.transparent_pixel_counter_enabled && rasterizer_debug_options.transparent_pixel_counter && global_window_parameters.window_index!=NONE)
	{
		IDirect3DDevice8_BeginVisibilityTest(global_d3d_device);
	}
}

void rasterizer_transparent_geometry_group_draw__internal(
	struct transparent_geometry_group const *group,
	boolean has_lightmap)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_transparent_geometry.c", 109, group);

	if (group->triangle_buffer)
	{
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_transparent_geometry.c", 113, !has_lightmap);

		if (group->vertex_buffers)
		{
			rasterizer_draw_static_triangles_static_vertices(group->triangle_buffer, group->first_triangle_index, group->triangle_count, group->vertex_buffers);
		}
		else
		{
			rasterizer_draw_static_triangles_dynamic_vertices(group->triangle_buffer, group->first_triangle_index, group->triangle_count, group->dynamic_vertex_buffer_index);
		}
	}
	else if (group->vertex_buffers)
	{
		if (has_lightmap)
		{
			rasterizer_draw_dynamic_triangles_static_vertices2(group->dynamic_triangle_buffer_index, group->first_triangle_index, group->triangle_count, group->vertex_buffers, group->vertex_buffers+1);
		}
		else
		{
			rasterizer_draw_dynamic_triangles_static_vertices(group->dynamic_triangle_buffer_index, group->first_triangle_index, group->triangle_count, group->vertex_buffers);
		}
	}
	else
	{
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_transparent_geometry.c", 156, !has_lightmap);

		if (group->dynamic_triangle_buffer_index>=0)
		{
			rasterizer_draw_dynamic_triangles_dynamic_vertices(group->dynamic_triangle_buffer_index, group->first_triangle_index, group->triangle_count, group->dynamic_vertex_buffer_index);
		}
		else
		{
			short vertices_per_primitive= (short)-group->dynamic_triangle_buffer_index;
			short primitive_count;

			if (vertices_per_primitive==3 || vertices_per_primitive==4)
			{
				primitive_count= (short)(group->triangle_count/(vertices_per_primitive-2));
			}
			else
			{
				primitive_count= 1;
				match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_transparent_geometry.c", 180, group->triangle_count==vertices_per_primitive-2);
			}

			rasterizer_draw_dynamic_vertices(0, primitive_count, group->dynamic_vertex_buffer_index, vertices_per_primitive);
		}
	}
}

// TODO: rasterizer_transparent_geometry_group_draw (0x3b10 bytes) not decompiled yet; the
// out-of-line D3D inline copies (_code_00163b40 etc.) are emitted by the compiler for it

void rasterizer_transparent_geometry_groups_end(
	void)
{
	if (rasterizer_debug_options.transparent_pixel_counter_enabled && rasterizer_debug_options.transparent_pixel_counter)
	{
		boolean success= TRUE;
		unsigned long index= RASTERIZER_TRANSPARENT_GEOMETRY_VISIBILITY_TEST_INDEX;
		UINT visible_pixels= NONE;
		ULONGLONG timestamp;
		HRESULT hr;

		if (global_window_parameters.window_index==0)
		{
			bss_004662e4= 0;
		}

		D3DCALL(success, IDirect3DDevice8_EndVisibilityTest(global_d3d_device, index));
		do
		{
			hr= IDirect3DDevice8_GetVisibilityTestResult(global_d3d_device, index, &visible_pixels, &timestamp);
		}
		while (hr==D3DERR_TESTINCOMPLETE);
		D3DCALL(success, hr);

		bss_004662e4+= visible_pixels;

		if (global_window_parameters.window_index==main_get_window_count()-1)
		{
			long font_index= hud_globals->messaging.single_player_font.index;

			if (font_index!=NONE)
			{
				rectangle2d const *viewport_bounds= &global_window_parameters.camera.viewport_bounds;
				rectangle2d bounds= global_window_parameters.camera.window_bounds;
				char string[256];
				long pixel_area= (short)(viewport_bounds->y1-viewport_bounds->y0)*(short)(viewport_bounds->x1-viewport_bounds->x0);

				sprintf(string, "%.02f", (real)bss_004662e4/pixel_area);
				bounds.x0= bounds.x1-160;
				bounds.y0= bounds.y1-50;
				bounds.x1-= 50;

				draw_string_set_format(NONE, 1, 0);
				draw_string_set_color(global_real_argb_yellow);
				draw_string_set_font(font_index);
				rasterizer_set_stencil_mode(0);
				rasterizer_draw_string(&bounds, NULL, NULL, 0, string);
			}
		}

		if (!success)
		{
			error(_error_silent, "### ERROR rasterizer_transparent_geometry_groups_begin failed");
		}
	}
}

real_vector4d *subtract_vectors4d(
	real_vector4d const *a,
	real_vector4d const *b,
	real_vector4d *result)
{
	result->i= a->i-b->i;
	result->j= a->j-b->j;
	result->k= a->k-b->k;
	result->l= a->l-b->l;

	return result;
}

real_vector4d *offset_vector4d(
	real_vector4d const *a,
	real_vector4d const *vector,
	real scale,
	real_vector4d *result)
{
	result->i= a->i+scale*vector->i;
	result->j= a->j+scale*vector->j;
	result->k= a->k+scale*vector->k;
	result->l= a->l+scale*vector->l;

	return result;
}

// TODO: target uses `or al,0xff` for the 0xff texcoord bytes and `mov al,1` for the success return
boolean rasterizer_transparent_geometry_initialize_aux_buffer(
	void)
{
	boolean success= TRUE;
	byte *vertices= NULL;

	D3DCALL(success, IDirect3DDevice8_CreateVertexBuffer(global_d3d_device, RASTERIZER_TRANSPARENT_GEOMETRY_TEXCOORD_STREAM_SIZE*(2*sizeof(byte)), RASTERIZER_STATIC_BUFFER_USAGE, 0, RASTERIZER_STATIC_BUFFER_POOL, &rasterizer_xbox_transparent_geometry_texcoord_stream));
	rasterizer_globals.current_lock_operation= _rasterizer_lock_vertexbuffer_new;
	D3DCALL(success, IDirect3DVertexBuffer8_Lock(rasterizer_xbox_transparent_geometry_texcoord_stream, 0, RASTERIZER_TRANSPARENT_GEOMETRY_TEXCOORD_STREAM_SIZE*(2*sizeof(byte)), (unsigned char**)&vertices, 0));
	rasterizer_globals.current_lock_operation= _rasterizer_lock_none;

	if (success && vertices)
	{
		byte quad_texcoords[8];
		long quad_index;

		quad_texcoords[0]= 0;
		quad_texcoords[1]= 0;
		quad_texcoords[2]= 0;
		quad_texcoords[3]= UCHAR_MAX;
		quad_texcoords[4]= UCHAR_MAX;
		quad_texcoords[5]= UCHAR_MAX;
		quad_texcoords[6]= UCHAR_MAX;
		quad_texcoords[7]= 0;
		for (quad_index= 0; quad_index<RASTERIZER_TRANSPARENT_GEOMETRY_TEXCOORD_STREAM_SIZE/8; quad_index++)
		{
			memcpy(vertices, quad_texcoords, sizeof(quad_texcoords));
			vertices+= sizeof(quad_texcoords);
		}
	}
	else
	{
		success= FALSE;
		error(_error_silent, "### ERROR failed to allocate texcoord stream");
	}

	return success;
}

void rasterizer_transparent_geometry_dispose_aux_buffer(
	void)
{
	if (rasterizer_xbox_transparent_geometry_texcoord_stream)
	{
		IDirect3DVertexBuffer8_Release(rasterizer_xbox_transparent_geometry_texcoord_stream);
		rasterizer_xbox_transparent_geometry_texcoord_stream= NULL;
	}
}
