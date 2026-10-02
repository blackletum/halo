/*
DIRECTOR.H

header included in hcex build.
*/

#ifndef __DIRECTOR_H
#define __DIRECTOR_H
#pragma once

/* ---------- headers */

#include "observer.h"

/* ---------- constants */

enum
{
	_director_perspective_first_person = 0,
	_director_perspective_third_person,
	_director_perspective_scripted,
	_director_perspective_neutral,
	NUMBER_OF_DIRECTOR_PERSPECTIVE_MODES,
};

enum
{
	_camera_following = 0,
	_camera_orbiting,
	_camera_flying,
	_camera_editor,
	_camera_first_person,
	NUMBER_OF_DIRECTOR_CAMERA_MODES,
};

enum
{
	_camera_control_forward_bit = 0,
	_camera_control_reverse_bit,
	_camera_control_left_bit,
	_camera_control_right_bit,
	_camera_control_up_bit,
	_camera_control_down_bit,
	_camera_control_roll_left_bit,
	_camera_control_roll_right_bit,
	NUMBER_OF_CAMERA_CONTROL_BITS,
};

enum
{
	_director_mode_game = 0,
	_director_mode_netgame,
	_director_mode_editor,
	_director_mode_scripted,
	_director_mode_script_camera_record,
	NUMBER_OF_DIRECTOR_GAME_MODES,
};

enum
{
	_variable_height = 0,
	_variable_roll,
	_variable_forward,
	_variable_right,
	NUMBER_OF_DIRECTOR_VARIABLES,
};

enum
{
	_not_in_seat = 0,
	_entering_seat,
	_seat_idle,
	_exiting_seat,
};

enum
{
	DIRECTOR_CAMERA_DATA_SIZE = 64,
};

/* ---------- macros */

/* ---------- structures */

struct director_variable_definition
{
	short negative_bit;
	short positive_bit;
	short reset_bit;
	real scale;
	real initial_value;
	real minimum;
	real maximum;
	boolean has_hyper_scale;
};

struct director_variable_instance
{
	real value;
	real velocity;
	real delta;
};

struct director
{
	short camera_mode_index;
	real camera_change_pause;
	void (*camera_proc)(void *, struct camera_control const *, struct observer_command *);
	byte camera_data[DIRECTOR_CAMERA_DATA_SIZE];
	long bored_time;
	boolean bored;
	boolean inhibited_facing;
	boolean inhibited_input;
	short seat_state;
	short perspective;
	struct observer_command command;
	boolean debug_controls;
	real debug_input_scale;
	struct director_variable_instance debug_variables[NUMBER_OF_DIRECTOR_VARIABLES];
};

struct camera_control
{
	short local_player_index;
	boolean active;
	real seconds_elapsed;
	real_euler_angles3d facing_delta;
	real_vector3d position_delta;
	real wheel_delta;
};

/* ---------- prototypes/DIRECTOR.C */

void director_initialize(void);
void director_initialize_for_saved_game(void);
void director_initialize_for_new_map(void);
void director_dispose_from_old_map(void);
void director_dispose(void);
void director_inhibit_facing(short local_player_index);
void director_inhibit_input(short local_player_index);
boolean director_inhibited_facing(short local_player_index);
boolean director_inhibited_input(short local_player_index);
void director_update(real dt);
void director_set_mode(short mode);
void director_save_camera(void);
void director_load_camera(void);
short director_get_perspective(short local_player_index);
short director_camera_deterministic(long unit_index, real_point3d *position, real_vector3d *forward);
short director_desired_perspective(long unit_index, short *seat_state);
void director_script_camera(boolean enabled);

/* ---------- globals */

extern boolean director_camera_switch_fast;
extern boolean *director_camera_scripted;

/* ---------- public code */

#endif // __DIRECTOR_H
