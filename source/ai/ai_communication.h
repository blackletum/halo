/*
AI_COMMUNICATION.H

header included in hcex build.
*/

#ifndef __AI_COMMUNICATION_H
#define __AI_COMMUNICATION_H
#pragma once

/* ---------- headers */

#include "ai.h"
#include "ai_constants.h"

/* ---------- constants */

enum
{
	NUMBER_OF_AI_COMMUNICATION_TYPES = 57
};

/* ---------- macros */

/* ---------- structures */

/* ---------- prototypes/AI_COMMUNICATION.C */

void ai_communication_packet_new(struct ai_information_packet *information);

short ai_communication_get_type_by_name(char const *name);
real ai_communication_get_player_rating(long unit_index, boolean test_line_of_sight, long *unit_index_reference, real *distance_reference);

/* ---------- globals */

/* ---------- public code */

#endif // __AI_COMMUNICATION_H
