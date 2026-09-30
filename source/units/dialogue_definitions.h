/*
DIALOGUE_DEFINITIONS.H

header included in hcex build.
*/

#ifndef __DIALOGUE_DEFINITIONS_H
#define __DIALOGUE_DEFINITIONS_H
#pragma once

/* ---------- constants */

enum
{
	NUMBER_OF_VOCALIZATION_TYPES = 209
};

/* ---------- macros */

/* ---------- structures */

/* ---------- prototypes/EXAMPLE.C */

short dialogue_get_vocalization_type_by_name(char const *name);
char const *dialogue_get_vocalization_name(short vocalization_type, boolean unknown);

/* ---------- globals */

/* ---------- public code */

#endif // __DIALOGUE_DEFINITIONS_H
