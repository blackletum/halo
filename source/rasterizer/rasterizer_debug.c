/*
RASTERIZER_DEBUG.C

symbols in this file:
0016D760 0070:
	_rasterizer_debug_new_primitive (0000)
0016D7D0 0090:
	_rasterizer_debug_initialize (0000)
0016D860 0020:
	_rasterizer_debug_begin (0000)
0016D880 0010:
	_rasterizer_debug_end (0000)
0016D890 00e0:
	_rasterizer_debug_dispose (0000)
0016D970 0010:
	_rasterizer_debug_test (0000)
0016D980 0060:
	_rasterizer_debug_primitive_compare (0000)
0016D9E0 0420:
	_rasterizer_debug_draw (0000)
0016DE00 0250:
	_rasterizer_debug_line_shaded (0000)
0016E050 0310:
	_rasterizer_debug_triangle_shaded (0000)
0016E360 0020:
	_rasterizer_debug_line (0000)
0016E380 0020:
	_rasterizer_debug_triangle (0000)
0029D990 002b:
	??_C@_0CL@IMCIMOMN@?$CD?$CD?$CD?5WARNING?5debug?5geometry?5buffe@ (0000)
0029D9BC 002b:
	??_C@_0CL@HKCMJLKE@?$CD?$CD?$CD?5ERROR?5failed?5to?5allocate?5deb@ (0000)
0029D9E8 002d:
	??_C@_0CN@HHLFKIED@c?3?2halo?2SOURCE?2rasterizer?2raster@ (0000)
0029DA18 0021:
	??_C@_0CB@NDEAGFJM@debug_data?4non_opaque_primitives@ (0000)
0029DA3C 0018:
	??_C@_0BI@INNMENHJ@debug_data?4opaque_lines?$AA@ (0000)
0029DA54 001c:
	??_C@_0BM@JLDDGFOM@debug_data?4opaque_triangles?$AA@ (0000)
0029DA70 0045:
	??_C@_0EF@HLJMNMGB@?$CD?$CD?$CD?5ERROR?5failed?5to?5lock?5dynamic@ (0000)
0029DAB8 0041:
	??_C@_0EB@BGLDJEMO@debug_data?4primitive_count?5?$DM?$DNRAS@ (0000)
0029DB00 004b:
	??_C@_0EL@KLLHFFMI@debug_data?4non_opaque_primitive_@ (0000)
0029DB50 0043:
	??_C@_0ED@KEPEIIND@debug_data?4opaque_line_count?5?$DM?$DNR@ (0000)
0029DB98 0047:
	??_C@_0EH@DHPFKGPL@debug_data?4opaque_triangle_count@ (0000)
0029DBE0 001d:
	??_C@_0BN@KMMBIEHE@p0?5?$CG?$CG?5p1?5?$CG?$CG?5color0?5?$CG?$CG?5color1?$AA@ (0000)
0029DC00 002d:
	??_C@_0CN@JOAFNCEE@p0?5?$CG?$CG?5p1?5?$CG?$CG?5p2?5?$CG?$CG?5color0?5?$CG?$CG?5colo@ (0000)
004662F8 0021:
	_debug_data (0000)
	?bss_00466318@?1??rasterizer_debug_new_primitive@@9@9 (0020)
*/

/* ---------- headers */

#include "cseries.h"
#include "errors.h"
#include "real_math.h"
#include "integer_math.h"
#include "rasterizer.h"

/* ---------- constants */

enum
{
	MAXIMUM_DEBUG_PRIMITIVES = 8192,
	MAXIMUM_VERTICES_PER_DEBUG_PRIMITIVE = 3,
};

/* ---------- macros */

/* ---------- structures */

struct rasterizer_debug_vertex
{
	real_point3d position;
	pixel32 color;
};

struct rasterizer_debug_primitive
{
	struct rasterizer_debug_vertex vertices[MAXIMUM_VERTICES_PER_DEBUG_PRIMITIVE];
	short vertex_count;
	real distance;
	boolean opaque;
};

struct rasterizer_debug_data
{
	boolean initialized;
	struct rasterizer_debug_primitive *opaque_triangles;
	long opaque_triangle_count;
	struct rasterizer_debug_primitive *opaque_lines;
	long opaque_line_count;
	struct rasterizer_debug_primitive *non_opaque_primitives;
	long non_opaque_primitive_count;
	long primitive_count;
};

/* ---------- prototypes */

long rasterizer_dynamic_vertices_new(short type, long count);
void *rasterizer_dynamic_vertices_lock(long dynamic_vertex_buffer_index);
void rasterizer_dynamic_vertices_unlock(long dynamic_vertex_buffer_index);
void rasterizer_dynamic_vertices_delete(long dynamic_vertex_buffer_index);
void rasterizer_draw_dynamic_vertices(long first_primitive_index, long primitive_count, long dynamic_vertex_buffer_index, short vertices_per_primitive);
// the second parameter is ignored by the xbox implementation
void rasterizer_debug_drawing_begin(boolean opaque, long zbias);
void rasterizer_debug_drawing_end(void);
pixel32 real_argb_color_to_pixel32(real_argb_color const *color);

void rasterizer_debug_line_shaded(real_point3d const *p0, real_point3d const *p1, real_argb_color const *color0, real_argb_color const *color1);
void rasterizer_debug_triangle_shaded(real_point3d const *p0, real_point3d const *p1, real_point3d const *p2, real_argb_color const *color0, real_argb_color const *color1, real_argb_color const *color2);

static int rasterizer_debug_primitive_compare(const void *a, const void *b);

/* ---------- globals */

extern struct rasterizer_window_begin_parameters global_window_parameters;

// real name is debug_data (see assert strings)
static struct rasterizer_debug_data debug_data;

/* ---------- public code */

long rasterizer_debug_new_primitive(
	long *count)
{
	static boolean bss_00466318= FALSE;
	long primitive_index= NONE;

	if (*count<MAXIMUM_DEBUG_PRIMITIVES && debug_data.primitive_count<MAXIMUM_DEBUG_PRIMITIVES)
	{
		primitive_index= (*count)++;
		debug_data.primitive_count++;

		if (rasterizer_debug_options.statistics_mode==_rasterizer_statistics_mode_geometry)
		{
			rasterizer_frame_statistics.debug_primitive_count++;
		}
	}
	else
	{
		if (!bss_00466318)
		{
			error(_error_silent, "### WARNING debug geometry buffer overflow");
			bss_00466318= TRUE;
		}
	}

	return primitive_index;
}

boolean rasterizer_debug_initialize(
	void)
{
	boolean success= TRUE;

	debug_data.opaque_triangles= match_malloc("c:\\halo\\SOURCE\\rasterizer\\rasterizer_debug.c", 96, MAXIMUM_DEBUG_PRIMITIVES*sizeof(struct rasterizer_debug_primitive));
	debug_data.opaque_lines= match_malloc("c:\\halo\\SOURCE\\rasterizer\\rasterizer_debug.c", 97, MAXIMUM_DEBUG_PRIMITIVES*sizeof(struct rasterizer_debug_primitive));
	debug_data.non_opaque_primitives= match_malloc("c:\\halo\\SOURCE\\rasterizer\\rasterizer_debug.c", 98, MAXIMUM_DEBUG_PRIMITIVES*sizeof(struct rasterizer_debug_primitive));

	if (debug_data.opaque_triangles && debug_data.opaque_lines && debug_data.non_opaque_primitives)
	{
		debug_data.initialized= success;
	}
	else
	{
		error(_error_silent, "### ERROR failed to allocate debug buffers");
		success= FALSE;
		debug_data.initialized= success;
	}

	return success;
}

void rasterizer_debug_begin(
	void)
{
	debug_data.opaque_triangle_count= 0;
	debug_data.opaque_line_count= 0;
	debug_data.non_opaque_primitive_count= 0;
	debug_data.primitive_count= 0;

	return;
}

void rasterizer_debug_end(
	void)
{
	return;
}

void rasterizer_debug_dispose(
	void)
{
	if (debug_data.initialized)
	{
		match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_debug.c", 137, debug_data.opaque_triangles);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_debug.c", 138, debug_data.opaque_lines);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_debug.c", 139, debug_data.non_opaque_primitives);

		match_free("c:\\halo\\SOURCE\\rasterizer\\rasterizer_debug.c", 141, debug_data.opaque_triangles);
		match_free("c:\\halo\\SOURCE\\rasterizer\\rasterizer_debug.c", 142, debug_data.opaque_lines);
		match_free("c:\\halo\\SOURCE\\rasterizer\\rasterizer_debug.c", 143, debug_data.non_opaque_primitives);
		debug_data.initialized= FALSE;
	}

	return;
}

void rasterizer_debug_line(
	real_point3d const *p0,
	real_point3d const *p1,
	real_argb_color const *color)
{
	rasterizer_debug_line_shaded(p0, p1, color, color);

	return;
}

void rasterizer_debug_line_shaded(
	real_point3d const *p0,
	real_point3d const *p1,
	real_argb_color const *color0,
	real_argb_color const *color1)
{
	if (debug_data.initialized && rasterizer_debug_options.draw_debug_geometry)
	{
		match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_debug.c", 171, p0 && p1 && color0 && color1);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_debug.c", 172, debug_data.opaque_triangles);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_debug.c", 173, debug_data.opaque_lines);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_debug.c", 174, debug_data.non_opaque_primitives);

		if (color0->alpha>0.f || color1->alpha>0.f)
		{
			boolean opaque;
			long *count;
			long primitive_index;

			if (color0->alpha==1.f && color1->alpha==1.f)
			{
				opaque= TRUE;
				count= &debug_data.opaque_line_count;
			}
			else
			{
				opaque= FALSE;
				count= &debug_data.non_opaque_primitive_count;
			}

			primitive_index= rasterizer_debug_new_primitive(count);
			if (primitive_index!=NONE)
			{
				struct rasterizer_debug_primitive *primitive= opaque ?
					&debug_data.opaque_lines[primitive_index] :
					&debug_data.non_opaque_primitives[primitive_index];
				real_vector3d v0, v1;
				real d0, d1;

				vector_from_points3d(p0, &global_window_parameters.camera.position, &v0);
				vector_from_points3d(p1, &global_window_parameters.camera.position, &v1);

				primitive->vertex_count= 2;
				primitive->vertices[0].position= *p0;
				primitive->vertices[1].position= *p1;
				primitive->vertices[0].color= real_argb_color_to_pixel32(color0);
				primitive->vertices[1].color= real_argb_color_to_pixel32(color1);
				d0= dot_product3d(&global_window_parameters.camera.forward, &v0);
				d1= dot_product3d(&global_window_parameters.camera.forward, &v1);
				primitive->distance= MIN(d0, d1);
				primitive->opaque= opaque;
			}
		}
	}

	return;
}

void rasterizer_debug_triangle(
	real_point3d const *p0,
	real_point3d const *p1,
	real_point3d const *p2,
	real_argb_color const *color)
{
	rasterizer_debug_triangle_shaded(p0, p1, p2, color, color, color);

	return;
}

void rasterizer_debug_triangle_shaded(
	real_point3d const *p0,
	real_point3d const *p1,
	real_point3d const *p2,
	real_argb_color const *color0,
	real_argb_color const *color1,
	real_argb_color const *color2)
{
	if (debug_data.initialized && rasterizer_debug_options.draw_debug_geometry)
	{
		match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_debug.c", 229, p0 && p1 && p2 && color0 && color1 && color2);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_debug.c", 230, debug_data.opaque_triangles);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_debug.c", 231, debug_data.opaque_lines);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_debug.c", 232, debug_data.non_opaque_primitives);

		if (color0->alpha>0.f || color1->alpha>0.f || color2->alpha>0.f)
		{
			boolean opaque;
			long *count;
			long primitive_index;

			if (color0->alpha==1.f && color1->alpha==1.f && color2->alpha==1.f)
			{
				opaque= TRUE;
				count= &debug_data.opaque_triangle_count;
			}
			else
			{
				opaque= FALSE;
				count= &debug_data.non_opaque_primitive_count;
			}

			primitive_index= rasterizer_debug_new_primitive(count);
			if (primitive_index!=NONE)
			{
				struct rasterizer_debug_primitive *primitive= opaque ?
					&debug_data.opaque_triangles[primitive_index] :
					&debug_data.non_opaque_primitives[primitive_index];
				real_vector3d v0, v1, v2;

				vector_from_points3d(p0, &global_window_parameters.camera.position, &v0);
				vector_from_points3d(p1, &global_window_parameters.camera.position, &v1);
				vector_from_points3d(p2, &global_window_parameters.camera.position, &v2);

				primitive->vertex_count= 3;
				primitive->vertices[0].position= *p0;
				primitive->vertices[1].position= *p1;
				primitive->vertices[2].position= *p2;
				primitive->vertices[0].color= real_argb_color_to_pixel32(color0);
				primitive->vertices[1].color= real_argb_color_to_pixel32(color1);
				primitive->vertices[2].color= real_argb_color_to_pixel32(color2);
				primitive->distance= MIN(dot_product3d(&global_window_parameters.camera.forward, &v0), MIN(dot_product3d(&global_window_parameters.camera.forward, &v1), dot_product3d(&global_window_parameters.camera.forward, &v2)));
				primitive->opaque= opaque;
			}
		}
	}

	return;
}

void rasterizer_debug_test(
	void)
{
	return;
}

static int rasterizer_debug_primitive_compare(
	const void *a,
	const void *b)
{
	struct rasterizer_debug_primitive const *primitive0= a;
	struct rasterizer_debug_primitive const *primitive1= b;
	int result= 0;

	if (primitive0->opaque || primitive1->opaque)
	{
		if (primitive0->opaque)
		{
			result-= primitive0->vertex_count;
		}
		if (primitive1->opaque)
		{
			result+= primitive1->vertex_count;
		}
	}
	else
	{
		if (primitive0->distance>primitive1->distance)
		{
			result= 1;
		}
		if (primitive0->distance<primitive1->distance)
		{
			result= -1;
		}
	}

	return result;
}

void rasterizer_debug_draw(
	void)
{
	boolean success= TRUE;

	if (debug_data.initialized && debug_data.primitive_count>0 && rasterizer_debug_options.draw_debug_geometry)
	{
		long primitive_index;

		match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_debug.c", 320, debug_data.opaque_triangles);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_debug.c", 321, debug_data.opaque_lines);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_debug.c", 322, debug_data.non_opaque_primitives);
		if (!(debug_data.opaque_triangle_count<=MAXIMUM_DEBUG_PRIMITIVES)) { display_assert("debug_data.opaque_triangle_count <=RASTERIZER_MAXIMUM_DEBUG_PRIMITIVES", "c:\\halo\\SOURCE\\rasterizer\\rasterizer_debug.c", 323, TRUE); system_exit(-1); }
		if (!(debug_data.opaque_line_count<=MAXIMUM_DEBUG_PRIMITIVES)) { display_assert("debug_data.opaque_line_count <=RASTERIZER_MAXIMUM_DEBUG_PRIMITIVES", "c:\\halo\\SOURCE\\rasterizer\\rasterizer_debug.c", 324, TRUE); system_exit(-1); }
		if (!(debug_data.non_opaque_primitive_count<=MAXIMUM_DEBUG_PRIMITIVES)) { display_assert("debug_data.non_opaque_primitive_count<=RASTERIZER_MAXIMUM_DEBUG_PRIMITIVES", "c:\\halo\\SOURCE\\rasterizer\\rasterizer_debug.c", 325, TRUE); system_exit(-1); }
		if (!(debug_data.primitive_count<=MAXIMUM_DEBUG_PRIMITIVES)) { display_assert("debug_data.primitive_count <=RASTERIZER_MAXIMUM_DEBUG_PRIMITIVES", "c:\\halo\\SOURCE\\rasterizer\\rasterizer_debug.c", 326, TRUE); system_exit(-1); }

		qsort(debug_data.non_opaque_primitives, debug_data.non_opaque_primitive_count, sizeof(struct rasterizer_debug_primitive), rasterizer_debug_primitive_compare);

		rasterizer_globals.current_lock_operation= _rasterizer_lock_debug;

		if (debug_data.opaque_triangle_count>0)
		{
			long dynamic_vertex_buffer_index= rasterizer_dynamic_vertices_new(9, 3*debug_data.opaque_triangle_count);

			if (dynamic_vertex_buffer_index!=NONE)
			{
				struct rasterizer_debug_vertex *vertices= rasterizer_dynamic_vertices_lock(dynamic_vertex_buffer_index);

				if (vertices)
				{
					long vertex_index= 0;
					long primitive_count= debug_data.opaque_triangle_count;

					for (primitive_index= 0; primitive_index<primitive_count; primitive_index++)
					{
						struct rasterizer_debug_primitive *primitive= &debug_data.opaque_triangles[primitive_index];

						memcpy(&vertices[vertex_index], primitive->vertices, primitive->vertex_count*sizeof(struct rasterizer_debug_vertex));
						vertex_index+= primitive->vertex_count;
					}

					rasterizer_dynamic_vertices_unlock(dynamic_vertex_buffer_index);
					rasterizer_debug_drawing_begin(TRUE, 0);
					rasterizer_draw_dynamic_vertices(0, primitive_count, dynamic_vertex_buffer_index, 3);
					rasterizer_debug_drawing_end();
				}
				else
				{
					error(_error_silent, "### ERROR failed to lock dynamic vertex buffers for debug primitives");
					success= FALSE;
				}

				rasterizer_dynamic_vertices_delete(dynamic_vertex_buffer_index);
			}
			else
			{
				success= FALSE;
			}
		}

		if (success && debug_data.opaque_line_count>0)
		{
			long dynamic_vertex_buffer_index= rasterizer_dynamic_vertices_new(9, 2*debug_data.opaque_line_count);

			if (dynamic_vertex_buffer_index!=NONE)
			{
				struct rasterizer_debug_vertex *vertices= rasterizer_dynamic_vertices_lock(dynamic_vertex_buffer_index);

				if (vertices)
				{
					long vertex_index= 0;
					long primitive_count= debug_data.opaque_line_count;

					for (primitive_index= 0; primitive_index<primitive_count; primitive_index++)
					{
						struct rasterizer_debug_primitive *primitive= &debug_data.opaque_lines[primitive_index];

						memcpy(&vertices[vertex_index], primitive->vertices, primitive->vertex_count*sizeof(struct rasterizer_debug_vertex));
						vertex_index+= primitive->vertex_count;
					}

					rasterizer_dynamic_vertices_unlock(dynamic_vertex_buffer_index);
					rasterizer_debug_drawing_begin(TRUE, 16);
					rasterizer_draw_dynamic_vertices(0, primitive_count, dynamic_vertex_buffer_index, 2);
					rasterizer_debug_drawing_end();
				}
				else
				{
					error(_error_silent, "### ERROR failed to lock dynamic vertex buffers for debug primitives");
					success= FALSE;
				}

				rasterizer_dynamic_vertices_delete(dynamic_vertex_buffer_index);
			}
			else
			{
				success= FALSE;
			}
		}

		for (primitive_index= 0; success && primitive_index<debug_data.non_opaque_primitive_count; primitive_index++)
		{
			struct rasterizer_debug_primitive *primitive= &debug_data.non_opaque_primitives[primitive_index];
			long dynamic_vertex_buffer_index= rasterizer_dynamic_vertices_new(9, primitive->vertex_count);

			if (dynamic_vertex_buffer_index!=NONE)
			{
				struct rasterizer_debug_vertex *vertices= rasterizer_dynamic_vertices_lock(dynamic_vertex_buffer_index);

				if (vertices)
				{
					memcpy(vertices, primitive->vertices, primitive->vertex_count*sizeof(struct rasterizer_debug_vertex));
					rasterizer_dynamic_vertices_unlock(dynamic_vertex_buffer_index);
					rasterizer_debug_drawing_begin(FALSE, 0);
					rasterizer_draw_dynamic_vertices(0, 1, dynamic_vertex_buffer_index, primitive->vertex_count);
					rasterizer_debug_drawing_end();
				}
				else
				{
					error(_error_silent, "### ERROR failed to lock dynamic vertex buffers for debug primitives");
					success= FALSE;
				}

				rasterizer_dynamic_vertices_delete(dynamic_vertex_buffer_index);
			}
			else
			{
				success= FALSE;
			}
		}

		rasterizer_globals.current_lock_operation= _rasterizer_lock_none;
	}

	return;
}
