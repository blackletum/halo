/*
BORED_CAMERA.C
*/

/* ---------- headers */

#include "cseries.h"
#include "bored_camera.h"
#include "director.h"
#include "observer.h"
#include "players.h"
#include "cseries_windows.h"
#include "unit_definitions.h"
#include "units.h"

/* ---------- prototypes */

static long bored_camera_get_threshold(long camera_count); /* fake name */
static long bored_camera_get_next_timer(long camera_count); /* fake name */

/* ---------- public code */

void bored_camera_new(
	struct bored_camera *camera)
{
	camera->camera_count = 0;
	camera->last_update_time = system_milliseconds();
	camera->timer = 0;

	return;
}

boolean is_bored(void)
{
	return FALSE;
}

boolean is_still_bored(void)
{
	return FALSE;
}

void bored_camera_update(
	struct bored_camera *camera,
	struct camera_control const *controls,
	struct observer_command *result)
{
	unsigned long current_time = system_milliseconds();

	match_assert("c:\\halo\\SOURCE\\camera\\bored_camera.c", 51, camera);
	match_assert("c:\\halo\\SOURCE\\camera\\bored_camera.c", 52, result);

	camera->timer += camera->last_update_time - current_time;
	camera->last_update_time = current_time;

	if (camera->timer<bored_camera_get_threshold(camera->camera_count))
	{
		struct unit_camera_info camera_info;
		real_euler_angles2d facing;
		real_point3d camera_position;
		long next_timer;
		long aiming_unit_index = player_control_get_aiming_unit_index(controls->local_player_index);

		player_control_get_unit_camera_info(controls->local_player_index, &camera_info);
		result->focus_position = camera_info.unit_origin;

		if (aiming_unit_index!=NONE)
		{
			if (camera_info.unit_camera->unit_camera_tracks.count)
			{
				struct unit_camera_track *track = TAG_BLOCK_GET_ELEMENT(&camera_info.unit_camera->unit_camera_tracks, 0, struct unit_camera_track);
			}

			facing = *player_control_get_facing_angles(controls->local_player_index);
			unit_get_camera_position(aiming_unit_index, &camera_position);

			facing.pitch = real_local_random_range(-1.0995574f, 0.3926991f);
			facing.yaw = real_local_random_range(-0.7853982f, 0.7853982f) + facing.yaw + _pi;
			vector3d_from_euler_angles2d(&result->forward, &facing);
			observer_up_from_forward(&result->forward, &result->up);

			result->field_of_view = (real_local_random_range(0.5235988f, 1.3962634f));
			result->focus_distance = real_local_random_range(1.0f, 6.0f);
			result->focus_velocity = *global_zero_vector3d;

			next_timer = bored_camera_get_next_timer(camera->camera_count);
			camera->timer = next_timer;
			result->flags = FLAG(_observer_command_valid_bit);
			result->timer = (real)next_timer;
			camera->camera_count++;

			if (TEST_FLAG(result->flags, _observer_command_valid_bit))
			{
				match_assert_valid_observer_command("c:\\halo\\SOURCE\\camera\\bored_camera.c", 95, result);
			}
		}
	}

	return;
}

/* ---------- private code */

static long bored_camera_get_threshold(
	long camera_count)
{
	return MIN(camera_count, 3)*MILLISECONDS_PER_SECOND;
}

static long bored_camera_get_next_timer(
	long camera_count)
{
	return MIN(camera_count+1, 3)*10*MILLISECONDS_PER_SECOND;
}
