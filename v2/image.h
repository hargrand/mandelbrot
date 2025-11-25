#include <png.h>

#ifndef IMAGE_H
#define IMAGE_H

#define NO_ERROR 0

#define PNG_ALLOC_WRITE_STRUCT_FAIL_ERR -1
#define PNG_ALLOC_WRITE_STRUCT_FAIL_MSG "Could not allocate PNG write struct"

#define PNG_ALLOC_INFO_STRUCT_FAIL_ERR -2
#define PNG_ALLOC_INFO_STRUCT_FAIL_MSG "Could not allocate PNG info struct"

#define PNG_ERROR_HANDLING_FAIL_ERR -3
#define PNG_ERROR_HANDLING_FAIL_MSG "An error occurred during PNG creation"

#define PNG_FILE_OPEN_FAIL_ERR -4
#define PNG_FILE_OPEN_FAIL_MSG "Could not open file for writing"

#define PNG_MAKE_ROWS_FAIL_ERR -5
#define PNG_MAKE_ROWS_FAIL_MSG "Could not allocate memory for row pointers"

#define PNG_MAKE_ROW_FAIL_ERR -6
#define PNG_MAKE_ROW_FAIL_MSG "Could not allocate memory for row"

#define DATA_ROW_ALLOCATION_FAIL_ERR -7
#define DATA_ROW_ALLOCATION_FAIL_MSG "Could not allocate memory for row in image data"

typedef struct
{
    png_structp png_ptr;
    png_infop info_ptr;
    png_bytep *rows_ptr;
    FILE *file_ptr;
    unsigned int width;
    unsigned int height;
    int bit_depth;
} image_config;

typedef image_config *image_config_ptr;

extern void report(int err);
extern int init_image(image_config_ptr image,
                      const char *filename,
                      unsigned int image_width,
                      unsigned int image_height,
                      int image_bit_depth);
extern void write_png_file(image_config_ptr image);
extern void cleanup_image(image_config_ptr image);

#endif
