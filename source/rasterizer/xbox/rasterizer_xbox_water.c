/*
RASTERIZER_XBOX_WATER.C

symbols in this file:
001688F0 01b0:
	_D3DDevice_SetRenderState (0000)
00168AA0 0050:
	_D3DDevice_SetTextureStageState (0000)
00168AF0 0020:
	_rasterizer_water_set_visibility_for_frame (0000)
00168B10 0010:
	_rasterizer_water_set_visibility_for_window (0000)
00168B20 0010:
	_rasterizer_water_get_visibility_for_window (0000)
00168B30 0220:
	_IDirect3DDevice8_SetRenderState@12 (0000)
00168D50 0060:
	_IDirect3DDevice8_SetTextureStageState@16 (0000)
00168DB0 0010:
	_IDirect3DDevice8_SetVertexShaderConstant@16 (0000)
00168DC0 0020:
	_IDirect3DDevice8_SetVertexData2f@16 (0000)
00168DE0 0010:
	_IDirect3DDevice8_SetVertexData2s@16 (0000)
00168DF0 0010:
	_IDirect3DDevice8_Begin@8 (0000)
00168E00 0010:
	_IDirect3DDevice8_End@4 (0000)
00168E10 0820:
	_rasterizer_water_build_bumpmap (0000)
00169630 08c0:
	_rasterizer_water_draw (0000)
0029CBA0 0030:
	??_C@_0DA@GMAFCPCK@?$CD?$CD?$CD?5ERROR?5rasterizer_water_build@ (0000)
0029CBD0 0043:
	??_C@_0ED@IHGINMLN@ripples?$FL2?$FN?4contibution_factor?5?$CL?5@ (0000)
0029CC18 0043:
	??_C@_0ED@IIOIOBNN@ripples?$FL0?$FN?4contibution_factor?5?$CL?5@ (0000)
0029CC5C 0024:
	??_C@_0CE@CFGOBBBI@ripples?$FLripple_index?$FN?4map_repeat@ (0000)
0029CC80 0037:
	??_C@_0DH@OMMLHAPF@c?3?2halo?2SOURCE?2rasterizer?2xbox?2r@ (0000)
004662E8 0002:
	_water_needs_update_flag (0000)
	_water_visible_for_window_flag (0000)
*/

/* ---------- headers */

#include "cseries.h"
#include "cseries_windows.h"
#include "errors.h"
#include "real_math.h"
#include "tag_groups.h"
#include "game_globals.h"
#include "rasterizer.h"
#include "xbox/rasterizer_xbox.h"
#include "shaders/shader_definitions.h"

/* ---------- constants */

#define VSDE_VERTEX 0

enum
{
	MAXIMUM_WATER_RIPPLES= 4,
	MAXIMUM_WATER_RIPPLE_MIPMAP_LEVELS= 4,
};

/* ---------- macros */

/* ---------- structures */

/* ---------- prototypes */

void *shader_get_and_verify_type(struct shader const *shader, short type);
short shader_get_vertex_shader_permutation(struct shader const *shader);
short rasterizer_transparent_geometry_get_primary_vertex_type(struct transparent_geometry_group const *group);
void rasterizer_transparent_geometry_group_draw__internal(struct transparent_geometry_group const *group, long unknown);
void *rasterizer_set_texture(short stage, short type, short usage, long bitmap_group_index, short bitmap_index);
boolean rasterizer_set_texture_direct(short stage, long bitmap_group_index, short bitmap_index);
void rasterizer_set_stencil_mode(short stencil_mode);
void rasterizer_set_target(short target, short mipmap_index, unsigned long background_color, boolean clear, boolean zbuffer);
void *rasterizer_set_target_as_texture(short stage, short target, short max_mipmap);
void rasterizer_set_vertex_shader_permutation(short vertex_shader, short vertex_type, short permutation);
void rasterizer_set_pixel_shader(D3DPIXELSHADERDEF *pixel_shader_definition);
void SetRenderStateSmart(D3DRENDERSTATETYPE state, unsigned long value);
unsigned long real_rgb_color_to_pixel32(real_rgb_color const *color);

void rasterizer_water_build_bumpmap(struct shader const *shader);

// lives in bitmaps_inlines.h
__inline unsigned long real_alpha_to_pixel32(
	real alpha)
{
	real scale= 255.f;
	long result;

	match_assert("..\\bitmaps\\bitmaps_inlines.h", 291, alpha>=0.0f && alpha<=1.0f);

	__asm
	{
		fld alpha
		fld scale
		fmulp st(1), st
		fistp result
		shl result, 24
	}

	return result;
}

/* ---------- globals */

extern struct rasterizer_window_begin_parameters global_window_parameters;
extern struct game_globals_rasterizer_data *global_rasterizer_data;
extern D3DPIXELSHADERDEF pixel_shader;

static boolean water_needs_update_flag;
static boolean water_visible_for_window_flag;

/* ---------- public code */

void rasterizer_water_set_visibility_for_frame(
	boolean visibility)
{
	water_needs_update_flag= !visibility;
	water_visible_for_window_flag= visibility;
}

void rasterizer_water_set_visibility_for_window(
	boolean visibility)
{
	water_visible_for_window_flag= visibility;
}

boolean rasterizer_water_get_visibility_for_window(
	void)
{
	return water_visible_for_window_flag;
}

void rasterizer_water_build_bumpmap(
	struct shader const *shader)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_water.c", 47, shader);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_water.c", 48, global_d3d_device);

	if (rasterizer_debug_options.draw_water)
	{
		struct shader_transparent_water const *water= shader_get_and_verify_type(shader, _shader_type_transparent_water);
		short num_passes= MIN(water->water.ripple_mipmap_levels, MAXIMUM_WATER_RIPPLE_MIPMAP_LEVELS);
		real_vector4d vsh_constants__texanim[2*MAXIMUM_WATER_RIPPLES];
		struct shader_transparent_water_ripple ripples[MAXIMUM_WATER_RIPPLES];
		short ripple_index;
		short pass_index;
		boolean success;

		for (ripple_index= 0; ripple_index<MAXIMUM_WATER_RIPPLES; ripple_index++)
		{
			if (ripple_index<water->water.ripples.count)
			{
				ripples[ripple_index]= *TAG_BLOCK_GET_ELEMENT(&water->water.ripples, ripple_index, struct shader_transparent_water_ripple);
			}
			else
			{
				csmemset(&ripples[ripple_index], 0, sizeof(struct shader_transparent_water_ripple));
				ripples[ripple_index].map_repeats= 1;
			}
		}

		if (ripples[0].contibution_factor==0.f && ripples[1].contibution_factor==0.f)
		{
			ripples[1].contibution_factor= 1.f;
		}
		if (ripples[2].contibution_factor==0.f && ripples[3].contibution_factor==0.f)
		{
			ripples[3].contibution_factor= 1.f;
		}

		for (ripple_index= 0; ripple_index<MAXIMUM_WATER_RIPPLES; ripple_index++)
		{
			rasterizer_set_texture(ripple_index, 0, 3, ripple_index<water->water.ripples.count ? water->water.ripple_maps.index : NONE, ripples[ripple_index].map_index);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, ripple_index, D3DTSS_ADDRESSU, D3DTADDRESS_WRAP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, ripple_index, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, ripple_index, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, ripple_index, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, ripple_index, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);
		}

		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_CCW);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_BLUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHABLENDENABLE, FALSE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHATESTENABLE, FALSE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZENABLE, D3DZB_FALSE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZBIAS, 0);

		rasterizer_set_vertex_shader_permutation(38, 8, 0);

		for (ripple_index= 0; ripple_index<MAXIMUM_WATER_RIPPLES; ripple_index++)
		{
			real cosine= (real)cos(ripples[ripple_index].animation_angle);
			real sine= (real)sin(ripples[ripple_index].animation_angle);

			match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_water.c", 124, ripples[ripple_index].map_repeats>0);

			vsh_constants__texanim[2*ripple_index].i= ripples[ripple_index].map_repeats;
			vsh_constants__texanim[2*ripple_index].j= 0.f;
			vsh_constants__texanim[2*ripple_index].k= 0.f;
			vsh_constants__texanim[2*ripple_index].l= cosine*(global_frame_parameters.game_time_sec*ripples[ripple_index].animation_velocity) + ripples[ripple_index].map_offset.i;
			vsh_constants__texanim[2*ripple_index+1].i= 0.f;
			vsh_constants__texanim[2*ripple_index+1].j= ripples[ripple_index].map_repeats;
			vsh_constants__texanim[2*ripple_index+1].k= 0.f;
			vsh_constants__texanim[2*ripple_index+1].l= global_frame_parameters.game_time_sec*ripples[ripple_index].animation_velocity*sine + ripples[ripple_index].map_offset.j;
		}

		IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, -81, vsh_constants__texanim, 2*MAXIMUM_WATER_RIPPLES);

		success= TRUE;
		csmemset(&pixel_shader, 0, sizeof(pixel_shader));
		pixel_shader.PSTextureModes= 0x00008421;
		pixel_shader.PSCombinerCount= 0x00011004;
		pixel_shader.PSRGBInputs[0]= 0x31481149;
		pixel_shader.PSRGBOutputs[0]= 0x00000c00;
		pixel_shader.PSRGBInputs[1]= 0x314a114b;
		pixel_shader.PSRGBOutputs[1]= 0x00000d00;
		pixel_shader.PSRGBInputs[2]= 0x31cc11cd;
		pixel_shader.PSRGBOutputs[2]= 0x00030c00;
		pixel_shader.PSRGBInputs[3]= 0xcc20a020;
		pixel_shader.PSRGBOutputs[3]= 0x00000c00;
		pixel_shader.PSFinalCombinerInputsABCD= 0x310c0100;
		pixel_shader.PSFinalCombinerInputsEFG= 0;

		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_water.c", 159, ripples[0].contibution_factor + ripples[1].contibution_factor>0.0f);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_water.c", 160, ripples[2].contibution_factor + ripples[3].contibution_factor>0.0f);

		pixel_shader.PSConstant0[0]= real_alpha_to_pixel32(ripples[0].contibution_factor/(ripples[0].contibution_factor + ripples[1].contibution_factor));
		pixel_shader.PSConstant0[1]= real_alpha_to_pixel32(ripples[2].contibution_factor/(ripples[2].contibution_factor + ripples[3].contibution_factor));
		pixel_shader.PSConstant0[2]= real_alpha_to_pixel32((ripples[0].contibution_factor + ripples[1].contibution_factor)/(ripples[0].contibution_factor + ripples[1].contibution_factor + ripples[2].contibution_factor + ripples[3].contibution_factor));
		rasterizer_set_pixel_shader(&pixel_shader);

		rasterizer_set_stencil_mode(0);

		for (pass_index= 0; pass_index<num_passes; pass_index++)
		{
			real scale;
			real mysterious_horizontal_offset;

			if (water->water.ripple_mipmap_levels>1)
			{
				pixel_shader.PSFinalCombinerConstant0= real_alpha_to_pixel32((real)pass_index/(water->water.ripple_mipmap_levels-1)*water->water.ripple_mipmap_fade_factor) | 0x008080ff;
			}
			else
			{
				pixel_shader.PSFinalCombinerConstant0= 0x007f7fff;
			}
			rasterizer_set_pixel_shader(&pixel_shader);
			rasterizer_set_target(6, pass_index, 0, FALSE, FALSE);

			scale= 1.f/(128>>pass_index);
			mysterious_horizontal_offset= scale*-2.f;

			D3DCALL(success, IDirect3DDevice8_Begin(global_d3d_device, D3DPT_TRIANGLEFAN));
			D3DCALL(success, IDirect3DDevice8_SetVertexData2s(global_d3d_device, 4, 0, 0));
			D3DCALL(success, IDirect3DDevice8_SetVertexData2f(global_d3d_device, VSDE_VERTEX, scale - 1.0f + mysterious_horizontal_offset, scale + 1.0f));
			D3DCALL(success, IDirect3DDevice8_SetVertexData2s(global_d3d_device, 4, 1, 0));
			D3DCALL(success, IDirect3DDevice8_SetVertexData2f(global_d3d_device, VSDE_VERTEX, scale + 1.0f + mysterious_horizontal_offset, scale + 1.0f));
			D3DCALL(success, IDirect3DDevice8_SetVertexData2s(global_d3d_device, 4, 1, 1));
			D3DCALL(success, IDirect3DDevice8_SetVertexData2f(global_d3d_device, VSDE_VERTEX, scale + 1.0f + mysterious_horizontal_offset, scale - 1.0f));
			D3DCALL(success, IDirect3DDevice8_SetVertexData2s(global_d3d_device, 4, 0, 1));
			D3DCALL(success, IDirect3DDevice8_SetVertexData2f(global_d3d_device, VSDE_VERTEX, scale - 1.0f + mysterious_horizontal_offset, scale - 1.0f));
			D3DCALL(success, IDirect3DDevice8_End(global_d3d_device));
		}

		rasterizer_set_target(global_window_parameters.rasterizer_target, 0, 0, FALSE, TRUE);
		rasterizer_set_stencil_mode(2);

		if (!success)
		{
			error(_error_silent, "### ERROR rasterizer_water_build_bumpmap failed");
		}
	}

	return;
}

// TODO: the third dot_product3d() in the PIN() is called out of line in the original but inlined here,
// and the load of water->water.flags for the atmospheric fog test is scheduled slightly earlier in the original
void rasterizer_water_draw(
	struct transparent_geometry_group const *group)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_water.c", 238, group);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_water.c", 239, global_d3d_device);

	if (rasterizer_debug_options.draw_water)
	{
		struct shader_transparent_water const *water= shader_get_and_verify_type(group->shader, _shader_type_transparent_water);
		short vertex_shader_permutation= shader_get_vertex_shader_permutation(group->shader);
		short vertex_type= rasterizer_transparent_geometry_get_primary_vertex_type(group);

		if (TEST_FLAG(water->water.flags, _shader_transparent_water_draw_before_fog_bit) && !(group->geometry_flags & 0x12))
		{
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_NONE);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_COLORWRITEENABLE, 0);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHABLENDENABLE, FALSE);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHATESTENABLE, FALSE);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZENABLE, D3DZB_TRUE);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZWRITEENABLE, TRUE);

			rasterizer_set_vertex_shader_permutation(20, vertex_type, vertex_shader_permutation);

			csmemset(&pixel_shader, 0, sizeof(pixel_shader));
			pixel_shader.PSCombinerCount= 1;
			rasterizer_set_pixel_shader(&pixel_shader);

			rasterizer_transparent_geometry_group_draw__internal(group, 0);
		}
		else
		{
			boolean zwrite_enable= !(group->geometry_flags & 0x10) && !TEST_FLAG(water->water.flags, _shader_transparent_water_draw_before_fog_bit);
			real vsh_constants__texscale[12];

			if (water_needs_update_flag)
			{
				rasterizer_water_build_bumpmap(group->shader);
				water_needs_update_flag= FALSE;
			}

			if (TEST_FLAG(water->water.flags, _shader_transparent_water_base_map_alpha_modulates_reflection_bit))
			{
				rasterizer_set_texture(0, 0, 1, water->water.base_map.index, group->shader_permutation_index);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);

				rasterizer_set_texture_direct(1, global_rasterizer_data->vector_normalization.index, 0);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_ADDRESSW, D3DTADDRESS_CLAMP);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);

				IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_NONE);
				IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_ALPHA);
				IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHABLENDENABLE, FALSE);
				IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHATESTENABLE, FALSE);
				IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZENABLE, D3DZB_TRUE);
				IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
				IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZWRITEENABLE, zwrite_enable);

				rasterizer_set_vertex_shader_permutation(20, vertex_type, vertex_shader_permutation);

				csmemset(&pixel_shader, 0, sizeof(pixel_shader));
				pixel_shader.PSTextureModes= 0x00000061;
				pixel_shader.PSCombinerCount= 2;
				pixel_shader.PSConstant0[0]= real_alpha_to_pixel32(water->water.view_perpendicular_tint_color.alpha);
				pixel_shader.PSConstant1[0]= real_alpha_to_pixel32(water->water.view_parallel_tint_color.alpha);
				pixel_shader.PSAlphaInputs[0]= 0x29120911;
				pixel_shader.PSAlphaOutputs[0]= 0x00000c00;
				pixel_shader.PSAlphaInputs[1]= 0x1c180000;
				pixel_shader.PSAlphaOutputs[1]= 0x000000c0;
				pixel_shader.PSFinalCombinerInputsABCD= 0;
				pixel_shader.PSFinalCombinerInputsEFG= 0x00001c00;
				rasterizer_set_pixel_shader(&pixel_shader);

				rasterizer_transparent_geometry_group_draw__internal(group, 0);
			}

			if (TEST_FLAG(water->water.flags, _shader_transparent_water_base_map_color_modulates_background_bit))
			{
				rasterizer_set_texture(0, 0, 1, water->water.base_map.index, group->shader_permutation_index);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);

				IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_NONE);
				SetRenderStateSmart(D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_BLUE);
				SetRenderStateSmart(D3DRS_ALPHABLENDENABLE, TRUE);
				SetRenderStateSmart(D3DRS_SRCBLEND, D3DBLEND_ZERO);
				SetRenderStateSmart(D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR);
				SetRenderStateSmart(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				SetRenderStateSmart(D3DRS_ALPHATESTENABLE, FALSE);
				SetRenderStateSmart(D3DRS_ZENABLE, D3DZB_TRUE);
				SetRenderStateSmart(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
				SetRenderStateSmart(D3DRS_ZWRITEENABLE, zwrite_enable);

				rasterizer_set_vertex_shader_permutation(20, vertex_type, vertex_shader_permutation);

				csmemset(&pixel_shader, 0, sizeof(pixel_shader));
				pixel_shader.PSTextureModes= 1;
				pixel_shader.PSCombinerCount= 1;
				pixel_shader.PSFinalCombinerInputsABCD= ((TEST_FLAG(water->water.flags, _shader_transparent_water_atmospheric_fog_bit) ? 0x13 : 0)<<24) | 0x00200800;
				rasterizer_set_pixel_shader(&pixel_shader);

				rasterizer_transparent_geometry_group_draw__internal(group, 0);
			}

			rasterizer_set_target_as_texture(0, 6, MIN(water->water.ripple_mipmap_levels, MAXIMUM_WATER_RIPPLE_MIPMAP_LEVELS));
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSU, D3DTADDRESS_WRAP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);

			rasterizer_set_texture(3, 2, 0, water->water.reflection_map.index, group->shader_permutation_index);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_ADDRESSW, D3DTADDRESS_CLAMP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);

			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_NONE);
			SetRenderStateSmart(D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_BLUE);
			SetRenderStateSmart(D3DRS_ALPHABLENDENABLE, !(group->geometry_flags & 0x10));
			SetRenderStateSmart(D3DRS_SRCBLEND, TEST_FLAG(water->water.flags, _shader_transparent_water_base_map_alpha_modulates_reflection_bit) ? D3DBLEND_DESTALPHA : D3DBLEND_ONE);
			SetRenderStateSmart(D3DRS_DESTBLEND, D3DBLEND_ONE);
			SetRenderStateSmart(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			SetRenderStateSmart(D3DRS_ALPHATESTENABLE, FALSE);
			SetRenderStateSmart(D3DRS_ZENABLE, D3DZB_TRUE);
			SetRenderStateSmart(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
			SetRenderStateSmart(D3DRS_ZWRITEENABLE, zwrite_enable);

			rasterizer_set_vertex_shader_permutation(23, vertex_type, vertex_shader_permutation);

			vsh_constants__texscale[0]= water->water.ripple_scale;
			vsh_constants__texscale[1]= water->water.ripple_scale;
			vsh_constants__texscale[2]= global_frame_parameters.game_time_sec*(cosine(water->water.ripple_animation_angle)*water->water.ripple_animation_velocity);
			vsh_constants__texscale[3]= global_frame_parameters.game_time_sec*(sine(water->water.ripple_animation_angle)*water->water.ripple_animation_velocity);
			vsh_constants__texscale[4]= 0.f;
			vsh_constants__texscale[5]= 0.f;
			vsh_constants__texscale[6]= 0.f;
			vsh_constants__texscale[7]= 0.f;
			vsh_constants__texscale[8]= 0.f;
			vsh_constants__texscale[9]= 0.f;
			vsh_constants__texscale[10]= 0.f;
			vsh_constants__texscale[11]= 0.f;
			IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, -84, vsh_constants__texscale, 3);

			csmemset(&pixel_shader, 0, sizeof(pixel_shader));
			pixel_shader.PSTextureModes= 0x00064621;
			pixel_shader.PSDotMapping= 0x00000111;
			pixel_shader.PSRGBOutputs[0]= 0x000000cd;
			pixel_shader.PSRGBInputs[0]= 0x0b0b0120;
			if (TEST_FLAG(water->water.flags, _shader_transparent_water_atmospheric_fog_bit))
			{
				pixel_shader.PSCombinerCount= 4;
				pixel_shader.PSRGBInputs[1]= 0x0c0c0000;
				pixel_shader.PSRGBOutputs[1]= 0x000000c0;
				pixel_shader.PSRGBInputs[2]= 0x0c0c0000;
				pixel_shader.PSRGBOutputs[2]= 0x000000c0;
				pixel_shader.PSRGBInputs[3]= 0x2d0c0d0b;
				pixel_shader.PSRGBOutputs[3]= 0x00000c00;
				pixel_shader.PSFinalCombinerInputsABCD= 0x330c0000;
			}
			else
			{
				pixel_shader.PSCombinerCount= 2;
				pixel_shader.PSRGBInputs[1]= 0x0c0c0000;
				pixel_shader.PSRGBOutputs[1]= 0x000000c0;
				pixel_shader.PSFinalCombinerInputsABCD= 0x2d0f0b00;
				pixel_shader.PSFinalCombinerInputsEFG= 0x0c0c0000;
			}

			if (magnitude3d(&group->plane.n)>0.f)
			{
				real t= PIN(-dot_product3d(&global_window_parameters.camera.forward, &group->plane.n), 0.f, 1.f);
				real_rgb_color color;

				color.red= (1.f-t)*water->water.view_parallel_tint_color.red + t*water->water.view_perpendicular_tint_color.red;
				color.green= (1.f-t)*water->water.view_parallel_tint_color.green + t*water->water.view_perpendicular_tint_color.green;
				color.blue= (1.f-t)*water->water.view_parallel_tint_color.blue + t*water->water.view_perpendicular_tint_color.blue;
				pixel_shader.PSConstant0[0]= real_rgb_color_to_pixel32(&color);
			}
			else
			{
				pixel_shader.PSConstant0[0]= 0x00ffffff;
			}
			rasterizer_set_pixel_shader(&pixel_shader);

			{
				real lod_bias= -water->water.ripple_mipmap_lod_bias;

				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MIPMAPLODBIAS, *(DWORD *)&lod_bias);
			}
			rasterizer_transparent_geometry_group_draw__internal(group, 0);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MIPMAPLODBIAS, 0);
		}
	}

	return;
}
