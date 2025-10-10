#include <png.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "mandelbrot.h"
#include "complex_math.h"

static struct complex iterate(struct complex z, struct complex c)
{
    return complex_add(complex_mul(z, z), c);
}

unsigned int mandelbrot(struct complex z, struct complex c, unsigned int max_i)
{
	unsigned int i = 0;
    struct complex val = z;
    while (i < max_i && complex_mag2(val) < 4.0) {
        val = iterate(val, c);
        i++;
    }
    return i;
}

// PNG Helpers
static void write_png_rgb8(
    const char* filename,
    int width,
    int height,
    void (*fill_row)(uint8_t* row, int y, int width))
{
    FILE* fp = fopen(filename, "wb");

    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info_ptr = png_create_info_struct(png_ptr);
    png_init_io(png_ptr, fp);
    png_set_IHDR(
        png_ptr, info_ptr,
        (png_uint_32)width, (png_uint_32)height,
        8,                      // bit depth
        PNG_COLOR_TYPE_RGB,     // RGB8
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT,
        PNG_FILTER_TYPE_DEFAULT);

    png_write_info(png_ptr, info_ptr);

    uint8_t* row = (uint8_t*)malloc((size_t)width * 3);

    for (int y = 0; y < height; ++y) {
        fill_row(row, y, width);
        png_write_row(png_ptr, row);
    }

    free(row);
    png_write_end(png_ptr, info_ptr);
    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(fp);
}

// Image parameters & coloring
enum { IMG_W = 256, IMG_H = 256 };
static const double MIN_RE = -2.0, MAX_RE = 2.0;
static const double MIN_IM = -2.0, MAX_IM = 2.0;
static const unsigned int MAX_ITERS = 256;

// Map pixel (x,y) -> complex c in the target region 
static struct complex pixel_to_complex(int x, int y)
{
    double re = MIN_RE + (MAX_RE - MIN_RE) * ((double)x / (IMG_W - 1));
    double im = MAX_IM - (MAX_IM - MIN_IM) * ((double)y / (IMG_H - 1)); // top to bottom
    struct complex c = { re, im };
    return c;
}

// Blue→Black ramp: exterior lighter, interior black
static inline uint8_t blue_from_iters(unsigned int iters)
{
    if (iters >= MAX_ITERS) return 0; // in-set to black
    // Map 0..(MAX_ITERS-1) to 255..~0 (lighter → darker)
    return (uint8_t)(255 - (255u * iters) / (MAX_ITERS - 1));
}

// Row filler that computes Mandelbrot and writes RGB bytes
static void fill_row_mandelbrot(uint8_t* row, int y, int width)
{
    (void)width; // fixed 256 in this program
    for (int x = 0; x < IMG_W; ++x) {
        struct complex c = pixel_to_complex(x, y);
        struct complex z0 = { 0.0, 0.0 };
        unsigned int it = mandelbrot(z0, c, MAX_ITERS);
        uint8_t b = blue_from_iters(it);

        // RGB: shades of blue
        row[3 * x + 0] = 0; // R
        row[3 * x + 1] = 0; // G
        row[3 * x + 2] = b; // B
    }
}

int generate_mandelbrot_image(const char* out_path) 
{
    if (!out_path) out_path = "mandelbrot.png";
    write_png_rgb8(out_path, IMG_W, IMG_H, fill_row_mandelbrot);
    return 0;
}

