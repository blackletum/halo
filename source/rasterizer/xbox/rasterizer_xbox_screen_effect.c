/*
RASTERIZER_XBOX_SCREEN_EFFECT.C

symbols in this file:
0015F720 01b0:
	_D3DDevice_SetRenderState (0000)
0015F8D0 0050:
	_D3DDevice_SetTextureStageState (0000)
0015F920 0090:
	___reciprocal_vector2d (0000)
0015F9B0 0220:
	_IDirect3DDevice8_SetRenderState@12 (0000)
0015FBD0 0060:
	_IDirect3DDevice8_SetTextureStageState@16 (0000)
0015FC30 0010:
	_IDirect3DDevice8_SetVertexShaderConstant@16 (0000)
0015FC40 0020:
	_IDirect3DDevice8_SetVertexData2f@16 (0000)
0015FC60 0010:
	_IDirect3DDevice8_SetVertexData2s@16 (0000)
0015FC70 0010:
	_IDirect3DDevice8_Begin@8 (0000)
0015FC80 0010:
	_IDirect3DDevice8_End@4 (0000)
0015FC90 0850:
	_rasterizer_screen_effect_set_texture_transforms (0000)
001604E0 0f30:
	__rasterizer_screen_effect (0000)
00161410 0540:
	__rasterizer_screen_flash (0000)
00292390 0019:
	??_C@_0BJ@BEKEHHEJ@v?9?$DOi?$CB?$DN0?40f?5?$CG?$CG?5v?9?$DOj?$CB?$DN0?40f?$AA@ (0000)
002923AC 0002:
	??_C@_01MHEDDDHA@v?$AA@ (0000)
002923B0 003f:
	??_C@_0DP@GDHJCEBP@c?3?2halo?2SOURCE?2rasterizer?2xbox?2r@ (0000)
002923F0 001b:
	??_C@_0BL@MEELOPHA@main_get_window_count?$CI?$CJ?$DM?$DN1?$AA@ (0000)
0029240C 0016:
	??_C@_0BG@OBFLACOO@?$CBparameters?9?$DOvideo_on?$AA@ (0000)
00292424 002a:
	??_C@_0CK@GCKMEOHN@?$CD?$CD?$CD?5ERROR?5rasterizer_screen_effe@ (0000)
00292450 0065:
	??_C@_0GF@LMEHBMJP@IDirect3DDevice8_SetVertexData2f@ (0000)
002924B8 0065:
	??_C@_0GF@CDJNJPAB@IDirect3DDevice8_SetVertexData2f@ (0000)
00292520 004a:
	??_C@_0EK@DDGAKMME@IDirect3DDevice8_SetVertexData2s@ (0000)
00292570 0065:
	??_C@_0GF@CCFPPFDG@IDirect3DDevice8_SetVertexData2f@ (0000)
002925D8 0058:
	??_C@_0FI@MCHFKFGN@IDirect3DDevice8_SetVertexData2s@ (0000)
00292630 0065:
	??_C@_0GF@LNIFHGKI@IDirect3DDevice8_SetVertexData2f@ (0000)
00292698 004b:
	??_C@_0EL@FFKPDIEL@IDirect3DDevice8_SetVertexData2s@ (0000)
002926E4 0004:
	__real@3b088889 (0000)
002926E8 0004:
	__real@3acccccd (0000)
002926EC 0033:
	??_C@_0DD@IJEPJHCB@combiner_count?$DM?$DNRASTERIZER_MAXIM@ (0000)
00292720 003a:
	??_C@_0DK@EJBEKMFA@?$CD?$CD?$CD?5ERROR?5video?5effect?5tried?5to?5@ (0000)
00292760 0084:
	??_C@_0IE@LDDMKLNC@parameters?9?$DOvideo_overbright_mod@ (0000)
002927E8 0044:
	??_C@_0EE@MEDEOJLI@?$CD?$CD?$CD?5ERROR?5non?9convolution?5effect@ (0000)
0029282C 0032:
	??_C@_0DC@CMADNDPH@video?5effect?5noise?5map?5cannot?5be@ (0000)
00292860 0008:
	??_C@_07MACHECCK@pass?$DN?$DN1?$AA@ (0000)
00292868 0008:
	??_C@_07NJDMHDGL@pass?$DN?$DN0?$AA@ (0000)
00292870 002c:
	??_C@_0CM@OFCEIJKA@blur?5effect?5cannot?5specify?5convo@ (0000)
0029289C 002d:
	??_C@_0CN@EJCBMOOJ@video?5effect?5cannot?5specify?5conv@ (0000)
002928CC 0037:
	??_C@_0DH@DCBDBJNG@video?5effect?5cannot?5specify?5nonz@ (0000)
00292904 002d:
	??_C@_0CN@CNLJNHLN@video?5effect?5cannot?5specify?5conv@ (0000)
00292934 0035:
	??_C@_0DF@FNIELJAM@video?5effect?5cannot?5specify?5extr@ (0000)
0029296C 0024:
	??_C@_0CE@MIPIKB@video?5effect?5must?5specify?5noise?5@ (0000)
00292990 0027:
	??_C@_0CH@KIKPHJLK@video?5effect?5must?5specify?5scanli@ (0000)
002929B8 0028:
	??_C@_0CI@PFHEHAHJ@?$CD?$CD?$CD?5ERROR?5unsupported?5screen?5fla@ (0000)
*/

/* ---------- headers */

#include "cseries.h"
#include "cseries_windows.h"
#include "errors.h"
#include "real_math.h"
#include "bitmaps.h"
#include "rasterizer.h"
#include "xbox/rasterizer_xbox.h"

/* ---------- constants */

enum
{
	RASTERIZER_MAXIMUM_COMBINER_STAGES= 8
};

enum
{
	_screen_flash_type_none= 0,
	_screen_flash_type_lighten,
	_screen_flash_type_darken,
	_screen_flash_type_max,
	_screen_flash_type_min,
	_screen_flash_type_tint,
	_screen_flash_type_invert,
	NUMBER_OF_SCREEN_FLASH_TYPES
};

enum
{
	_rasterizer_screen_effect_convolution_type_none= 0,
	_rasterizer_screen_effect_convolution_type_blur,
	_rasterizer_screen_effect_convolution_type_warp,
	NUMBER_OF_RASTERIZER_SCREEN_EFFECT_CONVOLUTION_TYPES
};

enum
{
	_rasterizer_screen_effect_video_overbright_mode_none= 0,
	_rasterizer_screen_effect_video_overbright_mode_2x,
	_rasterizer_screen_effect_video_overbright_mode_4x,
	NUMBER_OF_RASTERIZER_SCREEN_EFFECT_VIDEO_OVERBRIGHT_MODES
};

/* ---------- macros */

#define VSDE_VERTEX 0

/* ---------- prototypes */

short main_get_window_count(void);
struct rasterizer_screen_effect_parameters const *rasterizer_screen_effect_get_cinematic_parameters(struct rasterizer_screen_effect_parameters const *parameters);
unsigned long real_alpha_to_pixel32(real alpha);
unsigned long real_rgb_color_to_pixel32(real_rgb_color const *color);
boolean rasterizer_set_texture_bitmap_data(short stage, struct bitmap_data const *bitmap);
void *rasterizer_set_target_as_texture(short stage, short target, short maximum_mipmap_index);
void rasterizer_set_target(short target, short mipmap_index, unsigned long background_color, boolean clear, boolean zbuffer);

unsigned long real_argb_color_to_pixel32(real_argb_color const *color);
void SetRenderStateSmart(D3DRENDERSTATETYPE state, DWORD value);
void rasterizer_set_vertex_shader_permutation(short vertex_shader, unsigned long flags, short permutation);
void rasterizer_set_pixel_shader(D3DPIXELSHADERDEF *pixel_shader);

static real_vector2d __reciprocal_vector2d(real_vector2d const *v);
static void rasterizer_screen_effect_set_texture_transforms(struct rasterizer_screen_effect_parameters const *parameters, short pass, short pass_count);

/* ---------- globals */

extern struct rasterizer_window_begin_parameters global_window_parameters;
extern D3DPIXELSHADERDEF pixel_shader;

/* ---------- private code */

static real_vector2d __reciprocal_vector2d(
	real_vector2d const *v)
{
	real_vector2d result;

	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_screen_effect.c", 30, v);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_screen_effect.c", 31, v->i!=0.0f && v->j!=0.0f);
	result.i= 1.0f/v->i;
	result.j= 1.0f/v->j;

	return result;
}

// TODO: stack layout differs (frame 0x10c vs 0x108), warp offset for stage 1 and real_local_random() usage codegen differ
static void rasterizer_screen_effect_set_texture_transforms(
	struct rasterizer_screen_effect_parameters const *parameters,
	short pass,
	short pass_count)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_screen_effect.c", 47, parameters);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_screen_effect.c", 48, global_d3d_device);

	{
		struct bitmap_data framebuffer=
		{
			'bitm',
			global_window_parameters.camera.viewport_bounds.x1-global_window_parameters.camera.viewport_bounds.x0,
			global_window_parameters.camera.viewport_bounds.y1-global_window_parameters.camera.viewport_bounds.y0,
			1,
			_bitmap_type_2d,
			NONE,
			FLAG(_bitmap_linear_bit)
		};
		real vertex_constants[8][4];
		real_vector2d sizes[4];
		real_vector2d scale3;
		real_vector2d one;
		real_vector2d scale2, scale1, scale0;
		struct bitmap_data *bitmap1, *bitmap2;
		real viewport_width, viewport_height;
		struct bitmap_data *bitmap0;

		if (parameters->convolution_mask && (pass>0 || pass_count==1 || parameters->convolution_type))
		{
			bitmap0= parameters->convolution_mask;
		}
		else
		{
			bitmap0= &framebuffer;
		}
		bitmap1= parameters->video_on ? parameters->video_scanline_map : &framebuffer;
		bitmap2= parameters->video_on ? parameters->video_noise_map : &framebuffer;

		sizes[0].i= (real)bitmap0->width;
		sizes[0].j= (real)bitmap0->height;
		sizes[2].i= (real)bitmap1->width;
		sizes[2].j= (real)bitmap1->height;
		sizes[3].i= (real)bitmap2->width;
		sizes[3].j= (real)bitmap2->height;
		viewport_width= (real)framebuffer.width;
		viewport_height= (real)framebuffer.height;
		sizes[1].i= viewport_width;
		sizes[1].j= viewport_height;
		one.i= 1.0f;
		one.j= 1.0f;

		scale0= TEST_FLAG(bitmap0->flags, _bitmap_linear_bit) ? one : __reciprocal_vector2d(&sizes[0]);
		scale1= TEST_FLAG(bitmap1->flags, _bitmap_linear_bit) ? one : __reciprocal_vector2d(&sizes[2]);
		scale2= TEST_FLAG(bitmap2->flags, _bitmap_linear_bit) ? one : __reciprocal_vector2d(&sizes[3]);
		scale3= TEST_FLAG(framebuffer.flags, _bitmap_linear_bit) ? one : __reciprocal_vector2d(&sizes[1]);

		vertex_constants[0][0]= scale0.i;
		vertex_constants[0][1]= 0.0f;
		vertex_constants[0][2]= 0.0f;
		vertex_constants[0][3]= (sizes[0].i+1.0f-viewport_width)*scale0.i*0.5f;
		vertex_constants[1][0]= 0.0f;
		vertex_constants[1][1]= scale0.j;
		vertex_constants[1][2]= 0.0f;
		vertex_constants[1][3]= (sizes[0].j+1.0f-viewport_height)*scale0.j*0.5f;
		vertex_constants[2][0]= scale1.i;
		vertex_constants[2][1]= 0.0f;
		vertex_constants[2][2]= 0.0f;
		vertex_constants[2][3]= (sizes[2].i+1.0f-viewport_width)*scale1.i*0.5f;
		vertex_constants[3][0]= 0.0f;
		vertex_constants[3][1]= scale1.j;
		vertex_constants[3][2]= 0.0f;
		vertex_constants[3][3]= (sizes[2].j+1.0f-viewport_height)*scale1.j*0.5f;
		vertex_constants[4][0]= scale2.i;
		vertex_constants[4][1]= 0.0f;
		vertex_constants[4][2]= 0.0f;
		vertex_constants[4][3]= (sizes[3].i+1.0f-viewport_width)*scale2.i*0.5f;
		vertex_constants[5][0]= 0.0f;
		vertex_constants[5][1]= scale2.j;
		vertex_constants[5][2]= 0.0f;
		vertex_constants[5][3]= (sizes[3].j+1.0f-viewport_height)*scale2.j*0.5f;
		vertex_constants[6][0]= scale3.i;
		vertex_constants[6][1]= 0.0f;
		vertex_constants[6][2]= 0.0f;
		vertex_constants[6][3]= (sizes[1].i+1.0f-viewport_width)*scale3.i*0.5f;
		vertex_constants[7][0]= 0.0f;
		vertex_constants[7][1]= scale3.j;
		vertex_constants[7][2]= 0.0f;
		vertex_constants[7][3]= (sizes[1].j+1.0f-viewport_height)*scale3.j*0.5f;

		{
			long window_center_x= (global_window_parameters.camera.window_bounds.x1+global_window_parameters.camera.window_bounds.x0)/2;
			long window_center_y= (global_window_parameters.camera.window_bounds.y1+global_window_parameters.camera.window_bounds.y0)/2;
			short offset_x= (global_window_parameters.camera.viewport_bounds.x0+global_window_parameters.camera.viewport_bounds.x1)/2-window_center_x;
			short offset_y= (global_window_parameters.camera.viewport_bounds.y0+global_window_parameters.camera.viewport_bounds.y1)/2-window_center_y;

			if (bitmap0==&framebuffer)
			{
				vertex_constants[0][3]+= global_window_parameters.camera.viewport_bounds.x0;
				vertex_constants[1][3]+= global_window_parameters.camera.viewport_bounds.y0;
			}
			else if (bitmap0==parameters->convolution_mask)
			{
				vertex_constants[0][3]+= offset_x*scale0.i;
				vertex_constants[1][3]+= offset_y*scale0.j;
			}

			if (bitmap1==&framebuffer)
			{
				vertex_constants[2][3]+= global_window_parameters.camera.viewport_bounds.x0;
				vertex_constants[3][3]+= global_window_parameters.camera.viewport_bounds.y0;
			}
			else if (bitmap1==parameters->convolution_mask)
			{
				vertex_constants[2][3]+= offset_x*scale1.i;
				vertex_constants[3][3]+= offset_y*scale1.j;
			}
		}

		if (parameters->convolution_type==_rasterizer_screen_effect_convolution_type_blur)
		{
			real radius= parameters->convolution_radius;

			match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_screen_effect.c", 176, !parameters->video_on);
			match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_screen_effect.c", 177, main_get_window_count()<=1);

			vertex_constants[0][3]+= parameters->convolution_mask ? 0.0f : scale0.i*radius;
			vertex_constants[1][3]+= parameters->convolution_mask ? 0.0f : scale0.j*radius;
			vertex_constants[2][3]-= scale1.i*radius;
			vertex_constants[3][3]-= scale1.j*radius;
			vertex_constants[4][3]+= scale2.i*radius;
			vertex_constants[5][3]-= scale2.j*radius;
			vertex_constants[6][3]-= scale3.i*radius;
			vertex_constants[7][3]+= scale3.j*radius;
			IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, -81, vertex_constants, 8);
		}
		else if (parameters->convolution_type==_rasterizer_screen_effect_convolution_type_warp)
		{
			real radius= parameters->convolution_radius;
			real offset0= parameters->convolution_mask ? 0.0f : -radius;
			real offset3= parameters->convolution_mask ? -radius : radius+radius;

			match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_screen_effect.c", 198, !parameters->video_on);
			match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_screen_effect.c", 199, main_get_window_count()<=1);

			vertex_constants[0][0]*= 1.0f-offset0/sizes[0].i;
			vertex_constants[1][1]*= 1.0f-offset0/sizes[0].j;
			vertex_constants[2][0]*= 1.0f-0.0f/sizes[2].i;
			vertex_constants[3][1]*= 1.0f-0.0f/sizes[2].j;
			vertex_constants[4][0]*= 1.0f-radius/sizes[3].i;
			vertex_constants[5][1]*= 1.0f-radius/sizes[3].j;
			vertex_constants[6][0]*= 1.0f-offset3/sizes[1].i;
			vertex_constants[7][1]*= 1.0f-offset3/sizes[1].j;
			vertex_constants[0][3]+= offset0*0.5f;
			vertex_constants[1][3]+= offset0*0.5f;
			vertex_constants[2][3]+= 0.0f;
			vertex_constants[3][3]+= 0.0f;
			vertex_constants[4][3]+= radius*0.5f;
			vertex_constants[5][3]+= radius*0.5f;
			vertex_constants[6][3]+= offset3*0.5f;
			vertex_constants[7][3]+= offset3*0.5f;
			IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, -81, vertex_constants, 8);
		}
		else
		{
			if (pass==1 && parameters->video_on)
			{
				match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_screen_effect.c", 223, main_get_window_count()<=1);

				vertex_constants[4][3]+= scale2.i*real_local_random()*sizes[3].i;
				vertex_constants[5][3]+= scale2.j*real_local_random()*sizes[3].j;
			}
			IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, -81, vertex_constants, 8);
		}
	}

	return;
}

/* ---------- public code */

// TODO: register allocation differs in the pass loop (pass/parameters/source target registers)
void _rasterizer_screen_effect(
	struct rasterizer_screen_effect_parameters const *parameters)
{
	boolean success= TRUE;

	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_screen_effect.c", 251, global_d3d_device);

	rasterizer_profile_begin(_rasterizer_profile_screen_effect);

	parameters= rasterizer_screen_effect_get_cinematic_parameters(parameters);
	if (parameters &&
		(parameters->convolution_type!=_rasterizer_screen_effect_convolution_type_none ||
		parameters->convolution_mask ||
		parameters->filter_light_enhancement_intensity>0.0f ||
		parameters->filter_desaturation_intensity>0.0f ||
		parameters->video_on) &&
		rasterizer_debug_options.screen_effects_enabled &&
		global_window_parameters.rasterizer_target==0)
	{
		short pass_count= 2*(parameters->convolution_extra_passes+1);
		short pass;

		if (parameters->video_on)
		{
			match_vassert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_screen_effect.c", 276, parameters->video_scanline_map, "video effect must specify scanline map");
			match_vassert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_screen_effect.c", 277, parameters->video_noise_map, "video effect must specify noise map");
			match_vassert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_screen_effect.c", 278, parameters->convolution_extra_passes==0, "video effect cannot specify extra convolution passes");
			match_vassert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_screen_effect.c", 279, parameters->convolution_type==_rasterizer_screen_effect_convolution_type_none, "video effect cannot specify convolution type");
			match_vassert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_screen_effect.c", 280, parameters->convolution_radius==0.0f, "video effect cannot specify nonzero convolution radius");
			match_vassert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_screen_effect.c", 281, !parameters->convolution_mask, "video effect cannot specify convolution mask");
		}
		match_vassert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_screen_effect.c", 286, parameters->convolution_type!=_rasterizer_screen_effect_convolution_type_blur || !parameters->convolution_mask, "blur effect cannot specify convolution mask");

		rasterizer_set_vertex_shader_permutation(38, 8, 0);

		for (pass= 0; pass<pass_count; pass++)
		{
			short source_target, destination_target;
			short combiner_count;
			real_rectangle2d vertex_bounds;
			short viewport_width, viewport_height;

			if (pass_count==1)
			{
				match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_screen_effect.c", 313, pass==0);
				source_target= NONE;
				destination_target= NONE;
			}
			else if ((pass&1)==0)
			{
				source_target= 0;
				destination_target= 7;
			}
			else
			{
				source_target= 7;
				destination_target= 0;
			}

			if ((pass&1) && parameters->video_on)
			{
				match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_screen_effect.c", 334, pass==1);

				rasterizer_set_target_as_texture(0, source_target, 0);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MAGFILTER, D3DTEXF_POINT);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MINFILTER, D3DTEXF_POINT);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MIPFILTER, D3DTEXF_POINT);

				rasterizer_set_texture_bitmap_data(1, parameters->video_scanline_map);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MAGFILTER, D3DTEXF_POINT);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MINFILTER, D3DTEXF_POINT);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 1, D3DTSS_MIPFILTER, D3DTEXF_POINT);

				match_vassert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_screen_effect.c", 351, !TEST_FLAG(parameters->video_noise_map->flags, _bitmap_linear_bit), "video effect noise map cannot be in linear format");
				rasterizer_set_texture_bitmap_data(2, parameters->video_noise_map);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_ADDRESSU, D3DTADDRESS_WRAP);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
				IDirect3DDevice8_SetTextureStageState(global_d3d_device, 2, D3DTSS_MIPFILTER, D3DTEXF_POINT);
			}
			else
			{
				short stage;

				for (stage= 0; stage<4; stage++)
				{
					boolean stage_valid= FALSE;

					if (parameters->convolution_type==_rasterizer_screen_effect_convolution_type_none)
					{
						if (pass_count==1)
						{
							match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_screen_effect.c", 371, pass==0);
							if (stage==0)
							{
								rasterizer_set_texture_bitmap_data(0, parameters->convolution_mask);
								stage_valid= TRUE;
							}
						}
						else if (pass==0)
						{
							if (stage==0)
							{
								rasterizer_set_target_as_texture(0, source_target, 0);
								stage_valid= TRUE;
							}
						}
						else if (pass==1)
						{
							if (parameters->convolution_mask)
							{
								if (stage==0)
								{
									rasterizer_set_texture_bitmap_data(0, parameters->convolution_mask);
									stage_valid= TRUE;
								}
								else if (stage==1)
								{
									rasterizer_set_target_as_texture(1, source_target, 0);
									stage_valid= TRUE;
								}
							}
							else if (stage==0)
							{
								rasterizer_set_target_as_texture(0, source_target, 0);
								stage_valid= TRUE;
							}
						}
						else
						{
							match_vassert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_screen_effect.c", 398, FALSE, "### ERROR non-convolution effect tried to render more than 2 passes");
						}
					}
					else
					{
						if (parameters->convolution_mask && stage==0)
						{
							rasterizer_set_texture_bitmap_data(0, parameters->convolution_mask);
							stage_valid= TRUE;
						}
						else if (stage==0)
						{
							rasterizer_set_target_as_texture(0, source_target, 0);
							stage_valid= TRUE;
						}
						else if (stage==1)
						{
							rasterizer_set_target_as_texture(1, source_target, 0);
							stage_valid= TRUE;
						}
						else if (stage==2)
						{
							rasterizer_set_target_as_texture(2, source_target, 0);
							stage_valid= TRUE;
						}
						else if (stage==3)
						{
							rasterizer_set_target_as_texture(3, source_target, 0);
							stage_valid= TRUE;
						}
					}

					if (stage_valid)
					{
						IDirect3DDevice8_SetTextureStageState(global_d3d_device, stage, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
						IDirect3DDevice8_SetTextureStageState(global_d3d_device, stage, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
						IDirect3DDevice8_SetTextureStageState(global_d3d_device, stage, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
						IDirect3DDevice8_SetTextureStageState(global_d3d_device, stage, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
						IDirect3DDevice8_SetTextureStageState(global_d3d_device, stage, D3DTSS_MIPFILTER, D3DTEXF_POINT);
					}
				}
			}

			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_NONE);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED|D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_BLUE);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHABLENDENABLE, FALSE);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHATESTENABLE, FALSE);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZENABLE, FALSE);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZBIAS, 0);

			rasterizer_screen_effect_set_texture_transforms(parameters, pass, pass_count);

			if (destination_target!=NONE)
			{
				rasterizer_set_target(destination_target, 0, 0, FALSE, FALSE);
			}

			if (parameters->video_on)
			{
				csmemset(&pixel_shader, 0, sizeof(pixel_shader));
				if (pass==0)
				{
					pixel_shader.PSTextureModes= 0x1;
					pixel_shader.PSCombinerCount= 1;
					pixel_shader.PSFinalCombinerInputsABCD= 0x8;
				}
				else if (pass==1)
				{
					long overbright_shifts[NUMBER_OF_RASTERIZER_SCREEN_EFFECT_VIDEO_OVERBRIGHT_MODES]= {0x0, 0x10, 0x20};

					pixel_shader.PSTextureModes= 0x421;
					pixel_shader.PSCombinerCount= 4;
					pixel_shader.PSConstant0[0]= real_alpha_to_pixel32(PIN(parameters->video_noise_intensity, 0.0f, 1.0f));
					pixel_shader.PSAlphaInputs[0]= 0x3120111a;
					pixel_shader.PSAlphaOutputs[0]= 0xc00;
					pixel_shader.PSRGBInputs[0]= 0x3120110a;
					pixel_shader.PSRGBOutputs[0]= 0xc00;
					pixel_shader.PSRGBInputs[1]= 0x0c091c19;
					pixel_shader.PSRGBOutputs[1]= 0xc4;
					pixel_shader.PSRGBInputs[2]= 0x08080000;
					pixel_shader.PSRGBOutputs[2]= 0xd0;
					match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_screen_effect.c", 497, parameters->video_overbright_mode>=0 && parameters->video_overbright_mode<NUMBER_OF_RASTERIZER_SCREEN_EFFECT_VIDEO_OVERBRIGHT_MODES);
					pixel_shader.PSRGBInputs[3]= 0x0d0d0820;
					pixel_shader.PSRGBOutputs[3]= (overbright_shifts[parameters->video_overbright_mode]<<12)|0xd8;
					pixel_shader.PSFinalCombinerInputsABCD= 0x2c0d0800;
					pixel_shader.PSFinalCombinerInputsEFG= 0x400;
					IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHABLENDENABLE, TRUE);
					IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_SRCBLEND, D3DBLEND_INVSRCALPHA);
					IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_DESTBLEND, D3DBLEND_ZERO);
					IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_BLENDOP, D3DBLENDOP_ADD);
				}
				else
				{
					match_vassert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_screen_effect.c", 513, FALSE, "### ERROR video effect tried to render more than 2 passes");
				}
				rasterizer_set_pixel_shader(&pixel_shader);
			}
			else
			{
				long last_pass;
				long light_enhancement_input, desaturation_input;

				csmemset(&pixel_shader, 0, sizeof(pixel_shader));
				combiner_count= 0;
				if (parameters->convolution_type==_rasterizer_screen_effect_convolution_type_none)
				{
					if (pass_count==1)
					{
						match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_screen_effect.c", 529, pass==0);
						pixel_shader.PSTextureModes= 0x1;
						pixel_shader.PSRGBInputs[0]= 0x08200000;
						pixel_shader.PSRGBOutputs[0]= 0xc0;
						combiner_count= 1;
						pixel_shader.PSFinalCombinerInputsEFG= 0x800;
						pixel_shader.PSFinalCombinerInputsABCD= 0xc;
					}
					else if (pass==0)
					{
						pixel_shader.PSTextureModes= 0x1;
						pixel_shader.PSRGBInputs[0]= 0x08200000;
						pixel_shader.PSRGBOutputs[0]= 0xc0;
						combiner_count= 1;
						pixel_shader.PSFinalCombinerInputsEFG= 0x0;
						pixel_shader.PSFinalCombinerInputsABCD= 0xc;
					}
					else if (pass==1)
					{
						pixel_shader.PSFinalCombinerInputsABCD= 0xc;
						combiner_count= 1;
						pixel_shader.PSRGBOutputs[0]= 0xc0;
						pixel_shader.PSTextureModes= 0x21;
						if (parameters->convolution_mask)
						{
							pixel_shader.PSRGBInputs[0]= 0x09200000;
							pixel_shader.PSFinalCombinerInputsEFG= 0x800;
						}
						else
						{
							pixel_shader.PSRGBInputs[0]= 0x08200000;
							pixel_shader.PSFinalCombinerInputsEFG= 0x0;
						}
					}
					else
					{
						match_vassert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_screen_effect.c", 584, FALSE, "### ERROR non-convolution effect tried to render more than 2 passes");
					}
				}
				else
				{
					pixel_shader.PSTextureModes= 0x8421;
					if (parameters->convolution_mask)
					{
						pixel_shader.PSRGBInputs[0]= 0x89208a20;
						pixel_shader.PSRGBOutputs[0]= 0xc00;
						pixel_shader.PSConstant0[1]= real_alpha_to_pixel32(1.0f/3.0f);
						pixel_shader.PSRGBInputs[1]= 0xcc118b11;
						pixel_shader.PSRGBOutputs[1]= 0xc00;
						pixel_shader.PSRGBInputs[2]= 0xcc20a020;
						pixel_shader.PSRGBOutputs[2]= 0xc00;
						pixel_shader.PSRGBInputs[3]= 0x3809180c;
						pixel_shader.PSRGBOutputs[3]= 0xc00;
						combiner_count= 4;
						pixel_shader.PSFinalCombinerInputsEFG= 0x800;
					}
					else
					{
						pixel_shader.PSRGBInputs[0]= 0x88208920;
						pixel_shader.PSRGBOutputs[0]= 0x30c00;
						pixel_shader.PSRGBInputs[1]= 0x8a208b20;
						pixel_shader.PSRGBOutputs[1]= 0x30d00;
						pixel_shader.PSRGBInputs[2]= 0xcc20cd20;
						pixel_shader.PSRGBOutputs[2]= 0x30c00;
						pixel_shader.PSRGBInputs[3]= 0xcc20a020;
						pixel_shader.PSRGBOutputs[3]= 0xc00;
						combiner_count= 4;
						pixel_shader.PSFinalCombinerInputsEFG= 0x0;
					}
					pixel_shader.PSFinalCombinerInputsABCD= 0xc;
				}

				light_enhancement_input= parameters->filter_light_enhancement_uses_convolution_mask ? 0x68 : 0x20;
				desaturation_input= parameters->filter_desaturation_uses_convolution_mask ? 0x68 : 0x20;
				pixel_shader.PSConstant0[combiner_count]= real_alpha_to_pixel32(parameters->filter_light_enhancement_intensity);
				pixel_shader.PSConstant1[combiner_count]= real_alpha_to_pixel32(parameters->filter_desaturation_intensity);
				pixel_shader.PSAlphaInputs[combiner_count]= (light_enhancement_input<<16)|desaturation_input|0x11001200;
				pixel_shader.PSAlphaOutputs[combiner_count]= 0xcd;

				last_pass= pass_count-1;
				if (pass==last_pass && parameters->filter_light_enhancement_intensity>0.0f)
				{
					pixel_shader.PSRGBInputs[combiner_count]= 0x2c2c0000;
					pixel_shader.PSRGBOutputs[combiner_count]= 0xd00;
					combiner_count++;
					pixel_shader.PSRGBInputs[combiner_count]= 0x0d0d0000;
					pixel_shader.PSRGBOutputs[combiner_count]= 0xd00;
					combiner_count++;
					pixel_shader.PSFinalCombinerInputsABCD= 0x3c0c2d00;
					pixel_shader.PSFinalCombinerInputsEFG= (parameters->convolution_mask ? 0x8 : 0x0)<<8;
				}

				if (pass==last_pass && parameters->filter_desaturation_intensity>0.0f)
				{
					real_rgb_color one_third= {1.0f/3.0f, 1.0f/3.0f, 1.0f/3.0f};

					if (parameters->filter_light_enhancement_intensity>0.0f)
					{
						pixel_shader.PSConstant0[combiner_count]= real_alpha_to_pixel32(parameters->filter_light_enhancement_intensity);
						pixel_shader.PSRGBInputs[combiner_count]= 0x3c0c1c2d;
						pixel_shader.PSRGBOutputs[combiner_count]= 0xc00;
						combiner_count++;
					}
					pixel_shader.PSConstant0[combiner_count]= real_rgb_color_to_pixel32(&one_third);
					pixel_shader.PSRGBInputs[combiner_count]= 0x0c010000;
					pixel_shader.PSRGBOutputs[combiner_count]= 0x20d0;
					combiner_count++;
					if (parameters->filter_desaturation_is_additive)
					{
						pixel_shader.PSFinalCombinerConstant0= real_rgb_color_to_pixel32(&parameters->filter_desaturation_tint);
						pixel_shader.PSFinalCombinerInputsABCD= 0x1d0f000c;
						pixel_shader.PSFinalCombinerInputsEFG= ((parameters->convolution_mask ? 0x8 : 0x0)|0x10d00)<<8;
					}
					else
					{
						pixel_shader.PSFinalCombinerConstant0= real_rgb_color_to_pixel32(&parameters->filter_desaturation_tint);
						pixel_shader.PSFinalCombinerInputsABCD= 0x1d0f0c00;
						pixel_shader.PSFinalCombinerInputsEFG= ((parameters->convolution_mask ? 0x8 : 0x0)|0x10d00)<<8;
					}
				}

				match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_screen_effect.c", 705, combiner_count<=RASTERIZER_MAXIMUM_COMBINER_STAGES);
				pixel_shader.PSCombinerCount= combiner_count|0x11000;
				rasterizer_set_pixel_shader(&pixel_shader);

				if (pass_count==1)
				{
					IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHABLENDENABLE, TRUE);
					IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_SRCBLEND, D3DBLEND_ZERO);
					SetRenderStateSmart(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
					SetRenderStateSmart(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				}
				else if (pass==last_pass)
				{
					SetRenderStateSmart(D3DRS_ALPHABLENDENABLE, TRUE);
					SetRenderStateSmart(D3DRS_SRCBLEND, D3DBLEND_INVSRCALPHA);
					SetRenderStateSmart(D3DRS_DESTBLEND, D3DBLEND_ZERO);
					SetRenderStateSmart(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				}
			}

			viewport_height= global_window_parameters.camera.viewport_bounds.y1-global_window_parameters.camera.viewport_bounds.y0;
			viewport_width= global_window_parameters.camera.viewport_bounds.x1-global_window_parameters.camera.viewport_bounds.x0;
			if (pass==0 && main_get_window_count()>1 && pass_count!=1)
			{
				vertex_bounds.x0= (real)(2*global_window_parameters.camera.viewport_bounds.x0)*(1.0f/640.0f)-1.0f;
				vertex_bounds.x1= (real)(2*global_window_parameters.camera.viewport_bounds.x1)*(1.0f/640.0f)-1.0f;
				vertex_bounds.y0= (real)(-2*global_window_parameters.camera.viewport_bounds.y0)*(1.0f/480.0f)+1.0f;
				vertex_bounds.y1= (real)(-2*global_window_parameters.camera.viewport_bounds.y1)*(1.0f/480.0f)+1.0f;
			}
			else
			{
				vertex_bounds.y1= -1.0f;
				vertex_bounds.x0= -1.0f;
				vertex_bounds.y0= 1.0f;
				vertex_bounds.x1= 1.0f;
			}

			D3DCALL(success, IDirect3DDevice8_Begin(global_d3d_device, D3DPT_TRIANGLEFAN));
			D3DCALL(success, IDirect3DDevice8_SetVertexData2s(global_d3d_device, 4, 0, viewport_height));
			D3DCALL(success, IDirect3DDevice8_SetVertexData2f(global_d3d_device, VSDE_VERTEX, vertex_bounds.x0, vertex_bounds.y1));
			D3DCALL(success, IDirect3DDevice8_SetVertexData2s(global_d3d_device, 4, viewport_width, viewport_height));
			D3DCALL(success, IDirect3DDevice8_SetVertexData2f(global_d3d_device, VSDE_VERTEX, vertex_bounds.x1, vertex_bounds.y1));
			D3DCALL(success, IDirect3DDevice8_SetVertexData2s(global_d3d_device, 4, viewport_width, 0));
			D3DCALL(success, IDirect3DDevice8_SetVertexData2f(global_d3d_device, VSDE_VERTEX, vertex_bounds.x1, vertex_bounds.y0));
			D3DCALL(success, IDirect3DDevice8_SetVertexData2s(global_d3d_device, 4, 0, 0));
			D3DCALL(success, IDirect3DDevice8_SetVertexData2f(global_d3d_device, VSDE_VERTEX, vertex_bounds.x0, vertex_bounds.y0));
			D3DCALL(success, IDirect3DDevice8_End(global_d3d_device));
		}

		rasterizer_set_target(global_window_parameters.rasterizer_target, 0, 0, FALSE, TRUE);
	}

	rasterizer_profile_end(_rasterizer_profile_screen_effect);

	if (!success)
	{
		error(_error_silent, "### ERROR rasterizer_screen_effect failed");
	}

	return;
}

// TODO: default case reloads inverse color in original; viewport width/height instruction scheduling differs
void _rasterizer_screen_flash(
	void)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_screen_effect.c", 786, global_d3d_device);

	rasterizer_profile_begin(_rasterizer_profile_screen_flash);

	if (rasterizer_debug_options.screen_flash_enabled &&
		global_window_parameters.screen_flash.type!=_screen_flash_type_none)
	{
		real_argb_color color, inverse_color;
		unsigned long pixel_color, inverse_pixel_color;
		unsigned long rgb_inputs, alpha_inputs;
		real vertex_constants[5][4];

		color.alpha= global_window_parameters.screen_flash.intensity*global_window_parameters.screen_flash.color.alpha;
		color.red= global_window_parameters.screen_flash.color.red*global_window_parameters.screen_flash.intensity;
		color.green= global_window_parameters.screen_flash.color.green*global_window_parameters.screen_flash.intensity;
		color.blue= global_window_parameters.screen_flash.color.blue*global_window_parameters.screen_flash.intensity;
		inverse_color.alpha= color.alpha;
		inverse_color.red= (1.0f-global_window_parameters.screen_flash.color.red)*global_window_parameters.screen_flash.intensity;
		inverse_color.green= (1.0f-global_window_parameters.screen_flash.color.green)*global_window_parameters.screen_flash.intensity;
		inverse_color.blue= (1.0f-global_window_parameters.screen_flash.color.blue)*global_window_parameters.screen_flash.intensity;
		pixel_color= real_argb_color_to_pixel32(&color);
		inverse_pixel_color= real_argb_color_to_pixel32(&inverse_color);
		rgb_inputs= 0;
		alpha_inputs= 0;

		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_CCW);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED|D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_BLUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHABLENDENABLE, TRUE);

		switch (global_window_parameters.screen_flash.type)
		{
		case _screen_flash_type_lighten:
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_SRCBLEND, D3DBLEND_ONE);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_BLENDOP, D3DBLENDOP_ADD);
			rgb_inputs= 0x01200000;
			alpha_inputs= 0x11200000;
			break;
		case _screen_flash_type_darken:
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_SRCBLEND, D3DBLEND_ONE);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_DESTBLEND, D3DBLEND_ONE);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
			rgb_inputs= 0x01200000;
			alpha_inputs= 0x11200000;
			break;
		case _screen_flash_type_max:
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_SRCBLEND, D3DBLEND_INVDESTCOLOR);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_DESTBLEND, D3DBLEND_INVCONSTANTCOLOR);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_BLENDOP, D3DBLENDOP_MAX);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_BLENDCOLOR, pixel_color);
			rgb_inputs= 0x01201140;
			alpha_inputs= 0;
			break;
		case _screen_flash_type_min:
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_SRCBLEND, D3DBLEND_INVDESTCOLOR);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_DESTBLEND, D3DBLEND_INVCONSTANTCOLOR);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_BLENDOP, D3DBLENDOP_MIN);
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_BLENDCOLOR, pixel_color);
			rgb_inputs= 0x01201120;
			alpha_inputs= 0;
			break;
		case _screen_flash_type_tint:
			IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_SRCBLEND, D3DBLEND_INVDESTCOLOR);
			SetRenderStateSmart(D3DRS_DESTBLEND, D3DBLEND_INVCONSTANTCOLOR);
			SetRenderStateSmart(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			SetRenderStateSmart(D3DRS_BLENDCOLOR, pixel_color);
			rgb_inputs= 0x01411120;
			alpha_inputs= 0;
			break;
		case _screen_flash_type_invert:
			SetRenderStateSmart(D3DRS_SRCBLEND, D3DBLEND_ONE);
			SetRenderStateSmart(D3DRS_DESTBLEND, D3DBLEND_INVCONSTANTCOLOR);
			SetRenderStateSmart(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pixel_color= inverse_pixel_color;
			SetRenderStateSmart(D3DRS_BLENDCOLOR, pixel_color);
			rgb_inputs= 0x11200000;
			alpha_inputs= 0;
			break;
		default:
			match_vassert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_screen_effect.c", 875, FALSE, "### ERROR unsupported screen flash type");
		}

		SetRenderStateSmart(D3DRS_ALPHATESTENABLE, FALSE);
		SetRenderStateSmart(D3DRS_ZENABLE, FALSE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZBIAS, 0);
		rasterizer_set_vertex_shader_permutation(4, 8, 0);

		{
			short width= global_window_parameters.camera.viewport_bounds.x1-global_window_parameters.camera.viewport_bounds.x0;
			short height= global_window_parameters.camera.viewport_bounds.y1-global_window_parameters.camera.viewport_bounds.y0;
			real one_over_width= 1.0f/width;
			real one_over_height;

			vertex_constants[0][0]= one_over_width+one_over_width;
			vertex_constants[0][1]= 0.0f;
			vertex_constants[0][2]= 0.0f;
			vertex_constants[0][3]= -1.0f-one_over_width;
			one_over_height= 1.0f/height;
			vertex_constants[1][0]= 0.0f;
			vertex_constants[1][1]= -2.0f*one_over_height;
			vertex_constants[1][2]= 0.0f;
			vertex_constants[1][3]= one_over_height+1.0f;
			vertex_constants[2][0]= 0.0f;
			vertex_constants[2][1]= 0.0f;
			vertex_constants[2][2]= 0.0f;
			vertex_constants[2][3]= 0.5f;
			vertex_constants[3][0]= 0.0f;
			vertex_constants[3][1]= 0.0f;
			vertex_constants[3][2]= 0.0f;
			vertex_constants[3][3]= 1.0f;
			vertex_constants[4][0]= 0.0f;
			vertex_constants[4][1]= 0.0f;
			vertex_constants[4][2]= 0.0f;
			vertex_constants[4][3]= 1.0f;
			IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, -68, vertex_constants, 5);
		}

		csmemset(&pixel_shader, 0, sizeof(pixel_shader));
		pixel_shader.PSCombinerCount= 1;
		pixel_shader.PSConstant0[0]= pixel_color;
		pixel_shader.PSAlphaInputs[0]= alpha_inputs;
		pixel_shader.PSAlphaOutputs[0]= 0xc00;
		pixel_shader.PSRGBInputs[0]= rgb_inputs;
		pixel_shader.PSRGBOutputs[0]= 0xc00;
		pixel_shader.PSFinalCombinerInputsABCD= 0xc;
		pixel_shader.PSFinalCombinerInputsEFG= 0x1c00;
		rasterizer_set_pixel_shader(&pixel_shader);

		{
			short width= global_window_parameters.camera.viewport_bounds.x1-global_window_parameters.camera.viewport_bounds.x0;
			short height= global_window_parameters.camera.viewport_bounds.y1-global_window_parameters.camera.viewport_bounds.y0;

			IDirect3DDevice8_Begin(global_d3d_device, D3DPT_TRIANGLEFAN);
			IDirect3DDevice8_SetVertexData2s(global_d3d_device, VSDE_VERTEX, 0, 0);
			IDirect3DDevice8_SetVertexData2s(global_d3d_device, VSDE_VERTEX, width, 0);
			IDirect3DDevice8_SetVertexData2s(global_d3d_device, VSDE_VERTEX, width, height);
			IDirect3DDevice8_SetVertexData2s(global_d3d_device, VSDE_VERTEX, 0, height);
			IDirect3DDevice8_End(global_d3d_device);
		}
	}

	rasterizer_profile_end(_rasterizer_profile_screen_flash);

	return;
}
