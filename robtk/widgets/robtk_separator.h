/* separator line widget
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

#ifndef _ROB_TK_SEP_H_
#define _ROB_TK_SEP_H_

typedef struct {
	RobWidget *rw;
	bool horiz;
	float m_width, m_height;
	float w_width, w_height;
	float line_width;
} RobTkSep;

static bool robtk_sep_expose_event(RobWidget* handle, cairo_t* cr, cairo_rectangle_t* ev) {
	RobTkSep* d = (RobTkSep *)GET_HANDLE(handle);
	cairo_rectangle (cr, ev->x, ev->y, ev->width, ev->height);
	cairo_clip (cr);
	float c[4];
	get_color_from_theme(1, c);
	cairo_set_source_rgb (cr, c[0], c[1], c[2]);
	cairo_rectangle (cr, 0, 0, d->w_width, d->w_height);
	cairo_fill(cr);

	get_color_from_theme(0, c);
	cairo_set_source_rgba (cr, c[0], c[1], c[2], .7);

	if (d->line_width <=0 ) return TRUE;

	cairo_set_operator (cr, CAIRO_OPERATOR_OVER);
	cairo_set_line_width(cr, 1.0);
	if (d->horiz) {
		cairo_move_to (cr, 0.5, (d->w_height - 1.5) / 2);
		cairo_line_to (cr, d->w_width - 1.0 , (d->w_height - 1.5) / 2);
	} else {
		cairo_move_to (cr, (d->w_width - 1.5) / 2, 0.5);
		cairo_line_to (cr, (d->w_width - 1.5) / 2, d->w_height - 1.0);
	}
	cairo_stroke(cr);

	return TRUE;
}

/******************************************************************************
 * RobWidget stuff
 */

static void
priv_sep_size_request(RobWidget* handle, int *w, int *h) {
	RobTkSep* d = (RobTkSep*)GET_HANDLE(handle);
	*w = d->m_width;
	*h = d->m_height;
}


static void
priv_sep_size_allocate(RobWidget* handle, int w, int h) {
	RobTkSep* d = (RobTkSep*)GET_HANDLE(handle);
	d->w_width = w;
	d->w_height = h;
	robwidget_set_size(handle, d->w_width, d->w_height);
}


/******************************************************************************
 * public functions
 */

static RobTkSep * robtk_sep_new(bool horizontal) {
	RobTkSep *d = (RobTkSep *) malloc(sizeof(RobTkSep));
	d->horiz = horizontal;
	d->w_width = 4;
	d->w_height = 4;
	d->m_width = 4;
	d->m_height = 4;
	d->line_width = 1.0;

	d->rw = robwidget_new(d);
	if (horizontal) {
		ROBWIDGET_SETNAME(d->rw, "hsep");
	} else {
		ROBWIDGET_SETNAME(d->rw, "vsep");
	}
	robwidget_set_expose_event(d->rw, robtk_sep_expose_event);
	robwidget_set_size_request(d->rw, priv_sep_size_request);
	robwidget_set_size_allocate(d->rw, priv_sep_size_allocate);

	return d;
}

static void robtk_sep_destroy(RobTkSep *d) {
	robwidget_destroy(d->rw);
	free(d);
}

static void robtk_sep_set_alignment(RobTkSep *d, float x, float y) {
	robwidget_set_alignment(d->rw, x, y);
}

static void robtk_sep_set_linewidth(RobTkSep *d, float lw) {
	d->line_width = lw;
}

static RobWidget * robtk_sep_widget(RobTkSep *d) {
	return d->rw;
}
#endif
