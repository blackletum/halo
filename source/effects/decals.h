/*
DECALS.H

header included in hcex build.
*/

#ifndef __DECALS_H
#define __DECALS_H
#pragma once

/* ---------- headers */

#include "real_math.h"

/* ---------- constants */

/* ---------- macros */

/* ---------- structures */

struct decal_datum
{
	short identifier;
	word flags;
	short cluster_index;
	short layer;
	real_point3d position;
	long creation_time;
	char sequence_index;
	char unused___was_frames_remaining;
	char sprite_index;
	char bitmap_index;
	real lifetime;
	real decay_time;
	unsigned long color;
	unsigned char intensity;
	unsigned char pad;
	short quad_count;
	long definition_index;
	long prev_decal_index;
	long next_decal_index;
};

/* ---------- prototypes/DECALS.C */

/* ---------- globals */

/* ---------- public code */

#endif // __DECALS_H
