/*
BITMAP_GROUP.H

header included in hcex build.
*/

#ifndef __BITMAP_GROUP_H
#define __BITMAP_GROUP_H
#pragma once

/* ---------- headers */

#include "math/real_math.h"
#include "tag_files/tag_groups.h"

/* ---------- constants */

enum
{
	BITMAP_GROUP_TAG = 'bitm',
};

/* ---------- macros */

/* ---------- structures */

struct bitmap_group_sprite
{
	short bitmap_index;
	short bitmap_pad;
	long unused;
	real_rectangle2d bounds; // x0= left, x1= right, y0= top, y1= bottom
	real_point2d registration_point;
}; // 0x20

struct bitmap_group_sequence
{
	char name[32];
	short first_bitmap_index;
	short bitmap_count;
	long unused[4];
	struct tag_block sprites; // bitmap_group_sprite
}; // 0x40

struct bitmap_group
{
	short type;
	short format;
	short usage;
	unsigned short flags;
	real detail_fade;
	real sharpen_amount;
	real bump_height;
	short sprite_budget_size;
	short sprite_budget_count;
	short import_width;
	short import_height;
	struct tag_data import_bitmap;
	struct tag_data pixel_data;
	real smoothing_filter_size;
	real alpha_bias;
	short mipmap_count;
	short sprite_usage;
	short sprite_spacing;
	unsigned short pad;
	struct tag_block sequences; // bitmap_group_sequence
	struct tag_block bitmaps; // bitmap_data
}; // 0x6C

/* ---------- prototypes/BITMAP_GROUP.C */

/* ---------- globals */

/* ---------- public code */

#endif // __BITMAP_GROUP_H
