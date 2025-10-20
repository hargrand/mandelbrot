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

// ---------- PNG Helpers with cleanup ----------

// write_png_rgb8 handles all the fiole I/O and PNG encoding work with libpng.
// Essentially, this helper converts pixel rows into a .png file.

static void write_png_rgb8(
    const char* filename, // * is a memory address
    int width,
    int height,
    void (*fill_row)(uint8_t* row, int y, int width))
{
    FILE* fp = NULL;    // Opens output file in write binary (wb) mode
    png_structp png_ptr = NULL;
    png_infop info_ptr = NULL; // info_ptr stores metadata (width, height, etc.)
    uint8_t* row = NULL;

    fp = fopen(filename, "wb");
    if (!fp) {
        fprintf(stderr, "Error: Could not open '%s' for writing.\n", filename);
        goto cleanup;
    }

    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr) {
        fprintf(stderr, "Error: Could not allocate PNG write struct.\n");
        goto cleanup;
    }

    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        fprintf(stderr, "Error: Could not allocate PNG info struct.\n");
        goto cleanup;
    }

    if (setjmp(png_jmpbuf(png_ptr))) {
        fprintf(stderr, "Error: libpng encountered a problem during writing.\n");
        goto cleanup;
    }

    png_init_io(png_ptr, fp); // png_init_io tells libpng to write to the file
    png_set_IHDR(
        png_ptr, info_ptr,
        (png_uint_32)width, (png_uint_32)height,
        8,                      // bits per color channel
        PNG_COLOR_TYPE_RGB,     // RGB color mode
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT,
        PNG_FILTER_TYPE_DEFAULT);

    png_write_info(png_ptr, info_ptr);  // PNG file now knows its basic parameters

    row = (uint8_t*)malloc((size_t)width * 3); // Temporary array that holds pixel values for one image row 
                                               // before writing it out. Each pixel has 3 bytes (R, G, B).
    if (!row) {
        fprintf(stderr, "Error: Could not allocate row buffer.\n");
        goto cleanup;
    }

    for (int y = 0; y < height; ++y) {
        fill_row(row, y, width);
        png_write_row(png_ptr, row);
    }

    png_write_end(png_ptr, info_ptr);

cleanup:
    if (row) free(row);
    if (png_ptr && info_ptr)
        png_destroy_write_struct(&png_ptr, &info_ptr);
    else if (png_ptr)
        png_destroy_write_struct(&png_ptr, NULL);

    if (fp) fclose(fp);
}

// ---------- Image parameters ----------

enum { IMG_W = 2560, IMG_H = 2560 };      // Resolution, multiples of MAX_ITERS
static const double MIN_RE = -2.0, MAX_RE = 2.0;
static const double MIN_IM = -2.0, MAX_IM = 2.0;
static const unsigned int MAX_ITERS = 256;

// ---------- Complex mapping ----------

// Map pixel (x,y) -> complex c in the target region 
static struct complex pixel_to_complex(int x, int y)
{
    double re = MIN_RE + (MAX_RE - MIN_RE) * ((double)x / (IMG_W - 1));
    double im = MAX_IM - (MAX_IM - MIN_IM) * ((double)y / (IMG_H - 1)); // top to bottom
    struct complex c = { re, im };
    return c;
}

// ---------- Coloring ----------

// Converts the iteration count from the Mandelbrot formula into a shade of blue
static inline uint8_t blue_from_iters(unsigned int iters)
{
    if (iters >= MAX_ITERS) return 0; // in-set to black
    // Map 0..(MAX_ITERS-1) to 255..~0 (lighter → darker)
    return (uint8_t)(255 - (255u * iters) / (MAX_ITERS - 1));
}

// ---------- Row filler ----------

// Row filler that computes Mandelbrot and writes RGB bytes
static void fill_row_mandelbrot(uint8_t* row, int y, int width)
{
    (void)width; // fixed 256 in this program
    for (int x = 0; x < IMG_W; ++x) {
        struct complex c = pixel_to_complex(x, y);
        struct complex z0 = { 0.0, 0.0 };
        unsigned int it = mandelbrot(z0, c, MAX_ITERS);
        uint8_t b = blue_from_iters(it);

        // Simple rainbow banding
        uint8_t shade = (uint8_t)(255 - (255u * it) / (MAX_ITERS - 1));
        row[3 * x + 0] = (uint8_t)((shade * 5) % 256);  // R cycles
        row[3 * x + 1] = (uint8_t)((shade * 7) % 256);  // G cycles
        row[3 * x + 2] = (uint8_t)((shade * 11) % 256); // B cycles

        // // Simple black to blue gradient
        // row[3 * x + 0] = 0; // R
        // row[3 * x + 1] = 0; // G
        // row[3 * x + 2] = b; // B


    }
}

// ---------- Public entry point ----------

int generate_mandelbrot_image(const char* out_path) 
{
    if (!out_path) out_path = "../../renders/mandelbrot.png";
    write_png_rgb8(out_path, IMG_W, IMG_H, fill_row_mandelbrot);
    return 0;
}
