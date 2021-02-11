#include <cairo.h>
#include <stdio.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


int main()
{

    cairo_surface_t *surface =
        cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 500, 260);
    cairo_t *cr =
        cairo_create (surface);

    cairo_set_source_rgb(cr, 0.6, 0.6, 0.6);
    cairo_set_line_width(cr, 1);

    cairo_rectangle(cr, 20, 20, 120, 80);
    cairo_rectangle(cr, 180, 20, 80, 80);

    // cairo_pattern_t *old_pattern = cairo_get_source(cr);
    // cairo_pattern_type_t t = cairo_pattern_get_type(old_pattern);
    // printf("pattern type: %d\n", t);

    cairo_stroke_preserve(cr);  // 畫出來，保留位置。
    cairo_fill(cr);  // 塗滿顏色

    cairo_arc(cr, 330, 60, 40, 0, 2*M_PI);
    cairo_stroke_preserve(cr);
    cairo_fill(cr);

    cairo_arc(cr, 90, 160, 40, M_PI/4, M_PI);
    cairo_close_path(cr);
    cairo_stroke_preserve(cr);
    cairo_fill(cr);

    cairo_set_source_rgb(cr, 1.0, 0, 0);
    cairo_translate(cr, 220, 180);
    cairo_scale(cr, 1, 0.7);
    cairo_arc(cr, 0, 0, 50, 0, 2*M_PI);
    cairo_stroke_preserve(cr);
    cairo_fill(cr);


    cairo_destroy (cr);
    cairo_surface_write_to_png (surface, "draw.png");
    cairo_surface_destroy (surface);
}