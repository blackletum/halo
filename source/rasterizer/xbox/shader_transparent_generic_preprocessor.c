/*
SHADER_TRANSPARENT_GENERIC_PREPROCESSOR.C
*/

/* ---------- headers */

#include "cseries.h"
#include "cseries_windows.h"
#include "errors.h"
#include "real_math.h"
#include "tag_groups.h"
#include "rasterizer.h"
#include "xbox/rasterizer_xbox.h"
#include "shaders/shader_definitions.h"

/* ---------- constants */

#define SHADER_TRANSPARENT_GENERIC_PREPROCESSOR_FILE "c:\\halo\\SOURCE\\rasterizer\\xbox\\shader_transparent_generic_preprocessor.c"

enum
{
	NUMBER_OF_SHADER_TRANSPARENT_GENERIC_SPECIAL_STAGE_INPUTS= 5,
	NUMBER_OF_SHADER_TRANSPARENT_GENERIC_STAGE_INPUTS= 25,
	NUMBER_OF_SHADER_TRANSPARENT_GENERIC_STAGE_INPUT_MAPPINGS= 8,
	NUMBER_OF_SHADER_TRANSPARENT_GENERIC_STAGE_OUTPUTS= 9,
	NUMBER_OF_SHADER_TRANSPARENT_GENERIC_STAGE_OUTPUT_FUNCTIONS= 2,
	NUMBER_OF_SHADER_TRANSPARENT_GENERIC_STAGE_OUTPUT_MAPPINGS= 6
};

enum
{
	_shader_transparent_generic_stage_output_function_multiply= 0,
	_shader_transparent_generic_stage_output_function_dot_product
};

enum
{
	_shader_transparent_generic_stage_color_mux_bit= 0,
	_shader_transparent_generic_stage_alpha_mux_bit
};

enum
{
	_shader_transparent_generic_stage_output_fog= 3
};

/* ---------- structures */

/* ---------- prototypes */

void *shader_get_and_verify_type(struct shader const *shader, short type);
unsigned long real_argb_color_to_pixel32(real_argb_color const *color);

static long shader_transparent_generic_color_input(short register_index, short mapping_index);
static long shader_transparent_generic_color_output(short register_index);
static long shader_transparent_generic_color_output_flags(struct shader_transparent_generic_stage const *stage);
static long shader_transparent_generic_alpha_input(short register_index, short mapping_index);
static long shader_transparent_generic_alpha_output(short register_index);
static long shader_transparent_generic_alpha_output_flags(struct shader_transparent_generic_stage const *stage);
static boolean shader_transparent_generic_map_verify(struct shader_transparent_generic_map const *map, short map_index);
static boolean shader_transparent_generic_stage_verify(struct shader_transparent_generic_stage const *stage, short stage_index);

/* ---------- globals */

static const long shader_transparent_generic_color_input_registers[NUMBER_OF_SHADER_TRANSPARENT_GENERIC_STAGE_INPUTS+1]=
{
	NONE, NONE, NONE, NONE, NONE,
	0x08, 0x09, 0x0a, 0x0b,
	0x04, 0x05,
	0x0c, 0x0d,
	0x01, 0x02,
	0x18, 0x19, 0x1a, 0x1b,
	0x14, 0x15,
	0x1c, 0x1d,
	0x11, 0x12
};

static const long shader_transparent_generic_alpha_input_registers[NUMBER_OF_SHADER_TRANSPARENT_GENERIC_STAGE_INPUTS]=
{
	NONE, NONE, NONE, NONE, NONE,
	0x18, 0x19, 0x1a, 0x1b,
	0x14, 0x15,
	0x1c, 0x1d,
	0x11, 0x12,
	0x08, 0x09, 0x0a, 0x0b,
	0x04, 0x05,
	0x0c, 0x0d,
	0x01, 0x02
};

static const long shader_transparent_generic_color_input_mappings[NUMBER_OF_SHADER_TRANSPARENT_GENERIC_STAGE_INPUT_MAPPINGS]=
{
	0x00, 0x20, 0x40, 0x60, 0x80, 0xa0, 0xc0, 0xe0
};

static const long shader_transparent_generic_alpha_input_mappings[NUMBER_OF_SHADER_TRANSPARENT_GENERIC_STAGE_INPUT_MAPPINGS+1]=
{
	0x00, 0x20, 0x40, 0x60, 0x80, 0xa0, 0xc0, 0xe0
};

static const long shader_transparent_generic_special_inputs[NUMBER_OF_SHADER_TRANSPARENT_GENERIC_SPECIAL_STAGE_INPUTS][NUMBER_OF_SHADER_TRANSPARENT_GENERIC_STAGE_INPUT_MAPPINGS]=
{
	{0x00, 0x20, 0x40, 0x20, 0x80, 0xa0, 0x00, 0x00},
	{0x20, 0x00, 0x20, 0x40, 0xa0, 0x80, 0x20, 0x40},
	{0xa0, 0xa0, 0x00, 0x00, 0x00, 0x00, 0xa0, 0x80},
	{0x00, 0x20, 0x40, 0x20, 0x80, 0xa0, 0x40, 0x20},
	{0x00, 0x20, 0x40, 0x20, 0x80, 0xa0, 0x80, 0xa0}
};

static const long shader_transparent_generic_color_output_registers[NUMBER_OF_SHADER_TRANSPARENT_GENERIC_STAGE_OUTPUTS]=
{
	0x00, 0x0c, 0x0d, 0x04, 0x05, 0x08, 0x09, 0x0a, 0x0b
};

static const long shader_transparent_generic_alpha_output_registers[NUMBER_OF_SHADER_TRANSPARENT_GENERIC_STAGE_OUTPUTS]=
{
	0x00, 0x1c, 0x1d, 0x14, 0x15, 0x18, 0x19, 0x1a, 0x1b
};

static const long shader_transparent_generic_color_output_mappings[NUMBER_OF_SHADER_TRANSPARENT_GENERIC_STAGE_OUTPUT_MAPPINGS]=
{
	0x00, 0x30, 0x10, 0x20, 0x08, 0x18
};

static const long shader_transparent_generic_alpha_output_mappings[NUMBER_OF_SHADER_TRANSPARENT_GENERIC_STAGE_OUTPUT_MAPPINGS]=
{
	0x00, 0x30, 0x10, 0x20, 0x08, 0x18
};

/* ---------- public code */

static long shader_transparent_generic_color_input(
	short register_index,
	short mapping_index)
{
	long result;

	match_assert(SHADER_TRANSPARENT_GENERIC_PREPROCESSOR_FILE, 212, register_index>=0 && register_index<NUMBER_OF_SHADER_TRANSPARENT_GENERIC_STAGE_INPUTS);
	match_assert(SHADER_TRANSPARENT_GENERIC_PREPROCESSOR_FILE, 213, mapping_index>=0 && mapping_index<NUMBER_OF_SHADER_TRANSPARENT_GENERIC_STAGE_INPUT_MAPPINGS);

	if (shader_transparent_generic_color_input_registers[register_index]==NONE)
	{
		result= shader_transparent_generic_special_inputs[register_index][mapping_index];
	}
	else
	{
		result= shader_transparent_generic_color_input_registers[register_index] | shader_transparent_generic_color_input_mappings[mapping_index];
	}

	return result;
}

static long shader_transparent_generic_color_output(
	short register_index)
{
	match_assert(SHADER_TRANSPARENT_GENERIC_PREPROCESSOR_FILE, 233, register_index>=0 && register_index<NUMBER_OF_SHADER_TRANSPARENT_GENERIC_STAGE_OUTPUTS);

	return shader_transparent_generic_color_output_registers[register_index];
}

static long shader_transparent_generic_color_output_flags(
	struct shader_transparent_generic_stage const *stage)
{
	long result;

	match_assert(SHADER_TRANSPARENT_GENERIC_PREPROCESSOR_FILE, 246, stage);
	match_assert(SHADER_TRANSPARENT_GENERIC_PREPROCESSOR_FILE, 247, stage->color_output_mapping>=0 && stage->color_output_mapping<NUMBER_OF_SHADER_TRANSPARENT_GENERIC_STAGE_OUTPUT_MAPPINGS);
	match_assert(SHADER_TRANSPARENT_GENERIC_PREPROCESSOR_FILE, 248, stage->color_output_AB_function>=0 && stage->color_output_AB_function<NUMBER_OF_SHADER_TRANSPARENT_GENERIC_STAGE_OUTPUT_FUNCTIONS);
	match_assert(SHADER_TRANSPARENT_GENERIC_PREPROCESSOR_FILE, 249, stage->color_output_CD_function>=0 && stage->color_output_CD_function<NUMBER_OF_SHADER_TRANSPARENT_GENERIC_STAGE_OUTPUT_FUNCTIONS);

	result= shader_transparent_generic_color_output_mappings[stage->color_output_mapping];
	if (stage->color_output_AB_function==_shader_transparent_generic_stage_output_function_dot_product)
	{
		result|= PS_COMBINEROUTPUT_AB_DOT_PRODUCT;
	}
	if (stage->color_output_CD_function==_shader_transparent_generic_stage_output_function_dot_product)
	{
		result|= PS_COMBINEROUTPUT_CD_DOT_PRODUCT;
	}
	if (TEST_FLAG(stage->flags, _shader_transparent_generic_stage_color_mux_bit))
	{
		result|= PS_COMBINEROUTPUT_AB_CD_MUX;
	}

	return result;
}

static long shader_transparent_generic_alpha_input(
	short register_index,
	short mapping_index)
{
	long result;

	match_assert(SHADER_TRANSPARENT_GENERIC_PREPROCESSOR_FILE, 266, register_index>=0 && register_index<NUMBER_OF_SHADER_TRANSPARENT_GENERIC_STAGE_INPUTS);
	match_assert(SHADER_TRANSPARENT_GENERIC_PREPROCESSOR_FILE, 267, mapping_index>=0 && mapping_index<NUMBER_OF_SHADER_TRANSPARENT_GENERIC_STAGE_INPUT_MAPPINGS);

	if (shader_transparent_generic_alpha_input_registers[register_index]==NONE)
	{
		result= shader_transparent_generic_special_inputs[register_index][mapping_index];
	}
	else
	{
		result= shader_transparent_generic_alpha_input_registers[register_index] | shader_transparent_generic_alpha_input_mappings[mapping_index];
	}

	return result;
}

static long shader_transparent_generic_alpha_output(
	short register_index)
{
	match_assert(SHADER_TRANSPARENT_GENERIC_PREPROCESSOR_FILE, 287, register_index>=0 && register_index<NUMBER_OF_SHADER_TRANSPARENT_GENERIC_STAGE_OUTPUTS);

	return shader_transparent_generic_alpha_output_registers[register_index];
}

static long shader_transparent_generic_alpha_output_flags(
	struct shader_transparent_generic_stage const *stage)
{
	long result;

	match_assert(SHADER_TRANSPARENT_GENERIC_PREPROCESSOR_FILE, 300, stage);
	match_assert(SHADER_TRANSPARENT_GENERIC_PREPROCESSOR_FILE, 301, stage->alpha_output_mapping>=0 && stage->alpha_output_mapping<NUMBER_OF_SHADER_TRANSPARENT_GENERIC_STAGE_OUTPUT_MAPPINGS);

	result= shader_transparent_generic_alpha_output_mappings[stage->alpha_output_mapping];
	if (TEST_FLAG(stage->flags, _shader_transparent_generic_stage_alpha_mux_bit))
	{
		result|= PS_COMBINEROUTPUT_AB_CD_MUX;
	}

	return result;
}

static boolean shader_transparent_generic_map_verify(
	struct shader_transparent_generic_map const *map,
	short map_index)
{
	boolean success= TRUE;

	match_assert(SHADER_TRANSPARENT_GENERIC_PREPROCESSOR_FILE, 316, map);

	if (map->map.index==NONE)
	{
		error(_error_silent, "### ERROR transparent shader map #%d has no associated bitmap", map_index);
		success= FALSE;
	}
	if (map->mipmap_bias!=0.f)
	{
		error(_error_silent, "### ERROR unsupported: transparent shader map #%d has non-zero mipmap bias", map_index);
		success= FALSE;
	}

	return success;
}

static boolean shader_transparent_generic_stage_verify(
	struct shader_transparent_generic_stage const *stage,
	short stage_index)
{
	boolean success= TRUE;

	match_assert(SHADER_TRANSPARENT_GENERIC_PREPROCESSOR_FILE, 340, stage);

	if ((stage->color_output_AB && stage->color_output_CD && stage->color_output_AB==stage->color_output_CD) ||
		(stage->color_output_AB && stage->color_output_AB_CD_mux_sum && stage->color_output_AB==stage->color_output_AB_CD_mux_sum) ||
		(stage->color_output_CD && stage->color_output_AB_CD_mux_sum && stage->color_output_CD==stage->color_output_AB_CD_mux_sum) ||
		(stage->alpha_output_AB && stage->alpha_output_CD && stage->alpha_output_AB==stage->alpha_output_CD) ||
		(stage->alpha_output_AB && stage->alpha_output_AB_CD_mux_sum && stage->alpha_output_AB==stage->alpha_output_AB_CD_mux_sum) ||
		(stage->alpha_output_CD && stage->alpha_output_AB_CD_mux_sum && stage->alpha_output_CD==stage->alpha_output_AB_CD_mux_sum))
	{
		error(_error_silent, "### ERROR transparent shader output conflict in stage #%d", stage_index);
		success= FALSE;
	}
	if ((stage->color_output_AB_function || stage->color_output_CD_function) && stage->color_output_AB_CD_mux_sum)
	{
		error(_error_silent, "### ERROR transparent shader evaluates dot product and AB+CD sum in stage #%d", stage_index);
		success= FALSE;
	}
	if (stage->alpha_output_AB==_shader_transparent_generic_stage_output_fog || stage->alpha_output_AB_CD_mux_sum==_shader_transparent_generic_stage_output_fog)
	{
		error(_error_silent, "### ERROR transparent shader writes to fog density register in stage #%d", stage_index);
		success= FALSE;
	}
	if (TEST_FLAG(stage->flags, _shader_transparent_generic_stage_color_mux_bit) && (stage->color_output_AB_function || stage->color_output_CD_function))
	{
		error(_error_silent, "### ERROR transparent shader evaluates dot product and mux[AB,CD] in stage #%d", stage_index);
		success= FALSE;
	}

	return success;
}

boolean shader_transparent_generic_create(
	struct shader *shader,
	D3DPIXELSHADERDEF *pixel_shader)
{
	boolean success= TRUE;
	struct shader_transparent_generic *generic;

	match_assert(SHADER_TRANSPARENT_GENERIC_PREPROCESSOR_FILE, 388, shader);
	match_assert(SHADER_TRANSPARENT_GENERIC_PREPROCESSOR_FILE, 389, pixel_shader);

	generic= shader_get_and_verify_type(shader, _shader_type_transparent_generic);
	csmemset(pixel_shader, 0, sizeof(D3DPIXELSHADERDEF));

	if (generic->generic.maps.count<=0 && generic->generic.stages.count<=0)
	{
		error(_error_silent, "### ERROR generic shader has no maps or stages");
		success= FALSE;
	}
	else
	{
		short map_index;

		pixel_shader->PSTextureModes= PS_TEXTUREMODES(
			generic->generic.maps.count>0 ? (generic->generic.type!=0 ? PS_TEXTUREMODES_CUBEMAP : PS_TEXTUREMODES_PROJECT2D) : PS_TEXTUREMODES_NONE,
			generic->generic.maps.count>1,
			generic->generic.maps.count>2,
			generic->generic.maps.count>3);

		for (map_index= 0; map_index<generic->generic.maps.count; map_index++)
		{
			struct shader_transparent_generic_map *map= TAG_BLOCK_GET_ELEMENT(&generic->generic.maps, map_index, struct shader_transparent_generic_map);

			if (success)
			{
				success= shader_transparent_generic_map_verify(map, map_index);
			}
		}
	}

	pixel_shader->PSCombinerCount= PS_COMBINERCOUNT(MAX(1, generic->generic.stages.count)+1, PS_COMBINERCOUNT_MUX_MSB|PS_COMBINERCOUNT_UNIQUE_C0|PS_COMBINERCOUNT_UNIQUE_C1);

	if (generic->generic.stages.count>0)
	{
		short stage_index;

		for (stage_index= 0; stage_index<generic->generic.stages.count; stage_index++)
		{
			struct shader_transparent_generic_stage *stage= TAG_BLOCK_GET_ELEMENT(&generic->generic.stages, stage_index, struct shader_transparent_generic_stage);

			if (success)
			{
				success= shader_transparent_generic_stage_verify(stage, stage_index);
			}

			pixel_shader->PSConstant1[stage_index]= real_argb_color_to_pixel32(&stage->color1);

			// color combiner
			{
				long input_a, input_b, input_c, input_d;
				long output_ab, output_cd, output_mux_sum, output_flags;

				input_a= shader_transparent_generic_color_input(stage->color_input_A, stage->color_input_A_mapping);
				input_b= shader_transparent_generic_color_input(stage->color_input_B, stage->color_input_B_mapping);
				input_c= shader_transparent_generic_color_input(stage->color_input_C, stage->color_input_C_mapping);
				input_d= shader_transparent_generic_color_input(stage->color_input_D, stage->color_input_D_mapping);
				output_ab= shader_transparent_generic_color_output(stage->color_output_AB);
				output_cd= shader_transparent_generic_color_output(stage->color_output_CD);
				output_mux_sum= shader_transparent_generic_color_output(stage->color_output_AB_CD_mux_sum);
				output_flags= shader_transparent_generic_color_output_flags(stage);
				pixel_shader->PSRGBInputs[stage_index]= PS_COMBINERINPUTS(input_a, input_b, input_c, input_d);
				pixel_shader->PSRGBOutputs[stage_index]= PS_COMBINEROUTPUTS(output_ab&0xf, output_cd&0xf, output_mux_sum&0xf, output_flags);
			}
			// alpha combiner
			{
				long input_a, input_b, input_c, input_d;
				long output_ab, output_cd, output_mux_sum, output_flags;

				input_a= shader_transparent_generic_alpha_input(stage->alpha_input_A, stage->alpha_input_A_mapping);
				input_b= shader_transparent_generic_alpha_input(stage->alpha_input_B, stage->alpha_input_B_mapping);
				input_c= shader_transparent_generic_alpha_input(stage->alpha_input_C, stage->alpha_input_C_mapping);
				input_d= shader_transparent_generic_alpha_input(stage->alpha_input_D, stage->alpha_input_D_mapping);
				output_ab= shader_transparent_generic_alpha_output(stage->alpha_output_AB);
				output_cd= shader_transparent_generic_alpha_output(stage->alpha_output_CD);
				output_mux_sum= shader_transparent_generic_alpha_output(stage->alpha_output_AB_CD_mux_sum);
				output_flags= shader_transparent_generic_alpha_output_flags(stage);
				pixel_shader->PSAlphaInputs[stage_index]= PS_COMBINERINPUTS(input_a, input_b, input_c, input_d);
				pixel_shader->PSAlphaOutputs[stage_index]= PS_COMBINEROUTPUTS(output_ab&0xf, output_cd&0xf, output_mux_sum&0xf, output_flags);
			}
		}
	}
	else
	{
		pixel_shader->PSRGBInputs[0]= PS_COMBINERINPUTS(PS_REGISTER_T0, PS_REGISTER_ONE, 0, 0);
		pixel_shader->PSRGBOutputs[0]= PS_COMBINEROUTPUTS(PS_REGISTER_R0, 0, 0, 0);
		pixel_shader->PSAlphaInputs[0]= PS_COMBINERINPUTS(PS_REGISTER_T0|PS_CHANNEL_ALPHA, PS_REGISTER_ONE, 0, 0);
		pixel_shader->PSAlphaOutputs[0]= PS_COMBINEROUTPUTS(PS_REGISTER_R0, 0, 0, 0);
	}

	pixel_shader->PSFinalCombinerInputsABCD= PS_COMBINERINPUTS(0, 0, 0, PS_REGISTER_R0);
	pixel_shader->PSFinalCombinerInputsEFG= PS_COMBINERINPUTS(0, 0, PS_REGISTER_R0|PS_CHANNEL_ALPHA, 0);

	return success;
}

/* ---------- private code */
