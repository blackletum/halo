/*
RASTERIZER_TEXT.C

symbols in this file:
00172E80 0010:
	_lock_rasterizer_text_data (0000)
00172E90 0010:
	_unlock_rasterizer_text_data (0000)
00172EA0 0090:
	_rasterizer_text_cache_initialize (0000)
00172F30 0010:
	_rasterizer_text_set_shadow_color (0000)
00172F40 0030:
	_rasterizer_text_cache_flush (0000)
00172F70 0030:
	_rasterizer_text_cache_dispose (0000)
00172FA0 0020:
	_hardware_character_cache_get_bitmap (0000)
00172FC0 00b0:
	_hardware_character_cache_get_origin (0000)
00173070 0060:
	_flush_hardware_character (0000)
001730D0 0380:
	_cache_hardware_format_character (0000)
00173450 00f0:
	_rasterizer_draw_character (0000)
00173540 0170:
	_rasterizer_draw_character_with_dropshadow (0000)
001736B0 0200:
	_rasterizer_draw_string (0000)
001738B0 0200:
	_rasterizer_draw_unicode_string (0000)
0029EEE0 0033:
	??_C@_0DD@DKOHMJNA@?$CD?$CD?$CD?5ERROR?5failed?5to?5initialize?5h@ (0000)
0029EF14 0026:
	??_C@_0CG@HPKDNNGC@?$CBhardware_character_cache?4initia@ (0000)
0029EF3C 002c:
	??_C@_0CM@KJINBGGM@c?3?2halo?2SOURCE?2rasterizer?2raster@ (0000)
0029EF68 0009:
	??_C@_08KDNNBGOA@x0?5?$CG?$CG?5y0?$AA@ (0000)
0029EF78 0054:
	??_C@_0FE@BCPFIEIE@hardware_character_index?$DO?$DN0?5?$CG?$CG?5h@ (0000)
0029EFCC 0025:
	??_C@_0CF@POBHCEMM@hardware_character_cache?4initial@ (0000)
0029EFF4 0026:
	??_C@_0CG@JHCOKPHL@font?5cache?5overwrote?5character?5i@ (0000)
0029F01C 0013:
	??_C@_0BD@PIEBJAO@hardware_character?$AA@ (0000)
0029F030 0046:
	??_C@_0EG@CBPAFGHN@font_character?9?$DObitmap_height?$DM?$DNH@ (0000)
0029F078 0044:
	??_C@_0EE@KGLMBKON@font_character?9?$DObitmap_width?$DM?$DNHA@ (0000)
0029F0C0 0068:
	??_C@_0GI@IDEJCHPO@font_character?$DN?$DNhardware_charact@ (0000)
0029F128 0074:
	??_C@_0HE@KFKECHAF@font_character?9?$DOhardware_charact@ (0000)
0030D4D0 0002:
	_magic_number (0000)
004B82C0 0816:
	_hardware_character_cache (0000)
	_global_shadow_color (0000)
	?warned@?1??rasterizer_draw_string@@9@9 (0000)
	?warned@?1??rasterizer_draw_unicode_string@@9@9 (0000)
*/

/* ---------- headers */

#include "cseries.h"
#include "errors.h"
#include "real_math.h"
#include "bitmaps.h"
#include "rasterizer.h"
#include "render.h"
#include "rasterizer/rasterizer_geometry.h"
#include "tag_files/tag_groups.h"
#include "text/font_group.h"

/* ---------- constants */

enum
{
	HARDWARE_CHARACTER_CACHE_BITMAP_WIDTH= 128,
	HARDWARE_CHARACTER_CACHE_BITMAP_HEIGHT= 128,
	MAXIMUM_HARDWARE_CHARACTERS= 256,
	MAXIMUM_HARDWARE_CHARACTER_MASK= MAXIMUM_HARDWARE_CHARACTERS-1
};

/* ---------- structures */

struct hardware_character
{
	struct font_character *character;
	short x0;
	short y0;
};

struct parse_string_state;

typedef void (*draw_character_proc)(struct parse_string_state *parse_state, struct font_header *font_header, struct font_character *font_character, pixel32 color, short x0, short y0, short x, short y, short width, short height);

/* ---------- prototypes */

struct bitmap_data *bitmap_2d_new(short width, short height, short mipmap_count, short format);
void bitmap_delete(struct bitmap_data *bitmap);
void *bitmap_2d_address(struct bitmap_data const *bitmap, short x, short y, short mipmap_index);

void rasterizer_text_begin(struct rasterizer_dynamic_screen_geometry_parameters const *parameters);
void rasterizer_text_end(void);
void rasterizer_text_draw_character(struct dynamic_screen_vertex const *vertices);

void draw_string(draw_character_proc draw_character, rectangle2d const *bounds, point2d *cursor_reference, rectangle2d const *clip, short height_adjust, char const *string);
void draw_unicode_string(draw_character_proc draw_character, rectangle2d const *bounds, point2d *cursor_reference, rectangle2d const *clip, short height_adjust, wchar_t const *string);
long ustrlen(wchar_t const *string);

void rasterizer_text_cache_flush(void);
void rasterizer_text_cache_dispose(void);
struct bitmap_data *hardware_character_cache_get_bitmap(void);
void rasterizer_draw_character(struct parse_string_state *parse_state, struct font_header *font_header, struct font_character *font_character, pixel32 color, short x0, short y0, short x, short y, short width, short height);

void lock_rasterizer_text_data(void);
void unlock_rasterizer_text_data(void);
static void hardware_character_cache_get_origin(short hardware_character_index, short *x0, short *y0);
static void flush_hardware_character(struct hardware_character *hardware_character);
static void cache_hardware_format_character(struct font_header *font_header, struct font_character *font_character);
static void rasterizer_draw_character_with_dropshadow(struct parse_string_state *parse_state, struct font_header *font_header, struct font_character *font_character, pixel32 color, short x0, short y0, short x, short y, short width, short height);

/* ---------- globals */

extern struct rasterizer_window_begin_parameters global_window_parameters;

static struct
{
	boolean initialized;
	short read_index;
	short write_index;
	short x0;
	short y0;
	short maximum_character_height;
	struct bitmap_data *bitmap;
	struct hardware_character characters[MAXIMUM_HARDWARE_CHARACTERS];
} hardware_character_cache;
static unsigned long global_shadow_color;
static unsigned short magic_number= 12; // magic_number

/* ---------- public code */

// lock_rasterizer_text_data
void lock_rasterizer_text_data(
	void)
{
	return;
}

// unlock_rasterizer_text_data
void unlock_rasterizer_text_data(
	void)
{
	return;
}

boolean rasterizer_text_cache_initialize(
	void)
{
	struct bitmap_data *bitmap;
	boolean success= TRUE;

	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_text.c", 118, !hardware_character_cache.initialized);

	bitmap= bitmap_2d_new(HARDWARE_CHARACTER_CACHE_BITMAP_WIDTH, HARDWARE_CHARACTER_CACHE_BITMAP_HEIGHT, 0, _bitmap_format_a4r4g4b4);
	if (bitmap)
	{
		memset(&hardware_character_cache, 0, sizeof(hardware_character_cache));
		if (rasterizer_bitmap_new(bitmap))
		{
			hardware_character_cache.bitmap= bitmap;
			hardware_character_cache.initialized= success;
		}
		else
		{
			error(_error_silent, "### ERROR failed to initialize hardware text cache");
			success= FALSE;
		}
	}
	else
	{
		error(_error_silent, "### ERROR failed to initialize hardware text cache");
		success= FALSE;
	}

	return success;
}

void rasterizer_text_set_shadow_color(
	pixel32 color)
{
	global_shadow_color= color;

	return;
}

// TODO: x87 scheduling of the texture scale divides differs slightly
void rasterizer_draw_string(
	rectangle2d const *bounds,
	rectangle2d const *clip,
	point2d *cursor_reference,
	short height_adjust,
	char const *string)
{
	static boolean warned= FALSE;

	if (rasterizer_debug_options.draw_dynamic_screen_geometry && !global_window_parameters.rasterizer_target)
	{
		struct bitmap_data *bitmap;

		magic_number++;
		match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_text.c", 180, string);

		bitmap= hardware_character_cache_get_bitmap();
		if (bitmap && *string)
		{
			struct rasterizer_dynamic_screen_geometry_parameters parameters;
			rectangle2d adjusted_bounds;
			rectangle2d adjusted_clip;

			strlen(string);

			if (!bounds)
			{
				adjusted_bounds= render.camera.window_bounds;
				offset_rectangle2d(&adjusted_bounds, -render.camera.viewport_bounds.x0, -render.camera.viewport_bounds.y0);
			}
			else
			{
				adjusted_bounds= *bounds;
			}

			if (!clip)
			{
				adjusted_clip= render.camera.viewport_bounds;
				offset_rectangle2d(&adjusted_clip, -render.camera.viewport_bounds.x0, -render.camera.viewport_bounds.y0);
			}
			else
			{
				set_rectangle2d(&adjusted_clip,
					MAX(0, clip->x0),
					MAX(0, clip->y0),
					MIN(render.camera.viewport_bounds.x1-render.camera.viewport_bounds.x0, clip->x1),
					MIN(render.camera.viewport_bounds.y1-render.camera.viewport_bounds.y0, clip->y1));
			}

			memset(&parameters, 0, sizeof(parameters));
			parameters.meter_parameters= NULL;
			parameters.map[0]= bitmap;
			parameters.map_scale[0].i= 1.f;
			parameters.map_scale[0].j= 1.f;
			parameters.map_texture_scale[0].i= 1.f/bitmap->width;
			parameters.map_texture_scale[0].j= 1.f/bitmap->height;
			parameters.framebuffer_blend_function= 0;
			parameters.point_sampled= FALSE;
			rasterizer_text_begin(&parameters);
			draw_string(rasterizer_draw_character_with_dropshadow, &adjusted_bounds, cursor_reference, &adjusted_clip, height_adjust, string);
			rasterizer_text_end();
		}
	}

	return;
}

// TODO: x87 scheduling of the texture scale divides differs slightly
void rasterizer_draw_unicode_string(
	rectangle2d const *bounds,
	rectangle2d const *clip,
	point2d *cursor_reference,
	short height_adjust,
	wchar_t const *string)
{
	static boolean warned= FALSE;

	if (rasterizer_debug_options.draw_dynamic_screen_geometry && !global_window_parameters.rasterizer_target)
	{
		struct bitmap_data *bitmap;

		magic_number++;
		match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_text.c", 310, string);

		bitmap= hardware_character_cache_get_bitmap();
		if (bitmap && *string)
		{
			struct rasterizer_dynamic_screen_geometry_parameters parameters;
			rectangle2d adjusted_bounds;
			rectangle2d adjusted_clip;

			ustrlen(string);

			if (!bounds)
			{
				adjusted_bounds= render.camera.window_bounds;
				offset_rectangle2d(&adjusted_bounds, -render.camera.viewport_bounds.x0, -render.camera.viewport_bounds.y0);
			}
			else
			{
				adjusted_bounds= *bounds;
			}

			if (!clip)
			{
				adjusted_clip= render.camera.viewport_bounds;
				offset_rectangle2d(&adjusted_clip, -render.camera.viewport_bounds.x0, -render.camera.viewport_bounds.y0);
			}
			else
			{
				set_rectangle2d(&adjusted_clip,
					MAX(0, clip->x0),
					MAX(0, clip->y0),
					MIN(render.camera.viewport_bounds.x1-render.camera.viewport_bounds.x0, clip->x1),
					MIN(render.camera.viewport_bounds.y1-render.camera.viewport_bounds.y0, clip->y1));
			}

			memset(&parameters, 0, sizeof(parameters));
			parameters.meter_parameters= NULL;
			parameters.map[0]= bitmap;
			parameters.map_scale[0].i= 1.f;
			parameters.map_scale[0].j= 1.f;
			parameters.map_texture_scale[0].i= 1.f/bitmap->width;
			parameters.map_texture_scale[0].j= 1.f/bitmap->height;
			parameters.framebuffer_blend_function= 0;
			parameters.point_sampled= FALSE;
			rasterizer_text_begin(&parameters);
			draw_unicode_string(rasterizer_draw_character_with_dropshadow, &adjusted_bounds, cursor_reference, &adjusted_clip, height_adjust, string);
			rasterizer_text_end();
		}
	}

	return;
}

void rasterizer_text_cache_flush(
	void)
{
	if (hardware_character_cache.initialized)
	{
		short hardware_character_index;

		for (hardware_character_index= 0; hardware_character_index<MAXIMUM_HARDWARE_CHARACTERS; hardware_character_index++)
		{
			struct hardware_character *hardware_character= &hardware_character_cache.characters[hardware_character_index];

			if (hardware_character->character)
			{
				hardware_character->character->hardware_character_index= NONE;
			}
			hardware_character->character= NULL;
		}
	}

	return;
}

void rasterizer_text_cache_dispose(
	void)
{
	if (hardware_character_cache.initialized)
	{
		rasterizer_text_cache_flush();
		bitmap_delete(hardware_character_cache.bitmap);
		hardware_character_cache.initialized= FALSE;
	}

	return;
}

/* ---------- private code */

// rasterizer_draw_character
void rasterizer_draw_character(
	struct parse_string_state *parse_state,
	struct font_header *font_header,
	struct font_character *font_character,
	pixel32 color,
	short x0,
	short y0,
	short x,
	short y,
	short width,
	short height)
{
	cache_hardware_format_character(font_header, font_character);

	if (font_character->hardware_character_index!=NONE)
	{
		struct dynamic_screen_vertex vertices[4];
		short u0, v0;

		hardware_character_cache_get_origin(font_character->hardware_character_index, &u0, &v0);
		u0+= x;
		v0+= y;

		vertices[0].color= vertices[1].color= vertices[2].color= vertices[3].color= color;
		vertices[0].position.x= vertices[3].position.x= (real)x0;
		vertices[1].position.x= vertices[2].position.x= (real)(x0+width);
		vertices[0].position.y= vertices[1].position.y= (real)y0;
		vertices[2].position.y= vertices[3].position.y= (real)(y0+height);
		vertices[0].texcoord.x= vertices[3].texcoord.x= (real)u0;
		vertices[1].texcoord.x= vertices[2].texcoord.x= (real)(u0+width);
		vertices[0].texcoord.y= vertices[1].texcoord.y= (real)v0;
		vertices[2].texcoord.y= vertices[3].texcoord.y= (real)(v0+height);
		rasterizer_text_draw_character(vertices);
	}

	return;
}

// rasterizer_draw_character_with_dropshadow
static void rasterizer_draw_character_with_dropshadow(
	struct parse_string_state *parse_state,
	struct font_header *font_header,
	struct font_character *font_character,
	pixel32 color,
	short x0,
	short y0,
	short x,
	short y,
	short width,
	short height)
{
	cache_hardware_format_character(font_header, font_character);

	if (font_character->hardware_character_index!=NONE)
	{
		struct dynamic_screen_vertex vertices[4];
		pixel32 shadow_color;
		real dx= 1.f, dy= 1.f;
		real screen_x0, screen_x1, screen_y0, screen_y1;
		boolean shadow;
		short u0, v0;

		shadow_color= global_shadow_color ? global_shadow_color : color&0xFF000000;

		screen_x0= (real)x0;
		screen_x1= (real)(x0+width);
		screen_y0= (real)y0;
		screen_y1= (real)(y0+height);
		shadow= TRUE;

		while (TRUE)
		{
			boolean drawing_shadow;
			pixel32 vertex_color;

			hardware_character_cache_get_origin(font_character->hardware_character_index, &u0, &v0);
			u0+= x;
			v0+= y;
			drawing_shadow= shadow;
			vertex_color= drawing_shadow ? shadow_color : color;

			vertices[0].color= vertices[1].color= vertices[2].color= vertices[3].color= vertex_color;
			vertices[0].position.x= vertices[3].position.x= screen_x0+dx;
			vertices[1].position.x= vertices[2].position.x= screen_x1+dx;
			vertices[0].position.y= vertices[1].position.y= screen_y0+dy;
			vertices[2].position.y= vertices[3].position.y= screen_y1+dy;
			vertices[0].texcoord.x= vertices[3].texcoord.x= (real)u0;
			vertices[1].texcoord.x= vertices[2].texcoord.x= (real)(u0+width);
			vertices[0].texcoord.y= vertices[1].texcoord.y= (real)v0;
			vertices[2].texcoord.y= vertices[3].texcoord.y= (real)(v0+height);
			rasterizer_text_draw_character(vertices);

			if (!drawing_shadow)
			{
				break;
			}
			shadow= FALSE;
			dy= 0.f;
			dx= 0.f;
		}
	}

	return;
}

// hardware_character_cache_get_bitmap
struct bitmap_data *hardware_character_cache_get_bitmap(
	void)
{
	return hardware_character_cache.initialized ? hardware_character_cache.bitmap : NULL;
}

// hardware_character_cache_get_origin
static void hardware_character_cache_get_origin(
	short hardware_character_index,
	short *x0,
	short *y0)
{
	struct hardware_character *hardware_character= &hardware_character_cache.characters[hardware_character_index];

	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_text.c", 597, hardware_character_cache.initialized);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_text.c", 598, hardware_character_index>=0 && hardware_character_index<MAXIMUM_HARDWARE_CHARACTERS);
	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_text.c", 599, x0 && y0);

	*x0= hardware_character->x0;
	*y0= hardware_character->y0;

	return;
}

// flush_hardware_character
static void flush_hardware_character(
	struct hardware_character *hardware_character)
{
	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_text.c", 610, hardware_character);

	if (hardware_character->character)
	{
		hardware_character->character->hardware_character_index= NONE;
		if (hardware_character->character->pad==magic_number)
		{
			error(_error_log, "font cache overwrote character in use");
		}
		hardware_character->character= NULL;
	}

	return;
}

// cache_hardware_format_character
static void cache_hardware_format_character(
	struct font_header *font_header,
	struct font_character *font_character)
{
	boolean cached= FALSE;

	match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_text.c", 633, hardware_character_cache.initialized);

	if (font_character->hardware_character_index!=NONE)
	{
		match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_text.c", 637, font_character->hardware_character_index>=0 && font_character->hardware_character_index<MAXIMUM_HARDWARE_CHARACTERS);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_text.c", 638, font_character==hardware_character_cache.characters[font_character->hardware_character_index].character);
		cached= TRUE;
	}

	if (!cached)
	{
		struct hardware_character *hardware_character;
		byte *source;
		short next_write_index;
		short y;

		match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_text.c", 645, font_character->bitmap_width<=HARDWARE_CHARACTER_CACHE_BITMAP_WIDTH);
		match_assert("c:\\halo\\SOURCE\\rasterizer\\rasterizer_text.c", 646, font_character->bitmap_height<=HARDWARE_CHARACTER_CACHE_BITMAP_HEIGHT);

		font_character->pad= magic_number;

		if (hardware_character_cache.x0+font_character->bitmap_width>HARDWARE_CHARACTER_CACHE_BITMAP_WIDTH)
		{
			hardware_character_cache.x0= 0;
			hardware_character_cache.y0+= hardware_character_cache.maximum_character_height;
			hardware_character_cache.maximum_character_height= 0;
		}

		if (hardware_character_cache.y0+font_character->bitmap_height>HARDWARE_CHARACTER_CACHE_BITMAP_HEIGHT)
		{
			hardware_character_cache.y0= 0;
			hardware_character_cache.x0= 0;
			hardware_character_cache.maximum_character_height= 0;

			for (; hardware_character_cache.read_index!=hardware_character_cache.write_index; hardware_character_cache.read_index= (hardware_character_cache.read_index+1)&MAXIMUM_HARDWARE_CHARACTER_MASK)
			{
				hardware_character= &hardware_character_cache.characters[hardware_character_cache.read_index];
				if (hardware_character->y0<=0)
				{
					break;
				}
				flush_hardware_character(hardware_character);
			}
		}

		if (font_character->bitmap_height>hardware_character_cache.maximum_character_height)
		{
			short y0= hardware_character_cache.y0+hardware_character_cache.maximum_character_height;
			short y1= hardware_character_cache.y0+font_character->bitmap_height;

			for (; hardware_character_cache.read_index!=hardware_character_cache.write_index; hardware_character_cache.read_index= (hardware_character_cache.read_index+1)&MAXIMUM_HARDWARE_CHARACTER_MASK)
			{
				hardware_character= &hardware_character_cache.characters[hardware_character_cache.read_index];
				if (hardware_character->y0<y0 || hardware_character->y0>=y1)
				{
					break;
				}
				flush_hardware_character(hardware_character);
			}

			hardware_character_cache.maximum_character_height= font_character->bitmap_height;
		}

		next_write_index= (hardware_character_cache.write_index+1)&MAXIMUM_HARDWARE_CHARACTER_MASK;
		if (next_write_index==hardware_character_cache.read_index)
		{
			hardware_character= &hardware_character_cache.characters[hardware_character_cache.read_index];
			flush_hardware_character(hardware_character);
			hardware_character_cache.read_index= (hardware_character_cache.read_index+1)&MAXIMUM_HARDWARE_CHARACTER_MASK;
		}

		hardware_character= &hardware_character_cache.characters[hardware_character_cache.write_index];
		font_character->hardware_character_index= hardware_character_cache.write_index;
		hardware_character->character= font_character;
		hardware_character->x0= hardware_character_cache.x0;
		hardware_character->y0= hardware_character_cache.y0;

		source= (byte *)font_header->pixels.address+font_character->pixels_offset;
		for (y= 0; y<font_character->bitmap_height; y++)
		{
			word *destination= (word *)bitmap_2d_address(hardware_character_cache.bitmap, hardware_character->x0, hardware_character->y0+y, 0);
			short x;

			for (x= 0; x<font_character->bitmap_width; x++)
			{
				*destination++= (*source++<<8)|0xFFF;
			}
		}

		rasterizer_bitmap_changed(hardware_character_cache.bitmap);
		hardware_character_cache.x0+= font_character->bitmap_width;
		hardware_character_cache.write_index= (hardware_character_cache.write_index+1)&MAXIMUM_HARDWARE_CHARACTER_MASK;
	}

	return;
}
