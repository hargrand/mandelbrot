#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <png.h>

#define NO_ERROR 0

#define PNG_ALLOC_WRITE_STRUCT_FAIL_ERR -1
#define PNG_ALLOC_WRITE_STRUCT_FAIL_MSG "Could not allocate PNG write struct"

#define PNG_ALLOC_INFO_STRUCT_FAIL_ERR -2
#define PNG_ALLOC_INFO_STRUCT_FAIL_MSG "Could not allocate PNG info struct"

#define PNG_ERROR_HANDLING_FAIL_ERR -3
#define PNG_ERROR_HANDLING_FAIL_MSG "An error occurred during PNG creation"

#define FILE_OPEN_FAIL_ERR -4
#define FILE_OPEN_FAIL_MSG "Could not open file for writing"

#define PNG_MAKE_ROWS_FAIL_ERR -5
#define PNG_MAKE_ROWS_FAIL_MSG "Could not allocate memory for row pointers"

#define PNG_MAKE_ROW_FAIL_ERR -6
#define PNG_MAKE_ROW_FAIL_MSG "Could not allocate memory for row"

#define DATA_ALLOCATION_FAIL_ERR -7
#define DATA_ALLOCATION_FAIL_MSG "Could not allocate memory for image data"

#define DATA_ROW_ALLOCATION_FAIL_ERR -8
#define DATA_ROW_ALLOCATION_FAIL_MSG "Could not allocate memory for row in image data"

typedef struct
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} color_t;

void report(int err)
{
    switch (err)
    {
    case PNG_ALLOC_WRITE_STRUCT_FAIL_ERR:
        printf(PNG_ALLOC_WRITE_STRUCT_FAIL_MSG);
        break;
    case PNG_ALLOC_INFO_STRUCT_FAIL_ERR:
        printf(PNG_ALLOC_INFO_STRUCT_FAIL_MSG);
        break;
    case PNG_ERROR_HANDLING_FAIL_ERR:
        printf(PNG_ERROR_HANDLING_FAIL_MSG);
        break;
    case FILE_OPEN_FAIL_ERR:
        printf(FILE_OPEN_FAIL_MSG);
        break;
    case PNG_MAKE_ROWS_FAIL_ERR:
        printf(PNG_MAKE_ROWS_FAIL_MSG);
        break;
    case PNG_MAKE_ROW_FAIL_ERR:
        printf(PNG_MAKE_ROW_FAIL_MSG);
        break;
    case DATA_ALLOCATION_FAIL_ERR:
        printf(DATA_ALLOCATION_FAIL_MSG);
        break;
    case DATA_ROW_ALLOCATION_FAIL_ERR:
        printf(DATA_ROW_ALLOCATION_FAIL_MSG);
        break;
    default:
        printf("Unknown error %d", err);
        break;
    }
}

unsigned int mandel(double x0, double y0, unsigned int max_iters)
{
    double x = 0.0;
    double y = 0.0;
    unsigned int i = 0;
    double xtemp;

    while (i < max_iters && (x * x + y * y) < 4.0)
    {
        xtemp = x * x - y * y + x0;
        y = 2 * x * y + y0;
        x = xtemp;
        ++i;
    }
    return i;
}

void gen_color(unsigned int val, color_t *color, unsigned int max_iters)
{
    if (val == max_iters)
    {
        color->red = 0;
        color->green = 0;
        color->blue = 0;
    }
    else
    {
        color->red = val & 0xff;
        color->green = (val >> 8) & 0xff;
        color->blue = (val >> 16) & 0xff;
    }
}

int png_init(png_structp *png_ptr,
             png_infop *info_ptr)
{

    // Initialize the PNG write structures
    *png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!(*png_ptr))
        return PNG_ALLOC_WRITE_STRUCT_FAIL_ERR;

    *info_ptr = png_create_info_struct(*png_ptr);
    if (!(*info_ptr))
    {
        png_destroy_write_struct(png_ptr, NULL);
        return PNG_ALLOC_INFO_STRUCT_FAIL_ERR;
    }

    // Set up error handling
    if (setjmp(png_jmpbuf(*png_ptr)))
    {
        png_destroy_write_struct(png_ptr, info_ptr);
        return PNG_ERROR_HANDLING_FAIL_ERR;
    }

    return NO_ERROR;
}

int config_png_file(FILE **fp,
                    png_structp *png_ptr,
                    png_infop *info_ptr,
                    const char *filename)
{
    // Open the file for writing in binary mode
    *fp = fopen(filename, "wb");
    if (!(*fp))
        return FILE_OPEN_FAIL_ERR;

    // Initialize the PNG boilerplate
    int err = png_init(png_ptr, info_ptr);
    if (err)
    {
        fclose(*fp);
        return err;
    }

    // Set up the output control
    png_init_io(*png_ptr, *fp);

    return NO_ERROR;
}

int make_rows(png_structp png_ptr,
              png_infop info_ptr,
              png_bytep **row_pointers,
              unsigned int image_width,
              unsigned int image_height,
              int image_bit_depth)
{
    // Set the PNG header information
    png_set_IHDR(png_ptr, info_ptr, image_width, image_height, image_bit_depth,
                 PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

    // Write the header to the file
    png_write_info(png_ptr, info_ptr);

    // Allocate memory for the row pointers
    (*row_pointers) = (png_bytep *)malloc(sizeof(png_bytep) * image_height);
    if (!(*row_pointers))
        return PNG_MAKE_ROWS_FAIL_ERR;

    // Allocate memory for the image data and fill it
    for (unsigned int y = 0; y < image_height; y++)
    {
        (*row_pointers)[y] = (png_byte *)malloc(png_get_rowbytes(png_ptr, info_ptr));
        if (!((*row_pointers)[y]))
        {
            for (unsigned int i = 0; i < y; i++)
                free((*row_pointers)[i]);
            free(*row_pointers);
            (*row_pointers) = NULL;
            return PNG_MAKE_ROW_FAIL_ERR;
        }
    }

    return NO_ERROR;
}

void create_image(double view_left,
                  double view_bottom,
                  double view_height,
                  unsigned int image_width,
                  unsigned int image_height,
                  unsigned int max_iters,
                  png_bytep *row_pointers)
{
    color_t color;
    double scale = view_height / image_height;
    double view_top = view_bottom + view_height;

    for (unsigned int row = 0; row < image_height; row++)
    {
        png_bytep image_row = row_pointers[row];
        double y = view_top - row * scale;
        for (unsigned int col = 0; col < image_width; col++)
        {
            double x = view_left + col * scale;
            unsigned int iters = mandel(x, y, max_iters);
            png_bytep px = &(image_row[col * 3]);
            gen_color(iters, &color, max_iters);
            px[0] = color.red;
            px[1] = color.green;
            px[2] = color.blue;
        }
    }
}

// Function to write image data to a PNG file
int write_png_file(double view_left,
                   double view_bottom,
                   double view_height,
                   unsigned int max_iters,
                   unsigned int image_width,
                   unsigned int image_height,
                   int image_bit_depth,
                   const char *filename)
{
    FILE *fp = NULL;
    png_structp png_ptr = NULL;
    png_infop info_ptr = NULL;
    png_bytep *row_pointers = NULL;

    int err = config_png_file(&fp, &png_ptr, &info_ptr, filename);
    if (err)
        return err;

    err = make_rows(png_ptr, info_ptr, &row_pointers,
                    image_width, image_height, image_bit_depth);
    if (err)
    {
        fclose(fp);
        png_destroy_write_struct(&png_ptr, &info_ptr);
        return err;
    }

    create_image(view_left, view_bottom, view_height,
                 image_width, image_height, max_iters,
                 row_pointers);

    // Write the image data to the file
    png_write_image(png_ptr, row_pointers);

    // End the write process
    png_write_end(png_ptr, NULL);

    // --- Cleanup ---
    for (unsigned int y = 0; y < image_height; y++)
        free(row_pointers[y]);
    free(row_pointers);

    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(fp);

    return NO_ERROR;
}

int main(int argc, char *argv[])
{
    if (argc != 8)
    {
        fprintf(stderr, "Usage: %s <filename> <width> <height> <max_iters> <view_left> <view_bottom> <view_height>\n", argv[0]);
        fprintf(stderr, "Example: %s mandelbrot.png 1024 1024 4096 -2.0 -2.0 4.0\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    unsigned int image_width = strtoul(argv[2], NULL, 10);
    unsigned int image_height = strtoul(argv[3], NULL, 10);
    unsigned int max_iters = strtoul(argv[4], NULL, 10);
    double view_left = strtod(argv[5], NULL);
    double view_bottom = strtod(argv[6], NULL);
    double view_height = strtod(argv[7], NULL);

    int image_bit_depth = 8;

    int err = write_png_file(
        view_left,
        view_bottom,
        view_height,
        max_iters,
        image_width,
        image_height,
        image_bit_depth,
        filename);
    if (err)
    {
        report(err);
        return err;
    }

    printf("Successfully created PNG file: %s\n", filename);

    return NO_ERROR;
}