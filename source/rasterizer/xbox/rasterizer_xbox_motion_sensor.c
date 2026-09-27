/*
RASTERIZER_XBOX_MOTION_SENSOR.C

symbols in this file:
0015D220 01b0:
	_D3DDevice_SetRenderState (0000)
0015D3D0 0050:
	_D3DDevice_SetTextureStageState (0000)
0015D420 0220:
	_IDirect3DDevice8_SetRenderState@12 (0000)
0015D640 0060:
	_IDirect3DDevice8_SetTextureStageState@16 (0000)
0015D6A0 0010:
	_IDirect3DDevice8_SetVertexShaderConstant@16 (0000)
0015D6B0 0020:
	_IDirect3DDevice8_SetVertexData2f@16 (0000)
0015D6D0 0030:
	_IDirect3DDevice8_SetVertexData4f@24 (0000)
0015D700 0010:
	_IDirect3DDevice8_SetVertexData2s@16 (0000)
0015D710 0010:
	_IDirect3DDevice8_Begin@8 (0000)
0015D720 0010:
	_IDirect3DDevice8_End@4 (0000)
0015D730 0280:
	__rasterizer_hud_motion_sensor_blip_begin (0000)
0015D9B0 0180:
	__rasterizer_hud_motion_sensor_blip_draw (0000)
0015DB30 0780:
	__rasterizer_hud_motion_sensor_blip_end (0000)
00291ECC 003f:
	??_C@_0DP@DPMIHOMG@c?3?2halo?2SOURCE?2rasterizer?2xbox?2r@ (0000)
00291F0C 0004:
	__real@bd000000 (0000)
00465E27 0001:
	_rasterizer_motion_sensor_begin_said_to_draw (0000)
*/

/* ---------- headers */

#include "cseries.h"
#include "cseries_windows.h"
#include "real_math.h"
#include "bitmaps.h"
#include "rasterizer.h"
#include "xbox/rasterizer_xbox.h"
#include "interface.h"
#include "players.h"

/* ---------- constants */

enum
{
	_interface_tag_motion_sensor_background = 7,
	_interface_tag_motion_sensor_foreground = 8,
	_interface_tag_motion_sensor_blip = 12,
	_interface_tag_motion_sensor_custom_blip = 13,
};

/* ---------- macros */

/* ---------- structures */

/* ---------- prototypes */

struct bitmap_data *bitmap_group_try_and_get_bitmap(long bitmap_group_index, short bitmap_index);
void *_texture_cache_bitmap_get_hardware_format(struct bitmap_data *bitmap, boolean block, boolean load);

void rasterizer_set_target(short target, short mipmap_index, unsigned long background_color, boolean clear, boolean zbuffer);
void *rasterizer_set_target_as_texture(short stage, short target, short max_mipmap);
boolean rasterizer_set_texture_bitmap_data(short stage, struct bitmap_data *bitmap);
void rasterizer_set_vertex_shader_permutation(long vertex_shader, long permutation, short type);
void rasterizer_set_pixel_shader(D3DPIXELSHADERDEF *pixel_shader_definition);
void SetRenderStateSmart(D3DRENDERSTATETYPE state, unsigned long value);

/* ---------- globals */

extern struct rasterizer_window_begin_parameters global_window_parameters;
extern D3DPIXELSHADERDEF pixel_shader;

static boolean rasterizer_motion_sensor_begin_said_to_draw; // rasterizer_motion_sensor_begin_said_to_draw

/* ---------- public code */

void _rasterizer_hud_motion_sensor_blip_begin(
	void)
{
	struct bitmap_data *blip_bitmap = bitmap_group_try_and_get_bitmap(interface_get_tag_index(_interface_tag_motion_sensor_blip), 0);
	struct bitmap_data *custom_blip_bitmap = bitmap_group_try_and_get_bitmap(interface_get_tag_index(_interface_tag_motion_sensor_custom_blip), 0);

	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_motion_sensor.c", 27, global_d3d_device);

	rasterizer_motion_sensor_begin_said_to_draw = FALSE;
	if (rasterizer_debug_options.draw_hud_motion_sensor &&
		_texture_cache_bitmap_get_hardware_format(blip_bitmap, FALSE, TRUE) &&
		_texture_cache_bitmap_get_hardware_format(custom_blip_bitmap, FALSE, TRUE))
	{
		float vsh_constants[5][4];

		rasterizer_motion_sensor_begin_said_to_draw = TRUE;
		rasterizer_set_target(_rasterizer_target_sun_glow_primary, 0, 0, TRUE, FALSE);
		rasterizer_set_texture_bitmap_data(0, blip_bitmap);

		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSU, D3DTADDRESS_BORDER);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSV, D3DTADDRESS_BORDER);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MIPFILTER, D3DTEXF_POINT);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_CCW);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_BLUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHABLENDENABLE, TRUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_SRCBLEND, D3DBLEND_ONE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_DESTBLEND, D3DBLEND_ONE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_BLENDOP, D3DBLENDOP_ADD);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHATESTENABLE, FALSE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZENABLE, D3DZB_FALSE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZBIAS, 0);

		rasterizer_set_vertex_shader_permutation(4, 8, 0);

		vsh_constants[0][0] = 1.f;
		vsh_constants[0][1] = 0.f;
		vsh_constants[0][2] = 0.f;
		vsh_constants[0][3] = 0.f;
		vsh_constants[1][0] = 0.f;
		vsh_constants[1][1] = 1.f;
		vsh_constants[1][2] = 0.f;
		vsh_constants[1][3] = 0.f;
		vsh_constants[2][0] = 0.f;
		vsh_constants[2][1] = 0.f;
		vsh_constants[2][2] = 1.f;
		vsh_constants[2][3] = 0.f;
		vsh_constants[3][0] = 0.f;
		vsh_constants[3][1] = 0.f;
		vsh_constants[3][2] = 0.f;
		vsh_constants[3][3] = 1.f;
		vsh_constants[4][0] = 1.f;
		vsh_constants[4][1] = 1.f;
		vsh_constants[4][2] = 0.f;
		vsh_constants[4][3] = 1.f;
		IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, VSH_CONSTANTS__SCREENPROJ_OFFSET, vsh_constants, VSH_CONSTANTS__SCREENPROJ_COUNT);

		csmemset(&pixel_shader, 0, sizeof(pixel_shader));
		pixel_shader.PSTextureModes = 1;
		pixel_shader.PSCombinerCount = 1;
		pixel_shader.PSFinalCombinerInputsABCD = 0x08040000;
		rasterizer_set_pixel_shader(&pixel_shader);
	}
}

void _rasterizer_hud_motion_sensor_blip_draw(
	real_point2d const *blip_position,
	real fade,
	real radius,
	real_rgb_color const *blip_color,
	boolean custom)
{
	struct bitmap_data *blip_bitmap = bitmap_group_try_and_get_bitmap(interface_get_tag_index(_interface_tag_motion_sensor_blip), 0);
	struct bitmap_data *custom_blip_bitmap = bitmap_group_try_and_get_bitmap(interface_get_tag_index(_interface_tag_motion_sensor_custom_blip), 0);

	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_motion_sensor.c", 109, global_d3d_device);

	rasterizer_set_texture_bitmap_data(0, custom ? custom_blip_bitmap : blip_bitmap);

	if (rasterizer_debug_options.draw_hud_motion_sensor && rasterizer_motion_sensor_begin_said_to_draw)
	{
		real size = radius * 0.0625f;
		real_point2d point;

		point.x = blip_position->x * -0.03125f;
		point.y = blip_position->y * -0.03125f;

		IDirect3DDevice8_Begin(global_d3d_device, D3DPT_TRIANGLEFAN);
		IDirect3DDevice8_SetVertexData4f(global_d3d_device, D3DVSDE_TEXCOORD0, fade * blip_color->red, fade * blip_color->green, fade * blip_color->blue, 1.f);
		IDirect3DDevice8_SetVertexData2s(global_d3d_device, D3DVSDE_SPECULAR, 0, 0);
		IDirect3DDevice8_SetVertexData2f(global_d3d_device, D3DVSDE_POSITION, point.x - size, point.y + size);
		IDirect3DDevice8_SetVertexData2s(global_d3d_device, D3DVSDE_SPECULAR, 1, 0);
		IDirect3DDevice8_SetVertexData2f(global_d3d_device, D3DVSDE_POSITION, point.x + size, point.y + size);
		IDirect3DDevice8_SetVertexData2s(global_d3d_device, D3DVSDE_SPECULAR, 1, 1);
		IDirect3DDevice8_SetVertexData2f(global_d3d_device, D3DVSDE_POSITION, point.x + size, point.y - size);
		IDirect3DDevice8_SetVertexData2s(global_d3d_device, D3DVSDE_SPECULAR, 0, 1);
		IDirect3DDevice8_SetVertexData2f(global_d3d_device, D3DVSDE_POSITION, point.x - size, point.y - size);
		IDirect3DDevice8_End(global_d3d_device);
	}
}

// TODO: register allocation differs in the viewport width/height computation and the else branch's rasterizer_set_target call
void _rasterizer_hud_motion_sensor_blip_end(
	real_point2d const *center_point,
	real theta)
{
	struct bitmap_data *background_bitmap = bitmap_group_try_and_get_bitmap(interface_get_tag_index(_interface_tag_motion_sensor_background), 0);
	struct bitmap_data *foreground_bitmap = bitmap_group_try_and_get_bitmap(interface_get_tag_index(_interface_tag_motion_sensor_foreground), 0);

	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_motion_sensor.c", 156, global_d3d_device);

	if (rasterizer_debug_options.draw_hud_motion_sensor && rasterizer_motion_sensor_begin_said_to_draw &&
		_texture_cache_bitmap_get_hardware_format(background_bitmap, FALSE, TRUE) &&
		_texture_cache_bitmap_get_hardware_format(foreground_bitmap, FALSE, TRUE))
	{
		float vsh_constants[5][4];
		real u0, u1;
		real size;
		short width, height;
		real one_over_width, one_over_height;

		rasterizer_set_texture_bitmap_data(0, background_bitmap);

		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSU, D3DTADDRESS_BORDER);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSV, D3DTADDRESS_BORDER);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_BORDERCOLOR, 0x46000000);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MIPFILTER, D3DTEXF_POINT);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_CCW);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_BLUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHABLENDENABLE, TRUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_SRCBLEND, D3DBLEND_ONE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_DESTBLEND, D3DBLEND_SRCALPHA);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_BLENDOP, D3DBLENDOP_ADD);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHATESTENABLE, FALSE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZENABLE, D3DZB_FALSE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZBIAS, 0);

		rasterizer_set_vertex_shader_permutation(4, 8, 0);

		vsh_constants[0][0] = 1.f;
		vsh_constants[0][1] = 0.f;
		vsh_constants[0][2] = 0.f;
		vsh_constants[0][3] = 0.f;
		vsh_constants[1][0] = 0.f;
		vsh_constants[1][1] = 1.f;
		vsh_constants[1][2] = 0.f;
		vsh_constants[1][3] = 0.f;
		vsh_constants[2][0] = 0.f;
		vsh_constants[2][1] = 0.f;
		vsh_constants[2][2] = 1.f;
		vsh_constants[2][3] = 0.f;
		vsh_constants[3][0] = 0.f;
		vsh_constants[3][1] = 0.f;
		vsh_constants[3][2] = 0.f;
		vsh_constants[3][3] = 1.f;
		vsh_constants[4][0] = 1.f;
		vsh_constants[4][1] = 1.f;
		vsh_constants[4][2] = 0.f;
		vsh_constants[4][3] = 1.f;
		IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, VSH_CONSTANTS__SCREENPROJ_OFFSET, vsh_constants, VSH_CONSTANTS__SCREENPROJ_COUNT);

		csmemset(&pixel_shader, 0, sizeof(pixel_shader));
		pixel_shader.PSTextureModes = 1;
		pixel_shader.PSCombinerCount = 1;
		pixel_shader.PSRGBInputs[0] = 0x08040000;
		pixel_shader.PSRGBOutputs[0] = 0xC0;
		pixel_shader.PSAlphaInputs[0] = 0x18140000;
		pixel_shader.PSAlphaOutputs[0] = 0xC0;
		pixel_shader.PSFinalCombinerInputsABCD = 0x0C;
		pixel_shader.PSFinalCombinerInputsEFG = 0x1C00;
		rasterizer_set_pixel_shader(&pixel_shader);

		IDirect3DDevice8_Begin(global_d3d_device, D3DPT_TRIANGLEFAN);
		IDirect3DDevice8_SetVertexData4f(global_d3d_device, D3DVSDE_TEXCOORD0, 0.4588f, 0.7294f, 1.f, 1.f);
		u0 = 0.5f - theta * 0.5f;
		u1 = 0.5f + theta * 0.5f;
		IDirect3DDevice8_SetVertexData2f(global_d3d_device, D3DVSDE_SPECULAR, u1, u0);
		IDirect3DDevice8_SetVertexData2f(global_d3d_device, D3DVSDE_POSITION, -1.015625f, 1.046875f);
		IDirect3DDevice8_SetVertexData2f(global_d3d_device, D3DVSDE_SPECULAR, u0, u0);
		IDirect3DDevice8_SetVertexData2f(global_d3d_device, D3DVSDE_POSITION, 1.046875f, 1.046875f);
		IDirect3DDevice8_SetVertexData2f(global_d3d_device, D3DVSDE_SPECULAR, u0, u1);
		IDirect3DDevice8_SetVertexData2f(global_d3d_device, D3DVSDE_POSITION, 1.046875f, -1.015625f);
		IDirect3DDevice8_SetVertexData2f(global_d3d_device, D3DVSDE_SPECULAR, u1, u1);
		IDirect3DDevice8_SetVertexData2f(global_d3d_device, D3DVSDE_POSITION, -1.015625f, -1.015625f);
		IDirect3DDevice8_End(global_d3d_device);

		rasterizer_set_texture_bitmap_data(0, foreground_bitmap);

		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHABLENDENABLE, TRUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_SRCBLEND, D3DBLEND_ZERO);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_DESTBLEND, D3DBLEND_SRCALPHA);

		csmemset(&pixel_shader, 0, sizeof(pixel_shader));
		pixel_shader.PSTextureModes = 1;
		pixel_shader.PSCombinerCount = 1;
		pixel_shader.PSFinalCombinerInputsABCD = 0x08;
		pixel_shader.PSFinalCombinerInputsEFG = 0x1800;
		rasterizer_set_pixel_shader(&pixel_shader);

		IDirect3DDevice8_Begin(global_d3d_device, D3DPT_TRIANGLEFAN);
		IDirect3DDevice8_SetVertexData4f(global_d3d_device, D3DVSDE_TEXCOORD0, 0.4f, 0.8f, 0.4f, 1.f);
		IDirect3DDevice8_SetVertexData2f(global_d3d_device, D3DVSDE_SPECULAR, 1.f, 0.f);
		IDirect3DDevice8_SetVertexData2f(global_d3d_device, D3DVSDE_POSITION, -1.015625f, 1.046875f);
		IDirect3DDevice8_SetVertexData2f(global_d3d_device, D3DVSDE_SPECULAR, 0.f, 0.f);
		IDirect3DDevice8_SetVertexData2f(global_d3d_device, D3DVSDE_POSITION, 1.046875f, 1.046875f);
		IDirect3DDevice8_SetVertexData2f(global_d3d_device, D3DVSDE_SPECULAR, 0.f, 1.f);
		IDirect3DDevice8_SetVertexData2f(global_d3d_device, D3DVSDE_POSITION, 1.046875f, -1.015625f);
		IDirect3DDevice8_SetVertexData2f(global_d3d_device, D3DVSDE_SPECULAR, 1.f, 1.f);
		IDirect3DDevice8_SetVertexData2f(global_d3d_device, D3DVSDE_POSITION, -1.015625f, -1.015625f);
		IDirect3DDevice8_End(global_d3d_device);

		rasterizer_set_target(global_window_parameters.rasterizer_target, 0, 0, FALSE, TRUE);
		rasterizer_set_target_as_texture(0, _rasterizer_target_sun_glow_primary, 0);

		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MIPFILTER, D3DTEXF_POINT);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_BORDERCOLOR, 0);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_CCW);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_BLUE);
		SetRenderStateSmart(D3DRS_ALPHABLENDENABLE, TRUE);
		SetRenderStateSmart(D3DRS_SRCBLEND, D3DBLEND_ONE);
		SetRenderStateSmart(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		SetRenderStateSmart(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		SetRenderStateSmart(D3DRS_ALPHATESTENABLE, FALSE);
		SetRenderStateSmart(D3DRS_ZENABLE, D3DZB_FALSE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZBIAS, 0);

		rasterizer_set_vertex_shader_permutation(4, 8, 0);

		width = global_window_parameters.camera.viewport_bounds.x1 - global_window_parameters.camera.viewport_bounds.x0;
		height = global_window_parameters.camera.viewport_bounds.y1 - global_window_parameters.camera.viewport_bounds.y0;
		one_over_width = 1.f / width;
		vsh_constants[0][0] = 2.f * one_over_width;
		vsh_constants[0][1] = 0.f;
		vsh_constants[0][2] = 0.f;
		vsh_constants[0][3] = -1.f - one_over_width;
		one_over_height = 1.f / height;
		vsh_constants[1][0] = 0.f;
		vsh_constants[1][1] = -2.f * one_over_height;
		vsh_constants[1][2] = 0.f;
		vsh_constants[1][3] = 1.f + one_over_height;
		vsh_constants[2][0] = 0.f;
		vsh_constants[2][1] = 0.f;
		vsh_constants[2][2] = 0.f;
		vsh_constants[2][3] = 0.5f;
		vsh_constants[3][0] = 0.f;
		vsh_constants[3][1] = 0.f;
		vsh_constants[3][2] = 0.f;
		vsh_constants[3][3] = 1.f;
		vsh_constants[4][0] = 1.f;
		vsh_constants[4][1] = 1.f;
		vsh_constants[4][2] = 0.f;
		vsh_constants[4][3] = 1.f;
		IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, VSH_CONSTANTS__SCREENPROJ_OFFSET, vsh_constants, VSH_CONSTANTS__SCREENPROJ_COUNT);

		csmemset(&pixel_shader, 0, sizeof(pixel_shader));
		pixel_shader.PSTextureModes = 1;
		pixel_shader.PSCombinerCount = 1;
		pixel_shader.PSFinalCombinerInputsABCD = 0x08;
		pixel_shader.PSFinalCombinerInputsEFG = 0x1800;
		rasterizer_set_pixel_shader(&pixel_shader);

		size = local_player_count() > 1 ? 32.f : 42.f;

		IDirect3DDevice8_Begin(global_d3d_device, D3DPT_TRIANGLEFAN);
		IDirect3DDevice8_SetVertexData2s(global_d3d_device, D3DVSDE_SPECULAR, 0, 0);
		IDirect3DDevice8_SetVertexData2f(global_d3d_device, D3DVSDE_POSITION, center_point->x - size, center_point->y - size);
		IDirect3DDevice8_SetVertexData2s(global_d3d_device, D3DVSDE_SPECULAR, 1, 0);
		IDirect3DDevice8_SetVertexData2f(global_d3d_device, D3DVSDE_POSITION, size + center_point->x, center_point->y - size);
		IDirect3DDevice8_SetVertexData2s(global_d3d_device, D3DVSDE_SPECULAR, 1, 1);
		IDirect3DDevice8_SetVertexData2f(global_d3d_device, D3DVSDE_POSITION, size + center_point->x, size + center_point->y);
		IDirect3DDevice8_SetVertexData2s(global_d3d_device, D3DVSDE_SPECULAR, 0, 1);
		IDirect3DDevice8_SetVertexData2f(global_d3d_device, D3DVSDE_POSITION, center_point->x - size, size + center_point->y);
		IDirect3DDevice8_End(global_d3d_device);
	}
	else
	{
		if (rasterizer_debug_options.draw_hud_motion_sensor && rasterizer_motion_sensor_begin_said_to_draw)
		{
			rasterizer_set_target(global_window_parameters.rasterizer_target, 0, 0, FALSE, TRUE);
		}
	}
}

/* ---------- private code */
