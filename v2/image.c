#include "image.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

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
    case PNG_FILE_OPEN_FAIL_ERR:
        printf(PNG_FILE_OPEN_FAIL_MSG);
        break;
    case PNG_MAKE_ROWS_FAIL_ERR:
        printf(PNG_MAKE_ROWS_FAIL_MSG);
        break;
    case PNG_MAKE_ROW_FAIL_ERR:
        printf(PNG_MAKE_ROW_FAIL_MSG);
        break;
    case DATA_ROW_ALLOCATION_FAIL_ERR:
        printf(DATA_ROW_ALLOCATION_FAIL_MSG);
        break;
    default:
        printf("Unknown error %d", err);
        break;
    }
}

int png_init(image_config_ptr image)
{
    // Initialize the PNG write structures
    image->png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!(image->png_ptr))
        return PNG_ALLOC_WRITE_STRUCT_FAIL_ERR;

    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (!(image->info_ptr))
    {
        png_destroy_write_struct(&(image->png_ptr), NULL);
        return PNG_ALLOC_INFO_STRUCT_FAIL_ERR;
    }

    // Set up error handling
    if (setjmp(png_jmpbuf(image->png_ptr)))
    {
        png_destroy_write_struct(&(image->png_ptr), &(image->info_ptr));
        return PNG_ERROR_HANDLING_FAIL_ERR;
    }

    return NO_ERROR;
}

int config_png_file(image_config_ptr image,
                    const char *filename)
{
    // Open the file for writing in binary mode
    image->file_ptr = fopen(filename, "wb");
    if (!(image->file_ptr))
        return PNG_FILE_OPEN_FAIL_ERR;

    // Initialize the PNG boilerplate
    int err = png_init(image);
    if (err)
    {
        fclose(image->file_ptr);
        return err;
    }

    // Set up the output control
    png_init_io(image->png_ptr, image->file_ptr);

    return NO_ERROR;
}

int make_rows(image_config_ptr image)
{
    // Set the PNG header information
    png_set_IHDR(image->png_ptr, image->info_ptr, image->width,
                 image->height, image->bit_depth,
                 PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

    // Write the header to the file
    png_write_info(image->png_ptr, image->info_ptr);

    // Allocate memory for the row pointers
    (image->rows_ptr) = (png_bytep *)malloc(sizeof(png_bytep) * image->height);
    if (!(image->rows_ptr))
        return PNG_MAKE_ROWS_FAIL_ERR;

    // Allocate memory for the image data and fill it
    for (unsigned int y = 0; y < image->height; y++)
    {
        image->rows_ptr[y] = (png_bytep)malloc(png_get_rowbytes(image->png_ptr, image->info_ptr));
        if (!image->rows_ptr[y])
        {
            for (unsigned int i = 0; i < y; i++)
                free(image->rows_ptr[i]);
            free(image->rows_ptr);
            image->rows_ptr = NULL;
            return PNG_MAKE_ROW_FAIL_ERR;
        }
    }

    return NO_ERROR;
}

int init_image(image_config_ptr image,
               const char *filename,
               unsigned int width,
               unsigned int height,
               int bit_depth)
{
    image->width = width;
    image->height = height;
    image->bit_depth = bit_depth;

    int err = png_init(image);
    if (err)
        return err;

    err = config_png_file(image, filename);
    if (err)
        return err;

    err = make_rows(image);
    if (err)
        return err;

    return NO_ERROR;
}

// Function to write image data to a PNG file
void write_png_file(image_config_ptr image)
{
    // Write the image data to the file
    png_write_image(image->png_ptr, image->rows_ptr);

    // End the write process
    png_write_end(image->png_ptr, NULL);
}

void cleanup_image(image_config_ptr image)
{
    // Close the file

    fclose(image->file_ptr);

    // --- Cleanup ---
    for (unsigned int y = 0; y < image->height; y++)
        free(image->rows_ptr[y]);
    free(image->rows_ptr);

    png_destroy_write_struct(&(image->png_ptr), &(image->info_ptr));
}
