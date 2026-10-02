/*
ORBITING_CAMERA.C
*/

/* ---------- headers */

#include "cseries.h"
#include "orbiting_camera.h"
#include "director.h"
#include "observer.h"
#include "network_game_globals.h"
#include "units.h"
#include "players.h"

/* ---------- globals */

static real const orbiting_camera_field_of_view = DEGREES_TO_RADIANS(50.f);
static real const orbiting_camera_minimum_distance = 1.f;
static real const orbiting_camera_zoom_scale = 0.5f;
static real const orbiting_camera_latency = 0.5f;
static real const orbiting_camera_z_offset = 0.52f;

/* ---------- public code */

void orbiting_camera_new(
	struct orbiting_camera *camera,
	real distance,
	real_vector3d const *facing)
{
	camera->distance = distance;
	euler_angles2d_from_vector3d(&camera->orientation, facing);

	return;
}

void orbiting_camera_update(
	struct orbiting_camera *camera,
	struct camera_control const *controls,
	struct observer_command *result)
{
	struct unit_camera_info camera_info;

	player_control_get_unit_camera_info(controls->local_player_index, &camera_info);
	result->focus_position = camera_info.unit_origin;

	if (controls->active)
	{
		camera->orientation.yaw -= controls->facing_delta.yaw;
		camera->orientation.pitch = PIN(camera->orientation.pitch - controls->facing_delta.pitch, -1.2566371f, 1.2566371f);
		director_inhibit_input(controls->local_player_index);
	}

	camera->distance = MAX(camera->distance - controls->wheel_delta * (1.f/3.f), 0.6f);

	if (camera_info.unit_index != NONE)
	{
		vector3d_from_euler_angles2d(&result->forward, &camera->orientation);
		observer_up_from_forward(&result->forward, &result->up);
		object_get_velocities(camera_info.unit_index, &result->focus_velocity, NULL);
		result->focus_position.z += orbiting_camera_z_offset;
		result->flags = FLAG(_observer_command_valid_bit);
	}

	result->focus_offset = *global_zero_vector3d;
	result->focus_distance = camera->distance;
	result->field_of_view = orbiting_camera_field_of_view;
	result->timer = orbiting_camera_latency;

	match_assert_valid_observer_command("c:\\halo\\SOURCE\\camera\\orbiting_camera.c", 71, result);

	return;
}
