/*
RASTERIZER_XBOX.C
*/

/* ---------- headers */

#include "cseries.h"
#include "cseries_windows.h"
#include <string.h>
#include "errors.h"
#include "real_math.h"
#include "bitmaps.h"
#include "tag_groups.h"
#include "game_globals.h"
#include "bitmaps/bitmap_group.h"
#include "objects/light_definitions.h"
#include "render.h"
#include "rasterizer.h"
#include "xbox/rasterizer_xbox.h"

/* ---------- constants */

#define RASTERIZER_XBOX_FILE "c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox.c"

enum
{
	_fog_definition_screen_effect_only_bit= 2
};

enum
{
	RASTERIZER_MAXIMUM_TEXTURE_STAGES = 4,
	RASTERIZER_TARGET_WATER_MAX_MIPMAP_LEVELS = 4,
	NUMBER_OF_SHADER_FRAMEBUFFER_BLEND_FUNCTIONS = 8,
};

/* ---------- structures */

struct rasterizer_fake_surface
{
	DWORD Common;
	DWORD Data;
	DWORD Lock;
	DWORD Format;
	DWORD Size;
};

struct rasterizer_window_globals
{
	long unknown0;
	long unknown4;
	HWND hWndPresentTarget;
};

/* ---------- prototypes */

boolean rasterizer_memory_pool_initialize(void);
boolean rasterizer_dynamic_geometry_initialize(void);
boolean rasterizer_transparent_geometry_initialize(void);
boolean rasterizer_vertex_shaders_initialize(void);
boolean rasterizer_debug_initialize(void);
boolean rasterizer_frame_statistics_initialize(void);
boolean rasterizer_text_cache_initialize(void);
boolean rasterizer_detail_objects_initialize(void);
boolean rasterizer_profile_initialize(void);
boolean rasterizer_environment_fog_screen_initialize(void);
void rasterizer_screen_effects_initialize(void);
void texture_cache_new(void);
void rasterizer_debug_begin(void);

void rasterizer_memory_pool_dispose(void);
void rasterizer_dynamic_geometry_dispose(void);
void rasterizer_transparent_geometry_dispose(void);
void rasterizer_vertex_shaders_dispose(void);
void rasterizer_debug_dispose(void);
void rasterizer_frame_statistics_dispose(void);
void rasterizer_text_cache_dispose(void);
void rasterizer_detail_objects_dispose(void);
void rasterizer_profile_dispose(void);
void rasterizer_environment_fog_screen_dispose(void);
void rasterizer_screen_effects_dispose(void);
void texture_cache_delete(void);

void rasterizer_profile_frame_end(void);
void rasterizer_frame_statistics_end(void);

void profile_texture_start(void);
void profile_texture_end(void);
void *_texture_cache_bitmap_get_hardware_format(struct bitmap_data *bitmap, boolean block, boolean load);
struct bitmap_data *bitmap_group_try_and_get_bitmap(long bitmap_group_index, short bitmap_index);
char *bitmap_type_get_string(short type);

void SetupSmartStates(void);
void render_camera_hack_frustum_z(struct render_frustum *frustum, real z_near, real z_far);
void SetRenderStateSmart(D3DRENDERSTATETYPE state, DWORD value);
void rasterizer_set_vertex_shader_permutation(short vertex_type, short vertex_shader, short permutation);
void rasterizer_set_pixel_shader(D3DPIXELSHADERDEF *pixel_shader);
void rasterizer_set_frustum_z(real z_near, real z_far);
void rasterizer_set_target(short target, short mipmap_index, D3DCOLOR clear_color, boolean clear, boolean zbuffer);
void rasterizer_set_target_as_texture(short stage, short target, short max_mipmap);
void rasterizer_secondary_render_target_debug(rectangle2d const *bounds);
void rasterizer_set_stencil_mode(short stencil_mode);
void rasterizer_window_set_fog(struct render_fog const *fog);
void rasterizer_memory_pool_begin(void);
void rasterizer_dynamic_geometry_begin(void);
void rasterizer_transparent_geometry_begin(void);
void rasterizer_environment_fog_screen_window_begin(void);
void rasterizer_lights_begin(void);
void rasterizer_water_set_visibility_for_window(boolean visible);
void rasterizer_active_camouflage_set_visibility(boolean visible);
void rasterizer_profile_window_begin(void);
void rasterizer_memory_pool_end(void);
void rasterizer_dynamic_geometry_end(void);
void rasterizer_transparent_geometry_end(void);
void rasterizer_environment_fog_screen_window_end(void);
void rasterizer_lights_end(void);
void rasterizer_debug_end(void);
void rasterizer_profile_window_end(void);
short main_get_window_count(void);
void rasterizer_frame_statistics_get_fps(struct rasterizer_frame_statistics *statistics);
void rasterizer_frame_statistics_draw(void);
void *bitmap_2d_address(struct bitmap_data const *bitmap, short x, short y, short mipmap_index);
real rasterizer_get_near_clip_distance(void);
void rasterizer_profile_frame_begin(void);
void rasterizer_frame_statistics_begin(void);
void rasterizer_water_set_visibility_for_frame(boolean visible);
void rasterizer_lights_begin_for_new_frame(void);
void texture_cache_idle(void);
void rasterizer_decal_vertices_begin_update(void);
void decals_update(void);
void rasterizer_decal_vertices_end_update(void);
pixel32 real_rgb_color_to_pixel32(real_rgb_color const *color);

static void rasterizer_filthy_bitmap_defaults_initialize(void); // rasterizer_filthy_bitmap_defaults_initialize

/* ---------- globals */

extern struct game_globals_rasterizer_data *global_rasterizer_data;
extern struct vertex_shader_table_entry vertex_shader_table[NUMBER_OF_VERTEX_SHADERS];
extern struct rasterizer_window_begin_parameters global_window_parameters;
extern D3DCAPS8 global_d3d_caps;
extern D3DPIXELSHADERDEF pixel_shader;
extern struct rasterizer_window_globals window_globals;
extern D3DCOLOR global_vector_palette[256];
extern boolean global_frame_rate_throttle;
extern DWORD renderstate_table[D3DRS_MAX];
extern DWORD texturestagestate_table[D3DTSS_MAXSTAGES][D3DTSS_MAX];
extern D3DBaseTexture *texture_table[D3DTSS_MAXSTAGES];

static short data_0030ceec= NONE;
static short previous_stencil_mode= NONE;

static real vsh_constants__nodematrices[RASTERIZER_MAXIMUM_NODES_PER_MODEL][12];
static Direct3D *d3d;
static D3DBaseTexture *bss_0045e874[2];
static D3DSurface *bss_0045e87c;
static D3DSurface *global_d3d_surface_render_primary_z;
static D3DTexture *global_d3d_texture_render_secondary;
static D3DTexture *bss_0045e888;
static D3DSurface *global_d3d_surface_render_secondary;
static D3DSurface *bss_0045e890;
static D3DTexture *global_d3d_texture_shadow_primary;
static D3DSurface *global_d3d_surface_shadow_primary;
static D3DTexture *global_d3d_texture_shadow_secondary;
static D3DSurface *global_d3d_surface_shadow_secondary;
static D3DTexture *global_d3d_texture_sun_glow_primary;
static D3DSurface *global_d3d_surface_sun_glow_primary;
static D3DTexture *global_d3d_texture_sun_glow_secondary;
static D3DSurface *global_d3d_surface_sun_glow_secondary;
static D3DTexture *global_d3d_texture_water;
static D3DSurface *global_d3d_surface_water[RASTERIZER_TARGET_WATER_MAX_MIPMAP_LEVELS];
static D3DSurface *bss_0045e8c8;
static D3DSurface *bss_0045e8cc;
IDirect3DDevice8 *global_d3d_device;
static D3DPalette *d3d_palette;
static boolean bss_0045e8d8;
static short bss_0045e8dc;

/* ---------- macros */

#define RASTERIZER_DEVICE_CREATION_FLAGS D3DCREATE_HARDWARE_VERTEXPROCESSING

#define RASTERIZER_TARGET_RENDER_SECONDARY_WIDTH 320
#define RASTERIZER_TARGET_RENDER_SECONDARY_HEIGHT 240
#define RASTERIZER_TARGET_WATER_SIZE 128
#define RASTERIZER_TARGET_SHADOW_PRIMARY_SIZE 128
#define RASTERIZER_TARGET_SHADOW_SECONDARY_SIZE 128
#define RASTERIZER_TARGET_SUN_GLOW_SIZE 64

#define RASTERIZER_FAKE_SURFACE_COMMON 0x00040001
#define RASTERIZER_FAKE_SURFACE_SIZE 0x271df27f
#define RASTERIZER_FAKE_SURFACE_FORMAT 0x11229

/* ---------- public code */

// TODO: the code_XXXXXXXX functions interleaved through this file are out-of-line copies of XDK D3D8.h
// inline wrappers (IDirect3DDevice8_*, D3DDevice_SetRenderState, ...) emitted by LTCG with custom
// register calling conventions (args in eax/ecx/edx, esi/edi). they are unreferenced in the original and
// cannot be reproduced without /GL, so they are only approximated here.

unsigned long code_001448f0(
	void)
{
	return 1;
}

unsigned long code_00144900(
	Direct3D *direct3d)
{
	return 1;
}

HRESULT code_00144910(
	Direct3D *direct3d,
	UINT adapter,
	D3DDEVTYPE device_type,
	void *unused,
	DWORD behavior_flags,
	D3DPRESENT_PARAMETERS *presentation_parameters,
	D3DDevice **returned_device)
{
	return Direct3D_CreateDevice(adapter, device_type, unused, behavior_flags, presentation_parameters, returned_device);
}

void code_00144930(
	void)
{
	return;
}

void code_00144940(
	void)
{
	return;
}

void code_00144950(
	D3DRENDERSTATETYPE state,
	DWORD *value)
{
	*value= D3D__RenderState[state];
}

void code_00144960(
	DWORD stage,
	D3DTEXTURESTAGESTATETYPE type,
	DWORD *value)
{
	*value= D3D__TextureState[stage][type];
}

void code_00144980(
	D3DRENDERSTATETYPE state,
	DWORD value)
{
	D3DDevice_SetRenderState(state, value);
}

void code_00144b30(
	DWORD stage,
	D3DTEXTURESTAGESTATETYPE type,
	DWORD value)
{
	D3DDevice_SetTextureStageState(stage, type, value);
}

unsigned long code_00144b80(
	D3DDevice *device)
{
	return D3DDevice_Release();
}

HRESULT code_00144b90(
	D3DDevice *device,
	D3DCAPS8 *caps)
{
	D3DDevice_GetDeviceCaps(caps);
	return S_OK;
}

HRESULT code_00144ba0(
	D3DDevice *device,
	CONST RECT *source_rect,
	CONST RECT *dest_rect,
	void *unused,
	void *unused2)
{
	D3DDevice_Present(source_rect, dest_rect, unused, unused2);
	return S_OK;
}

HRESULT code_00144bc0(
	D3DDevice *device,
	INT back_buffer,
	D3DBACKBUFFER_TYPE type,
	D3DSurface **back_buffer_surface)
{
	D3DDevice_GetBackBuffer(back_buffer, type, back_buffer_surface);
	return S_OK;
}

HRESULT code_00144bd0(
	D3DDevice *device,
	UINT width,
	UINT height,
	UINT levels,
	DWORD usage,
	D3DFORMAT format,
	D3DPOOL pool,
	D3DTexture **texture)
{
	return D3DDevice_CreateTexture(width, height, levels, usage, format, pool, texture);
}

HRESULT code_00144bf0(
	D3DDevice *device,
	UINT width,
	UINT height,
	UINT depth,
	UINT levels,
	DWORD usage,
	D3DFORMAT format,
	D3DPOOL pool,
	D3DVolumeTexture **volume_texture)
{
	return D3DDevice_CreateVolumeTexture(width, height, depth, levels, usage, format, pool, volume_texture);
}

HRESULT code_00144c20(
	D3DDevice *device,
	UINT edge_length,
	UINT levels,
	DWORD usage,
	D3DFORMAT format,
	D3DPOOL pool,
	D3DCubeTexture **cube_texture)
{
	return D3DDevice_CreateCubeTexture(edge_length, levels, usage, format, pool, cube_texture);
}

HRESULT code_00144c40(
	D3DDevice *device,
	D3DPALETTESIZE size,
	D3DPalette **palette)
{
	return D3DDevice_CreatePalette(size, palette);
}

HRESULT code_00144c50(
	D3DDevice *device,
	D3DSurface *render_target,
	D3DSurface *z_stencil)
{
	D3DDevice_SetRenderTarget(render_target, z_stencil);
	return S_OK;
}

boolean rasterizer_preinitialize__fill_you_up_with_the_devils_cock(
	void)
{
	boolean success;

	d3d= Direct3DCreate8(D3D_SDK_VERSION);
	if (!d3d)
	{
		error(_error_silent, "### ERROR failed to create D3D object");
		success= FALSE;
	}
	else
	{
		D3DPRESENT_PARAMETERS d3d_present_parameters;

		csmemset(&d3d_present_parameters, 0, sizeof(d3d_present_parameters));
		d3d_present_parameters.Flags= D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
		d3d_present_parameters.Windowed= FALSE;
		d3d_present_parameters.SwapEffect= D3DSWAPEFFECT_DISCARD;
		d3d_present_parameters.EnableAutoDepthStencil= TRUE;
		d3d_present_parameters.AutoDepthStencilFormat= D3DFMT_D24S8;
		d3d_present_parameters.BackBufferFormat= D3DFMT_A8R8G8B8;
		d3d_present_parameters.BackBufferWidth= 640;
		d3d_present_parameters.BackBufferHeight= 480;
		d3d_present_parameters.FullScreen_PresentationInterval= 0;

		success= TRUE;
		D3DCALL(success, IDirect3D8_CreateDevice(d3d, D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, NULL, RASTERIZER_DEVICE_CREATION_FLAGS, &d3d_present_parameters, &global_d3d_device));
		if (!global_d3d_device)
		{
			success= FALSE;
		}

		if (!success)
		{
			global_d3d_device= NULL;
			error(_error_silent, "### ERROR failed to create D3D device");
		}
		else
		{
			IDirect3DDevice8_GetDeviceCaps(global_d3d_device, &global_d3d_caps);
			IDirect3DDevice8_Present(global_d3d_device, NULL, NULL, NULL, NULL);
		}
	}

	if (success)
	{
		if (global_d3d_device)
		{
			IDirect3DDevice8_Release(global_d3d_device);
			global_d3d_device= NULL;
		}

		if (d3d)
		{
			IDirect3D8_Release(d3d);
			d3d= NULL;
		}
	}
	else
	{
		error(_error_silent, "### ERROR rasterizer_preinitialize failed");
	}

	return success;
}

D3DSurface *code_00144d80(
	D3DDevice *device,
	D3DSurface **surface)
{
	return (D3DSurface *)D3DDevice_GetDepthStencilSurface(surface);
}

HRESULT code_00144d90(
	D3DDevice *device)
{
	return S_OK;
}

HRESULT code_00144da0(
	D3DDevice *device)
{
	return S_OK;
}

HRESULT code_00144db0(
	D3DDevice *device,
	DWORD count,
	CONST D3DRECT *rects,
	DWORD flags,
	D3DCOLOR color,
	float z,
	DWORD stencil)
{
	D3DDevice_Clear(count, rects, flags, color, z, stencil);
	return S_OK;
}

HRESULT code_00144dd0(
	D3DDevice *device,
	CONST D3DVIEWPORT8 *viewport)
{
	D3DDevice_SetViewport(viewport);
	return S_OK;
}

void *rasterizer_get_bitmap_default_hardware_format(
	struct bitmap_data const *bitmap)
{
	void *hardware_format;

	match_assert(RASTERIZER_XBOX_FILE, 209, bitmap);

	switch (bitmap->type)
	{
	case _bitmap_type_2d:
		hardware_format= rasterizer_globals.default_2d_hardware_format;
		break;
	case _bitmap_type_3d:
		hardware_format= rasterizer_globals.default_2d_hardware_format;
		break;
	case _bitmap_type_cube_map:
		hardware_format= rasterizer_globals.default_cm_hardware_format;
		break;
	default:
		match_vassert(RASTERIZER_XBOX_FILE, 223, FALSE, "### ERROR unsupported bitmap type");
	}

	match_assert(RASTERIZER_XBOX_FILE, 226, hardware_format);

	return hardware_format;
}

HRESULT code_00144e80(
	D3DRENDERSTATETYPE state,
	DWORD value)
{
	D3DDevice_SetRenderState(state, value);
	return S_OK;
}

HRESULT code_001450a0(
	D3DRENDERSTATETYPE state,
	DWORD *value)
{
	*value= D3D__RenderState[state];
	return S_OK;
}

HRESULT code_001450b0(
	DWORD stage,
	D3DBaseTexture *texture)
{
	D3DDevice_SetTexture(stage, texture);
	return S_OK;
}

HRESULT code_001450c0(
	DWORD stage,
	D3DPalette *palette)
{
	D3DDevice_SetPalette(stage, palette);
	return S_OK;
}

HRESULT code_001450d0(
	DWORD stage,
	D3DTEXTURESTAGESTATETYPE type,
	DWORD *value)
{
	*value= D3D__TextureState[stage][type];
	return S_OK;
}

HRESULT code_001450f0(
	DWORD stage,
	D3DTEXTURESTAGESTATETYPE type,
	DWORD value)
{
	D3DDevice_SetTextureStageState(stage, type, value);
	return S_OK;
}

HRESULT code_00145150(
	DWORD handle)
{
	D3DDevice_SetVertexShader(handle);
	return S_OK;
}

HRESULT code_00145160(
	INT register_index,
	CONST void *constant_data,
	DWORD constant_count)
{
	D3DDevice_SetVertexShaderConstant(register_index, constant_data, constant_count);
	return S_OK;
}

HRESULT code_00145170(
	DWORD mode)
{
	D3DDevice_SetShaderConstantMode(mode);
	return S_OK;
}

HRESULT code_00145180(
	UINT stream_number,
	D3DVertexBuffer *stream_data,
	UINT stride)
{
	D3DDevice_SetStreamSource(stream_number, stream_data, stride);
	return S_OK;
}

HRESULT code_00145190(
	D3DIndexBuffer *index_data,
	UINT base_vertex_index)
{
	D3DDevice_SetIndices(index_data, base_vertex_index);
	return S_OK;
}

HRESULT code_001451a0(
	D3DPIXELSHADERDEF *pixel_shader)
{
	D3DDevice_SetPixelShaderProgram(pixel_shader);
	return S_OK;
}

void code_001451b0(
	D3DCALLBACK callback)
{
	D3DDevice_SetVerticalBlankCallback(callback);
}

HRESULT code_001451c0(
	INT register_index,
	SHORT a,
	SHORT b)
{
	D3DDevice_SetVertexData2s(register_index, a, b);
	return S_OK;
}

HRESULT code_001451d0(
	D3DPRIMITIVETYPE primitive_type)
{
	D3DDevice_Begin(primitive_type);
	return S_OK;
}

HRESULT code_001451e0(
	D3DDevice *device)
{
	D3DDevice_End();
	return S_OK;
}

static void rasterizer_filthy_bitmap_defaults_initialize(
	void)
{
	boolean success= TRUE;
	void *default_2d_hardware_format;
	void *default_3d_hardware_format;
	void *default_cm_hardware_format;

	match_assert(RASTERIZER_XBOX_FILE, 239, global_d3d_device);

	D3DCALL(success, IDirect3DDevice8_CreateTexture(global_d3d_device, 4, 4, 1, 0, D3DFMT_A4R4G4B4, D3DPOOL_MANAGED, &(IDirect3DTexture8*)default_2d_hardware_format));
	D3DCALL(success, IDirect3DDevice8_CreateVolumeTexture(global_d3d_device, 4, 4, 4, 1, 0, D3DFMT_A4R4G4B4, D3DPOOL_MANAGED, &(IDirect3DVolumeTexture8*)default_3d_hardware_format));
	D3DCALL(success, IDirect3DDevice8_CreateCubeTexture(global_d3d_device, 4, 1, 0, D3DFMT_A4R4G4B4, D3DPOOL_MANAGED, &(IDirect3DCubeTexture8*)default_cm_hardware_format));

	if (success && default_2d_hardware_format && default_3d_hardware_format && default_cm_hardware_format)
	{
		unsigned short const checkers[2]= {0x0f00, 0xf0f0};
		D3DLOCKED_RECT d3d_locked_rect;
		D3DLOCKED_BOX d3d_locked_box;
		short pixel_index;
		short face_index;

		IDirect3DTexture8_LockRect((IDirect3DTexture8*)default_2d_hardware_format, 0, &d3d_locked_rect, NULL, 0);
		for (pixel_index= 0; pixel_index<4*4; pixel_index++)
		{
			((unsigned short *)d3d_locked_rect.pBits)[pixel_index]= checkers[pixel_index&1];
		}
		IDirect3DTexture8_UnlockRect((IDirect3DTexture8*)default_2d_hardware_format, 0);

		IDirect3DVolumeTexture8_LockBox((IDirect3DVolumeTexture8*)default_3d_hardware_format, 0, &d3d_locked_box, NULL, 0);
		for (pixel_index= 0; pixel_index<4*4*4; pixel_index++)
		{
			((unsigned short *)d3d_locked_box.pBits)[pixel_index]= checkers[pixel_index&1];
		}
		IDirect3DVolumeTexture8_UnlockBox((IDirect3DVolumeTexture8*)default_3d_hardware_format, 0);

		for (face_index= 0; face_index<6; face_index++)
		{
			D3DCALL(success, IDirect3DCubeTexture8_LockRect((IDirect3DCubeTexture8*)default_cm_hardware_format, face_index, 0, &d3d_locked_rect, NULL, 0));
			for (pixel_index= 0; pixel_index<4*4; pixel_index++)
			{
				((unsigned short *)d3d_locked_rect.pBits)[pixel_index]= checkers[pixel_index&1];
			}
			D3DCALL(success, IDirect3DCubeTexture8_UnlockRect((IDirect3DCubeTexture8*)default_cm_hardware_format, face_index, 0));
		}
	}
	else
	{
		success= FALSE;
	}

	match_vassert(RASTERIZER_XBOX_FILE, 311, success, "### ERROR rasterizer_filthy_bitmap_default_initialize failed");

	rasterizer_globals.default_2d_hardware_format= default_2d_hardware_format;
	rasterizer_globals.default_3d_hardware_format= default_3d_hardware_format;
	rasterizer_globals.default_cm_hardware_format= default_cm_hardware_format;

	return;
}

boolean _rasterizer_initialize(
	void)
{
	boolean success= TRUE;

	if (!rasterizer_globals.push_buffer_size)
	{
		rasterizer_globals.push_buffer_size= 512;
	}
	if (!rasterizer_globals.push_buffer_kickoff_size)
	{
		rasterizer_globals.push_buffer_kickoff_size= 32;
	}
	Direct3D_SetPushBufferSize(rasterizer_globals.push_buffer_size*1024, rasterizer_globals.push_buffer_kickoff_size*1024);

	d3d= Direct3DCreate8(D3D_SDK_VERSION);
	if (!d3d)
	{
		error(_error_silent, "### ERROR failed to create D3D object");
		success= FALSE;
	}
	else
	{
		D3DPRESENT_PARAMETERS d3d_present_parameters;

		rasterizer_globals.screen_bounds.y0= 0;
		rasterizer_globals.screen_bounds.x0= 0;
		rasterizer_globals.screen_bounds.x1= 640;
		rasterizer_globals.screen_bounds.y1= 480;
		rasterizer_globals.frame_bounds.x0= 48;
		rasterizer_globals.frame_bounds.x1= 592;
		rasterizer_globals.frame_bounds.y0= 36;
		rasterizer_globals.frame_bounds.y1= 444;
		rasterizer_globals.frame_index= 1;

		csmemset(&d3d_present_parameters, 0, sizeof(d3d_present_parameters));
		d3d_present_parameters.BackBufferWidth= rasterizer_globals.screen_bounds.x1-rasterizer_globals.screen_bounds.x0;
		d3d_present_parameters.Flags= D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
		d3d_present_parameters.AutoDepthStencilFormat= rasterizer_globals.use_floating_point_zbuffer ? D3DFMT_F24S8 : D3DFMT_D24S8;
		d3d_present_parameters.BackBufferHeight= rasterizer_globals.screen_bounds.y1-rasterizer_globals.screen_bounds.y0;
		d3d_present_parameters.Windowed= FALSE;
		d3d_present_parameters.SwapEffect= D3DSWAPEFFECT_DISCARD;
		d3d_present_parameters.EnableAutoDepthStencil= TRUE;
		d3d_present_parameters.BackBufferFormat= D3DFMT_A8R8G8B8;

		switch (rasterizer_globals.refresh_rate)
		{
		case NONE:
			d3d_present_parameters.FullScreen_PresentationInterval= D3DPRESENT_INTERVAL_IMMEDIATE;
			global_frame_rate_throttle= FALSE;
			break;
		case 30:
			d3d_present_parameters.FullScreen_PresentationInterval= D3DPRESENT_INTERVAL_TWO;
			global_frame_rate_throttle= TRUE;
			break;
		case 60:
			d3d_present_parameters.FullScreen_PresentationInterval= D3DPRESENT_INTERVAL_ONE;
			global_frame_rate_throttle= TRUE;
			break;
		default:
			if (rasterizer_globals.refresh_rate!=0)
			{
				error(_error_silent, "### ERROR unsupported refresh rate (%dHz), switching to default", rasterizer_globals.refresh_rate);
				rasterizer_globals.refresh_rate= 0;
			}
			d3d_present_parameters.FullScreen_PresentationInterval= D3DPRESENT_INTERVAL_DEFAULT;
			global_frame_rate_throttle= TRUE;
			break;
		}

		D3DCALL(success, IDirect3D8_CreateDevice(d3d, D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, NULL, RASTERIZER_DEVICE_CREATION_FLAGS, &d3d_present_parameters, &global_d3d_device));
		if (!global_d3d_device)
		{
			success= FALSE;
		}

		if (!success)
		{
			global_d3d_device= NULL;
			error(_error_silent, "### ERROR failed to create D3D device");
		}
		else
		{
			D3DCOLOR *palette_data= NULL;

			IDirect3DDevice8_GetDeviceCaps(global_d3d_device, &global_d3d_caps);
			SetupSmartStates();

			D3DCALL(success, IDirect3DDevice8_CreatePalette(global_d3d_device, D3DPALETTE_256, &d3d_palette));
			D3DCALL(success, IDirect3DPalette8_Lock(d3d_palette, &palette_data, 0));
			csmemcpy(palette_data, global_vector_palette, sizeof(global_vector_palette));
			D3DCALL(success, IDirect3DPalette8_Unlock(d3d_palette));
			D3DCALL(success, IDirect3DDevice8_SetPalette(global_d3d_device, 0, d3d_palette));
			D3DCALL(success, IDirect3DDevice8_SetPalette(global_d3d_device, 1, d3d_palette));
			D3DCALL(success, IDirect3DDevice8_SetPalette(global_d3d_device, 2, d3d_palette));
			D3DCALL(success, IDirect3DDevice8_SetPalette(global_d3d_device, 3, d3d_palette));

			if (success)
			{
				short surface_index;
				short mipmap_index;
				D3DSurface *surface;

				IDirect3DDevice8_GetBackBuffer(global_d3d_device, 0, D3DBACKBUFFER_TYPE_MONO, &bss_0045e87c);
				D3DCALL(success, IDirect3DDevice8_GetDepthStencilSurface(global_d3d_device, &global_d3d_surface_render_primary_z));

				bss_0045e874[0]= debug_malloc(sizeof(struct rasterizer_fake_surface), FALSE, RASTERIZER_XBOX_FILE, 562);
				bss_0045e874[1]= debug_malloc(sizeof(struct rasterizer_fake_surface), FALSE, RASTERIZER_XBOX_FILE, 563);
				if (bss_0045e874[0] && bss_0045e874[1])
				{
					for (surface_index= 0; surface_index<2; surface_index++)
					{
						struct rasterizer_fake_surface *surface= (struct rasterizer_fake_surface *)bss_0045e874[surface_index];

						surface->Common= RASTERIZER_FAKE_SURFACE_COMMON;
						surface->Data= surface_index==1 ? bss_0045e87c->Data : 0;
						surface->Lock= 0;
						surface->Size= RASTERIZER_FAKE_SURFACE_SIZE;
						surface->Format= RASTERIZER_FAKE_SURFACE_FORMAT;
					}
				}
				else
				{
					success= FALSE;
				}

				bss_0045e8cc= surface= debug_malloc(sizeof(D3DSurface), FALSE, RASTERIZER_XBOX_FILE, 610);
				if (surface)
				{
					*surface= *bss_0045e87c;
					surface->Data= global_d3d_surface_render_primary_z->Data;
				}
				else
				{
					success= FALSE;
				}

				bss_0045e8c8= debug_malloc(sizeof(struct rasterizer_fake_surface), FALSE, RASTERIZER_XBOX_FILE, 623);
				if (bss_0045e8c8)
				{
					struct rasterizer_fake_surface *surface= (struct rasterizer_fake_surface *)bss_0045e8c8;

					surface->Common= RASTERIZER_FAKE_SURFACE_COMMON;
					surface->Data= global_d3d_surface_render_primary_z->Data;
					surface->Lock= 0;
					surface->Size= RASTERIZER_FAKE_SURFACE_SIZE;
					surface->Format= RASTERIZER_FAKE_SURFACE_FORMAT;
				}
				else
				{
					success= FALSE;
				}

				D3DCALL(success, IDirect3DDevice8_CreateTexture(global_d3d_device, RASTERIZER_TARGET_RENDER_SECONDARY_WIDTH, RASTERIZER_TARGET_RENDER_SECONDARY_HEIGHT, 1, D3DUSAGE_RENDERTARGET, D3DFMT_LIN_A8R8G8B8, D3DPOOL_DEFAULT, &global_d3d_texture_render_secondary));
				D3DCALL(success, IDirect3DTexture8_GetSurfaceLevel(global_d3d_texture_render_secondary, 0, &global_d3d_surface_render_secondary));
				if (!global_d3d_texture_render_secondary || !global_d3d_surface_render_secondary)
				{
					success= FALSE;
				}
				bss_0045e888= NULL;
				bss_0045e890= NULL;

				D3DCALL(success, IDirect3DDevice8_CreateTexture(global_d3d_device, RASTERIZER_TARGET_WATER_SIZE, RASTERIZER_TARGET_WATER_SIZE, RASTERIZER_TARGET_WATER_MAX_MIPMAP_LEVELS, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &global_d3d_texture_water));
				if (!global_d3d_texture_water)
				{
					success= FALSE;
				}
				for (mipmap_index= 0; success && mipmap_index<RASTERIZER_TARGET_WATER_MAX_MIPMAP_LEVELS; mipmap_index++)
				{
					D3DCALL(success, IDirect3DTexture8_GetSurfaceLevel(global_d3d_texture_water, mipmap_index, &global_d3d_surface_water[mipmap_index]));
					if (!global_d3d_surface_water[mipmap_index])
					{
						success= FALSE;
					}
				}

				D3DCALL(success, IDirect3DDevice8_CreateTexture(global_d3d_device, RASTERIZER_TARGET_SHADOW_PRIMARY_SIZE, RASTERIZER_TARGET_SHADOW_PRIMARY_SIZE, 1, D3DUSAGE_RENDERTARGET, D3DFMT_R5G6B5, D3DPOOL_DEFAULT, &global_d3d_texture_shadow_primary));
				D3DCALL(success, IDirect3DTexture8_GetSurfaceLevel(global_d3d_texture_shadow_primary, 0, &global_d3d_surface_shadow_primary));
				if (!global_d3d_texture_shadow_primary || !global_d3d_surface_shadow_primary)
				{
					success= FALSE;
				}

				D3DCALL(success, IDirect3DDevice8_CreateTexture(global_d3d_device, RASTERIZER_TARGET_SHADOW_SECONDARY_SIZE, RASTERIZER_TARGET_SHADOW_SECONDARY_SIZE, 1, D3DUSAGE_RENDERTARGET, D3DFMT_R5G6B5, D3DPOOL_DEFAULT, &global_d3d_texture_shadow_secondary));
				D3DCALL(success, IDirect3DTexture8_GetSurfaceLevel(global_d3d_texture_shadow_secondary, 0, &global_d3d_surface_shadow_secondary));
				if (!global_d3d_texture_shadow_secondary || !global_d3d_surface_shadow_secondary)
				{
					success= FALSE;
				}

				D3DCALL(success, IDirect3DDevice8_CreateTexture(global_d3d_device, RASTERIZER_TARGET_SUN_GLOW_SIZE, RASTERIZER_TARGET_SUN_GLOW_SIZE, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &global_d3d_texture_sun_glow_primary));
				D3DCALL(success, IDirect3DTexture8_GetSurfaceLevel(global_d3d_texture_sun_glow_primary, 0, &global_d3d_surface_sun_glow_primary));
				if (!global_d3d_texture_sun_glow_primary || !global_d3d_surface_sun_glow_primary)
				{
					success= FALSE;
				}

				D3DCALL(success, IDirect3DDevice8_CreateTexture(global_d3d_device, RASTERIZER_TARGET_SUN_GLOW_SIZE, RASTERIZER_TARGET_SUN_GLOW_SIZE, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &global_d3d_texture_sun_glow_secondary));
				D3DCALL(success, IDirect3DTexture8_GetSurfaceLevel(global_d3d_texture_sun_glow_secondary, 0, &global_d3d_surface_sun_glow_secondary));
				if (!global_d3d_texture_sun_glow_secondary || !global_d3d_surface_sun_glow_secondary)
				{
					success= FALSE;
				}

				if (!success)
				{
					error(_error_silent, "### ERROR failed to create offscreen surface(s)");
				}
				else
				{
					IDirect3DDevice8_SetShaderConstantMode(global_d3d_device, D3DSCM_192CONSTANTS);
					IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZENABLE, TRUE);
					IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZWRITEENABLE, TRUE);
					IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
					IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZBIAS, 0);
					IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_SOLIDOFFSETENABLE, TRUE);
					IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHATESTENABLE, FALSE);
					IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHAFUNC, D3DCMP_GREATER);
					IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHAREF, 0);
					IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHABLENDENABLE, FALSE);
					IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_SRCBLEND, D3DBLEND_ONE);
					IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_DESTBLEND, D3DBLEND_ZERO);
					IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_BLENDOP, D3DBLENDOP_ADD);
					IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_FOGENABLE, TRUE);
					IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_LIGHTING, FALSE);
					IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_SPECULARENABLE, TRUE);
					IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_TEXCOORDINDEX, 0);
					IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_TEXCOORDINDEX, 1);
					IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_TEXCOORDINDEX, 2);
					IDirect3DDevice8_SetTextureStageState(global_d3d_device, 3, D3DTSS_TEXCOORDINDEX, 3);
					IDirect3DDevice8_SetFlickerFilter(global_d3d_device, 5);
					IDirect3DDevice8_SetSoftDisplayFilter(global_d3d_device, FALSE);
				}
			}
		}
	}

	rasterizer_filthy_bitmap_defaults_initialize();

	success= success &&
		rasterizer_memory_pool_initialize() &&
		rasterizer_dynamic_geometry_initialize() &&
		rasterizer_transparent_geometry_initialize() &&
		rasterizer_vertex_shaders_initialize() &&
		rasterizer_debug_initialize() &&
		rasterizer_frame_statistics_initialize() &&
		rasterizer_text_cache_initialize() &&
		rasterizer_detail_objects_initialize() &&
		rasterizer_profile_initialize() &&
		rasterizer_environment_fog_screen_initialize();

	rasterizer_screen_effects_initialize();
	texture_cache_new();
	rasterizer_debug_begin();

	if (success)
	{
		rasterizer_globals.active= TRUE;
	}
	else
	{
		error(_error_silent, "### ERROR failed to initialize rasterizer");
	}

	return success;
}

void _rasterizer_reset_state(
	void)
{
	return;
}

void rasterizer_spin_begin(
	void)
{
	return;
}

void rasterizer_spin_end(
	void)
{
	return;
}

void _rasterizer_frame_begin(
	struct rasterizer_frame_begin_parameters const *parameters)
{
	match_assert(RASTERIZER_XBOX_FILE, 1256, global_d3d_device);

	rasterizer_globals.z_near= rasterizer_get_near_clip_distance();
	global_frame_parameters.game_time_sec= parameters->game_time_sec;

	rasterizer_profile_frame_begin();
	rasterizer_frame_statistics_begin();
	rasterizer_water_set_visibility_for_frame(FALSE);
	rasterizer_lights_begin_for_new_frame();
	texture_cache_idle();

	IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_DXT1NOISEENABLE, rasterizer_debug_options.DXTC_noise_enabled);

	if (rasterizer_debug_options.draw_environment_decals)
	{
		rasterizer_decal_vertices_begin_update();
		decals_update();
		rasterizer_decal_vertices_end_update();
	}

	return;
}

void _rasterizer_windows_begin(
	void)
{
	match_assert(RASTERIZER_XBOX_FILE, 1331, global_d3d_device);

	return;
}

void _rasterizer_window_begin(
	struct rasterizer_window_begin_parameters const *parameters)
{
	D3DCOLOR clear_color;

	match_assert(RASTERIZER_XBOX_FILE, 1351, parameters);
	match_assert(RASTERIZER_XBOX_FILE, 1352, global_d3d_device);

	global_window_parameters= *parameters;

	bss_0045e8d8= bss_0045e8dc!=NONE && parameters->window_index==NONE;
	bss_0045e8dc= parameters->window_index;

	if (!bss_0045e8d8)
	{
		rasterizer_memory_pool_begin();
		rasterizer_dynamic_geometry_begin();
		rasterizer_transparent_geometry_begin();
		rasterizer_environment_fog_screen_window_begin();
		rasterizer_lights_begin();
	}

	rasterizer_water_set_visibility_for_window(FALSE);
	rasterizer_active_camouflage_set_visibility(FALSE);
	rasterizer_profile_window_begin();
	rasterizer_set_stencil_mode(0);
	rasterizer_window_set_fog(&parameters->fog);

	if (rasterizer_debug_options.drawing_mode==1)
	{
		clear_color= 0;
	}
	else
	{
		clear_color= real_rgb_color_to_pixel32(&global_window_parameters.fog.atmospheric_color);
	}

	if (parameters->rasterizer_target==_rasterizer_target_render_primary || parameters->rasterizer_target==_rasterizer_target_render_secondary)
	{
		rasterizer_profile_begin(_rasterizer_profile_clear);
		rasterizer_set_target(parameters->rasterizer_target, 0, clear_color, !parameters->suppress_clear, TRUE);
		rasterizer_profile_end(_rasterizer_profile_clear);
		if (parameters->rasterizer_target==_rasterizer_target_render_primary)
		{
			match_assert(RASTERIZER_XBOX_FILE, 1415, parameters->camera.z_near!=0.0f);
		}
	}
	else
	{
		match_vassert(RASTERIZER_XBOX_FILE, 1420, FALSE, "### ERROR unsupported rasterizer target for scene rendering");
	}

	rasterizer_set_frustum_z(-1.0f, -1.0f);
	IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_FILLMODE, rasterizer_debug_options.wireframe_enabled ? D3DFILL_WIREFRAME : D3DFILL_SOLID);

	return;
}

void _rasterizer_window_get_fog(
	struct render_fog *fog)
{
	match_assert(RASTERIZER_XBOX_FILE, 1440, fog);

	*fog= global_window_parameters.fog;

	return;
}

void code_00145290(
	void *a,
	void *b)
{
	return;
}

void _rasterizer_window_set_fog(
	struct render_fog const *fog)
{
	real vsh_constants__fog[16];
	real planar_eye_distance;
	real one_over_atmospheric_distance;
	real camera_forward_distance;
	real one_over_planar_maximum_distance;
	real one_over_planar_maximum_depth;

	match_assert(RASTERIZER_XBOX_FILE, 1452, fog);

	global_window_parameters.fog= *fog;

	if (global_window_parameters.fog.atmospheric_maximum_density<=0.0f)
	{
		global_window_parameters.fog.atmospheric_maximum_density= 1.0f;
	}

	if (global_window_parameters.fog.atmospheric_maximum_distance==0.0f || !rasterizer_debug_options.fog_atmospheric_enabled)
	{
		global_window_parameters.fog.atmospheric_maximum_density= 0.0f;
		global_window_parameters.fog.atmospheric_minimum_distance= global_window_parameters.camera.z_far;
		global_window_parameters.fog.atmospheric_maximum_distance= 2.0f*global_window_parameters.camera.z_far;
	}

	if (global_window_parameters.fog.planar_maximum_density<=0.0f)
	{
		global_window_parameters.fog.planar_maximum_density= 1.0f;
	}

	if (global_window_parameters.fog.planar_mode && !TEST_FLAG(fog->fog_definition_flags, _fog_definition_screen_effect_only_bit) && rasterizer_debug_options.fog_planar_enabled)
	{
		if (global_window_parameters.fog.planar_mode==2)
		{
			match_vassert(RASTERIZER_XBOX_FILE, 1498, global_window_parameters.fog.planar_maximum_distance!=0.0f, "global_window_parameters.fog.planar_maximum_distance!=0.0f");
			global_window_parameters.fog.planar_maximum_depth= 1.0f;
			plane3d_from_point_and_normal(&global_window_parameters.fog.plane, &global_window_parameters.camera.position, &global_window_parameters.camera.forward);
			global_window_parameters.fog.plane.d+= global_window_parameters.camera.z_far;
		}
	}
	else
	{
		global_window_parameters.fog.planar_mode= 0;
		global_window_parameters.fog.planar_maximum_density= 0.0f;
		global_window_parameters.fog.planar_maximum_distance= 1.0f;
		global_window_parameters.fog.planar_maximum_depth= 1.0f;
		global_window_parameters.fog.planar_color= *global_real_rgb_white;
		global_window_parameters.fog.plane.n= global_window_parameters.camera.forward;
		global_window_parameters.fog.plane.d= dot_product3d((real_vector3d *)&global_window_parameters.camera.position, &global_window_parameters.camera.forward);
	}

	match_vassert(RASTERIZER_XBOX_FILE, 1511, global_window_parameters.fog.atmospheric_maximum_distance>=global_window_parameters.fog.atmospheric_minimum_distance, "global_window_parameters.fog.atmospheric_maximum_distance>=global_window_parameters.fog.atmospheric_minimum_distance");
	match_vassert(RASTERIZER_XBOX_FILE, 1512, global_window_parameters.fog.planar_maximum_distance>0.0f, "global_window_parameters.fog.planar_maximum_distance>0.0f");
	match_vassert(RASTERIZER_XBOX_FILE, 1513, global_window_parameters.fog.planar_maximum_depth>0.0f, "global_window_parameters.fog.planar_maximum_depth>0.0f");

	one_over_atmospheric_distance= 1.0f/(global_window_parameters.fog.atmospheric_maximum_distance-global_window_parameters.fog.atmospheric_minimum_distance);
	planar_eye_distance= dot_product3d((real_vector3d *)&global_window_parameters.camera.position, &global_window_parameters.fog.plane.n)-global_window_parameters.fog.plane.d;
	camera_forward_distance= dot_product3d((real_vector3d *)&global_window_parameters.camera.position, &global_window_parameters.camera.forward);
	one_over_planar_maximum_distance= 1.0f/global_window_parameters.fog.planar_maximum_distance;
	one_over_planar_maximum_depth= 1.0f/global_window_parameters.fog.planar_maximum_depth;

	vsh_constants__fog[0]= global_window_parameters.camera.forward.i*one_over_atmospheric_distance;
	vsh_constants__fog[1]= global_window_parameters.camera.forward.j*one_over_atmospheric_distance;
	vsh_constants__fog[2]= global_window_parameters.camera.forward.k*one_over_atmospheric_distance;
	vsh_constants__fog[3]= -((global_window_parameters.fog.atmospheric_minimum_distance+camera_forward_distance)*one_over_atmospheric_distance);
	vsh_constants__fog[4]= -(global_window_parameters.fog.plane.n.i*one_over_planar_maximum_depth);
	vsh_constants__fog[5]= -(global_window_parameters.fog.plane.n.j*one_over_planar_maximum_depth);
	vsh_constants__fog[6]= -(global_window_parameters.fog.plane.n.k*one_over_planar_maximum_depth);
	vsh_constants__fog[7]= global_window_parameters.fog.plane.d*one_over_planar_maximum_depth;
	vsh_constants__fog[8]= global_window_parameters.camera.forward.i*one_over_planar_maximum_distance;
	vsh_constants__fog[9]= global_window_parameters.camera.forward.j*one_over_planar_maximum_distance;
	vsh_constants__fog[10]= global_window_parameters.camera.forward.k*one_over_planar_maximum_distance;
	vsh_constants__fog[11]= -(camera_forward_distance*one_over_planar_maximum_distance);
	vsh_constants__fog[12]= PIN(global_window_parameters.fog.atmospheric_maximum_density, 0.0f, 1.0f);
	vsh_constants__fog[13]= PIN(-(one_over_planar_maximum_depth*planar_eye_distance), 0.0f, 1.0f);
	vsh_constants__fog[14]= PIN(global_window_parameters.fog.planar_maximum_density, 0.0f, 1.0f);
	vsh_constants__fog[15]= 0.0f;

	IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, -88, vsh_constants__fog, 4);
	IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_FOGCOLOR, real_rgb_color_to_pixel32(&global_window_parameters.fog.atmospheric_color));

	return;
}

void _rasterizer_window_end(
	void)
{
	match_assert(RASTERIZER_XBOX_FILE, 1567, global_d3d_device);

	if (main_get_window_count()>1 && !rasterizer_debug_options.pad3)
	{
		IDirect3DDevice8_Clear(global_d3d_device, 0, NULL, D3DCLEAR_TARGET_A, 0, 1.0f, 0);
	}

	if (global_window_parameters.has_mirror)
	{
		rectangle2d bounds;

		bounds.x0= 512;
		bounds.x1= 640;
		bounds.y0= 0;
		bounds.y1= 96;
		rasterizer_secondary_render_target_debug(&bounds);
	}

	if (global_window_parameters.window_index==NONE)
	{
		rasterizer_frame_statistics_get_fps(&rasterizer_frame_statistics);
		rasterizer_frame_statistics_draw();
	}

	if (!bss_0045e8d8)
	{
		rasterizer_memory_pool_end();
		rasterizer_dynamic_geometry_end();
		rasterizer_transparent_geometry_end();
		rasterizer_environment_fog_screen_window_end();
		rasterizer_lights_end();
		rasterizer_debug_end();
		rasterizer_debug_begin();
	}

	rasterizer_profile_window_end();

	return;
}

void _rasterizer_windows_end(
	void)
{
	match_assert(RASTERIZER_XBOX_FILE, 1629, global_d3d_device);

	return;
}

void _rasterizer_frame_end(
	void)
{
	boolean success= TRUE;
	short index;

	match_assert(RASTERIZER_XBOX_FILE, 1648, global_d3d_device);

	rasterizer_profile_frame_end();
	rasterizer_frame_statistics_end();

	for (index= 0; index<4; index++)
	{
		D3DCALL(success, IDirect3DDevice8_SetTexture(global_d3d_device, index, NULL));
	}

	for (index= 0; index<16; index++)
	{
		D3DCALL(success, IDirect3DDevice8_SetStreamSource(global_d3d_device, index, NULL, 0));
	}

	D3DCALL(success, IDirect3DDevice8_SetIndices(global_d3d_device, NULL, 0));

	if (!success)
	{
		error(_error_silent, "### ERROR rasterizer_frame_end failed");
	}

	return;
}

HRESULT code_001453a0(
	D3DTexture *texture,
	UINT level,
	D3DSurface **surface_level)
{
	return (HRESULT)D3DTexture_GetSurfaceLevel(texture, level, surface_level);
}

HRESULT code_001453b0(
	D3DTexture *texture,
	UINT level,
	D3DLOCKED_RECT *locked_rect,
	CONST RECT *rect,
	DWORD flags)
{
	D3DTexture_LockRect(texture, level, locked_rect, rect, flags);
	return S_OK;
}

HRESULT code_001453d0(
	D3DTexture *texture,
	UINT level)
{
	return S_OK;
}

void code_001453e0(
	void *a,
	void *b)
{
	return;
}

void _rasterizer_present(
	struct bitmap_data *screenshot_bitmap,
	point2d const *screenshot_index)
{
	boolean success= TRUE;

	match_assert(RASTERIZER_XBOX_FILE, 1689, global_d3d_device);

	if (screenshot_bitmap && screenshot_bitmap->base_address)
	{
		rectangle2d bounds= rasterizer_globals.screen_bounds;

		if (screenshot_index)
		{
			short screen_width= rasterizer_globals.screen_bounds.x1-rasterizer_globals.screen_bounds.x0;
			short screen_height= rasterizer_globals.screen_bounds.y1-rasterizer_globals.screen_bounds.y0;

			bounds.x0= screenshot_index->x*screen_width;
			bounds.y0= screenshot_index->y*screen_height;
			bounds.x1= bounds.x0+screen_width;
			bounds.y1= bounds.y0+screen_height;
		}

		if ((screenshot_bitmap->format==_bitmap_format_a8r8g8b8 || screenshot_bitmap->format==_bitmap_format_x8r8g8b8) &&
			screenshot_bitmap->mipmap_count==0 &&
			bounds.x0>=0 && bounds.y0>=0 &&
			bounds.x1<=screenshot_bitmap->width && bounds.y1<=screenshot_bitmap->height)
		{
			D3DSurface *d3d_backbuffer= NULL;
			D3DSURFACE_DESC d3d_surface_description;

			IDirect3DDevice8_GetBackBuffer(global_d3d_device, 0, D3DBACKBUFFER_TYPE_MONO, &d3d_backbuffer);
			IDirect3DSurface8_GetDesc(d3d_backbuffer, &d3d_surface_description);

			if (d3d_surface_description.Size==d3d_surface_description.Width*d3d_surface_description.Height*sizeof(pixel32))
			{
				D3DLOCKED_RECT d3d_locked_rect;

				IDirect3DSurface8_LockRect(d3d_backbuffer, &d3d_locked_rect, NULL, D3DLOCK_READONLY|D3DLOCK_TILED);

				if (d3d_locked_rect.pBits)
				{
					short screen_width= rasterizer_globals.screen_bounds.x1-rasterizer_globals.screen_bounds.x0;
					short screen_height= rasterizer_globals.screen_bounds.y1-rasterizer_globals.screen_bounds.y0;
					short row_index;

					match_vassert(RASTERIZER_XBOX_FILE, 1732, d3d_locked_rect.Pitch==bitmap_format_get_bits_per_pixel(screenshot_bitmap->format)*screen_width/CHAR_BITS, "d3d_locked_rect.Pitch==bitmap_format_get_bits_per_pixel(screenshot_bitmap->format)*screen_width/CHAR_BITS");

					for (row_index= 0; row_index<screen_height; row_index++)
					{
						void *destination= bitmap_2d_address(screenshot_bitmap, bounds.x0, (short)(bounds.y0+row_index), 0);

						csmemcpy(destination, (byte *)d3d_locked_rect.pBits+row_index*d3d_locked_rect.Pitch, d3d_locked_rect.Pitch);
					}
					success= TRUE;
				}
				else
				{
					error(_error_silent, "### ERROR rasterizer_present: failed to lock backbuffer surface");
					success= FALSE;
				}
			}
			else
			{
				error(_error_silent, "### ERROR rasterizer_present: failed to get backbuffer surface");
				success= FALSE;
			}
		}
		else
		{
			error(_error_silent, "### ERROR rasterizer_present: invalid bitmap");
			success= FALSE;
		}
	}

	D3DCALL(success, IDirect3DDevice8_Present(global_d3d_device, NULL, NULL, window_globals.hWndPresentTarget, NULL));
	rasterizer_globals.frame_index++;

	if (!success)
	{
		error(_error_silent, "### ERROR rasterizer_present failed");
	}

	return;
}

void _rasterizer_dispose(
	void)
{
	rasterizer_memory_pool_dispose();
	rasterizer_dynamic_geometry_dispose();
	rasterizer_transparent_geometry_dispose();
	rasterizer_vertex_shaders_dispose();
	rasterizer_debug_dispose();
	rasterizer_frame_statistics_dispose();
	rasterizer_text_cache_dispose();
	rasterizer_detail_objects_dispose();
	rasterizer_profile_dispose();
	rasterizer_environment_fog_screen_dispose();
	rasterizer_screen_effects_dispose();
	texture_cache_delete();

	if (global_d3d_device)
	{
		IDirect3DDevice8_Release(global_d3d_device);
		global_d3d_device= NULL;
	}

	if (d3d)
	{
		IDirect3D8_Release(d3d);
		d3d= NULL;
	}

	return;
}

void _rasterizer_set_vblank_callback(
	D3DCALLBACK callback)
{
	IDirect3DDevice8_SetVerticalBlankCallback(global_d3d_device, callback);

	return;
}

HRESULT code_00145470(
	D3DVolumeTexture *volume_texture,
	UINT level,
	D3DLOCKED_BOX *locked_box,
	CONST D3DBOX *box,
	DWORD flags)
{
	D3DVolumeTexture_LockBox(volume_texture, level, locked_box, box, flags);
	return S_OK;
}

HRESULT code_00145490(
	D3DVolumeTexture *volume_texture,
	UINT level)
{
	return S_OK;
}

void rasterizer_set_framebuffer_blend_function(
	short framebuffer_blend_function)
{
	static unsigned long const srcblend_table[NUMBER_OF_SHADER_FRAMEBUFFER_BLEND_FUNCTIONS+1]=
	{
		D3DBLEND_SRCALPHA,
		D3DBLEND_DESTCOLOR,
		D3DBLEND_DESTCOLOR,
		D3DBLEND_ONE,
		D3DBLEND_ONE,
		D3DBLEND_ONE,
		D3DBLEND_ONE,
		D3DBLEND_ONE,
		NONE
	};
	static unsigned long const destblend_table[NUMBER_OF_SHADER_FRAMEBUFFER_BLEND_FUNCTIONS+1]=
	{
		D3DBLEND_INVSRCALPHA,
		D3DBLEND_ZERO,
		D3DBLEND_SRCCOLOR,
		D3DBLEND_ONE,
		D3DBLEND_ONE,
		D3DBLEND_ONE,
		D3DBLEND_ONE,
		D3DBLEND_INVSRCALPHA,
		NONE
	};
	static unsigned long const blendop_table[NUMBER_OF_SHADER_FRAMEBUFFER_BLEND_FUNCTIONS+1]=
	{
		D3DBLENDOP_ADD,
		D3DBLENDOP_ADD,
		D3DBLENDOP_ADD,
		D3DBLENDOP_ADD,
		D3DBLENDOP_REVSUBTRACT,
		D3DBLENDOP_MIN,
		D3DBLENDOP_MAX,
		D3DBLENDOP_ADD,
		NONE
	};

	match_vassert(RASTERIZER_XBOX_FILE, 1907, framebuffer_blend_function>=0 && framebuffer_blend_function<NUMBER_OF_SHADER_FRAMEBUFFER_BLEND_FUNCTIONS, "framebuffer_blend_function>=0 && framebuffer_blend_function<NUMBER_OF_SHADER_FRAMEBUFFER_BLEND_FUNCTIONS");

	IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_SRCBLEND, srcblend_table[framebuffer_blend_function]);
	IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_DESTBLEND, destblend_table[framebuffer_blend_function]);
	IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_BLENDOP, blendop_table[framebuffer_blend_function]);

	return;
}

boolean rasterizer_set_texture_bitmap_data(
	short stage,
	struct bitmap_data *bitmap)
{
	match_vassert(RASTERIZER_XBOX_FILE, 1935, stage>=0 && stage<RASTERIZER_MAXIMUM_TEXTURE_STAGES, "stage>=0 && stage<RASTERIZER_MAXIMUM_TEXTURE_STAGES");

	if (bitmap)
	{
		void *hardware_format;

		profile_texture_start();
		hardware_format= _texture_cache_bitmap_get_hardware_format(bitmap, TRUE, TRUE);
		profile_texture_end();

		IDirect3DDevice8_SetTexture(global_d3d_device, stage, (IDirect3DBaseTexture8 *)hardware_format);
	}
	else
	{
		display_assert("### YOU GOT FUCKED in rasterizer_set_texture_bitmap_data", RASTERIZER_XBOX_FILE, 1943, TRUE);
		error(_error_silent, "### ERROR direct texture not found (stage=%d)", stage);
	}

	return TRUE;
}

boolean rasterizer_set_texture_direct(
	short stage,
	long bitmap_group_index,
	short bitmap_index)
{
	boolean success= FALSE;

	match_vassert(RASTERIZER_XBOX_FILE, 1958, stage>=0 && stage<RASTERIZER_MAXIMUM_TEXTURE_STAGES, "stage>=0 && stage<RASTERIZER_MAXIMUM_TEXTURE_STAGES");

	if (bitmap_group_index!=NONE)
	{
		struct bitmap_group *bitmap_group= tag_get(BITMAP_GROUP_TAG, bitmap_group_index);

		if (bitmap_group->bitmaps.count>0)
		{
			struct bitmap_data *bitmap= bitmap_group_try_and_get_bitmap(bitmap_group_index, (short)(bitmap_index%bitmap_group->bitmaps.count));

			if (bitmap)
			{
				rasterizer_set_texture_bitmap_data(stage, bitmap);
				success= TRUE;
			}
		}
	}

	if (!success)
	{
		display_assert("### YOU GOT FUCKED in rasterizer_set_texture_direct", RASTERIZER_XBOX_FILE, 1982, TRUE);
		error(_error_silent, "### ERROR direct texture not found (stage=%d)", stage);
	}

	return success;
}

void code_001455f0(
	void *a,
	void *b,
	void *c)
{
	return;
}

boolean rasterizer_set_texture_direct_non_blocking(
	short stage,
	long bitmap_group_index,
	short bitmap_index)
{
	boolean loading= FALSE;
	boolean found= FALSE;

	match_vassert(RASTERIZER_XBOX_FILE, 2003, stage>=0 && stage<RASTERIZER_MAXIMUM_TEXTURE_STAGES, "stage>=0 && stage<RASTERIZER_MAXIMUM_TEXTURE_STAGES");

	if (bitmap_group_index!=NONE)
	{
		struct bitmap_group *bitmap_group= tag_get(BITMAP_GROUP_TAG, bitmap_group_index);

		if (bitmap_group->bitmaps.count>0)
		{
			struct bitmap_data *bitmap= bitmap_group_try_and_get_bitmap(bitmap_group_index, (short)(bitmap_index%bitmap_group->bitmaps.count));

			if (bitmap)
			{
				if (_texture_cache_bitmap_get_hardware_format(bitmap, FALSE, TRUE))
				{
					rasterizer_set_texture_bitmap_data(stage, bitmap);
				}
				else
				{
					loading= TRUE;
				}
				found= TRUE;
			}
		}
	}

	if (!found)
	{
		display_assert("### YOU GOT FUCKED in rasterizer_set_texture_direct_non_blocking", RASTERIZER_XBOX_FILE, 2035, TRUE);
		error(_error_silent, "### ERROR direct texture not found (stage=%d)", stage);
	}

	return loading;
}

point2d *rasterizer_set_texture(
	short stage,
	short type,
	short usage,
	long bitmap_group_index,
	short bitmap_index)
{
	static point2d dimensions;
	boolean success= FALSE;

	match_vassert(RASTERIZER_XBOX_FILE, 2058, stage>=0 && stage<RASTERIZER_MAXIMUM_TEXTURE_STAGES, "stage>=0 && stage<RASTERIZER_MAXIMUM_TEXTURE_STAGES");
	match_vassert(RASTERIZER_XBOX_FILE, 2059, type>=0 && type<3, "type>=0 && type<NUMBER_OF_BITMAP_TYPES");
	match_vassert(RASTERIZER_XBOX_FILE, 2060, usage>=0 && usage<4, "usage>=0 && usage<NUMBER_OF_BITMAP_USAGES");

	if ((rasterizer_debug_options.bump_mapping_enabled || usage!=3) && bitmap_group_index!=NONE)
	{
		struct bitmap_group *bitmap_group= tag_get(BITMAP_GROUP_TAG, bitmap_group_index);

		if (bitmap_group->bitmaps.count>0)
		{
			struct bitmap_data *bitmap= bitmap_group_try_and_get_bitmap(bitmap_group_index, (short)(bitmap_index%bitmap_group->bitmaps.count));

			if (bitmap->type==type)
			{
				rasterizer_set_texture_bitmap_data(stage, bitmap);
				dimensions.x= bitmap->width;
				dimensions.y= bitmap->height;
				success= TRUE;
			}
			else
			{
				error(_error_silent, "### ERROR incompatible bitmap type in shader got %s expected %s", bitmap_type_get_string(bitmap->type), bitmap_type_get_string(type));
			}
		}
	}

	if (!success)
	{
		long default_bitmap_group_index= global_rasterizer_data->default_textures[type].index;
		struct bitmap_data *bitmap;

		if (default_bitmap_group_index!=NONE && (bitmap= bitmap_group_try_and_get_bitmap(default_bitmap_group_index, usage))!=NULL)
		{
			rasterizer_set_texture_bitmap_data(stage, bitmap);
			dimensions.x= bitmap->width;
			dimensions.y= bitmap->height;
			success= TRUE;
		}
		else
		{
			display_assert("### YOU GOT FUCKED in rasterizer_set_texture", RASTERIZER_XBOX_FILE, 2117, TRUE);
			error(_error_silent, "### ERROR default texture not found (stage=%d, type=%d, usage=%d)", stage, type, usage);
		}
	}

	return success ? &dimensions : NULL;
}

HRESULT code_001458c0(
	D3DCubeTexture *cube_texture,
	D3DCUBEMAP_FACES face,
	UINT level,
	D3DLOCKED_RECT *locked_rect,
	CONST RECT *rect,
	DWORD flags)
{
	D3DCubeTexture_LockRect(cube_texture, face, level, locked_rect, rect, flags);
	return S_OK;
}

HRESULT code_001458e0(
	D3DCubeTexture *cube_texture,
	D3DCUBEMAP_FACES face,
	UINT level)
{
	return S_OK;
}

boolean rasterizer_set_texture_non_blocking(
	short stage,
	short type,
	short usage,
	long bitmap_group_index,
	short bitmap_index)
{
	static point2d dimensions;
	struct bitmap_data *bitmap;
	long default_bitmap_group_index;

	match_vassert(RASTERIZER_XBOX_FILE, 2142, stage>=0 && stage<RASTERIZER_MAXIMUM_TEXTURE_STAGES, "stage>=0 && stage<RASTERIZER_MAXIMUM_TEXTURE_STAGES");
	match_vassert(RASTERIZER_XBOX_FILE, 2143, type>=0 && type<3, "type>=0 && type<NUMBER_OF_BITMAP_TYPES");
	match_vassert(RASTERIZER_XBOX_FILE, 2144, usage>=0 && usage<4, "usage>=0 && usage<NUMBER_OF_BITMAP_USAGES");

	if ((rasterizer_debug_options.bump_mapping_enabled || usage!=3) && bitmap_group_index!=NONE)
	{
		struct bitmap_group *bitmap_group= tag_get(BITMAP_GROUP_TAG, bitmap_group_index);

		if (bitmap_group->bitmaps.count>0)
		{
			bitmap= bitmap_group_try_and_get_bitmap(bitmap_group_index, (short)(bitmap_index%bitmap_group->bitmaps.count));

			if (_texture_cache_bitmap_get_hardware_format(bitmap, FALSE, TRUE))
			{
				if (bitmap->type==type)
				{
					rasterizer_set_texture_bitmap_data(stage, bitmap);
					dimensions.x= bitmap->width;
					dimensions.y= bitmap->height;
					return FALSE;
				}

				error(_error_silent, "### ERROR incompatible bitmap type in shader got %s expected %s", bitmap_type_get_string(bitmap->type), bitmap_type_get_string(type));
			}
			else
			{
				return TRUE;
			}
		}
	}

	default_bitmap_group_index= global_rasterizer_data->default_textures[type].index;
	if (default_bitmap_group_index!=NONE && (bitmap= bitmap_group_try_and_get_bitmap(default_bitmap_group_index, usage))!=NULL)
	{
		rasterizer_set_texture_bitmap_data(stage, bitmap);
		dimensions.x= bitmap->width;
		dimensions.y= bitmap->height;
		return FALSE;
	}

	display_assert("### YOU GOT FUCKED in rasterizer_set_texture_non_blocking", RASTERIZER_XBOX_FILE, 2210, TRUE);
	error(_error_silent, "### ERROR default texture not found (stage=%d, type=%d, usage=%d)", stage, type, usage);

	return FALSE;
}

void code_00145c60(
	void *a)
{
	return;
}

HRESULT code_00145c70(
	D3DPalette *palette,
	D3DCOLOR **colors,
	DWORD flags)
{
	D3DPalette_Lock(palette, colors, flags);
	return S_OK;
}

HRESULT code_00145c80(
	D3DPalette *palette)
{
	return S_OK;
}

void rasterizer_set_vertex_shader(
	short vertex_shader_index)
{
	match_assert(RASTERIZER_XBOX_FILE, 2613, vertex_shader_index>=0);
	match_assert(RASTERIZER_XBOX_FILE, 2614, vertex_shader_index<NUMBER_OF_VERTEX_SHADERS);

	if (vertex_shader_index!=data_0030ceec)
	{
		boolean success;

		if (vertex_shader_table[vertex_shader_index].handle!=NONE)
		{
			IDirect3DDevice8_SetVertexShader(global_d3d_device, vertex_shader_table[vertex_shader_index].handle);
			success= TRUE;

			if (rasterizer_debug_options.statistics_mode)
			{
				rasterizer_frame_statistics.vertex_shader_total+= vertex_shader_table[vertex_shader_index].size;
			}
		}
		else
		{
			error(_error_silent, "### ERROR vertex shader not valid (#%d)", vertex_shader_index);
			success= FALSE;
		}

		data_0030ceec= vertex_shader_index;

		if (!success)
		{
			error(_error_silent, "### ERROR rasterizer_set_vertex_shader failed");
		}
	}

	return;
}

void rasterizer_set_pixel_shader(
	D3DPIXELSHADERDEF *pixel_shader)
{
	short combiner_count;

	match_assert(RASTERIZER_XBOX_FILE, 2652, pixel_shader);

	combiner_count= (short)(pixel_shader->PSCombinerCount&0xf);
	if (combiner_count<6)
	{
		boolean unique_c0= (boolean)((pixel_shader->PSCombinerCount>>12)&1);
		boolean unique_c1= (boolean)((pixel_shader->PSCombinerCount>>16)&1);
		short stage;

		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_PSTEXTUREMODES, pixel_shader->PSTextureModes);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_PSCOMBINERCOUNT, pixel_shader->PSCombinerCount);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_PSINPUTTEXTURE, pixel_shader->PSInputTexture);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_PSDOTMAPPING, pixel_shader->PSDotMapping);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_PSFINALCOMBINERINPUTSABCD, pixel_shader->PSFinalCombinerInputsABCD);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_PSFINALCOMBINERINPUTSEFG, pixel_shader->PSFinalCombinerInputsEFG);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_PSFINALCOMBINERCONSTANT0, pixel_shader->PSFinalCombinerConstant0);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_PSFINALCOMBINERCONSTANT1, pixel_shader->PSFinalCombinerConstant1);

		for (stage= 0; stage<combiner_count; stage++)
		{
			IDirect3DDevice8_SetRenderStateNotInline(global_d3d_device, D3DRS_PSALPHAINPUTS0+stage, pixel_shader->PSAlphaInputs[stage]);
			IDirect3DDevice8_SetRenderStateNotInline(global_d3d_device, D3DRS_PSALPHAOUTPUTS0+stage, pixel_shader->PSAlphaOutputs[stage]);
			IDirect3DDevice8_SetRenderStateNotInline(global_d3d_device, D3DRS_PSRGBINPUTS0+stage, pixel_shader->PSRGBInputs[stage]);
			IDirect3DDevice8_SetRenderStateNotInline(global_d3d_device, D3DRS_PSRGBOUTPUTS0+stage, pixel_shader->PSRGBOutputs[stage]);
			if (unique_c0 || stage==0)
			{
				IDirect3DDevice8_SetRenderStateNotInline(global_d3d_device, D3DRS_PSCONSTANT0_0+stage, pixel_shader->PSConstant0[stage]);
			}
			if (unique_c1 || stage==0)
			{
				IDirect3DDevice8_SetRenderStateNotInline(global_d3d_device, D3DRS_PSCONSTANT1_0+stage, pixel_shader->PSConstant1[stage]);
			}
		}

		if (rasterizer_debug_options.statistics_mode==2)
		{
			rasterizer_frame_statistics.pushbuffer_size+= 8*sizeof(DWORD)+combiner_count*(unique_c0+unique_c1+4)*sizeof(DWORD);
		}
	}
	else
	{
		IDirect3DDevice8_SetPixelShaderProgram(global_d3d_device, pixel_shader);

		if (rasterizer_debug_options.statistics_mode==2)
		{
			rasterizer_frame_statistics.pushbuffer_size+= sizeof(D3DPIXELSHADERDEF)-3*sizeof(DWORD);
		}
	}

	return;
}

void rasterizer_set_model_skinning(
	struct render_skinning const *skinning)
{
	short node_index;

	match_assert(RASTERIZER_XBOX_FILE, 2749, skinning);
	match_assert(RASTERIZER_XBOX_FILE, 2750, skinning->node_matrices);
	match_vassert(RASTERIZER_XBOX_FILE, 2751, skinning->node_matrix_count>0 && skinning->node_matrix_count<RASTERIZER_MAXIMUM_NODES_PER_MODEL, "skinning->node_matrix_count>0 && skinning->node_matrix_count<RASTERIZER_MAXIMUM_NODES_PER_MODEL");

	for (node_index= 0; node_index<skinning->node_matrix_count; node_index++)
	{
		real *constants= vsh_constants__nodematrices[node_index];
		real_matrix4x3 const *matrix= &skinning->node_matrices[node_index];
		real scale= matrix->scale;

		constants[0]= scale*matrix->forward.i;
		constants[1]= scale*matrix->left.i;
		constants[2]= scale*matrix->up.i;
		constants[3]= matrix->position.x;
		constants[4]= scale*matrix->forward.j;
		constants[5]= scale*matrix->left.j;
		constants[6]= scale*matrix->up.j;
		constants[7]= matrix->position.y;
		constants[8]= scale*matrix->forward.k;
		constants[9]= scale*matrix->left.k;
		constants[10]= scale*matrix->up.k;
		constants[11]= matrix->position.z;
	}

	IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, -36, vsh_constants__nodematrices, 3*skinning->node_matrix_count);

	if (rasterizer_debug_options.statistics_mode)
	{
		rasterizer_frame_statistics.skinning_total+= 3*skinning->node_matrix_count*sizeof(real)*4;
	}

	return;
}

void code_001460a0(
	void *a)
{
	return;
}

ULONG code_001460b0(
	D3DResource *resource)
{
	return D3DResource_Release(resource);
}

void rasterizer_set_model_lighting_point_light(
	long light_index,
	short light_num,
	struct rasterizer_model_lighting_constants *lighting_constants)
{
	match_assert(RASTERIZER_XBOX_FILE, 2826, lighting_constants);

	if (light_index!=NONE)
	{
		struct rasterizer_light_submit_parameters *light;
		struct rasterizer_point_light_constants *point_light;
		real radius;

		match_vassert(RASTERIZER_XBOX_FILE, 2835, light_index>=0 && light_index<rasterizer_lights.light_count, csprintf(temporary, "### ERROR invalid light index #%d (count=#%d)", light_index, rasterizer_lights.light_count));
		light= &rasterizer_lights.lights[light_index];
		match_assert(RASTERIZER_XBOX_FILE, 2837, light->radius>0.0f);

		point_light= &lighting_constants->point_lights[light_num];
		point_light->position= light->position;
		radius= light->radius;
		point_light->inverse_radius_squared= 1.0f/(radius*radius);
		point_light->forward= light->forward;
		point_light->color= light->color;

		if (light->definition->geometry.runtime_cosine_falloff_angle!=-1.0f)
		{
			point_light->spot_falloff_coefficient_A= 1.0f/(light->definition->geometry.runtime_cosine_falloff_angle-light->definition->geometry.runtime_cosine_cutoff_angle);
			point_light->spot_falloff_coefficient_B= -(point_light->spot_falloff_coefficient_A*light->definition->geometry.runtime_cosine_cutoff_angle);
		}
		else
		{
			point_light->spot_falloff_coefficient_A= 0.0f;
			point_light->spot_falloff_coefficient_B= 1.0f;
		}
	}
	else
	{
		csmemset(&lighting_constants->point_lights[light_num], 0, sizeof(lighting_constants->point_lights[light_num]));
		lighting_constants->point_lights[light_num].spot_falloff_coefficient_A= 0.0f;
		lighting_constants->point_lights[light_num].spot_falloff_coefficient_B= 1.0f;
	}

	return;
}

HRESULT code_00146240(
	D3DSurface *surface,
	D3DSURFACE_DESC *description)
{
	D3DSurface_GetDesc(surface, description);
	return S_OK;
}

HRESULT code_00146250(
	D3DSurface *surface,
	D3DLOCKED_RECT *locked_rect,
	CONST RECT *rect,
	DWORD flags)
{
	D3DSurface_LockRect(surface, locked_rect, rect, flags);
	return S_OK;
}

HRESULT code_00146270(
	D3DSurface *surface)
{
	return S_OK;
}

void rasterizer_set_model_lighting_distant_light(
	struct render_distant_light const *light,
	short light_num,
	struct rasterizer_model_lighting_constants *lighting_constants)
{
	match_assert(RASTERIZER_XBOX_FILE, 2874, lighting_constants);

	if (light)
	{
		lighting_constants->distant_lights[light_num].forward= light->direction;
		lighting_constants->distant_lights[light_num].color= light->color;
	}
	else
	{
		csmemset(&lighting_constants->distant_lights[light_num], 0, sizeof(lighting_constants->distant_lights[light_num]));
	}

	return;
}

void rasterizer_set_model_lighting(
	struct render_lighting const *lighting)
{
	struct rasterizer_model_lighting_constants lighting_constants;

	match_assert(RASTERIZER_XBOX_FILE, 2896, lighting);
	match_vassert(RASTERIZER_XBOX_FILE, 2897, lighting->point_light_count>=0 && lighting->point_light_count<=MAXIMUM_RENDERED_POINT_LIGHTS, "lighting->point_light_count>=0 && lighting->point_light_count<=MAXIMUM_RENDERED_POINT_LIGHTS");
	match_vassert(RASTERIZER_XBOX_FILE, 2898, lighting->distant_light_count>=0 && lighting->distant_light_count<=MAXIMUM_RENDERED_DISTANT_LIGHTS, "lighting->distant_light_count>=0 && lighting->distant_light_count<=MAXIMUM_RENDERED_DISTANT_LIGHTS");

	if (rasterizer_debug_options.model_lighting_ambient>0.0f)
	{
		csmemset(&lighting_constants, 0, sizeof(lighting_constants));
		lighting_constants.ambient.red= lighting_constants.ambient.green= lighting_constants.ambient.blue= rasterizer_debug_options.model_lighting_ambient;
	}
	else
	{
		short light_num;

		for (light_num= 0; light_num<MAXIMUM_RENDERED_POINT_LIGHTS; light_num++)
		{
			rasterizer_set_model_lighting_point_light(lighting->point_light_count>light_num ? lighting->point_light_indices[light_num] : NONE, light_num, &lighting_constants);
		}

		for (light_num= 0; light_num<MAXIMUM_RENDERED_DISTANT_LIGHTS; light_num++)
		{
			rasterizer_set_model_lighting_distant_light(lighting->distant_light_count>light_num ? &lighting->distant_lights[light_num] : NULL, light_num, &lighting_constants);
		}

		lighting_constants.ambient= lighting->ambient_color;
	}

	IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, -79, &lighting_constants, sizeof(lighting_constants)/(sizeof(real)*4));

	if (rasterizer_debug_options.statistics_mode)
	{
		rasterizer_frame_statistics.lighting_total+= sizeof(lighting_constants);
	}

	return;
}

void rasterizer_set_frustum_z(
	real z_near,
	real z_far)
{
	real vsh_constants[8][4];
	short row;
	short column;

	match_assert(RASTERIZER_XBOX_FILE, 2967, global_d3d_device);

	render_camera_hack_frustum_z(&global_window_parameters.frustum, z_near, z_far);

	for (row= 0; row<4; row++)
	{
		for (column= 0; column<4; column++)
		{
			vsh_constants[row][column]=
				global_window_parameters.frustum.world_to_view.n[column][0]*global_window_parameters.frustum.projection_matrix[0][row]+
				global_window_parameters.frustum.projection_matrix[1][row]*global_window_parameters.frustum.world_to_view.n[column][1]+
				global_window_parameters.frustum.world_to_view.n[column][2]*global_window_parameters.frustum.projection_matrix[2][row];
		}
		vsh_constants[row][3]+= global_window_parameters.frustum.projection_matrix[3][row];
	}

	vsh_constants[4][0]= global_window_parameters.camera.position.x;
	vsh_constants[4][1]= global_window_parameters.camera.position.y;
	vsh_constants[4][2]= global_window_parameters.camera.position.z;
	vsh_constants[4][3]= 2.0f;
	vsh_constants[5][0]= global_window_parameters.camera.forward.i;
	vsh_constants[5][1]= global_window_parameters.camera.forward.j;
	vsh_constants[5][2]= global_window_parameters.camera.forward.k;
	vsh_constants[5][3]= 0.5f;
	vsh_constants[6][0]= global_window_parameters.frustum.view_to_world.forward.i;
	vsh_constants[6][1]= global_window_parameters.frustum.view_to_world.forward.j;
	vsh_constants[6][2]= global_window_parameters.frustum.view_to_world.forward.k;
	vsh_constants[6][3]= 1.0f;
	vsh_constants[7][0]= global_window_parameters.frustum.view_to_world.left.i;
	vsh_constants[7][1]= global_window_parameters.frustum.view_to_world.left.j;
	vsh_constants[7][2]= global_window_parameters.frustum.view_to_world.left.k;
	vsh_constants[7][3]= 255.9375f;

	IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, -96, vsh_constants, 8);

	return;
}

void rasterizer_set_stencil_mode(
	short stencil_mode)
{
	match_assert(RASTERIZER_XBOX_FILE, 3034, global_d3d_device);

	if (!rasterizer_debug_options.stencil_mask_enabled)
	{
		stencil_mode= 0;
	}

	if (stencil_mode!=previous_stencil_mode)
	{
		switch (stencil_mode)
		{
		case 0:
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_STENCILENABLE, FALSE);
			break;
		case 1:
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_STENCILENABLE, TRUE);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_STENCILREF, 1);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_STENCILMASK, 1);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_STENCILWRITEMASK, 1);
			break;
		case 2:
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_STENCILENABLE, TRUE);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_STENCILFUNC, D3DCMP_EQUAL);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_STENCILREF, 0);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_STENCILMASK, 1);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_STENCILWRITEMASK, 0);
			break;
		case 3:
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_STENCILENABLE, TRUE);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
			SetRenderStateSmart(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
			SetRenderStateSmart(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
			SetRenderStateSmart(D3DRS_STENCILFUNC, D3DCMP_NOTEQUAL);
			SetRenderStateSmart(D3DRS_STENCILREF, 0);
			SetRenderStateSmart(D3DRS_STENCILMASK, 1);
			SetRenderStateSmart(D3DRS_STENCILWRITEMASK, 0);
			break;
		case 4:
			SetRenderStateSmart(D3DRS_STENCILENABLE, TRUE);
			SetRenderStateSmart(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
			SetRenderStateSmart(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
			SetRenderStateSmart(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
			SetRenderStateSmart(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
			SetRenderStateSmart(D3DRS_STENCILREF, 2);
			SetRenderStateSmart(D3DRS_STENCILMASK, 1);
			SetRenderStateSmart(D3DRS_STENCILWRITEMASK, 2);
			break;
		case 5:
			SetRenderStateSmart(D3DRS_STENCILENABLE, TRUE);
			SetRenderStateSmart(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
			SetRenderStateSmart(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
			SetRenderStateSmart(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
			SetRenderStateSmart(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
			SetRenderStateSmart(D3DRS_STENCILREF, 0);
			SetRenderStateSmart(D3DRS_STENCILMASK, 3);
			SetRenderStateSmart(D3DRS_STENCILWRITEMASK, 0);
			break;
		default:
			match_vassert(RASTERIZER_XBOX_FILE, 3099, FALSE, "### ERROR unsupported stencil mode");
		}

		previous_stencil_mode= stencil_mode;
	}

	return;
}

short rasterizer_get_stencil_mode(
	void)
{
	return previous_stencil_mode;
}

// not bungie code, doesn't use cseries memcpy
#undef memcpy

void SetupSmartStates(
	void)
{
	long state;
	long stage;

	memcpy(renderstate_table, D3D__RenderState, sizeof(renderstate_table));

	for (state= 0; state<D3DTSS_MAX; state++)
	{
		for (stage= 0; stage<D3DTSS_MAXSTAGES; stage++)
		{
			texturestagestate_table[stage][state]= D3D__TextureState[stage][state];
		}
	}

	for (stage= 0; stage<D3DTSS_MAXSTAGES; stage++)
	{
		texture_table[stage]= NULL;
	}

	return;
}

#define memcpy csmemcpy

D3DSurface *rasterizer_get_target(
	short target,
	short mipmap_index)
{
	D3DSurface *surface= NULL;

	switch (target)
	{
	case _rasterizer_target_render_primary:
		match_assert(RASTERIZER_XBOX_FILE, 2232, mipmap_index==0);
		surface= bss_0045e87c;
		break;
	case _rasterizer_target_render_secondary:
		match_assert(RASTERIZER_XBOX_FILE, 2236, mipmap_index==0);
		surface= global_d3d_surface_render_secondary;
		break;
	case _rasterizer_target_shadow_primary:
		match_assert(RASTERIZER_XBOX_FILE, 2240, mipmap_index==0);
		surface= global_d3d_surface_shadow_primary;
		break;
	case _rasterizer_target_shadow_secondary:
		match_assert(RASTERIZER_XBOX_FILE, 2244, mipmap_index==0);
		surface= global_d3d_surface_shadow_secondary;
		break;
	case _rasterizer_target_sun_glow_primary:
		match_assert(RASTERIZER_XBOX_FILE, 2248, mipmap_index==0);
		surface= global_d3d_surface_sun_glow_primary;
		break;
	case _rasterizer_target_sun_glow_secondary:
		match_assert(RASTERIZER_XBOX_FILE, 2252, mipmap_index==0);
		surface= global_d3d_surface_sun_glow_secondary;
		break;
	case _rasterizer_target_water:
		match_vassert(RASTERIZER_XBOX_FILE, 2256, mipmap_index>=0 && mipmap_index<RASTERIZER_TARGET_WATER_MAX_MIPMAP_LEVELS, "mipmap_index>=0 && mipmap_index<RASTERIZER_TARGET_WATER_MAX_MIPMAP_LEVELS");
		surface= global_d3d_surface_water[mipmap_index];
		break;
	default:
		match_vassert(RASTERIZER_XBOX_FILE, 2260, FALSE, "### ERROR unsupported rasterizer target");
	}

	return surface;
}

void rasterizer_set_target(
	short target,
	short mipmap_index,
	D3DCOLOR clear_color,
	boolean clear,
	boolean zbuffer)
{
	D3DSurface *d3d_surface= NULL;
	D3DSurface *d3d_surface_z= NULL;
	D3DVIEWPORT8 viewport;

	switch (target)
	{
	case _rasterizer_target_render_primary:
		match_assert(RASTERIZER_XBOX_FILE, 2280, mipmap_index==0);
		d3d_surface= bss_0045e87c;
		d3d_surface_z= global_d3d_surface_render_primary_z;
		match_assert(RASTERIZER_XBOX_FILE, 2284, d3d_surface);
		break;
	case _rasterizer_target_render_secondary:
		match_assert(RASTERIZER_XBOX_FILE, 2287, mipmap_index==0);
		d3d_surface= global_d3d_surface_render_secondary;
		d3d_surface_z= bss_0045e890 ? bss_0045e890 : global_d3d_surface_render_primary_z;
		match_assert(RASTERIZER_XBOX_FILE, 2290, d3d_surface);
		break;
	case _rasterizer_target_shadow_primary:
		match_assert(RASTERIZER_XBOX_FILE, 2293, mipmap_index==0);
		d3d_surface= global_d3d_surface_shadow_primary;
		match_assert(RASTERIZER_XBOX_FILE, 2295, d3d_surface);
		break;
	case _rasterizer_target_shadow_secondary:
		match_assert(RASTERIZER_XBOX_FILE, 2298, mipmap_index==0);
		d3d_surface= global_d3d_surface_shadow_secondary;
		match_assert(RASTERIZER_XBOX_FILE, 2300, d3d_surface);
		break;
	case _rasterizer_target_sun_glow_primary:
		match_assert(RASTERIZER_XBOX_FILE, 2303, mipmap_index==0);
		d3d_surface= global_d3d_surface_sun_glow_primary;
		match_assert(RASTERIZER_XBOX_FILE, 2305, d3d_surface);
		break;
	case _rasterizer_target_sun_glow_secondary:
		match_assert(RASTERIZER_XBOX_FILE, 2308, mipmap_index==0);
		d3d_surface= global_d3d_surface_sun_glow_secondary;
		match_assert(RASTERIZER_XBOX_FILE, 2310, d3d_surface);
		break;
	case _rasterizer_target_water:
		match_vassert(RASTERIZER_XBOX_FILE, 2313, mipmap_index>=0 && mipmap_index<RASTERIZER_TARGET_WATER_MAX_MIPMAP_LEVELS, "mipmap_index>=0 && mipmap_index<RASTERIZER_TARGET_WATER_MAX_MIPMAP_LEVELS");
		d3d_surface= global_d3d_surface_water[mipmap_index];
		match_assert(RASTERIZER_XBOX_FILE, 2315, d3d_surface);
		break;
	case _rasterizer_target_render_primary_copy:
		match_assert(RASTERIZER_XBOX_FILE, 2331, mipmap_index==0);
		d3d_surface= bss_0045e8cc;
		match_assert(RASTERIZER_XBOX_FILE, 2333, d3d_surface);
		break;
	default:
		match_vassert(RASTERIZER_XBOX_FILE, 2336, FALSE, "### ERROR unsupported rasterizer target");
	}

	match_assert(RASTERIZER_XBOX_FILE, 2340, !zbuffer||d3d_surface_z);
	IDirect3DDevice8_SetRenderTarget(global_d3d_device, d3d_surface, zbuffer ? d3d_surface_z : NULL);

	if (target==_rasterizer_target_render_primary)
	{
		viewport.X= global_window_parameters.camera.viewport_bounds.x0;
		viewport.Y= global_window_parameters.camera.viewport_bounds.y0;
		viewport.Width= global_window_parameters.camera.viewport_bounds.x1-global_window_parameters.camera.viewport_bounds.x0;
		viewport.Height= global_window_parameters.camera.viewport_bounds.y1-global_window_parameters.camera.viewport_bounds.y0;
	}
	else
	{
		D3DSURFACE_DESC d3d_surface_description;

		IDirect3DSurface8_GetDesc(d3d_surface, &d3d_surface_description);
		viewport.X= 0;
		viewport.Y= 0;
		viewport.Width= d3d_surface_description.Width;
		viewport.Height= d3d_surface_description.Height;
	}
	viewport.MinZ= 0.0f;
	viewport.MaxZ= 1.0f;
	IDirect3DDevice8_SetViewport(global_d3d_device, &viewport);

	if (clear)
	{
		DWORD flags;

		if (target==_rasterizer_target_render_primary)
		{
			flags= D3DCLEAR_TARGET;
		}
		else if (target==_rasterizer_target_render_secondary)
		{
			flags= D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER|D3DCLEAR_STENCIL;
		}
		else
		{
			flags= D3DCLEAR_TARGET;
		}

		IDirect3DDevice8_Clear(global_d3d_device, 0, NULL, flags, clear_color, 1.0f, 0);
	}

	return;
}

void rasterizer_set_target_as_texture(
	short stage,
	short target,
	short max_mipmap)
{
	boolean success= TRUE;
	D3DTexture *d3d_texture= NULL;
	D3DBaseTexture *texture;

	switch (target)
	{
	case _rasterizer_target_render_primary:
		texture= bss_0045e874[rasterizer_globals.frame_index&1];
		match_assert(RASTERIZER_XBOX_FILE, 2415, max_mipmap==0);
		if (!texture->Data)
		{
			D3DSurface *d3d_backbuffer;

			IDirect3DDevice8_GetBackBuffer(global_d3d_device, 0, D3DBACKBUFFER_TYPE_MONO, &d3d_backbuffer);
			texture->Common= RASTERIZER_FAKE_SURFACE_COMMON;
			texture->Data= d3d_backbuffer->Data;
			texture->Lock= 0;
			texture->Size= RASTERIZER_FAKE_SURFACE_SIZE;
			texture->Format= RASTERIZER_FAKE_SURFACE_FORMAT;
			D3DCALL(success, IDirect3DSurface8_Release(d3d_backbuffer));
		}
		d3d_texture= (D3DTexture *)bss_0045e874[rasterizer_globals.frame_index&1];
		break;
	case _rasterizer_target_render_secondary:
		match_assert(RASTERIZER_XBOX_FILE, 2457, max_mipmap==0);
		d3d_texture= global_d3d_texture_render_secondary;
		break;
	case _rasterizer_target_shadow_primary:
		match_assert(RASTERIZER_XBOX_FILE, 2461, max_mipmap==0);
		d3d_texture= global_d3d_texture_shadow_primary;
		break;
	case _rasterizer_target_shadow_secondary:
		match_assert(RASTERIZER_XBOX_FILE, 2465, max_mipmap==0);
		d3d_texture= global_d3d_texture_shadow_secondary;
		break;
	case _rasterizer_target_sun_glow_primary:
		match_assert(RASTERIZER_XBOX_FILE, 2469, max_mipmap==0);
		d3d_texture= global_d3d_texture_sun_glow_primary;
		break;
	case _rasterizer_target_sun_glow_secondary:
		match_assert(RASTERIZER_XBOX_FILE, 2473, max_mipmap==0);
		d3d_texture= global_d3d_texture_sun_glow_secondary;
		break;
	case _rasterizer_target_water:
		match_vassert(RASTERIZER_XBOX_FILE, 2477, max_mipmap>=0 && max_mipmap<=RASTERIZER_TARGET_WATER_MAX_MIPMAP_LEVELS, "max_mipmap>=0 && max_mipmap<=RASTERIZER_TARGET_WATER_MAX_MIPMAP_LEVELS");
		d3d_texture= global_d3d_texture_water;
		break;
	case _rasterizer_target_render_primary_copy:
		match_assert(RASTERIZER_XBOX_FILE, 2492, max_mipmap==0);
		d3d_texture= (D3DTexture *)bss_0045e8c8;
		break;
	default:
		match_vassert(RASTERIZER_XBOX_FILE, 2496, FALSE, "### ERROR unsupported rasterizer target");
	}

	match_assert(RASTERIZER_XBOX_FILE, 2499, d3d_texture);

	{
		D3DBaseTexture *water_texture= (D3DBaseTexture *)global_d3d_texture_water;

		if (!max_mipmap)
		{
			max_mipmap= RASTERIZER_TARGET_WATER_MAX_MIPMAP_LEVELS;
		}
		match_vassert(RASTERIZER_XBOX_FILE, 2508, max_mipmap>=0 && max_mipmap<=RASTERIZER_TARGET_WATER_MAX_MIPMAP_LEVELS, "max_mipmap>=0 && max_mipmap<=RASTERIZER_TARGET_WATER_MAX_MIPMAP_LEVELS");
		water_texture->Format= (water_texture->Format&~D3DFORMAT_MIPMAP_MASK)|(max_mipmap<<D3DFORMAT_MIPMAP_SHIFT);
	}

	D3DCALL(success, IDirect3DDevice8_SetTexture(global_d3d_device, stage, (IDirect3DBaseTexture8*)d3d_texture));
	if (!success)
	{
		error(_error_silent, "### ERROR rasterizer_set_target_as_texture failed");
	}

	return;
}

void rasterizer_secondary_render_target_debug(
	rectangle2d const *bounds)
{
	match_assert(RASTERIZER_XBOX_FILE, 2532, bounds);
	match_assert(RASTERIZER_XBOX_FILE, 2533, global_d3d_device);

	if (rasterizer_debug_options.secondary_render_target_debug_enabled && global_window_parameters.rasterizer_target==_rasterizer_target_render_primary)
	{
		real vsh_constants[20];
		short width;
		short height;
		real one_over_width;
		real one_over_height;

		rasterizer_set_target_as_texture(0, _rasterizer_target_render_secondary, 0);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_CCW);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED|D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_BLUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHABLENDENABLE, FALSE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHATESTENABLE, FALSE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZENABLE, FALSE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZBIAS, 0);
		rasterizer_set_vertex_shader_permutation(4, 8, 0);

		width= global_window_parameters.camera.viewport_bounds.x1-global_window_parameters.camera.viewport_bounds.x0;
		height= global_window_parameters.camera.viewport_bounds.y1-global_window_parameters.camera.viewport_bounds.y0;
		one_over_width= 1.0f/(real)width;
		vsh_constants[0]= one_over_width+one_over_width;
		vsh_constants[1]= 0.0f;
		vsh_constants[2]= 0.0f;
		vsh_constants[3]= -1.0f-one_over_width;
		one_over_height= 1.0f/(real)height;
		vsh_constants[4]= 0.0f;
		vsh_constants[5]= -2.0f*one_over_height;
		vsh_constants[6]= 0.0f;
		vsh_constants[7]= one_over_height+1.0f;
		vsh_constants[8]= 0.0f;
		vsh_constants[9]= 0.0f;
		vsh_constants[10]= 0.0f;
		vsh_constants[11]= 0.5f;
		vsh_constants[12]= 0.0f;
		vsh_constants[13]= 0.0f;
		vsh_constants[14]= 0.0f;
		vsh_constants[15]= 1.0f;
		vsh_constants[16]= 320.0f;
		vsh_constants[17]= 240.0f;
		vsh_constants[18]= 0.0f;
		vsh_constants[19]= 1.0f;
		IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, -68, vsh_constants, 5);

		csmemset(&pixel_shader, 0, sizeof(pixel_shader));
		pixel_shader.PSTextureModes= PS_TEXTUREMODES(PS_TEXTUREMODES_PROJECT2D, PS_TEXTUREMODES_NONE, PS_TEXTUREMODES_NONE, PS_TEXTUREMODES_NONE);
		pixel_shader.PSCombinerCount= 1;
		pixel_shader.PSFinalCombinerInputsABCD= 8;
		rasterizer_set_pixel_shader(&pixel_shader);

		IDirect3DDevice8_Begin(global_d3d_device, D3DPT_TRIANGLEFAN);
		IDirect3DDevice8_SetVertexData2s(global_d3d_device, 4, 0, 1);
		IDirect3DDevice8_SetVertexData2s(global_d3d_device, 0, (word)bounds->x0, (word)bounds->y0);
		IDirect3DDevice8_SetVertexData2s(global_d3d_device, 4, 1, 1);
		IDirect3DDevice8_SetVertexData2s(global_d3d_device, 0, (word)bounds->x1, (word)bounds->y0);
		IDirect3DDevice8_SetVertexData2s(global_d3d_device, 4, 1, 0);
		IDirect3DDevice8_SetVertexData2s(global_d3d_device, 0, (word)bounds->x1, (word)bounds->y1);
		IDirect3DDevice8_SetVertexData2s(global_d3d_device, 4, 0, 0);
		IDirect3DDevice8_SetVertexData2s(global_d3d_device, 0, (word)bounds->x0, (word)bounds->y1);
		IDirect3DDevice8_End(global_d3d_device);
	}

	return;
}
