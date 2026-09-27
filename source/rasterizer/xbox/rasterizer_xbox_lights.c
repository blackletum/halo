/*
RASTERIZER_XBOX_LIGHTS.C

symbols in this file:
00158850 01b0:
	_code_00158850 (0000) // D3DDevice_SetRenderState (d3d8.h, out of line)
00158A00 0050:
	_code_00158a00 (0000) // D3DDevice_SetTextureStageState (d3d8.h, out of line)
00158A50 01c0:
	_rasterizer_project_billboard (0000) // rasterizer_project_billboard
00158C10 0220:
	_code_00158c10 (0000) // IDirect3DDevice8_SetRenderState (d3d8.h, out of line)
00158E30 0060:
	_code_00158e30 (0000) // IDirect3DDevice8_SetTextureStageState (d3d8.h, out of line)
00158E90 0010:
	_code_00158e90 (0000) // IDirect3DDevice8_SetVertexShaderConstant (d3d8.h, out of line)
00158EA0 0020:
	_code_00158ea0 (0000) // IDirect3DDevice8_SetVertexData2f (d3d8.h, out of line)
00158EC0 0030:
	_code_00158ec0 (0000) // IDirect3DDevice8_SetVertexData4f (d3d8.h, out of line)
00158EF0 0010:
	_code_00158ef0 (0000) // IDirect3DDevice8_SetVertexData2s (d3d8.h, out of line)
00158F00 0010:
	_code_00158f00 (0000) // IDirect3DDevice8_Begin (d3d8.h, out of line)
00158F10 0010:
	_code_00158f10 (0000) // IDirect3DDevice8_End (d3d8.h, out of line)
00158F20 0380:
	_rasterizer_sun_glow_copy_source (0000) // rasterizer_sun_glow_copy_source
001592A0 0580:
	_rasterizer_sun_glow_convolve (0000) // rasterizer_sun_glow_convolve
00159820 0930:
	_rasterizer_sun_glow_draw (0000)
002911D0 0038:
	??_C@_0DI@FKFGJLFP@c?3?2halo?2SOURCE?2rasterizer?2xbox?2r@ (0000)
00291208 002e:
	??_C@_0CO@KOLMKNFB@?$CD?$CD?$CD?5ERROR?5rasterizer_sun_glow_co@ (0000)
00291238 007c:
	??_C@_0HM@HAPGHELG@IDirect3DDevice8_SetVertexData2f@ (0000)
002912B4 003d:
	??_C@_0DN@HPJBNCPC@IDirect3DDevice8_SetVertexData2s@ (0000)
002912F8 007c:
	??_C@_0HM@KNFENDHB@IDirect3DDevice8_SetVertexData2f@ (0000)
00291374 003d:
	??_C@_0DN@LEMNABFH@IDirect3DDevice8_SetVertexData2s@ (0000)
002913B8 007c:
	??_C@_0HM@GLDLNKPG@IDirect3DDevice8_SetVertexData2f@ (0000)
00291434 003d:
	??_C@_0DN@LFAPGLGA@IDirect3DDevice8_SetVertexData2s@ (0000)
00291478 007c:
	??_C@_0HM@LGJJHNDB@IDirect3DDevice8_SetVertexData2f@ (0000)
002914F4 003d:
	??_C@_0DN@HOFDLIMF@IDirect3DDevice8_SetVertexData2s@ (0000)
00291534 003d:
	??_C@_0DN@POLEKNHJ@IDirect3DDevice8_Begin?$CIglobal_d3@ (0000)
00291578 0045:
	??_C@_0EF@CFFLNGMH@secondary_target?$DO?$DN0?5?$CG?$CG?5secondary@ (0000)
002915C0 0041:
	??_C@_0EB@GKNGOOIJ@primary_target?$DO?$DN0?5?$CG?$CG?5primary_tar@ (0000)
00291604 002a:
	??_C@_0CK@FKCHNKBL@?$CD?$CD?$CD?5ERROR?5rasterizer_sun_glow_dr@ (0000)
00291630 005f:
	??_C@_0FP@CKNMNDPB@IDirect3DDevice8_SetVertexData2f@ (0000)
00291690 005f:
	??_C@_0FP@LJNHCKOE@IDirect3DDevice8_SetVertexData2f@ (0000)
002916F0 005f:
	??_C@_0FP@JAOANEPA@IDirect3DDevice8_SetVertexData2f@ (0000)
00291750 005f:
	??_C@_0FP@DOLCNOF@IDirect3DDevice8_SetVertexData2f@ (0000)
002917B0 0066:
	??_C@_0GG@GCMGACEI@IDirect3DDevice8_SetVertexData4f@ (0000)
*/

/* ---------- headers */

#include "cseries.h"
#include "cseries_windows.h"
#include "errors.h"
#include "real_math.h"
#include "rasterizer.h"
#include "xbox/rasterizer_xbox.h"
#include "tag_groups.h"
#include "game_globals.h"
#include "light_definitions.h"

/* ---------- constants */

enum
{
	SUN_GLOW_CONVOLVE_PASSES = 4,
	SUN_GLOW_DRAW_PASSES = 16,
};

#define VSDE_VERTEX 0

#define SUN_GLOW_SIZE 32.0f

/* ---------- macros */

/* ---------- structures */

/* ---------- prototypes */

real_vector3d uncompress_int32_to_real_vector3d(unsigned long compressed);

void rasterizer_set_target(short target, short mipmap_index, unsigned long background_color, boolean clear, boolean zbuffer);
void *rasterizer_set_target_as_texture(short stage, short target, short max_mipmap);
void rasterizer_set_texture_direct(short stage, long bitmap_tag_index, short bitmap_index);
void rasterizer_set_vertex_shader_permutation(long vertex_shader, long permutation, short type);
void rasterizer_set_pixel_shader(D3DPIXELSHADERDEF *pixel_shader_definition);
void SetRenderStateSmart(D3DRENDERSTATETYPE state, unsigned long value);

void rasterizer_sun_glow_draw(struct rasterizer_lens_flare_submit_parameters const *flare);

static boolean rasterizer_project_billboard(real_point3d const *point, real radius, real_point3d *projected_center, real_vector2d *projected_axes);
static void rasterizer_sun_glow_copy_source(short target, real_rectangle2d const *bounds);
static short rasterizer_sun_glow_convolve(short primary_target, short secondary_target, short passes);

/* ---------- globals */

extern struct rasterizer_window_begin_parameters global_window_parameters;
extern struct game_globals_rasterizer_data *global_rasterizer_data;
extern D3DPIXELSHADERDEF pixel_shader;

/* ---------- private code */

static boolean rasterizer_project_billboard(
	real_point3d const *point,
	real radius,
	real_point3d *projected_center,
	real_vector2d *projected_axes)
{
	boolean valid = FALSE;

	if (radius > 0.0f)
	{
		short width = global_window_parameters.camera.viewport_bounds.x1 - global_window_parameters.camera.viewport_bounds.x0;
		short height = global_window_parameters.camera.viewport_bounds.y1 - global_window_parameters.camera.viewport_bounds.y0;
		real_point3d p_view;
		real x, y, z, w;
		real axis_x, axis_y;

		matrix4x3_transform_point(&global_window_parameters.frustum.world_to_view, point, &p_view);
		x = global_window_parameters.frustum.projection_matrix[0][0]*p_view.x + global_window_parameters.frustum.projection_matrix[1][0]*p_view.y + global_window_parameters.frustum.projection_matrix[2][0]*p_view.z + global_window_parameters.frustum.projection_matrix[3][0];
		y = global_window_parameters.frustum.projection_matrix[0][1]*p_view.x + global_window_parameters.frustum.projection_matrix[1][1]*p_view.y + global_window_parameters.frustum.projection_matrix[2][1]*p_view.z + global_window_parameters.frustum.projection_matrix[3][1];
		z = global_window_parameters.frustum.projection_matrix[0][2]*p_view.x + global_window_parameters.frustum.projection_matrix[1][2]*p_view.y + global_window_parameters.frustum.projection_matrix[2][2]*p_view.z + global_window_parameters.frustum.projection_matrix[3][2];
		w = global_window_parameters.frustum.projection_matrix[0][3]*p_view.x + global_window_parameters.frustum.projection_matrix[1][3]*p_view.y + global_window_parameters.frustum.projection_matrix[2][3]*p_view.z + global_window_parameters.frustum.projection_matrix[3][3];
		axis_x = global_window_parameters.frustum.projection_matrix[0][0]*radius;
		axis_y = global_window_parameters.frustum.projection_matrix[1][1]*radius;

		if (z > 0.0f)
		{
			real one_over_w = 1.0f / w;

			projected_center->x = ((x*one_over_w + 1.0f)*width - 1.0f)*0.5f;
			projected_center->y = ((1.0f - one_over_w*y)*height - 1.0f)*0.5f;
			projected_center->z = MIN(1.0f, one_over_w*z);
			projected_axes->i = width*one_over_w*axis_x*0.5f;
			projected_axes->j = height*one_over_w*axis_y*0.5f;
			valid = TRUE;
		}
	}

	return valid;
}

static void rasterizer_sun_glow_copy_source(
	short target,
	real_rectangle2d const *bounds)
{
	float vsh_constants__texanim[32];
	real scale = 0.015625f;
	real mysterious_horizontal_offset = -0.03125f;

	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_lights.c", 323, bounds);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_lights.c", 324, global_d3d_device);

	rasterizer_set_target_as_texture(0, 0, 0);
	IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
	IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
	IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
	IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
	IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MIPFILTER, D3DTEXF_POINT);
	rasterizer_set_texture_direct(1, global_rasterizer_data->glow.index, 0);
	IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
	IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
	IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
	IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
	IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);
	IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_CCW);
	IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_ALL);
	IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHABLENDENABLE, FALSE);
	IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHATESTENABLE, FALSE);
	IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZENABLE, FALSE);
	IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZBIAS, 0);
	rasterizer_set_vertex_shader_permutation(38, 8, 0);

	vsh_constants__texanim[0] = bounds->x1 - bounds->x0;
	vsh_constants__texanim[1] = 0.0f;
	vsh_constants__texanim[2] = 0.0f;
	vsh_constants__texanim[3] = bounds->x0;
	vsh_constants__texanim[4] = 0.0f;
	vsh_constants__texanim[5] = bounds->y1 - bounds->y0;
	vsh_constants__texanim[6] = 0.0f;
	vsh_constants__texanim[7] = bounds->y0;
	vsh_constants__texanim[8] = 1.0f;
	vsh_constants__texanim[9] = 0.0f;
	vsh_constants__texanim[10] = 0.0f;
	vsh_constants__texanim[11] = 0.0f;
	vsh_constants__texanim[12] = 0.0f;
	vsh_constants__texanim[13] = 1.0f;
	vsh_constants__texanim[14] = 0.0f;
	vsh_constants__texanim[15] = 0.0f;
	vsh_constants__texanim[16] = 1.0f;
	vsh_constants__texanim[17] = 0.0f;
	vsh_constants__texanim[18] = 0.0f;
	vsh_constants__texanim[19] = 0.0f;
	vsh_constants__texanim[20] = 0.0f;
	vsh_constants__texanim[21] = 1.0f;
	vsh_constants__texanim[22] = 0.0f;
	vsh_constants__texanim[23] = 0.0f;
	vsh_constants__texanim[24] = 1.0f;
	vsh_constants__texanim[25] = 0.0f;
	vsh_constants__texanim[26] = 0.0f;
	vsh_constants__texanim[27] = 0.0f;
	vsh_constants__texanim[28] = 0.0f;
	vsh_constants__texanim[29] = 1.0f;
	vsh_constants__texanim[30] = 0.0f;
	vsh_constants__texanim[31] = 0.0f;
	IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, VSH_CONSTANTS__TEXANIM_OFFSET, vsh_constants__texanim, 8);

	csmemset(&pixel_shader, 0, sizeof(pixel_shader));
	pixel_shader.PSTextureModes = 0x21;
	pixel_shader.PSCombinerCount = 1;
	pixel_shader.PSConstant0[0] = 0xC0000000;
	pixel_shader.PSAlphaInputs[0] = 0x19110000;
	pixel_shader.PSAlphaOutputs[0] = 0x100C0;
	pixel_shader.PSFinalCombinerInputsABCD = 0x18;
	pixel_shader.PSFinalCombinerInputsEFG = 0x1C00;
	rasterizer_set_pixel_shader(&pixel_shader);

	rasterizer_set_target(target, 0, 0, FALSE, FALSE);
	IDirect3DDevice8_Begin(global_d3d_device, D3DPT_TRIANGLEFAN);
	IDirect3DDevice8_SetVertexData2s(global_d3d_device, 4, 0, 0);
	IDirect3DDevice8_SetVertexData2f(global_d3d_device, VSDE_VERTEX, scale - 1.0f + mysterious_horizontal_offset, scale + 1.0f);
	IDirect3DDevice8_SetVertexData2s(global_d3d_device, 4, 1, 0);
	IDirect3DDevice8_SetVertexData2f(global_d3d_device, VSDE_VERTEX, scale + 1.0f + mysterious_horizontal_offset, scale + 1.0f);
	IDirect3DDevice8_SetVertexData2s(global_d3d_device, 4, 1, 1);
	IDirect3DDevice8_SetVertexData2f(global_d3d_device, VSDE_VERTEX, scale + 1.0f + mysterious_horizontal_offset, scale - 1.0f);
	IDirect3DDevice8_SetVertexData2s(global_d3d_device, 4, 0, 1);
	IDirect3DDevice8_SetVertexData2f(global_d3d_device, VSDE_VERTEX, scale - 1.0f + mysterious_horizontal_offset, scale - 1.0f);
	IDirect3DDevice8_End(global_d3d_device);
	rasterizer_set_target(global_window_parameters.rasterizer_target, 0, 0, FALSE, TRUE);

	return;
}

static short rasterizer_sun_glow_convolve(
	short primary_target,
	short secondary_target,
	short passes)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_lights.c", 427, primary_target>=0 && primary_target<NUMBER_OF_RASTERIZER_TARGETS);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_lights.c", 428, secondary_target>=0 && secondary_target<NUMBER_OF_RASTERIZER_TARGETS);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_lights.c", 429, global_d3d_device);

	if (passes>0)
	{
		boolean success;
		short pass;
		real scale = 0.015625f;
		real mysterious_horizontal_offset = -0.03125f;

		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_CCW);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_BLUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHABLENDENABLE, TRUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_SRCBLEND, D3DBLEND_DESTALPHA);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_DESTBLEND, D3DBLEND_ZERO);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_BLENDOP, D3DBLENDOP_ADD);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHATESTENABLE, FALSE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZENABLE, FALSE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZBIAS, 0);
		rasterizer_set_vertex_shader_permutation(38, 8, 0);
		{
			float vsh_constants__texanim[32] =
			{
				1.0f, 0.0f, 0.0f, -0.0078125f,
				0.0f, 1.0f, 0.0f, -0.0078125f,
				1.0f, 0.0f, 0.0f, 0.0078125f,
				0.0f, 1.0f, 0.0f, 0.0078125f,
				1.0f, 0.0f, 0.0f, -0.0078125f,
				0.0f, 1.0f, 0.0f, 0.0078125f,
				1.0f, 0.0f, 0.0f, 0.0078125f,
				0.0f, 1.0f, 0.0f, -0.0078125f,
			};

			IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, VSH_CONSTANTS__TEXANIM_OFFSET, vsh_constants__texanim, 8);
		}

		success = TRUE;
		csmemset(&pixel_shader, 0, sizeof(pixel_shader));
		pixel_shader.PSTextureModes = 0x8421;
		pixel_shader.PSCombinerCount = 2;
		pixel_shader.PSConstant0[0] = 0xFF000000;
		pixel_shader.PSAlphaInputs[0] = 0x08A009A0;
		pixel_shader.PSAlphaOutputs[0] = 0xC00;
		pixel_shader.PSRGBInputs[0] = 0x0AA00BA0;
		pixel_shader.PSRGBOutputs[0] = 0xC00;
		pixel_shader.PSRGBInputs[1] = 0x1C110C11;
		pixel_shader.PSRGBOutputs[1] = 0xC00;
		pixel_shader.PSFinalCombinerInputsABCD = 0x0C;
		rasterizer_set_pixel_shader(&pixel_shader);

		for (pass = 0; pass<passes; pass++)
		{
			short source_target;
			short destination_target;
			short stage;

			source_target = (pass & 1) ? secondary_target : primary_target;
			destination_target = (pass & 1) ? primary_target : secondary_target;

			for (stage = 0; stage<4; stage++)
			{
				rasterizer_set_target_as_texture(stage, source_target, 0);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, stage, D3DTSS_ADDRESSU, D3DTADDRESS_BORDER);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, stage, D3DTSS_ADDRESSV, D3DTADDRESS_BORDER);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, stage, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, stage, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, stage, D3DTSS_MIPFILTER, D3DTEXF_POINT);
			}

			rasterizer_set_target(destination_target, 0, 0, FALSE, FALSE);
			pixel_shader.PSConstant0[0] = (pass>0 ? 0x7F : 0xFF)<<24;
			rasterizer_set_pixel_shader(&pixel_shader);
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
		if (!success)
		{
			error(2, "### ERROR rasterizer_sun_glow_convolve failed");
		}
	}

	return (passes & 1) ? secondary_target : primary_target;
}

/* ---------- public code */

// TODO: stack slot assignment differs (float temps / success not kept in bl); some x87 operand ordering
void rasterizer_sun_glow_draw(
	struct rasterizer_lens_flare_submit_parameters const *flare)
{
	real_vector3d eye_to_corona_vector;
	real brightness;

	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_lights.c", 583, global_d3d_device);

	vector_from_points3d(&global_window_parameters.camera.position, &flare->position, &eye_to_corona_vector);
	normalize3d(&eye_to_corona_vector);
	brightness = dot_product3d(&global_window_parameters.camera.forward, &eye_to_corona_vector);
	brightness = PIN((brightness - (real)cos(_pi/4.0f)) / (1.0f - (real)cos(_pi/4.0f)), 0.0f, 1.0f);

	{
		short width = global_window_parameters.camera.viewport_bounds.x1 - global_window_parameters.camera.viewport_bounds.x0;
		short height = global_window_parameters.camera.viewport_bounds.y1 - global_window_parameters.camera.viewport_bounds.y0;
		float vsh_constants__screenproj[5][4];

		vsh_constants__screenproj[0][0] = 2.0f / width;
		vsh_constants__screenproj[0][1] = 0.0f;
		vsh_constants__screenproj[0][2] = 0.0f;
		vsh_constants__screenproj[0][3] = -1.0f - 1.0f / width;
		vsh_constants__screenproj[1][0] = 0.0f;
		vsh_constants__screenproj[1][1] = -2.0f / height;
		vsh_constants__screenproj[1][2] = 0.0f;
		vsh_constants__screenproj[1][3] = 1.0f + 1.0f / height;
		vsh_constants__screenproj[2][0] = 0.0f;
		vsh_constants__screenproj[2][1] = 0.0f;
		vsh_constants__screenproj[2][2] = 1.0f;
		vsh_constants__screenproj[2][3] = 0.0f;
		vsh_constants__screenproj[3][0] = 0.0f;
		vsh_constants__screenproj[3][1] = 0.0f;
		vsh_constants__screenproj[3][2] = 0.0f;
		vsh_constants__screenproj[3][3] = 1.0f;
		vsh_constants__screenproj[4][0] = 0.0f;
		vsh_constants__screenproj[4][1] = 0.0f;
		vsh_constants__screenproj[4][2] = 0.0f;
		vsh_constants__screenproj[4][3] = 1.0f;
		IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, VSH_CONSTANTS__SCREENPROJ_OFFSET, vsh_constants__screenproj, 5);
	}

	{
		real_vector3d direction = uncompress_int32_to_real_vector3d(flare->compressed_direction);
		real_point3d position;
		real_point3d center;
		real_vector2d axes;

		point_from_line3d(&flare->position, &direction, flare->definition->occlusion_radius, &position);
		if (rasterizer_project_billboard(&position, flare->definition->occlusion_radius, &center, &axes))
		{
			real_rectangle2d bounds;
			real_rectangle2d screen_bounds;

			center.x = (real)floor(center.x + 0.5f);
			center.y = (real)floor(center.y + 0.5f);
			bounds.x0 = center.x - SUN_GLOW_SIZE;
			bounds.y0 = center.y - SUN_GLOW_SIZE;
			bounds.x1 = center.x + SUN_GLOW_SIZE;
			bounds.y1 = center.y + SUN_GLOW_SIZE;
			screen_bounds.x0 = bounds.x0 + global_window_parameters.camera.viewport_bounds.x0;
			screen_bounds.y0 = bounds.y0 + global_window_parameters.camera.viewport_bounds.y0;
			screen_bounds.x1 = bounds.x1 + global_window_parameters.camera.viewport_bounds.x0;
			screen_bounds.y1 = bounds.y1 + global_window_parameters.camera.viewport_bounds.y0;

			if (screen_bounds.x0 < global_window_parameters.camera.viewport_bounds.x1 &&
				screen_bounds.y0 < global_window_parameters.camera.viewport_bounds.y1 &&
				screen_bounds.x1 > global_window_parameters.camera.viewport_bounds.x0 &&
				screen_bounds.y1 > global_window_parameters.camera.viewport_bounds.y0)
			{
				boolean success = TRUE;
				short target;
				short num_passes = SUN_GLOW_DRAW_PASSES;
				short pass;

				// clear the destination alpha
				rasterizer_set_vertex_shader_permutation(56, 6, 0);
				IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_CCW);
				IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_ALPHA);
				IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHABLENDENABLE, FALSE);
				IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHATESTENABLE, FALSE);
				IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZENABLE, FALSE);
				IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZBIAS, 0);
				csmemset(&pixel_shader, 0, sizeof(pixel_shader));
				pixel_shader.PSCombinerCount = 1;
				pixel_shader.PSFinalCombinerConstant0 = 0;
				pixel_shader.PSFinalCombinerInputsEFG = 0x1100;
				rasterizer_set_pixel_shader(&pixel_shader);
				IDirect3DDevice8_Begin(global_d3d_device, D3DPT_TRIANGLEFAN);
				IDirect3DDevice8_SetVertexData2f(global_d3d_device, VSDE_VERTEX, bounds.x0, bounds.y0);
				IDirect3DDevice8_SetVertexData2f(global_d3d_device, VSDE_VERTEX, bounds.x1, bounds.y0);
				IDirect3DDevice8_SetVertexData2f(global_d3d_device, VSDE_VERTEX, bounds.x1, bounds.y1);
				IDirect3DDevice8_SetVertexData2f(global_d3d_device, VSDE_VERTEX, bounds.x0, bounds.y1);
				IDirect3DDevice8_End(global_d3d_device);

				// write the glow mask into destination alpha where the sun is visible
				rasterizer_set_vertex_shader_permutation(56, 6, 0);
				rasterizer_set_texture_direct(0, global_rasterizer_data->glow.index, 0);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);
				IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_CCW);
				IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_ALPHA);
				IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHABLENDENABLE, FALSE);
				IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHATESTENABLE, FALSE);
				IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZENABLE, TRUE);
				IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
				IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZWRITEENABLE, FALSE);
				IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZBIAS, 0);
				csmemset(&pixel_shader, 0, sizeof(pixel_shader));
				pixel_shader.PSTextureModes = 1;
				pixel_shader.PSCombinerCount = 1;
				pixel_shader.PSAlphaInputs[0] = 0x18200000;
				pixel_shader.PSAlphaOutputs[0] = 0x200C0;
				pixel_shader.PSFinalCombinerInputsEFG = 0x1C00;
				rasterizer_set_pixel_shader(&pixel_shader);
				IDirect3DDevice8_Begin(global_d3d_device, D3DPT_TRIANGLEFAN);
				IDirect3DDevice8_SetVertexData2s(global_d3d_device, 4, 0, 0);
				IDirect3DDevice8_SetVertexData4f(global_d3d_device, VSDE_VERTEX, bounds.x0, bounds.y0, center.z, 1.0f);
				IDirect3DDevice8_SetVertexData2s(global_d3d_device, 4, 1, 0);
				IDirect3DDevice8_SetVertexData4f(global_d3d_device, VSDE_VERTEX, bounds.x1, bounds.y0, center.z, 1.0f);
				IDirect3DDevice8_SetVertexData2s(global_d3d_device, 4, 1, 1);
				IDirect3DDevice8_SetVertexData4f(global_d3d_device, VSDE_VERTEX, bounds.x1, bounds.y1, center.z, 1.0f);
				IDirect3DDevice8_SetVertexData2s(global_d3d_device, 4, 0, 1);
				IDirect3DDevice8_SetVertexData4f(global_d3d_device, VSDE_VERTEX, bounds.x0, bounds.y1, center.z, 1.0f);
				IDirect3DDevice8_End(global_d3d_device);

				// blur it
				rasterizer_sun_glow_copy_source(_rasterizer_target_sun_glow_primary, &screen_bounds);
				rasterizer_sun_glow_copy_source(_rasterizer_target_sun_glow_secondary, &screen_bounds);
				target = rasterizer_sun_glow_convolve(_rasterizer_target_sun_glow_primary, _rasterizer_target_sun_glow_secondary, SUN_GLOW_CONVOLVE_PASSES);

				// draw the glow
				rasterizer_set_vertex_shader_permutation(56, 6, 0);
				rasterizer_set_target_as_texture(0, target, 0);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);
				IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_CCW);
				SetRenderStateSmart(D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_BLUE);
				SetRenderStateSmart(D3DRS_ALPHABLENDENABLE, TRUE);
				SetRenderStateSmart(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				SetRenderStateSmart(D3DRS_DESTBLEND, D3DBLEND_ONE);
				SetRenderStateSmart(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				SetRenderStateSmart(D3DRS_ALPHATESTENABLE, FALSE);
				SetRenderStateSmart(D3DRS_ZENABLE, FALSE);
				IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZBIAS, 0);
				csmemset(&pixel_shader, 0, sizeof(pixel_shader));
				pixel_shader.PSTextureModes = 1;
				pixel_shader.PSCombinerCount = 2;
				pixel_shader.PSConstant0[0] = 0x00B0B080;
				pixel_shader.PSConstant1[0] = 0x00FFFFFF;
				pixel_shader.PSAlphaInputs[0] = 0x48200000;
				pixel_shader.PSAlphaOutputs[0] = 0xC0;
				pixel_shader.PSRGBInputs[1] = 0x3C011C02;
				pixel_shader.PSRGBOutputs[1] = 0xC00;
				pixel_shader.PSFinalCombinerInputsABCD = 0x0C080000;
				pixel_shader.PSFinalCombinerInputsEFG = 0x1400;
				rasterizer_set_pixel_shader(&pixel_shader);

				for (pass = 0; pass<num_passes; pass++)
				{
					real r = ((real)pass / num_passes) * 80.0f - 4.0f;

					D3DCALL(success, IDirect3DDevice8_Begin(global_d3d_device, D3DPT_TRIANGLEFAN));
					D3DCALL(success, IDirect3DDevice8_SetVertexData4f(global_d3d_device, 9, 0.0f, 0.0f, 0.0f, brightness/(real)(pass + 1)));
					D3DCALL(success, IDirect3DDevice8_SetVertexData2s(global_d3d_device, 4, 0, 0));
					D3DCALL(success, IDirect3DDevice8_SetVertexData2f(global_d3d_device, VSDE_VERTEX, bounds.x0 - r, bounds.y0 - r));
					D3DCALL(success, IDirect3DDevice8_SetVertexData2s(global_d3d_device, 4, 1, 0));
					D3DCALL(success, IDirect3DDevice8_SetVertexData2f(global_d3d_device, VSDE_VERTEX, bounds.x1 + r, bounds.y0 - r));
					D3DCALL(success, IDirect3DDevice8_SetVertexData2s(global_d3d_device, 4, 1, 1));
					D3DCALL(success, IDirect3DDevice8_SetVertexData2f(global_d3d_device, VSDE_VERTEX, bounds.x1 + r, bounds.y1 + r));
					D3DCALL(success, IDirect3DDevice8_SetVertexData2s(global_d3d_device, 4, 0, 1));
					D3DCALL(success, IDirect3DDevice8_SetVertexData2f(global_d3d_device, VSDE_VERTEX, bounds.x0 - r, bounds.y1 + r));
					D3DCALL(success, IDirect3DDevice8_End(global_d3d_device));
				}

				if (!success)
				{
					error(2, "### ERROR rasterizer_sun_glow_draw failed");
				}
			}
		}
	}

	return;
}
