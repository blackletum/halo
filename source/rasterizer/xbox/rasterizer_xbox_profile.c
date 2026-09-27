/*
RASTERIZER_XBOX_PROFILE.C

symbols in this file:
0015ECD0 0080:
	_rasterizer_profile_assert (0000)
0015ED50 0110:
	_rasterizer_profile_callback (0000)
0015EE60 0090:
	_rasterizer_profile_frame_callback (0000)
0015EEF0 0020:
	_rasterizer_profile_enabled (0000)
0015EF10 0070:
	_rasterizer_profile_initialize (0000)
0015EF80 0150:
	_rasterizer_profile_frame_begin (0000)
0015F0D0 0020:
	_rasterizer_profile_window_begin (0000)
0015F0F0 0070:
	__rasterizer_profile_enable (0000)
0015F160 0130:
	_rasterizer_profile_begin (0000)
0015F290 0140:
	_rasterizer_profile_end (0000)
0015F3D0 0050:
	_rasterizer_profile_get_string (0000)
0015F420 0120:
	_rasterizer_profile_query (0000)
0015F540 00e0:
	_rasterizer_profile_query_pushbuffer (0000)
0015F620 00e0:
	_rasterizer_profile_frame_end (0000)
0015F700 0010:
	_rasterizer_profile_window_end (0000)
0015F710 0010:
	_rasterizer_profile_dispose (0000)
00291FBC 000d:
	??_C@_0N@NPLHKNPM@screen?5flash?$AA@ (0000)
00291FCC 0004:
	??_C@_03HOHJDGGL@HUD?$AA@ (0000)
00291FD0 000e:
	??_C@_0O@KEPDLHCB@screen?5effect?$AA@ (0000)
00291FE0 000c:
	??_C@_0M@MPLNCIAM@lens?5flares?$AA@ (0000)
00291FEC 0017:
	??_C@_0BH@JMHHLHBN@lens?5flare?5occl?4?5query?$AA@ (0000)
00292004 0018:
	??_C@_0BI@BJCKIOBM@lens?5flare?5occl?4?5submit?$AA@ (0000)
0029201C 0014:
	??_C@_0BE@PGACMIOM@queued?5transparents?$AA@ (0000)
00292030 000f:
	??_C@_0P@NADPEMMH@detail?5objects?$AA@ (0000)
00292040 0011:
	??_C@_0BB@JKPKBHGC@env?5decals?5water?$AA@ (0000)
00292054 000f:
	??_C@_0P@CMGCGEPL@env?5fog?5screen?$AA@ (0000)
00292064 0008:
	??_C@_07LCJPKBIL@env?5fog?$AA@ (0000)
0029206C 0010:
	??_C@_0BA@POKLBKIL@env?5transparent?$AA@ (0000)
0029207C 0010:
	??_C@_0BA@NCEEKADL@env?5reflections?$AA@ (0000)
0029208C 0017:
	??_C@_0BH@HJJDMAAJ@env?5reflection?5mirrors?$AA@ (0000)
002920A4 0017:
	??_C@_0BH@BIDFOOOJ@env?5lightmaps?5ref?4mask?$AA@ (0000)
002920BC 0017:
	??_C@_0BH@JPGDBMFC@env?5lightmaps?5specular?$AA@ (0000)
002920D4 0014:
	??_C@_0BE@NMLCJCAM@env?5lights?5specular?$AA@ (0000)
002920E8 0015:
	??_C@_0BF@MCHCJCJA@env?5decals?5secondary?$AA@ (0000)
00292100 0013:
	??_C@_0BD@OMPHEFCG@env?5decals?5primary?$AA@ (0000)
00292114 000d:
	??_C@_0N@LLIEDNIN@env?5textures?$AA@ (0000)
00292124 0018:
	??_C@_0BI@LPGLMPFG@env?5decals?5alpha?9tested?$AA@ (0000)
0029213C 0011:
	??_C@_0BB@NPLFGCFP@env?5decals?5light?$AA@ (0000)
00292150 000b:
	??_C@_0L@OBJNHOKI@env?5lights?$AA@ (0000)
0029215C 000c:
	??_C@_0M@EMKKMCPM@env?5shadows?$AA@ (0000)
00292168 000e:
	??_C@_0O@OEMAEMFI@env?5lightmaps?$AA@ (0000)
00292178 0007:
	??_C@_06FEMFHOOG@models?$AA@ (0000)
00292180 000a:
	??_C@_09ELJLJCBG@model?5sky?$AA@ (0000)
0029218C 0020:
	??_C@_0CA@HHAEBLHJ@?$CD?$CD?$CD?5PROFILE?3?5?$CFs?5?9?9?5tell?5Bernie?$CB?$AA@ (0000)
002921AC 0026:
	??_C@_0CG@CABPNPIN@?$CD?$CD?$CD?5PROFILE?5?$CI?$CD?$CFd?$CJ?3?5?$CFs?5?9?9?5tell?5Be@ (0000)
002921D4 0039:
	??_C@_0DJ@EMCMCPAB@c?3?2halo?2SOURCE?2rasterizer?2xbox?2r@ (0000)
00292210 0011:
	??_C@_0BB@LCIAJAAI@end?5out?9of?9synch?$AA@ (0000)
00292224 0013:
	??_C@_0BD@PDKEIIAE@begin?5out?9of?9synch?$AA@ (0000)
00292238 0022:
	??_C@_0CC@GJPJJFMA@callback?5recieved?5invalid?5contex@ (0000)
0029225C 0019:
	??_C@_0BJ@HIIHLGIF@local_profile_enable?$DM100?$AA@ (0000)
00292278 0017:
	??_C@_0BH@CGAGFGCG@local_profile_enable?$DO0?$AA@ (0000)
00292290 002c:
	??_C@_0CM@MDDANJMO@profile?5begin?1end?5pairing?5incorr@ (0000)
002922BC 0029:
	??_C@_0CJ@FEPBBPKK@profile?5duplication?5within?5frame@ (0000)
002922E8 0034:
	??_C@_0DE@PLFGBHLC@profile?$DO?$DN0?5?$CG?$CG?5profile?$DMNUMBER_OF_@ (0000)
0029231C 002a:
	??_C@_0CK@GJJPMKBP@profile?5begin?1end?5pairing?5incorr@ (0000)
00292348 0027:
	??_C@_0CH@BKOLJHAH@profile?5duplication?5within?5frame@ (0000)
00292370 001e:
	??_C@_0BO@KDABKJGE@profile?5not?5completed?5?$CIquery?$CJ?$AA@ (0000)
0030CF00 0084:
	_data_0030cf00 (0000)
	_data_0030cf08 (0008)
	_data_0030cf0c (000c)
	_data_0030cf10 (0010)
00465E28 0462:
	_bss_00465e28 (0000)
	_bss_00465ea8 (0080)
	_bss_00465f28 (0100)
	_bss_00465fa8 (0180)
	_bss_00466090 (0268)
	_bss_00466178 (0350)
	_bss_00466260 (0438)
	_bss_00466268 (0440)
	_bss_00466270 (0448)
	_bss_00466274 (044c)
	_local_profile_enable (0450)
	_bss_0046627c (0454)
	_bss_00466280 (0458)
	_bss_00466284 (045c)
	_bss_00466288 (0460)
*/

/* ---------- headers */

#include "cseries.h"
#include "cseries_windows.h"
#include "errors.h"
#include "real_math.h"
#include "rasterizer.h"
#include "xbox/rasterizer_xbox.h"

/* ---------- constants */

enum
{
	MAXIMUM_PROFILE_ERRORS = 3,
	NUMBER_OF_PROFILE_FRAMES = 16,
	PROFILE_BEGIN_FLAG = 0x80000000
};

enum
{
	_profile_error_invalid_context_bit = 0,
	_profile_error_begin_out_of_synch_bit,
	_profile_error_end_out_of_synch_bit,
	NUMBER_OF_PROFILE_ERROR_BITS
};

/* ---------- prototypes */

void profile_rasterizer_stats(real milliseconds, __int64 pushbuffer_size);

static void rasterizer_profile_assert(short profile, char const *message, boolean condition); // rasterizer_profile_assert?
static void __cdecl rasterizer_profile_callback(DWORD context); // rasterizer_profile_callback
static void __cdecl rasterizer_profile_frame_callback(DWORD context); // rasterizer_profile_frame_callback
static boolean rasterizer_profile_enabled(void); // rasterizer_profile_enabled

/* ---------- globals */

extern struct rasterizer_window_begin_parameters global_window_parameters;

// separate statics in the original; names unknown (no hcex counterpart), so placeholders are named after their addresses.
// bss_00466284 (4 bytes at 0x45c) is never referenced and is discarded by the compiler
static LARGE_INTEGER data_0030cf00= {1, 0}; // counter frequency
static short data_0030cf08= NONE; // current profile
static short data_0030cf0c= NONE; // window index
static char const *data_0030cf10[NUMBER_OF_RASTERIZER_PROFILES]= // profile names
{
	"clear",
	"model sky",
	"models",
	"env lightmaps",
	"env shadows",
	"env lights",
	"env decals light",
	"env decals alpha-tested",
	"env textures",
	"env decals primary",
	"env decals secondary",
	"env lights specular",
	"env lightmaps specular",
	"env lightmaps ref.mask",
	"env reflection mirrors",
	"env reflections",
	"env transparent",
	"env fog",
	"env fog screen",
	"water",
	"env decals water",
	"detail objects",
	"queued transparents",
	"lens flare occl. submit",
	"lens flare occl. query",
	"lens flares",
	"screen effect",
	"HUD",
	"screen flash"
};

static LARGE_INTEGER bss_00465e28[NUMBER_OF_PROFILE_FRAMES]; // frame times
static LARGE_INTEGER bss_00465ea8[NUMBER_OF_PROFILE_FRAMES]; // frame end times
static LARGE_INTEGER bss_00465f28[NUMBER_OF_PROFILE_FRAMES]; // frame begin times
static __int64 bss_00465fa8[NUMBER_OF_RASTERIZER_PROFILES]; // pushbuffer sizes
static LARGE_INTEGER bss_00466090[NUMBER_OF_RASTERIZER_PROFILES]; // profile times
static LARGE_INTEGER bss_00466178[NUMBER_OF_RASTERIZER_PROFILES]; // profile begin times
static __int64 bss_00466260; // frame pushbuffer size
static __int64 bss_00466268; // pushbuffer size
static short bss_00466270; // frame index
static short bss_00466274; // completed frame index
static short local_profile_enable;
static unsigned long bss_0046627c; // completed profiles
static volatile short bss_00466280; // error flags
static short bss_00466288; // error count

/* ---------- private code */

static void rasterizer_profile_assert(
	short profile,
	char const *message,
	boolean condition)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_profile.c", 60, message);

	if (!condition && bss_00466288<MAXIMUM_PROFILE_ERRORS)
	{
		if (profile!=NONE)
		{
			error(_error_silent, "### PROFILE (#%d): %s -- tell Bernie!", profile, message);
		}
		else
		{
			error(_error_silent, "### PROFILE: %s -- tell Bernie!", profile, message);
		}
		bss_00466288++;
	}

	return;
}

// TODO: profile index sign extension hoisted above the begin/end branch, begin time reload missing in end branch
static void __cdecl rasterizer_profile_callback(
	DWORD context)
{
	short profile= (short)context;
	boolean begin= TEST_FLAG(context, 31);

	if (profile>=0 && profile<NUMBER_OF_RASTERIZER_PROFILES)
	{
		LARGE_INTEGER time;

		QueryPerformanceCounter(&time);
		if (begin)
		{
			if (bss_00466178[profile].QuadPart)
			{
				SET_FLAG(bss_00466280, _profile_error_begin_out_of_synch_bit, TRUE);
			}
			bss_00466178[profile]= time;
		}
		else
		{
			if (bss_00466178[profile].QuadPart)
			{
				LARGE_INTEGER begin_time= bss_00466178[profile];

				bss_00466090[profile].QuadPart= time.QuadPart-begin_time.QuadPart;
				bss_00466178[profile].QuadPart= 0;
			}
			else
			{
				SET_FLAG(bss_00466280, _profile_error_end_out_of_synch_bit, TRUE);
			}
		}
	}
	else
	{
		SET_FLAG(bss_00466280, _profile_error_invalid_context_bit, TRUE);
	}

	return;
}

// TODO: instruction scheduling of the frame time subtraction
static void __cdecl rasterizer_profile_frame_callback(
	DWORD context)
{
	short frame_index= (short)(context>>1);

	if (frame_index>=0 && frame_index<NUMBER_OF_PROFILE_FRAMES)
	{
		LARGE_INTEGER time;

		QueryPerformanceCounter(&time);
		if (context&1)
		{
			LARGE_INTEGER begin_time= bss_00465f28[frame_index];

			bss_00465ea8[frame_index]= time;
			bss_00466274= frame_index;
			bss_00465e28[frame_index].QuadPart= time.QuadPart-begin_time.QuadPart;
		}
		else
		{
			bss_00465f28[frame_index]= time;
		}
	}

	return;
}

static boolean rasterizer_profile_enabled(
	void)
{
	return rasterizer_debug_options.statistics_mode==_rasterizer_statistics_mode_profile || rasterizer_debug_options.profile_log_enabled;
}

/* ---------- public code */

boolean rasterizer_profile_initialize(
	void)
{
	short profile;

	for (profile= 0; profile<NUMBER_OF_RASTERIZER_PROFILES; profile++)
	{
		bss_00466178[profile].LowPart= 0;
		bss_00466178[profile].HighPart= 0;
		bss_00466090[profile].LowPart= 0;
		bss_00466090[profile].HighPart= 0;
	}
	csmemset(bss_00465f28, 0, sizeof(bss_00465f28));
	csmemset(bss_00465ea8, 0, sizeof(bss_00465ea8));
	csmemset(bss_00465e28, 0, sizeof(bss_00465e28));
	QueryPerformanceFrequency(&data_0030cf00);

	return TRUE;
}

void rasterizer_profile_frame_begin(
	void)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_profile.c", 194, global_d3d_device);

	rasterizer_profile_assert(NONE, "callback recieved invalid context", !TEST_FLAG(bss_00466280, _profile_error_invalid_context_bit));
	rasterizer_profile_assert(NONE, "begin out-of-synch", !TEST_FLAG(bss_00466280, _profile_error_begin_out_of_synch_bit));
	rasterizer_profile_assert(NONE, "end out-of-synch", !TEST_FLAG(bss_00466280, _profile_error_end_out_of_synch_bit));
	bss_00466280= 0;

	if (rasterizer_profile_enabled())
	{
		bss_0046627c= 0;
		data_0030cf0c= 0;
		data_0030cf08= NONE;
		bss_00466260= 0;
		bss_00466270= (bss_00466270+1)%NUMBER_OF_PROFILE_FRAMES;
		D3DDevice_InsertCallback(D3DCALLBACK_READ, rasterizer_profile_frame_callback, bss_00466270*2);
	}

	return;
}

void rasterizer_profile_window_begin(
	void)
{
	data_0030cf0c= global_window_parameters.window_index;
	data_0030cf08= NONE;

	return;
}

void _rasterizer_profile_enable(
	boolean enable)
{
	if (enable)
	{
		match_vassert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_profile.c", 244, local_profile_enable>0, "local_profile_enable>0");
		local_profile_enable--;
	}
	else
	{
		match_vassert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_profile.c", 249, local_profile_enable<100, "local_profile_enable<100");
		local_profile_enable++;
	}

	return;
}

void rasterizer_profile_begin(
	short profile)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_profile.c", 259, global_d3d_device);

	if (rasterizer_profile_enabled() && !data_0030cf0c && !local_profile_enable)
	{
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_profile.c", 265, profile>=0 && profile<NUMBER_OF_RASTERIZER_PROFILES);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_profile.c", 266, global_d3d_device);

		rasterizer_profile_assert(profile, "profile duplication within frame (begin)", !TEST_FLAG(bss_0046627c, profile));
		rasterizer_profile_assert(profile, "profile begin/end pairing incorrect (begin)", data_0030cf08==NONE);
		D3DDevice_InsertCallback(D3DCALLBACK_READ, rasterizer_profile_callback, profile|PROFILE_BEGIN_FLAG);
		data_0030cf08= profile;
		bss_00465fa8[profile]= 0;
	}

	return;
}

void rasterizer_profile_end(
	short profile)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_profile.c", 294, global_d3d_device);

	if (rasterizer_profile_enabled() && !data_0030cf0c && !local_profile_enable)
	{
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_profile.c", 300, profile>=0 && profile<NUMBER_OF_RASTERIZER_PROFILES);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_profile.c", 301, global_d3d_device);

		rasterizer_profile_assert(profile, "profile duplication within frame (end)", !TEST_FLAG(bss_0046627c, profile));
		rasterizer_profile_assert(profile, "profile begin/end pairing incorrect (end)", data_0030cf08==profile);
		D3DDevice_InsertCallback(D3DCALLBACK_WRITE, rasterizer_profile_callback, profile);
		bss_00465fa8[profile]= 0;
		data_0030cf08= NONE;
		SET_FLAG(bss_0046627c, profile, TRUE);
	}

	return;
}

char const *rasterizer_profile_get_string(
	short profile)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_profile.c", 363, profile>=0 && profile<NUMBER_OF_RASTERIZER_PROFILES);

	return data_0030cf10[profile];
}

// TODO: register allocation in the NUMBER_OF_RASTERIZER_PROFILES summation loop (esi vs edx)
real rasterizer_profile_query(
	short profile)
{
	real time= 0.f;

	if (rasterizer_profile_enabled())
	{
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_profile.c", 375, global_d3d_device);

		if (profile==NUMBER_OF_RASTERIZER_PROFILES)
		{
			short profile_index;

			for (profile_index= 0; profile_index<NUMBER_OF_RASTERIZER_PROFILES; profile_index++)
			{
				LARGE_INTEGER profile_time= bss_00466090[profile_index];

				time+= (real)profile_time.QuadPart;
			}
			time/= (real)data_0030cf00.QuadPart;
		}
		else
		{
			match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_profile.c", 391, profile>=0 && profile<NUMBER_OF_RASTERIZER_PROFILES);
			rasterizer_profile_assert(profile, "profile not completed (query)", data_0030cf08==NONE);

			if (TEST_FLAG(bss_0046627c, profile))
			{
				LARGE_INTEGER profile_time= bss_00466090[profile];

				time= (real)profile_time.QuadPart/(real)data_0030cf00.QuadPart;
			}
			else
			{
				time= -1.f;
			}
		}
	}

	return time;
}

long rasterizer_profile_query_pushbuffer(
	short profile)
{
	long size= 0;

	if (rasterizer_profile_enabled())
	{
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_profile.c", 415, global_d3d_device);

		if (profile==NUMBER_OF_RASTERIZER_PROFILES)
		{
			size= 0;
		}
		else
		{
			match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_profile.c", 430, profile>=0 && profile<NUMBER_OF_RASTERIZER_PROFILES);
			rasterizer_profile_assert(profile, "profile not completed (query)", data_0030cf08==NONE);

			if (TEST_FLAG(bss_0046627c, profile))
			{
				__int64 pushbuffer_size= bss_00465fa8[profile];

				if (pushbuffer_size>LONG_MAX)
				{
					size= LONG_MAX;
				}
				else
				{
					size= (long)pushbuffer_size;
				}
			}
			else
			{
				size= NONE;
			}
		}
	}

	return size;
}

void rasterizer_profile_frame_end(
	void)
{
	if (rasterizer_profile_enabled())
	{
		__int64 pushbuffer_size;

		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_profile.c", 455, global_d3d_device);

		pushbuffer_size= -bss_00466260;
		bss_00466268= (long)(pushbuffer_size>LONG_MAX ? LONG_MAX : pushbuffer_size);

		D3DDevice_InsertCallback(D3DCALLBACK_WRITE, rasterizer_profile_frame_callback, bss_00466270*2+1);
		profile_rasterizer_stats((real)bss_00465e28[bss_00466274].QuadPart*1000.f/(real)data_0030cf00.QuadPart,
			bss_00466268);
	}

	return;
}

void rasterizer_profile_window_end(
	void)
{
	return;
}

void rasterizer_profile_dispose(
	void)
{
	return;
}
