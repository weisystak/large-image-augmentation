#include <cairo.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <jpeglib.h>

unsigned char * read_jpg(char * filename, int* width, int* height)
{
	int rc, i, j;


    // Variables for the source jpg
	struct stat file_info;
	unsigned long jpg_size;
	unsigned char *jpg_buffer;

	// Variables for the decompressor itself
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;

	// Variables for the output buffer, and how long each row is
	unsigned long bmp_size;
	unsigned char *bmp_buffer;
	int row_stride, pixel_size;

	rc = stat(filename, &file_info);

    jpg_size = file_info.st_size;
	jpg_buffer = (unsigned char*) malloc(jpg_size + 100);

    int fd = open(filename, O_RDONLY);
	i = 0;
	while (i < jpg_size) {
		rc = read(fd, jpg_buffer + i, jpg_size - i);
		i += rc;
	}
	close(fd);


    cinfo.err = jpeg_std_error(&jerr);	
	jpeg_create_decompress(&cinfo);
	jpeg_mem_src(&cinfo, jpg_buffer, jpg_size);
	rc = jpeg_read_header(&cinfo, TRUE);

	cinfo.out_color_space = JCS_EXT_BGRX;

	jpeg_start_decompress(&cinfo);
	printf("jpeg color space: %d\n", cinfo.jpeg_color_space);
	printf("output color space %d \n", cinfo.out_color_space);

    *width = cinfo.output_width;
	*height = cinfo.output_height;
	pixel_size = cinfo.output_components;

    printf("Proc: Image is %d by %d with %d components\n", 
			*width, *height, pixel_size);

    bmp_size = *width * *height * pixel_size;
	bmp_buffer = (unsigned char*) malloc(bmp_size);

	// The row_stride is the total number of bytes it takes to store an
	// entire scanline (row). 
	row_stride = *width * pixel_size;

    while (cinfo.output_scanline < cinfo.output_height) {
		unsigned char *buffer_array[1];
		buffer_array[0] = bmp_buffer + \
						   (cinfo.output_scanline) * row_stride;

		jpeg_read_scanlines(&cinfo, buffer_array, 1);
		// printf("scanlines: %d\n", cinfo.output_scanline);

	}

    jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	free(jpg_buffer);

    return bmp_buffer;
}

int main()
{

    cairo_surface_t *surface =
        cairo_image_surface_create (CAIRO_FORMAT_RGB24, 380,380);
    cairo_t *cr = cairo_create(surface);
	

	// saturate those seams away!
	// cairo_set_operator(cr, CAIRO_OPERATOR_SATURATE);

    // cairo_t *cr =
    //     cairo_create (surface);

    // cairo_set_source_rgba (cr, 1.0, 0.0, 0.0, 0.5);
    // cairo_paint(cr);

    // cairo_translate (cr, 20, 20);
    // cairo_set_source_rgba (cr, 0.0, 1.0, 0.0, 0.5);
    // cairo_paint(cr);


    // cairo_surface_write_to_png (surface, "paint.png");

    int w, h;
    unsigned char * img = read_jpg("tree.jpg", &w, &h);

	int stride = cairo_format_stride_for_width (CAIRO_FORMAT_RGB24, w);
	cairo_surface_t *src = cairo_image_surface_create_for_data(
                img,
                CAIRO_FORMAT_RGB24, w, h, stride);
	
	printf("stride: %d\n", stride);
	cairo_status_t stat = cairo_surface_status(src);
	printf("%d\n", stat);
	printf("w: %d h: %d\n", w, h);
	printf("%d, %d, %d, %d\n", img[0], img[1], img[2], img[3]);

    cairo_translate (cr, 20, 20);
	cairo_set_source_surface(cr, src, 0, 0);
    cairo_paint(cr);
    cairo_surface_write_to_png (surface, "paint.png");
	
}