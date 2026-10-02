/*
STATIC_CAMERA.H

header included in hcex build.
*/

#ifndef __STATIC_CAMERA_H
#define __STATIC_CAMERA_H
#pragma once

/* ---------- headers */

#include "director.h"
#include "observer.h"

/* ---------- constants */

/* ---------- macros */

/* ---------- structures */

struct static_camera
{
	/* fake names */
	real_point3d position; /* fake name */
	real unknown; /* fake name */
	real_vector3d forward; /* fake name */
	real_vector3d up; /* fake name */
	real field_of_view; /* fake name */
	long timer; /* fake name */
	long flags; /* fake name */
	boolean initialized; /* fake name */
};

/* ---------- prototypes/STATIC_CAMERA.C */

void static_camera_new(
	struct static_camera *camera,
	real_point3d const *position,
	real unknown /* fake name */,
	real_vector3d const *forward,
	real_vector3d const *up,
	real field_of_view,
	long timer,
	long flags);
void static_camera_update(struct static_camera *camera, struct camera_control const *action, struct observer_command *result);

/* ---------- globals */

/* ---------- public code */

#endif // __STATIC_CAMERA_H
