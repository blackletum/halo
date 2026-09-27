/*
RASTERIZER_SWIZZLE.C

symbols in this file:
00171E60 0080:
	_compute_swizzle_masks (0000)
00171EE0 0130:
	_bitmap_swizzle_vector2d (0000)
00172010 0080:
	_bitmap_swizzle_vector3d (0000)
00172090 00d0:
	_rasterizer_xbox_bitmap_swizzle2d_byte (0000)
00172160 00e0:
	_rasterizer_xbox_bitmap_swizzle2d_word (0000)
00172240 00d0:
	_rasterizer_xbox_bitmap_swizzle2d_long (0000)
00172310 0110:
	_rasterizer_xbox_bitmap_swizzle3d_byte (0000)
00172420 0120:
	_rasterizer_xbox_bitmap_swizzle3d_word (0000)
00172540 0110:
	_rasterizer_xbox_bitmap_swizzle3d_long (0000)
00172650 0320:
	_rasterizer_xbox_bitmap_swizzle (0000)
00172970 0170:
	_rasterizer_xbox_bitmap_get_max_mipmap_count (0000)
00172AE0 0100:
	_rasterizer_xbox_bitmap_get_pixel_data_size (0000)
00172BE0 02a0:
	_rasterizer_xbox_bitmap_rebuild_hardware_format (0000)
0029ED10 008c:
	?swizzle_table@?1??bitmap_swizzle_vector2d@@9@9 (0000)
	?face_mapping_inverse_table@?1??rasterizer_xbox_bitmap_rebuild_hardware_format@@9@9 (0080)
0029ED9C 000f:
	??_C@_0P@KPAPAAAB@upper_mask?$DM?$DN63?$AA@ (0000)
0029EDAC 002f:
	??_C@_0CP@CLCMMKEO@c?3?2halo?2SOURCE?2rasterizer?2raster@ (0000)
0029EDDC 0004:
	??_C@_03HHBLCKEM@dst?$AA@ (0000)
0029EDE0 003c:
	??_C@_0DM@OLNFINAL@?$CD?$CD?$CD?5ERROR?5failed?5to?5allocate?5tem@ (0000)
0029EE1C 0036:
	??_C@_0DG@PCFNAGMO@?$CD?$CD?$CD?5ERROR?5unsupported?5bitmap?5for@ (0000)
0029EE58 0050:
	??_C@_0FA@BCGGDOFM@?$CD?$CD?$CD?5ERROR?5rasterizer_xbox_bitmap@ (0000)
0029EEA8 000d:
	??_C@_0N@ENHGMGIM@offset?$DN?$DNsize?$AA@ (0000)
0029EEB8 0028:
	??_C@_0CI@PFEJDDNL@face_index?$DN?$DN0?5?$CG?$CG?5adjusted_face_i@ (0000)
004B82B0 000c:
	_az (0000)
	_ay (0004)
	_ax (0008)
*/

/* ---------- headers */

#include "cseries.h"
#include "errors.h"
#include "integer_math.h"
#include "real_math.h"
#include "bitmaps.h"

/* ---------- constants */

#define NUMBER_OF_CUBE_MAP_FACES 6

/* ---------- macros */

/* ---------- structures */

/* ---------- prototypes */

void bitmap_swizzle_vector2d(short width, short height, short x, short y, long *swizzled);
void bitmap_swizzle_vector3d(short width, short height, short depth, short x, short y, short z, long *swizzled);
void rasterizer_xbox_bitmap_swizzle2d_byte(void *dst, void const *src, short width, short height);
void rasterizer_xbox_bitmap_swizzle2d_word(void *dst, void const *src, short width, short height);
void rasterizer_xbox_bitmap_swizzle2d_long(void *dst, void const *src, short width, short height);
void rasterizer_xbox_bitmap_swizzle3d_byte(void *dst, void const *src, short width, short height, short depth);
void rasterizer_xbox_bitmap_swizzle3d_word(void *dst, void const *src, short width, short height, short depth);
void rasterizer_xbox_bitmap_swizzle3d_long(void *dst, void const *src, short width, short height, short depth);

void rasterizer_xbox_bitmap_swizzle(struct bitmap_data *bitmap);
short rasterizer_xbox_bitmap_get_max_mipmap_count(struct bitmap_data const *bitmap);
long rasterizer_xbox_bitmap_get_pixel_data_size(struct bitmap_data const *bitmap);
boolean rasterizer_xbox_bitmap_rebuild_hardware_format(struct bitmap_data *bitmap);

// compute_swizzle_masks
static void compute_swizzle_masks(short width, short height, short depth);

/* ---------- globals */

static unsigned long ax;
static unsigned long ay;
static unsigned long az;

/* ---------- private code */

static void compute_swizzle_masks(
	short width,
	short height,
	short depth)
{
	unsigned long bit= 1;
	long mask= 1;
	long changed;

	az= 0;
	ay= 0;
	ax= 0;

	do
	{
		changed= 0;

		if (bit<(unsigned long)width)
		{
			ax|= mask;
			mask<<= 1;
			changed= mask;
		}

		if (bit<(unsigned long)height)
		{
			ay|= mask;
			mask<<= 1;
			changed= mask;
		}

		if (bit<(unsigned long)depth)
		{
			az|= mask;
			mask<<= 1;
			changed= mask;
		}

		bit<<= 1;
	}
	while (changed);

	return;
}

/* ---------- public code */

void bitmap_swizzle_vector2d(
	short width,
	short height,
	short x,
	short y,
	long *swizzled)
{
	static unsigned short const swizzle_table[64]=
	{
		0x0000, 0x0001, 0x0004, 0x0005, 0x0010, 0x0011, 0x0014, 0x0015,
		0x0040, 0x0041, 0x0044, 0x0045, 0x0050, 0x0051, 0x0054, 0x0055,
		0x0100, 0x0101, 0x0104, 0x0105, 0x0110, 0x0111, 0x0114, 0x0115,
		0x0140, 0x0141, 0x0144, 0x0145, 0x0150, 0x0151, 0x0154, 0x0155,
		0x0400, 0x0401, 0x0404, 0x0405, 0x0410, 0x0411, 0x0414, 0x0415,
		0x0440, 0x0441, 0x0444, 0x0445, 0x0450, 0x0451, 0x0454, 0x0455,
		0x0500, 0x0501, 0x0504, 0x0505, 0x0510, 0x0511, 0x0514, 0x0515,
		0x0540, 0x0541, 0x0544, 0x0545, 0x0550, 0x0551, 0x0554, 0x0555,
	};

	short log2_width= floor_log2(width);
	short log2_height= floor_log2(height);
	short log2_size= MIN(log2_width, log2_height);
	short mask= (1<<log2_size)-1;
	long swizzled_x, swizzled_y;

	if (mask<=63)
	{
		swizzled_x= swizzle_table[x&mask];
		swizzled_y= swizzle_table[y&mask];
	}
	else
	{
		long upper_mask= mask>>6;

		match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c", 86, upper_mask<=63);
		swizzled_x= swizzle_table[x&63] | (swizzle_table[(x>>6)&upper_mask]<<12);
		swizzled_y= swizzle_table[y&63] | (swizzle_table[(y>>6)&upper_mask]<<12);
	}
	swizzled_y<<= 1;

	if (log2_width>log2_size)
	{
		swizzled_x|= (x>>log2_size)<<(2*log2_size);
	}
	else if (log2_height>log2_size)
	{
		swizzled_y|= (y>>log2_size)<<(2*log2_size);
	}

	swizzled[0]= swizzled_x;
	swizzled[1]= swizzled_y;

	return;
}

void bitmap_swizzle_vector3d(
	short width,
	short height,
	short depth,
	short x,
	short y,
	short z,
	long *swizzled)
{
	short shift= 0;
	long swizzled_x= 0;
	long swizzled_y= 0;
	long swizzled_z= 0;
	short bit= 1;
	short last_shift;

	do
	{
		last_shift= shift;

		if (bit<width)
		{
			swizzled_x|= (x&1)<<shift;
			x>>= 1;
			shift++;
		}

		if (bit<height)
		{
			swizzled_y|= (y&1)<<shift;
			y>>= 1;
			shift++;
		}

		if (bit<depth)
		{
			swizzled_z|= (z&1)<<shift;
			z>>= 1;
			shift++;
		}

		bit<<= 1;
	}
	while (last_shift!=shift);

	swizzled[0]= swizzled_x;
	swizzled[1]= swizzled_y;
	swizzled[2]= swizzled_z;

	return;
}

void rasterizer_xbox_bitmap_swizzle2d_byte(
	void *dst,
	void const *src,
	short width,
	short height)
{
	long source_index= 0;
	long x_offset= 0;
	long y_offset= 0;
	short y;

	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c", 147, dst);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c", 148, src);

	compute_swizzle_masks(width, height, 1);

	for (y= 0; y<height; y++)
	{
		short x;

		for (x= 0; x<width; x++)
		{
			((byte *)dst)[y_offset|x_offset]= ((byte const *)src)[source_index];
			source_index++;
			x_offset= (x_offset-ax)&ax;
		}

		y_offset= (y_offset-ay)&ay;
	}

	return;
}

void rasterizer_xbox_bitmap_swizzle2d_word(
	void *dst,
	void const *src,
	short width,
	short height)
{
	long source_index= 0;
	long x_offset= 0;
	long y_offset= 0;
	short y;

	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c", 176, dst);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c", 177, src);

	compute_swizzle_masks(width, height, 1);

	for (y= 0; y<height; y++)
	{
		short x;

		for (x= 0; x<width; x++)
		{
			((word *)dst)[y_offset|x_offset]= ((word const *)src)[source_index];
			source_index++;
			x_offset= (x_offset-ax)&ax;
		}

		y_offset= (y_offset-ay)&ay;
	}

	return;
}

void rasterizer_xbox_bitmap_swizzle2d_long(
	void *dst,
	void const *src,
	short width,
	short height)
{
	long source_index= 0;
	long x_offset= 0;
	long y_offset= 0;
	short y;

	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c", 205, dst);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c", 206, src);

	compute_swizzle_masks(width, height, 1);

	for (y= 0; y<height; y++)
	{
		short x;

		for (x= 0; x<width; x++)
		{
			((unsigned long *)dst)[y_offset|x_offset]= ((unsigned long const *)src)[source_index];
			source_index++;
			x_offset= (x_offset-ax)&ax;
		}

		y_offset= (y_offset-ay)&ay;
	}

	return;
}

void rasterizer_xbox_bitmap_swizzle3d_byte(
	void *dst,
	void const *src,
	short width,
	short height,
	short depth)
{
	long source_index= 0;
	long x_offset= 0;
	long y_offset= 0;
	long z_offset= 0;
	short z;

	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c", 235, dst);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c", 236, src);

	compute_swizzle_masks(width, height, depth);

	for (z= 0; z<depth; z++)
	{
		short y;

		for (y= 0; y<height; y++)
		{
			short x;

			for (x= 0; x<width; x++)
			{
				((byte *)dst)[z_offset|y_offset|x_offset]= ((byte const *)src)[source_index];
				source_index++;
				x_offset= (x_offset-ax)&ax;
			}

			y_offset= (y_offset-ay)&ay;
		}

		z_offset= (z_offset-az)&az;
	}

	return;
}

void rasterizer_xbox_bitmap_swizzle3d_word(
	void *dst,
	void const *src,
	short width,
	short height,
	short depth)
{
	long source_index= 0;
	long x_offset= 0;
	long y_offset= 0;
	long z_offset= 0;
	short z;

	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c", 270, dst);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c", 271, src);

	compute_swizzle_masks(width, height, depth);

	for (z= 0; z<depth; z++)
	{
		short y;

		for (y= 0; y<height; y++)
		{
			short x;

			for (x= 0; x<width; x++)
			{
				((word *)dst)[z_offset|y_offset|x_offset]= ((word const *)src)[source_index];
				source_index++;
				x_offset= (x_offset-ax)&ax;
			}

			y_offset= (y_offset-ay)&ay;
		}

		z_offset= (z_offset-az)&az;
	}

	return;
}

void rasterizer_xbox_bitmap_swizzle3d_long(
	void *dst,
	void const *src,
	short width,
	short height,
	short depth)
{
	long source_index= 0;
	long x_offset= 0;
	long y_offset= 0;
	long z_offset= 0;
	short z;

	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c", 305, dst);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c", 306, src);

	compute_swizzle_masks(width, height, depth);

	for (z= 0; z<depth; z++)
	{
		short y;

		for (y= 0; y<height; y++)
		{
			short x;

			for (x= 0; x<width; x++)
			{
				((unsigned long *)dst)[z_offset|y_offset|x_offset]= ((unsigned long const *)src)[source_index];
				source_index++;
				x_offset= (x_offset-ax)&ax;
			}

			y_offset= (y_offset-ay)&ay;
		}

		z_offset= (z_offset-az)&az;
	}

	return;
}

void rasterizer_xbox_bitmap_swizzle(
	struct bitmap_data *bitmap)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c", 334, bitmap);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c", 335, bitmap->base_address);

	if (!TEST_FLAG(bitmap->flags, _bitmap_compressed_bit) && !TEST_FLAG(bitmap->flags, _bitmap_linear_bit))
	{
		short mipmap_index;

		match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c", 345, TEST_FLAG(bitmap->flags, _bitmap_has_power_of_two_dimensions_bit));

		for (mipmap_index= 0; mipmap_index<=bitmap->mipmap_count; mipmap_index++)
		{
			long pixel_data_size= bitmap_mipmap_get_pixel_data_size(bitmap, mipmap_index);
			byte *source= bitmap_mipmap_address(bitmap, mipmap_index);
			byte *buffer= match_malloc("c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c", 351, pixel_data_size);
			short width= bitmap_mipmap_get_width(bitmap, mipmap_index);
			short height= bitmap_mipmap_get_height(bitmap, mipmap_index);
			short depth= bitmap_mipmap_get_depth(bitmap, mipmap_index);

			if (buffer)
			{
				short bytes_per_pixel= bitmap_format_get_bits_per_pixel(bitmap->format)/8;

				compute_swizzle_masks(width, height, depth);

				switch (bitmap->type)
				{
				case _bitmap_type_2d:
					switch (bytes_per_pixel)
					{
					case 1:
						rasterizer_xbox_bitmap_swizzle2d_byte(buffer, source, width, height);
						break;
					case 2:
						rasterizer_xbox_bitmap_swizzle2d_word(buffer, source, width, height);
						break;
					case 4:
						rasterizer_xbox_bitmap_swizzle2d_long(buffer, source, width, height);
						break;
					default:
						match_vassert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c", 379, FALSE, "### ERROR unsupported bitmap format (bytes per pixel)");
					}
					break;
				case _bitmap_type_3d:
					switch (bytes_per_pixel)
					{
					case 1:
						rasterizer_xbox_bitmap_swizzle3d_byte(buffer, source, width, height, depth);
						break;
					case 2:
						rasterizer_xbox_bitmap_swizzle3d_word(buffer, source, width, height, depth);
						break;
					case 4:
						rasterizer_xbox_bitmap_swizzle3d_long(buffer, source, width, height, depth);
						break;
					default:
						match_vassert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c", 399, FALSE, "### ERROR unsupported bitmap format (bytes per pixel)");
					}
					break;
				case _bitmap_type_cube_map:
					{
						short face_index;
						byte *face_source= source;
						byte *face_buffer= buffer;

						for (face_index= 0; face_index<NUMBER_OF_CUBE_MAP_FACES; face_index++)
						{
							switch (bytes_per_pixel)
							{
							case 1:
								rasterizer_xbox_bitmap_swizzle2d_byte(face_buffer, face_source, width, height);
								break;
							case 2:
								rasterizer_xbox_bitmap_swizzle2d_word(face_buffer, face_source, width, height);
								break;
							case 4:
								rasterizer_xbox_bitmap_swizzle2d_long(face_buffer, face_source, width, height);
								break;
							default:
								match_vassert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c", 425, FALSE, "### ERROR unsupported bitmap format (bytes per pixel)");
							}

							face_source+= pixel_data_size/NUMBER_OF_CUBE_MAP_FACES;
							face_buffer+= pixel_data_size/NUMBER_OF_CUBE_MAP_FACES;
						}
					}
					break;
				default:
					match_vassert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c", 436, FALSE, "### ERROR unsupported bitmap type");
				}

				memcpy(source, buffer, pixel_data_size);
				match_free("c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c", 440, buffer);
				SET_FLAG(bitmap->flags, _bitmap_swizzled_bit, TRUE);
			}
			else
			{
				error(_error_silent, "### ERROR failed to allocate temporary buffer for swizzling");
			}
		}
	}

	return;
}

short rasterizer_xbox_bitmap_get_max_mipmap_count(
	struct bitmap_data const *bitmap)
{
	short max_mipmap_count= 0;

	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c", 459, bitmap_verify(bitmap, FALSE));

	if (TEST_FLAG(bitmap->flags, _bitmap_has_power_of_two_dimensions_bit) && !TEST_FLAG(bitmap->flags, _bitmap_linear_bit))
	{
		if (TEST_FLAG(bitmap->flags, _bitmap_compressed_bit))
		{
			max_mipmap_count= MIN(bitmap->mipmap_count, floor_log2(MAX(bitmap->width/4, MAX(bitmap->height/4, bitmap->depth))));
		}
		else
		{
			max_mipmap_count= MIN(bitmap->mipmap_count, floor_log2(MAX(bitmap->width, MAX(bitmap->height, bitmap->depth))));
		}
	}

	return max_mipmap_count;
}

long rasterizer_xbox_bitmap_get_pixel_data_size(
	struct bitmap_data const *bitmap)
{
	long pixel_data_size= 0;
	short max_mipmap_count= rasterizer_xbox_bitmap_get_max_mipmap_count(bitmap);
	short mipmap_index;

	for (mipmap_index= 0; mipmap_index<=max_mipmap_count; mipmap_index++)
	{
		long mipmap_size= bitmap_mipmap_get_pixel_data_size(bitmap, mipmap_index);

		if (TEST_FLAG(bitmap->flags, _bitmap_linear_bit))
		{
			long padding;

			match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c", 506, mipmap_index==0);
			match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c", 507, !TEST_FLAG(bitmap->flags, _bitmap_compressed_bit));
			padding= (64-bitmap_mipmap_get_row_pitch(bitmap, mipmap_index))&63;
			mipmap_size+= padding*bitmap_mipmap_get_height(bitmap, mipmap_index);
		}

		if (bitmap->type==_bitmap_type_cube_map)
		{
			mipmap_size/= NUMBER_OF_CUBE_MAP_FACES;
		}

		pixel_data_size+= mipmap_size;
	}

	pixel_data_size+= (128-pixel_data_size)&127;
	if (bitmap->type==_bitmap_type_cube_map)
	{
		pixel_data_size*= NUMBER_OF_CUBE_MAP_FACES;
	}

	return pixel_data_size;
}

boolean rasterizer_xbox_bitmap_rebuild_hardware_format(
	struct bitmap_data *bitmap)
{
	static short const face_mapping_inverse_table[NUMBER_OF_CUBE_MAP_FACES]= {0, 2, 1, 3, 4, 5};

	long size= rasterizer_xbox_bitmap_get_pixel_data_size(bitmap);
	long offset= 0;
	short face_count= (bitmap->type==_bitmap_type_cube_map) ? NUMBER_OF_CUBE_MAP_FACES : 1;
	byte *buffer;
	boolean success;

	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c", 549, bitmap->base_address);

	buffer= match_malloc("c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c", 552, size);
	if (buffer)
	{
		short face_index;

		rasterizer_xbox_bitmap_swizzle(bitmap);

		for (face_index= 0; face_index<face_count; face_index++)
		{
			short mipmap_index;
			short max_mipmap_count= rasterizer_xbox_bitmap_get_max_mipmap_count(bitmap);

			for (mipmap_index= 0; mipmap_index<=max_mipmap_count; mipmap_index++)
			{
				byte *mipmap_address= bitmap_mipmap_address(bitmap, mipmap_index);
				long mipmap_size= bitmap_mipmap_get_pixel_data_size(bitmap, mipmap_index);
				short adjusted_face_index= face_mapping_inverse_table[face_index];

				if (bitmap->type==_bitmap_type_cube_map)
				{
					mipmap_size/= NUMBER_OF_CUBE_MAP_FACES;
				}

				if (TEST_FLAG(bitmap->flags, _bitmap_linear_bit))
				{
					long row_pitch;
					long padding;
					short row;

					match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c", 588, face_index==0 && adjusted_face_index==0);
					match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c", 589, mipmap_index==0);
					match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c", 590, !TEST_FLAG(bitmap->flags, _bitmap_compressed_bit));

					row_pitch= bitmap_mipmap_get_row_pitch(bitmap, mipmap_index);
					padding= (64-row_pitch)&63;
					for (row= 0; row<bitmap->height; row++)
					{
						memcpy(buffer+offset, mipmap_address, row_pitch);
						offset+= row_pitch;
						memset(buffer+offset, 0, padding);
						mipmap_address+= row_pitch;
						offset+= padding;
					}
				}
				else
				{
					memcpy(buffer+offset, mipmap_address+mipmap_size*adjusted_face_index, mipmap_size);
					offset+= mipmap_size;
				}
			}

			memset(buffer+offset, 0, (128-offset)&127);
			offset+= (128-offset)&127;
		}

		match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c", 625, offset==size);
		memcpy(bitmap->base_address, buffer, size);
		match_free("c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c", 629, buffer);
		success= TRUE;
	}
	else
	{
		error(_error_silent, "### ERROR rasterizer_xbox_bitmap_rebuild_hardware_format failed (out of memory)");
		success= FALSE;
	}

	return success;
}
