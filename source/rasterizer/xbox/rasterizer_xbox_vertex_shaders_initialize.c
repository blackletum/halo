/*
RASTERIZER_XBOX_VERTEX_SHADERS_INITIALIZE.C

symbols in this file:
00168070 0020:
	_IDirect3DDevice8_CreateVertexShader@20 (0000)
00168090 0010:
	_IDirect3DDevice8_DeleteVertexShader@8 (0000)
001680A0 0260:
	_rasterizer_vertex_shaders_initialize (0000)
00168300 0050:
	_rasterizer_vertex_shaders_dispose (0000)
0029BF94 0010:
	_d3dve_debug (0000)
0029BFA4 0010:
	_d3dve_decal (0000)
0029BFB4 0014:
	_d3dve_detail_object (0000)
0029BFC8 0014:
	_d3dve_unlit (0000)
0029BFDC 001c:
	_d3dve_unlit_zsprite (0000)
0029BFF8 0014:
	_d3dve_screen (0000)
0029C00C 0024:
	_d3dve_model (0000)
0029C030 0028:
	_d3dve_environment_lightmap (0000)
0029C058 001c:
	_d3dve_environment (0000)
0029C074 0036:
	??_C@_0DG@DJPOAFHM@?$CD?$CD?$CD?5ERROR?5rasterizer_vertex_shad@ (0000)
0029C0B0 00e9:
	??_C@_0OJ@IGEKCPEI@IDirect3DDevice8_CreateVertexSha@ (0000)
0029C19C 002e:
	??_C@_0CO@JPPOFKGN@vertex_shader_table?$FLvertex_shade@ (0000)
0029C1CC 0035:
	??_C@_0DF@NLIMIMDJ@vertex_shader_table?$FLvertex_shade@ (0000)
0029C208 004b:
	??_C@_0EL@FLPDNHEI@c?3?2halo?2SOURCE?2rasterizer?2xbox?2r@ (0000)
0029C254 0033:
	??_C@_0DD@EOLJNOFA@?$CD?$CD?$CD?5ERROR?5rasterizer_vertex_shad@ (0000)
0029C288 006f:
	??_C@_0GP@DNJKFNGM@IDirect3DDevice8_DeleteVertexSha@ (0000)
*/

/* ---------- headers */

#include "cseries.h"
#include "cseries_windows.h"
#include "errors.h"
#include "real_math.h"
#include "rasterizer.h"
#include "xbox/rasterizer_xbox.h"

/* ---------- globals */

extern struct vertex_shader_table_entry vertex_shader_table[NUMBER_OF_VERTEX_SHADERS];

// vertex shader declarations (D3DVSD_* tokens); names from the hcex port (rasterizer_dx9_shaders_vdecl9.c d3dve_*)
static const DWORD d3dve_debug[4]=
{
	D3DVSD_STREAM(0),
	D3DVSD_REG(0, D3DVSDT_FLOAT3),
	D3DVSD_REG(9, D3DVSDT_D3DCOLOR),
	D3DVSD_END()
};

static const DWORD d3dve_decal[4]=
{
	D3DVSD_STREAM(0),
	D3DVSD_REG(0, D3DVSDT_FLOAT3),
	D3DVSD_REG(4, D3DVSDT_NORMSHORT2),
	D3DVSD_END()
};

static const DWORD d3dve_detail_object[5]=
{
	D3DVSD_STREAM(0),
	D3DVSD_REG(0, D3DVSDT_PBYTE3),
	D3DVSD_REG(9, D3DVSDT_PBYTE3),
	D3DVSD_REG(8, D3DVSDT_SHORT1),
	D3DVSD_END()
};

static const DWORD d3dve_unlit[5]=
{
	D3DVSD_STREAM(0),
	D3DVSD_REG(0, D3DVSDT_FLOAT3),
	D3DVSD_REG(4, D3DVSDT_FLOAT2),
	D3DVSD_REG(9, D3DVSDT_D3DCOLOR),
	D3DVSD_END()
};

static const DWORD d3dve_unlit_zsprite[7]=
{
	D3DVSD_STREAM(0),
	D3DVSD_REG(0, D3DVSDT_FLOAT3),
	D3DVSD_REG(4, D3DVSDT_FLOAT2),
	D3DVSD_REG(9, D3DVSDT_D3DCOLOR),
	D3DVSD_STREAM(1),
	D3DVSD_REG(11, D3DVSDT_PBYTE2),
	D3DVSD_END()
};

static const DWORD d3dve_screen[5]=
{
	D3DVSD_STREAM(0),
	D3DVSD_REG(0, D3DVSDT_FLOAT2),
	D3DVSD_REG(4, D3DVSDT_FLOAT2),
	D3DVSD_REG(9, D3DVSDT_D3DCOLOR),
	D3DVSD_END()
};

static const DWORD d3dve_model[9]=
{
	D3DVSD_STREAM(0),
	D3DVSD_REG(0, D3DVSDT_FLOAT3),
	D3DVSD_REG(1, D3DVSDT_NORMPACKED3),
	D3DVSD_REG(2, D3DVSDT_NORMPACKED3),
	D3DVSD_REG(3, D3DVSDT_NORMPACKED3),
	D3DVSD_REG(4, D3DVSDT_NORMSHORT2),
	D3DVSD_REG(5, D3DVSDT_PBYTE2),
	D3DVSD_REG(6, D3DVSDT_NORMSHORT1),
	D3DVSD_END()
};

static const DWORD d3dve_environment_lightmap[10]=
{
	D3DVSD_STREAM(0),
	D3DVSD_REG(0, D3DVSDT_FLOAT3),
	D3DVSD_REG(1, D3DVSDT_NORMPACKED3),
	D3DVSD_REG(2, D3DVSDT_NORMPACKED3),
	D3DVSD_REG(3, D3DVSDT_NORMPACKED3),
	D3DVSD_REG(4, D3DVSDT_FLOAT2),
	D3DVSD_STREAM(1),
	D3DVSD_REG(7, D3DVSDT_NORMPACKED3),
	D3DVSD_REG(8, D3DVSDT_NORMSHORT2),
	D3DVSD_END()
};

static const DWORD d3dve_environment[7]=
{
	D3DVSD_STREAM(0),
	D3DVSD_REG(0, D3DVSDT_FLOAT3),
	D3DVSD_REG(1, D3DVSDT_NORMPACKED3),
	D3DVSD_REG(2, D3DVSDT_NORMPACKED3),
	D3DVSD_REG(3, D3DVSDT_NORMPACKED3),
	D3DVSD_REG(4, D3DVSDT_FLOAT2),
	D3DVSD_END()
};

/* ---------- public code */

boolean rasterizer_vertex_shaders_initialize(
	void)
{
	boolean success= TRUE;
	short vertex_shader_index;

	for (vertex_shader_index= 0; vertex_shader_index<NUMBER_OF_VERTEX_SHADERS; vertex_shader_index++)
	{
		vertex_shader_table[vertex_shader_index].declaration= NULL;
	}

	vertex_shader_table[4].declaration= d3dve_screen;
	vertex_shader_table[3].declaration= d3dve_screen;
	vertex_shader_table[38].declaration= d3dve_screen;
	vertex_shader_table[65].declaration= d3dve_unlit;
	vertex_shader_table[2].declaration= d3dve_unlit;
	vertex_shader_table[12].declaration= d3dve_unlit;
	vertex_shader_table[56].declaration= d3dve_unlit;
	vertex_shader_table[0].declaration= d3dve_debug;
	vertex_shader_table[1].declaration= d3dve_decal;
	vertex_shader_table[66].declaration= d3dve_unlit_zsprite;
	vertex_shader_table[16].declaration= d3dve_environment_lightmap;
	vertex_shader_table[49].declaration= d3dve_environment;
	vertex_shader_table[29].declaration= d3dve_environment;
	vertex_shader_table[40].declaration= d3dve_environment;
	vertex_shader_table[21].declaration= d3dve_environment;
	vertex_shader_table[41].declaration= d3dve_environment;
	vertex_shader_table[59].declaration= d3dve_environment_lightmap;
	vertex_shader_table[58].declaration= d3dve_environment_lightmap;
	vertex_shader_table[26].declaration= d3dve_environment;
	vertex_shader_table[42].declaration= d3dve_environment;
	vertex_shader_table[44].declaration= d3dve_environment_lightmap;
	vertex_shader_table[51].declaration= d3dve_environment;
	vertex_shader_table[6].declaration= d3dve_environment;
	vertex_shader_table[8].declaration= d3dve_environment;
	vertex_shader_table[10].declaration= d3dve_model;
	vertex_shader_table[9].declaration= d3dve_model;
	vertex_shader_table[27].declaration= d3dve_model;
	vertex_shader_table[17].declaration= d3dve_model;
	vertex_shader_table[64].declaration= d3dve_model;
	vertex_shader_table[39].declaration= d3dve_model;
	vertex_shader_table[13].declaration= d3dve_model;
	vertex_shader_table[33].declaration= d3dve_detail_object;
	vertex_shader_table[11].declaration= d3dve_detail_object;
	vertex_shader_table[5].declaration= d3dve_model;
	vertex_shader_table[24].declaration= d3dve_environment;
	vertex_shader_table[48].declaration= d3dve_environment;
	vertex_shader_table[34].declaration= d3dve_environment;
	vertex_shader_table[19].declaration= d3dve_environment;
	vertex_shader_table[35].declaration= d3dve_environment;
	vertex_shader_table[47].declaration= d3dve_model;
	vertex_shader_table[31].declaration= d3dve_model;
	vertex_shader_table[60].declaration= d3dve_model;
	vertex_shader_table[57].declaration= d3dve_model;
	vertex_shader_table[45].declaration= d3dve_model;
	vertex_shader_table[62].declaration= d3dve_model;
	vertex_shader_table[46].declaration= d3dve_environment;
	vertex_shader_table[28].declaration= d3dve_environment;
	vertex_shader_table[43].declaration= d3dve_environment;
	vertex_shader_table[61].declaration= d3dve_environment;
	vertex_shader_table[25].declaration= d3dve_environment_lightmap;
	vertex_shader_table[30].declaration= d3dve_model;
	vertex_shader_table[63].declaration= d3dve_model;
	vertex_shader_table[36].declaration= d3dve_model;
	vertex_shader_table[50].declaration= d3dve_model;
	vertex_shader_table[20].declaration= d3dve_environment;
	vertex_shader_table[23].declaration= d3dve_environment;
	vertex_shader_table[18].declaration= d3dve_model;
	vertex_shader_table[14].declaration= d3dve_model;
	vertex_shader_table[22].declaration= d3dve_environment;
	vertex_shader_table[32].declaration= d3dve_model;
	vertex_shader_table[15].declaration= d3dve_model;
	vertex_shader_table[37].declaration= d3dve_environment;
	vertex_shader_table[7].declaration= d3dve_environment;
	vertex_shader_table[54].declaration= d3dve_environment;
	vertex_shader_table[55].declaration= d3dve_environment;
	vertex_shader_table[53].declaration= d3dve_environment;
	vertex_shader_table[52].declaration= d3dve_environment;

	for (vertex_shader_index= 0; vertex_shader_index<NUMBER_OF_VERTEX_SHADERS; vertex_shader_index++)
	{
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_vertex_shaders_initialize.c", 242, vertex_shader_table[vertex_shader_index].declaration);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_vertex_shaders_initialize.c", 243, vertex_shader_table[vertex_shader_index].code);

		D3DCALL(success, IDirect3DDevice8_CreateVertexShader(global_d3d_device, (DWORD*)vertex_shader_table[vertex_shader_index].declaration, (DWORD*)vertex_shader_table[vertex_shader_index].code, (DWORD*)&vertex_shader_table[vertex_shader_index].handle, 0));
	}

	if (!success)
	{
		error(_error_silent, "### ERROR rasterizer_vertex_shaders_initialize failed");
	}

	return success;
}

void rasterizer_vertex_shaders_dispose(
	void)
{
	boolean success= TRUE;
	short vertex_shader_index;

	for (vertex_shader_index= 0; vertex_shader_index<NUMBER_OF_VERTEX_SHADERS; vertex_shader_index++)
	{
		D3DCALL(success, IDirect3DDevice8_DeleteVertexShader(global_d3d_device, (DWORD)vertex_shader_table[vertex_shader_index].handle));
	}

	if (!success)
	{
		error(_error_silent, "### ERROR rasterizer_vertex_shaders_dispose failed");
	}
}
