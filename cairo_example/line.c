

#include <cairo.h>

int
main (int argc, char *argv[])
{
        cairo_surface_t *surface =
            cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 120, 30);
        cairo_t *cr =
            cairo_create (surface);

        cairo_set_source_rgb (cr, 1.0, 0.0, 0.0);

        cairo_move_to (cr, 10, 10);
        cairo_line_to (cr, 100, 10);
        cairo_set_line_width (cr, 1);
        cairo_stroke (cr);



        cairo_destroy (cr);
        cairo_surface_write_to_png (surface, "line.png");
        cairo_surface_destroy (surface);
        return 0;
}