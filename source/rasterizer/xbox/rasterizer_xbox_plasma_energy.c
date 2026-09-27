/*
RASTERIZER_XBOX_PLASMA_ENERGY.C

symbols in this file:
0015E2B0 01b0:
	_D3DDevice_SetRenderState (0000)
0015E460 0050:
	_D3DDevice_SetTextureStageState (0000)
0015E4B0 0220:
	_IDirect3DDevice8_SetRenderState@12 (0000)
0015E6D0 0060:
	_IDirect3DDevice8_SetTextureStageState@16 (0000)
0015E730 0010:
	_IDirect3DDevice8_SetVertexShaderConstant@16 (0000)
0015E740 0590:
	_rasterizer_plasma_energy_draw (0000)
00291F10 0004:
	__real@3a03126f (0000)
00291F14 0033:
	??_C@_0DD@OEJHPIIG@plasma?9?$DOsecondary_noise_map_anim@ (0000)
00291F48 0031:
	??_C@_0DB@CGFOFGKP@plasma?9?$DOprimary_noise_map_animat@ (0000)
00291F7C 003f:
	??_C@_0DP@HOMIPMOO@c?3?2halo?2SOURCE?2rasterizer?2xbox?2r@ (0000)
*/

/* ---------- headers */

#include "cseries.h"
#include "cseries_windows.h"
#include "errors.h"
#include "real_math.h"
#include "tag_groups.h"
#include "render.h"
#include "rasterizer.h"
#include "xbox/rasterizer_xbox.h"
#include "shaders/shader_definitions.h"

/* ---------- constants */

/* ---------- macros */

/* ---------- structures */

/* ---------- prototypes */

void *shader_get_and_verify_type(struct shader const *shader, short type);
short rasterizer_transparent_geometry_get_primary_vertex_type(struct transparent_geometry_group const *group);
void rasterizer_transparent_geometry_group_draw__internal(struct transparent_geometry_group const *group, boolean has_lightmap);
void *rasterizer_set_texture(short stage, short type, short usage, long bitmap_group_index, short bitmap_index);
void rasterizer_set_vertex_shader_permutation(short vertex_shader, short permutation, short type);
void rasterizer_set_pixel_shader(D3DPIXELSHADERDEF *pixel_shader_definition);

/* ---------- globals */

extern D3DPIXELSHADERDEF pixel_shader;

/* ---------- public code */

void rasterizer_plasma_energy_draw(
	struct transparent_geometry_group const *group)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_plasma_energy.c", 21, global_d3d_device);

	if (rasterizer_debug_options.plasma_energy_enabled)
	{
		struct _shader_transparent_plasma const *plasma= &((struct shader_transparent_plasma const *)shader_get_and_verify_type(group->shader, _shader_type_transparent_plasma))->plasma;
		real_rgb_color const *tint_color= global_real_rgb_white;
		real offset;
		real intensity;
		real texanim_constants[6][4];
		real color_constants[3][4];

		intensity= 1.f;
		offset= 0.f;
		if (group->animation)
		{
			if (group->animation->colors && plasma->tint_color_source>=1 && plasma->tint_color_source<=4)
			{
				tint_color= &group->animation->colors[plasma->tint_color_source-1];
			}
			if (group->animation->values)
			{
				if (plasma->intensity_source>=1 && plasma->intensity_source<=4)
				{
					intensity= (real)pow(group->animation->values[plasma->intensity_source-1], plasma->intensity_exponent);
				}
				if (plasma->offset_source>=1 && plasma->offset_source<=4)
				{
					offset= (real)pow(group->animation->values[plasma->offset_source-1], plasma->offset_exponent)*plasma->offset_amount;
				}
			}
		}

		rasterizer_set_texture(0, 1, 0, plasma->primary_noise_map.index, group->shader_permutation_index);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSU, D3DTADDRESS_WRAP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSW, D3DTADDRESS_WRAP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);

		rasterizer_set_texture(1, 1, 0, plasma->secondary_noise_map.index, group->shader_permutation_index);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_ADDRESSU, D3DTADDRESS_WRAP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_ADDRESSW, D3DTADDRESS_WRAP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);

		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_NONE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_BLUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHABLENDENABLE, TRUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_DESTBLEND, D3DBLEND_ONE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_BLENDOP, D3DBLENDOP_ADD);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHATESTENABLE, FALSE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZENABLE, D3DZB_TRUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZWRITEENABLE, FALSE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZBIAS, 0);

		rasterizer_set_vertex_shader_permutation(15, rasterizer_transparent_geometry_get_primary_vertex_type(group), 0);

		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_plasma_energy.c", 105, plasma->primary_noise_map_animation_period!=0.0f);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_plasma_energy.c", 106, plasma->secondary_noise_map_animation_period!=0.0f);

		if (offset<0.0005f)
		{
			offset= 0.f;
		}

		{
			real primary_time= global_frame_parameters.game_time_sec/plasma->primary_noise_map_animation_period;
			real secondary_time;
			real primary_scale;
			real secondary_scale;

			texanim_constants[0][1]= 0.f;
			texanim_constants[0][2]= offset;
			texanim_constants[1][0]= 0.f;
			texanim_constants[1][2]= 0.f;
			texanim_constants[2][0]= 0.f;
			texanim_constants[2][1]= 0.f;
			texanim_constants[3][1]= 0.f;
			texanim_constants[3][2]= 0.f;
			texanim_constants[4][0]= 0.f;
			texanim_constants[4][2]= 0.f;
			texanim_constants[5][0]= 0.f;
			texanim_constants[5][1]= 0.f;
			color_constants[0][0]= 1.f;
			color_constants[0][1]= 1.f;
			color_constants[0][2]= 1.f;
			color_constants[0][3]= 1.f;
			secondary_time= global_frame_parameters.game_time_sec/plasma->secondary_noise_map_animation_period;
			primary_scale= plasma->primary_noise_map_scale;
			secondary_scale= plasma->secondary_noise_map_scale;
			texanim_constants[0][0]= primary_scale;
			texanim_constants[0][3]= plasma->primary_noise_map_animation_direction.i*primary_time;
			texanim_constants[1][1]= primary_scale;
			texanim_constants[1][3]= plasma->primary_noise_map_animation_direction.j*primary_time;
			texanim_constants[2][2]= primary_scale;
			texanim_constants[2][3]= plasma->primary_noise_map_animation_direction.k*primary_time;
			texanim_constants[3][0]= secondary_scale;
			texanim_constants[3][3]= plasma->secondary_noise_map_animation_direction.i*secondary_time;
			texanim_constants[4][1]= secondary_scale;
			texanim_constants[4][3]= plasma->secondary_noise_map_animation_direction.j*secondary_time;
			texanim_constants[5][2]= secondary_scale;
			texanim_constants[5][3]= plasma->secondary_noise_map_animation_direction.k*secondary_time;
		}

		color_constants[1][0]= (plasma->view_perpendicular_color.rgb.red-plasma->view_parallel_color.rgb.red)*tint_color->red;
		color_constants[1][1]= (plasma->view_perpendicular_color.rgb.green-plasma->view_parallel_color.rgb.green)*tint_color->green;
		color_constants[1][2]= (plasma->view_perpendicular_color.rgb.blue-plasma->view_parallel_color.rgb.blue)*tint_color->blue;
		color_constants[1][3]= (plasma->view_perpendicular_color.alpha-plasma->view_parallel_color.alpha)*intensity;
		color_constants[2][0]= plasma->view_parallel_color.rgb.red*tint_color->red;
		color_constants[2][1]= plasma->view_parallel_color.rgb.green*tint_color->green;
		color_constants[2][2]= plasma->view_parallel_color.rgb.blue*tint_color->blue;
		color_constants[2][3]= plasma->view_parallel_color.alpha*intensity;

		IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, -81, texanim_constants, 6);
		IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, -84, color_constants, 3);

		csmemset(&pixel_shader, 0, sizeof(pixel_shader));
		pixel_shader.PSTextureModes= 0x42;
		pixel_shader.PSCombinerCount= 0x104;
		pixel_shader.PSAlphaInputs[0]= 0x0820a920;
		pixel_shader.PSAlphaOutputs[0]= 0xc00;
		pixel_shader.PSRGBInputs[0]= 0x1920b820;
		pixel_shader.PSRGBOutputs[0]= 0xc00;
		pixel_shader.PSAlphaInputs[1]= 0x1c1c0c0c;
		pixel_shader.PSAlphaOutputs[1]= 0x24c00;
		pixel_shader.PSRGBInputs[1]= 0;
		pixel_shader.PSRGBOutputs[1]= 0;
		pixel_shader.PSAlphaInputs[2]= 0x5c5c;
		pixel_shader.PSAlphaOutputs[2]= 0x4d00;
		pixel_shader.PSRGBInputs[2]= 0;
		pixel_shader.PSRGBOutputs[2]= 0;
		pixel_shader.PSAlphaInputs[3]= 0x14150000;
		pixel_shader.PSAlphaOutputs[3]= 0x40;
		pixel_shader.PSRGBInputs[3]= 0x1c051da0;
		pixel_shader.PSRGBOutputs[3]= 0xc00;
		pixel_shader.PSFinalCombinerInputsABCD= 0x0c0f0000;
		pixel_shader.PSFinalCombinerInputsEFG= 0x1c1c1400;
		rasterizer_set_pixel_shader(&pixel_shader);

		rasterizer_transparent_geometry_group_draw__internal(group, FALSE);
	}
}
