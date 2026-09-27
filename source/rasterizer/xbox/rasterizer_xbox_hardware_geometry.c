/*
RASTERIZER_XBOX_HARDWARE_GEOMETRY.C
*/

/* ---------- headers */

#include "cseries.h"
#include "cseries_windows.h"
#include "errors.h"
#include "real_math.h"
#include "rasterizer.h"
#include "rasterizer_geometry.h"
#include "xbox/rasterizer_xbox.h"

/* ---------- constants */

#define RASTERIZER_XBOX_HARDWARE_GEOMETRY_FILE "c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_hardware_geometry.c"

#define RASTERIZER_STATIC_BUFFER_USAGE D3DUSAGE_WRITEONLY
#define RASTERIZER_STATIC_BUFFER_POOL D3DPOOL_MANAGED

/* ---------- prototypes */

long rasterizer_geometry_get_vertex_size(short vertex_type);

boolean rasterizer_vertex_buffer_new(struct vertex_buffer *buffer, short type, long count, void *vertices, long buffer_size);
void rasterizer_vertex_buffer_delete(struct vertex_buffer *buffer);
boolean rasterizer_triangle_buffer_new(struct triangle_buffer *buffer, short type, long count, void *triangles);
void rasterizer_triangle_buffer_delete(struct triangle_buffer *buffer);

/* ---------- public code */

boolean rasterizer_vertex_buffer_new(
	struct vertex_buffer *vertex_buffer,
	short type,
	long count,
	void *vertices,
	long buffer_size)
{
	boolean success= TRUE;
	short vertex_size= (short)rasterizer_geometry_get_vertex_size(type);
	IDirect3DVertexBuffer8 *d3d_vertex_buffer;
	BYTE *vertex_data;

	match_assert(RASTERIZER_XBOX_HARDWARE_GEOMETRY_FILE, 24, vertex_buffer);
	match_assert(RASTERIZER_XBOX_HARDWARE_GEOMETRY_FILE, 25, vertex_size*count==buffer_size || !vertices);

	if (!count)
	{
		success= FALSE;
	}

	if (!global_d3d_device)
	{
		success= FALSE;
	}
	else if (success)
	{
		D3DCALL(success, IDirect3DDevice8_CreateVertexBuffer(global_d3d_device, buffer_size, RASTERIZER_STATIC_BUFFER_USAGE, 0, RASTERIZER_STATIC_BUFFER_POOL, &d3d_vertex_buffer));

		if (!d3d_vertex_buffer)
		{
			success= FALSE;
		}

		if (!success)
		{
			d3d_vertex_buffer= NULL;
		}
	}

	if (vertices)
	{
		if (success)
		{
			rasterizer_globals.current_lock_operation= _rasterizer_lock_vertexbuffer_new;
			IDirect3DVertexBuffer8_Lock(d3d_vertex_buffer, 0, buffer_size, &vertex_data, 0);
			rasterizer_globals.current_lock_operation= _rasterizer_lock_none;

			if (!vertex_data)
			{
				success= FALSE;
			}

			if (success)
			{
				csmemcpy(vertex_data, vertices, buffer_size);
				D3DCALL(success, IDirect3DVertexBuffer8_Unlock(d3d_vertex_buffer));

				vertex_buffer->count= count;
				vertex_buffer->offset= 0;
				vertex_buffer->type= type;
				vertex_buffer->base_address= vertices;
				vertex_buffer->hardware_format= d3d_vertex_buffer;
			}
			else
			{
				vertex_data= NULL;
			}
		}
	}

	if (!success)
	{
		csmemset(vertex_buffer, 0, sizeof(struct vertex_buffer));
		error(_error_silent, "### ERROR failed to create vertex buffer hardware format");
	}

	return success;
}

void rasterizer_vertex_buffer_delete(
	struct vertex_buffer *buffer)
{
	if (buffer && buffer->hardware_format)
	{
		IDirect3DVertexBuffer8_Release((IDirect3DVertexBuffer8 *)buffer->hardware_format);
		buffer->hardware_format= NULL;
	}

	return;
}

boolean rasterizer_triangle_buffer_new(
	struct triangle_buffer *triangle_buffer,
	short type,
	long count,
	void *triangles)
{
	boolean success= TRUE;
	long buffer_size= 0;
	IDirect3DIndexBuffer8 *d3d_index_buffer;
	BYTE *index_buffer_data;

	match_assert(RASTERIZER_XBOX_HARDWARE_GEOMETRY_FILE, 115, triangle_buffer);
	match_assert(RASTERIZER_XBOX_HARDWARE_GEOMETRY_FILE, 116, triangles);
	match_assert(RASTERIZER_XBOX_HARDWARE_GEOMETRY_FILE, 117, count>0);

	switch (type)
	{
	case _triangle_buffer_type_triangles:
		buffer_size= 3*sizeof(word)*count;
		break;
	case _triangle_buffer_type_precompiled_strip:
		buffer_size= sizeof(word)*(count+2);
		break;
	default:
		match_vassert(RASTERIZER_XBOX_HARDWARE_GEOMETRY_FILE, 128, FALSE, "### ERROR unsupported triangle buffer type");
	}

	if (!global_d3d_device)
	{
		success= FALSE;
		csmemset(triangle_buffer, 0, sizeof(struct triangle_buffer));
		error(_error_silent, "### ERROR failed to create triangle buffer hardware format");
	}
	else
	{
		if (success)
		{
			D3DCALL(success, IDirect3DDevice8_CreateIndexBuffer(global_d3d_device, buffer_size, RASTERIZER_STATIC_BUFFER_USAGE, D3DFMT_INDEX16, RASTERIZER_STATIC_BUFFER_POOL, &d3d_index_buffer));

			if (!d3d_index_buffer)
			{
				success= FALSE;
			}

			if (!success)
			{
				d3d_index_buffer= NULL;
			}
		}

		if (success)
		{
			IDirect3DIndexBuffer8_Lock(d3d_index_buffer, 0, buffer_size, &index_buffer_data, 0);

			if (!index_buffer_data)
			{
				success= FALSE;
			}

			if (!success)
			{
				index_buffer_data= NULL;
			}
		}

		if (success)
		{
			csmemcpy(index_buffer_data, triangles, buffer_size);
			D3DCALL(success, IDirect3DIndexBuffer8_Unlock(d3d_index_buffer));

			triangle_buffer->type= type;
			triangle_buffer->count= count;
			triangle_buffer->offset= (long)triangles;
			triangle_buffer->hardware_format= d3d_index_buffer;
		}
		else
		{
			csmemset(triangle_buffer, 0, sizeof(struct triangle_buffer));
			error(_error_silent, "### ERROR failed to create triangle buffer hardware format");
		}
	}

	return success;
}

void rasterizer_triangle_buffer_delete(
	struct triangle_buffer *buffer)
{
	if (buffer && buffer->hardware_format)
	{
		IDirect3DIndexBuffer8_Release((IDirect3DIndexBuffer8 *)buffer->hardware_format);
		buffer->hardware_format= NULL;
	}

	return;
}
