/*
RASTERIZER_GEOMETRY.C

symbols in this file:
0016F7D0 0020:
	_uncompress_int8_to_real (0000)
0016F7F0 0020:
	_uncompress_int16_to_real (0000)
0016F810 0090:
	_uncompress_int32_to_real_vector3d (0000)
0016F8A0 0050:
	_rasterizer_geometry_get_vertex_size (0000)
0016F8F0 0010:
	_rasterizer_geometry_byte_swap_vertices (0000)
0016F900 0440:
	_rasterizer_geometry_uncompress_vertices (0000)
0016FD40 0010:
	_rasterizer_geometry_stripify (0000)
0016FD50 0070:
	_environment_vertex_compressed_get_point (0000)
0016FDC0 0080:
	_environment_vertex_compressed_get_normal (0000)
0016FE40 0070:
	_environment_vertex_compressed_get_texcoord (0000)
0016FEB0 0080:
	_environment_lightmap_vertex_compressed_get_incident_radiosity (0000)
0016FF30 0090:
	_environment_lightmap_vertex_compressed_get_texcoord (0000)
0016FFC0 0060:
	_compress_real_to_int8 (0000)
00170020 0050:
	_compress_real_to_int8_clamp (0000)
00170070 0070:
	_compress_real_to_int16 (0000)
001700E0 0060:
	_compress_real_to_int16_clamp (0000)
00170140 0220:
	_compress_real_vector3d_to_int32 (0000)
00170360 0200:
	_compress_real_vector3d_to_int32_clamp (0000)
00170560 02e0:
	_rasterizer_geometry_compress_vertices (0000)
0029E344 001a:
	?rasterizer_vertex_type_sizes@?1??rasterizer_geometry_get_vertex_size@@9@9 (0000)
0029E360 0004:
	__real@35000000 (0000)
0029E364 0004:
	__real@3a001002 (0000)
0029E368 0030:
	??_C@_0DA@GFMENBNG@c?3?2halo?2SOURCE?2rasterizer?2raster@ (0000)
0029E398 0044:
	??_C@_0EE@PNJAPPJM@count?$CKsizeof?$CIstruct?5environment_@ (0000)
0029E3E0 0048:
	??_C@_0EI@DONGBPFL@count?$CKsizeof?$CIstruct?5environment_@ (0000)
0029E428 004d:
	??_C@_0EN@HJINING@count?$CKsizeof?$CIstruct?5environment_@ (0000)
0029E478 0051:
	??_C@_0FB@GCMMGGGN@count?$CKsizeof?$CIstruct?5environment_@ (0000)
0029E4CC 0013:
	??_C@_0BD@OPFHNGDK@src?9?$DOnodes?$FL1?$FN?$CF3?$DN?$DN0?$AA@ (0000)
0029E4E0 0013:
	??_C@_0BD@CDPNNGKE@src?9?$DOnodes?$FL0?$FN?$CF3?$DN?$DN0?$AA@ (0000)
0029E4F4 003e:
	??_C@_0DO@MIHGPCNE@count?$CKsizeof?$CIstruct?5model_vertex@ (0000)
0029E538 0042:
	??_C@_0EC@DGDJGMJD@count?$CKsizeof?$CIstruct?5model_vertex@ (0000)
0029E57C 0036:
	??_C@_0DG@CBADPEAN@?$CD?$CD?$CD?5ERROR?5can?8t?5uncompress?5this?5@ (0000)
0029E5B4 000d:
	??_C@_0N@NFCOPMLF@uncompressed?$AA@ (0000)
0029E5C4 0009:
	??_C@_08FDJGCBLL@texcoord?$AA@ (0000)
0029E5D0 0013:
	??_C@_0BD@GHLLAJAG@z?$DO?$DN0?40f?5?$CG?$CG?5z?$DM?$DN1?40f?$AA@ (0000)
0029E5E4 0004:
	__real@46ffff00 (0000)
0029E5E8 0014:
	??_C@_0BE@NNGOJEKG@z?$DO?$DN?91?40f?5?$CG?$CG?5z?$DM?$DN1?40f?$AA@ (0000)
0029E5FC 0018:
	??_C@_0BI@PFBMHOJF@fabs?$CIv2?4k?5?9?5v?9?$DOk?$CJ?$DM0?401f?$AA@ (0000)
0029E614 0018:
	??_C@_0BI@EMAPPLEH@fabs?$CIv2?4j?5?9?5v?9?$DOj?$CJ?$DM0?401f?$AA@ (0000)
0029E62C 0018:
	??_C@_0BI@FMEKHDHA@fabs?$CIv2?4i?5?9?5v?9?$DOi?$CJ?$DM0?401f?$AA@ (0000)
0029E644 0004:
	__real@43ffc000 (0000)
0029E648 0004:
	__real@447fe000 (0000)
0029E64C 0024:
	??_C@_0CE@BAFANFAL@invalid?5vector?$DN?5?$FL?$CFf?5?$CFf?5?$CFf?$FN?50x?$CFx?$CF@ (0000)
0029E670 0034:
	??_C@_0DE@MCFDJBBN@?$CD?$CD?$CD?5ERROR?5can?8t?5compress?5this?5ty@ (0000)
*/

/* ---------- headers */

#include "cseries.h"
#include "errors.h"
#include "real_math.h"
#include "rasterizer_geometry.h"

/* ---------- constants */

/* ---------- macros */

/* ---------- structures */

/* ---------- prototypes */

byte compress_real_to_int8(real z);
byte compress_real_to_int8_clamp(real z);
short compress_real_to_int16(real z);
short compress_real_to_int16_clamp(real z);
unsigned long compress_real_vector3d_to_int32(const real_vector3d *v);
unsigned long compress_real_vector3d_to_int32_clamp(const real_vector3d *v);
real uncompress_int8_to_real(byte i);
real uncompress_int16_to_real(short i);
real_vector3d uncompress_int32_to_real_vector3d(unsigned long i);
long rasterizer_geometry_get_vertex_size(short type);
void rasterizer_geometry_byte_swap_vertices(short type, long count, void *vertices, long buffer_size);
void rasterizer_geometry_compress_vertices(short type, long count, void *compressed, long compressed_size, const void *uncompressed, long uncompressed_size);
void rasterizer_geometry_uncompress_vertices(short type, long count, void *uncompressed, long uncompressed_size, const void *compressed, long compressed_size);
boolean rasterizer_geometry_stripify(struct triangle_buffer *triangle_buffer, struct vertex_buffer *vertex_buffer);
void environment_vertex_compressed_get_point(const struct environment_vertex_compressed *vertex, real_point3d *point);
void environment_vertex_compressed_get_normal(const struct environment_vertex_compressed *vertex, real_vector3d *normal);
void environment_vertex_compressed_get_texcoord(const struct environment_vertex_compressed *vertex, real_point2d *texcoord);
void environment_lightmap_vertex_compressed_get_incident_radiosity(const struct environment_lightmap_vertex_compressed *vertex, real_vector3d *normal);
void environment_lightmap_vertex_compressed_get_texcoord(const struct environment_lightmap_vertex_compressed *vertex, real_point2d *texcoord);

/* ---------- globals */

/* ---------- public code */

byte compress_real_to_int8(
	real z)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 42, z>=0.0f && z<=1.0f);

	return (byte)fast_ftol(z*255.f);
}

byte compress_real_to_int8_clamp(
	real z)
{
	return (byte)fast_ftol(PIN(z, 0.f, 1.f)*255.f);
}

short compress_real_to_int16(
	real z)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 55, z>=-1.0f && z<=1.0f);

	return (short)fast_ftol((real)floor(z*32767.5f));
}

short compress_real_to_int16_clamp(
	real z)
{
	return (short)fast_ftol((real)floor(PIN(z, -1.f, 1.f)*32767.5f));
}

// TODO: the original reuses one stack slot for the three fast_ftol results and masks them
// into edi/ebx immediately; ours keeps three slots and combines at the end
unsigned long compress_real_vector3d_to_int32(
	const real_vector3d *v)
{
	unsigned long i, j, k;
	unsigned long compressed;
	real_vector3d v2;

	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 69, v);
	match_vassert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 78,
		v->i>=-1.f && v->i<=1.f &&
		v->j>=-1.f && v->j<=1.f &&
		v->k>=-1.f && v->k<=1.f,
		csprintf(temporary, "invalid vector= [%f %f %f] 0x%x%x%x", v->i, v->j, v->k, *(long *)&v->i, *(long *)&v->j, *(long *)&v->k));

	i= fast_ftol((real)floor(v->i*1023.5f))&0x7ff;
	j= fast_ftol((real)floor(v->j*1023.5f))&0x7ff;
	k= fast_ftol((real)floor(v->k*511.5f))&0x3ff;
	compressed= (((k<<11)|j)<<11)|i;

	v2= uncompress_int32_to_real_vector3d(compressed);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 92, fabs(v2.i - v->i)<0.01f);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 93, fabs(v2.j - v->j)<0.01f);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 94, fabs(v2.k - v->k)<0.01f);

	return compressed;
}

// TODO: same fast_ftol stack slot / register allocation mismatch as compress_real_vector3d_to_int32
unsigned long compress_real_vector3d_to_int32_clamp(
	const real_vector3d *v)
{
	unsigned long i, j, k;
	unsigned long compressed;
	real_vector3d v2;

	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 104, v);

	i= fast_ftol((real)floor(PIN(v->i, -1.f, 1.f)*1023.5f))&0x7ff;
	j= fast_ftol((real)floor(PIN(v->j, -1.f, 1.f)*1023.5f))&0x7ff;
	k= fast_ftol((real)floor(PIN(v->k, -1.f, 1.f)*511.5f))&0x3ff;
	compressed= (((k<<11)|j)<<11)|i;

	v2= uncompress_int32_to_real_vector3d(compressed);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 118, fabs(v2.i - v->i)<0.01f);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 119, fabs(v2.j - v->j)<0.01f);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 120, fabs(v2.k - v->k)<0.01f);

	return compressed;
}

real uncompress_int8_to_real(
	byte i)
{
	return i*(1.f/255.f);
}

real uncompress_int16_to_real(
	short i)
{
	return (2.f*i+1.f)*(1.f/65535.f);
}

// TODO: `shl eax,16h` is scheduled before the first fadd instead of after it
real_vector3d uncompress_int32_to_real_vector3d(
	unsigned long i)
{
	real_vector3d v;

	v.i= (1.f+(real)(long)(i<<21)/(real)(1<<20))*(1.f/2047.f);
	i>>= 11;
	v.j= (1.f+(real)(long)(i<<21)/(real)(1<<20))*(1.f/2047.f);
	i>>= 11;
	v.k= (1.f+(real)(long)(i<<22)/(real)(1<<21))*(1.f/1023.f);

	return v;
}

long rasterizer_geometry_get_vertex_size(
	short type)
{
	// trailing zero entry is in the original
	static const short rasterizer_vertex_type_sizes[NUMBER_OF_XBOX_RASTERIZER_VERTEX_TYPES+1]=
	{
		sizeof(struct environment_vertex_uncompressed),
		sizeof(struct environment_vertex_compressed),
		sizeof(struct environment_lightmap_vertex_uncompressed),
		sizeof(struct environment_lightmap_vertex_compressed),
		sizeof(struct model_vertex_uncompressed),
		sizeof(struct model_vertex_compressed),
		24,
		36,
		20,
		16,
		16,
		8
	};

	match_vassert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 170, type>=0 && type<NUMBER_OF_XBOX_RASTERIZER_VERTEX_TYPES,
		"type>=0 && type<NUMBER_OF_RASTERIZER_VERTEX_TYPES");

	return rasterizer_vertex_type_sizes[type];
}

void rasterizer_geometry_byte_swap_vertices(
	short type,
	long count,
	void *vertices,
	long buffer_size)
{
	return;
}

void rasterizer_geometry_compress_vertices(
	short type,
	long count,
	void *compressed,
	long compressed_size,
	const void *uncompressed,
	long uncompressed_size)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 194, uncompressed);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 195, compressed);

	switch (type)
	{
	case _rasterizer_vertex_type_environment_uncompressed:
	{
		struct environment_vertex_compressed *dst= (struct environment_vertex_compressed *)compressed;
		const struct environment_vertex_uncompressed *src= (const struct environment_vertex_uncompressed *)uncompressed;
		long vertex_index;

		match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 201, count*sizeof(struct environment_vertex_uncompressed)==uncompressed_size);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 202, count*sizeof(struct environment_vertex_compressed)==compressed_size);

		for (vertex_index= 0; vertex_index<count; vertex_index++, src++, dst++)
		{
			dst->position= src->position;
			dst->normal= compress_real_vector3d_to_int32_clamp(&src->normal);
			dst->binormal= compress_real_vector3d_to_int32_clamp(&src->binormal);
			dst->tangent= compress_real_vector3d_to_int32_clamp(&src->tangent);
			dst->texcoord= src->texcoord;
		}
		break;
	}
	case _rasterizer_vertex_type_environment_lightmap_uncompressed:
	{
		struct environment_lightmap_vertex_compressed *dst= (struct environment_lightmap_vertex_compressed *)compressed;
		const struct environment_lightmap_vertex_uncompressed *src= (const struct environment_lightmap_vertex_uncompressed *)uncompressed;
		long vertex_index;

		match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 221, count*sizeof(struct environment_lightmap_vertex_uncompressed)==uncompressed_size);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 222, count*sizeof(struct environment_lightmap_vertex_compressed)==compressed_size);

		for (vertex_index= 0; vertex_index<count; vertex_index++, src++, dst++)
		{
			dst->incident_radiosity= compress_real_vector3d_to_int32_clamp(&src->incident_radiosity);
			dst->lightmap_u= compress_real_to_int16_clamp(src->texcoord.x);
			dst->lightmap_v= compress_real_to_int16_clamp(src->texcoord.y);
		}
		break;
	}
	case _rasterizer_vertex_type_model_uncompressed:
	{
		struct model_vertex_compressed *dst= (struct model_vertex_compressed *)compressed;
		const struct model_vertex_uncompressed *src= (const struct model_vertex_uncompressed *)uncompressed;
		long vertex_index;

		match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 239, count*sizeof(struct model_vertex_uncompressed)==uncompressed_size);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 240, count*sizeof(struct model_vertex_compressed)==compressed_size);

		for (vertex_index= 0; vertex_index<count; vertex_index++, src++, dst++)
		{
			dst->position= src->position;
			dst->normal= compress_real_vector3d_to_int32_clamp(&src->normal);
			dst->binormal= compress_real_vector3d_to_int32_clamp(&src->binormal);
			dst->tangent= compress_real_vector3d_to_int32_clamp(&src->tangent);
			dst->texcoord_u= compress_real_to_int16_clamp(src->texcoord.x);
			dst->texcoord_v= compress_real_to_int16_clamp(src->texcoord.y);
			dst->nodes[0]= (byte)(3*src->nodes[0]);
			dst->nodes[1]= (byte)(3*src->nodes[1]);
			dst->weights[0]= compress_real_to_int16_clamp(src->weights[0]);
		}
		break;
	}
	default:
		error(_error_silent, "### ERROR can't compress this type of vertex buffer");
		break;
	}

	return;
}

void rasterizer_geometry_uncompress_vertices(
	short type,
	long count,
	void *uncompressed,
	long uncompressed_size,
	const void *compressed,
	long compressed_size)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 280, uncompressed);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 281, compressed);

	switch (type)
	{
	case _rasterizer_vertex_type_environment_compressed:
	{
		struct environment_vertex_uncompressed *dst= (struct environment_vertex_uncompressed *)uncompressed;
		const struct environment_vertex_compressed *src= (const struct environment_vertex_compressed *)compressed;
		long vertex_index;

		match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 287, count*sizeof(struct environment_vertex_uncompressed)==uncompressed_size);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 288, count*sizeof(struct environment_vertex_compressed)==compressed_size);

		for (vertex_index= 0; vertex_index<count; vertex_index++, dst++, src++)
		{
			dst->position= src->position;
			dst->normal= uncompress_int32_to_real_vector3d(src->normal);
			dst->binormal= uncompress_int32_to_real_vector3d(src->binormal);
			dst->tangent= uncompress_int32_to_real_vector3d(src->tangent);
			dst->texcoord= src->texcoord;
		}
		break;
	}
	case _rasterizer_vertex_type_environment_lightmap_compressed:
	{
		struct environment_lightmap_vertex_uncompressed *dst= (struct environment_lightmap_vertex_uncompressed *)uncompressed;
		const struct environment_lightmap_vertex_compressed *src= (const struct environment_lightmap_vertex_compressed *)compressed;
		long vertex_index;

		match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 307, count*sizeof(struct environment_lightmap_vertex_uncompressed)==uncompressed_size);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 308, count*sizeof(struct environment_lightmap_vertex_compressed)==compressed_size);

		for (vertex_index= 0; vertex_index<count; vertex_index++, dst++, src++)
		{
			dst->incident_radiosity= uncompress_int32_to_real_vector3d(src->incident_radiosity);
			dst->texcoord.x= uncompress_int16_to_real(src->lightmap_u);
			dst->texcoord.y= uncompress_int16_to_real(src->lightmap_v);
		}
		break;
	}
	case _rasterizer_vertex_type_model_compressed:
	{
		struct model_vertex_uncompressed *dst= (struct model_vertex_uncompressed *)uncompressed;
		const struct model_vertex_compressed *src= (const struct model_vertex_compressed *)compressed;
		long vertex_index;

		match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 325, count*sizeof(struct model_vertex_uncompressed)==uncompressed_size);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 326, count*sizeof(struct model_vertex_compressed)==compressed_size);

		for (vertex_index= 0; vertex_index<count; vertex_index++, dst++, src++)
		{
			dst->position= src->position;
			dst->normal= uncompress_int32_to_real_vector3d(src->normal);
			dst->binormal= uncompress_int32_to_real_vector3d(src->binormal);
			dst->tangent= uncompress_int32_to_real_vector3d(src->tangent);
			dst->texcoord.x= uncompress_int16_to_real(src->texcoord_u);
			dst->texcoord.y= uncompress_int16_to_real(src->texcoord_v);
			match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 341, src->nodes[0]%3==0);
			match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 342, src->nodes[1]%3==0);
			dst->nodes[0]= src->nodes[0]/3;
			dst->nodes[1]= src->nodes[1]/3;
			dst->weights[0]= uncompress_int8_to_real((byte)src->weights[0]);
			dst->weights[1]= 1.f-dst->weights[0];
		}
		break;
	}
	default:
		error(_error_silent, "### ERROR can't uncompress this type of vertex buffer");
		break;
	}

	return;
}

boolean rasterizer_geometry_stripify(
	struct triangle_buffer *triangle_buffer,
	struct vertex_buffer *vertex_buffer)
{
	return TRUE;
}

void environment_vertex_compressed_get_point(
	const struct environment_vertex_compressed *vertex,
	real_point3d *point)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 438, vertex);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 439, point);

	*point= vertex->position;

	return;
}

void environment_vertex_compressed_get_normal(
	const struct environment_vertex_compressed *vertex,
	real_vector3d *normal)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 450, vertex);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 451, normal);

	*normal= uncompress_int32_to_real_vector3d(vertex->normal);

	return;
}

void environment_vertex_compressed_get_texcoord(
	const struct environment_vertex_compressed *vertex,
	real_point2d *texcoord)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 462, vertex);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 463, texcoord);

	*texcoord= vertex->texcoord;

	return;
}

void environment_lightmap_vertex_compressed_get_incident_radiosity(
	const struct environment_lightmap_vertex_compressed *vertex,
	real_vector3d *normal)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 474, vertex);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 475, normal);

	*normal= uncompress_int32_to_real_vector3d(vertex->incident_radiosity);

	return;
}

void environment_lightmap_vertex_compressed_get_texcoord(
	const struct environment_lightmap_vertex_compressed *vertex,
	real_point2d *texcoord)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 486, vertex);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 487, texcoord);

	texcoord->x= uncompress_int16_to_real(vertex->lightmap_u);
	texcoord->y= uncompress_int16_to_real(vertex->lightmap_v);

	return;
}
