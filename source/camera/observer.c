/*
OBSERVER.C
*/

/* ---------- headers */

#include "cseries.h"
#include "observer.h"
#include "director.h"
#include "render.h"
#include "network_game_globals.h"
#include "units.h"
#include "players.h"
#include "collisions.h"
#include "predicted_resources.h"

/* ---------- prototypes */

static struct observer *observer_get(short local_player_index);
static void observer_clear(struct observer *observer);
static void observer_update_command(short local_player_index);
static void observer_pass_time(short local_player_index);
static void observer_update_displacements(short local_player_index);
static void observer_update_polynomial(short local_player_index);
static void observer_update_accelerations(short local_player_index);
static void observer_update_velocities(short local_player_index);
static void observer_update_positions(short local_player_index);
static void observer_find_displacement(real const *position0, real const *position1, struct observer_derivative *displacement);
static void observer_rotational_displacement(real_vector3d const *forward0, real_vector3d const *up0, real_vector3d const *forward1, real_vector3d const *up1, real_vector3d *rotation);
static void observer_apply_rotational_displacement(real_vector3d const *rotational_displacement, real_vector3d *forward, real_vector3d *up);
static void observer_postcheck(short local_player_index);
static void observer_check_penetration(real_point3d *focus_position, real_vector3d const *forward, real_vector3d const *up, real *distance, real safe_distance);
static boolean observer_collision_test_with_t(real_point3d const *p0, real_point3d const *p1, real *t, boolean ignore_media);
static boolean observer_collision_test_differential(real_point3d const *origin, real_point3d const *destination, real_vector3d const *differential_basis, real differential, real *t, boolean ignore_media);

/* ---------- globals */

static struct
{
	real dtime;
	struct observer local_players[MAXIMUM_NUMBER_OF_LOCAL_PLAYERS];
} observer_globals;

static short observer_parameter_real_counts[NUMBER_OF_OBSERVER_PARAMETERS] = {3, 3, 1, 1, 6};
static short observer_parameter_derivative_real_counts[NUMBER_OF_OBSERVER_PARAMETERS] = {3, 3, 1, 1, 3};

static real const observer_maximum_accelerations[NUMBER_OF_OBSERVER_PARAMETERS] = {1500.f, 1500.f, 100000.f, 100000.f, 100000.f};
static real const seconds_per_tick = SECONDS_PER_TICK;

/* ---------- public code */

void observer_initialize(void)
{
	return;
}

void observer_initialize_for_new_map(void)
{
	short local_player_index;

	for (local_player_index = 0; local_player_index < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS; local_player_index++)
	{
		observer_clear(observer_get(local_player_index));
	}

	return;
}

void observer_dispose_from_old_map(void)
{
	return;
}

void observer_set_camera(
	short local_player_index,
	struct observer_command *command)
{
	struct observer *observer = observer_get(local_player_index);

	match_assert_valid_observer_command("c:\\halo\\SOURCE\\camera\\observer.c", 233, command);

	observer->pending_command = command;
	observer->updated_for_frame = FALSE;

	if (!observer->first_command)
	{
		observer->first_command = TRUE;
		command->timer = 0.f;
		SET_FLAG(observer->pending_command->flags, _observer_command_force_time_bit, TRUE);
		csmemset(observer->pending_command->parameter_timers, 0, sizeof(observer->pending_command->parameter_timers));
	}

	return;
}

void observer_update(
	real dt)
{
	short local_player_index;

	observer_globals.dtime = dt;

	for (local_player_index = 0; local_player_index < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS; local_player_index++)
	{
		if (local_player_get_player_index(local_player_index) != NONE)
		{
			struct observer *observer = observer_get(local_player_index);

			match_assert("c:\\halo\\SOURCE\\camera\\observer.c", 264, observer->header_signature==OBSERVER_SIGNATURE && observer->trailer_signature==OBSERVER_SIGNATURE);
			match_assert("c:\\halo\\SOURCE\\camera\\observer.c", 265, !observer->updated_for_frame);

			observer->updated_for_frame = TRUE;

			observer_update_command(local_player_index);

			if (observer_globals.dtime != 0.f)
			{
				observer_pass_time(local_player_index);
			}

			observer_postcheck(local_player_index);

			match_assert("c:\\halo\\SOURCE\\camera\\observer.c", 279, observer->header_signature==OBSERVER_SIGNATURE && observer->trailer_signature==OBSERVER_SIGNATURE);
		}
	}

	return;
}

struct observer_result const *observer_get_camera(
	short local_player_index)
{
	struct observer const *observer;
	struct observer_result const *result = NULL;

	if (local_player_index != NONE)
	{
		observer = observer_get(local_player_index);
		result = &observer->result;

		match_assert("c:\\halo\\SOURCE\\camera\\observer.c", 301, observer->result.location.cluster_index>=NONE && observer->result.location.cluster_index<global_structure_bsp_get()->clusters.count);
	}

	return result;
}

boolean observer_command_has_finished(
	short local_player_index)
{
	short parameter_index;
	struct observer const *observer = observer_get(local_player_index);

	if (observer->last_command.timer != 0.f)
	{
		return FALSE;
	}

	for (parameter_index = 0; parameter_index < NUMBER_OF_OBSERVER_PARAMETERS; parameter_index++)
	{
		if (observer->last_command.parameter_timers[parameter_index] != 0.f)
		{
			return FALSE;
		}
	}

	return TRUE;
}

void observer_up_from_forward(
	real_vector3d const *forward,
	real_vector3d *up)
{
	real_vector3d right;

	right.i = forward->j;
	right.j = -forward->i;
	right.k = 0.f;

	if (normalize3d(&right) == 0.f)
	{
		right.i = 1.f;
		right.j = right.k = 0.f;
	}

	cross_product3d(&right, forward, up);

	return;
}

void observer_reconnect_to_structure_bsp(void)
{
	short local_player_index;

	for (local_player_index = 0; local_player_index < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS; local_player_index++)
	{
		if (local_player_get_player_index(local_player_index) != NONE)
		{
			struct observer *observer = observer_get(local_player_index);

			scenario_location_from_point(&observer->result.location, &observer->result.position);
		}
	}

	return;
}

void observer_obsolete_position(
	short local_player_index)
{
	observer_clear(observer_get(local_player_index));

	return;
}

/* ---------- private code */

static struct observer *observer_get(
	short local_player_index)
{
	match_assert("c:\\halo\\SOURCE\\camera\\observer.c", 114, local_player_index>=0 && local_player_index<MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);

	return &observer_globals.local_players[local_player_index];
}

static void observer_clear(
	struct observer *observer)
{
	observer->forward = *global_forward3d;
	observer->up = *global_up3d;
	observer->field_of_view = DEGREES_TO_RADIANS(50.f);
	observer->result.position = *global_origin3d;
	observer->result.location.cluster_index = NONE;
	observer->result.location.leaf_index = NONE;
	observer->result.velocity = *global_zero_vector3d;
	observer->result.forward = *global_forward3d;
	observer->result.up = *global_up3d;
	observer->result.field_of_view = DEGREES_TO_RADIANS(50.f);

	csmemset(&observer->last_command, 0, sizeof(observer->last_command));
	observer->last_command.forward = observer->forward;
	observer->last_command.up = observer->up;
	observer->last_command.field_of_view = observer->field_of_view;

	observer->trailer_signature = OBSERVER_SIGNATURE;
	observer->header_signature = OBSERVER_SIGNATURE;
	observer->updated_for_frame = TRUE;
	observer->first_command = FALSE;

	return;
}

static void observer_update_command(
	short local_player_index)
{
	short parameter_index;
	struct observer *observer = observer_get(local_player_index);
	real *pending_timer = observer->pending_command->parameter_timers;
	real const *last_timer = observer->last_command.parameter_timers;
	byte const *pending_flags = observer->pending_command->parameter_flags;

	match_assert_valid_observer_command("c:\\halo\\SOURCE\\camera\\observer.c", 370, observer->pending_command);

	if (TEST_FLAG(observer->pending_command->flags, _observer_command_valid_bit))
	{
		for (parameter_index = 0; parameter_index < NUMBER_OF_OBSERVER_PARAMETERS; parameter_index++, pending_timer++, last_timer++, pending_flags++)
		{
			if (TEST_FLAG(*pending_flags, _observer_time_valid_bit))
			{
				if (!TEST_FLAG(*pending_flags, _observer_time_force_bit))
				{
					if (*pending_timer < *last_timer)
					{
						*pending_timer = CEILING(*last_timer, 2.f);
					}
				}
			}
			else
			{
				if (observer->pending_command->timer < *last_timer && !TEST_FLAG(observer->pending_command->flags, _observer_command_force_time_bit))
				{
					*pending_timer = CEILING(*last_timer, 2.f);
				}
				else
				{
					*pending_timer = observer->pending_command->timer;
				}
			}
		}

		observer->last_command = *observer->pending_command;
	}

	return;
}

static void observer_pass_time(
	short local_player_index)
{
	short parameter_index;
	struct observer *observer = observer_get(local_player_index);
	real *timer = observer->last_command.parameter_timers;

	if (!TEST_FLAG(observer->pending_command->flags, _observer_command_freeze_camera_bit))
	{
		observer_update_displacements(local_player_index);
		observer_update_polynomial(local_player_index);
		observer_update_accelerations(local_player_index);
		observer_update_velocities(local_player_index);
		observer_update_positions(local_player_index);

		for (parameter_index = 0; parameter_index < NUMBER_OF_OBSERVER_PARAMETERS; parameter_index++, timer++)
		{
			*timer = MAX(*timer - observer_globals.dtime, 0.f);
		}
	}

	return;
}

static void observer_update_displacements(
	short local_player_index)
{
	struct observer *observer = observer_get(local_player_index);

	observer_find_displacement(observer->positions, observer->last_command.parameters, &observer->displacements);

	return;
}

static void observer_update_polynomial(
	short local_player_index)
{
	short parameter_index;
	short real_index;
	struct observer *observer = observer_get(local_player_index);
	real const *acceleration = observer->accelerations.n;
	real const *displacement = observer->displacements.n;
	real const *velocity = observer->velocities.n;
	real *a = observer->a;
	real *b = observer->b;
	real *c = observer->c;
	real *d = observer->d;
	real *e = observer->e;
	real *f = observer->f;
	real const *timer = observer->last_command.parameter_timers;

	match_assert_valid_observer_command("c:\\halo\\SOURCE\\camera\\observer.c", 502, &observer->last_command);

	for (parameter_index = 0; parameter_index < NUMBER_OF_OBSERVER_PARAMETERS; parameter_index++)
	{
		if (TEST_FLAG(observer->last_command.flags, _observer_command_valid_bit) && *timer > observer_globals.dtime)
		{
			real t1 = 1.f / *timer;
			real t2 = t1 * t1;
			real t3 = t2 * t1;
			real t4 = t3 * t1;
			real t5 = t4 * t1;

			for (real_index = 0; real_index < observer_parameter_derivative_real_counts[parameter_index]; real_index++)
			{
				a[real_index] = -6.f*t5*displacement[real_index] + -3.f*t4*velocity[real_index] + 0.5f*t3*acceleration[real_index];
				b[real_index] = 15.f*t4*displacement[real_index] + 7.f*t3*velocity[real_index] + -1.f*t2*acceleration[real_index];
				c[real_index] = -10.f*t3*displacement[real_index] + -4.f*t2*velocity[real_index] + 0.5f*t1*acceleration[real_index];
				d[real_index] = 0.f;
				e[real_index] = 0.f;
				f[real_index] = displacement[real_index];

				if (parameter_index == _observer_focus_position)
				{
					real focus_velocity = observer->last_command.focus_velocity.n[real_index] * 30.f;

					a[real_index] = a[real_index] - 3.f*focus_velocity*t4;
					b[real_index] = 8.f*focus_velocity*t3 + b[real_index];
					c[real_index] = c[real_index] - 6.f*focus_velocity*t2;
					e[real_index] = e[real_index] + focus_velocity;
				}
			}
		}

		acceleration += observer_parameter_derivative_real_counts[parameter_index];
		displacement += observer_parameter_derivative_real_counts[parameter_index];
		velocity += observer_parameter_derivative_real_counts[parameter_index];
		a += observer_parameter_derivative_real_counts[parameter_index];
		b += observer_parameter_derivative_real_counts[parameter_index];
		c += observer_parameter_derivative_real_counts[parameter_index];
		d += observer_parameter_derivative_real_counts[parameter_index];
		e += observer_parameter_derivative_real_counts[parameter_index];
		f += observer_parameter_derivative_real_counts[parameter_index];
		timer++;
	}

	return;
}

static void observer_update_accelerations(
	short local_player_index)
{
	short parameter_index;
	short real_index;
	short timer_index;
	struct observer *observer = observer_get(local_player_index);
	real *acceleration = observer->accelerations.n;
	real const *displacement = observer->displacements.n;
	real const *velocity = observer->velocities.n;
	real const *a = observer->a;
	real const *b = observer->b;
	real const *c = observer->c;
	real const *d = observer->d;
	real const *e = observer->e;
	real const *f = observer->f;
	real *timer = observer->last_command.parameter_timers;

	for (parameter_index = 0; parameter_index < NUMBER_OF_OBSERVER_PARAMETERS; parameter_index++)
	{
		real time_remaining = *timer - observer_globals.dtime;
		real const *unused;

		if (time_remaining > 0.f)
		{
			real t2 = time_remaining * time_remaining;
			real t3 = t2 * time_remaining;

			for (real_index = 0; real_index < observer_parameter_derivative_real_counts[parameter_index]; real_index++)
			{
				acceleration[real_index] = 20.f*a[real_index]*t3 + 12.f*b[real_index]*t2 + 6.f*c[real_index]*time_remaining + 2.f*d[real_index];

				if (acceleration[real_index] > observer_maximum_accelerations[parameter_index] || acceleration[real_index] < -observer_maximum_accelerations[parameter_index])
				{
					for (timer_index = 0; timer_index < NUMBER_OF_OBSERVER_PARAMETERS; timer_index++)
					{
						if (timer_index != parameter_index && observer->last_command.parameter_timers[timer_index] == *timer)
						{
							observer->last_command.parameter_timers[timer_index] = 0.f;
						}
					}

					*timer = 0.f;
				}
			}
		}
		else
		{
			csmemset(acceleration, 0, observer_parameter_derivative_real_counts[parameter_index] * sizeof(real));
		}

		acceleration += observer_parameter_derivative_real_counts[parameter_index];
		displacement += observer_parameter_derivative_real_counts[parameter_index];
		velocity += observer_parameter_derivative_real_counts[parameter_index];
		a += observer_parameter_derivative_real_counts[parameter_index];
		b += observer_parameter_derivative_real_counts[parameter_index];
		c += observer_parameter_derivative_real_counts[parameter_index];
		d += observer_parameter_derivative_real_counts[parameter_index];
		e += observer_parameter_derivative_real_counts[parameter_index];
		f += observer_parameter_derivative_real_counts[parameter_index];
		timer++;
	}

	return;
}

static void observer_update_velocities(
	short local_player_index)
{
	short parameter_index;
	short real_index;
	struct observer *observer = observer_get(local_player_index);
	real const *displacement = observer->displacements.n;
	real *velocity = observer->velocities.n;
	real const *a = observer->a;
	real const *b = observer->b;
	real const *c = observer->c;
	real const *d = observer->d;
	real const *e = observer->e;
	real const *f = observer->f;
	real const *timer = observer->last_command.parameter_timers;
	byte const *flags = observer->last_command.parameter_flags;
	real inverse_dtime = 1.0 / observer_globals.dtime;

	for (parameter_index = 0; parameter_index < NUMBER_OF_OBSERVER_PARAMETERS; parameter_index++)
	{
		real time_remaining = *timer - observer_globals.dtime;
		real const *unused;

		if (time_remaining > 0.f)
		{
			real t2 = time_remaining * time_remaining;
			real t3 = t2 * time_remaining;
			real t4 = t3 * time_remaining;

			for (real_index = 0; real_index < observer_parameter_derivative_real_counts[parameter_index]; real_index++)
			{
				velocity[real_index] = 5.f*a[real_index]*t4 + 4.f*b[real_index]*t3 + 3.f*c[real_index]*t2 + 2.f*d[real_index]*time_remaining + e[real_index];
			}
		}
		else
		{
			if (TEST_FLAG(observer->last_command.flags, _observer_command_valid_bit) && (TEST_FLAG(*flags, _observer_time_force_bit) || TEST_FLAG(observer->last_command.flags, _observer_command_force_time_bit)))
			{
				csmemset(velocity, 0, observer_parameter_derivative_real_counts[parameter_index] * sizeof(real));
			}
			else if (TEST_FLAG(observer->last_command.flags, _observer_command_valid_bit))
			{
				for (real_index = 0; real_index < observer_parameter_derivative_real_counts[parameter_index]; real_index++)
				{
					velocity[real_index] = -displacement[real_index] * inverse_dtime;
				}
			}
		}

		displacement += observer_parameter_derivative_real_counts[parameter_index];
		velocity += observer_parameter_derivative_real_counts[parameter_index];
		a += observer_parameter_derivative_real_counts[parameter_index];
		b += observer_parameter_derivative_real_counts[parameter_index];
		c += observer_parameter_derivative_real_counts[parameter_index];
		d += observer_parameter_derivative_real_counts[parameter_index];
		e += observer_parameter_derivative_real_counts[parameter_index];
		f += observer_parameter_derivative_real_counts[parameter_index];
		timer++;
		flags++;
	}

	return;
}

static void observer_update_positions(
	short local_player_index)
{
	struct observer_derivative new_camera_displacements;
	short parameter_index;
	struct observer *observer = observer_get(local_player_index);
	real *position = observer->positions;
	real const *velocity = observer->velocities.n;
	real *new_displacement = new_camera_displacements.n;
	real const *parameter = observer->last_command.parameters;
	real const *a = observer->a;
	real const *b = observer->b;
	real const *c = observer->c;
	real const *d = observer->d;
	real const *e = observer->e;
	real const *f = observer->f;
	real const *timer = observer->last_command.parameter_timers;

	for (parameter_index = 0; parameter_index < NUMBER_OF_OBSERVER_CARTESIAN_VELOCITIES + NUMBER_OF_OBSERVER_POLAR_VELOCITIES; parameter_index++)
	{
		match_assert_valid_real("c:\\halo\\SOURCE\\camera\\observer.c", 756, observer->velocities.n[parameter_index]);
	}

	for (parameter_index = 0; parameter_index < NUMBER_OF_OBSERVER_PARAMETERS; parameter_index++)
	{
		real time_remaining = *timer - observer_globals.dtime;
		real const *unused;

		if (time_remaining > 0.f || !(observer->last_command.flags & FLAG(_observer_command_valid_bit)))
		{
			short real_index;

			if (time_remaining > 0.f)
			{
				real t2 = time_remaining * time_remaining;
				real t3 = t2 * time_remaining;
				real t4 = t3 * time_remaining;
				real t5 = t4 * time_remaining;
				real t6;

				for (real_index = 0; real_index < observer_parameter_derivative_real_counts[parameter_index]; real_index++)
				{
					new_displacement[real_index] = a[real_index]*t5 + b[real_index]*t4 + c[real_index]*t3 + d[real_index]*t2 + e[real_index]*time_remaining + f[real_index];
				}
			}
			else
			{
				for (real_index = 0; real_index < observer_parameter_derivative_real_counts[parameter_index]; real_index++)
				{
					new_displacement[real_index] = -(velocity[real_index] * observer_globals.dtime);
				}
			}

			if (parameter_index < _observer_orientation)
			{
				for (real_index = 0; real_index < observer_parameter_derivative_real_counts[parameter_index]; real_index++)
				{
					position[real_index] += new_displacement[real_index];
				}
			}
			else
			{
				observer_apply_rotational_displacement((real_vector3d *)new_displacement, (real_vector3d *)position, (real_vector3d *)(position + 3));
			}
		}
		else
		{
			short real_index;

			for (real_index = 0; real_index < observer_parameter_real_counts[parameter_index]; real_index++)
			{
				position[real_index] = parameter[real_index];
			}
		}

		position += observer_parameter_real_counts[parameter_index];
		parameter += observer_parameter_real_counts[parameter_index];
		velocity += observer_parameter_derivative_real_counts[parameter_index];
		new_displacement += observer_parameter_derivative_real_counts[parameter_index];
		a += observer_parameter_derivative_real_counts[parameter_index];
		b += observer_parameter_derivative_real_counts[parameter_index];
		c += observer_parameter_derivative_real_counts[parameter_index];
		d += observer_parameter_derivative_real_counts[parameter_index];
		e += observer_parameter_derivative_real_counts[parameter_index];
		f += observer_parameter_derivative_real_counts[parameter_index];
		timer++;
	}

	position = observer->positions + 8;

	for (parameter_index = _observer_orientation; parameter_index < NUMBER_OF_OBSERVER_PARAMETERS; parameter_index++)
	{
		real_vector3d *forward = (real_vector3d *)position;
		real_vector3d *up = (real_vector3d *)(position + 3);

		if (!valid_real_vector3d_axes2(forward, up))
		{
			real_vector3d left;

			cross_product3d(up, forward, &left);
			cross_product3d(forward, &left, up);
			normalize3d(forward);
			normalize3d(up);
		}

		position += observer_parameter_real_counts[parameter_index];
	}

	return;
}

static void observer_find_displacement(
	real const *position0,
	real const *position1,
	struct observer_derivative *displacement)
{
	short real_index;
	real *displacement_real = displacement->n;

	for (real_index = 0; real_index < NUMBER_OF_OBSERVER_CARTESIAN_REALS; real_index++)
	{
		*displacement_real++ = *position1++ - *position0++;
	}

	for (; real_index < NUMBER_OF_OBSERVER_REAL_PARAMETERS; real_index += 6)
	{
		observer_rotational_displacement(
			(real_vector3d const *)position0,
			(real_vector3d const *)(position0 + 3),
			(real_vector3d const *)position1,
			(real_vector3d const *)(position1 + 3),
			(real_vector3d *)displacement_real);

		position0 += 6;
		position1 += 6;
		displacement_real += 3;
	}

	return;
}

static void observer_rotational_displacement(
	real_vector3d const *forward0,
	real_vector3d const *up0,
	real_vector3d const *forward1,
	real_vector3d const *up1,
	real_vector3d *rotation)
{
	real_matrix4x3 orientation_matrix0;
	real_matrix4x3 orientation_matrix1;

	match_assert_valid_real_vector3d_axes2("c:\\halo\\SOURCE\\camera\\observer.c", 898, forward0, up0);
	match_assert_valid_real_vector3d_axes2("c:\\halo\\SOURCE\\camera\\observer.c", 899, forward1, up1);

	matrix4x3_rotation_from_vectors(&orientation_matrix0, forward0, up0);
	matrix4x3_rotation_from_vectors(&orientation_matrix1, forward1, up1);
	vector_from_matrices4x3(&orientation_matrix0, &orientation_matrix1, rotation);

	return;
}

static void observer_apply_rotational_displacement(
	real_vector3d const *rotational_displacement,
	real_vector3d *forward,
	real_vector3d *up)
{
	real_vector3d axis_of_rotation = *rotational_displacement;
	real angle = normalize3d(&axis_of_rotation);

	if (angle != 0.f)
	{
		real sine = sin(angle);
		real cosine = cos(angle);

		rotate_vector_about_axis(forward, &axis_of_rotation, sine, cosine);
		rotate_vector_about_axis(up, &axis_of_rotation, sine, cosine);
	}

	return;
}

static void observer_postcheck(
	short local_player_index)
{
	real_vector2d camera_horizontal;
	real water_depth;
	struct observer *observer = observer_get(local_player_index);
	real_point3d focus_position = observer->focus_position;
	real focus_distance = PIN(observer->focus_distance, 0.f, REAL_MAX);

	match_assert("c:\\halo\\SOURCE\\camera\\observer.c", 943, valid_world_real_point3d(&focus_position));
	match_assert_valid_real_vector3d_axes2("c:\\halo\\SOURCE\\camera\\observer.c", 944, &observer->forward, &observer->up);
	match_assert("c:\\halo\\SOURCE\\camera\\observer.c", 945, valid_world_real_point3d((real_point3d *) &observer->focus_offset));
	match_assert("c:\\halo\\SOURCE\\camera\\observer.c", 946, valid_focus_distance(focus_distance));

	observer->field_of_view = PIN(observer->field_of_view, 0.001f, _half_pi);
	focus_position.x = PIN(focus_position.x, -MAXIMUM_WORLD_COORDINATE, MAXIMUM_WORLD_COORDINATE);
	focus_position.y = PIN(focus_position.y, -MAXIMUM_WORLD_COORDINATE, MAXIMUM_WORLD_COORDINATE);
	focus_position.z = PIN(focus_position.z, -MAXIMUM_WORLD_COORDINATE, MAXIMUM_WORLD_COORDINATE);
	focus_distance = PIN(focus_distance, 0.f, MAXIMUM_WORLD_COORDINATE);

	camera_horizontal.i = observer->forward.i;
	camera_horizontal.j = observer->forward.j;
	normalize2d(&camera_horizontal);

	focus_position.x = observer->focus_offset.i*camera_horizontal.i + observer->focus_offset.j*camera_horizontal.j + focus_position.x;
	focus_position.y = observer->focus_offset.i*camera_horizontal.j - observer->focus_offset.j*camera_horizontal.i + focus_position.y;
	focus_position.z = focus_position.z + observer->focus_offset.k;

	if (!TEST_FLAG(observer->last_command.flags, _observer_command_ignore_obstructions_bit) && focus_distance != 0.f)
	{
		observer_check_penetration(&focus_position, &observer->forward, &observer->up, &focus_distance, 0.02f);
	}

	observer->result.position.x = focus_position.x - focus_distance*observer->forward.i;
	observer->result.position.y = focus_position.y - focus_distance*observer->forward.j;
	observer->result.position.z = focus_position.z - focus_distance*observer->forward.k;

	{
		struct location new_location;

		scenario_location_from_point(&new_location, &observer->result.position);

		if (new_location.cluster_index != NONE)
		{
			if (new_location.cluster_index != observer->result.location.cluster_index)
			{
				predicted_resources_precache(&TAG_BLOCK_GET_ELEMENT(&global_structure_bsp_get()->clusters, new_location.cluster_index, struct structure_cluster)->predicted_resources);
			}

			observer->result.location = new_location;
		}
	}

	water_depth = scenario_location_water_depth(&observer->result.location, &observer->result.position);

	if (fabs(water_depth) < 0.05f)
	{
		if (water_depth > 0.f)
		{
			observer->result.position.z = observer->result.position.z - (0.05f - water_depth);
		}
		else
		{
			observer->result.position.z = 0.05f + water_depth + observer->result.position.z;
		}
	}

	match_assert("c:\\halo\\SOURCE\\camera\\observer.c", 1055, valid_world_real_point3d(&observer->result.position));
	match_assert_valid_real_vector3d_axes2("c:\\halo\\SOURCE\\camera\\observer.c", 1056, &observer->forward, &observer->up);
	match_assert("c:\\halo\\SOURCE\\camera\\observer.c", 1057, valid_field_of_view(observer->field_of_view));

	observer->result.position.x = PIN(observer->result.position.x, -MAXIMUM_WORLD_COORDINATE, MAXIMUM_WORLD_COORDINATE);
	observer->result.position.y = PIN(observer->result.position.y, -MAXIMUM_WORLD_COORDINATE, MAXIMUM_WORLD_COORDINATE);
	observer->result.position.z = PIN(observer->result.position.z, -MAXIMUM_WORLD_COORDINATE, MAXIMUM_WORLD_COORDINATE);

	observer->result.velocity.i = -observer->velocities.focus_position.i;
	observer->result.velocity.j = -observer->velocities.focus_position.j;
	observer->result.velocity.k = -observer->velocities.focus_position.k;
	observer->result.forward = observer->forward;
	observer->result.up = observer->up;
	observer->result.field_of_view = observer->field_of_view;

	return;
}

static void observer_check_penetration(
	real_point3d *focus_position,
	real_vector3d const *forward,
	real_vector3d const *up,
	real *distance,
	real safe_distance)
{
	static real const sine_region_angle = 0.174f;

	real safe_t = 1.f;
	struct location location;
	real_vector3d camera_ray;
	real_point3d camera_point;
	boolean ignore_media;
	real minimum_t;
	real_vector3d const *minimum_basis;
	real minimum_sign;
	real region_radius;
	real_vector3d camera_region_basis[2];
	short basis_index;

	scenario_location_from_point(&location, focus_position);
	ignore_media = scenario_location_underwater(&location, focus_position, NULL);

	camera_ray.i = -(*distance + safe_distance) * forward->i;
	camera_ray.j = -(*distance + safe_distance) * forward->j;
	camera_ray.k = -(*distance + safe_distance) * forward->k;
	camera_point.x = focus_position->x + camera_ray.i;
	camera_point.y = focus_position->y + camera_ray.j;
	camera_point.z = focus_position->z + camera_ray.k;

	observer_collision_test_with_t(focus_position, &camera_point, &safe_t, ignore_media);

	minimum_t = safe_t;
	minimum_basis = NULL;
	region_radius = sine_region_angle * *distance;

	camera_region_basis[0] = *up;
	cross_product3d(up, forward, &camera_region_basis[1]);
	camera_region_basis[0].i = camera_region_basis[0].i * region_radius;
	camera_region_basis[0].j = camera_region_basis[0].j * region_radius;
	camera_region_basis[0].k = camera_region_basis[0].k * region_radius;
	camera_region_basis[1].i = camera_region_basis[1].i * region_radius;
	camera_region_basis[1].j = camera_region_basis[1].j * region_radius;
	camera_region_basis[1].k = camera_region_basis[1].k * region_radius;

	for (basis_index = 0; basis_index < 4; basis_index++)
	{
		real sign = (basis_index & 2) ? 1 : -1;
		real t;

		if (observer_collision_test_differential(focus_position, &camera_point, &camera_region_basis[basis_index & 1], sign, &t, ignore_media) && t < minimum_t)
		{
			minimum_t = t;
			minimum_basis = &camera_region_basis[basis_index & 1];
			minimum_sign = sign;
		}
	}

	if (minimum_basis)
	{
		real low = 0.f;
		real high = minimum_sign;
		real safe_low_t = safe_t;
		real safe_high_t = minimum_t;
		short iteration;

		for (iteration = 0; iteration < 10; iteration++)
		{
			real middle = (low + high) * 0.5f;
			real t;
			boolean collision = observer_collision_test_differential(focus_position, &camera_point, minimum_basis, middle, &t, ignore_media);

			if (collision && fabs(t - safe_high_t) < 0.1f)
			{
				high = middle;
				safe_high_t = t;
			}
			else
			{
				low = middle;
				safe_low_t = collision ? t : 1.f;
			}
		}

		{
			real fraction = ABS(safe_low_t < safe_high_t ? low : high);

			safe_t = fraction*safe_t + (1.f - fraction)*minimum_t;
		}
	}

	*distance = *distance * safe_t;

	return;
}

static boolean observer_collision_test_with_t(
	real_point3d const *p0,
	real_point3d const *p1,
	real *t,
	boolean ignore_media)
{
	struct collision_result collision;
	unsigned long flags = FLAG(_collision_test_front_facing_surfaces_bit) | FLAG(_collision_test_structure_bit) | FLAG(_collision_test_media_bit) | FLAG(_collision_test_objects_bit) | FLAG(_collision_test_objects_scenery_bit);
	boolean success = FALSE;

	if (ignore_media)
	{
		SET_FLAG(flags, _collision_test_media_bit, FALSE);
	}

	match_collision_log_begin_user("c:\\halo\\SOURCE\\camera\\observer.c", 1204, _collision_user_observer);

	if (collision_test_line(flags, p0, p1, NONE, &collision))
	{
		*t = collision.t;
		success = TRUE;
	}

	match_collision_log_end_user("c:\\halo\\SOURCE\\camera\\observer.c", 1210);

	return success;
}

static boolean observer_collision_test_differential(
	real_point3d const *origin,
	real_point3d const *destination,
	real_vector3d const *differential_basis,
	real differential,
	real *t,
	boolean ignore_media)
{
	real_point3d destination_plus_d;

	point_from_line3d(destination, differential_basis, differential, &destination_plus_d);

	return observer_collision_test_with_t(origin, &destination_plus_d, t, ignore_media);
}
