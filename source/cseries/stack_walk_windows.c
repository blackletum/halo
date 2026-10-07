/*
STACK_WALK_WINDOWS.C

symbols in this file:
000806A0 0020:
	_stack_walk_global_function_offset (0000)
000806C0 0010:
	_stack_walk_disregard_symbol_names (0000)
000806D0 0030:
	_code_000806d0 (0000)
00080700 0080:
	_free_symbol_table (0000)
00080780 00b0:
	_symbol_name_from_address (0000)
00080830 0060:
	_base_address_from_symbol_name (0000)
00080890 0020:
	_code_00080890 (0000)
000808B0 0040:
	_code_000808b0 (0000)
000808F0 0020:
	_code_000808f0 (0000)
00080910 00d0:
	_code_00080910 (0000)
000809E0 00d0:
	_code_000809e0 (0000)
00080AB0 0020:
	_stack_walk_dispose (0000)
00080AD0 02b0:
	_stack_walk_with_context (0000)
00080D80 0620:
	_load_symbol_table (0000)
000813A0 0030:
	_stack_walk_initialize (0000)
000813D0 0020:
	_stack_walk (0000)
002586B4 000d:
	??_C@_0N@CNIOPMPL@symbol_table?$AA@ (0000)
002586C4 002c:
	??_C@_0CM@LOAPPLNB@c?3?2halo?2SOURCE?2cseries?2stack_wal@ (0000)
002586F0 0010:
	??_C@_0BA@OFOBHDCE@?$CFs?5?$CL?5?$CF04lX?5?3?5?$CFs?$AA@ (0000)
00258700 000a:
	??_C@_09JLKGDFIH@?$CF08lX?5?$CFs?6?$AA@ (0000)
0025870C 0029:
	??_C@_0CJ@POGHEDC@EIP?3?50x?$CF08lX?0?5?$CF02lX?5?$CF02lX?5?$CF02lX?5@ (0000)
00258738 000d:
	??_C@_0N@DEGIIKCL@ESP?3?50x?$CF08lX?$AA@ (0000)
00258748 000d:
	??_C@_0N@KDNFCLLI@EBP?3?50x?$CF08lX?$AA@ (0000)
00258758 000d:
	??_C@_0N@OBNDHAGF@ESI?3?50x?$CF08lX?$AA@ (0000)
00258768 000d:
	??_C@_0N@JJFDHEBG@EDI?3?50x?$CF08lX?$AA@ (0000)
00258778 000d:
	??_C@_0N@PGCLGPBN@EDX?3?50x?$CF08lX?$AA@ (0000)
00258788 000d:
	??_C@_0N@ICLDIGJC@ECX?3?50x?$CF08lX?$AA@ (0000)
00258798 000d:
	??_C@_0N@BJBGMKPN@EBX?3?50x?$CF08lX?$AA@ (0000)
002587A8 000d:
	??_C@_0N@GOIIBIAN@EAX?3?50x?$CF08lX?$AA@ (0000)
002587B8 0009:
	??_C@_08CCCCNONO@?$CF08lX?5?$CFs?$AA@ (0000)
002587C4 0006:
	??_C@_05EHMBKEBF@?$DP?$DP?$DP?$DP?$DP?$AA@ (0000)
002587CC 0025:
	??_C@_0CF@JNHFBDOE@Printing?5stuff?5for?5Mat?8s?5edifica@ (0000)
002587F4 002e:
	??_C@_0CO@DKHIBCJD@could?5not?5allocate?5enough?5memory@ (0000)
00258828 0051:
	??_C@_0FB@FDLBMJMP@string_storage_used?5?$CL?5strlen?$CIlib@ (0000)
00258880 0044:
	??_C@_0EE@HFHPDHDJ@string_storage_used?5?$CL?5strlen?$CIsym@ (0000)
002588C8 006b:
	??_C@_0GL@HCCMEKIO@string_storage_used?5?$CL?5strlen?$CIsym@ (0000)
00258934 0013:
	??_C@_0BD@IFIGKEIG@_load_symbol_table?$AA@ (0000)
00258948 000f:
	??_C@_0P@JLHKGDG@Static?5symbols?$AA@ (0000)
00258958 000f:
	??_C@_0P@BNEDFJAM@entry?5point?5at?$AA@ (0000)
00258968 0005:
	??_C@_04DNCNJDPH@?5?7?6?$AN?$AA@ (0000)
00258970 0002:
	??_C@_01JLIPDDHJ@?3?$AA@ (0000)
00258974 0008:
	??_C@_07DFGIHOIL@nothing?$AA@ (0000)
0025897C 0019:
	??_C@_0BJ@BLEJAHCK@map?5file?5appears?5corrupt?$AA@ (0000)
00258998 000a:
	??_C@_09KDGENIOP@Timestamp?$AA@ (0000)
002589A4 000b:
	??_C@_0L@CKIHAGIB@Lib?3Object?$AA@ (0000)
002589B0 001c:
	??_C@_0BM@LBIFOOIP@Couldn?8t?5read?5map?5file?5?8?$CFs?8?$AA@ (0000)
002589CC 0011:
	??_C@_0BB@LJHACKGC@d?3?2cachebeta?4map?$AA@ (0000)
002589E0 0019:
	??_C@_0BJ@NNIPHMJN@Mon?5Dec?517?512?349?336?52001?$AA@ (0000)
002DCD40 0014:
	_stack_walk_globals (0000)
00431C98 4008:
	_bss_00431c98 (0000)
*/

/* ---------- headers */

#include "cseries.h"

/* ---------- constants */

enum
{
	MAXIMUM_STACK_WALK_LEVELS = 64, /* fake name */
	MAXIMUM_MAP_FILE_LINE_LENGTH = 16384, /* fake name */
	MAXIMUM_SYMBOL_NAME_LENGTH = 256,
	SYMBOL_TABLE_SYMBOL_INCREMENT = 0x1000, /* fake name */
	SYMBOL_TABLE_STRING_STORAGE_INCREMENT = 0x4000, /* fake name */
	MAXIMUM_SYMBOL_OFFSET = 0xffff, /* fake name */
};

/* ---------- macros */

/* ---------- structures */

struct debug_symbol_table
{
	long number_of_symbols;
	char *string_storage;
	struct debug_symbol *symbols;
};

struct debug_symbol
{
	unsigned long address;
	unsigned long rva_base;
	unsigned long name_string_offset;
	unsigned long library_object_string_offset;
};

struct _stack_walk_globals
{
	long fixup;
	boolean disregard_symbol_names;
	struct debug_symbol_table symbol_table;
};

/* ---------- prototypes */

static int symbol_sort_proc(void const *elem1, void const *elem2);
static boolean is_valid_ebp(void);
static unsigned long walk_up(void);
static void initialize_stack_walk(CONTEXT *context);
static void walk_stack_context(unsigned long *routine_addresses, unsigned long number_of_levels, unsigned long ignore_levels, unsigned long *levels_dumped);
static void walk_stack(unsigned long *routine_addresses, unsigned long number_of_levels, unsigned long ignore_levels, unsigned long *levels_dumped);


/* ---------- globals */

struct _stack_walk_globals stack_walk_globals =
{
	NONE,
	FALSE
};

static unsigned long *old_ebp;
static unsigned long old_esp; /* fake name */

/* ---------- public code */

long stack_walk_global_function_offset(
	void)
{
	return stack_walk_globals.fixup == NONE ? 0 : stack_walk_globals.fixup;
}

void stack_walk_disregard_symbol_names(
	boolean disregard)
{
	stack_walk_globals.disregard_symbol_names = disregard;

	return;
}

static int symbol_sort_proc(
	void const *elem1,
	void const *elem2)
{
	struct debug_symbol *symbol1 = (struct debug_symbol *)elem1;
	struct debug_symbol *symbol2 = (struct debug_symbol *)elem2;
	int result;

	if (!symbol1->rva_base || symbol1->rva_base > symbol2->rva_base)
	{
		result = 1;
	}
	else if (!symbol2->rva_base || symbol1->rva_base < symbol2->rva_base)
	{
		result = -1;
	}
	else
	{
		result = 0;
	}

	return result;
}

void free_symbol_table(
	struct debug_symbol_table *symbol_table)
{
	match_assert("c:\\halo\\SOURCE\\cseries\\stack_walk_windows.c", 549, symbol_table);

	if (symbol_table->string_storage)
	{
		debug_free(symbol_table->string_storage, "c:\\halo\\SOURCE\\cseries\\stack_walk_windows.c", 551);
	}

	if (symbol_table->symbols)
	{
		debug_free(symbol_table->symbols, "c:\\halo\\SOURCE\\cseries\\stack_walk_windows.c", 552);
	}

	symbol_table->number_of_symbols = 0;
	symbol_table->string_storage = NULL;
	symbol_table->symbols = NULL;

	return;
}

char *symbol_name_from_address(
	unsigned long fake_address,
	struct debug_symbol_table *symbol_table)
{
	static char symbol_buffer[16384];
	unsigned long address = fake_address + stack_walk_globals.fixup;

	strcpy(symbol_buffer, "<unknown>");

	if (symbol_table->number_of_symbols > 0 &&
		address >= symbol_table->symbols[0].rva_base &&
		address < symbol_table->symbols[symbol_table->number_of_symbols - 1].rva_base + MAXIMUM_SYMBOL_OFFSET)
	{
		long symbol_index;

		for (symbol_index = 1; symbol_index < symbol_table->number_of_symbols; symbol_index++)
		{
			if (symbol_table->symbols[symbol_index - 1].rva_base <= address && address < symbol_table->symbols[symbol_index].rva_base)
			{
				_snprintf(symbol_buffer, sizeof(symbol_buffer) - 1, "%s + %04lX : %s",
					symbol_table->string_storage + symbol_table->symbols[symbol_index - 1].name_string_offset,
					address - symbol_table->symbols[symbol_index - 1].rva_base,
					symbol_table->string_storage + symbol_table->symbols[symbol_index - 1].library_object_string_offset);
				break;
			}
		}
	}

	return symbol_buffer;
}

unsigned long base_address_from_symbol_name(
	char const *name,
	struct debug_symbol_table *symbol_table)
{
	unsigned long result = NONE;
	long symbol_index;

	for (symbol_index = 1; symbol_index < symbol_table->number_of_symbols; symbol_index++)
	{
		char *symbol_name = symbol_table->string_storage + symbol_table->symbols[symbol_index].name_string_offset;

		if (!strcmp(name, symbol_name))
		{
			result = symbol_table->symbols[symbol_index].rva_base;
		}
	}

	return result;
}

static boolean is_valid_ebp(
	void)
{
	return 0 == ((unsigned long)old_ebp & 3) && (unsigned long)old_ebp >= old_esp;
}

static unsigned long walk_up(
	void)
{
	unsigned long return_address = 0;

	if (old_ebp)
	{
		return_address = old_ebp[1];
		old_ebp = (unsigned long *)old_ebp[0];

		if (!is_valid_ebp())
		{
			old_ebp = NULL;
		}

		old_esp = (unsigned long)old_ebp;
	}

	return return_address;
}

static void initialize_stack_walk(
	CONTEXT *context)
{
	old_esp = context->Esp;
	old_ebp = (unsigned long *)context->Ebp;

	return;
}

static void walk_stack_context(
	unsigned long *routine_addresses,
	unsigned long number_of_levels,
	unsigned long ignore_levels,
	unsigned long *levels_dumped)
{
	unsigned long level;

	if (!is_valid_ebp())
	{
		old_ebp = NULL;
	}

	if (ignore_levels)
	{
		ignore_levels--;
	}

	while (ignore_levels)
	{
		walk_up();
		ignore_levels--;
	}

	for (level = 0; level < number_of_levels; level++)
	{
		routine_addresses[level] = walk_up();

		if (!routine_addresses[level])
		{
			break;
		}
	}

	*levels_dumped = level;

	return;
}

static void walk_stack(
	unsigned long *routine_addresses,
	unsigned long number_of_levels,
	unsigned long ignore_levels,
	unsigned long *levels_dumped)
{
	unsigned long level;

	__asm
	{
		mov old_ebp, ebp
		mov old_esp, esp
	}

	if (!is_valid_ebp())
	{
		old_ebp = NULL;
	}

	if (ignore_levels)
	{
		ignore_levels--;
	}

	while (ignore_levels)
	{
		walk_up();
		ignore_levels--;
	}

	for (level = 0; level < number_of_levels; level++)
	{
		routine_addresses[level] = walk_up();

		if (!routine_addresses[level])
		{
			break;
		}
	}

	*levels_dumped = level;

	return;
}

void stack_walk_dispose(
	void)
{
	stack_walk_globals.fixup = NONE;
	stack_walk_globals.disregard_symbol_names = FALSE;
	free_symbol_table(&stack_walk_globals.symbol_table);

	return;
}

void stack_walk_with_context(
	FILE *error_stream,
	short levels_to_ignore,
	CONTEXT *context_pointer)
{
	long frame_number;
	unsigned long addresses[MAXIMUM_STACK_WALK_LEVELS] = { 0 };

	if (context_pointer)
	{
		initialize_stack_walk(context_pointer);
		walk_stack_context(addresses, MAXIMUM_STACK_WALK_LEVELS, levels_to_ignore, &frame_number);
	}
	else
	{
		walk_stack(addresses, MAXIMUM_STACK_WALK_LEVELS, levels_to_ignore, &frame_number);
	}

	if (!error_stream)
	{
		long function_index;

		error(_error_silent, "Printing stuff for Mat's edification");

		for (function_index = frame_number - 1; function_index >= levels_to_ignore; function_index--)
		{
			unsigned long function_address = addresses[function_index] + *(long *)(addresses[function_index] - sizeof(long));

			error(_error_silent, "%08lX %s", function_address, stack_walk_globals.symbol_table.number_of_symbols && !stack_walk_globals.disregard_symbol_names ? symbol_name_from_address(function_address, &stack_walk_globals.symbol_table) : "?????");
		}
	}

	if (context_pointer)
	{
		unsigned long instruction = *(unsigned long *)context_pointer->Eip;
		unsigned long byte0 = instruction & 0xff;
		unsigned long byte1 = (instruction >> 8) & 0xff;
		unsigned long byte2 = (instruction >> 16) & 0xff;
		unsigned long byte3 = (instruction >> 24) & 0xff;

		error(_error_silent, "EAX: 0x%08lX", context_pointer->Eax);
		error(_error_silent, "EBX: 0x%08lX", context_pointer->Ebx);
		error(_error_silent, "ECX: 0x%08lX", context_pointer->Ecx);
		error(_error_silent, "EDX: 0x%08lX", context_pointer->Edx);
		error(_error_silent, "EDI: 0x%08lX", context_pointer->Edi);
		error(_error_silent, "ESI: 0x%08lX", context_pointer->Esi);
		error(_error_silent, "EBP: 0x%08lX", context_pointer->Ebp);
		error(_error_silent, "ESP: 0x%08lX", context_pointer->Esp);
		error(_error_silent, "EIP: 0x%08lX, %02lX %02lX %02lX %02lX %s", context_pointer->Eip, byte0, byte1, byte2, byte3,
			stack_walk_globals.symbol_table.number_of_symbols && !stack_walk_globals.disregard_symbol_names ? symbol_name_from_address(context_pointer->Eip, &stack_walk_globals.symbol_table) : "?????");
	}

	{
		long address_index;

		for (address_index = frame_number - 1; address_index >= levels_to_ignore; address_index--)
		{
			if (!error_stream)
			{
				error(_error_silent, "%08lX %s", addresses[address_index], stack_walk_globals.symbol_table.number_of_symbols && !stack_walk_globals.disregard_symbol_names ? symbol_name_from_address(addresses[address_index], &stack_walk_globals.symbol_table) : "?????");
			}
			else
			{
				fprintf(error_stream, "%08lX %s\n", addresses[address_index], stack_walk_globals.symbol_table.number_of_symbols && !stack_walk_globals.disregard_symbol_names ? symbol_name_from_address(addresses[address_index], &stack_walk_globals.symbol_table) : "?????");
			}
		}
	}

	return;
}

boolean load_symbol_table(
	char *filename,
	struct debug_symbol_table *symbol_table,
	char *timestamp_str)
{
	boolean success = TRUE;
	FILE *file = NULL;

	match_assert("c:\\halo\\SOURCE\\cseries\\stack_walk_windows.c", 256, symbol_table);
	memset(symbol_table, 0, sizeof(*symbol_table));

	file = fopen(filename, "r");

	if (!file)
	{
		error(_error_silent, "Couldn't read map file '%s'", filename);
		success = FALSE;
	}
	else
	{
		char line[MAXIMUM_MAP_FILE_LINE_LENGTH] = "";

		if (!fgets(line, MAXIMUM_MAP_FILE_LINE_LENGTH, file))
		{
			success = FALSE;
		}

		while (success)
		{
			if (fgets(line, MAXIMUM_MAP_FILE_LINE_LENGTH, file))
			{
				if (strstr(line, "Lib:Object"))
				{
					break;
				}
				else if (strstr(line, "Timestamp"))
				{
					strstr(line, timestamp_str);
				}
			}
			else
			{
				error(_error_silent, "map file appears corrupt");
				success = FALSE;
			}
		}

		if (success)
		{
			char last_object_file_name[MAXIMUM_SYMBOL_NAME_LENGTH];
			unsigned long last_object_file_name_offset;
			unsigned long string_storage_size = 0;
			unsigned long string_storage_used = 0;
			unsigned long maximum_symbols = 0;
			boolean corrupt = TRUE;
			boolean out_of_memory = FALSE;

			strcpy(last_object_file_name, "nothing");
			last_object_file_name_offset = NONE;

			while (TRUE)
			{
				if (fgets(line, MAXIMUM_MAP_FILE_LINE_LENGTH, file))
				{
					char *token;
					unsigned long address;
					unsigned long rva_base;
					char symbol_name[MAXIMUM_SYMBOL_NAME_LENGTH];
					char library_object_file_name[MAXIMUM_SYMBOL_NAME_LENGTH];
					char *delimiters = " \t\n\r";
					char *end_str = NULL;

					token = strtok(line, ":");

					if (token && *token == ' ')
					{
						token = strtok(NULL, delimiters);

						if (token)
						{
							address = strtoul(token, &end_str, 16);
						}
						else
						{
							break;
						}

						token = strtok(NULL, delimiters);

						if (token)
						{
							strncpy(symbol_name, token, MAXIMUM_SYMBOL_NAME_LENGTH - 1);
							symbol_name[MAXIMUM_SYMBOL_NAME_LENGTH - 1] = '\0';
						}
						else if (strstr(line, "entry point at"))
						{
							fgets(line, MAXIMUM_MAP_FILE_LINE_LENGTH, file);

							if (!isspace(line[0]))
							{
								break;
							}

							fgets(line, MAXIMUM_MAP_FILE_LINE_LENGTH, file);

							if (!strstr(line, "Static symbols"))
							{
								break;
							}

							fgets(line, MAXIMUM_MAP_FILE_LINE_LENGTH, file);

							if (!isspace(line[0]))
							{
								break;
							}

							fgets(line, MAXIMUM_MAP_FILE_LINE_LENGTH, file);
							token = strtok(line, ":");

							if (token && *token == ' ')
							{
								token = strtok(NULL, delimiters);

								if (token)
								{
									address = strtoul(token, &end_str, 16);
								}
								else
								{
									break;
								}

								token = strtok(NULL, delimiters);

								if (token)
								{
									strncpy(symbol_name, token, MAXIMUM_SYMBOL_NAME_LENGTH - 1);
									symbol_name[MAXIMUM_SYMBOL_NAME_LENGTH - 1] = '\0';
								}
							}
							else
							{
								break;
							}
						}
						else
						{
							break;
						}

						token = strtok(NULL, delimiters);

						if (token)
						{
							rva_base = strtoul(token, &end_str, 16);

							if (!strcmp(symbol_name, "_load_symbol_table"))
							{
								stack_walk_globals.fixup = rva_base - (unsigned long)load_symbol_table;
							}
						}
						else
						{
							break;
						}

						if (!end_str)
						{
							break;
						}

						end_str += 5;
						token = strtok(end_str, delimiters);

						if (token)
						{
							strncpy(library_object_file_name, token, MAXIMUM_SYMBOL_NAME_LENGTH - 1);
							library_object_file_name[MAXIMUM_SYMBOL_NAME_LENGTH - 1] = '\0';
						}
						else
						{
							break;
						}

						if ((unsigned long)symbol_table->number_of_symbols >= maximum_symbols)
						{
							struct debug_symbol *symbols;

							maximum_symbols += SYMBOL_TABLE_SYMBOL_INCREMENT;
							symbols = debug_realloc(symbol_table->symbols, maximum_symbols * sizeof(struct debug_symbol), "c:\\halo\\SOURCE\\cseries\\stack_walk_windows.c", 454);

							if (!symbols)
							{
								out_of_memory = TRUE;
								break;
							}
							else
							{
								symbol_table->symbols = symbols;
							}
						}

						if (string_storage_used + strlen(symbol_name) + 1 + strlen(library_object_file_name) + 1 >= string_storage_size)
						{
							char *string_storage;

							string_storage_size += SYMBOL_TABLE_STRING_STORAGE_INCREMENT;
							string_storage = debug_realloc(symbol_table->string_storage, string_storage_size, "c:\\halo\\SOURCE\\cseries\\stack_walk_windows.c", 471);

							if (!string_storage)
							{
								out_of_memory = TRUE;
								break;
							}
							else
							{
								symbol_table->string_storage = string_storage;
							}

							match_assert("c:\\halo\\SOURCE\\cseries\\stack_walk_windows.c", 482, string_storage_used + strlen(symbol_name) + 1 + strlen(library_object_file_name) + 1 < string_storage_size);
						}

						{
							struct debug_symbol *symbol = &symbol_table->symbols[symbol_table->number_of_symbols++];

							symbol->address = address;
							symbol->rva_base = rva_base;

							match_assert("c:\\halo\\SOURCE\\cseries\\stack_walk_windows.c", 489, string_storage_used + strlen(symbol_name) + 1 < string_storage_size);
							strcpy(symbol_table->string_storage + string_storage_used, symbol_name);
							symbol->name_string_offset = string_storage_used;
							string_storage_used += strlen(symbol_name) + 1;

							if (!strcmp(last_object_file_name, library_object_file_name))
							{
								symbol->library_object_string_offset = last_object_file_name_offset;
							}
							else
							{
								match_assert("c:\\halo\\SOURCE\\cseries\\stack_walk_windows.c", 501, string_storage_used + strlen(library_object_file_name) + 1 < string_storage_size);
								strcpy(symbol_table->string_storage + string_storage_used, library_object_file_name);
								symbol->library_object_string_offset = string_storage_used;
								string_storage_used += strlen(library_object_file_name) + 1;
								last_object_file_name_offset = symbol->library_object_string_offset;
								strcpy(last_object_file_name, library_object_file_name);
							}
						}
					}
				}
				else
				{
					corrupt = FALSE;
					break;
				}
			}

			if (out_of_memory)
			{
				error(_error_silent, "could not allocate enough memory for map file");
				free_symbol_table(symbol_table);
			}
			else if (corrupt)
			{
				error(_error_silent, "map file appears corrupt");
				free_symbol_table(symbol_table);
			}
		}
	}

	if (file)
	{
		fclose(file);
	}

	if (symbol_table->number_of_symbols > 0)
	{
		qsort(symbol_table->symbols, symbol_table->number_of_symbols, sizeof(struct debug_symbol), symbol_sort_proc);

		while (!symbol_table->symbols[symbol_table->number_of_symbols - 1].rva_base)
		{
			symbol_table->number_of_symbols--;
		}
	}

	return symbol_table->number_of_symbols > 0;
}

void stack_walk_initialize(
	void)
{
	load_symbol_table("d:\\cachebeta.map", &stack_walk_globals.symbol_table, "Mon Dec 17 12:49:36 2001");

	if (stack_walk_globals.fixup == NONE)
	{
		stack_walk_globals.fixup = 0;
	}

	return;
}

void stack_walk(
	short levels_to_ignore)
{
	stack_walk_with_context(NULL, (short)(levels_to_ignore + 1), NULL);

	return;
}

/* ---------- private code */
