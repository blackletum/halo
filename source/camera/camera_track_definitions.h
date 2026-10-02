/*
CAMERA_TRACK_DEFINITIONS.H

header included in hcex build.
*/

#ifndef __CAMERA_TRACK_DEFINITIONS_H
#define __CAMERA_TRACK_DEFINITIONS_H
#pragma once

/* ---------- constants */

enum
{
	CAMERA_TRACK_DEFINITION_TAG = 'trak', /* fake name */
};

/* ---------- macros */

#define camera_track_definition_get(index) ((struct camera_track_definition *)tag_get(CAMERA_TRACK_DEFINITION_TAG, index))

/* ---------- structures */

struct camera_track_control_point
{
	real_vector3d position;
	real_quaternion orientation;
	long unused[8];
};

struct camera_track_definition
{
	unsigned long flags;
	struct tag_block control_points;		// camera_track_control_point
	long unused[8];
};

/* ---------- prototypes/EXAMPLE.C */

/* ---------- globals */

/* ---------- public code */

#endif // __CAMERA_TRACK_DEFINITIONS_H
