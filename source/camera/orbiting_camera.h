/*
ORBITING_CAMERA.H

header included in hcex build.
*/

#ifndef __ORBITING_CAMERA_H
#define __ORBITING_CAMERA_H
#pragma once

/* ---------- headers */

#include "director.h"
#include "observer.h"

/* ---------- constants */

/* ---------- macros */

/* ---------- structures */

struct orbiting_camera
{
	real_euler_angles2d orientation;
	real distance;
};

/* ---------- prototypes/ORBITING_CAMERA.C */

void orbiting_camera_new(struct orbiting_camera *camera, real distance, real_vector3d const *facing);
void orbiting_camera_update(struct orbiting_camera *camera, struct camera_control const *controls, struct observer_command *result);

/* ---------- globals */

/* ---------- public code */

#endif // __ORBITING_CAMERA_H
