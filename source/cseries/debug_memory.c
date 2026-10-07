/*
DEBUG_MEMORY.C

symbols in this file:
0007CCC0 0030:
	_debug_memory_manager_initialize (0000)
0007CCF0 0050:
	_code_0007ccf0 (0000)
0007CD40 0050:
	_code_0007cd40 (0000)
0007CD90 0030:
	_code_0007cd90 (0000)
0007CDC0 0020:
	_code_0007cdc0 (0000)
0007CDE0 0050:
	_check_memory_status (0000)
0007CE30 0010:
	_local_random (0000)
0007CE40 0110:
	_code_0007ce40 (0000)
0007CF50 0070:
	_code_0007cf50 (0000)
0007CFC0 00a0:
	_code_0007cfc0 (0000)
0007D060 00e0:
	_code_0007d060 (0000)
0007D140 00b0:
	_debug_check_memory (0000)
0007D1F0 00e0:
	_debug_dump_memory_for_file (0000)
0007D2D0 0200:
	_debug_dump_memory_by_file (0000)
0007D4D0 0110:
	_debug_malloc (0000)
0007D5E0 00d0:
	_debug_free (0000)
0007D6B0 01a0:
	_debug_realloc (0000)
0007D850 0010:
	_debug_dump_memory (0000)
00257820 003c:
	??_C@_0DM@OPHCCCEJ@Debug?5memory?5manager?5is?5uninitia@ (0000)
0025785C 0026:
	??_C@_0CG@MJFPFHAG@c?3?2halo?2SOURCE?2cseries?2debug_mem@ (0000)
00257888 0052:
	??_C@_0FC@OHFGNKPI@Pointer?5allocated?5at?5?$CFs?0?5?$CFd?5has?5@ (0000)
002578E0 004c:
	??_C@_0EM@MBCHGNP@memory?5check?5failed?5at?5?$CFs?0?5diffe@ (0000)
00257930 0060:
	??_C@_0GA@PLIGMMOI@Invalid?5pointer?3?5header?3?50x?$CFx?5si@ (0000)
00257990 0017:
	??_C@_0BH@JLBIJIH@Checksum?5is?5incorrect?4?$AA@ (0000)
002579A8 0018:
	??_C@_0BI@HDCLMAAI@Signature?5is?5incorrect?4?$AA@ (0000)
002579C0 001b:
	??_C@_0BL@CLGIALFN@Pointer?5has?5been?5disposed?4?$AA@ (0000)
002579E0 0059:
	??_C@_0FJ@FAIAKDFC@Attempted?5an?5operation?5with?5poin@ (0000)
00257A40 005a:
	??_C@_0FK@OHOEBNNG@Attempted?5an?5operation?5with?5poin@ (0000)
00257A9C 0008:
	??_C@_07PFMCDPMA@pointer?$AA@ (0000)
00257AA4 0009:
	??_C@_08KCJKEBBA@previous?$AA@ (0000)
00257AB0 0020:
	??_C@_0CA@HBGNFHPA@?$AN?6Total?5Allocated?3?5?$CFd?5bytes?$AN?6?$AN?6?$AA@ (0000)
00257AD0 0020:
	??_C@_0CA@BMBACHBF@?$CF?540s?5?5?$CF?56d?5?$CF?510d?5?$CF?510d?5bytes?$AN?6?$AA@ (0000)
00257AF0 001a:
	??_C@_0BK@OKIDMCBD@?$CF?540s?5?5?$CF?56s?5?$CF?510s?5?$CF?510s?$AN?6?$AA@ (0000)
00257B0C 0005:
	??_C@_04HJPCFDOP@line?$AA@ (0000)
00257B14 0003:
	??_C@_02EGCJHIOB@id?$AA@ (0000)
00257B18 0005:
	??_C@_04IAGNFIBA@size?$AA@ (0000)
00257B20 0011:
	??_C@_0BB@NOMJNHJF@d?3?2heap_dump?4txt?$AA@ (0000)
00257B34 0004:
	??_C@_03DOPCBAKB@a?$CLb?$AA@ (0000)
00257B38 0049:
	??_C@_0EJ@PBGKLMDM@?$AN?6Total?3?5?$CF40d?5bytes?5in?5?$CF4d?5point@ (0000)
00257B84 003b:
	??_C@_0DL@LDKOLIEH@total_pointer_size?$DN?$DNdebug_memory@ (0000)
00257BC0 0047:
	??_C@_0EH@ELPDFPOK@File?3?5?$CF32s?5?$CF8d?5bytes?5in?5?$CF4d?5poin@ (0000)
00257C08 0027:
	??_C@_0CH@ICOHMPPJ@file_count?$DMMAXIMUM_FILES_WITH_PO@ (0000)
00257C30 0025:
	??_C@_0CF@FHDKMLKL@size?$DO?$DN0?5?$CG?$CG?5size?$DMMAXIMUM_POINTER_@ (0000)
00257C58 0010:
	??_C@_0BA@BEKDBLPJ@pointer?5?$HM?$HM?5size?$AA@ (0000)
002DCD0C 0020:
	_data_002dcd0c (0000)
*/

/* ---------- headers */

#include "cseries.h"

/* ---------- constants */

enum
{
	DEBUG_MEMORY_GLOBALS_SIGNATURE = 'SAFT', /* fake name */
	POINTER_HEADER_SIGNATURE = '--->', /* fake name */
	POINTER_TRAILER_SIGNATURE = '<---', /* fake name */
	POINTER_FREED_SIGNATURE = '<BAD', /* fake name */

	MAXIMUM_POINTER_SIZE = 0x10000000,
	MAXIMUM_FILES_WITH_POINTERS = 512,

	MEMORY_STATUS_WARNING_DIFFERENCE = 0x4000, /* fake name */
	UNINITIALIZED_MEMORY_FILL = 0xca, /* fake name */
};

/* ---------- macros */

/* ---------- structures */

struct pointer_header
{
	unsigned long signature;
	struct pointer_header *next;
	struct pointer_header *previous;
	unsigned int size;
	char const *source_file;
	long source_line;
	long identifier;
	unsigned long checksum;
};

struct pointer_trailer
{
	unsigned long signature;
};

struct debug_memory_globals_definition /* fake name */
{
	unsigned long header_signature;
	long current_heap_size;
	long largest_heap_size;
	struct pointer_header *header_queue;
	struct pointer_header *valid_header_range_bottom;
	struct pointer_header *valid_header_range_top;
	long identifier;
	unsigned long trailer_signature;
};

struct debug_source_file_data /* fake name */
{
	char const *name;
	long total_count;
	long minimum_size;
	long maximum_size;
	long total_size;
};

/* ---------- prototypes */

static void check_debug_memory_globals(char const *source_file, long source_line);
static void check_pointer(void *pointer, char const *source_file, long source_line);
static unsigned long checksum_header(struct pointer_header *header);
static int compare_files_by_total_size(void const *elem0, void const *elem1);
static void check_header(struct pointer_header *header, char const *source_file, long source_line);
static void debug_randomize_memory(void *pointer, unsigned int size);
static void queue_header(struct pointer_header *header);
static void dequeue_header(struct pointer_header *header, char const *source_file, long source_line);

/* ---------- globals */

static struct debug_memory_globals_definition debug_memory_globals =
{
	DEBUG_MEMORY_GLOBALS_SIGNATURE,
	0,
	0,
	NULL,
	NULL,
	NULL,
	0,
	DEBUG_MEMORY_GLOBALS_SIGNATURE
};

/* ---------- public code */

void debug_memory_manager_initialize(
	void)
{
	debug_memory_globals.header_signature = DEBUG_MEMORY_GLOBALS_SIGNATURE;
	debug_memory_globals.current_heap_size = 0;
	debug_memory_globals.largest_heap_size = 0;
	debug_memory_globals.header_queue = NULL;
	debug_memory_globals.valid_header_range_bottom = NULL;
	debug_memory_globals.valid_header_range_top = NULL;
	debug_memory_globals.trailer_signature = DEBUG_MEMORY_GLOBALS_SIGNATURE;

	return;
}

void check_memory_status(
	struct memory_status *status,
	char const *string)
{
	MEMORYSTATUS memory_status;
	unsigned long difference;

	GlobalMemoryStatus(&memory_status);
	status->minimum_free = MIN(memory_status.dwAvailPhys, status->minimum_free);
	status->maximum_free = MAX(memory_status.dwAvailPhys, status->maximum_free);

	difference = status->maximum_free - status->minimum_free;

	if (difference > MEMORY_STATUS_WARNING_DIFFERENCE)
	{
		error(_error_silent, "memory check failed at %s, difference between min and max memory free is %d", string, difference);
	}

	return;
}

void debug_check_memory(
	char const *source_file,
	long source_line)
{
	struct pointer_header *header;

	check_debug_memory_globals(source_file, source_line);

	for (header = debug_memory_globals.header_queue; header; header = header->next)
	{
		check_header(header, source_file, source_line);
		check_pointer(header + 1, source_file, source_line);
	}

	return;
}

void debug_dump_memory_for_file(
	char const *source_file_substring)
{
	FILE *dump_file = NULL;
	struct pointer_header *header = debug_memory_globals.header_queue;
	long total = 0;

	debug_check_memory("c:\\halo\\SOURCE\\cseries\\debug_memory.c", 513);

	while (header)
	{
		if (!source_file_substring || strstr(header->source_file, source_file_substring))
		{
			if (!dump_file)
			{
				dump_file = fopen("d:\\heap_dump.txt", "a+b");

				if (dump_file)
				{
					fprintf(dump_file, "% 40s  % 6s % 10s % 10s\r\n", "file", "line", "id", "size");
				}
			}

			if (dump_file)
			{
				fprintf(dump_file, "% 40s  % 6d % 10d % 10d bytes\r\n", header->source_file, header->source_line, header->identifier, header->size);
			}

			total += header->size;
		}

		header = header->next;
	}

	if (dump_file)
	{
		fprintf(dump_file, "\r\nTotal Allocated: %d bytes\r\n\r\n", total);
		fclose(dump_file);
	}

	return;
}

void debug_dump_memory_by_file(
	void)
{
	struct debug_source_file_data files[MAXIMUM_FILES_WITH_POINTERS];
	short file_count = 0;
	long total_pointer_count = 0;
	long total_pointer_size = 0;
	struct pointer_header *header = debug_memory_globals.header_queue;

	debug_check_memory("c:\\halo\\SOURCE\\cseries\\debug_memory.c", 553);

	while (header)
	{
		short file_index;

		total_pointer_count++;
		total_pointer_size += header->size;

		for (file_index = 0; file_index < file_count; file_index++)
		{
			if (header->source_file == files[file_index].name)
			{
				files[file_index].total_count++;
				files[file_index].total_size += header->size;

				if (header->size < (unsigned int)files[file_index].minimum_size)
				{
					files[file_index].minimum_size = header->size;
				}

				if (header->size > (unsigned int)files[file_index].maximum_size)
				{
					files[file_index].maximum_size = header->size;
				}

				break;
			}
		}

		if (file_index == file_count)
		{
			match_assert("c:\\halo\\SOURCE\\cseries\\debug_memory.c", 585, file_count<MAXIMUM_FILES_WITH_POINTERS);
			files[file_count].name = header->source_file;
			files[file_count].total_count = 1;
			files[file_count].total_size = files[file_count].minimum_size = files[file_count].maximum_size = header->size;
			file_count++;
		}

		header = header->next;
	}

	if (file_count)
	{
		FILE *dump_file = fopen("d:\\heap_dump.txt", "a+b");

		if (dump_file)
		{
			short file_index;

			qsort(files, file_count, sizeof(files[0]), compare_files_by_total_size);

			for (file_index = 0; file_index < file_count; file_index++)
			{
				fprintf(dump_file, "File: %32s %8d bytes in %4d pointers. (Min: %8d Max: %8d Avg: %5.3f)\r\n", files[file_index].name, files[file_index].total_size, files[file_index].total_count, files[file_index].minimum_size, files[file_index].maximum_size, (real)files[file_index].total_size / files[file_index].total_count);
			}

			match_assert("c:\\halo\\SOURCE\\cseries\\debug_memory.c", 612, total_pointer_size==debug_memory_globals.current_heap_size);
			fprintf(dump_file, "\r\nTotal: %40d bytes in %4d pointers\r\n\r\nLargest Heap Size: %28d bytes\r\n\r\n", total_pointer_size, total_pointer_count, debug_memory_globals.largest_heap_size);
			fclose(dump_file);
		}
	}

	return;
}

void *debug_malloc(
	unsigned int size,
	boolean clear,
	char const *source_file,
	long source_line)
{
	struct pointer_header *header = NULL;
	void *user_pointer = NULL;
	unsigned int system_size = size + sizeof(struct pointer_header) + sizeof(struct pointer_trailer);

	match_assert("c:\\halo\\SOURCE\\cseries\\debug_memory.c", 214, size>=0 && size<MAXIMUM_POINTER_SIZE);
	check_debug_memory_globals(source_file, source_line);

	header = system_malloc(system_size);

	if (header)
	{
		struct pointer_trailer *trailer;

		header->signature = POINTER_HEADER_SIGNATURE;
		header->source_line = source_line;
		header->source_file = source_file;
		header->identifier = debug_memory_globals.identifier++;
		header->size = size;
		trailer = (struct pointer_trailer *)((byte *)(header + 1) + header->size);
		trailer->signature = POINTER_TRAILER_SIGNATURE;
		queue_header(header);

		user_pointer = header + 1;

		if (clear)
		{
			memset(user_pointer, 0, size);
		}
		else
		{
			memset(user_pointer, UNINITIALIZED_MEMORY_FILL, size);
		}
	}

	if (user_pointer)
	{
		debug_memory_globals.current_heap_size += size;

		if (debug_memory_globals.largest_heap_size < debug_memory_globals.current_heap_size)
		{
			debug_memory_globals.largest_heap_size = debug_memory_globals.current_heap_size;
		}
	}

	return user_pointer;
}

void debug_free(
	void *pointer,
	char const *source_file,
	long source_line)
{
	struct pointer_header *header = (struct pointer_header *)pointer - 1;

	check_debug_memory_globals(source_file, source_line);
	check_header(header, source_file, source_line);
	check_pointer(header + 1, source_file, source_line);
	debug_memory_globals.current_heap_size -= header->size;
	dequeue_header(header, source_file, source_line);
	header->signature = POINTER_FREED_SIGNATURE;
	system_free(header);

	return;
}

void *debug_realloc(
	void *pointer,
	unsigned int size,
	char const *source_file,
	long source_line)
{
	struct pointer_header *header = NULL;
	void *user_pointer = NULL;
	struct pointer_header *old_header = NULL;
	unsigned int system_size = size + sizeof(struct pointer_header) + sizeof(struct pointer_trailer);
	unsigned int old_size = 0;

	match_assert("c:\\halo\\SOURCE\\cseries\\debug_memory.c", 337, pointer || size);
	match_assert("c:\\halo\\SOURCE\\cseries\\debug_memory.c", 338, size>=0 && size<MAXIMUM_POINTER_SIZE);
	check_debug_memory_globals(source_file, source_line);

	if (pointer)
	{
		struct pointer_header *pointer_header = (struct pointer_header *)pointer - 1;

		check_header(pointer_header, source_file, source_line);
		check_pointer(pointer, source_file, source_line);
		dequeue_header(pointer_header, source_file, source_line);
		pointer_header->signature = POINTER_FREED_SIGNATURE;
		old_header = pointer_header;
		source_file = pointer_header->source_file;
		source_line = pointer_header->source_line;
		old_size = pointer_header->size;
	}

	header = system_realloc(old_header, !size && pointer ? 0 : system_size);

	if (header)
	{
		struct pointer_trailer *trailer;

		header->signature = POINTER_HEADER_SIGNATURE;
		header->source_line = source_line;
		header->source_file = source_file;
		header->identifier = debug_memory_globals.identifier++;
		header->size = size;
		trailer = (struct pointer_trailer *)((byte *)(header + 1) + header->size);
		trailer->signature = POINTER_TRAILER_SIGNATURE;
		queue_header(header);

		user_pointer = header + 1;

		if (size > old_size)
		{
			debug_randomize_memory((byte *)user_pointer + old_size, size - old_size);
		}
	}

	if (user_pointer || !size)
	{
		debug_memory_globals.current_heap_size += size - old_size;

		if (debug_memory_globals.largest_heap_size < debug_memory_globals.current_heap_size)
		{
			debug_memory_globals.largest_heap_size = debug_memory_globals.current_heap_size;
		}
	}

	return user_pointer;
}

void debug_dump_memory(
	void)
{
	debug_dump_memory_for_file(NULL);

	return;
}

/* ---------- private code */

static void check_debug_memory_globals(
	char const *source_file,
	long source_line)
{
	match_vassert("c:\\halo\\SOURCE\\cseries\\debug_memory.c", 145, debug_memory_globals.header_signature == DEBUG_MEMORY_GLOBALS_SIGNATURE && debug_memory_globals.trailer_signature == DEBUG_MEMORY_GLOBALS_SIGNATURE,
		csprintf("Debug memory manager is uninitialized or corrupted. (%s:%d)", (char *)source_file, source_line));

	return;
}

static void check_pointer(
	void *pointer,
	char const *source_file,
	long source_line)
{
	struct pointer_header *header = (struct pointer_header *)pointer - 1;
	struct pointer_trailer const *trailer = (struct pointer_trailer const *)((byte *)pointer + header->size);

	match_vassert("c:\\halo\\SOURCE\\cseries\\debug_memory.c", 199, trailer->signature == POINTER_TRAILER_SIGNATURE,
		csprintf(temporary, "Pointer allocated at %s, %d has overrun the end of its buffer. (Size: %d) (%s:%d)", header->source_file, header->source_line, header->size, source_file, source_line));

	return;
}

static unsigned long checksum_header(
	struct pointer_header *header)
{
	unsigned long checksum;

	crc_new(&checksum);
	crc_checksum_buffer(&checksum, header, offsetof(struct pointer_header, checksum));

	return checksum;
}

static int compare_files_by_total_size(
	void const *elem0,
	void const *elem1)
{
	struct debug_source_file_data const *row0 = elem0;
	struct debug_source_file_data const *row1 = elem1;

	return row1->total_size - row0->total_size;
}

static void check_header(
	struct pointer_header *header,
	char const *source_file,
	long source_line)
{
	char const *failure = NULL;

	match_vassert("c:\\halo\\SOURCE\\cseries\\debug_memory.c", 160, debug_memory_globals.header_queue,
		csprintf(temporary, "Attempted an operation with pointer at 0x%x when no pointers have been allocated. (%s:%d)", header + 1, source_file, source_line));
	match_vassert("c:\\halo\\SOURCE\\cseries\\debug_memory.c", 165, header >= debug_memory_globals.valid_header_range_bottom && header <= debug_memory_globals.valid_header_range_top,
		csprintf(temporary, "Attempted an operation with pointer at 0x%x, outside of the valid pointer range. (%s:%d)", header + 1, source_file, source_line));

	if (header->signature == POINTER_FREED_SIGNATURE)
	{
		failure = "Pointer has been disposed.";
	}
	else if (header->signature != POINTER_HEADER_SIGNATURE)
	{
		failure = "Signature is incorrect.";
	}
	else if (checksum_header(header) != header->checksum)
	{
		failure = "Checksum is incorrect.";
	}

	match_vassert("c:\\halo\\SOURCE\\cseries\\debug_memory.c", 183, !failure,
		csprintf(temporary, "Invalid pointer: header: 0x%x signature: 0x%x line: %d file: 0x%x size: 0x%x reason: %s (%s:%d)", header, header->signature, header->source_line, header->source_file, header->size, failure, source_file, source_line));

	return;
}

static void debug_randomize_memory(
	void *pointer,
	unsigned int size)
{
	byte *p;

	match_assert("c:\\halo\\SOURCE\\cseries\\debug_memory.c", 269, pointer);

	for (p = pointer; p < (byte *)pointer + size - 1; p += sizeof(word))
	{
		*(word *)p = local_random();
	}

	if (size & 1)
	{
		((byte *)pointer)[size - 1] = (byte)local_random();
	}

	return;
}

static void queue_header(
	struct pointer_header *header)
{
	if (!debug_memory_globals.header_queue || header < debug_memory_globals.valid_header_range_bottom)
	{
		debug_memory_globals.valid_header_range_bottom = header;
	}

	if (!debug_memory_globals.header_queue || header > debug_memory_globals.valid_header_range_top)
	{
		debug_memory_globals.valid_header_range_top = header;
	}

	header->next = debug_memory_globals.header_queue;

	if (debug_memory_globals.header_queue)
	{
		debug_memory_globals.header_queue->previous = header;
		header->next->checksum = checksum_header(header->next);
	}

	header->previous = NULL;
	debug_memory_globals.header_queue = header;
	header->checksum = checksum_header(header);

	return;
}

static void dequeue_header(
	struct pointer_header *header,
	char const *source_file,
	long source_line)
{
	if (header == debug_memory_globals.header_queue)
	{
		debug_memory_globals.header_queue = header->next;

		if (debug_memory_globals.header_queue)
		{
			debug_memory_globals.header_queue->previous = NULL;
			debug_memory_globals.header_queue->checksum = checksum_header(debug_memory_globals.header_queue);
		}
	}
	else
	{
		struct pointer_header *previous = header->previous;

		match_assert("c:\\halo\\SOURCE\\cseries\\debug_memory.c", 446, previous);
		previous->next = header->next;
		previous->checksum = checksum_header(previous);

		if (previous->next)
		{
			previous->next->previous = previous;
			previous->next->checksum = checksum_header(previous->next);
		}
	}

	return;
}
