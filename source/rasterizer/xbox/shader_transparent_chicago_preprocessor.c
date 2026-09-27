/*
SHADER_TRANSPARENT_CHICAGO_PREPROCESSOR.C

symbols in this file:
0016B4E0 0010:
	_code_0016b4e0 (0000)
0016B4F0 01b0:
	_shader_transparent_chicago_create (0000)
0029CE08 0068:
	_rdata_0029ce08 (0000)
0029CE70 0034:
	_rdata_0029ce70 (0000)
0029CEA4 0034:
	_rdata_0029cea4 (0000)
0029CED8 0025:
	??_C@_0CF@ILPKPMME@?$CD?$CD?$CD?5ERROR?5chicago?5shader?5has?5no?5@ (0000)
0029CF00 0049:
	??_C@_0EJ@GDMOILEK@c?3?2halo?2SOURCE?2rasterizer?2xbox?2s@ (0000)
*/

/* ---------- headers */

#include "cseries.h"
#include "cseries_windows.h"
#include "errors.h"
#include "real_math.h"
#include "tag_groups.h"
#include "shaders/shader_definitions.h"

/* ---------- constants */

enum
{
	NUMBER_OF_SHADER_TRANSPARENT_CHICAGO_MAP_FUNCTIONS= 13,
};

enum
{
	_shader_transparent_chicago_map_unfiltered_bit= 0,
	_shader_transparent_chicago_map_alpha_replicate_bit,
	NUMBER_OF_SHADER_TRANSPARENT_CHICAGO_MAP_FLAGS
};

/* ---------- macros */

/* ---------- structures */

/* ---------- prototypes */

void *shader_get_and_verify_type(struct shader const *shader, short type);

/* ---------- globals */

static const unsigned long rdata_0029ce08[2][NUMBER_OF_SHADER_TRANSPARENT_CHICAGO_MAP_FUNCTIONS]=
{
	{
		0x0c200000, 0x08200000, 0x080c0000, 0x080c080c,
		0x08200c20, 0x08204c20, 0x0c204820, 0x08200c40,
		0x0c200840, 0x081c0c3c, 0x0c1c083c, 0x08180c38,
		0x0c180838
	},
	{
		0x0c200000, 0x18200000, 0x180c0000, 0x180c180c,
		0x18200c20, 0x18204c20, 0x0c205820, 0x18200c40,
		0x0c201840, 0x181c0c3c, 0x0c1c183c, 0x18180c38,
		0x0c181838
	}
};

static const unsigned long rdata_0029ce70[NUMBER_OF_SHADER_TRANSPARENT_CHICAGO_MAP_FUNCTIONS]=
{
	0x1c200000, 0x18200000, 0x181c0000, 0x181c181c,
	0x18201c20, 0x18205c20, 0x1c205820, 0x18201c40,
	0x1c201840, 0x181c1c3c, 0x1c1c183c, 0x18181c38,
	0x1c181838
};

static const unsigned long rdata_0029cea4[NUMBER_OF_SHADER_TRANSPARENT_CHICAGO_MAP_FUNCTIONS]=
{
	0x00000000, 0x01000000, 0x01000000, 0x01000100,
	0x01000000, 0x01000000, 0x00000100, 0x01000000,
	0x00000100, 0x01000000, 0x00000100, 0x01010001,
	0x00010101
};

/* ---------- public code */

boolean code_0016b4e0(
	void)
{
	return TRUE;
}

// TODO: loop increment uses eax instead of ecx and the original keeps al=TRUE across the loop exit (skips reloading success)
boolean shader_transparent_chicago_create(
	struct shader const *shader,
	D3DPIXELSHADERDEF *pixel_shader)
{
	struct shader_transparent_chicago const *chicago;
	boolean success= TRUE;
	short map_index;
	struct shader_transparent_chicago_map const *map;

	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\shader_transparent_chicago_preprocessor.c", 100, shader);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\shader_transparent_chicago_preprocessor.c", 101, pixel_shader);

	chicago= shader_get_and_verify_type(shader, _shader_type_transparent_chicago);
	csmemset(pixel_shader, 0, sizeof(D3DPIXELSHADERDEF));

	pixel_shader->PSCombinerCount= (chicago->chicago.maps.count+1) | 0x11000;

	if (chicago->chicago.maps.count>0)
	{
		pixel_shader->PSTextureModes= PS_TEXTUREMODES(
			chicago->chicago.type ? PS_TEXTUREMODES_CUBEMAP : PS_TEXTUREMODES_PROJECT2D,
			chicago->chicago.maps.count>1 ? PS_TEXTUREMODES_PROJECT2D : PS_TEXTUREMODES_NONE,
			chicago->chicago.maps.count>2 ? PS_TEXTUREMODES_PROJECT2D : PS_TEXTUREMODES_NONE,
			chicago->chicago.maps.count>3 ? PS_TEXTUREMODES_PROJECT2D : PS_TEXTUREMODES_NONE);

		for (map_index= 0; map_index<chicago->chicago.maps.count; map_index++)
		{
			map= TAG_BLOCK_GET_ELEMENT(&chicago->chicago.maps, map_index, struct shader_transparent_chicago_map);

			if (map_index!=chicago->chicago.maps.count-1)
			{
				pixel_shader->PSAlphaInputs[map_index+1]= rdata_0029cea4[map->alpha_function]*(map_index+1) + rdata_0029ce70[map->alpha_function];
				pixel_shader->PSRGBInputs[map_index+1]= rdata_0029cea4[map->color_function]*(map_index+1) +
					rdata_0029ce08[TEST_FLAG(map->flags, _shader_transparent_chicago_map_alpha_replicate_bit)][map->color_function];
			}
			else
			{
				pixel_shader->PSAlphaInputs[0]= 0x18200000;
				pixel_shader->PSRGBInputs[0]= 0x08200000;
			}
			pixel_shader->PSAlphaOutputs[map_index]= 0xc00;
			pixel_shader->PSRGBOutputs[map_index]= 0xc00;
		}
	}
	else
	{
		error(_error_silent, "### ERROR chicago shader has no maps");
		success= FALSE;
	}

	pixel_shader->PSFinalCombinerInputsABCD= 0xc;
	pixel_shader->PSFinalCombinerInputsEFG= 0x1c00;

	return success;
}

/* ---------- private code */
