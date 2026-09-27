/*
FONT_GROUP.H

header included in hcex build.
*/

#ifndef __FONT_GROUP_H
#define __FONT_GROUP_H
#pragma once

/* ---------- headers */

#include "tag_files/tag_groups.h"
#include "text/text_group.h"

/* ---------- constants */

enum
{
	FONT_GROUP_TAG = 'font',
};

/* ---------- macros */

#define font_definition_get(index) ((struct font_header *)tag_get(FONT_GROUP_TAG, index))

/* ---------- structures */

struct font_character
{
	unsigned short character;
	short character_width;
	short bitmap_width;
	short bitmap_height;
	short bitmap_origin_x;
	short bitmap_origin_y;
	short hardware_character_index;
	unsigned short pad; // used at runtime to tag the hardware character cache (rasterizer_text.c magic_number)
	long pixels_offset;
}; // 0x14

struct font_header
{
	unsigned long flags;
	short ascending_height;
	short descending_height;
	short leading_height;
	short leading_width;
	long pad[9];
	struct tag_block character_tables;
	struct tag_reference style_fonts[NUMBER_OF_TEXT_STYLES];
	struct tag_block characters;
	struct tag_data pixels;
}; // 0x9C

/* ---------- prototypes/FONT_GROUP.C */

/* ---------- globals */

/* ---------- public code */

#endif // __FONT_GROUP_H
