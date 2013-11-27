/* robwidget - gtk2 & GL wrapper
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

#ifndef COMMON_CAIRO_H
#define COMMON_CAIRO_H

#include <string.h>
#include <cairo/cairo.h>
#include <pango/pango.h>

static PangoFontDescription * get_font_from_theme () {
  PangoFontDescription * rv;
	rv = pango_font_description_from_string("Sans 10");
	assert(rv);
	return rv;
}

static void get_color_from_theme (int which, float *col) {
	switch(which) {
		default: // fg
			col[0] = .9;
			col[1] = .9;
			col[2] = .9;
			col[3] = 1.0;
			break;
		case 1: // bg
			col[0] = 84/255.0;
			col[1] = 85/255.0;
			col[2] = 93/255.0;
			col[3] = 1.0;
			break;
		case 2: // fg alt
			col[0] = 0;
			col[1] = 0;
			col[2] = 0;
			col[3] = 1.0;
			break;
	}
}
#endif
