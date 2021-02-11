#include <cairo.h>
#include <stdio.h>

int main()
{
    cairo_surface_t *surface =
        cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 80,80);
    cairo_t *cr =
        cairo_create (surface);


    cairo_push_group(cr);

    cairo_rectangle(cr,10, 10, 50, 50);
    cairo_set_source_rgba(cr,0, 0, 0, 0.8);
    cairo_set_line_width(cr, 8);
    cairo_fill(cr);

    cairo_set_operator(cr, CAIRO_OPERATOR_SATURATE);
    cairo_set_source_rgba(cr,1, 0, 0, 0.8);
    cairo_rectangle(cr,20, 20, 50, 50);
    cairo_fill(cr);

    cairo_pop_group_to_source(cr);
    cairo_paint(cr);
    // cairo_paint_with_alpha(cr, 0.5);

    // cairo_paint_with_alpha(cr, 0.5);


    cairo_surface_write_to_png(surface, "push_pop_noAlpha.png");

    // cairo_pattern_t * rgba_pattern = cairo_pattern_create_rgba(1.0, 0, 0, 0);

// cairo_pattern_create_radial();
// cairo_pattern_add_color_stop_rgb();
//     cairo_push_group(cr);
//     cairo_set_source(cr, fill_pattern);
//     cairo_fill_preserve(cr);
//     cairo_set_source(cr, stroke_pattern);
//     cairo_stroke(cr);
//     cairo_pop_group_to_source(cr);
//     cairo_paint_with_alpha(cr, alpha);
}