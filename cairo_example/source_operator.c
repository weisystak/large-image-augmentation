#include <cairo.h>


int main()
{
    cairo_surface_t *surface =
        cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 80,80);
    cairo_t *cr =
        cairo_create (surface);
    
    
    cairo_rectangle(cr,10, 10, 50, 50);
    cairo_set_source_rgba(cr,0, 0, 0, 0.8);
    cairo_set_line_width(cr, 8);
    cairo_fill(cr);

    cairo_set_operator(cr, CAIRO_OPERATOR_SATURATE);
    cairo_set_source_rgba(cr,1, 0, 0, 0.8);
    cairo_rectangle(cr,20, 20, 50, 50);
    cairo_fill(cr);

    cairo_surface_write_to_png (surface, "source_operator.png");

}
