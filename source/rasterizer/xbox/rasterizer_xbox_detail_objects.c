/*
RASTERIZER_XBOX_DETAIL_OBJECTS.C

symbols in this file:
0014B7E0 01b0:
	_D3DDevice_SetRenderState (0000)
0014B990 0050:
	_D3DDevice_SetTextureStageState (0000)
0014B9E0 0020:
	_IDirect3DDevice8_CreateVertexBuffer@24 (0000)
0014BA00 0120:
	_detail_object_build_vertices (0000)
0014BB20 0070:
	_rasterizer_detail_objects_initialize (0000)
0014BB90 0220:
	_IDirect3DDevice8_SetRenderState@12 (0000)
0014BDB0 0060:
	_IDirect3DDevice8_SetTextureStageState@16 (0000)
0014BE10 0010:
	_IDirect3DDevice8_DrawVertices@16 (0000)
0014BE20 0010:
	_IDirect3DDevice8_SetVertexShaderConstant@16 (0000)
0014BE30 0010:
	_IDirect3DDevice8_SetStreamSource@16 (0000)
0014BE40 0010:
	__rasterizer_detail_objects_end (0000)
0014BE50 0030:
	_IDirect3DDevice8_SetVertexData4f@24 (0000)
0014BE80 0010:
	_D3DVertexBuffer_Unlock@4 (0000)
0014BE90 0010:
	_IDirect3DVertexBuffer8_Release@4 (0000)
0014BEA0 0020:
	_IDirect3DVertexBuffer8_Lock@20 (0000)
0014BEC0 0010:
	_IDirect3DVertexBuffer8_Unlock@4 (0000)
0014BED0 0070:
	_rasterizer_detail_objects_dispose (0000)
0014BF40 0290:
	__rasterizer_detail_objects_begin (0000)
0014C1D0 0230:
	__rasterizer_detail_objects_rebuild_vertices (0000)
0014C400 0470:
	__rasterizer_detail_objects_draw (0000)
0028E028 0036:
	??_C@_0DG@OJLPBMH@?$CD?$CD?$CD?5ERROR?5rasterizer_detail_obje@ (0000)
0028E060 010b:
	??_C@_0BAL@NENAACKL@IDirect3DDevice8_CreateVertexBuf@ (0000)
0028E170 0040:
	??_C@_0EA@LGHKKBIM@c?3?2halo?2SOURCE?2rasterizer?2xbox?2r@ (0000)
0028E1B0 003f:
	??_C@_0DP@PFBAPIPD@?$CD?$CD?$CD?5ERROR?5too?5many?5detail?5object@ (0000)
0028E1F0 0018:
	??_C@_0BI@NKKNLOHO@detail_object_view_data?$AA@ (0000)
0028E208 0030:
	??_C@_0DA@LEHODDDN@?$CD?$CD?$CD?5ERROR?5rasterizer_detail_obje@ (0000)
0028E238 00a5:
	??_C@_0KF@HFCLJJLO@IDirect3DDevice8_DrawVertices?$CIgl@ (0000)
0028E2E0 00ab:
	??_C@_0KL@CKHIIGPN@IDirect3DDevice8_SetVertexData4f@ (0000)
0028E390 00c7:
	??_C@_0MH@KOGEPMP@IDirect3DDevice8_SetVertexData4f@ (0000)
0028E458 0019:
	??_C@_0BJ@ODGAOKJE@cell?9?$DOz_reference_vector?$AA@ (0000)
0028E478 0098:
	??_C@_0JI@PJJHOGAJ@IDirect3DDevice8_SetVertexShader@ (0000)
0028E510 00b8:
	??_C@_0LI@CELBHMPB@IDirect3DDevice8_SetVertexShader@ (0000)
0045E904 0004:
	_local_d3d_vertex_buffer (0000)
*/

/* ---------- headers */

#include "cseries.h"
#include "cseries_windows.h"
#include "errors.h"
#include "real_math.h"
#include "tag_groups.h"
#include "bitmaps.h"
#include "scenario/scenario.h"
#include "scenario/scenario_definitions.h"
#include "structures/structure_bsp_definitions.h"
#include "structures/detail_object_definitions.h"
#include "bitmaps/bitmap_group.h"
#include "rasterizer.h"
#include "xbox/rasterizer_xbox.h"

/* ---------- constants */

#define RASTERIZER_DYNAMIC_BUFFER_USAGE (D3DUSAGE_WRITEONLY|D3DUSAGE_DYNAMIC)
#define RASTERIZER_DYNAMIC_BUFFER_POOL D3DPOOL_DEFAULT

#define DETAIL_OBJECT_COLLECTION_DEFINITION_TAG 'dobc'

enum
{
	DETAIL_OBJECT_CELL_SIZE = 8,

	MAXIMUM_DETAIL_OBJECT_TYPES_PER_COLLECTION = 16,
	MAXIMUM_DETAIL_OBJECT_FRAMES_PER_COLLECTION = 128,

	VSH_CONSTANTS__DETAILOBJ_OFFSET = -81,
	VSH_CONSTANTS__DETAILOBJ_TYPEDATA_OFFSET = -75,
	VSH_CONSTANTS__DETAILOBJ_FRAMEDATA_OFFSET = -36,
};

/* ---------- structures */

/* ---------- prototypes */

short main_get_window_count(void);

point2d *rasterizer_set_texture(short stage, short type, short usage, long bitmap_group_index, short bitmap_index);
void rasterizer_set_vertex_shader_permutation(short vertex_shader, short vertex_type, short permutation);
void rasterizer_set_pixel_shader(D3DPIXELSHADERDEF *pixel_shader);

static void detail_object_build_vertices(struct detail_object_collection_definition const *collection_definition, struct detail_object const *detail_objects, struct detail_object_vertex *vertices, long detail_object_count);

/* ---------- globals */

extern D3DPIXELSHADERDEF pixel_shader;

static IDirect3DVertexBuffer8 *local_d3d_vertex_buffer;

/* ---------- private code */

static void detail_object_build_vertices(
	struct detail_object_collection_definition const *collection_definition,
	struct detail_object const *detail_objects,
	struct detail_object_vertex *vertices,
	long detail_object_count)
{
	long detail_object_index;

	for (detail_object_index= 0; detail_object_index<detail_object_count; detail_object_index++)
	{
		struct detail_object const *detail_object= &detail_objects[detail_object_index];
		struct detail_object_type_definition *type_definition;
		struct detail_object_vertex vertex;
		short type_index;
		long frame_index;
		unsigned short color;

		vertex.position[0]= detail_object->position[0];
		vertex.position[1]= detail_object->position[1];
		vertex.position[2]= detail_object->position[2];
		color= detail_object->color;
		vertex.color[0]= (unsigned char)((color>>8)&0xf8)|((color>>13)&0x7);
		vertex.color[1]= (unsigned char)((color>>3)&0xfc)|((color>>9)&0x3);
		vertex.color[2]= (unsigned char)(((unsigned char)color>>2)&0x7)|(color<<3);

		type_index= (short)((detail_object->data>>4)%collection_definition->type_definitions.count);
		type_definition= TAG_BLOCK_GET_ELEMENT(&collection_definition->type_definitions, type_index, struct detail_object_type_definition);
		frame_index= (detail_object->data&0xf)%type_definition->frame_count+type_definition->first_frame_index;

		vertex.data= (unsigned short)((frame_index<<8)|(type_index<<4));
		*vertices++= vertex;
		vertex.data++;
		*vertices++= vertex;
		vertex.data++;
		*vertices++= vertex;
		vertex.data++;
		*vertices++= vertex;
	}

	return;
}

/* ---------- public code */

boolean rasterizer_detail_objects_initialize(
	void)
{
	boolean success= TRUE;

	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_detail_objects.c", 98, global_d3d_device);

	D3DCALL(success, IDirect3DDevice8_CreateVertexBuffer(global_d3d_device, RASTERIZER_MAXIMUM_DETAIL_OBJECTS_PER_FRAME*NUMBER_OF_VERTICES_PER_QUADRILATERAL*sizeof(struct detail_object_vertex), RASTERIZER_DYNAMIC_BUFFER_USAGE, 0, RASTERIZER_DYNAMIC_BUFFER_POOL, &local_d3d_vertex_buffer));
	if (!success)
	{
		error(_error_silent, "### ERROR rasterizer_detail_objects_initialize failed");
	}

	return success;
}

void rasterizer_detail_objects_dispose(
	void)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_detail_objects.c", 119, local_d3d_vertex_buffer);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_detail_objects.c", 120, global_d3d_device);

	if (local_d3d_vertex_buffer)
	{
		IDirect3DVertexBuffer8_Release(local_d3d_vertex_buffer);
		local_d3d_vertex_buffer= NULL;
	}

	return;
}

void _rasterizer_detail_objects_begin(
	void)
{
	rasterizer_profile_begin(_rasterizer_profile_detail_objects);

	if (rasterizer_debug_options.draw_detail_objects && main_get_window_count()<=1)
	{
		real vsh_constants__detailobj[24];

		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_detail_objects.c", 136, local_d3d_vertex_buffer);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_detail_objects.c", 137, global_d3d_device);

		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_CULLMODE, D3DCULL_NONE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED|D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_BLUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHABLENDENABLE, TRUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_BLENDOP, D3DBLENDOP_ADD);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ALPHATESTENABLE, FALSE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZENABLE, D3DZB_TRUE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZWRITEENABLE, FALSE);
		IDirect3DDevice8_SetRenderState(global_d3d_device, D3DRS_ZBIAS, 0);

		vsh_constants__detailobj[0]= 1.f/256.f;
		vsh_constants__detailobj[1]= 16.f;
		vsh_constants__detailobj[2]= 541.f;
		vsh_constants__detailobj[3]= 659.f;
		vsh_constants__detailobj[4]= (real)DETAIL_OBJECT_CELL_SIZE;
		vsh_constants__detailobj[5]= (real)DETAIL_OBJECT_CELL_SIZE;
		vsh_constants__detailobj[6]= (real)DETAIL_OBJECT_CELL_SIZE;
		vsh_constants__detailobj[7]= rasterizer_debug_options.detail_object_screen_facing_offset_multiplier;
		vsh_constants__detailobj[8]= 1.f;
		vsh_constants__detailobj[9]= 1.f;
		vsh_constants__detailobj[10]= 0.5f;
		vsh_constants__detailobj[11]= 0.f;
		vsh_constants__detailobj[12]= 0.f;
		vsh_constants__detailobj[13]= 1.f;
		vsh_constants__detailobj[14]= -0.5f;
		vsh_constants__detailobj[15]= 0.f;
		vsh_constants__detailobj[16]= 0.f;
		vsh_constants__detailobj[17]= 0.f;
		vsh_constants__detailobj[18]= -0.5f;
		vsh_constants__detailobj[19]= 1.f;
		vsh_constants__detailobj[20]= 1.f;
		vsh_constants__detailobj[21]= 0.f;
		vsh_constants__detailobj[22]= 0.5f;
		vsh_constants__detailobj[23]= 1.f;
		IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, VSH_CONSTANTS__DETAILOBJ_OFFSET, vsh_constants__detailobj, 6);

		csmemset(&pixel_shader, 0, sizeof(pixel_shader));
		pixel_shader.PSTextureModes= 1;
		pixel_shader.PSCombinerCount= 1;
		pixel_shader.PSRGBInputs[0]= 0x08040000;
		pixel_shader.PSRGBOutputs[0]= 0xc0;
		pixel_shader.PSAlphaInputs[0]= 0x18140000;
		pixel_shader.PSAlphaOutputs[0]= 0xc0;
		pixel_shader.PSFinalCombinerInputsABCD= 0xc;
		pixel_shader.PSFinalCombinerInputsEFG= 0x1c00;
		rasterizer_set_pixel_shader(&pixel_shader);

		IDirect3DDevice8_SetStreamSource(global_d3d_device, 0, local_d3d_vertex_buffer, sizeof(struct detail_object_vertex));
	}

	return;
}

void _rasterizer_detail_objects_rebuild_vertices(
	struct detail_object_view_data const *detail_object_view_data)
{
	if (rasterizer_debug_options.draw_detail_objects && main_get_window_count()<=1)
	{
		struct scenario *scenario= global_scenario_get();
		struct detail_object_vertex *vertices= NULL;

		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_detail_objects.c", 215, detail_object_view_data);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_detail_objects.c", 216, local_d3d_vertex_buffer);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_detail_objects.c", 217, global_d3d_device);

		rasterizer_globals.current_lock_operation= _rasterizer_lock_detail_objects;
		IDirect3DVertexBuffer8_Lock(local_d3d_vertex_buffer, 0, RASTERIZER_MAXIMUM_DETAIL_OBJECTS_PER_FRAME*NUMBER_OF_VERTICES_PER_QUADRILATERAL*sizeof(struct detail_object_vertex), (BYTE **)&vertices, 0);
		rasterizer_globals.current_lock_operation= _rasterizer_lock_none;

		if (vertices)
		{
			struct structure_detail_object_data *detail_object_data= global_structure_bsp_get()->detail_object_data.count ?
				TAG_BLOCK_GET_ELEMENT(&global_structure_bsp_get()->detail_object_data, 0, struct structure_detail_object_data) :
				NULL;
			struct detail_object *detail_objects= TAG_BLOCK_GET_ELEMENT(&detail_object_data->detail_objects, 0, struct detail_object);
			long vertex_index= 0;
			long total_detail_object_count= 0;
			boolean too_many_detail_objects= FALSE;
			short layer_index;

			for (layer_index= 0; layer_index<detail_object_view_data->layer_count; layer_index++)
			{
				struct detail_object_layer_data *layer= &detail_object_view_data->layers[layer_index];
				struct scenario_detail_object_collection_palette_entry *palette_entry= TAG_BLOCK_GET_ELEMENT(&scenario->detail_object_collection_palette, layer->collection_definition_index, struct scenario_detail_object_collection_palette_entry);
				struct detail_object_collection_definition *collection_definition= tag_get(DETAIL_OBJECT_COLLECTION_DEFINITION_TAG, palette_entry->reference.index);
				short cell_index;

				for (cell_index= 0; cell_index<layer->cell_count; cell_index++)
				{
					struct detail_object_cell_data *cell= &layer->cells[cell_index];
					long detail_object_count= cell->detail_object_count;

					if (detail_object_count>RASTERIZER_MAXIMUM_DETAIL_OBJECTS_PER_FRAME-total_detail_object_count)
					{
						detail_object_count= RASTERIZER_MAXIMUM_DETAIL_OBJECTS_PER_FRAME-total_detail_object_count;
					}

					detail_object_build_vertices(collection_definition, &detail_objects[cell->first_detail_object_index], &vertices[vertex_index], detail_object_count);
					cell->internal__first_vertex_index= vertex_index;
					vertex_index+= cell->detail_object_count*NUMBER_OF_VERTICES_PER_QUADRILATERAL;

					if (cell->detail_object_count>detail_object_count)
					{
						cell->detail_object_count= detail_object_count;
						if (!too_many_detail_objects)
						{
							too_many_detail_objects= TRUE;
							error(_error_silent, "### ERROR too many detail object submitted for frame (max=#%d)", RASTERIZER_MAXIMUM_DETAIL_OBJECTS_PER_FRAME);
						}
					}

					total_detail_object_count+= detail_object_count;
				}
			}

			IDirect3DVertexBuffer8_Unlock(local_d3d_vertex_buffer);
		}
	}

	return;
}

void _rasterizer_detail_objects_draw(
	struct detail_object_view_data const *detail_object_view_data)
{
	boolean success= TRUE;

	if (rasterizer_debug_options.draw_detail_objects && main_get_window_count()<=1)
	{
		struct scenario *scenario= global_scenario_get();
		short layer_index;

		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_detail_objects.c", 306, detail_object_view_data);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_detail_objects.c", 307, global_d3d_device);

		for (layer_index= 0; layer_index<detail_object_view_data->layer_count; layer_index++)
		{
			struct detail_object_layer_data *layer= &detail_object_view_data->layers[layer_index];
			struct scenario_detail_object_collection_palette_entry *palette_entry= TAG_BLOCK_GET_ELEMENT(&scenario->detail_object_collection_palette, layer->collection_definition_index, struct scenario_detail_object_collection_palette_entry);
			struct detail_object_collection_definition *collection_definition= tag_get(DETAIL_OBJECT_COLLECTION_DEFINITION_TAG, palette_entry->reference.index);
			struct bitmap_group *bitmap= tag_get(BITMAP_GROUP_TAG, collection_definition->map.index);
			real_vector4d vsh_constants__detailobj_typedata[MAXIMUM_DETAIL_OBJECT_TYPES_PER_COLLECTION];
			real_vector4d vsh_constants__detailobj_framedata[MAXIMUM_DETAIL_OBJECT_FRAMES_PER_COLLECTION];
			short frame_count;
			short type_index;
			short sequence_index;
			short cell_index;

			rasterizer_set_texture(0, 0, 1, collection_definition->map.index, 0);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
			IDirect3DDevice8_SetTextureStageState(global_d3d_device, 0, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);

			if (collection_definition->collection_type!=NONE)
			{
				rasterizer_set_vertex_shader_permutation(33, 11, collection_definition->collection_type);
			}

			frame_count= 0;
			for (type_index= 0; type_index<collection_definition->type_definitions.count; type_index++)
			{
				struct detail_object_type_definition *type_definition= TAG_BLOCK_GET_ELEMENT(&collection_definition->type_definitions, type_index, struct detail_object_type_definition);
				struct bitmap_group_sequence *sequence= TAG_BLOCK_GET_ELEMENT(&bitmap->sequences, type_definition->sequence_index, struct bitmap_group_sequence);
				struct bitmap_data *bitmap_data= TAG_BLOCK_GET_ELEMENT(&bitmap->bitmaps, sequence->first_bitmap_index, struct bitmap_data);
				real fade_distance= type_definition->far_fade_distance-type_definition->near_fade_distance;
				real size= type_definition->size_min;
				real_vector4d *typedata;

				if (fade_distance>0.f)
				{
					fade_distance= 1.f/fade_distance;
				}

				typedata= &vsh_constants__detailobj_typedata[type_index];
				typedata->i= fade_distance*type_definition->far_fade_distance;
				typedata->j= -fade_distance;
				typedata->k= (real)bitmap_data->width*size;
				typedata->l= (real)bitmap_data->height*size;
			}

			for (sequence_index= 0; sequence_index<bitmap->sequences.count; sequence_index++)
			{
				struct bitmap_group_sequence *sequence= TAG_BLOCK_GET_ELEMENT(&bitmap->sequences, sequence_index, struct bitmap_group_sequence);
				short sprite_index;

				for (sprite_index= 0; sprite_index<sequence->sprites.count; sprite_index++)
				{
					struct bitmap_group_sprite *sprite= TAG_BLOCK_GET_ELEMENT(&sequence->sprites, sprite_index, struct bitmap_group_sprite);
					struct bitmap_data *bitmap_data= TAG_BLOCK_GET_ELEMENT(&bitmap->bitmaps, sprite->bitmap_index, struct bitmap_data);
					real_vector4d *framedata= &vsh_constants__detailobj_framedata[frame_count++];

					framedata->i= sprite->bounds.x0;
					framedata->j= sprite->bounds.y0;
					framedata->k= sprite->bounds.x1-sprite->bounds.x0;
					framedata->l= sprite->bounds.y1-sprite->bounds.y0;
				}
			}

			D3DCALL(success, IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, VSH_CONSTANTS__DETAILOBJ_TYPEDATA_OFFSET, vsh_constants__detailobj_typedata, collection_definition->type_definitions.count));
			D3DCALL(success, IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, VSH_CONSTANTS__DETAILOBJ_FRAMEDATA_OFFSET, vsh_constants__detailobj_framedata, frame_count));

			for (cell_index= 0; cell_index<layer->cell_count; cell_index++)
			{
				struct detail_object_cell_data *cell= &layer->cells[cell_index];

				match_assert("c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_detail_objects.c", 394, cell->z_reference_vector);

				D3DCALL(success, IDirect3DDevice8_SetVertexData4f(global_d3d_device, 2, (real)(cell->cell_x*DETAIL_OBJECT_CELL_SIZE), (real)(cell->cell_y*DETAIL_OBJECT_CELL_SIZE), (cell->cell_z*(real)DETAIL_OBJECT_CELL_SIZE), 1.0f));
				D3DCALL(success, IDirect3DDevice8_SetVertexData4f(global_d3d_device, 3, cell->z_reference_vector->i, cell->z_reference_vector->j, cell->z_reference_vector->k, cell->z_reference_vector->l));
				D3DCALL(success, IDirect3DDevice8_DrawVertices(global_d3d_device, D3DPT_QUADLIST, cell->internal__first_vertex_index, cell->detail_object_count*NUMBER_OF_VERTICES_PER_QUADRILATERAL));
			}
		}

		if (!success)
		{
			error(_error_silent, "### ERROR rasterizer_detail_objects_draw failed");
		}
	}

	return;
}

void _rasterizer_detail_objects_end(
	void)
{
	rasterizer_profile_end(_rasterizer_profile_detail_objects);

	return;
}
