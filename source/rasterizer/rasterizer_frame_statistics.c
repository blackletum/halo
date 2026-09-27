/*
RASTERIZER_FRAME_STATISTICS.C

symbols in this file:
0016E3A0 0040:
	_rasterizer_frame_statistics_initialize (0000)
0016E3E0 0020:
	_rasterizer_frame_statistics_begin (0000)
0016E400 0180:
	_rasterizer_frame_statistics_get_fps (0000)
0016E580 0040:
	_rasterizer_fps_accumulate (0000)
0016E5C0 0020:
	_code_0016e5c0 (0000)
0016E5E0 0040:
	_rasterizer_frame_statistics_count_static_vertices (0000)
0016E620 0130:
	_rasterizer_frame_statistics_count_dynamic_vertices (0000)
0016E750 1050:
	_rasterizer_frame_statistics_draw (0000)
0016F7A0 0010:
	_rasterizer_frame_statistics_end (0000)
0016F7B0 0020:
	_rasterizer_frame_statistics_dispose (0000)
0029DC30 000e:
	??_C@_0O@JFBHNPBL@d?3?2r?9prof?4txt?$AA@ (0000)
0029DC40 0018:
	??_C@_0BI@GCMBLDJP@?$CD?$CD?$CD?5ERROR?5out?5of?5memory?$AA@ (0000)
0029DC58 0038:
	??_C@_0DI@DAFJELOG@c?3?2halo?2SOURCE?2rasterizer?2raster@ (0000)
0029DC90 0028:
	??_C@_0CI@LGKHNHMC@rasterizer_frame_statistics_temp@ (0000)
0029DCB8 0040:
	??_C@_0EA@PGBNPAHI@triangle_count?$DMRASTERIZER_MAXIMU@ (0000)
0029DCF8 0024:
	??_C@_0CE@KDLIJAEE@average?5total?5pushbuffer?$DN?5?$CFd?5byt@ (0000)
0029DD1C 0026:
	??_C@_0CG@DFFGIJGJ@average?5total?5frame?5time?$DN?5?$CF?42f?5m@ (0000)
0029DD44 0007:
	??_C@_06NBDEAPCB@?5?5?9?9?9?9?$AA@ (0000)
0029DD4C 0006:
	??_C@_05GDJIKCCN@?$CF6?42f?$AA@ (0000)
0029DD54 0002:
	??_C@_01LFCBOECM@?4?$AA@ (0000)
0029DD58 0035:
	??_C@_0DF@GMJOLAAA@?$CD?$CD?$CD?5ERROR?5failed?5to?5open?5rasteri@ (0000)
0029DD90 0019:
	??_C@_0BJ@JJFENEFI@?$HMtsystem?5available?$HMt?$CFdKb?$AA@ (0000)
0029DDAC 0017:
	??_C@_0BH@EJIDKNJD@?$HMn?$HMtsystem?5total?$HMt?$CFdKb?$AA@ (0000)
0029DDC4 0013:
	??_C@_0BD@JJMMIDNN@?$HMn?$HMttotal?$HMt?$CFd?5?$CI?$CFd?$CJ?$AA@ (0000)
0029DDD8 0009:
	??_C@_08NACADNAD@?$HMt?$CFs?$HMt?$CFd?$AA@ (0000)
0029DDE4 0024:
	??_C@_0CE@GPLJMHJA@vertex?5shaders?$HMt?$HO35k?5last?5i?5chec@ (0000)
0029DE08 0010:
	??_C@_0BA@PIMAGLFH@debug?5geometry?$CK?$AA@ (0000)
0029DE18 0017:
	??_C@_0BH@OHBLOMMO@motion?5sensor?5buffers?$CK?$AA@ (0000)
0029DE30 000e:
	??_C@_0O@LPNPGMEL@water?5buffers?$AA@ (0000)
0029DE40 0012:
	??_C@_0BC@MBLMGAF@sun?5glow?5buffers?$CK?$AA@ (0000)
0029DE54 000f:
	??_C@_0P@JGCOFABI@shadow?5buffers?$AA@ (0000)
0029DE64 0024:
	??_C@_0CE@GGJOAJBB@mirror?5buffers?5?$CIincludes?5z?9buffe@ (0000)
0029DE88 0011:
	??_C@_0BB@IAJCMCIG@bump?5map?5palette?$AA@ (0000)
0029DE9C 001c:
	??_C@_0BM@KDCCBLNC@transparent?5geometry?5groups?$AA@ (0000)
0029DEB8 0012:
	??_C@_0BC@BJBCACME@dynamic?5triangles?$AA@ (0000)
0029DECC 0022:
	??_C@_0CC@LDJJCNJE@dynamic?5vertices?5?$CIdetail?5objects@ (0000)
0029DEF0 0019:
	??_C@_0BJ@MNAIOGBM@dynamic?5vertices?5?$CImodel?$CJ?$AA@ (0000)
0029DF0C 001a:
	??_C@_0BK@CDEJLHGG@dynamic?5vertices?5?$CIscreen?$CJ?$AA@ (0000)
0029DF28 0018:
	??_C@_0BI@HPJPBHLO@dynamic?5vertices?5?$CIlit?$CK?$CJ?$AA@ (0000)
0029DF40 0019:
	??_C@_0BJ@DKPGOBKB@dynamic?5vertices?5?$CIunlit?$CJ?$AA@ (0000)
0029DF5C 000c:
	??_C@_0M@DEOKAGLG@memory?5pool?$AA@ (0000)
0029DF68 0023:
	??_C@_0CD@ELLHHMII@?$HMtallocation?$HMtmemory?5usage?5?$CIbyte@ (0000)
0029DF8C 0014:
	??_C@_0BE@ELPADKKO@?$HMttotal?$HMt?$CF?42f?$HMt?$CFd?$HMn?$AA@ (0000)
0029DFA0 000e:
	??_C@_0O@NBNGOGEK@?$HMt?$CFs?$HMt?9?9?9?9?$HMt0?$AA@ (0000)
0029DFB0 000f:
	??_C@_0P@EMPKACCD@?$HMt?$CFs?$HMt?$CF?42f?$HMt?$CFd?$AA@ (0000)
0029DFC0 002a:
	??_C@_0CK@PDOKMEKL@?$HMtGPU?5profile?$HMttime?5?$CImsecs?$CJ?$HMtdat@ (0000)
0029DFEC 0028:
	??_C@_0CI@OJALLPNK@?$HMt?$CFd?5dynamic?5lights?$HMn?$HMt?$CFd?5lens?5f@ (0000)
0029E014 0023:
	??_C@_0CD@DPCNBBDK@?$HMtdynamic?5geometry?$HMt?$CFd?1?$CFd?$HMt?$CFd?1?$CFd@ (0000)
0029E038 0017:
	??_C@_0BH@JLJHFKOG@?$HMtdecals?$HMt?$CFd?$HMt?$CFd?$HMt?$CFd?$HMn?$AA@ (0000)
0029E050 0034:
	??_C@_0DE@DDLABOMO@?$HMtsolid?$HMt?$CFd?$HMt?$CFd?$HMt?$CFd?$HMn?$HMttranspare@ (0000)
0029E084 001a:
	??_C@_0BK@IOKCDMIA@?$HMtmodels?5?$CI?$CFd?$CJ?$HMt?$CFd?$HMt?$CFd?$HMt?$CFd?$AA@ (0000)
0029E0A0 0021:
	??_C@_0CB@EOMGBMNP@?$HMtmodel?5shadows?5?$CI?$CFd?$CJ?$HMt?$CFd?$HMt?$CFd?$HMt?$CFd@ (0000)
0029E0C8 0113:
	??_C@_0BBD@GCJAAPME@?$HMtlightmaps?$HMt?$CFd?$HMt?$CFd?$HMt?$CFd?$HMn?$HMtshado@ (0000)
0029E1DC 001a:
	??_C@_0BK@KOANHEHC@?$HMtenvironment?$HMt?$CFd?$HMt?$CFd?$HMt?$CFd?$AA@ (0000)
0029E1F8 0016:
	??_C@_0BG@GAEDMNLC@?$HMttotal?$HMt?$CFd?$HMt?$CFd?$HMt?$CFd?$HMn?$AA@ (0000)
0029E210 0024:
	??_C@_0CE@EIBEMOMJ@?$HMt?$HMtvertices?$HMttriangles?$HMtprimiti@ (0000)
0029E234 0038:
	??_C@_0DI@JADDMGFO@?$HMtlocal_player_count?$HMt?$CFd?$HMn?$HMtmain@ (0000)
0029E26C 0037:
	??_C@_0DH@JFMJJCIO@?$HMtskinning?$HMt?$CFd?$HMn?$HMtlighting?$HMt?$CFd?$HMn@ (0000)
0029E2A4 0038:
	??_C@_0DI@GOEPEHGF@?$HMtfogged?$HMt?$CFd?$HMn?$HMtnormal?$HMt?$CFd?$HMn?$HMtfa@ (0000)
0029E2DC 001b:
	??_C@_0BL@IBKJHKIF@?$HMt?$CF?40f?$HMt?$CF?40f?$HMt?$CF?40f?$HMt?$CF?40f?$HMn?$AA@ (0000)
0029E2F8 0020:
	??_C@_0CA@DPIIOMPF@?$HMt?$CF?40f?$HMt?$CF?40f?1?$CF?40f?$HMt?$CF?40f?$HMt?$CF?40f?$HMn?$AA@ (0000)
0029E318 0029:
	??_C@_0CJ@FFAAFLA@?$HMn?$HMtframerate?$HMtaverage?5?$CIof?5?$CFd?$CJ?$HMt@ (0000)
0030D4CC 0004:
	_profile_log_path (0000)
00466320 0740:
	_bss_00466320 (0000)
00466A60 0004:
	_rasterizer_frame_statistics_temp_buffer (0000)
00466A68 0008:
	_rasterizer_fps_accumulation_time (0000)
00466A70 0008:
	_rasterizer_fps_accumulation_frame_index (0000)
00466A78 0004:
	_local_profile_log (0000)
00466A80 00f0:
	?time_samples@?1??rasterizer_frame_statistics_get_fps@@9@9 (0000)
00466B70 0002:
	?fps_sample_count@?1??rasterizer_frame_statistics_get_fps@@9@9 (0000)
00466B74 0002:
	_bss_00466b74 (0000)
00466B78 0004:
	_bss_00466b78 (0000)
00466B7C 0004:
	_bss_00466b7c (0000)
*/

/* ---------- headers */

#include "cseries.h"
#include "cseries_windows.h"
#include "errors.h"
#include "real_math.h"
#include "integer_math.h"
#include "rasterizer.h"
#include "rasterizer_geometry.h"
#include "draw_string.h"
#include "interface.h"

/* ---------- constants */

enum
{
	RASTERIZER_FRAME_STATISTICS_FPS_SAMPLE_COUNT = 60,
	RASTERIZER_FRAME_STATISTICS_TEMP_BUFFER_SIZE = 0x24000,
	RASTERIZER_PROFILE_LOG_FRAME_COUNT = 16,
	RASTERIZER_PROFILE_LOG_NAME_WIDTH = 32,
	NUMBER_OF_MEMORY_ALLOCATIONS = 16
};

/* ---------- structures */

struct memory_allocation
{
	char *name;
	long size;
	long unused;
};

/* ---------- prototypes */

void *rasterizer_dynamic_triangles_lock(long triangle_buffer_index);
void rasterizer_dynamic_triangles_unlock(long triangle_buffer_index);
void qsort_2byte(void *base, long count, boolean (*compare)(word a, word b));

real rasterizer_profile_query(short profile_index);
long rasterizer_profile_query_pushbuffer(short profile_index);
char *rasterizer_profile_get_string(short profile_index);

short main_get_window_count(void);
short local_player_count(void);

static boolean code_0016e5c0(word a, word b);

/* ---------- globals */

const char *profile_log_path = "d:\\r-prof.txt";

static unsigned short *rasterizer_frame_statistics_temp_buffer;
static __int64 rasterizer_fps_accumulation_time;
static __int64 rasterizer_fps_accumulation_frame_index;
static FILE *local_profile_log;

static real bss_00466320[NUMBER_OF_RASTERIZER_PROFILES][RASTERIZER_PROFILE_LOG_FRAME_COUNT];
static short bss_00466b74;
static real bss_00466b78;
static long bss_00466b7c;

/* ---------- public code */

boolean rasterizer_frame_statistics_initialize(
	void)
{
	boolean success = TRUE;

	rasterizer_frame_statistics_temp_buffer = match_malloc("c:\\halo\\SOURCE\\rasterizer\\rasterizer_frame_statistics.c", 41, RASTERIZER_FRAME_STATISTICS_TEMP_BUFFER_SIZE);
	if (!rasterizer_frame_statistics_temp_buffer)
	{
		error(_error_silent, "### ERROR out of memory");
		success = FALSE;
	}

	return success;
}

void rasterizer_frame_statistics_begin(
	void)
{
	csmemset(&rasterizer_frame_statistics, 0, sizeof(rasterizer_frame_statistics));

	return;
}

// TODO: register allocation differs (the original reloads fps_sample_count from memory at the loop start and
// after the loop, as if the stores to time_samples might alias it; with separate statics the compiler folds these loads)
void rasterizer_frame_statistics_get_fps(
	struct rasterizer_frame_statistics *statistics)
{
	static unsigned long time_samples[RASTERIZER_FRAME_STATISTICS_FPS_SAMPLE_COUNT];
	static short fps_sample_count;

	if (rasterizer_debug_options.statistics_mode && statistics)
	{
		unsigned long time = system_milliseconds();
		short sample_count = fps_sample_count;

		if (sample_count)
		{
			short sample_index;
			unsigned long dt = time - time_samples[0];
			unsigned long min_dt = dt;
			unsigned long max_dt = dt;

			for (sample_index = fps_sample_count - 1; sample_index > 0; sample_index--)
			{
				if (sample_index > 1)
				{
					dt = time_samples[sample_index - 1] - time_samples[sample_index];

					if (dt <= min_dt)
					{
						min_dt = dt;
					}
					if (dt > max_dt)
					{
						max_dt = dt;
					}
				}
				time_samples[sample_index] = time_samples[sample_index - 1];
			}
			sample_count = fps_sample_count;

			statistics->fps = 1000.f / MAX(time - time_samples[0], 1);
			statistics->fps_sample_count = sample_count;
			statistics->fps_average = sample_count * 1000.f / MAX(time - time_samples[sample_count - 1], 1);
			statistics->fps_max = 1000.f / MAX(min_dt, 1);
			statistics->fps_min = 1000.f / MAX(max_dt, 1);
		}

		time_samples[0] = time;
		fps_sample_count = MIN(sample_count + 1, RASTERIZER_FRAME_STATISTICS_FPS_SAMPLE_COUNT);
	}
	else
	{
		fps_sample_count = 0;
	}

	return;
}

void rasterizer_fps_accumulate(
	void)
{
	rasterizer_debug_options.fps_accumulation = TRUE;
	rasterizer_fps_accumulation_time = system_milliseconds();
	rasterizer_fps_accumulation_frame_index = rasterizer_globals.frame_index;

	return;
}

static boolean code_0016e5c0(
	word a,
	word b)
{
	boolean result;

	if (a > b)
	{
		result = TRUE;
	}
	else if (a < b)
	{
		result = FALSE;
	}
	else
	{
		result = FALSE;
	}

	return result;
}

// TODO: original pushes esi after the first null check (branches straight to the epilogue)
long rasterizer_frame_statistics_count_static_vertices(
	const struct triangle_buffer *triangle_buffer,
	const struct vertex_buffer *vertex_buffer)
{
	long vertex_count = 0;

	if (triangle_buffer && vertex_buffer)
	{
		if (triangle_buffer->type == _triangle_buffer_type_precompiled_strip)
		{
			vertex_count = triangle_buffer->count + 2;
		}
		else if (triangle_buffer->type == _triangle_buffer_type_triangles)
		{
			vertex_count = vertex_buffer->count;
		}
	}

	return vertex_count;
}

long rasterizer_frame_statistics_count_dynamic_vertices(
	long triangle_buffer_index,
	long first_triangle,
	long triangle_count)
{
	long vertex_count = 0;

	if (triangle_buffer_index >= 0)
	{
		word *triangles = rasterizer_dynamic_triangles_lock(triangle_buffer_index);

		if (triangles)
		{
			long index_count = 3 * triangle_count;
			word last_index = NONE;
			long index;

			match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_frame_statistics.c", 217, triangle_count<RASTERIZER_MAXIMUM_TRIANGLES_PER_TRIANGLE_BUFFER);
			match_vassert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_frame_statistics.c", 218, rasterizer_frame_statistics_temp_buffer, "rasterizer_frame_statistics_temp_buffer");

			csmemcpy(rasterizer_frame_statistics_temp_buffer, triangles + 3 * first_triangle, 3 * triangle_count * sizeof(word));
			qsort_2byte(rasterizer_frame_statistics_temp_buffer, index_count, code_0016e5c0);

			for (index = 0; index < index_count; index++)
			{
				if (last_index != rasterizer_frame_statistics_temp_buffer[index])
				{
					last_index = rasterizer_frame_statistics_temp_buffer[index];
					vertex_count++;
				}
			}

			rasterizer_dynamic_triangles_unlock(triangle_buffer_index);
		}
	}
	else
	{
		short type = (short)-triangle_buffer_index;

		if (type == 3 || type == 4)
		{
			vertex_count = triangle_count / (type - 2);
		}
		else
		{
			vertex_count = type;
		}
	}

	return vertex_count;
}

// TODO: a few register swaps in the geometry total sums at the top
void rasterizer_frame_statistics_draw(
	void)
{
	if (rasterizer_debug_options.statistics_mode)
	{
		char string[12288];
		point2d cursor = { 0, 0 };
		rectangle2d bounds;
		short tab_stops[6] = { 100, 200, 300, 400, 500, 600 };
		real_argb_color text_color = { 1.f, 0.66f, 1.f, 0.66f };
		real_argb_color header_color = { 1.f, 1.f, 1.f, 1.f };
		real_argb_color default_color = { 1.f, 1.f, 1.f, 1.f };
		short x0 = rasterizer_globals.frame_bounds.x0;
		long environment_vertices = rasterizer_frame_statistics.lightmaps.vertices + (rasterizer_frame_statistics.shadows.vertices + (rasterizer_frame_statistics.lights.vertices + (rasterizer_frame_statistics.textures.vertices + (rasterizer_frame_statistics.lights_specular.vertices + (rasterizer_frame_statistics.lightmaps_specular.vertices + (rasterizer_frame_statistics.lightmaps_reflection_mask.vertices + (rasterizer_frame_statistics.reflections.vertices + rasterizer_frame_statistics.transparent.vertices + rasterizer_frame_statistics.fog.vertices)))))));
		long environment_triangles = rasterizer_frame_statistics.lightmaps.triangles + (rasterizer_frame_statistics.shadows.triangles + (rasterizer_frame_statistics.lights.triangles + (rasterizer_frame_statistics.textures.triangles + (rasterizer_frame_statistics.lights_specular.triangles + (rasterizer_frame_statistics.lightmaps_specular.triangles + (rasterizer_frame_statistics.lightmaps_reflection_mask.triangles + (rasterizer_frame_statistics.reflections.triangles + rasterizer_frame_statistics.fog.triangles + rasterizer_frame_statistics.transparent.triangles)))))));
		long environment_primitives = rasterizer_frame_statistics.lightmaps.primitives + (rasterizer_frame_statistics.shadows.primitives + (rasterizer_frame_statistics.lights.primitives + (rasterizer_frame_statistics.textures.primitives + (rasterizer_frame_statistics.lights_specular.primitives + (rasterizer_frame_statistics.lightmaps_specular.primitives + (rasterizer_frame_statistics.lightmaps_reflection_mask.primitives + (rasterizer_frame_statistics.reflections.primitives + rasterizer_frame_statistics.transparent.primitives + rasterizer_frame_statistics.fog.primitives)))))));
		long model_vertices = rasterizer_frame_statistics.models_transparent.vertices + rasterizer_frame_statistics.models_solid.vertices;
		long model_triangles = rasterizer_frame_statistics.models_solid.triangles + rasterizer_frame_statistics.models_transparent.triangles;
		long model_primitives = rasterizer_frame_statistics.models_solid.primitives + rasterizer_frame_statistics.models_transparent.primitives;
		long total_vertices = environment_vertices + model_vertices + rasterizer_frame_statistics.model_shadows.vertices;
		long total_triangles = environment_triangles + model_triangles + rasterizer_frame_statistics.model_shadows.triangles;
		long total_primitives = environment_primitives + model_primitives + rasterizer_frame_statistics.model_shadows.primitives;
		short tab_index;

		for (tab_index = 0; tab_index < NUMBEROF(tab_stops); tab_index++)
		{
			tab_stops[tab_index] += x0;
		}

		bounds = rasterizer_globals.frame_bounds;
		offset_rectangle2d(&bounds, 0, 32);
		interface_set_bitmap_text_draw_mode(1, -1, 0, 0, 5, 0);

		sprintf(string, "|n|tframerate|taverage (of %d)|tmin|tmax", rasterizer_frame_statistics.fps_sample_count);
		tab_stops[0] = x0;
		draw_string_set_tab_stops(tab_stops, NUMBEROF(tab_stops));
		draw_string_set_color(&header_color);
		rasterizer_draw_string(&bounds, NULL, &cursor, -4, string);
		bounds.y0 = cursor.y - 1;

		if (rasterizer_debug_options.fps_accumulation)
		{
			__int64 frames = rasterizer_globals.frame_index - rasterizer_fps_accumulation_frame_index;
			__int64 milliseconds = system_milliseconds() - rasterizer_fps_accumulation_time;

			sprintf(string, "|t%.0f|t%.0f/%.0f|t%.0f|t%.0f|n", rasterizer_frame_statistics.fps, rasterizer_frame_statistics.fps_average, (real)frames * 1000.f / milliseconds, rasterizer_frame_statistics.fps_min, rasterizer_frame_statistics.fps_max);
		}
		else
		{
			sprintf(string, "|t%.0f|t%.0f|t%.0f|t%.0f|n", rasterizer_frame_statistics.fps, rasterizer_frame_statistics.fps_average, rasterizer_frame_statistics.fps_min, rasterizer_frame_statistics.fps_max);
		}
		tab_stops[0] = x0;
		draw_string_set_tab_stops(tab_stops, NUMBEROF(tab_stops));
		draw_string_set_color(&text_color);
		rasterizer_draw_string(&bounds, NULL, &cursor, -4, string);
		bounds.y0 = cursor.y - 1;

		if (rasterizer_debug_options.statistics_mode == _rasterizer_statistics_mode_general)
		{
			tab_stops[0] = x0;
			draw_string_set_tab_stops(tab_stops, NUMBEROF(tab_stops));
			draw_string_set_color(&text_color);
			sprintf(string, "|tfogged|t%d|n|tnormal|t%d|n|tfast|t%d|n|tscenery|t%d|n", rasterizer_frame_statistics.permutation_counts[0], rasterizer_frame_statistics.permutation_counts[1], rasterizer_frame_statistics.permutation_counts[2], rasterizer_frame_statistics.permutation_counts[3]);
			rasterizer_draw_string(&bounds, NULL, &cursor, -4, string);
			bounds.y0 = cursor.y - 1;
			sprintf(string, "|tskinning|t%d|n|tlighting|t%d|n|tvertex shaders|t%d|n", rasterizer_frame_statistics.skinning_count, rasterizer_frame_statistics.lighting_count, rasterizer_frame_statistics.vertex_shader_count);
			rasterizer_draw_string(&bounds, NULL, &cursor, -4, string);
			bounds.y0 = cursor.y - 1;
			sprintf(string, "|tlocal_player_count|t%d|n|tmain_get_window_count|t%d|n", local_player_count(), main_get_window_count());
			rasterizer_draw_string(&bounds, NULL, &cursor, -4, string);
			bounds.y0 = cursor.y - 1;
		}
		else if (rasterizer_debug_options.statistics_mode == _rasterizer_statistics_mode_geometry)
		{
			sprintf(string, "|t|tvertices|ttriangles|tprimitives");
			tab_stops[0] = x0;
			draw_string_set_tab_stops(tab_stops, NUMBEROF(tab_stops));
			draw_string_set_color(&header_color);
			rasterizer_draw_string(&bounds, NULL, &cursor, -4, string);
			bounds.y0 = cursor.y - 1;

			sprintf(string, "|ttotal|t%d|t%d|t%d|n", total_vertices, total_triangles, total_primitives);
			tab_stops[0] = x0;
			draw_string_set_tab_stops(tab_stops, NUMBEROF(tab_stops));
			draw_string_set_color(&text_color);
			rasterizer_draw_string(&bounds, NULL, &cursor, -4, string);
			bounds.y0 = cursor.y - 1;

			sprintf(string, "|tenvironment|t%d|t%d|t%d", environment_vertices, environment_triangles, environment_primitives);
			tab_stops[0] = x0 + 25;
			draw_string_set_tab_stops(tab_stops, NUMBEROF(tab_stops));
			rasterizer_draw_string(&bounds, NULL, &cursor, -4, string);
			bounds.y0 = cursor.y - 1;

			sprintf(string, "|tlightmaps|t%d|t%d|t%d|n|tshadows (%d)|t%d|t%d|t%d|n|tlights|t%d|t%d|t%d|n|ttextures|t%d|t%d|t%d|n|tlights specular|t%d|t%d|t%d|n|tlightmaps specular|t%d|t%d|t%d|n|tlightmaps ref.mask|t%d|t%d|t%d|n|treflections|t%d|t%d|t%d|n|ttransparent|t%d|t%d/%d|t%d|n|tfog|t%d|t%d|t%d|n",
				rasterizer_frame_statistics.lightmaps.vertices, rasterizer_frame_statistics.lightmaps.triangles, rasterizer_frame_statistics.lightmaps.primitives,
				rasterizer_frame_statistics.shadow_count, rasterizer_frame_statistics.shadows.vertices, rasterizer_frame_statistics.shadows.triangles, rasterizer_frame_statistics.shadows.primitives,
				rasterizer_frame_statistics.lights.vertices, rasterizer_frame_statistics.lights.triangles, rasterizer_frame_statistics.lights.primitives,
				rasterizer_frame_statistics.textures.vertices, rasterizer_frame_statistics.textures.triangles, rasterizer_frame_statistics.textures.primitives,
				rasterizer_frame_statistics.lights_specular.vertices, rasterizer_frame_statistics.lights_specular.triangles, rasterizer_frame_statistics.lights_specular.primitives,
				rasterizer_frame_statistics.lightmaps_specular.vertices, rasterizer_frame_statistics.lightmaps_specular.triangles, rasterizer_frame_statistics.lightmaps_specular.primitives,
				rasterizer_frame_statistics.lightmaps_reflection_mask.vertices, rasterizer_frame_statistics.lightmaps_reflection_mask.triangles, rasterizer_frame_statistics.lightmaps_reflection_mask.primitives,
				rasterizer_frame_statistics.reflections.vertices, rasterizer_frame_statistics.reflections.triangles, rasterizer_frame_statistics.reflections.primitives,
				rasterizer_frame_statistics.transparent.vertices, rasterizer_frame_statistics.transparent.triangles, rasterizer_frame_statistics.transparent.triangles_maximum, rasterizer_frame_statistics.transparent.primitives,
				rasterizer_frame_statistics.fog.vertices, rasterizer_frame_statistics.fog.triangles, rasterizer_frame_statistics.fog.primitives);
			tab_stops[0] = x0 + 50;
			draw_string_set_tab_stops(tab_stops, NUMBEROF(tab_stops));
			rasterizer_draw_string(&bounds, NULL, &cursor, -4, string);
			bounds.y0 = cursor.y - 1;

			sprintf(string, "|tmodel shadows (%d)|t%d|t%d|t%d", rasterizer_frame_statistics.model_shadow_count, rasterizer_frame_statistics.model_shadows.vertices, rasterizer_frame_statistics.model_shadows.triangles, rasterizer_frame_statistics.model_shadows.primitives);
			tab_stops[0] = x0 + 25;
			draw_string_set_tab_stops(tab_stops, NUMBEROF(tab_stops));
			rasterizer_draw_string(&bounds, NULL, &cursor, -4, string);
			bounds.y0 = cursor.y - 1;

			sprintf(string, "|tmodels (%d)|t%d|t%d|t%d", rasterizer_frame_statistics.model_count, model_vertices, model_triangles, model_primitives);
			tab_stops[0] = x0 + 25;
			draw_string_set_tab_stops(tab_stops, NUMBEROF(tab_stops));
			rasterizer_draw_string(&bounds, NULL, &cursor, -4, string);
			bounds.y0 = cursor.y - 1;

			sprintf(string, "|tsolid|t%d|t%d|t%d|n|ttransparent|t%d|t%d/%d|t%d|n",
				rasterizer_frame_statistics.models_solid.vertices, rasterizer_frame_statistics.models_solid.triangles, rasterizer_frame_statistics.models_solid.primitives,
				rasterizer_frame_statistics.models_transparent.vertices, rasterizer_frame_statistics.models_transparent.triangles, rasterizer_frame_statistics.models_transparent.triangles_maximum, rasterizer_frame_statistics.models_transparent.primitives);
			tab_stops[0] = x0 + 50;
			draw_string_set_tab_stops(tab_stops, NUMBEROF(tab_stops));
			rasterizer_draw_string(&bounds, NULL, &cursor, -4, string);
			bounds.y0 = cursor.y - 1;

			sprintf(string, "|tdecals|t%d|t%d|t%d|n", rasterizer_frame_statistics.decals.vertices, rasterizer_frame_statistics.decals.triangles, rasterizer_frame_statistics.decals.primitives);
			tab_stops[0] = x0;
			draw_string_set_tab_stops(tab_stops, NUMBEROF(tab_stops));
			rasterizer_draw_string(&bounds, NULL, &cursor, -4, string);
			bounds.y0 = cursor.y - 1;

			sprintf(string, "|tdynamic geometry|t%d/%d|t%d/%d|n", rasterizer_frame_statistics.dynamic_vertex_count, rasterizer_frame_statistics.dynamic_vertex_buffer_count, rasterizer_frame_statistics.dynamic_triangle_count, rasterizer_frame_statistics.dynamic_triangle_buffer_count);
			tab_stops[0] = x0;
			draw_string_set_tab_stops(tab_stops, NUMBEROF(tab_stops));
			rasterizer_draw_string(&bounds, NULL, &cursor, -4, string);
			bounds.y0 = cursor.y - 1;

			sprintf(string, "|t%d dynamic lights|n|t%d lens flares|n", rasterizer_frame_statistics.dynamic_light_count, rasterizer_frame_statistics.lens_flare_count);
			tab_stops[0] = x0;
			draw_string_set_tab_stops(tab_stops, NUMBEROF(tab_stops));
			rasterizer_draw_string(&bounds, NULL, &cursor, -4, string);
			bounds.y0 = cursor.y - 1;
		}
		else if (rasterizer_debug_options.statistics_mode == _rasterizer_statistics_mode_profile)
		{
			short profile_index;

			tab_stops[0] = x0;
			tab_stops[1] = x0 + 200;
			tab_stops[2] = x0 + 300;
			tab_stops[3] = 600;
			sprintf(string, "|tGPU profile|ttime (msecs)|tdata (bytes)");
			draw_string_set_tab_stops(tab_stops, 4);
			draw_string_set_color(&header_color);
			cursor.y -= 30;
			rasterizer_draw_string(&bounds, NULL, &cursor, -4, string);
			bounds.y0 = cursor.y - 1;

			draw_string_set_color(&text_color);
			for (profile_index = 0; profile_index < NUMBER_OF_RASTERIZER_PROFILES; profile_index++)
			{
				real time = rasterizer_profile_query(profile_index);

				if (time >= 0.f)
				{
					sprintf(string, "|t%s|t%.2f|t%d", rasterizer_profile_get_string(profile_index), time * 1000.f, rasterizer_profile_query_pushbuffer(profile_index));
				}
				else
				{
					sprintf(string, "|t%s|t----|t0", rasterizer_profile_get_string(profile_index));
				}
				rasterizer_draw_string(&bounds, NULL, &cursor, -4, string);
				bounds.y0 = cursor.y - 1;
			}

			sprintf(string, "|ttotal|t%.2f|t%d|n", rasterizer_profile_query(NUMBER_OF_RASTERIZER_PROFILES) * 1000.f, rasterizer_profile_query_pushbuffer(NUMBER_OF_RASTERIZER_PROFILES));
			draw_string_set_color(global_real_argb_yellow);
			bounds.y0 += 4;
			rasterizer_draw_string(&bounds, NULL, &cursor, -4, string);
			bounds.y0 = cursor.y - 1;
		}
		else if (rasterizer_debug_options.statistics_mode == _rasterizer_statistics_mode_memory)
		{
			long total = 0;
			long total_used = 0;
			struct memory_allocation allocations[NUMBER_OF_MEMORY_ALLOCATIONS] =
			{
				{ "memory pool", 98304, 0 },
				{ "dynamic vertices (unlit)", 196608, 0 },
				{ "dynamic vertices (lit*)", 72, 307200 },
				{ "dynamic vertices (screen)", 327680, 0 },
				{ "dynamic vertices (model)", 65536, 0 },
				{ "dynamic vertices (detail objects)", 131072, 0 },
				{ "dynamic triangles", 196608, 0 },
				{ "transparent geometry groups", 61440, 0 },
				{ "bump map palette", 1024, 0 },
				{ "mirror buffers (includes z-buffer*)", 614400, 307200 },
				{ "shadow buffers", 65536, 0 },
				{ "sun glow buffers*", 32768, 32768 },
				{ "water buffers", 65536, 0 },
				{ "motion sensor buffers*", 81920, 81920 },
				{ "debug geometry*", 1769472, 1769472 },
				{ "vertex shaders|t~35k last i checked", 35840, 12288 },
			};
			long allocation_index;
			MEMORYSTATUS memory_status;

			tab_stops[0] = x0;
			tab_stops[1] = x0 + 300;
			tab_stops[2] = 600;
			sprintf(string, "|tallocation|tmemory usage (bytes)");
			draw_string_set_tab_stops(tab_stops, 3);
			draw_string_set_color(&header_color);
			rasterizer_draw_string(&bounds, NULL, &cursor, -4, string);
			bounds.y0 = cursor.y - 1;

			draw_string_set_color(&text_color);
			for (allocation_index = 0; allocation_index < NUMBER_OF_MEMORY_ALLOCATIONS; allocation_index++)
			{
				sprintf(string, "|t%s|t%d", allocations[allocation_index].name, allocations[allocation_index].size);
				rasterizer_draw_string(&bounds, NULL, &cursor, -4, string);
				bounds.y0 = cursor.y - 1;
				total += allocations[allocation_index].size;
				total_used += allocations[allocation_index].size - allocations[allocation_index].unused;
			}

			sprintf(string, "|n|ttotal|t%d (%d)", total, total_used);
			rasterizer_draw_string(&bounds, NULL, &cursor, -4, string);
			bounds.y0 = cursor.y - 1;

			GlobalMemoryStatus(&memory_status);
			draw_string_set_color(&header_color);
			sprintf(string, "|n|tsystem total|t%dKb", memory_status.dwTotalPhys >> 10);
			rasterizer_draw_string(&bounds, NULL, &cursor, -4, string);
			bounds.y0 = cursor.y - 1;
			sprintf(string, "|tsystem available|t%dKb", memory_status.dwAvailPhys >> 10);
			rasterizer_draw_string(&bounds, NULL, &cursor, -4, string);
			bounds.y0 = cursor.y - 1;
			draw_string_set_color(&text_color);
		}

		draw_string_set_tab_stops(NULL, 0);
		draw_string_set_color(&default_color);
	}

	if (rasterizer_debug_options.profile_log_enabled)
	{
		if (!local_profile_log)
		{
			local_profile_log = fopen(profile_log_path, "w");
			if (!local_profile_log)
			{
				error(_error_silent, "### ERROR failed to open rasterizer profile log (%s)", profile_log_path);
				rasterizer_debug_options.profile_log_enabled = FALSE;
			}
			bss_00466b78 = 0.f;
			bss_00466b7c = 0;
		}

		if (local_profile_log)
		{
			short profile_index;

			for (profile_index = 0; profile_index < NUMBER_OF_RASTERIZER_PROFILES; profile_index++)
			{
				bss_00466320[profile_index][bss_00466b74] = rasterizer_profile_query(profile_index) * 1000.f;
			}
			bss_00466b78 += rasterizer_profile_query(NUMBER_OF_RASTERIZER_PROFILES) * 1000.f;
			bss_00466b7c += rasterizer_profile_query_pushbuffer(NUMBER_OF_RASTERIZER_PROFILES);

			if (++bss_00466b74 == RASTERIZER_PROFILE_LOG_FRAME_COUNT)
			{
				short log_profile_index;

				fprintf(local_profile_log, "\n");
				for (log_profile_index = 0; log_profile_index < NUMBER_OF_RASTERIZER_PROFILES; log_profile_index++)
				{
					short length;
					long frame_index;

					fprintf(local_profile_log, "%s", rasterizer_profile_get_string(log_profile_index));
					length = (short)csstrlen(rasterizer_profile_get_string(log_profile_index));
					while (length < RASTERIZER_PROFILE_LOG_NAME_WIDTH)
					{
						fprintf(local_profile_log, ".");
						length++;
					}

					for (frame_index = 0; frame_index < RASTERIZER_PROFILE_LOG_FRAME_COUNT; frame_index++)
					{
						if (bss_00466320[log_profile_index][frame_index] >= 0.f)
						{
							fprintf(local_profile_log, "%6.2f", bss_00466320[log_profile_index][frame_index]);
						}
						else
						{
							fprintf(local_profile_log, "  ----");
						}
					}
					fprintf(local_profile_log, "\n");
				}

				fprintf(local_profile_log, "average total frame time= %.2f msecs\n", bss_00466b78 / RASTERIZER_PROFILE_LOG_FRAME_COUNT);
				fprintf(local_profile_log, "average total pushbuffer= %d bytes\n", (bss_00466b7c + RASTERIZER_PROFILE_LOG_FRAME_COUNT / 2) / RASTERIZER_PROFILE_LOG_FRAME_COUNT);
				fflush(local_profile_log);

				bss_00466b74 = 0;
				bss_00466b78 = 0.f;
				bss_00466b7c = 0;
			}
		}
	}
	else if (local_profile_log)
	{
		fclose(local_profile_log);
		local_profile_log = NULL;
	}

	return;
}

void rasterizer_frame_statistics_end(
	void)
{
	return;
}

void rasterizer_frame_statistics_dispose(
	void)
{
	if (rasterizer_frame_statistics_temp_buffer)
	{
		match_free("c:\\halo\\SOURCE\\rasterizer\\rasterizer_frame_statistics.c", 837, rasterizer_frame_statistics_temp_buffer);
	}

	return;
}

