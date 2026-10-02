/*
EDITOR_FLYING_CAMERA.H

header included in hcex build.
*/

#ifndef __EDITOR_FLYING_CAMERA_H
#define __EDITOR_FLYING_CAMERA_H
#pragma once

/* ---------- headers */

#include "flying_camera.h"

/* ---------- constants */

enum
{
	_editor_camera_flying = 0,
	_editor_camera_orbiting,
	NUMBER_OF_EDITOR_CAMERA_MODES,
};

enum
{
	_translate_from = 0,
	_translate_to,
	NUMBER_OF_CAMERA_TRANSLATIONS,
};

/* ---------- macros */

/* ---------- structures */

struct editor_camera_focus_definition
{
	real_point3d position;
	real_euler_angles2d angles;
};

struct persisted_camera_data
{
	struct flying_camera camera_data;
	boolean saved;
};

/* ---------- prototypes/EDITOR_FLYING_CAMERA.C */

void editor_camera_new(struct flying_camera *camera, short local_player_index);
void editor_camera_get_focus(real_point3d *position, real_euler_angles2d *angles);
void editor_camera_set_focus(real_point3d const *position, real_euler_angles2d const *angles);
void editor_camera_move_to_point(real_point3d const *point);
void editor_camera_set_position(real_point3d const *point, real_euler_angles2d const *angles);
void editor_camera_set_position_and_roll(real_point3d const *point, real_euler_angles3d const *angles);
void editor_camera_bump_speed(void);
long editor_camera_get_speed(void);
boolean editor_camera_use_roll(boolean new_use_roll);
void editor_camera_set_unit_focus(long unit_index);
long editor_camera_get_unit_focus(void);
void editor_camera_set_mode(short mode);
short editor_camera_get_mode(void);
void editor_camera_update(struct flying_camera *camera, struct camera_control const *controls, struct observer_command *result);
void editor_camera_set_scripted(boolean scripted);
boolean editor_camera_get_scripted(void);
real editor_camera_get_field_of_view(void);

/* ---------- globals */

extern struct render_globals *editor_custom_render;

/* ---------- public code */

#endif // __EDITOR_FLYING_CAMERA_H
