/*
PROFILE.C

symbols in this file:
0007DCA0 0080:
	_profile_initialize (0000)
0007DD20 0160:
	_code_0007dd20 (0000)
0007DE80 0020:
	_profile_rasterizer_stats (0000)
0007DEA0 0040:
	_code_0007dea0 (0000)
0007DEE0 0010:
	_profile_seconds_elapsed (0000)
0007DEF0 0040:
	_profile_lapsed_frames (0000)
0007DF30 0020:
	_profile_lapsed_msec (0000)
0007DF50 0160:
	_find_profile_section (0000)
0007E0B0 0080:
	_profile_enter_private (0000)
0007E130 00a0:
	_profile_exit_private (0000)
0007E1D0 0610:
	_code_0007e1d0 (0000)
0007E7E0 0010:
	_code_0007e7e0 (0000)
0007E7F0 0050:
	_code_0007e7f0 (0000)
0007E840 0120:
	_compare_profile_sections (0000)
0007E960 0360:
	_profile_dump (0000)
0007ECC0 0080:
	_profile_dump_to_file (0000)
0007ED40 0080:
	_code_0007ed40 (0000)
0007EDC0 0040:
	_code_0007edc0 (0000)
0007EE00 0030:
	_code_0007ee00 (0000)
0007EE30 00a0:
	_code_0007ee30 (0000)
0007EED0 0020:
	_profile_sections_activate (0000)
0007EEF0 0020:
	_profile_sections_deactivate (0000)
0007EF10 0430:
	_profile_find_frame_value (0000)
0007F340 0040:
	_profile_find_game_value (0000)
0007F380 03a0:
	_profile_frame_get_value (0000)
0007F720 0060:
	_profile_frame_iterator_new (0000)
0007F780 0080:
	_profile_frame_iterator_next (0000)
0007F800 0090:
	_profile_frame_get_messages (0000)
0007F890 00a0:
	_profile_frame_get_stalls (0000)
0007F930 0090:
	_profile_rasterizer_stalls (0000)
0007F9C0 0030:
	_code_0007f9c0 (0000)
0007F9F0 0060:
	_code_0007f9f0 (0000)
0007FA50 0090:
	_profile_tick_start (0000)
0007FAE0 00a0:
	_profile_tick_end (0000)
0007FB80 0030:
	_profile_render_start (0000)
0007FBB0 0070:
	_profile_render_end (0000)
0007FC20 0090:
	_profile_render_window_start (0000)
0007FCB0 00a0:
	_profile_render_window_end (0000)
0007FD50 0030:
	_profile_texture_start (0000)
0007FD80 0070:
	_profile_texture_end (0000)
0007FDF0 0080:
	_profile_frame_start (0000)
0007FE70 0370:
	_profile_frame_end (0000)
000801E0 0030:
	_profile_idle_start (0000)
00080210 0070:
	_profile_idle_end (0000)
00257E54 0033:
	??_C@_0DD@GJHCEALK@?$HMl?$CFs?$HMt?$HMr?$CF?53?42f?1?$CF?54ld?$HMt?$CF?53?42f?1?$CF?54@ (0000)
00257E88 0044:
	??_C@_0EE@LGPEPOLG@?$CF?950s?$CF6ld?5?1?5?$CF7?43f?5?5?5?5?5?5?5?5?5?5?5?5?$CF5?4@ (0000)
00257ECC 0020:
	??_C@_0CA@IFDPKCJJ@?$HMt?$HMrthis?5frame?$HMtaverage?$HMtpeak?$HMn?$AA@ (0000)
00257EF0 0074:
	??_C@_0HE@OCELNIBL@section?7?5?5?5?5?5?5?5?5?5?5?5?5?5?5?5?5?5?5?5?5?5?5?5?5@ (0000)
00257F68 0041:
	??_C@_0EB@DNCFGCLL@parent_timesection?9?$DOself_msec?5?$DO?$DN@ (0000)
00257FAC 0021:
	??_C@_0CB@JIHDKIHN@c?3?2halo?2SOURCE?2cseries?2profile?4c@ (0000)
00257FD0 0037:
	??_C@_0DH@IAAOFPKE@profile_globals?4section_count?$DMMA@ (0000)
00258008 0039:
	??_C@_0DJ@MGEBDNKL@don?8t?5call?5profile_enter_private@ (0000)
00258044 0010:
	??_C@_0BA@OFIJJPPF@section?9?$DOactive?$AA@ (0000)
00258054 0008:
	??_C@_07BNGFJMOB@section?$AA@ (0000)
0025805C 001b:
	??_C@_0BL@DCGIKKDM@section?9?$DOstack_depth?$DN?$DNNONE?$AA@ (0000)
00258078 0032:
	??_C@_0DC@EBAGECGL@section?9?$DOstack_depth?$DN?$DNprofile_gl@ (0000)
002580AC 000e:
	??_C@_0O@CAINCP@f?9misc?5?$CF6?42f?5?$AA@ (0000)
002580BC 000e:
	??_C@_0O@HPDODOFI@r?9misc?5?$CF6?42f?5?$AA@ (0000)
002580CC 000b:
	??_C@_0L@CCBFPMDD@?5?5?5?5?5?5?5?5?5?5?$AA@ (0000)
002580D8 000a:
	??_C@_09DIDNDMFB@tex?$CF6?42f?5?$AA@ (0000)
002580E4 000d:
	??_C@_0N@ONKJJLFA@?5?5?5?5?5?5?5?5?5?5?5?5?$AA@ (0000)
002580F4 000c:
	??_C@_0M@CIJICDBL@stall?$CF6?42f?5?$AA@ (0000)
00258100 000a:
	??_C@_09LLNJGGAC@?5?5?5?5?5?5?5?$CFs?$AA@ (0000)
0025810C 000a:
	??_C@_09MEJENFBG@?$CFs?$CF6?42f?$CFs?$AA@ (0000)
00258118 0002:
	??_C@_01EFFIKLCJ@n?$AA@ (0000)
0025811C 0002:
	??_C@_01JBBJJEPG@p?$AA@ (0000)
00258120 000d:
	??_C@_0N@KKPPKAFO@?5render?$CF6?42f?$AA@ (0000)
00258130 0002:
	??_C@_01PKGAHCOL@?$CJ?$AA@ (0000)
00258134 0009:
	??_C@_08PBAHBJAK@?5?5?5?5?5?5?$CFs?$AA@ (0000)
00258140 0008:
	??_C@_07CCGGFFIN@?$CF6?42f?$CFs?$AA@ (0000)
00258148 0003:
	??_C@_02GFKOMOKH@?5?$CI?$AA@ (0000)
0025814C 0009:
	??_C@_08GLEMDNF@game?$CF2d?5?$AA@ (0000)
00258158 000c:
	??_C@_0M@CKHGFAEI@?5?5?5?5?5?5?5?5?5?5?5?$AA@ (0000)
00258164 000b:
	??_C@_0L@PHBKFODP@idle?$CF6?42f?5?$AA@ (0000)
00258170 000a:
	??_C@_09CIKJCKOO@?$CIsynced?$CJ?5?$AA@ (0000)
0025817C 000a:
	??_C@_09CCMCFOJI@?$CIslowed?$CJ?5?$AA@ (0000)
00258188 000a:
	??_C@_09CLBOIIGO@?$CIf?4?$CF3dms?$CJ?$AA@ (0000)
00258194 000a:
	??_C@_09LODAACPA@?$CIl?4?$CF3dms?$CJ?$AA@ (0000)
002581A0 000a:
	??_C@_09OAGDEMOJ@?$CIfree?$CF3d?$CJ?$AA@ (0000)
002581AC 000a:
	??_C@_09FOHHJKEH@?$CIlost?$CF3d?$CJ?$AA@ (0000)
002581B8 001e:
	??_C@_0BO@KFBPKJAE@frame?5?$CF5d?5vbl?5?$CF5I64d?5tot?$CF6?42f?$AA@ (0000)
002581D8 0008:
	__real@408f400000000000 (0000)
002581E0 0018:
	??_C@_0BI@LMKLONDN@maximum_section_count?$DO0?$AA@ (0000)
002581F8 0042:
	??_C@_0EC@FFADJNIP@format_mode?$DO?$DN0?5?$CG?$CG?5format_mode?$DMNU@ (0000)
0025823C 0037:
	??_C@_0DH@ICGEGPLO@sort_mode?$DO?$DN0?5?$CG?$CG?5sort_mode?$DMNUMBER@ (0000)
00258274 0005:
	??_C@_04LLEBNMDN@?$CFs?$AN?6?$AA@ (0000)
0025827C 000f:
	??_C@_0P@NHLICBHE@d?3?2profile?4txt?$AA@ (0000)
0025828C 0011:
	??_C@_0BB@MGJFLJKK@d?3?2framedump?4txt?$AA@ (0000)
002582A0 0003:
	??_C@_02GMLFBBN@wb?$AA@ (0000)
002582A4 0002:
	??_C@_01NBENCBCI@?$CK?$AA@ (0000)
002582A8 000b:
	??_C@_0L@KMPGOPBB@pushbuffer?$AA@ (0000)
002582B4 0004:
	??_C@_03HOPDAKLK@gpu?$AA@ (0000)
002582B8 0003:
	??_C@_02EDDPJOD@dt?$AA@ (0000)
002582BC 0008:
	??_C@_07JDHEGGGP@texture?$AA@ (0000)
002582C4 0006:
	??_C@_05MEMGOBLF@stall?$AA@ (0000)
002582CC 000c:
	??_C@_0M@BFMMLLIC@game_render?$AA@ (0000)
002582D8 000c:
	??_C@_0M@HBFEAABD@render0_3np?$AA@ (0000)
002582E4 000a:
	??_C@_09PKCOAFOC@render0_3?$AA@ (0000)
002582F0 000a:
	??_C@_09ODDFDEKD@render0_2?$AA@ (0000)
002582FC 000a:
	??_C@_09MIBIGHGA@render0_1?$AA@ (0000)
00258308 0008:
	??_C@_07HHKBOHGC@render0?$AA@ (0000)
00258310 0007:
	??_C@_06IAAOMEKN@render?$AA@ (0000)
00258318 000a:
	??_C@_09OHMOODOI@nonplayer?$AA@ (0000)
00258324 0008:
	??_C@_07OCBHBHOJ@player3?$AA@ (0000)
0025832C 0008:
	??_C@_07PLAMCGKI@player2?$AA@ (0000)
00258334 0008:
	??_C@_07NACBHFGL@player1?$AA@ (0000)
0025833C 0008:
	??_C@_07MJDKEECK@player0?$AA@ (0000)
00258344 0006:
	??_C@_05OIMJLJGC@game7?$AA@ (0000)
0025834C 0006:
	??_C@_05PBNCIICD@game6?$AA@ (0000)
00258354 0006:
	??_C@_05NKPPNLOA@game5?$AA@ (0000)
0025835C 0006:
	??_C@_05MDOEOKKB@game4?$AA@ (0000)
00258364 0006:
	??_C@_05IMKFHMGG@game3?$AA@ (0000)
0025836C 0006:
	??_C@_05JFLOENCH@game2?$AA@ (0000)
00258374 0006:
	??_C@_05LOJDBOOE@game1?$AA@ (0000)
0025837C 0006:
	??_C@_05KHIICPKF@game0?$AA@ (0000)
00258384 0005:
	??_C@_04EONOHKEP@load?$AA@ (0000)
0025838C 0006:
	??_C@_05MIJNFGED@frame?$AA@ (0000)
00258394 0020:
	??_C@_0CA@LFOMCIIE@name?5?$CG?$CG?5section_index_reference?$AA@ (0000)
002583B4 0004:
	__real@42055555 (0000)
002583B8 0004:
	__real@35aaaaab (0000)
002583C0 004e:
	??_C@_0EO@JBFLBLLD@iterator?9?$DOcurrent_buffer_index?5?$CB@ (0000)
00258410 0078:
	??_C@_0HI@EANDMEO@?$CIiterator?9?$DOcurrent_buffer_index?5@ (0000)
00258488 0087:
	??_C@_0IH@HJNMEKLP@?$CIprofile_globals?4current_frame?4g@ (0000)
00258510 0074:
	??_C@_0HE@FKBCHJEP@?$CIprofile_globals?4current_frame?4w@ (0000)
00258588 0075:
	??_C@_0HF@JPMAIONJ@?$CIprofile_globals?4current_frame?4w@ (0000)
00258600 0088:
	??_C@_0II@PFDJGDHA@?$CIprofile_globals?4current_frame?4g@ (0000)
002DCD30 0010:
	_header_strings (0000)
	_format_strings (0008)
0031DF40 113d54:
	_bss_0031df40 (0000)
	_profile_timebase_ticks (113d50)
	_profile_global_enable (113d51)
	_profile_dump_frames (113d52)
	_profile_dump_lost_frames (113d53)
*/

/* ---------- headers */

#include "cseries.h"
#include "profile.h"
#include "rasterizer.h"
#include "render.h"
#include "players.h"
#include "main.h"

/* ---------- constants */

enum
{
	MAXIMUM_PROFILE_SECTIONS = 256,
	PROFILE_SECTION_HISTORY_FRAMES = 120, /* fake name */
	MAXIMUM_PROFILE_FRAMES = 256, /* fake name */
	MAXIMUM_GAME_TICKS_PER_FRAME = 150,
	MAXIMUM_PROFILE_MESSAGE_LENGTH = 512, /* fake name */
	PROFILE_CLOCKS_PER_SECOND = 733333333, /* fake name */
	PROFILE_LOST_FRAME_PADDING = 3, /* fake name */
	PROFILE_INITIAL_LOST_FRAME_COUNT = 999, /* fake name */
	MINIMUM_DISPLAYED_GAME_TICKS = 8, /* fake name */
	PROFILE_PUSHBUFFER_SIZE = 768 * 1024, /* fake name */
	PROFILE_DUMP_BUFFER_SIZE = 0x2000, /* fake name */
};

enum
{
	_profile_sort_name = 0, /* fake name */
	_profile_sort_average_time, /* fake name */
	_profile_sort_total_time, /* fake name */
	NUMBER_OF_PROFILE_SORT_MODES
};

enum
{
	_profile_dump_format_text = 0, /* fake name */
	_profile_dump_format_table, /* fake name */
	NUMBER_OF_PROFILE_DUMP_FORMAT_MODES
};

enum
{
	_profile_frame_value_none = 0, /* fake names */
	_profile_frame_value_frame,
	_profile_frame_value_load,
	_profile_frame_value_game0,
	_profile_frame_value_game1,
	_profile_frame_value_game2,
	_profile_frame_value_game3,
	_profile_frame_value_game4,
	_profile_frame_value_game5,
	_profile_frame_value_game6,
	_profile_frame_value_game7,
	_profile_frame_value_player0,
	_profile_frame_value_player1,
	_profile_frame_value_player2,
	_profile_frame_value_player3,
	_profile_frame_value_nonplayer,
	_profile_frame_value_render0,
	_profile_frame_value_render0_1,
	_profile_frame_value_render0_2,
	_profile_frame_value_render0_3,
	_profile_frame_value_render0_3np,
	_profile_frame_value_render,
	_profile_frame_value_game_render,
	_profile_frame_value_stall,
	_profile_frame_value_texture,
	_profile_frame_value_idle,
	_profile_frame_value_dt,
	_profile_frame_value_gpu,
	_profile_frame_value_pushbuffer,
	NUMBER_OF_PROFILE_FRAME_VALUES
};

/* ---------- macros */

/* ---------- structures */

struct profile_timesection
{
	__int64 start_time; /* fake name */
	__int64 end_time; /* fake name */
	real elapsed_msec;
	real self_msec;
};

struct profile_frame /* fake name */
{
	boolean dumped; /* fake name */
	long frame_index; /* fake name */
	__int64 vbl_count; /* fake name */
	short game_tick_count;
	short window_count;
	boolean window_player[MAXIMUM_WINDOWS]; /* fake name */
	struct profile_timesection frame; /* fake name */
	struct profile_timesection game_ticks[MAXIMUM_GAME_TICKS_PER_FRAME]; /* fake name */
	struct profile_timesection windows[MAXIMUM_WINDOWS]; /* fake name */
	struct profile_timesection render; /* fake name */
	struct profile_timesection stall; /* fake name */
	struct profile_timesection texture; /* fake name */
	struct profile_timesection idle; /* fake name */
	real seconds_elapsed; /* fake name */
	short lapsed_frames; /* fake name */
	long lapsed_msec; /* fake name */
	boolean slowed; /* fake name */
	char messages[MAXIMUM_PROFILE_MESSAGE_LENGTH]; /* fake name */
	real gpu_msec; /* fake name */
	unsigned long pushbuffer_clocks; /* fake name */
	long stalls; /* fake name */
	short stall_count; /* fake name */
	real stall_msec; /* fake name */
};

struct profile_globals_definition /* fake name */
{
	__int64 clocks_per_second; /* fake name */
	short stack_depth;
	boolean discard_frame; /* fake name */
	long section_history_index; /* fake name */
	short section_count;
	struct profile_section *sections[MAXIMUM_PROFILE_SECTIONS];
	FILE *framedump_file; /* fake name */
	short sort_mode; /* fake name */
	long lost_frame_count; /* fake name */
	boolean framedump_line_pending; /* fake name */
	short current_frame_history_count;
	short current_frame_history_index;
	struct profile_frame frames[MAXIMUM_PROFILE_FRAMES]; /* fake name */
	struct profile_frame current_frame;
};

/* ---------- prototypes */

static void profile_internal_step(void);
static void profile_timesection_inherit(struct profile_timesection *parent_timesection, struct profile_timesection *child_timesection);
static void profile_describe_frame(struct profile_frame *frame, char *string, short maximum_length);
static void profile_timesection_begin(struct profile_timesection *timesection, __int64 time);
static void profile_timesection_end(struct profile_timesection *timesection, __int64 time);
static void profile_dump_frame(struct profile_frame *frame);
static void profile_dump_frame_stop(void);
static boolean string_has_prefix(char const *string, char const *prefix);
static void profile_sections_activation(char const *name, boolean active);
static void profile_timesection_begin_now(struct profile_timesection *timesection);
static void profile_timesection_end_now(struct profile_timesection *timesection);

/* ---------- globals */

static char const *header_strings[NUMBER_OF_PROFILE_DUMP_FORMAT_MODES] =
{
	"section\t                                     total calls / time           av. calls / time      peak calls / time\r\n",
	"|t|rthis frame|taverage|tpeak|n"
};

static char const *format_strings[NUMBER_OF_PROFILE_DUMP_FORMAT_MODES] =
{
	"%-50s%6ld / %7.3f            %5.2f / %7.3f            %ld / %7.3f\r\n",
	"|l%s|t|r% 3.2f/% 4ld|t% 3.2f/% 4ld|t% 3.2f/% 4ld|n"
};

struct profile_globals_definition profile_globals = { 0 };
boolean profile_timebase_ticks = FALSE;
boolean profile_global_enable = FALSE;
boolean profile_dump_frames = FALSE;
boolean profile_dump_lost_frames = FALSE;

/* ---------- public code */

static __inline __int64 RDTSC(
	void)
{
	__int64 time;

	__asm
	{
		push eax
		push edx
		rdtsc
		mov dword ptr [time], eax
		mov dword ptr [time+4], edx
		pop edx
		pop eax
	}

	return time;
}

void profile_initialize(
	void)
{
	short section_index;

	profile_globals.clocks_per_second = PROFILE_CLOCKS_PER_SECOND;

	for (section_index = 0; section_index < profile_globals.section_count; section_index++)
	{
		profile_globals.sections[section_index]->section_index = NONE;
	}

	profile_global_enable = TRUE;
	profile_globals.section_count = 0;
	profile_globals.stack_depth = 0;
	profile_globals.discard_frame = TRUE;
	profile_globals.section_history_index = 0;
	profile_globals.current_frame_history_count = 0;
	profile_globals.current_frame_history_index = 0;
	profile_globals.lost_frame_count = PROFILE_INITIAL_LOST_FRAME_COUNT;
	profile_globals.framedump_file = NULL;

	return;
}

static void profile_internal_step(
	void)
{
	if (profile_global_enable)
	{
		short section_index;

		for (section_index = 0; section_index < profile_globals.section_count; section_index++)
		{
			struct profile_section *section = profile_globals.sections[section_index];

			if (section->active)
			{
				section->total_time -= section->time_history[profile_globals.section_history_index];
				section->total_calls -= section->call_history[profile_globals.section_history_index];
				section->time_history[profile_globals.section_history_index] = section->frame_time;
				section->call_history[profile_globals.section_history_index] = section->frame_calls;
				section->total_time += section->frame_time;
				section->total_calls += section->frame_calls;

				if (section->frame_time > section->peak_time)
				{
					section->peak_time = section->frame_time;
				}

				if (section->frame_calls > section->peak_calls)
				{
					section->peak_calls = section->frame_calls;
				}

				section->accumulated_time += section->frame_time;
				section->accumulated_calls += section->frame_calls;
				section->frame_time = 0;
				section->frame_calls = 0;
				section->frame_count++;
			}
		}
	}

	profile_globals.section_history_index = (profile_globals.section_history_index + 1) % PROFILE_SECTION_HISTORY_FRAMES;
	profile_globals.discard_frame = FALSE;

	return;
}

void profile_rasterizer_stats(
	real value,
	unsigned long count)
{
	profile_globals.current_frame.gpu_msec = value;
	profile_globals.current_frame.pushbuffer_clocks = count;

	return;
}

static void profile_timesection_inherit(
	struct profile_timesection *parent_timesection,
	struct profile_timesection *child_timesection)
{
	match_assert("c:\\halo\\SOURCE\\cseries\\profile.c", 434, parent_timesection->self_msec >= child_timesection->elapsed_msec);
	parent_timesection->self_msec -= child_timesection->elapsed_msec;

	return;
}

void profile_seconds_elapsed(
	real seconds_elapsed)
{
	profile_globals.current_frame.seconds_elapsed = seconds_elapsed;

	return;
}

void profile_lapsed_frames(
	short lapsed_frames,
	boolean at_minimum,
	char *string)
{
	profile_globals.current_frame.lapsed_frames = lapsed_frames;
	profile_globals.current_frame.slowed = lapsed_frames > 0 || !at_minimum;

	if (string)
	{
		strcpy(profile_globals.current_frame.messages, string);
	}

	return;
}

void profile_lapsed_msec(
	long msec)
{
	profile_globals.current_frame.lapsed_msec = msec;
	profile_globals.current_frame.slowed = msec > 0;

	return;
}

void find_profile_section(
	struct profile_section *section)
{
	match_assert("c:\\halo\\SOURCE\\cseries\\profile.c", 559, section);
	match_assert("c:\\halo\\SOURCE\\cseries\\profile.c", 560, section->active);

	if (section->section_index != NONE)
	{
		match_vassert("c:\\halo\\SOURCE\\cseries\\profile.c", 566, section->section_index >= 0 && section->section_index < profile_globals.section_count && profile_globals.sections[section->section_index] == section, "don't call profile_enter_private(), call profile_enter()");
	}
	else
	{
		match_assert("c:\\halo\\SOURCE\\cseries\\profile.c", 570, profile_globals.section_count<MAXIMUM_PROFILE_SECTIONS);
		section->section_index = profile_globals.section_count++;
		profile_globals.sections[section->section_index] = section;
		memset(section->time_history, 0, sizeof(section->time_history));
		memset(section->call_history, 0, sizeof(section->call_history));
		section->total_calls = 0;
		section->total_time = 0;
		section->stack_depth = NONE;
		section->frame_count = 0;
		section->frame_time = 0;
		section->frame_calls = 0;
		section->accumulated_time = 0;
		section->accumulated_calls = 0;
		section->peak_time = 0;
		section->peak_calls = 0;
	}

	return;
}

void profile_enter_private(
	struct profile_section *section)
{
	find_profile_section(section);
	match_assert("c:\\halo\\SOURCE\\cseries\\profile.c", 597, section->stack_depth==NONE);
	section->stack_depth = ++profile_globals.stack_depth;
	section->start_time = RDTSC();
	section->frame_calls++;

	return;
}

void profile_exit_private(
	struct profile_section *section)
{
	if (!profile_globals.discard_frame)
	{
		__int64 end_time;

		find_profile_section(section);
		match_assert("c:\\halo\\SOURCE\\cseries\\profile.c", 615, section->stack_depth==profile_globals.stack_depth);
		profile_globals.stack_depth--;
		end_time = RDTSC();
		section->frame_time += end_time - section->start_time;
	}

	section->stack_depth = NONE;

	return;
}

static void profile_describe_frame(
	struct profile_frame *frame,
	char *string,
	short maximum_length)
{
	short game_tick_display_count;
	short window_display_count;
	short index;

	strcpy(string, "");
	_snprintf(string + strlen(string), maximum_length - strlen(string), "frame %5d vbl %5I64d tot%6.2f", frame->frame_index, frame->vbl_count, frame->frame.elapsed_msec);

	if (frame->lapsed_frames > 0)
	{
		if (global_frame_rate_throttle)
		{
			_snprintf(string + strlen(string), maximum_length - strlen(string), "(lost%3d)", frame->lapsed_frames);
		}
		else
		{
			_snprintf(string + strlen(string), maximum_length - strlen(string), "(free%3d)", frame->lapsed_frames);
		}
	}
	else if (frame->lapsed_msec > 0)
	{
		if (global_frame_rate_throttle)
		{
			_snprintf(string + strlen(string), maximum_length - strlen(string), "(l.%3dms)", frame->lapsed_msec);
		}
		else
		{
			_snprintf(string + strlen(string), maximum_length - strlen(string), "(f.%3dms)", frame->lapsed_msec);
		}
	}
	else if (frame->slowed)
	{
		_snprintf(string + strlen(string), maximum_length - strlen(string), "(slowed) ");
	}
	else
	{
		_snprintf(string + strlen(string), maximum_length - strlen(string), "(synced) ");
	}

	if (frame->idle.self_msec > 0.f)
	{
		_snprintf(string + strlen(string), maximum_length - strlen(string), "idle%6.2f ", frame->idle.self_msec);
	}
	else
	{
		_snprintf(string + strlen(string), maximum_length - strlen(string), "           ", frame->idle.self_msec);
	}

	game_tick_display_count = frame->game_tick_count > MINIMUM_DISPLAYED_GAME_TICKS ? frame->game_tick_count : MINIMUM_DISPLAYED_GAME_TICKS;
	_snprintf(string + strlen(string), maximum_length - strlen(string), "game%2d ", frame->game_tick_count);
	_snprintf(string + strlen(string), maximum_length - strlen(string), " (");

	for (index = 0; index < game_tick_display_count; index++)
	{
		if (index < frame->game_tick_count)
		{
			_snprintf(string + strlen(string), maximum_length - strlen(string), "%6.2f%s", frame->game_ticks[index].self_msec, index < game_tick_display_count - 1 ? " " : "");
		}
		else
		{
			_snprintf(string + strlen(string), maximum_length - strlen(string), "      %s", index < game_tick_display_count - 1 ? " " : "");
		}
	}

	_snprintf(string + strlen(string), maximum_length - strlen(string), ")");

	window_display_count = frame->window_count > local_player_count() + 1 ? frame->window_count : local_player_count() + 1;
	_snprintf(string + strlen(string), maximum_length - strlen(string), " render%6.2f", frame->render.elapsed_msec);
	_snprintf(string + strlen(string), maximum_length - strlen(string), " (");

	for (index = 0; index < window_display_count; index++)
	{
		if (index < frame->window_count)
		{
			_snprintf(string + strlen(string), maximum_length - strlen(string), "%s%6.2f%s", frame->window_player[index] ? "p" : "n", frame->windows[index].self_msec, index < window_display_count - 1 ? " " : "");
		}
		else
		{
			_snprintf(string + strlen(string), maximum_length - strlen(string), "       %s", index < window_display_count - 1 ? " " : "");
		}
	}

	_snprintf(string + strlen(string), maximum_length - strlen(string), ")");

	if (frame->stall.self_msec > 0.f)
	{
		_snprintf(string + strlen(string), maximum_length - strlen(string), "stall%6.2f ", frame->stall.self_msec);
	}
	else
	{
		_snprintf(string + strlen(string), maximum_length - strlen(string), "            ", frame->stall.self_msec);
	}

	if (frame->texture.self_msec > 0.f)
	{
		_snprintf(string + strlen(string), maximum_length - strlen(string), "tex%6.2f ", frame->texture.self_msec);
	}
	else
	{
		_snprintf(string + strlen(string), maximum_length - strlen(string), "          ", frame->texture.self_msec);
	}

	_snprintf(string + strlen(string), maximum_length - strlen(string), "r-misc %6.2f ", frame->render.self_msec);
	_snprintf(string + strlen(string), maximum_length - strlen(string), "f-misc %6.2f ", frame->frame.self_msec);
	strncat(string + strlen(string), frame->messages, maximum_length - strlen(string));

	return;
}

static void profile_timesection_begin(
	struct profile_timesection *timesection,
	__int64 time)
{
	timesection->start_time = time;

	return;
}

static void profile_timesection_end(
	struct profile_timesection *timesection,
	__int64 time)
{
	real msec;

	timesection->end_time = time;
	msec = (real)(timesection->end_time - timesection->start_time) * 1000.f / profile_globals.clocks_per_second;
	timesection->elapsed_msec += msec;
	timesection->self_msec += msec;

	return;
}

long compare_profile_sections(
	void const *a,
	void const *b)
{
	long result;

	if ((*(struct profile_section **)a)->active && !(*(struct profile_section **)b)->active)
	{
		result = -1;
	}
	else if ((*(struct profile_section **)b)->active && !(*(struct profile_section **)a)->active)
	{
		result = 1;
	}
	else
	{
		switch (profile_globals.sort_mode)
		{
		case _profile_sort_name:
			result = strcmp((*(struct profile_section **)a)->name, (*(struct profile_section **)b)->name);
			break;
		case _profile_sort_average_time:
		{
			double average_a = !(*(struct profile_section **)a)->frame_count ? 0.0 : (double)(*(struct profile_section **)a)->accumulated_time / (*(struct profile_section **)a)->frame_count;
			double average_b = !(*(struct profile_section **)b)->frame_count ? 0.0 : (double)(*(struct profile_section **)b)->accumulated_time / (*(struct profile_section **)b)->frame_count;

			if (average_a > average_b)
			{
				result = -1;
			}
			else if (average_a < average_b)
			{
				result = 1;
			}
			else
			{
				result = 0;
			}
			break;
		}
		case _profile_sort_total_time:
			if ((*(struct profile_section **)a)->total_time > (*(struct profile_section **)b)->total_time)
			{
				result = -1;
			}
			else if ((*(struct profile_section **)a)->total_time < (*(struct profile_section **)b)->total_time)
			{
				result = 1;
			}
			else
			{
				result = 0;
			}
			break;
		default:
			match_unreachable("c:\\halo\\SOURCE\\cseries\\profile.c", 844);
		}
	}

	return result;
}

void profile_dump(
	char const *name,
	short sort_mode,
	short format_mode,
	short maximum_section_count,
	char *buffer)
{
	struct profile_section *sections[MAXIMUM_PROFILE_SECTIONS];
	short section_count = 0;

	match_assert("c:\\halo\\SOURCE\\cseries\\profile.c", 879, sort_mode>=0 && sort_mode<NUMBER_OF_PROFILE_SORT_MODES);
	match_assert("c:\\halo\\SOURCE\\cseries\\profile.c", 880, format_mode>=0 && format_mode<NUMBER_OF_PROFILE_DUMP_FORMAT_MODES);
	match_assert("c:\\halo\\SOURCE\\cseries\\profile.c", 881, maximum_section_count>0);
	match_assert("c:\\halo\\SOURCE\\cseries\\profile.c", 882, buffer);

	profile_globals.sort_mode = sort_mode;
	memcpy(sections, profile_globals.sections, profile_globals.section_count * sizeof(struct profile_section *));
	qsort(sections, profile_globals.section_count, sizeof(struct profile_section *), compare_profile_sections);

	if (profile_globals.section_count && sections[0]->active)
	{
		short section_index;

		sprintf(buffer, header_strings[format_mode]);

		for (section_index = 0; section_index < profile_globals.section_count && section_count < maximum_section_count; section_index++)
		{
			struct profile_section *first_section = sections[section_index];
			long total_calls = 0;
			real total_time = 0.f;
			real average_calls = 0.f;
			real average_time = 0.f;
			long peak_calls = 0;
			real peak_time = 0.f;
			long frame_calls = 0;
			real frame_time = 0.f;

			if (first_section->active && (!name || strstr(first_section->name, name)))
			{
				do
				{
					struct profile_section *section = sections[section_index];

					total_calls += section->accumulated_calls;
					total_time += (double)section->accumulated_time / profile_globals.clocks_per_second;
					average_calls += (real)section->accumulated_calls / section->frame_count;
					average_time += 1000.0 * (!section->frame_count ? 0.0 : (double)section->accumulated_time / section->frame_count) / profile_globals.clocks_per_second;
					peak_calls += section->peak_calls;
					peak_time += section->peak_time * 1000.0 / profile_globals.clocks_per_second;
					frame_calls += section->frame_calls;
					frame_time += section->frame_time * 1000.0 / profile_globals.clocks_per_second;
					section_index++;
				}
				while (section_index < profile_globals.section_count && !strcmp(sections[section_index]->name, first_section->name));

				switch (format_mode)
				{
				case _profile_dump_format_text:
					sprintf(buffer + strlen(buffer), format_strings[format_mode], first_section->name, total_calls, total_time, average_calls, average_time, peak_calls, peak_time);
					break;
				case _profile_dump_format_table:
					sprintf(buffer + strlen(buffer), format_strings[format_mode], first_section->name, frame_time, frame_calls, average_time, (long)(average_calls + 0.5f), peak_time, peak_calls, total_time, total_calls);
					break;
				}

				section_index--;
				section_count++;
			}
		}
	}

	return;
}

void profile_dump_to_file(
	char *name)
{
	char buffer[PROFILE_DUMP_BUFFER_SIZE];
	short sort_mode = (name && strlen(name)) ? _profile_sort_average_time : _profile_sort_name;
	FILE *file = fopen("d:\\profile.txt", "a+b");

	if (file)
	{
		profile_dump(name, sort_mode, _profile_dump_format_text, MAXIMUM_PROFILE_SECTIONS, buffer);
		fprintf(file, "%s\r\n", buffer);
	}

	fclose(file);

	return;
}

static void profile_dump_frame(
	struct profile_frame *frame)
{
	char string[512];

	if (!profile_globals.framedump_file)
	{
		profile_globals.framedump_file = fopen("d:\\framedump.txt", "wb");
	}

	if (profile_globals.framedump_file && !frame->dumped)
	{
		frame->dumped = TRUE;
		profile_describe_frame(frame, string, sizeof(string));
		fprintf(profile_globals.framedump_file, "%s\r\n", string);
		frame->dumped = TRUE;
	}

	profile_globals.framedump_line_pending = TRUE;

	return;
}

static void profile_dump_frame_stop(
	void)
{
	if (profile_globals.framedump_line_pending)
	{
		if (profile_globals.framedump_file)
		{
			fprintf(profile_globals.framedump_file, "\r\n");
			fflush(profile_globals.framedump_file);
		}

		profile_globals.framedump_line_pending = FALSE;
	}

	return;
}

static boolean string_has_prefix(
	char const *string,
	char const *prefix)
{
	boolean result = TRUE;

	while (*prefix)
	{
		if (*prefix != *string)
		{
			result = FALSE;
			break;
		}

		prefix++;
		string++;
	}

	return result;
}

static void profile_sections_activation(
	char const *name,
	boolean active)
{
	boolean all = !strcmp(name, "*");
	boolean prefix = name[0] == '_';
	short section_index;

	for (section_index = 0; section_index < profile_globals.section_count; section_index++)
	{
		struct profile_section *section = profile_globals.sections[section_index];

		if (all || (prefix && string_has_prefix(section->name, name + 1)) || (!prefix && strstr(section->name, name)))
		{
			section->active = active;
		}
	}

	return;
}

void profile_sections_activate(
	char const *name)
{
	profile_sections_activation(name, TRUE);

	return;
}

void profile_sections_deactivate(
	char const *name)
{
	profile_sections_activation(name, FALSE);

	return;
}

short profile_find_frame_value(
	char *name,
	short *section_index_reference)
{
	short value = NONE;

	match_assert("c:\\halo\\SOURCE\\cseries\\profile.c", 1094, name && section_index_reference);

	if (!_stricmp(name, "frame"))
	{
		value = _profile_frame_value_frame;
	}
	else if (!_stricmp(name, "load"))
	{
		value = _profile_frame_value_load;
	}
	else if (!_stricmp(name, "game0"))
	{
		value = _profile_frame_value_game0;
	}
	else if (!_stricmp(name, "game1"))
	{
		value = _profile_frame_value_game1;
	}
	else if (!_stricmp(name, "game2"))
	{
		value = _profile_frame_value_game2;
	}
	else if (!_stricmp(name, "game3"))
	{
		value = _profile_frame_value_game3;
	}
	else if (!_stricmp(name, "game4"))
	{
		value = _profile_frame_value_game4;
	}
	else if (!_stricmp(name, "game5"))
	{
		value = _profile_frame_value_game5;
	}
	else if (!_stricmp(name, "game6"))
	{
		value = _profile_frame_value_game6;
	}
	else if (!_stricmp(name, "game7"))
	{
		value = _profile_frame_value_game7;
	}
	else if (!_stricmp(name, "player0"))
	{
		value = _profile_frame_value_player0;
	}
	else if (!_stricmp(name, "player1"))
	{
		value = _profile_frame_value_player1;
	}
	else if (!_stricmp(name, "player2"))
	{
		value = _profile_frame_value_player2;
	}
	else if (!_stricmp(name, "player3"))
	{
		value = _profile_frame_value_player3;
	}
	else if (!_stricmp(name, "nonplayer"))
	{
		value = _profile_frame_value_nonplayer;
	}
	else if (!_stricmp(name, "render"))
	{
		value = _profile_frame_value_render;
	}
	else if (!_stricmp(name, "render0"))
	{
		value = _profile_frame_value_render0;
	}
	else if (!_stricmp(name, "render0_1"))
	{
		value = _profile_frame_value_render0_1;
	}
	else if (!_stricmp(name, "render0_2"))
	{
		value = _profile_frame_value_render0_2;
	}
	else if (!_stricmp(name, "render0_3"))
	{
		value = _profile_frame_value_render0_3;
	}
	else if (!_stricmp(name, "render0_3np"))
	{
		value = _profile_frame_value_render0_3np;
	}
	else if (!_stricmp(name, "game_render"))
	{
		value = _profile_frame_value_game_render;
	}
	else if (!_stricmp(name, "stall"))
	{
		value = _profile_frame_value_stall;
	}
	else if (!_stricmp(name, "texture"))
	{
		value = _profile_frame_value_texture;
	}
	else if (!_stricmp(name, "idle"))
	{
		value = _profile_frame_value_idle;
	}
	else if (!_stricmp(name, "dt"))
	{
		value = _profile_frame_value_dt;
	}
	else if (!_stricmp(name, "gpu"))
	{
		value = _profile_frame_value_gpu;
	}
	else if (!_stricmp(name, "pushbuffer"))
	{
		value = _profile_frame_value_pushbuffer;
	}

	*section_index_reference = NONE;

	return value;
}

short profile_find_game_value(
	char *name,
	short *section_index_reference)
{
	match_assert("c:\\halo\\SOURCE\\cseries\\profile.c", 1224, name && section_index_reference);
	*section_index_reference = NONE;

	return NONE;
}

real profile_frame_get_value(
	struct profile_frame_iterator *iterator,
	short value)
{
	struct profile_frame *frame = &profile_globals.frames[iterator->current_buffer_index];
	real result = 0.f;

	match_assert("c:\\halo\\SOURCE\\cseries\\profile.c", 1239, (iterator->current_buffer_index >= 0) && (iterator->current_buffer_index < profile_globals.current_frame_history_count));
	match_assert("c:\\halo\\SOURCE\\cseries\\profile.c", 1240, iterator->current_buffer_index != profile_globals.current_frame_history_index);

	switch (value)
	{
	case _profile_frame_value_frame:
		result = frame->frame.elapsed_msec;
		break;
	case _profile_frame_value_load:
		result = frame->frame.elapsed_msec - frame->idle.elapsed_msec;
		break;
	case _profile_frame_value_game0:
		if (frame->game_tick_count > 0)
		{
			result = frame->game_ticks[0].elapsed_msec;
		}
		break;
	case _profile_frame_value_player0:
		if (frame->window_count > 0)
		{
			result = frame->windows[0].elapsed_msec;
		}
		break;
	case _profile_frame_value_nonplayer:
	{
		short window_index;

		for (window_index = 0; window_index < frame->window_count; window_index++)
		{
			if (!frame->window_player[window_index])
			{
				result = frame->windows[window_index].elapsed_msec;
				break;
			}
		}
		break;
	}
	case _profile_frame_value_render:
		result = frame->render.elapsed_msec;
		break;
	case _profile_frame_value_render0:
	{
		short window_index;
		short player_count = 0;

		result = 0.f;

		for (window_index = 0; window_index < frame->window_count && player_count < 1; window_index++)
		{
			if (frame->window_player[window_index])
			{
				result += frame->windows[window_index].elapsed_msec;
				player_count++;
			}
		}
		break;
	}
	case _profile_frame_value_render0_1:
	{
		short window_index;
		short player_count = 0;

		result = 0.f;

		for (window_index = 0; window_index < frame->window_count && player_count < 2; window_index++)
		{
			if (frame->window_player[window_index])
			{
				result += frame->windows[window_index].elapsed_msec;
				player_count++;
			}
		}
		break;
	}
	case _profile_frame_value_render0_2:
	{
		short window_index;
		short player_count = 0;

		result = 0.f;

		for (window_index = 0; window_index < frame->window_count && player_count < 3; window_index++)
		{
			if (frame->window_player[window_index])
			{
				result += frame->windows[window_index].elapsed_msec;
				player_count++;
			}
		}
		break;
	}
	case _profile_frame_value_render0_3:
	{
		short window_index;
		short player_count = 0;

		result = 0.f;

		for (window_index = 0; window_index < frame->window_count && player_count < 4; window_index++)
		{
			if (frame->window_player[window_index])
			{
				result += frame->windows[window_index].elapsed_msec;
				player_count++;
			}
		}
		break;
	}
	case _profile_frame_value_render0_3np:
	{
		short window_index;
		short player_count = 0;

		result = 0.f;

		for (window_index = 0; window_index < frame->window_count && player_count < 4; window_index++)
		{
			if (frame->window_player[window_index])
			{
				result += frame->windows[window_index].elapsed_msec;
				player_count++;
			}
			else
			{
				result += frame->windows[window_index].elapsed_msec;
			}
		}
		break;
	}
	case _profile_frame_value_game_render:
	{
		short game_tick_index;

		result = frame->render.elapsed_msec;

		for (game_tick_index = 0; game_tick_index < frame->game_tick_count; game_tick_index++)
		{
			result += frame->game_ticks[game_tick_index].elapsed_msec;
		}
		break;
	}
	case _profile_frame_value_stall:
		result = frame->stall.elapsed_msec;
		break;
	case _profile_frame_value_texture:
		result = frame->texture.elapsed_msec;
		break;
	case _profile_frame_value_idle:
		result = frame->idle.elapsed_msec;
		break;
	case _profile_frame_value_dt:
		result = frame->seconds_elapsed * 1000.f;
		break;
	case _profile_frame_value_gpu:
		result = frame->gpu_msec;
		break;
	case _profile_frame_value_pushbuffer:
		result = ((real)frame->pushbuffer_clocks * (1.f / PROFILE_PUSHBUFFER_SIZE)) * (100.f / 3.f);
		break;
	}

	return result;
}

void profile_frame_iterator_new(
	struct profile_frame_iterator *iterator)
{
	match_assert("c:\\halo\\SOURCE\\cseries\\profile.c", 1419, iterator);
	iterator->current_buffer_index = NONE;
	iterator->next_buffer_index = (profile_globals.current_frame_history_index + MAXIMUM_PROFILE_FRAMES - 1) % MAXIMUM_PROFILE_FRAMES;

	return;
}

boolean profile_frame_iterator_next(
	struct profile_frame_iterator *iterator,
	__int64 *vbl_count)
{
	boolean result = FALSE;

	iterator->current_buffer_index = iterator->next_buffer_index;

	if (iterator->current_buffer_index != NONE && iterator->current_buffer_index < profile_globals.current_frame_history_count)
	{
		result = TRUE;

		if (vbl_count)
		{
			*vbl_count = profile_globals.frames[iterator->current_buffer_index].vbl_count;
		}

		iterator->next_buffer_index = (iterator->current_buffer_index + MAXIMUM_PROFILE_FRAMES - 1) % MAXIMUM_PROFILE_FRAMES;

		if (iterator->next_buffer_index == profile_globals.current_frame_history_index)
		{
			iterator->next_buffer_index = NONE;
		}
	}

	return result;
}

void profile_frame_get_messages(
	struct profile_frame_iterator *iterator)
{
	match_assert("c:\\halo\\SOURCE\\cseries\\profile.c", 1463, iterator);
	match_assert("c:\\halo\\SOURCE\\cseries\\profile.c", 1464, (iterator->current_buffer_index >= 0) && (iterator->current_buffer_index < profile_globals.current_frame_history_count));
	match_assert("c:\\halo\\SOURCE\\cseries\\profile.c", 1465, iterator->current_buffer_index != profile_globals.current_frame_history_index);

	return;
}

long profile_frame_get_stalls(
	struct profile_frame_iterator *iterator,
	short *stall_count,
	real *stall_msec)
{
	struct profile_frame *frame = &profile_globals.frames[iterator->current_buffer_index];

	match_assert("c:\\halo\\SOURCE\\cseries\\profile.c", 1480, (iterator->current_buffer_index >= 0) && (iterator->current_buffer_index < profile_globals.current_frame_history_count));
	match_assert("c:\\halo\\SOURCE\\cseries\\profile.c", 1481, iterator->current_buffer_index != profile_globals.current_frame_history_index);
	*stall_count = frame->stall_count;
	*stall_msec = frame->stall_msec;

	return frame->stalls;
}

void profile_rasterizer_stalls(
	long stalls,
	short stall_count,
	__int64 stall_clocks,
	__int64 stall_time)
{
	unsigned long clocks = (unsigned long)stall_clocks;

	profile_timesection_begin(&profile_globals.current_frame.stall, 0);
	profile_timesection_end(&profile_globals.current_frame.stall, stall_time);
	profile_globals.current_frame.stalls = stalls;
	profile_globals.current_frame.stall_count = stall_count;
	profile_globals.current_frame.stall_msec = (real)clocks * 1000.f / profile_globals.clocks_per_second;

	return;
}

static void profile_timesection_begin_now(
	struct profile_timesection *timesection)
{
	timesection->start_time = RDTSC();

	return;
}

static void profile_timesection_end_now(
	struct profile_timesection *timesection)
{
	real msec;

	timesection->end_time = RDTSC();
	msec = (real)(timesection->end_time - timesection->start_time) * 1000.f / profile_globals.clocks_per_second;
	timesection->elapsed_msec += msec;
	timesection->self_msec += msec;

	return;
}

void profile_tick_start(
	void)
{
	if (profile_timebase_ticks)
	{
		profile_internal_step();
	}

	if (profile_globals.current_frame.game_tick_count < MAXIMUM_GAME_TICKS_PER_FRAME)
	{
		profile_globals.current_frame.game_tick_count++;
	}

	match_assert("c:\\halo\\SOURCE\\cseries\\profile.c", 311, (profile_globals.current_frame.game_tick_count > 0) && (profile_globals.current_frame.game_tick_count <= MAXIMUM_GAME_TICKS_PER_FRAME));
	profile_timesection_begin_now(&profile_globals.current_frame.game_ticks[profile_globals.current_frame.game_tick_count - 1]);

	return;
}

void profile_tick_end(
	void)
{
	match_assert("c:\\halo\\SOURCE\\cseries\\profile.c", 320, (profile_globals.current_frame.game_tick_count > 0) && (profile_globals.current_frame.game_tick_count <= MAXIMUM_GAME_TICKS_PER_FRAME));
	profile_timesection_end_now(&profile_globals.current_frame.game_ticks[profile_globals.current_frame.game_tick_count - 1]);

	return;
}

void profile_render_start(
	void)
{
	profile_globals.current_frame.window_count = 0;
	profile_timesection_begin_now(&profile_globals.current_frame.render);

	return;
}

void profile_render_end(
	void)
{
	profile_timesection_end_now(&profile_globals.current_frame.render);

	return;
}

void profile_render_window_start(
	boolean player)
{
	if (profile_globals.current_frame.window_count < MAXIMUM_WINDOWS)
	{
		profile_globals.current_frame.window_count++;
		profile_globals.current_frame.window_player[profile_globals.current_frame.window_count - 1] = player;
	}

	match_assert("c:\\halo\\SOURCE\\cseries\\profile.c", 353, (profile_globals.current_frame.window_count > 0) && (profile_globals.current_frame.window_count <= MAXIMUM_WINDOWS));
	profile_timesection_begin_now(&profile_globals.current_frame.windows[profile_globals.current_frame.window_count - 1]);

	return;
}

void profile_render_window_end(
	void)
{
	match_assert("c:\\halo\\SOURCE\\cseries\\profile.c", 362, (profile_globals.current_frame.window_count > 0) && (profile_globals.current_frame.window_count <= MAXIMUM_WINDOWS));
	profile_timesection_end_now(&profile_globals.current_frame.windows[profile_globals.current_frame.window_count - 1]);

	return;
}

void profile_texture_start(
	void)
{
	profile_timesection_begin_now(&profile_globals.current_frame.texture);

	return;
}

void profile_texture_end(
	void)
{
	profile_timesection_end_now(&profile_globals.current_frame.texture);

	return;
}

void profile_frame_start(
	void)
{
	if (!profile_timebase_ticks)
	{
		profile_internal_step();
	}

	memset(&profile_globals.current_frame, 0, sizeof(profile_globals.current_frame));
	profile_globals.current_frame.frame_index = render.frame_index;
	profile_globals.current_frame.vbl_count = rasterizer_globals.vblank_index;
	profile_globals.current_frame.game_tick_count = 0;
	profile_timesection_begin_now(&profile_globals.current_frame.frame);

	return;
}

void profile_frame_end(
	void)
{
	short index;

	profile_timesection_end_now(&profile_globals.current_frame.frame);

	match_assert("c:\\halo\\SOURCE\\cseries\\profile.c", 448, (profile_globals.current_frame.game_tick_count >= 0) && (profile_globals.current_frame.game_tick_count <= MAXIMUM_GAME_TICKS_PER_FRAME));

	for (index = 0; index < profile_globals.current_frame.game_tick_count; index++)
	{
		profile_timesection_inherit(&profile_globals.current_frame.frame, &profile_globals.current_frame.game_ticks[index]);
	}

	match_assert("c:\\halo\\SOURCE\\cseries\\profile.c", 454, (profile_globals.current_frame.window_count >= 0) && (profile_globals.current_frame.window_count <= MAXIMUM_WINDOWS));
	profile_timesection_inherit(&profile_globals.current_frame.frame, &profile_globals.current_frame.render);

	for (index = 0; index < profile_globals.current_frame.window_count; index++)
	{
		profile_timesection_inherit(&profile_globals.current_frame.render, &profile_globals.current_frame.windows[index]);
	}

	profile_timesection_inherit(&profile_globals.current_frame.frame, &profile_globals.current_frame.idle);

	profile_globals.frames[profile_globals.current_frame_history_index] = profile_globals.current_frame;
	profile_globals.current_frame_history_count = MAX(profile_globals.current_frame_history_count, profile_globals.current_frame_history_index + 1);
	profile_globals.current_frame_history_index = (profile_globals.current_frame_history_index + 1) % MAXIMUM_PROFILE_FRAMES;

	if (profile_globals.current_frame.slowed)
	{
		profile_globals.lost_frame_count = 0;
	}
	else
	{
		profile_globals.lost_frame_count++;

		if (profile_dump_lost_frames && !profile_dump_frames && profile_globals.lost_frame_count > PROFILE_LOST_FRAME_PADDING)
		{
			profile_dump_frame_stop();
		}
	}

	if (profile_dump_frames || (profile_dump_lost_frames && profile_globals.lost_frame_count <= PROFILE_LOST_FRAME_PADDING))
	{
		short frame_index = (profile_globals.current_frame_history_index + MAXIMUM_PROFILE_FRAMES - PROFILE_LOST_FRAME_PADDING) % MAXIMUM_PROFILE_FRAMES;

		do
		{
			if (frame_index < profile_globals.current_frame_history_count)
			{
				profile_dump_frame(&profile_globals.frames[frame_index]);
			}

			frame_index = (frame_index + 1) % MAXIMUM_PROFILE_FRAMES;
		}
		while (frame_index != profile_globals.current_frame_history_index);
	}

	return;
}

void profile_idle_start(
	void)
{
	profile_timesection_begin_now(&profile_globals.current_frame.idle);

	return;
}

void profile_idle_end(
	void)
{
	profile_timesection_end_now(&profile_globals.current_frame.idle);

	return;
}

/* ---------- private code */
