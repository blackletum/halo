/*
RASTERIZER_TRANSPARENT_GEOMETRY.C

symbols in this file:
00173AB0 00a0:
	_rasterizer_transparent_geometry_initialize (0000)
00173B50 0030:
	_rasterizer_transparent_geometry_begin (0000)
00173B80 0030:
	_rasterizer_transparent_geometry_new_group (0000)
00173BB0 0030:
	_rasterizer_transparent_geometry_new_group2 (0000)
00173BE0 0020:
	_rasterizer_transparent_geometry_get_groups2 (0000)
00173C00 00a0:
	_rasterizer_transparent_geometry_next_group (0000)
00173CA0 0010:
	_rasterizer_transparent_geometry_get_groups (0000)
00173CB0 0050:
	_rasterizer_transparent_geometry_get_group_from_presorted_index (0000)
00173D00 00c0:
	_rasterizer_transparent_geometry_get_group_presorted_index (0000)
00173DC0 0040:
	_rasterizer_transparent_geometry_get_group_pending_status (0000)
00173E00 0060:
	_rasterizer_transparent_geometry_set_group_pending_status (0000)
00173E60 0070:
	_rasterizer_transparent_geometry_get_primary_vertex_type (0000)
00173ED0 0010:
	_rasterizer_transparent_geometry_end (0000)
00173EE0 0080:
	_rasterizer_transparent_geometry_dispose (0000)
00173F60 0010:
	_rasterizer_transparent_geometry_stop (0000)
00173F70 0030:
	_rasterizer_sort_internal (0000)
00173FA0 0180:
	_group_sorted_indices_cmpfn (0000)
00174120 00b0:
	_rasterizer_sort_external (0000)
001741D0 01e0:
	_rasterizer_transparent_geometry_draw (0000)
0029F19C 0039:
	??_C@_0DJ@FPHMGBGH@?$CD?$CD?$CD?5ERROR?5failed?5to?5allocate?5tra@ (0000)
0029F1D8 003c:
	??_C@_0DM@PHFAKDJD@c?3?2halo?2SOURCE?2rasterizer?2raster@ (0000)
0029F214 001b:
	??_C@_0BL@MKAECLFF@next_group_sorted_index?$DO?$DN0?$AA@ (0000)
0029F230 004f:
	??_C@_0EP@FBJFLNLL@group?9?$DOsorted_index?$DO?$DN0?5?$CG?$CG?5group?9@ (0000)
0029F280 0053:
	??_C@_0FD@BILDLJMA@group_presorted_index?$DO?$DN0?5?$CG?$CG?5grou@ (0000)
0029F2D8 006f:
	??_C@_0GP@EGPBNBIE@?$CI?$CIunsigned?5long?$CJgroup?9?$CIunsigned?5@ (0000)
0029F348 0035:
	??_C@_0DF@OBMEADDC@?$CD?$CD?$CD?5ERROR?5transparent?5geometry?5g@ (0000)
0029F380 0057:
	??_C@_0FH@DJGEIAGF@group_index2?5?$CG?$CG?5?$CI?$CKgroup_index2?$CJ?$DO@ (0000)
0029F3D8 0057:
	??_C@_0FH@MLHLDOCN@group_index1?5?$CG?$CG?5?$CI?$CKgroup_index1?$CJ?$DO@ (0000)
0029F430 0013:
	??_C@_0BD@KIEBCHPI@?$CBfirst_person_flag?$AA@ (0000)
0029F444 0007:
	??_C@_06OGEFEFJ@?$CBwater?$AA@ (0000)
004B8AD8 004a:
	?group_index@?1??rasterizer_transparent_geometry_draw@@9@9 (0000)
	_bss_004b8adc (0004)
	_transparent_geometry_groups (0034)
	_transparent_geometry_groups2 (0038)
	_transparent_geometry_group_count (003c)
	_transparent_geometry_group_count2 (0040)
	_transparent_geometry_group_sorted_indices (0044)
	_transparent_geometry_attached_group_count (0048)
*/

/* ---------- headers */

#include "cseries.h"
#include "cseries_windows.h"
#include "errors.h"
#include "real_math.h"
#include "tag_groups.h"
#include "rasterizer.h"
#include "rasterizer_geometry.h"
#include "xbox/rasterizer_xbox.h"
#include "shaders/shader_definitions.h"
#include "shaders.h"

/* ---------- constants */

/* ---------- macros */

/* ---------- structures */

/* ---------- prototypes */

boolean rasterizer_transparent_geometry_initialize_aux_buffer(void);
void rasterizer_transparent_geometry_dispose_aux_buffer(void);
void rasterizer_transparent_geometry_groups_begin(void);
void rasterizer_transparent_geometry_groups_end(void);
void rasterizer_transparent_geometry_group_draw(struct transparent_geometry_group const *group, boolean unknown);
short rasterizer_dynamic_vertices_get_type(long dynamic_vertex_buffer_index);
void rasterizer_set_stencil_mode(short mode);
void rasterizer_set_frustum_z(real z_near, real z_far);

static void rasterizer_sort_internal(struct transparent_geometry_group *group);
static int __cdecl group_sorted_indices_cmpfn(const void *group_index1, const void *group_index2);
static void rasterizer_sort_external(void);

/* ---------- globals */

extern struct rasterizer_window_begin_parameters global_window_parameters;

static struct transparent_geometry_group *transparent_geometry_groups;
static struct transparent_geometry_group *transparent_geometry_groups2;
static long transparent_geometry_group_count;
static long transparent_geometry_group_count2;
static short *transparent_geometry_group_sorted_indices;
static short transparent_geometry_attached_group_count;
static long bss_004b8adc[BIT_VECTOR_SIZE_IN_LONGS(RASTERIZER_MAXIMUM_TRANSPARENT_GEOMETRY_GROUPS)]; // xbox-only, not in hcex

/* ---------- public code */

boolean rasterizer_transparent_geometry_initialize(
	void)
{
	boolean success = TRUE;

	transparent_geometry_groups = match_malloc("c:\\halo\\SOURCE\\rasterizer\\rasterizer_transparent_geometry.c", 41, RASTERIZER_MAXIMUM_TRANSPARENT_GEOMETRY_GROUPS*sizeof(struct transparent_geometry_group));
	transparent_geometry_group_sorted_indices = match_malloc("c:\\halo\\SOURCE\\rasterizer\\rasterizer_transparent_geometry.c", 43, RASTERIZER_MAXIMUM_TRANSPARENT_GEOMETRY_GROUPS*sizeof(short));
	transparent_geometry_groups2 = match_malloc("c:\\halo\\SOURCE\\rasterizer\\rasterizer_transparent_geometry.c", 46, RASTERIZER_MAXIMUM_TRANSPARENT_GEOMETRY_GROUPS2*sizeof(struct transparent_geometry_group));
	transparent_geometry_group_count2 = 0;
	transparent_geometry_group_count = 0;

	if (!transparent_geometry_groups || !transparent_geometry_group_sorted_indices || !transparent_geometry_groups2)
	{
		error(_error_silent, "### ERROR failed to allocate transparent geometry buffer");
		success = FALSE;
	}

	if (success && !rasterizer_transparent_geometry_initialize_aux_buffer())
	{
		success = FALSE;
	}

	return success;
}

void rasterizer_transparent_geometry_begin(
	void)
{
	transparent_geometry_group_count = 0;
	transparent_geometry_attached_group_count = 0;
	memset(bss_004b8adc, 0, sizeof(bss_004b8adc));
	transparent_geometry_group_count2 = 0;

	return;
}

struct transparent_geometry_group *rasterizer_transparent_geometry_new_group(
	void)
{
	struct transparent_geometry_group *group = NULL;

	if (transparent_geometry_group_count<RASTERIZER_MAXIMUM_TRANSPARENT_GEOMETRY_GROUPS)
	{
		group = transparent_geometry_groups+transparent_geometry_group_count;
		group->sorted_index = transparent_geometry_group_count;
		transparent_geometry_group_count++;
	}

	return group;
}

struct transparent_geometry_group *rasterizer_transparent_geometry_new_group2(
	void)
{
	struct transparent_geometry_group *group = NULL;

	if (transparent_geometry_group_count2<RASTERIZER_MAXIMUM_TRANSPARENT_GEOMETRY_GROUPS2)
	{
		group = transparent_geometry_groups2+transparent_geometry_group_count2;
		group->sorted_index = transparent_geometry_group_count2;
		transparent_geometry_group_count2++;
	}

	return group;
}

struct transparent_geometry_group const *rasterizer_transparent_geometry_get_groups2(
	short *count)
{
	if (count)
	{
		*count = (short)transparent_geometry_group_count2;
	}

	return transparent_geometry_groups2;
}

struct transparent_geometry_group const *rasterizer_transparent_geometry_next_group(
	struct transparent_geometry_group const *group)
{
	if (group)
	{
		short next_group_sorted_index = (short)(group->sorted_index+1);

		match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_transparent_geometry.c", 137, group->sorted_index>=0 && group->sorted_index<transparent_geometry_group_count);
		if (next_group_sorted_index<transparent_geometry_group_count)
		{
			match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_transparent_geometry.c", 141, next_group_sorted_index>=0);
			group = transparent_geometry_groups+transparent_geometry_group_sorted_indices[next_group_sorted_index];
		}
		else
		{
			group = NULL;
		}
	}

	return group;
}

struct transparent_geometry_group *rasterizer_transparent_geometry_get_groups(
	void)
{
	return transparent_geometry_groups;
}

struct transparent_geometry_group const *rasterizer_transparent_geometry_get_group_from_presorted_index(
	short group_presorted_index)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_transparent_geometry.c", 188, group_presorted_index>=0 && group_presorted_index<transparent_geometry_group_count);

	return transparent_geometry_groups+group_presorted_index;
}

short rasterizer_transparent_geometry_get_group_presorted_index(
	struct transparent_geometry_group const *group)
{
	short group_presorted_index = NONE;

	if (group>=transparent_geometry_groups && group<transparent_geometry_groups+transparent_geometry_group_count)
	{
		group_presorted_index = (short)(group-transparent_geometry_groups);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_transparent_geometry.c", 203, group_presorted_index>=0 && group_presorted_index<transparent_geometry_group_count);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_transparent_geometry.c", 204, ((unsigned long)group-(unsigned long)transparent_geometry_groups)%sizeof(struct transparent_geometry_group)==0);
	}

	return group_presorted_index;
}

boolean rasterizer_transparent_geometry_get_group_pending_status(
	struct transparent_geometry_group const *group)
{
	short group_presorted_index = rasterizer_transparent_geometry_get_group_presorted_index(group);
	boolean status = TRUE;

	if (group_presorted_index!=NONE)
	{
		status = !BIT_VECTOR_TEST_FLAG(bss_004b8adc, group_presorted_index);
	}

	return status;
}

void rasterizer_transparent_geometry_set_group_pending_status(
	struct transparent_geometry_group const *group,
	boolean status)
{
	short group_presorted_index = rasterizer_transparent_geometry_get_group_presorted_index(group);

	if (group_presorted_index!=NONE)
	{
		BIT_VECTOR_SET_FLAG(bss_004b8adc, group_presorted_index, !status);
	}

	return;
}

short rasterizer_transparent_geometry_get_primary_vertex_type(
	struct transparent_geometry_group const *group)
{
	short vertex_type = NONE;

	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_transparent_geometry.c", 244, group);
	if (group->vertex_buffers)
	{
		vertex_type = group->vertex_buffers->type;
	}
	else if (group->dynamic_vertex_buffer_index!=NONE)
	{
		vertex_type = rasterizer_dynamic_vertices_get_type(group->dynamic_vertex_buffer_index);
	}
	else
	{
		error(_error_silent, "### ERROR transparent geometry group has no vertices");
	}

	return vertex_type;
}

void rasterizer_transparent_geometry_end(
	void)
{
	return;
}

void rasterizer_transparent_geometry_dispose(
	void)
{
	rasterizer_transparent_geometry_dispose_aux_buffer();

	if (transparent_geometry_groups)
	{
		match_free("c:\\halo\\SOURCE\\rasterizer\\rasterizer_transparent_geometry.c", 273, transparent_geometry_groups);
	}
	transparent_geometry_groups = NULL;

	if (transparent_geometry_group_sorted_indices)
	{
		match_free("c:\\halo\\SOURCE\\rasterizer\\rasterizer_transparent_geometry.c", 276, transparent_geometry_group_sorted_indices);
	}
	transparent_geometry_group_sorted_indices = NULL;

	if (transparent_geometry_groups2)
	{
		match_free("c:\\halo\\SOURCE\\rasterizer\\rasterizer_transparent_geometry.c", 280, transparent_geometry_groups2);
	}
	transparent_geometry_groups2 = NULL;

	transparent_geometry_group_count2 = 0;
	transparent_geometry_group_count = 0;

	return;
}

void rasterizer_transparent_geometry_draw(
	boolean water)
{
	static short group_index;
	short profile = water ? _rasterizer_profile_water : _rasterizer_profile_queued_transparents;

	rasterizer_profile_begin(profile);
	if (transparent_geometry_group_count>0)
	{
		boolean first_person_flag = FALSE;

		if (water)
		{
			rasterizer_sort_external();
			group_index = 0;
			if (global_window_parameters.window_index!=NONE)
			{
				rasterizer_debug_options.transparent_pixel_counter_enabled = TRUE;
			}
		}

		rasterizer_transparent_geometry_groups_begin();
		rasterizer_debug_options.transparent_pixel_counter_enabled = FALSE;
		while (group_index<transparent_geometry_group_count)
		{
			struct transparent_geometry_group const *group = transparent_geometry_groups+transparent_geometry_group_sorted_indices[group_index];

			if (water && (!group->shader || (group->shader->base.type!=_shader_type_transparent_water && !shader_is_water_decal((struct shader *)group->shader))))
			{
				break;
			}

			if (TEST_FLAG(group->geometry_flags, _rasterizer_geometry_first_person_bit))
			{
				match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_transparent_geometry.c", 340, !water);
				match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_transparent_geometry.c", 341, global_window_parameters.rasterizer_target==_rasterizer_target_render_primary);
				if (!first_person_flag)
				{
					rasterizer_set_stencil_mode(0);
					rasterizer_set_frustum_z(rasterizer_globals.z_near_first_person, rasterizer_globals.z_far_first_person);
					first_person_flag = TRUE;
				}
			}
			else
			{
				match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_transparent_geometry.c", 355, !first_person_flag);
			}

			rasterizer_transparent_geometry_group_draw(group, FALSE);
			group_index++;
		}

		if (!water && global_window_parameters.window_index!=NONE)
		{
			rasterizer_debug_options.transparent_pixel_counter_enabled = TRUE;
		}
		rasterizer_transparent_geometry_groups_end();
		rasterizer_debug_options.transparent_pixel_counter_enabled = FALSE;

		if (first_person_flag)
		{
			rasterizer_set_frustum_z(0.f, 0.f);
		}
	}
	rasterizer_profile_end(profile);

	return;
}

void rasterizer_transparent_geometry_stop(
	void)
{
	rasterizer_set_stencil_mode(0);

	return;
}

/* ---------- private code */

// rasterizer_sort_internal
static void rasterizer_sort_internal(
	struct transparent_geometry_group *group)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_transparent_geometry.c", 402, group);

	return;
}

// group_sorted_indices_cmpfn
static int __cdecl group_sorted_indices_cmpfn(
	const void *a,
	const void *b)
{
	short const *group_index1 = a;
	short const *group_index2 = b;
	struct transparent_geometry_group const *group1;
	struct transparent_geometry_group const *group2;
	int result = 0;

	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_transparent_geometry.c", 426, group_index1 && (*group_index1)>=0 && (*group_index1)<transparent_geometry_group_count);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_transparent_geometry.c", 427, group_index2 && (*group_index2)>=0 && (*group_index2)<transparent_geometry_group_count);

	group1 = transparent_geometry_groups+(*group_index1);
	group2 = transparent_geometry_groups+(*group_index2);

	if (shader_is_water_decal((struct shader *)group1->shader))
	{
		result = -1;
	}
	else if (shader_is_water_decal((struct shader *)group2->shader))
	{
		result = 1;
	}
	else if (group1->shader && group1->shader->base.type==_shader_type_transparent_water)
	{
		result = -1;
	}
	else if (group2->shader && group2->shader->base.type==_shader_type_transparent_water)
	{
		result = 1;
	}
	else if (TEST_FLAG(group1->geometry_flags, _rasterizer_geometry_first_person_bit) && !TEST_FLAG(group2->geometry_flags, _rasterizer_geometry_first_person_bit))
	{
		result = 1;
	}
	else if (TEST_FLAG(group2->geometry_flags, _rasterizer_geometry_first_person_bit) && !TEST_FLAG(group1->geometry_flags, _rasterizer_geometry_first_person_bit))
	{
		result = -1;
	}
	else if (group1->z_sort>group2->z_sort)
	{
		result = 1;
	}
	else if (group1->z_sort<group2->z_sort)
	{
		result = -1;
	}
	else if (group1->source_object_index>group2->source_object_index)
	{
		result = 1;
	}
	else if (group1->source_object_index<group2->source_object_index)
	{
		result = -1;
	}

	if (group1->cortana_hack && !group2->cortana_hack)
	{
		result = 1;
	}
	else if (group2->cortana_hack && !group1->cortana_hack)
	{
		result = -1;
	}

	return result;
}

// rasterizer_sort_external
static void rasterizer_sort_external(
	void)
{
	short group_index;

	for (group_index = 0; group_index<transparent_geometry_group_count; group_index++)
	{
		rasterizer_sort_internal(transparent_geometry_groups+group_index);
		transparent_geometry_group_sorted_indices[group_index] = group_index;
	}

	qsort(transparent_geometry_group_sorted_indices, transparent_geometry_group_count, sizeof(short), group_sorted_indices_cmpfn);

	for (group_index = 0; group_index<transparent_geometry_group_count; group_index++)
	{
		transparent_geometry_groups[transparent_geometry_group_sorted_indices[group_index]].sorted_index = group_index;
	}

	return;
}
