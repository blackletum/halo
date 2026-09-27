/*
RASTERIZER_XBOX_DEBUG.C

symbols in this file:
00149930 01b0:
	_D3DDevice_SetRenderState (0000)
00149AE0 0010:
	_rasterizer_debug_drawing_end (0000)
00149AF0 0220:
	_IDirect3DDevice8_SetRenderState@12 (0000)
00149D10 0010:
	__rasterizer_debug_immediate_end (0000)
00149D20 0010:
	_IDirect3DDevice8_SetVertexShaderConstant@16 (0000)
00149D30 0010:
	__rasterizer_debug_immediate_end_screenspace (0000)
00149D40 0030:
	_IDirect3DDevice8_SetVertexData4f@24 (0000)
00149D70 0010:
	_IDirect3DDevice8_SetVertexData2s@16 (0000)
00149D80 0010:
	_IDirect3DDevice8_SetVertexDataColor@12 (0000)
00149D90 0010:
	_IDirect3DDevice8_Begin@8 (0000)
00149DA0 0010:
	_IDirect3DDevice8_End@4 (0000)
00149DB0 01a0:
	_rasterizer_debug_drawing_begin (0000)
00149F50 00f0:
	__rasterizer_debug_immediate_begin (0000)
0014A040 0100:
	__rasterizer_debug_immediate_line (0000)
0014A140 0150:
	__rasterizer_debug_immediate_triangle (0000)
0014A290 01a0:
	__rasterizer_debug_immediate_begin_screenspace (0000)
0014A430 00e0:
	__rasterizer_debug_immediate_line_screenspace (0000)
0014A510 00e0:
	__rasterizer_debug_immediate_linestrip_screenspace (0000)
0028DBF0 0037:
	??_C@_0DH@DIBILDIH@c?3?2halo?2SOURCE?2rasterizer?2xbox?2r@ (0000)
0028DC28 0013:
	??_C@_0BD@COPILOKK@p0?5?$CG?$CG?5p1?5?$CG?$CG?5color0?$AA@ (0000)
0028DC3C 0019:
	??_C@_0BJ@NENINKJJ@p0?5?$CG?$CG?5p1?5?$CG?$CG?5p2?5?$CG?$CG?5color0?$AA@ (0000)
0028DC58 0028:
	??_C@_0CI@JKACMLIP@IDirect3DDevice8_End?$CIglobal_d3d_@ (0000)
0028DC80 006f:
	??_C@_0GP@HCEKPJMM@IDirect3DDevice8_SetVertexData2s@ (0000)
0028DCF0 0021:
	??_C@_0CB@FKKHNBEF@points?5?$CG?$CG?5color?5?$CG?$CG?5point_count?$DO1@ (0000)

notes:
	_code_00149930, _code_00149af0, _code_00149d20 .. _code_00149da0 are the
	out-of-line copies of the d3d8.h D3DINLINE wrappers the compiler emits for
	this unit (D3DDevice_SetRenderState, IDirect3DDevice8_SetRenderState,
	_SetVertexShaderConstant, _SetVertexData4f, _SetVertexData2s,
	_SetVertexDataColor, _Begin, _End); they are not written by hand.
*/

/* ---------- headers */

#include "cseries.h"
#include "cseries_windows.h"
#include "errors.h"
#include "real_math.h"
#include "render.h"
#include "rasterizer.h"
#include "xbox/rasterizer_xbox.h"

/* ---------- constants */

#define VSDE_VERTEX 0
#define VSDE_DIFFUSE 9

/* ---------- macros */

/* ---------- structures */

/* ---------- prototypes */

void rasterizer_set_vertex_shader_permutation(short vertex_shader, short vertex_type, short permutation);
void rasterizer_set_pixel_shader(D3DPIXELSHADERDEF *pixel_shader);
unsigned long real_rgb_color_to_pixel32(real_rgb_color const *color);

/* ---------- globals */

extern struct rasterizer_window_begin_parameters global_window_parameters;
extern D3DPIXELSHADERDEF pixel_shader;

/* ---------- public code */

void rasterizer_debug_drawing_begin(
	boolean opaque)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_debug.c", 19, global_d3d_device);

	if (rasterizer_debug_options.draw_debug_geometry)
	{
		rasterizer_set_vertex_shader_permutation(0, 9, 0);

		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_NONE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZENABLE, D3DZB_TRUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZBIAS, rasterizer_debug_options.zbias);

		csmemset(&pixel_shader, 0, sizeof(pixel_shader));
		pixel_shader.PSTextureModes= 0;
		pixel_shader.PSCombinerCount= 1;
		pixel_shader.PSFinalCombinerInputsABCD= 4;

		if (opaque)
		{
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHABLENDENABLE, FALSE);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHATESTENABLE, FALSE);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZWRITEENABLE, TRUE);
		}
		else
		{
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHABLENDENABLE, TRUE);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHATESTENABLE, FALSE);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_BLENDOP, D3DBLENDOP_ADD);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZWRITEENABLE, FALSE);
			pixel_shader.PSFinalCombinerInputsEFG= 0x1400;
		}

		rasterizer_set_pixel_shader(&pixel_shader);
	}
}

void rasterizer_debug_drawing_end(
	void)
{
}

void _rasterizer_debug_immediate_begin(
	void)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_debug.c", 81, global_d3d_device);

	IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_NONE);
	IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHABLENDENABLE, FALSE);
	IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHATESTENABLE, FALSE);
	IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZENABLE, D3DZB_TRUE);
	IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZWRITEENABLE, TRUE);
	IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZBIAS, rasterizer_debug_options.zbias);

	rasterizer_set_vertex_shader_permutation(0, 9, 0);

	csmemset(&pixel_shader, 0, sizeof(pixel_shader));
	pixel_shader.PSTextureModes= 0;
	pixel_shader.PSCombinerCount= 1;
	pixel_shader.PSFinalCombinerInputsABCD= 4;
	rasterizer_set_pixel_shader(&pixel_shader);
}

void _rasterizer_debug_immediate_line(
	real_point3d const *p0,
	real_point3d const *p1,
	real_rgb_color const *color0,
	real_rgb_color const *color1)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_debug.c", 116, p0 && p1 && color0);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_debug.c", 117, global_d3d_device);

	IDirect3DDevice8_Begin(global_d3d_device, D3DPT_LINELIST);
	IDirect3DDevice8_SetVertexData4f(global_d3d_device, VSDE_DIFFUSE, color0->red, color0->green, color0->blue, 1.0f);
	IDirect3DDevice8_SetVertexData4f(global_d3d_device, VSDE_VERTEX, p0->x, p0->y, p0->z, 1.0f);
	if (color1)
	{
		IDirect3DDevice8_SetVertexData4f(global_d3d_device, VSDE_DIFFUSE, color1->red, color1->green, color1->blue, 1.0f);
	}
	IDirect3DDevice8_SetVertexData4f(global_d3d_device, VSDE_VERTEX, p1->x, p1->y, p1->z, 1.0f);
	IDirect3DDevice8_End(global_d3d_device);
}

void _rasterizer_debug_immediate_triangle(
	real_point3d const *p0,
	real_point3d const *p1,
	real_point3d const *p2,
	real_rgb_color const *color0,
	real_rgb_color const *color1,
	real_rgb_color const *color2)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_debug.c", 139, p0 && p1 && p2 && color0);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_debug.c", 140, global_d3d_device);

	IDirect3DDevice8_Begin(global_d3d_device, D3DPT_TRIANGLELIST);
	IDirect3DDevice8_SetVertexData4f(global_d3d_device, VSDE_DIFFUSE, color0->red, color0->green, color0->blue, 1.0f);
	IDirect3DDevice8_SetVertexData4f(global_d3d_device, VSDE_VERTEX, p0->x, p0->y, p0->z, 1.0f);
	if (color1)
	{
		IDirect3DDevice8_SetVertexData4f(global_d3d_device, VSDE_DIFFUSE, color1->red, color1->green, color1->blue, 1.0f);
	}
	IDirect3DDevice8_SetVertexData4f(global_d3d_device, VSDE_VERTEX, p1->x, p1->y, p1->z, 1.0f);
	if (color2)
	{
		IDirect3DDevice8_SetVertexData4f(global_d3d_device, VSDE_DIFFUSE, color2->red, color2->green, color2->blue, 1.0f);
	}
	IDirect3DDevice8_SetVertexData4f(global_d3d_device, VSDE_VERTEX, p2->x, p2->y, p2->z, 1.0f);
	IDirect3DDevice8_End(global_d3d_device);
}

void _rasterizer_debug_immediate_end(
	void)
{
}

// TODO: viewport height is loaded bottom-then-top into edx/ecx instead of top-then-bottom
void _rasterizer_debug_immediate_begin_screenspace(
	void)
{
	real one_over_width;
	real one_over_height;
	real constants[5][4];

	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_debug.c", 167, global_d3d_device);

	IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_NONE);
	IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHABLENDENABLE, FALSE);
	IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHATESTENABLE, FALSE);
	IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZENABLE, D3DZB_FALSE);
	IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZBIAS, 0);

	rasterizer_set_vertex_shader_permutation(4, 8, 0);

	one_over_width= 1.0f/(short)(global_window_parameters.camera.viewport_bounds.x1 - global_window_parameters.camera.viewport_bounds.x0);
	constants[0][0]= one_over_width + one_over_width;
	constants[0][1]= 0.0f;
	constants[0][2]= 0.0f;
	constants[0][3]= -1.0f - one_over_width;
	one_over_height= 1.0f/(short)(global_window_parameters.camera.viewport_bounds.y1 - global_window_parameters.camera.viewport_bounds.y0);
	constants[1][0]= 0.0f;
	constants[1][1]= -2.0f*one_over_height;
	constants[1][2]= 0.0f;
	constants[1][3]= one_over_height + 1.0f;
	constants[2][0]= 0.0f;
	constants[2][1]= 0.0f;
	constants[2][2]= 0.0f;
	constants[2][3]= 0.5f;
	constants[3][0]= 0.0f;
	constants[3][1]= 0.0f;
	constants[3][2]= 0.0f;
	constants[3][3]= 1.0f;
	constants[4][0]= 1.0f;
	constants[4][1]= 1.0f;
	constants[4][2]= 0.0f;
	constants[4][3]= 1.0f;
	IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, VSH_CONSTANTS__SCREENPROJ_OFFSET, constants, VSH_CONSTANTS__SCREENPROJ_COUNT);

	csmemset(&pixel_shader, 0, sizeof(pixel_shader));
	pixel_shader.PSTextureModes= 0;
	pixel_shader.PSCombinerCount= 1;
	pixel_shader.PSFinalCombinerInputsABCD= 4;
	rasterizer_set_pixel_shader(&pixel_shader);
}

void _rasterizer_debug_immediate_line_screenspace(
	point2d const *p0,
	point2d const *p1,
	real_rgb_color const *color0,
	real_rgb_color const *color1)
{
	unsigned long pixel_color0;
	unsigned long pixel_color1;

	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_debug.c", 221, p0 && p1 && color0);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_debug.c", 222, global_d3d_device);

	pixel_color0= real_rgb_color_to_pixel32(color0);
	if (color1)
	{
		pixel_color1= real_rgb_color_to_pixel32(color1);
	}

	IDirect3DDevice8_Begin(global_d3d_device, D3DPT_LINESTRIP);
	IDirect3DDevice8_SetVertexDataColor(global_d3d_device, VSDE_DIFFUSE, pixel_color0);
	IDirect3DDevice8_SetVertexData2s(global_d3d_device, VSDE_VERTEX, p0->x, p0->y);
	if (color1)
	{
		IDirect3DDevice8_SetVertexDataColor(global_d3d_device, VSDE_DIFFUSE, pixel_color1);
	}
	IDirect3DDevice8_SetVertexData2s(global_d3d_device, VSDE_VERTEX, p1->x, p1->y);
	IDirect3DDevice8_End(global_d3d_device);
}

void _rasterizer_debug_immediate_linestrip_screenspace(
	point2d const *points,
	short point_count,
	real_rgb_color const *color)
{
	boolean success;
	unsigned long pixel_color;
	short point_index;

	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_debug.c", 249, points && color && point_count>1);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_debug.c", 250, global_d3d_device);

	pixel_color= real_rgb_color_to_pixel32(color);

	IDirect3DDevice8_Begin(global_d3d_device, D3DPT_LINESTRIP);
	IDirect3DDevice8_SetVertexDataColor(global_d3d_device, VSDE_DIFFUSE, pixel_color);
	success= TRUE;
	for (point_index= 0; point_index<point_count; point_index++)
	{
		D3DCALL(success, IDirect3DDevice8_SetVertexData2s(global_d3d_device, VSDE_VERTEX, points[point_index].x, points[point_index].y));
	}
	D3DCALL(success, IDirect3DDevice8_End(global_d3d_device));
}

void _rasterizer_debug_immediate_end_screenspace(
	void)
{
}

/* ---------- private code */
