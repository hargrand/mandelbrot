#include <png.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "mandelbrot.h"
#include "complex_math.h"

// ---------- Mandelbrot core ----------

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
    const char* filename,
    int width,
    int height,
    void (*fill_row)(uint8_t* row, int y, int width, void* ctx),
    void* ctx)
{
    FILE* fp = fopen(filename, "wb");
    if (!fp) {
        fprintf(stderr, "Error: Could not open '%s' for writing.\n", filename);
        return;
    }

    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!png_ptr || !info_ptr) {
        fprintf(stderr, "Error: Could not allocate PNG structs.\n");
        fclose(fp);
        return;
    }

    if (setjmp(png_jmpbuf(png_ptr))) {
        fprintf(stderr, "Error: libpng encountered a problem.\n");
        png_destroy_write_struct(&png_ptr, &info_ptr);
        fclose(fp);
        return;
    }

    png_init_io(png_ptr, fp); // png_init_io tells libpng to write to the file
    png_set_IHDR(
        png_ptr, info_ptr,
        (png_uint_32)width, (png_uint_32)height,
        8,                  // bits per color channel
        PNG_COLOR_TYPE_RGB, // RGB color mode
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT, 
        PNG_FILTER_TYPE_DEFAULT);

    png_write_info(png_ptr, info_ptr); // PNG file now knows its basic parameters

    uint8_t* row = (uint8_t*)malloc((size_t)width * 3); // Temporary array that holds pixel values for one image row 
                                                        // before writing it out. Each pixel has 3 bytes (R, G, B).
    for (int y = 0; y < height; ++y) {
        (*fill_row)(row, y, width, ctx);
        png_write_row(png_ptr, row);
    }
    free(row);

    png_write_end(png_ptr, info_ptr);
    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(fp);
}

// ---------- Coloring ----------

// Converts the iteration count from the Mandelbrot formula into a shade of blue
static inline uint8_t blue_from_iters(unsigned int iters, unsigned int max_iters)
{
    if (iters >= max_iters) return 0;
    return (uint8_t)(255 - (255u * iters) / (max_iters - 1));
}


// ---------- Row filler ----------

struct fractal_cfg {
    double min_re, max_re;
    double min_im, max_im;
    unsigned int max_iters;
    int w, h;
};

// Row filler that computes Mandelbrot and writes RGB bytes
static void fill_row_mandelbrot(uint8_t* row, int y, int width, void* ctx)
{
    struct fractal_cfg* cfg = (struct fractal_cfg*)ctx;

    for (int x = 0; x < cfg->w; ++x) {
        double re = cfg->min_re + (cfg->max_re - cfg->min_re) * ((double)x / (cfg->w - 1));
        double im = cfg->max_im - (cfg->max_im - cfg->min_im) * ((double)y / (cfg->h - 1));
        struct complex c = { re, im };
        struct complex z0 = { 0.0, 0.0 };
        unsigned int it = mandelbrot(z0, c, cfg->max_iters);

        uint8_t shade = (uint8_t)(255 - (255u * it) / (cfg->max_iters - 1));
        row[3 * x + 0] = (shade * 5) % 256;  // R
        row[3 * x + 1] = (shade * 7) % 256;  // G
        row[3 * x + 2] = (shade * 11) % 256; // B

    }
}

// ---------- Custom generator ----------

int generate_mandelbrot_image_custom(
    const char* out_path,
    double min_re, double max_re,
    double min_im, double max_im,
    unsigned int max_iters,
    int img_w, int img_h)
{
    if (!out_path) out_path = "mandelbrot.png";

    struct fractal_cfg cfg = {
        .min_re = min_re, .max_re = max_re,
        .min_im = min_im, .max_im = max_im,
        .max_iters = max_iters,
        .w = img_w, .h = img_h
    };

    write_png_rgb8(out_path, img_w, img_h, fill_row_mandelbrot, &cfg);
    return 0;
}

// ---------- Parsing args ----------

int parse_mandelbrot_args(int argc, char* argv[], struct mandelbrot_config* cfg)
{
    // Set defaults
    cfg->min_re = -2.0;
    cfg->max_re = 2.0;
    cfg->min_im = -2.0;
    cfg->max_im = 2.0;
    cfg->max_iters = 256;
    cfg->img_w = 256;
    cfg->img_h = 256;
    cfg->out_file = "mandelbrot.png";

    // If no args are passed, main.c will run default generation
    if (argc == 1) {
        printf("No arguments given - using default Mandelbrot settings.\n");
    }

    // Parse CLI args
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-region") == 0 && i + 4 < argc) {
            cfg->min_re = atof(argv[++i]);
            cfg->max_re = atof(argv[++i]);
            cfg->min_im = atof(argv[++i]);
            cfg->max_im = atof(argv[++i]);
        }
        else if (strcmp(argv[i], "-iters") == 0 && i + 1 < argc) {
            cfg->max_iters = (unsigned int)atoi(argv[++i]);
        }
        else if (strcmp(argv[i], "-res") == 0 && i + 2 < argc) {
            cfg->img_w = atoi(argv[++i]);
            cfg->img_h = atoi(argv[++i]);
        }
        else if (strcmp(argv[i], "-out") == 0 && i + 1 < argc) {
            cfg->out_file = argv[++i];
        }
        else if (strcmp(argv[i], "-help") == 0) {
            printf("Usage:\n");
            printf("  mandelbrot.exe [options]\n\n");
            printf("Options:\n");
            printf("  -region <minRe> <maxRe> <minIm> <maxIm>\n");
            printf("  -res <width> <height>\n");
            printf("  -iters <n>\n");
            printf("  -out <filename>\n");
            printf("  -help\n");
            return 1;  // Signal "help printed"
        }
        else {
            fprintf(stderr, "Unknown argument: %s\n", argv[i]);
            printf("Use -help for usage information.\n");
            return -1;
        }
    }

    // Print full config summary
    printf("Generating Mandelbrot image...\n");
    printf("Region: Re[%.3f, %.3f], Im[%.3f, %.3f]\n",
        cfg->min_re, cfg->max_re, cfg->min_im, cfg->max_im);
    printf("Resolution: %dx%d\n", cfg->img_w, cfg->img_h);
    printf("Max Iterations: %u\n", cfg->max_iters);
    printf("Output: %s\n", cfg->out_file);

    return 0;
}


