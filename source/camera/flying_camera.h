/*
FLYING_CAMERA.H

header included in hcex build.
*/

#ifndef __FLYING_CAMERA_H
#define __FLYING_CAMERA_H
#pragma once

/* ---------- constants */

/* ---------- macros */

/* ---------- structures */

struct flying_camera
{
	real_point3d position;
	real_euler_angles2d orientation;
	real roll;
	real field_of_view;
};

/* ---------- prototypes/FLYING_CAMERA.C */

void flying_camera_new(struct flying_camera *camera);
void flying_camera_new_from_point_and_vector(struct flying_camera *camera, real_point3d const *focus, real_vector3d const *orientation);
void flying_camera_update(struct flying_camera *camera, struct camera_control const *controls, struct observer_command *result);

/* ---------- globals */

/* ---------- public code */

#endif // __FLYING_CAMERA_H
