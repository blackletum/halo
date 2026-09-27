/*
RASTERIZER_XBOX_DECALS.C

symbols in this file:
0014A5F0 01b0:
	_D3DDevice_SetRenderState (0000)
0014A7A0 0050:
	_D3DDevice_SetTextureStageState (0000)
0014A7F0 0120:
	_rasterizer_decal_vertices_purge_proc (0000)
0014A910 0090:
	_rasterizer_decal_vertices_locked_proc (0000)
0014A9A0 0040:
	__rasterizer_decals_update_function_pointers (0000)
0014A9E0 0220:
	_IDirect3DDevice8_SetRenderState@12 (0000)
0014AC00 0010:
	__rasterizer_decals_initialize_for_new_map (0000)
0014AC10 0040:
	__rasterizer_decals_dispose_from_old_map (0000)
0014AC50 0040:
	__rasterizer_decals_flush (0000)
0014AC90 0010:
	_rasterizer_decal_vertices_begin_update (0000)
0014ACA0 0010:
	_rasterizer_decal_vertices_end_update (0000)
0014ACB0 0070:
	__rasterizer_decal_vertices_new (0000)
0014AD20 0060:
	_IDirect3DDevice8_SetTextureStageState@16 (0000)
0014AD80 0030:
	_IDirect3DDevice8_DrawPrimitive@16 (0000)
0014ADB0 0070:
	__rasterizer_decal_vertices_delete (0000)
0014AE20 0010:
	_IDirect3DDevice8_SetStreamSource@16 (0000)
0014AE30 0070:
	__rasterizer_decals_end (0000)
0014AEA0 0020:
	_IDirect3DDevice8_SetVertexData4ub@24 (0000)
0014AEC0 0010:
	_D3DVertexBuffer_Unlock@4 (0000)
0014AED0 0010:
	_IDirect3DVertexBuffer8_Release@4 (0000)
0014AEE0 0010:
	_IDirect3DVertexBuffer8_Register@8 (0000)
0014AEF0 0020:
	_IDirect3DVertexBuffer8_Lock@20 (0000)
0014AF10 0010:
	_IDirect3DVertexBuffer8_Unlock@4 (0000)
0014AF20 0110:
	__rasterizer_decals_initialize (0000)
0014B030 00b0:
	__rasterizer_decals_dispose (0000)
0014B0E0 00d0:
	__rasterizer_decal_vertices_lock (0000)
0014B1B0 0010:
	__rasterizer_decal_vertices_unlock (0000)
0014B1C0 02d0:
	__rasterizer_decals_begin (0000)
0014B490 0350:
	__rasterizer_decals_draw (0000)
0028DD18 0058:
	_D3DPRIMITIVETOVERTEXCOUNT (0000)
0028DD70 0012:
	??_C@_0BC@JENGFNKJ@decal_index?$CB?$DNNONE?$AA@ (0000)
0028DD88 005d:
	??_C@_0FN@KMDPMKOA@?$CD?$CD?$CD?5ERROR?5decals?3?5deleting?5perma@ (0000)
0028DDE8 005a:
	??_C@_0FK@BJHCLOEJ@?$CD?$CD?$CD?5ERROR?5decals?3?5deleting?5locke@ (0000)
0028DE44 000f:
	??_C@_0P@MKLHCCBN@decal_index?$CB?$DN0?$AA@ (0000)
0028DE54 000c:
	??_C@_0M@LJKLFPHM@decal_index?$AA@ (0000)
0028DE60 0029:
	??_C@_0CJ@FLPDNPAK@lruv_has_locked_proc?$CIlocal_verte@ (0000)
0028DE8C 0038:
	??_C@_0DI@DFPBIFJA@c?3?2halo?2SOURCE?2rasterizer?2xbox?2r@ (0000)
0028DEC4 0013:
	??_C@_0BD@GMDLIMJM@local_vertex_cache?$AA@ (0000)
0028DED8 002a:
	??_C@_0CK@DKKOCKIP@cache_size?$CFsizeof?$CIstruct?5decal_v@ (0000)
0028DF04 0027:
	??_C@_0CH@FLDEKCGM@cache_size?$DOsizeof?$CIstruct?5decal_v@ (0000)
0028DF2C 0012:
	??_C@_0BC@NONEJICN@cache_index?$CB?$DNNONE?$AA@ (0000)
0028DF40 0013:
	??_C@_0BD@NBMEPDOH@decal?5vertex?5cache?$AA@ (0000)
0028DF54 001e:
	??_C@_0BO@OHOOIFNI@local_d3d_vertex_buffer?9?$DOData?$AA@ (0000)
0028DF74 000f:
	??_C@_0P@PKAEFIHO@decal?5vertices?$AA@ (0000)
0028DF84 0018:
	??_C@_0BI@PCGDDGMG@local_d3d_vertex_buffer?$AA@ (0000)
0028DF9C 0032:
	??_C@_0DC@BMDAFKAI@vertex_data_offset?$CFsizeof?$CIstruct@ (0000)
0028DFD0 0022:
	??_C@_0CC@GHCFEIDO@intensity?$DM?$DNPIXEL32_COMPONENT_MAS@ (0000)
0028DFF4 0031:
	??_C@_0DB@GLODBMEM@?$CD?$CD?$CD?5ERROR?5unsupported?5framebuffe@ (0000)
0030CEF4 0004:
	_last_decal_index_queried_by_lruv_cache (0000)
0045E8E8 0002:
	_local_layer (0000)
0045E8EC 0004:
	_bss_0045e8ec (0000)
0045E8F0 0002:
	_bss_0045e8f0 (0000)
0045E8F4 0002:
	_local_framebuffer_blend_function (0000)
0045E8F8 0004:
	_local_d3d_vertex_buffer (0000)
0045E8FC 0004:
	_local_vertex_cache (0000)
0045E900 0001:
	_bss_0045e900 (0000)
0045E901 0001:
	_bss_0045e901 (0000)
0045E902 0001:
	_local_filthy_decal_fog_hack_enabled (0000)
*/

/* ---------- headers */

#include "cseries.h"
#include "cseries_windows.h"
#include "errors.h"
#include "real_math.h"
#include "data.h"
#include "tag_groups.h"
#include "game_state.h"
#include "rasterizer.h"
#include "rasterizer_geometry.h"
#include "xbox/rasterizer_xbox.h"
#include "shaders/shader_definitions.h"
#include "effects/decal_definitions.h"
#include "effects/decals.h"

/* ---------- constants */

enum
{
	_decal_layer_primary = 0,
	_decal_layer_secondary,
	_decal_layer_light,
	_decal_layer_alpha_tested,
	_decal_layer_water,
	NUMBER_OF_DECAL_LAYERS
};

enum
{
	_decal_locked_bit = 0,
	_decal_permanent_bit,
};

enum
{
	_framebuffer_blend_function_alpha_blend = 0,
	_framebuffer_blend_function_multiply,
	_framebuffer_blend_function_double_multiply,
	_framebuffer_blend_function_add,
	_framebuffer_blend_function_subtract,
	_framebuffer_blend_function_component_min,
	_framebuffer_blend_function_component_max,
	_framebuffer_blend_function_alpha_multiply_add,
	NUMBER_OF_FRAMEBUFFER_BLEND_FUNCTIONS
};

enum
{
	DECAL_VERTEX_BUFFER_SIZE = 0x28000,
	DECAL_VERTEX_CACHE_PAGE_COUNT = 0xa00,
	DECAL_VERTEX_CACHE_PAGE_SIZE_BITS = 6,
	DECAL_VERTEX_CACHE_MAXIMUM_BLOCK_COUNT = 0x800,
};

#define PIXEL32_COMPONENT_MASK 0xff

/* ---------- prototypes */

void *datum_get(struct data_array *data, long index);

long decal_get_first_decal_index(short cluster_index, short layer);
void decal_delete(long decal_index);
void decals_unlock(boolean permanent);

void lruv_update_function_pointers(struct lruv_cache *cache, void (*delete_block_proc)(long), boolean (*locked_block_proc)(long));
boolean lruv_has_locked_proc(struct lruv_cache *cache);
void lruv_idle(struct lruv_cache *cache);
void lruv_flush(struct lruv_cache *cache);
void lruv_delete(struct lruv_cache *cache);
long lruv_block_new(struct lruv_cache *cache, long size);
void lruv_block_delete(struct lruv_cache *cache, long block_index);
long lruv_block_get_address(struct lruv_cache *cache, long block_index);

void *rasterizer_set_texture(short stage, short type, short usage, long bitmap_group_index, short bitmap_index);
void rasterizer_set_stencil_mode(short stencil_mode);
void rasterizer_set_vertex_shader_permutation(short vertex_shader, short vertex_type, short permutation);
void rasterizer_set_pixel_shader(D3DPIXELSHADERDEF *pixel_shader);
void rasterizer_set_framebuffer_blend_function(short framebuffer_blend_function);

static void rasterizer_decal_vertices_purge_proc(long decal_index);
static boolean rasterizer_decal_vertices_locked_proc(long decal_index);

/* ---------- globals */

extern struct data_array *global_decal_data;
extern struct rasterizer_window_begin_parameters global_window_parameters;
extern D3DPIXELSHADERDEF pixel_shader;

static long last_decal_index_queried_by_lruv_cache = NONE; // last_decal_index_queried_by_lruv_cache (hcex)

// comm. statics in target address order (0045e8e8..0045e902). names from hcex where it has them;
// bitmap_group_index (0045e8ec), bitmap_index (0045e8f0) and the locked/permanent warning flags (0045e900/0045e901)
// have no known name (hcex stubs out their users), so they keep address placeholders.
static short local_layer;
static long bss_0045e8ec;
static short bss_0045e8f0;
static short local_framebuffer_blend_function;
static IDirect3DVertexBuffer8 *local_d3d_vertex_buffer;
static struct lruv_cache *local_vertex_cache;
static boolean bss_0045e900;
static boolean bss_0045e901;
static boolean local_filthy_decal_fog_hack_enabled;

/* ---------- private code */

// comm. the _code_0014a5f0/_code_0014a7a0/_code_0014a9e0/_code_0014ad20..._code_0014af10 symbols are the unreferenced
// out-of-line copies of the D3DINLINE functions from D3D8.h that the compiler emits (D3DDevice_SetRenderState etc.)

// rasterizer_decal_vertices_purge_proc (hcex)
static void rasterizer_decal_vertices_purge_proc(
	long decal_index)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_decals.c", 29, lruv_has_locked_proc(local_vertex_cache));
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_decals.c", 30, decal_index);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_decals.c", 31, decal_index!=NONE);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_decals.c", 32, decal_index!=0);

	if (TEST_FLAG(((struct decal_datum *)datum_get(global_decal_data, decal_index))->flags, _decal_locked_bit) && !bss_0045e900)
	{
		error(_error_silent, "### ERROR decals: deleting locked decal (#%d, queried=#%d) in rasterizer -- tell Bernie!!", decal_index, last_decal_index_queried_by_lruv_cache);
		bss_0045e900 = TRUE;
	}
	if (TEST_FLAG(((struct decal_datum *)datum_get(global_decal_data, decal_index))->flags, _decal_permanent_bit) && !bss_0045e901)
	{
		error(_error_silent, "### ERROR decals: deleting permanent decal (#%d, queried=#%d) in rasterizer -- tell Bernie!!", decal_index, last_decal_index_queried_by_lruv_cache);
		bss_0045e901 = TRUE;
	}

	decal_delete(decal_index);

	return;
}

// rasterizer_decal_vertices_locked_proc (hcex)
static boolean rasterizer_decal_vertices_locked_proc(
	long decal_index)
{
	struct decal_datum *decal;
	boolean locked;

	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_decals.c", 71, decal_index);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_decals.c", 72, decal_index!=NONE);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_decals.c", 73, decal_index!=0);

	decal = datum_get(global_decal_data, decal_index);
	locked = (TEST_FLAG(decal->flags, _decal_locked_bit) || TEST_FLAG(decal->flags, _decal_permanent_bit)) ? TRUE : FALSE;
	last_decal_index_queried_by_lruv_cache = decal_index;

	return locked;
}

/* ---------- public code */

void _rasterizer_decals_initialize(
	void)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_decals.c", 89, global_d3d_device);

	local_d3d_vertex_buffer = match_malloc("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_decals.c", 91, sizeof(IDirect3DVertexBuffer8));
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_decals.c", 92, local_d3d_vertex_buffer);

	local_d3d_vertex_buffer->Common = 1;
	local_d3d_vertex_buffer->Data = (DWORD)game_state_gpu_malloc("decal vertices", NULL, DECAL_VERTEX_BUFFER_SIZE);
	local_d3d_vertex_buffer->Lock = 0;
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_decals.c", 96, local_d3d_vertex_buffer->Data);

	IDirect3DVertexBuffer8_Register(local_d3d_vertex_buffer, NULL);

	local_vertex_cache = game_state_lruv_cache_new("decal vertex cache",
		DECAL_VERTEX_CACHE_PAGE_COUNT,
		DECAL_VERTEX_CACHE_PAGE_SIZE_BITS,
		DECAL_VERTEX_CACHE_MAXIMUM_BLOCK_COUNT,
		rasterizer_decal_vertices_purge_proc,
		rasterizer_decal_vertices_locked_proc);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_decals.c", 106, local_vertex_cache);

	return;
}

void _rasterizer_decals_update_function_pointers(
	void)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_decals.c", 116, local_vertex_cache);
	lruv_update_function_pointers(local_vertex_cache, rasterizer_decal_vertices_purge_proc, rasterizer_decal_vertices_locked_proc);

	return;
}

void _rasterizer_decals_initialize_for_new_map(
	void)
{
	return;
}

void _rasterizer_decals_dispose_from_old_map(
	void)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_decals.c", 131, local_vertex_cache);
	decals_unlock(TRUE);
	lruv_flush(local_vertex_cache);

	return;
}

void _rasterizer_decals_flush(
	void)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_decals.c", 142, local_vertex_cache);
	decals_unlock(FALSE);
	lruv_flush(local_vertex_cache);

	return;
}

void _rasterizer_decals_dispose(
	void)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_decals.c", 153, local_vertex_cache);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_decals.c", 154, local_d3d_vertex_buffer);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_decals.c", 155, global_d3d_device);

	if (local_d3d_vertex_buffer)
	{
		IDirect3DVertexBuffer8_Release(local_d3d_vertex_buffer);
		local_d3d_vertex_buffer = NULL;
	}
	lruv_delete(local_vertex_cache);

	return;
}

void rasterizer_decal_vertices_begin_update(
	void)
{
	lruv_idle(local_vertex_cache);

	return;
}

void rasterizer_decal_vertices_end_update(
	void)
{
	return;
}

long _rasterizer_decal_vertices_new(
	long cache_size)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_decals.c", 204, cache_size>sizeof(struct decal_vertex));
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_decals.c", 205, cache_size%sizeof(struct decal_vertex)==0);

	return lruv_block_new(local_vertex_cache, cache_size);
}

void *_rasterizer_decal_vertices_lock(
	long cache_index,
	long cache_size)
{
	BYTE *vertices = NULL;
	long vertex_data_offset;

	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_decals.c", 217, cache_index!=NONE);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_decals.c", 218, local_vertex_cache);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_decals.c", 219, global_d3d_device);

	vertex_data_offset = lruv_block_get_address(local_vertex_cache, cache_index);
	rasterizer_globals.current_lock_operation = _rasterizer_lock_decal_vertices;
	IDirect3DVertexBuffer8_Lock(local_d3d_vertex_buffer, vertex_data_offset, cache_size, &vertices, D3DLOCK_READONLY);
	rasterizer_globals.current_lock_operation = _rasterizer_lock_none;

	return vertices;
}

void _rasterizer_decal_vertices_unlock(
	void)
{
	IDirect3DVertexBuffer8_Unlock(local_d3d_vertex_buffer);

	return;
}

void _rasterizer_decal_vertices_delete(
	long cache_index)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_decals.c", 262, cache_index!=NONE);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_decals.c", 263, local_vertex_cache);

	lruv_block_delete(local_vertex_cache, cache_index);

	return;
}

void _rasterizer_decals_begin(
	short layer)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_decals.c", 283, global_d3d_device);

	{
		short profile_types[NUMBER_OF_DECAL_LAYERS]=
		{
			_rasterizer_profile_environment_decals_primary,
			_rasterizer_profile_environment_decals_secondary,
			_rasterizer_profile_environment_decals_light,
			_rasterizer_profile_environment_decals_alpha_tested,
			_rasterizer_profile_environment_decals_water
		};

		if (layer>=0 && layer<NUMBER_OF_DECAL_LAYERS)
		{
			rasterizer_profile_begin(profile_types[layer]);
		}
	}

	local_layer = layer;

	if (!rasterizer_debug_options.drawing_mode && rasterizer_debug_options.draw_environment_decals)
	{
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_decals.c", 307, layer>=0 && layer<NUMBER_OF_DECAL_LAYERS);

		local_framebuffer_blend_function = NONE;
		bss_0045e8f0 = NONE;
		bss_0045e8ec = NONE;
		local_filthy_decal_fog_hack_enabled = FALSE;

		rasterizer_set_texture(0, 0, 1, NONE, 0);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);

		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_CCW);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHABLENDENABLE, TRUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZENABLE, D3DZB_TRUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZWRITEENABLE, FALSE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZBIAS, *(DWORD *)&rasterizer_debug_options.zbias);

		if (layer==_decal_layer_alpha_tested)
		{
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHATESTENABLE, TRUE);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHAREF, 0x7f);
			rasterizer_set_stencil_mode(_rasterizer_stencil_mode_write_alpha_tested_decal);
		}
		else
		{
			if (rasterizer_debug_options.filthy_decal_fog_hack_enabled && global_window_parameters.fog.atmospheric_maximum_density==1.f)
			{
				local_filthy_decal_fog_hack_enabled = TRUE;
			}

			if (local_filthy_decal_fog_hack_enabled)
			{
				IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHATESTENABLE, TRUE);
				IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHAREF, 0);
			}
			else
			{
				IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHATESTENABLE, FALSE);
			}
		}

		rasterizer_set_vertex_shader_permutation(1, 10, 0);

		memset(&pixel_shader, 0, sizeof(pixel_shader));
		pixel_shader.PSTextureModes = 1;
		pixel_shader.PSRGBOutputs[0] = 0xc00;
		pixel_shader.PSAlphaOutputs[1] = 0xc00;
		pixel_shader.PSRGBOutputs[1] = 0xc00;
		if (local_filthy_decal_fog_hack_enabled)
		{
			pixel_shader.PSCombinerCount = 3;
			pixel_shader.PSConstant0[0] = 0x1000000;
			pixel_shader.PSAlphaInputs[2] = 0x1c151115;
			pixel_shader.PSAlphaOutputs[2] = 0xc00;
		}
		else
		{
			pixel_shader.PSCombinerCount = 2;
		}
		pixel_shader.PSFinalCombinerInputsABCD = 0xc;
		pixel_shader.PSFinalCombinerInputsEFG = 0x1c00;

		IDirect3DDevice8_SetStreamSource(global_d3d_device, 0, local_d3d_vertex_buffer, sizeof(struct decal_vertex));
	}

	return;
}

// comm. matches; objdiff only disagrees on the switch jump table relocations ($L labels vs function-relative)
void _rasterizer_decals_draw(
	short cluster_index)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_decals.c", 408, global_d3d_device);

	if (!rasterizer_debug_options.drawing_mode && rasterizer_debug_options.draw_environment_decals)
	{
		struct decal_datum *decal;
		long decal_index;

		for (decal_index = decal_get_first_decal_index(cluster_index, local_layer); decal_index!=NONE; decal_index = decal->next_decal_index)
		{
			struct decal_definition *definition;
			struct _shader_decal *shader;
			unsigned long vertex_data_offset;
			unsigned long intensity;
			unsigned long color;

			decal = datum_get(global_decal_data, decal_index);
			definition = tag_get(DECAL_DEFINITION_TAG, decal->definition_index);
			shader = &definition->shader.decal;

			if (local_framebuffer_blend_function!=shader->framebuffer_blend_function)
			{
				local_framebuffer_blend_function = shader->framebuffer_blend_function;

				if (local_framebuffer_blend_function==_framebuffer_blend_function_multiply ||
					local_framebuffer_blend_function==_framebuffer_blend_function_double_multiply)
				{
					IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_ALL);
				}
				else
				{
					IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED|D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_BLUE);
				}

				switch (local_framebuffer_blend_function)
				{
				case _framebuffer_blend_function_add:
				case _framebuffer_blend_function_subtract:
				case _framebuffer_blend_function_component_max:
					pixel_shader.PSRGBInputs[0] = 0x08040000;
					pixel_shader.PSRGBInputs[1] = 0x340c0000;
					break;
				case _framebuffer_blend_function_multiply:
				case _framebuffer_blend_function_component_min:
					pixel_shader.PSRGBInputs[0] = 0x28240820;
					pixel_shader.PSRGBInputs[1] = 0x340c1420;
					pixel_shader.PSAlphaInputs[1] = 0x341c1420;
					break;
				case _framebuffer_blend_function_double_multiply:
					pixel_shader.PSRGBInputs[0] = 0xa8240820;
					pixel_shader.PSRGBInputs[1] = 0x340c14a0;
					pixel_shader.PSAlphaInputs[1] = 0x341c14a0;
					break;
				case _framebuffer_blend_function_alpha_blend:
					pixel_shader.PSRGBInputs[0] = 0x08040000;
					pixel_shader.PSRGBInputs[1] = 0x200c0000;
					pixel_shader.PSAlphaInputs[1] = 0x34180000;
					break;
				case _framebuffer_blend_function_alpha_multiply_add:
					pixel_shader.PSRGBInputs[0] = 0x08040000;
					pixel_shader.PSRGBInputs[1] = 0x340c0000;
					pixel_shader.PSAlphaInputs[1] = 0x34180000;
					break;
				default:
					match_vassert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_decals.c", 470, FALSE, "### ERROR unsupported framebuffer blend function");
				}

				rasterizer_set_framebuffer_blend_function(local_framebuffer_blend_function);
				rasterizer_set_pixel_shader(&pixel_shader);

				if (rasterizer_debug_options.statistics_mode==2)
				{
					rasterizer_frame_statistics.decal_shader_count++;
				}
			}

			if (bss_0045e8ec!=shader->map.index || bss_0045e8f0!=decal->bitmap_index)
			{
				bss_0045e8ec = shader->map.index;
				bss_0045e8f0 = decal->bitmap_index;
				rasterizer_set_texture(0, 0, 1, bss_0045e8ec, bss_0045e8f0);

				if (rasterizer_debug_options.statistics_mode==2)
				{
					rasterizer_frame_statistics.decal_texture_count++;
				}
			}

			vertex_data_offset = lruv_block_get_address(local_vertex_cache, decal_index);
			color = decal->color;
			intensity = (decal->intensity*(color>>24)+(PIXEL32_COMPONENT_MASK>>1))>>8;
			match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_decals.c", 510, intensity<=PIXEL32_COMPONENT_MASK);
			match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_decals.c", 511, vertex_data_offset%sizeof(struct decal_vertex)==0);

			IDirect3DDevice8_SetVertexData4ub(global_d3d_device, D3DVSDE_TEXCOORD0,
				(BYTE)(color>>16),
				(BYTE)(color>>8),
				(BYTE)color,
				(BYTE)(PIXEL32_COMPONENT_MASK-intensity));
			IDirect3DDevice8_DrawPrimitive(global_d3d_device, D3DPT_QUADLIST, vertex_data_offset/sizeof(struct decal_vertex), decal->quad_count);

			if (rasterizer_debug_options.statistics_mode==2)
			{
				rasterizer_frame_statistics.decals.primitives++;
				rasterizer_frame_statistics.decals.triangles += 2*decal->quad_count;
				rasterizer_frame_statistics.decals.vertices += 4*decal->quad_count;
			}
		}
	}

	return;
}

void _rasterizer_decals_end(
	void)
{
	if (local_layer==_decal_layer_alpha_tested)
	{
		rasterizer_set_stencil_mode(_rasterizer_stencil_mode_reject);
	}

	{
		short profile_types[NUMBER_OF_DECAL_LAYERS]=
		{
			_rasterizer_profile_environment_decals_primary,
			_rasterizer_profile_environment_decals_secondary,
			_rasterizer_profile_environment_decals_light,
			_rasterizer_profile_environment_decals_alpha_tested,
			_rasterizer_profile_environment_decals_water
		};

		if (local_layer>=0 && local_layer<NUMBER_OF_DECAL_LAYERS)
		{
			rasterizer_profile_end(profile_types[local_layer]);
		}
	}

	return;
}
