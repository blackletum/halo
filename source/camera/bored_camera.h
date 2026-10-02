/*
BORED_CAMERA.H

header included in hcex build.
*/

#ifndef __BORED_CAMERA_H
#define __BORED_CAMERA_H
#pragma once

/* ---------- constants */

/* ---------- macros */

/* ---------- structures */

struct bored_camera
{
	unsigned long last_update_time; /* fake name */
	long timer; /* fake name */
	long camera_count; /* fake name */
};

/* ---------- prototypes/BORED_CAMERA.C */

void bored_camera_new(struct bored_camera *camera);
boolean is_bored(void);
boolean is_still_bored(void);
void bored_camera_update(struct bored_camera *camera, struct camera_control const *controls, struct observer_command *result);

/* ---------- globals */

/* ---------- public code */

#endif // __BORED_CAMERA_H
