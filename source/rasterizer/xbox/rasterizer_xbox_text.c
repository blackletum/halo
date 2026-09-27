/*
RASTERIZER_XBOX_TEXT.C

symbols in this file:
00162EA0 01b0:
	_D3DDevice_SetRenderState (0000)
00163050 0050:
	_D3DDevice_SetTextureStageState (0000)
001630A0 0220:
	_IDirect3DDevice8_SetRenderState@12 (0000)
001632C0 0060:
	_IDirect3DDevice8_SetTextureStageState@16 (0000)
00163320 0010:
	_IDirect3DDevice8_SetVertexShaderConstant@16 (0000)
00163330 0010:
	_rasterizer_text_end (0000)
00163340 0020:
	_IDirect3DDevice8_SetVertexData2f@16 (0000)
00163360 0010:
	_IDirect3DDevice8_SetVertexDataColor@12 (0000)
00163370 0010:
	_IDirect3DDevice8_Begin@8 (0000)
00163380 0010:
	_IDirect3DDevice8_End@4 (0000)
00163390 0690:
	_rasterizer_text_begin (0000)
00163A20 0120:
	_rasterizer_text_draw_character (0000)
00292B28 0036:
	??_C@_0DG@NLGEIAMP@c?3?2halo?2SOURCE?2rasterizer?2xbox?2r@ (0000)
00292B60 0030:
	??_C@_0DA@FEBHLDDN@?$CD?$CD?$CD?5ERROR?5rasterizer_text_draw_c@ (0000)
00292B90 0087:
	??_C@_0IH@NAGGOICD@IDirect3DDevice8_SetVertexData2f@ (0000)
00292C18 007d:
	??_C@_0HN@NMADEKEL@IDirect3DDevice8_SetVertexData2f@ (0000)
00292C98 0058:
	??_C@_0FI@KKLBHBJN@IDirect3DDevice8_SetVertexDataCo@ (0000)
*/

/* ---------- headers */

#include "cseries.h"
#include "cseries_windows.h"
#include "errors.h"
#include "real_math.h"
#include "rasterizer.h"
#include "rasterizer_geometry.h"
#include "xbox/rasterizer_xbox.h"

/*
the D3DDevice_* and IDirect3DDevice8_* symbols above are uninlined copies of d3d8.h
__forceinline functions emitted by the compiler (D3DDevice_SetRenderState,
D3DDevice_SetTextureStageState, IDirect3DDevice8_SetRenderState, _SetTextureStageState,
_SetVertexShaderConstant, _SetVertexData2f, _SetVertexDataColor, _Begin, _End)
*/

/* ---------- constants */

enum
{
	NUMBER_OF_TEXT_CHARACTER_VERTICES = 4
};

/* ---------- macros */

#define VSDE_VERTEX 0

/* ---------- prototypes */

void rasterizer_set_framebuffer_blend_function(short framebuffer_blend_function);
boolean rasterizer_set_texture_bitmap_data(short stage, struct bitmap_data const *bitmap);
void rasterizer_set_vertex_shader_permutation(long vertex_shader, long vertex_type, long permutation);
void rasterizer_set_pixel_shader(D3DPIXELSHADERDEF *definition);

pixel32 real_argb_color_to_pixel32(real_argb_color const *color);

/* ---------- globals */

extern struct rasterizer_window_begin_parameters global_window_parameters;
extern D3DPIXELSHADERDEF pixel_shader;

/* ---------- public code */

void rasterizer_text_begin(
	struct rasterizer_dynamic_screen_geometry_parameters const *parameters)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_text.c", 13, global_d3d_device);

	if (rasterizer_debug_options.draw_dynamic_screen_geometry && !global_window_parameters.rasterizer_target)
	{
		short stage;
		short width, height;
		real_vector2d offset;

		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_text.c", 18, parameters);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_text.c", 20, parameters->map[0]);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_text.c", 22, !parameters->map[2] || parameters->map[1]);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_text.c", 24, !parameters->map[1] || !parameters->meter_parameters);

		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_NONE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED|D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_BLUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHABLENDENABLE, TRUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZENABLE, D3DZB_FALSE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZBIAS, 0);
		rasterizer_set_framebuffer_blend_function(parameters->framebuffer_blend_function);

		width= global_window_parameters.camera.viewport_bounds.x1-global_window_parameters.camera.viewport_bounds.x0;
		height= global_window_parameters.camera.viewport_bounds.y1-global_window_parameters.camera.viewport_bounds.y0;
		offset.i= parameters->offset ? 2.f*parameters->offset->i/width : 0.f;
		offset.j= parameters->offset ? -2.f*parameters->offset->j/height : 0.f;

		{
			real inverse_width= 1.f/width;
			real inverse_height;
			real_vector4d position_constants[5];
			real_vector4d texture_constants[6];

			position_constants[0].i= 2.f*inverse_width;
			position_constants[0].j= 0.f;
			position_constants[0].k= 0.f;
			position_constants[0].l= offset.i-(inverse_width+1.f);
			inverse_height= 1.f/height;
			position_constants[1].i= 0.f;
			position_constants[1].j= -2.f*inverse_height;
			position_constants[1].k= 0.f;
			position_constants[1].l= inverse_height+offset.j+1.f;
			position_constants[2].i= 0.f;
			position_constants[2].j= 0.f;
			position_constants[2].k= 0.f;
			position_constants[2].l= 0.5f;
			position_constants[3].i= 0.f;
			position_constants[3].j= 0.f;
			position_constants[3].k= 0.f;
			position_constants[3].l= 1.f;
			position_constants[4].i= parameters->map_texture_scale[0].i;
			position_constants[4].j= parameters->map_texture_scale[0].j;
			position_constants[4].k= 0.f;
			position_constants[4].l= 1.f;

			texture_constants[0].i= parameters->map_texture_scale[1].i;
			texture_constants[0].j= parameters->map_texture_scale[1].j;
			texture_constants[0].k= parameters->map_texture_scale[2].i;
			texture_constants[0].l= parameters->map_texture_scale[2].j;
			texture_constants[1].i= parameters->map_anchor_screen[0] ? 1.f : 0.f;
			texture_constants[1].j= parameters->map_anchor_screen[0] ? 0.f : 1.f;
			texture_constants[1].k= parameters->map_anchor_screen[1] ? 1.f : 0.f;
			texture_constants[1].l= parameters->map_anchor_screen[1] ? 0.f : 1.f;
			texture_constants[2].i= parameters->map_anchor_screen[2] ? 1.f : 0.f;
			texture_constants[2].j= parameters->map_anchor_screen[2] ? 0.f : 1.f;
			texture_constants[2].k= parameters->map_offset[0] ? parameters->map_offset[0]->x : 0.f;
			texture_constants[2].l= parameters->map_offset[0] ? parameters->map_offset[0]->y : 0.f;
			texture_constants[3].i= parameters->map_offset[1] ? parameters->map_offset[1]->x : 0.f;
			texture_constants[3].j= parameters->map_offset[1] ? parameters->map_offset[1]->y : 0.f;
			texture_constants[3].k= parameters->map_offset[2] ? parameters->map_offset[2]->x : 0.f;
			texture_constants[3].l= parameters->map_offset[2] ? parameters->map_offset[2]->y : 0.f;
			texture_constants[4].i= parameters->map_scale[0].i;
			texture_constants[4].j= parameters->map_scale[0].j;
			texture_constants[4].k= parameters->map_scale[1].i;
			texture_constants[4].l= parameters->map_scale[1].j;
			texture_constants[5].i= parameters->map_scale[2].i;
			texture_constants[5].j= parameters->map_scale[2].j;
			texture_constants[5].k= 0.f;
			texture_constants[5].l= 0.f;

			IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, -68, position_constants, 5);
			IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, -63, texture_constants, 6);
		}

		for (stage= 0; stage<NUMBER_OF_DYNAMIC_SCREEN_GEOMETRY_MAPS; stage++)
		{
			if (!parameters->map[stage])
			{
				break;
			}

			rasterizer_set_texture_bitmap_data(stage, parameters->map[stage]);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, stage, D3DTSS_ADDRESSU, parameters->map_wrapped[stage] ? D3DTADDRESS_WRAP : D3DTADDRESS_CLAMP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, stage, D3DTSS_ADDRESSV, parameters->map_wrapped[stage] ? D3DTADDRESS_WRAP : D3DTADDRESS_CLAMP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, stage, D3DTSS_MAGFILTER, parameters->point_sampled ? D3DTEXF_POINT : D3DTEXF_LINEAR);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, stage, D3DTSS_MINFILTER, parameters->point_sampled ? D3DTEXF_POINT : D3DTEXF_LINEAR);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, stage, D3DTSS_MIPFILTER, parameters->point_sampled ? D3DTEXF_POINT : D3DTEXF_LINEAR);
		}

		rasterizer_set_vertex_shader_permutation(4, 8, 1);

		if (parameters->map[0])
		{
			real_argb_color colors[NUMBER_OF_DYNAMIC_SCREEN_GEOMETRY_MAPS];

			csmemset(&pixel_shader, 0, sizeof(pixel_shader));
			pixel_shader.PSTextureModes= PS_TEXTUREMODES(parameters->map[0] ? PS_TEXTUREMODES_PROJECT2D : PS_TEXTUREMODES_NONE, parameters->map[1] ? PS_TEXTUREMODES_PROJECT2D : PS_TEXTUREMODES_NONE, parameters->map[2] ? PS_TEXTUREMODES_PROJECT2D : PS_TEXTUREMODES_NONE, PS_TEXTUREMODES_NONE);

			colors[0].rgb= *(parameters->map_tint[0] ? parameters->map_tint[0] : global_real_rgb_white);
			colors[1].rgb= *(parameters->map_tint[1] ? parameters->map_tint[1] : global_real_rgb_white);
			colors[2].rgb= *(parameters->map_tint[2] ? parameters->map_tint[2] : global_real_rgb_white);
			colors[0].alpha= parameters->map_fade[0] ? *parameters->map_fade[0] : 1.f;
			colors[1].alpha= parameters->map_fade[1] ? *parameters->map_fade[1] : 1.f;
			colors[2].alpha= parameters->map_fade[2] ? *parameters->map_fade[2] : 1.f;

			pixel_shader.PSConstant0[0]= real_argb_color_to_pixel32(&colors[0]);
			pixel_shader.PSConstant1[0]= real_argb_color_to_pixel32(&colors[1]);
			pixel_shader.PSConstant0[1]= real_argb_color_to_pixel32(&colors[2]);
			pixel_shader.PSConstant0[4]= real_argb_color_to_pixel32(&parameters->plasma_fade);
			pixel_shader.PSConstant0[5]= real_argb_color_to_pixel32(&parameters->plasma_fade);
			pixel_shader.PSConstant0[6]= real_argb_color_to_pixel32(&parameters->plasma_fade);
			pixel_shader.PSConstant0[7]= real_argb_color_to_pixel32(&parameters->plasma_fade);

			pixel_shader.PSRGBOutputs[0]= 0x89;
			pixel_shader.PSAlphaOutputs[0]= 0x89;
			pixel_shader.PSRGBInputs[0]= 0x08010902;
			pixel_shader.PSAlphaInputs[0]= 0x18111912;
			pixel_shader.PSRGBInputs[1]= 0x0a010804;
			pixel_shader.PSRGBOutputs[1]= 0xac;
			pixel_shader.PSAlphaInputs[1]= 0x1a111814;
			pixel_shader.PSAlphaOutputs[1]= 0xac;
			pixel_shader.PSCombinerCount= 0x11102;
			pixel_shader.PSFinalCombinerInputsABCD= 0x0c;
			pixel_shader.PSFinalCombinerInputsEFG= 0x1c00;
		}

		rasterizer_set_pixel_shader(&pixel_shader);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_CCW);
		rasterizer_set_vertex_shader_permutation(4, 8, 0);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ALPHAKILL, D3DTALPHAKILL_DISABLE);
	}
}

void rasterizer_text_draw_character(
	struct dynamic_screen_vertex const *vertices)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_text.c", 216, global_d3d_device);

	if (rasterizer_debug_options.draw_dynamic_screen_geometry && !global_window_parameters.rasterizer_target)
	{
		boolean success;
		short vertex_index;

		IDirect3DDevice8_Begin(global_d3d_device, D3DPT_TRIANGLEFAN);
		success= TRUE;
		for (vertex_index= 0; vertex_index<NUMBER_OF_TEXT_CHARACTER_VERTICES; vertex_index++)
		{
			D3DCALL(success, IDirect3DDevice8_SetVertexDataColor(global_d3d_device, 9, vertices[vertex_index].color));
			D3DCALL(success, IDirect3DDevice8_SetVertexData2f(global_d3d_device, 4, vertices[vertex_index].texcoord.u, vertices[vertex_index].texcoord.v));
			D3DCALL(success, IDirect3DDevice8_SetVertexData2f(global_d3d_device, VSDE_VERTEX, vertices[vertex_index].position.x, vertices[vertex_index].position.y));
		}
		D3DCALL(success, IDirect3DDevice8_End(global_d3d_device));

		if (!success)
		{
			error(_error_silent, "### ERROR rasterizer_text_draw_character failed");
		}
	}
}

void rasterizer_text_end(
	void)
{
	return;
}
