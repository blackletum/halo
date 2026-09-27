/*
RASTERIZER_GEOMETRY.H

header included in hcex build.
*/

#ifndef __RASTERIZER_GEOMETRY_H
#define __RASTERIZER_GEOMETRY_H
#pragma once

/* ---------- headers */

#include "math/integer_math.h"
#include "math/real_math.h"

/* ---------- constants */

enum
{
	_rasterizer_vertex_type_environment_uncompressed = 0,
	_rasterizer_vertex_type_environment_compressed,
	_rasterizer_vertex_type_environment_lightmap_uncompressed,
	_rasterizer_vertex_type_environment_lightmap_compressed,
	_rasterizer_vertex_type_model_uncompressed,
	_rasterizer_vertex_type_model_compressed,
	_rasterizer_vertex_type_dynamic_unlit,
	_rasterizer_vertex_type_dynamic_lit,
	_rasterizer_vertex_type_dynamic_screen,
	_rasterizer_vertex_type_debug,
	_rasterizer_vertex_type_decal,
	_rasterizer_vertex_type_detail_object,
	_rasterizer_vertex_type_environment_uncompressed_ff,
	_rasterizer_vertex_type_environment_lightmap_uncompressed_ff,
	_rasterizer_vertex_type_model_uncompressed_ff,
	_rasterizer_vertex_type_model_processed,
	_rasterizer_vertex_type_unlit_zsprite,
	_rasterizer_vertex_type_widget,
	NUMBER_OF_RASTERIZER_VERTEX_TYPES,

	// the xbox build only has the first twelve vertex types
	NUMBER_OF_XBOX_RASTERIZER_VERTEX_TYPES = _rasterizer_vertex_type_environment_uncompressed_ff
};

enum
{
	_triangle_buffer_type_triangles = 0,
	_triangle_buffer_type_precompiled_strip,
	NUMBER_OF_TRIANGLE_BUFFER_TYPES
};

/* ---------- macros */

/* ---------- structures */

struct rasterizer_triangle
{
	word vertex_indices[NUMBER_OF_VERTICES_PER_TRIANGLE];
};

struct triangle_buffer
{
	short type; // 0x0
	word pad; // 0x2
	long count; // 0x4
	long offset; // 0x8
	void *hardware_format; // 0xC IDirect3DIndexBuffer8 *
};

struct vertex_buffer
{
	short type; // 0x0
	word pad; // 0x2
	long count; // 0x4
	long offset; // 0x8
	void *base_address; // 0xC
	void *hardware_format; // 0x10 IDirect3DVertexBuffer8 *
};

// _rasterizer_vertex_type_environment_uncompressed
struct environment_vertex_uncompressed
{
	real_point3d position; // 0x0
	real_vector3d normal; // 0xC
	real_vector3d binormal; // 0x18
	real_vector3d tangent; // 0x24
	real_point2d texcoord; // 0x30
};

// _rasterizer_vertex_type_environment_compressed
struct environment_vertex_compressed
{
	real_point3d position; // 0x0
	unsigned long normal; // 0xC
	unsigned long binormal; // 0x10
	unsigned long tangent; // 0x14
	real_point2d texcoord; // 0x18
};

// _rasterizer_vertex_type_environment_lightmap_uncompressed
struct environment_lightmap_vertex_uncompressed
{
	real_vector3d incident_radiosity; // 0x0
	real_point2d texcoord; // 0xC
};

// _rasterizer_vertex_type_environment_lightmap_compressed
struct environment_lightmap_vertex_compressed
{
	unsigned long incident_radiosity; // 0x0
	short lightmap_u; // 0x4
	short lightmap_v; // 0x6
};

// _rasterizer_vertex_type_model_uncompressed
struct model_vertex_uncompressed
{
	real_point3d position; // 0x0
	real_vector3d normal; // 0xC
	real_vector3d binormal; // 0x18
	real_vector3d tangent; // 0x24
	real_point2d texcoord; // 0x30
	short nodes[2]; // 0x38
	real weights[2]; // 0x3C
};

// _rasterizer_vertex_type_model_compressed
struct model_vertex_compressed
{
	real_point3d position; // 0x0
	unsigned long normal; // 0xC
	unsigned long binormal; // 0x10
	unsigned long tangent; // 0x14
	short texcoord_u; // 0x18
	short texcoord_v; // 0x1A
	unsigned char nodes[2]; // 0x1C
	short weights[1]; // 0x1E
};

// _rasterizer_vertex_type_dynamic_screen (xbox layout, differs from hcex)
struct dynamic_screen_vertex
{
	real_point2d position; // 0x0
	real_point2d texcoord; // 0x8
	pixel32 color; // 0x10
};

// _rasterizer_vertex_type_decal
struct decal_vertex
{
	real_point3d position; // 0x0
	unsigned long texcoord; // 0xC
};

// _rasterizer_vertex_type_detail_object (xbox layout, differs from hcex)
struct detail_object_vertex
{
	unsigned char position[3]; // 0x0
	unsigned char color[3]; // 0x3
	unsigned short data; // 0x6
};

/* ---------- prototypes/EXAMPLE.C */

/* ---------- globals */

/* ---------- public code */

#endif // __RASTERIZER_GEOMETRY_H
