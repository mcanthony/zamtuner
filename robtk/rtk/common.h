/* robTK - gtk2 & GL cairo-wrapper
 *
 * Copyright (C) 2013 Robin Gareus <robin@gareus.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef RTK_CAIRO_H
#define RTK_CAIRO_H

#include <string.h>
#include <math.h>

static void rounded_rectangle (cairo_t* cr, double x, double y, double w, double h, double r)
{
  double degrees = M_PI / 180.0;

  cairo_new_sub_path (cr);
  cairo_arc (cr, x + w - r, y + r, r, -90 * degrees, 0 * degrees);
  cairo_arc (cr, x + w - r, y + h - r, r, 0 * degrees, 90 * degrees);
  cairo_arc (cr, x + r, y + h - r, r, 90 * degrees, 180 * degrees);
  cairo_arc (cr, x + r, y + r, r, 180 * degrees, 270 * degrees);
  cairo_close_path (cr);
}

static void get_text_geometry( const char *txt, PangoFontDescription *font, int *tw, int *th) {
	cairo_surface_t* tmp = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 8, 8);
	cairo_t *cr = cairo_create (tmp);
	PangoLayout * pl = pango_cairo_create_layout(cr);
	pango_layout_set_font_description(pl, font);
	pango_layout_set_text(pl, txt, -1);
	pango_layout_get_pixel_size(pl, tw, th);
	g_object_unref(pl);
	cairo_destroy (cr);
	cairo_surface_destroy(tmp);
}

static void write_text_full(
		cairo_t* cr,
		const char *txt,
		PangoFontDescription *font,
		const float x, const float y,
		const float ang, const int align,
		const float * const col) {
	int tw, th;
	cairo_save(cr);

	PangoLayout * pl = pango_cairo_create_layout(cr);
	pango_layout_set_font_description(pl, font);
	cairo_set_source_rgba (cr, col[0], col[1], col[2], col[3]);
	pango_layout_set_text(pl, txt, -1);
	pango_layout_get_pixel_size(pl, &tw, &th);
	cairo_translate (cr, x, y);
	if (ang != 0) { cairo_rotate (cr, ang); }
	switch(abs(align)) {
		case 1:
			cairo_translate (cr, -tw, -th/2.0);
			break;
		case 2:
			cairo_translate (cr, -tw/2.0 - 0.5, -th/2.0);
			break;
		case 3:
			cairo_translate (cr, -0.5, -th/2.0);
			break;
		case 4:
			cairo_translate (cr, -tw, -th);
			break;
		case 5:
			cairo_translate (cr, -tw/2.0 - 0.5, -th);
			break;
		case 6:
			cairo_translate (cr, -0.5, -th);
			break;
		case 7:
			cairo_translate (cr, -tw, 0);
			break;
		case 8:
			cairo_translate (cr, -tw/2.0 - 0.5, 0);
			break;
		case 9:
			cairo_translate (cr, -0.5, 0);
			break;
		default:
			break;
	}
	pango_cairo_layout_path(cr, pl);
	pango_cairo_show_layout(cr, pl);
	g_object_unref(pl);
	cairo_restore(cr);
	cairo_new_path (cr);
}

static void create_text_surface(cairo_surface_t ** sf,
		const float w, const float h,
		const float x, const float y,
		const char * txt, PangoFontDescription *font, float *c_col) {
	assert(sf);

	if (*sf) {
		cairo_surface_destroy(*sf);
	}
	*sf = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, w, h);
	cairo_t *cr = cairo_create (*sf);
	cairo_set_source_rgba (cr, .0, .0, .0, 0);
	cairo_set_operator (cr, CAIRO_OPERATOR_SOURCE);
	cairo_rectangle (cr, 0, 0, w, h);
	cairo_fill (cr);
	cairo_set_operator (cr, CAIRO_OPERATOR_OVER);

	write_text_full(cr, txt, font, x, y, 0, 2, c_col);
	cairo_surface_flush(*sf);
	cairo_destroy (cr);
}

#endif
