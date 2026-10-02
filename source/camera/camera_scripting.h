/*
CAMERA_SCRIPTING.H

header included in hcex build.
*/

#ifndef __CAMERA_SCRIPTING_H
#define __CAMERA_SCRIPTING_H
#pragma once

/* ---------- constants */

enum
{
	_camera_script_mode_point = 0,
	_camera_script_mode_animation,
	_camera_script_mode_first_person,
	_camera_script_mode_dead,
	NUMBER_OF_CAMERA_SCRIPT_MODES,
};

/* ---------- macros */

/* ---------- structures */

/* ---------- prototypes/CAMERA_SCRIPTING.C */

void scripted_camera_enable(boolean enabled);
void scripted_camera_set_animation(long animation_graph_index, char const *animation_name);
void scripted_camera_set_first_person(long unit_index);
void scripted_camera_set_dead(long unit_index);
boolean scripted_camera_object_is_first_person_camera(long object_index);
void scripted_camera_set(short camera_point_index, short tick_count, long relative_to_object_index);
void scripted_camera_set_absolute(short camera_point_index, short tick_count);
void scripted_camera_set_camera_point_relative(real_point3d const *position, real_vector3d const *forward, real_vector3d const *up, real fov, short tick_count, long relative_to_object_index);
void scripted_camera_set_camera_point_absolute(real_point3d const *position, real_vector3d const *forward, real_vector3d const *up, real fov, short tick_count);
short scripted_camera_next_camera_point(void);
long scripted_camera_object_relative_to(void);
short scripted_camera_time(void);
void scripted_camera_update(struct scripted_camera *camera, struct camera_control const *controls, struct observer_command *result);

/* ---------- globals */

/* ---------- public code */

#endif // __CAMERA_SCRIPTING_H
