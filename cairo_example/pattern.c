#include <cairo.h>
#include <stdio.h>

int main()
{
    cairo_surface_t *surface =
        cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 80,80);
    cairo_t *cr =
        cairo_create (surface);

    // The default source pattern is a solid pattern that is opaque black, 
    // (that is, it is equivalent to cairo_set_source_rgb(cr, 0.0, 0.0, 0.0)).

    cairo_pattern_t *old_pattern = cairo_get_source(cr);
    cairo_pattern_type_t t = cairo_pattern_get_type(old_pattern);
    printf("pattern type: %d\n", t);
    
    unsigned int ref_cnt = cairo_pattern_get_reference_count(old_pattern);
    printf("ref_cnt: %d\n", ref_cnt);
    
    cairo_pattern_reference(old_pattern);  // increace by 1
    cairo_pattern_destroy(old_pattern);    // decrease by 1

    ref_cnt = cairo_pattern_get_reference_count(old_pattern);
    printf("ref_cnt: %d\n", ref_cnt);
}