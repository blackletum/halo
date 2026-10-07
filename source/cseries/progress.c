/*
PROGRESS.C

symbols in this file:
00080280 0060:
	_progress_new (0000)
000802E0 0080:
	_progress_update (0000)
00258688 0005:
	??_C@_04PJOLNDGD@data?$AA@ (0000)
00258690 0022:
	??_C@_0CC@EAAFHEOB@c?3?2halo?2SOURCE?2cseries?2progress?4@ (0000)
*/

/* ---------- headers */

#include "cseries.h"

/* ---------- constants */

/* ---------- macros */

/* ---------- structures */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

void progress_new(
	struct progress *progress,
	struct progress_callbacks const *callbacks,
	char const *description,
	long maximum)
{
	memset(progress, 0, sizeof(*progress));

	if (callbacks && callbacks->update_proc)
	{
		progress->callbacks.update_proc = callbacks->update_proc;
		progress->callbacks.user_data = callbacks->user_data;

		if (description)
		{
			strncpy(progress->description, description, PROGRESS_STRING_LENGTH);
		}

		progress->maximum = maximum;
	}

	return;
}

void progress_update(
	struct progress *progress,
	char const *status,
	long current,
	boolean force)
{
	match_assert("c:\\halo\\SOURCE\\cseries\\progress.c", 35, progress);

	if (progress->callbacks.update_proc && progress->maximum)
	{
		unsigned long time = system_milliseconds();
		unsigned long elapsed = time - progress->last_milliseconds;

		if (elapsed > PROGRESS_UPDATE_FREQUENCY_IN_MILLISECONDS || force)
		{
			progress->callbacks.update_proc(progress->callbacks.user_data, progress->description, status, (current * 100) / progress->maximum);
			progress->last_milliseconds = time;
		}
	}

	return;
}

/* ---------- private code */
