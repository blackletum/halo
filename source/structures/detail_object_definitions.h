/*
DETAIL_OBJECT_DEFINITIONS.H

header included in hcex build.
*/

#ifndef __DETAIL_OBJECT_DEFINITIONS_H
#define __DETAIL_OBJECT_DEFINITIONS_H
#pragma once

/* ---------- headers */

#include "math/real_math.h"
#include "tag_files/tag_groups.h"

/* ---------- constants */

/* ---------- macros */

/* ---------- structures */

struct detail_object_type_definition
{
	char name[32];
	byte sequence_index;
	byte flags;
	byte first_frame_index;
	byte frame_count;
	real color_override_factor;
	long unused1[2];
	real near_fade_distance;
	real far_fade_distance;
	real size_min;
	real size_max;
	real_rgb_color color_min;
	real_rgb_color color_max;
	unsigned long color_ambient;
	long unused2[1];
};

struct detail_object_collection_definition
{
	short collection_type;
	word pad;
	real global_z_offset;
	long unused1[11];
	struct tag_reference map;
	struct tag_block type_definitions;				// detail_object_type_definition
	long unused2[12];
};

struct detail_object
{
	byte position[3];
	byte data;
	word color;
};

struct detail_object_cell_data
{
	long first_detail_object_index;
	long detail_object_count;
	short cell_x;
	short cell_y;
	real cell_z;
	long internal__first_vertex_index;
	real_vector4d const *z_reference_vector;
};

struct detail_object_layer_data
{
	struct detail_object_cell_data *cells;
	short cell_count;
	short collection_definition_index;
};

struct detail_object_view_data
{
	struct detail_object_layer_data *layers;
	short layer_count;
	short pad;
};

/* ---------- prototypes/EXAMPLE.C */

/* ---------- globals */

/* ---------- public code */

#endif // __DETAIL_OBJECT_DEFINITIONS_H
