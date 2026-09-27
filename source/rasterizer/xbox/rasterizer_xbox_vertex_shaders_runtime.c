/*
RASTERIZER_XBOX_VERTEX_SHADERS_RUNTIME.C

symbols in this file:
00168350 0010:
	_IDirect3DDevice8_SetVertexShader@8 (0000)
00168360 0010:
	_IDirect3DDevice8_LoadVertexShader@12 (0000)
00168370 0010:
	_IDirect3DDevice8_SelectVertexShader@12 (0000)
00168380 0010:
	_IDirect3DDevice8_GetVertexShaderSize@12 (0000)
00168390 0560:
	_rasterizer_set_vertex_shader_permutation (0000)
0029C2F8 0018:
	_rdata_0029c2f8 (0000)
0029C310 0018:
	_rdata_0029c310 (0000)
0029C328 0030:
	_rdata_0029c328 (0000)
0029C358 0018:
	_rdata_0029c358 (0000)
0029C370 0060:
	_rdata_0029c370 (0000)
0029C3D0 0018:
	_rdata_0029c3d0 (0000)
0029C3E8 0018:
	_rdata_0029c3e8 (0000)
0029C400 0018:
	_rdata_0029c400 (0000)
0029C418 0018:
	_rdata_0029c418 (0000)
0029C430 0018:
	_rdata_0029c430 (0000)
0029C448 0048:
	_rdata_0029c448 (0000)
0029C490 0018:
	_rdata_0029c490 (0000)
0029C4A8 0048:
	_rdata_0029c4a8 (0000)
0029C4F0 0018:
	_rdata_0029c4f0 (0000)
0029C508 0018:
	_rdata_0029c508 (0000)
0029C520 0018:
	_rdata_0029c520 (0000)
0029C538 0090:
	_rdata_0029c538 (0000)
0029C5C8 0060:
	_rdata_0029c5c8 (0000)
0029C628 0018:
	_rdata_0029c628 (0000)
0029C640 0018:
	_rdata_0029c640 (0000)
0029C658 0018:
	_rdata_0029c658 (0000)
0029C670 0018:
	_rdata_0029c670 (0000)
0029C688 0090:
	_rdata_0029c688 (0000)
0029C718 0018:
	_rdata_0029c718 (0000)
0029C730 0018:
	_rdata_0029c730 (0000)
0029C748 0018:
	_rdata_0029c748 (0000)
0029C760 0048:
	_rdata_0029c760 (0000)
0029C7A8 0018:
	_rdata_0029c7a8 (0000)
0029C7C0 0018:
	_rdata_0029c7c0 (0000)
0029C7D8 0018:
	_rdata_0029c7d8 (0000)
0029C7F0 0030:
	_rdata_0029c7f0 (0000)
0029C820 0043:
	??_C@_0ED@PALLOMFH@IDirect3DDevice8_SetVertexShader@ (0000)
0029C868 0054:
	??_C@_0FE@NPNOIOBA@IDirect3DDevice8_SelectVertexSha@ (0000)
0029C8C0 0052:
	??_C@_0FC@JAKGKFDP@IDirect3DDevice8_LoadVertexShade@ (0000)
0029C918 0049:
	??_C@_0EJ@GJBDGHE@IDirect3DDevice8_SelectVertexSha@ (0000)
0029C964 0026:
	??_C@_0CG@FJEBEMLC@?$CD?$CD?$CD?5ERROR?5vertex?5shader?5was?5not?5@ (0000)
0029C98C 0038:
	??_C@_0DI@ENBGJMAN@?$CD?$CD?$CD?5ERROR?5packed?5vertex?5shaders?5@ (0000)
0029C9C8 0094:
	??_C@_0JE@FLCOGNAM@IDirect3DDevice8_GetVertexShader@ (0000)
0029CA60 004b:
	??_C@_0EL@IDNOJKOP@translation_table?$FLvertex_type?$CKpe@ (0000)
0029CAAC 003c:
	??_C@_0DM@HGGNMEDI@permutation_index?$DO?$DN0?5?$CG?$CG?5permutat@ (0000)
0029CAE8 0024:
	??_C@_0CE@IOILLCAH@?$CD?$CD?$CD?5ERROR?5unsupported?5vertex?5sha@ (0000)
0029CB10 0047:
	??_C@_0EH@NIDAECGF@vertex_shader_index?$DO?$DN0?5?$CG?$CG?5vertex@ (0000)
0029CB58 0048:
	??_C@_0EI@JLPCJIEP@c?3?2halo?2SOURCE?2rasterizer?2xbox?2r@ (0000)
0030D3B8 0002:
	_data_0030d3b8 (0000)
0030D3BC 0018:
	_data_0030d3bc (0000)

notes:
	_code_00168350 .. _code_00168380 are the out-of-line copies of the d3d8.h
	D3DINLINE wrappers (IDirect3DDevice8_SetVertexShader, _LoadVertexShader,
	_SelectVertexShader, _GetVertexShaderSize) the compiler emits for this unit;
	they are not written by hand.
*/

/* ---------- headers */

#include "cseries.h"
#include "cseries_windows.h"
#include "errors.h"
#include "rasterizer.h"
#include "rasterizer_geometry.h"
#include "xbox/rasterizer_xbox.h"

/* ---------- constants */

#define RASTERIZER_XBOX_VERTEX_SHADERS_RUNTIME_FILE "c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_vertex_shaders_runtime.c"

enum
{
	NUMBER_OF_PACKED_VERTEX_SHADERS = 3,
	MAXIMUM_PACKED_VERTEX_SHADER_SIZE = 136
};

/* ---------- structures */

struct packed_vertex_shader
{
	short vertex_shader_index;
	boolean loaded;
	UINT offset;
};

/* ---------- prototypes */

/* ---------- globals */

extern struct vertex_shader_table_entry vertex_shader_table[NUMBER_OF_VERTEX_SHADERS];

static short const rdata_0029c2f8[NUMBER_OF_XBOX_RASTERIZER_VERTEX_TYPES*1]= // vertex shader 0
{NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, 0, NONE, NONE};

static short const rdata_0029c310[NUMBER_OF_XBOX_RASTERIZER_VERTEX_TYPES*1]= // vertex shader 1
{NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, 1, NONE};

static short const rdata_0029c328[NUMBER_OF_XBOX_RASTERIZER_VERTEX_TYPES*2]= // vertex shader 4
{
	NONE, NONE,
	NONE, NONE,
	NONE, NONE,
	NONE, NONE,
	NONE, NONE,
	NONE, NONE,
	NONE, NONE,
	NONE, NONE,
	4, 3,
	NONE, NONE,
	NONE, NONE,
	NONE, NONE
};

static short const rdata_0029c358[NUMBER_OF_XBOX_RASTERIZER_VERTEX_TYPES*1]= // vertex shader 38
{NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, 38, NONE, NONE, NONE};

static short const rdata_0029c370[NUMBER_OF_XBOX_RASTERIZER_VERTEX_TYPES*4]= // vertex shader 65
{
	NONE, NONE, NONE, NONE,
	NONE, NONE, NONE, NONE,
	NONE, NONE, NONE, NONE,
	NONE, NONE, NONE, NONE,
	NONE, NONE, NONE, NONE,
	NONE, NONE, NONE, NONE,
	65, 2, 12, 66,
	NONE, NONE, NONE, NONE,
	NONE, NONE, NONE, NONE,
	NONE, NONE, NONE, NONE,
	NONE, NONE, NONE, NONE,
	NONE, NONE, NONE, NONE
};

static short const rdata_0029c3d0[NUMBER_OF_XBOX_RASTERIZER_VERTEX_TYPES*1]= // vertex shader 56
{NONE, NONE, NONE, NONE, NONE, NONE, 56, NONE, NONE, NONE, NONE, NONE};

static short const rdata_0029c3e8[NUMBER_OF_XBOX_RASTERIZER_VERTEX_TYPES*1]= // vertex shader 16
{16, 16, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE};

static short const rdata_0029c400[NUMBER_OF_XBOX_RASTERIZER_VERTEX_TYPES*1]= // vertex shader 49
{49, 49, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE};

static short const rdata_0029c418[NUMBER_OF_XBOX_RASTERIZER_VERTEX_TYPES*1]= // vertex shader 29
{29, 29, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE};

static short const rdata_0029c430[NUMBER_OF_XBOX_RASTERIZER_VERTEX_TYPES*1]= // vertex shader 40
{40, 40, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE};

static short const rdata_0029c448[NUMBER_OF_XBOX_RASTERIZER_VERTEX_TYPES*3]= // vertex shader 21
{
	21, 41, 59,
	21, 41, 59,
	NONE, NONE, NONE,
	NONE, NONE, NONE,
	NONE, NONE, NONE,
	NONE, NONE, NONE,
	NONE, NONE, NONE,
	NONE, NONE, NONE,
	NONE, NONE, NONE,
	NONE, NONE, NONE,
	NONE, NONE, NONE,
	NONE, NONE, NONE
};

static short const rdata_0029c490[NUMBER_OF_XBOX_RASTERIZER_VERTEX_TYPES*1]= // vertex shader 58
{58, 58, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE};

static short const rdata_0029c4a8[NUMBER_OF_XBOX_RASTERIZER_VERTEX_TYPES*3]= // vertex shader 42
{
	26, 42, 44,
	26, 42, 44,
	NONE, NONE, NONE,
	NONE, NONE, NONE,
	NONE, NONE, NONE,
	NONE, NONE, NONE,
	NONE, NONE, NONE,
	NONE, NONE, NONE,
	NONE, NONE, NONE,
	NONE, NONE, NONE,
	NONE, NONE, NONE,
	NONE, NONE, NONE
};

static short const rdata_0029c4f0[NUMBER_OF_XBOX_RASTERIZER_VERTEX_TYPES*1]= // vertex shader 51
{51, 51, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE};

static short const rdata_0029c508[NUMBER_OF_XBOX_RASTERIZER_VERTEX_TYPES*1]= // vertex shader 6
{6, 6, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE};

static short const rdata_0029c520[NUMBER_OF_XBOX_RASTERIZER_VERTEX_TYPES*1]= // vertex shader 8
{8, 8, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE};

static short const rdata_0029c538[NUMBER_OF_XBOX_RASTERIZER_VERTEX_TYPES*6]= // vertex shader 37
{
	37, 7, 54, 55, 53, 52,
	37, 7, 54, 55, 53, 52,
	NONE, NONE, NONE, NONE, NONE, NONE,
	NONE, NONE, NONE, NONE, NONE, NONE,
	NONE, NONE, NONE, NONE, NONE, NONE,
	NONE, NONE, NONE, NONE, NONE, NONE,
	NONE, NONE, NONE, NONE, NONE, NONE,
	NONE, NONE, NONE, NONE, NONE, NONE,
	NONE, NONE, NONE, NONE, NONE, NONE,
	NONE, NONE, NONE, NONE, NONE, NONE,
	NONE, NONE, NONE, NONE, NONE, NONE,
	NONE, NONE, NONE, NONE, NONE, NONE
};

static short const rdata_0029c5c8[NUMBER_OF_XBOX_RASTERIZER_VERTEX_TYPES*4]= // vertex shader 10
{
	NONE, NONE, NONE, NONE,
	NONE, NONE, NONE, NONE,
	NONE, NONE, NONE, NONE,
	NONE, NONE, NONE, NONE,
	17, 10, 9, 27,
	17, 10, 9, 27,
	NONE, NONE, NONE, NONE,
	NONE, NONE, NONE, NONE,
	NONE, NONE, NONE, NONE,
	NONE, NONE, NONE, NONE,
	NONE, NONE, NONE, NONE,
	NONE, NONE, NONE, NONE
};

static short const rdata_0029c628[NUMBER_OF_XBOX_RASTERIZER_VERTEX_TYPES*1]= // vertex shader 64
{NONE, NONE, NONE, NONE, 64, 64, NONE, NONE, NONE, NONE, NONE, NONE};

static short const rdata_0029c640[NUMBER_OF_XBOX_RASTERIZER_VERTEX_TYPES*1]= // vertex shader 39
{NONE, NONE, NONE, NONE, 39, 39, NONE, NONE, NONE, NONE, NONE, NONE};

static short const rdata_0029c658[NUMBER_OF_XBOX_RASTERIZER_VERTEX_TYPES*1]= // vertex shader 13
{NONE, NONE, NONE, NONE, 13, 13, NONE, NONE, NONE, NONE, NONE, NONE};

static short const rdata_0029c670[NUMBER_OF_XBOX_RASTERIZER_VERTEX_TYPES*1]= // vertex shader 5
{NONE, NONE, NONE, NONE, 5, 5, NONE, NONE, NONE, NONE, NONE, NONE};

static short const rdata_0029c688[NUMBER_OF_XBOX_RASTERIZER_VERTEX_TYPES*6]= // vertex shader 24
{
	24, 48, 34, 19, 35, NONE,
	24, 48, 34, 19, 35, NONE,
	NONE, NONE, NONE, NONE, NONE, NONE,
	NONE, NONE, NONE, NONE, NONE, NONE,
	47, 60, 57, 45, 62, 31,
	47, 60, 57, 45, 62, 31,
	NONE, NONE, NONE, NONE, NONE, NONE,
	NONE, NONE, NONE, NONE, NONE, NONE,
	NONE, NONE, NONE, NONE, NONE, NONE,
	NONE, NONE, NONE, NONE, NONE, NONE,
	NONE, NONE, NONE, NONE, NONE, NONE,
	NONE, NONE, NONE, NONE, NONE, NONE
};

static short const rdata_0029c718[NUMBER_OF_XBOX_RASTERIZER_VERTEX_TYPES*1]= // vertex shader 20
{20, 20, NONE, NONE, 18, 18, NONE, NONE, NONE, NONE, NONE, NONE};

static short const rdata_0029c730[NUMBER_OF_XBOX_RASTERIZER_VERTEX_TYPES*1]= // vertex shader 23
{23, 23, NONE, NONE, 14, 14, NONE, NONE, NONE, NONE, NONE, NONE};

static short const rdata_0029c748[NUMBER_OF_XBOX_RASTERIZER_VERTEX_TYPES*1]= // vertex shader 46
{46, 46, NONE, NONE, 30, 30, NONE, NONE, NONE, NONE, NONE, NONE};

static short const rdata_0029c760[NUMBER_OF_XBOX_RASTERIZER_VERTEX_TYPES*3]= // vertex shader 43
{
	28, 43, 61,
	28, 43, 61,
	NONE, NONE, NONE,
	NONE, NONE, NONE,
	63, 36, NONE,
	63, 36, NONE,
	NONE, NONE, NONE,
	NONE, NONE, NONE,
	NONE, NONE, NONE,
	NONE, NONE, NONE,
	NONE, NONE, NONE,
	NONE, NONE, NONE
};

static short const rdata_0029c7a8[NUMBER_OF_XBOX_RASTERIZER_VERTEX_TYPES*1]= // vertex shader 25
{25, 25, NONE, NONE, 50, 50, NONE, NONE, NONE, NONE, NONE, NONE};

static short const rdata_0029c7c0[NUMBER_OF_XBOX_RASTERIZER_VERTEX_TYPES*1]= // vertex shader 22
{22, 22, NONE, NONE, 32, 32, NONE, NONE, NONE, NONE, NONE, NONE};

static short const rdata_0029c7d8[NUMBER_OF_XBOX_RASTERIZER_VERTEX_TYPES*1]= // vertex shader 15
{NONE, NONE, NONE, NONE, 15, 15, NONE, NONE, NONE, NONE, NONE, NONE};

static short const rdata_0029c7f0[NUMBER_OF_XBOX_RASTERIZER_VERTEX_TYPES*2]= // vertex shader 33
{
	NONE, NONE,
	NONE, NONE,
	NONE, NONE,
	NONE, NONE,
	NONE, NONE,
	NONE, NONE,
	NONE, NONE,
	NONE, NONE,
	NONE, NONE,
	NONE, NONE,
	NONE, NONE,
	33, 11
};

static short data_0030d3b8= NONE; // current vertex shader index

static struct packed_vertex_shader data_0030d3bc[NUMBER_OF_PACKED_VERTEX_SHADERS]=
{
	{10, FALSE, 0},
	{9, FALSE, 0},
	{27, FALSE, 0}
};

/* ---------- public code */

// code matches; objdiff only disagrees on the switch jump table relocations ($L labels vs function-relative)
void rasterizer_set_vertex_shader_permutation(
	short vertex_shader_index,
	short vertex_type,
	short permutation_index)
{
	boolean success= TRUE;
	short const *translation_table= NULL;
	short permutation_count= 1;

	match_assert(RASTERIZER_XBOX_VERTEX_SHADERS_RUNTIME_FILE, 135, vertex_shader_index>=0 && vertex_shader_index<NUMBER_OF_VERTEX_SHADERS);

	switch (vertex_shader_index)
	{
	case 0:
		translation_table= rdata_0029c2f8;
		break;
	case 1:
		translation_table= rdata_0029c310;
		break;
	case 4:
		permutation_count= 2;
		translation_table= rdata_0029c328;
		break;
	case 38:
		translation_table= rdata_0029c358;
		break;
	case 65:
		translation_table= rdata_0029c370;
		permutation_count= 4;
		break;
	case 56:
		translation_table= rdata_0029c3d0;
		break;
	case 16:
		translation_table= rdata_0029c3e8;
		break;
	case 49:
		translation_table= rdata_0029c400;
		break;
	case 29:
		translation_table= rdata_0029c418;
		break;
	case 40:
		translation_table= rdata_0029c430;
		break;
	case 21:
		translation_table= rdata_0029c448;
		permutation_count= 3;
		break;
	case 58:
		translation_table= rdata_0029c490;
		break;
	case 42:
		translation_table= rdata_0029c4a8;
		permutation_count= 3;
		break;
	case 51:
		translation_table= rdata_0029c4f0;
		break;
	case 6:
		translation_table= rdata_0029c508;
		break;
	case 8:
		translation_table= rdata_0029c520;
		break;
	case 37:
		translation_table= rdata_0029c538;
		permutation_count= 6;
		break;
	case 10:
		translation_table= rdata_0029c5c8;
		permutation_count= 4;
		break;
	case 64:
		translation_table= rdata_0029c628;
		break;
	case 39:
		translation_table= rdata_0029c640;
		break;
	case 13:
		translation_table= rdata_0029c658;
		break;
	case 5:
		translation_table= rdata_0029c670;
		break;
	case 24:
		translation_table= rdata_0029c688;
		permutation_count= 6;
		break;
	case 20:
		translation_table= rdata_0029c718;
		break;
	case 23:
		translation_table= rdata_0029c730;
		break;
	case 46:
		translation_table= rdata_0029c748;
		break;
	case 43:
		translation_table= rdata_0029c760;
		permutation_count= 3;
		break;
	case 25:
		translation_table= rdata_0029c7a8;
		break;
	case 22:
		translation_table= rdata_0029c7c0;
		break;
	case 15:
		translation_table= rdata_0029c7d8;
		break;
	case 33:
		translation_table= rdata_0029c7f0;
		permutation_count= 2;
		break;
	default:
		match_vassert(RASTERIZER_XBOX_VERTEX_SHADERS_RUNTIME_FILE, 876, FALSE, "### ERROR unsupported vertex shader");
	}

	match_vassert(RASTERIZER_XBOX_VERTEX_SHADERS_RUNTIME_FILE, 879, vertex_type>=0 && vertex_type<NUMBER_OF_XBOX_RASTERIZER_VERTEX_TYPES, "vertex_type>=0 && vertex_type<NUMBER_OF_RASTERIZER_VERTEX_TYPES");
	match_assert(RASTERIZER_XBOX_VERTEX_SHADERS_RUNTIME_FILE, 880, permutation_index>=0 && permutation_index<permutation_count);
	match_assert(RASTERIZER_XBOX_VERTEX_SHADERS_RUNTIME_FILE, 881, translation_table[vertex_type*permutation_count + permutation_index]!=NONE);
	vertex_shader_index= translation_table[vertex_type*permutation_count + permutation_index];

	if (vertex_shader_index!=data_0030d3b8)
	{
		short packed_shader_index;

		if (!data_0030d3bc[1].offset)
		{
			long offset= 0;

			for (packed_shader_index= 0; packed_shader_index<NUMBER_OF_PACKED_VERTEX_SHADERS; packed_shader_index++)
			{
				UINT size;

				D3DCALL(success, IDirect3DDevice8_GetVertexShaderSize(global_d3d_device, vertex_shader_table[data_0030d3bc[packed_shader_index].vertex_shader_index].handle, &size));
				data_0030d3bc[packed_shader_index].offset= offset;
				offset+= size;
			}
			match_vassert(RASTERIZER_XBOX_VERTEX_SHADERS_RUNTIME_FILE, 930, offset<=MAXIMUM_PACKED_VERTEX_SHADER_SIZE, "### ERROR packed vertex shaders don't fit in GPU memory");
		}

		for (packed_shader_index= 0; packed_shader_index<NUMBER_OF_PACKED_VERTEX_SHADERS; packed_shader_index++)
		{
			if (vertex_shader_index==data_0030d3bc[packed_shader_index].vertex_shader_index)
			{
				break;
			}
		}

		if (packed_shader_index<NUMBER_OF_PACKED_VERTEX_SHADERS && data_0030d3bc[packed_shader_index].loaded)
		{
			UINT offset= data_0030d3bc[packed_shader_index].offset;

			D3DCALL(success, IDirect3DDevice8_SelectVertexShader(global_d3d_device, 0L, (UINT)offset));
		}
		else
		{
			if (packed_shader_index<NUMBER_OF_PACKED_VERTEX_SHADERS)
			{
				UINT offset= data_0030d3bc[packed_shader_index].offset;
				DWORD handle= vertex_shader_table[data_0030d3bc[packed_shader_index].vertex_shader_index].handle;

				match_vassert(RASTERIZER_XBOX_VERTEX_SHADERS_RUNTIME_FILE, 956, handle, "### ERROR vertex shader was not valid");
				D3DCALL(success, IDirect3DDevice8_LoadVertexShader(global_d3d_device, (DWORD)handle, (UINT)offset));
				D3DCALL(success, IDirect3DDevice8_SelectVertexShader(global_d3d_device, (DWORD)handle, (UINT)offset));
				data_0030d3bc[packed_shader_index].loaded= TRUE;
			}
			else
			{
				DWORD handle= vertex_shader_table[vertex_shader_index].handle;

				match_vassert(RASTERIZER_XBOX_VERTEX_SHADERS_RUNTIME_FILE, 969, handle, "### ERROR vertex shader was not valid");
				D3DCALL(success, IDirect3DDevice8_SetVertexShader(global_d3d_device, (DWORD)handle));
				for (packed_shader_index= 0; packed_shader_index<NUMBER_OF_PACKED_VERTEX_SHADERS; packed_shader_index++)
				{
					data_0030d3bc[packed_shader_index].loaded= FALSE;
				}
			}

			if (rasterizer_debug_options.statistics_mode)
			{
				rasterizer_frame_statistics.vertex_shader_total+= vertex_shader_table[vertex_shader_index].size;
			}
		}

		data_0030d3b8= vertex_shader_index;
		if (!success)
		{
			error(_error_silent, "### ERROR rasterizer_set_vertex_shader failed");
		}
	}
}

/* ---------- private code */
