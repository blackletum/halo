/*
AI_PROFILE.H

header included in hcex build.
*/

#ifndef __AI_PROFILE_H
#define __AI_PROFILE_H
#pragma once

/* ---------- constants */

enum
{
	_ai_meter_collision_vector = 21,
	_ai_meter_line_of_sight,
	_ai_meter_line_of_fire,
	_ai_meter_path_flood,
	_ai_meter_path_find,
	_ai_meter_action_change,
	_ai_meter_firing_point_eval,
	NUMBER_OF_AI_METERS,
};

/* ---------- macros */

/* ---------- structures */

struct ai_meter
{
	short current_count;
	short last_count;
	real average_count;
	long average_total;
	short history_next_index;
	short history_max_index;
	short history_count[60];
};

struct ai_profile_state
{
	boolean disable_ai;
	boolean move_randomly;
	short render_spray_mode;
	boolean show;
	boolean show_stats;
	boolean show_actors;
	boolean show_swarms;
	boolean show_paths;
	boolean show_line_of_sight;
	boolean show_prop_types;
	boolean show_sound_distance;
	struct ai_meter meters[NUMBER_OF_AI_METERS];
};

/* ---------- prototypes/AI_PROFILE.C */

void ai_profile_change_render_spray(void);

/* ---------- globals */

extern struct ai_profile_state ai_profile;

/* ---------- public code */

#endif // __AI_PROFILE_H
