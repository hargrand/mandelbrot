#include "mandel.h"
#include "image.h"

#include <stdio.h>
#include <stdlib.h>

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
    image_config img_config;

    int err = init_image(&img_config,
                         filename,
                         image_width,
                         image_height,
                         image_bit_depth);
    if (err)
    {
        report(err);
        return err;
    }

    mandel_config mdl_config = {
        view_left,
        view_bottom,
        view_height,
        max_iters};

    create_image(&mdl_config, &img_config);
    write_png_file(&img_config);
    cleanup_image(&img_config);

    printf("Successfully created PNG file: %s\n", filename);

    return NO_ERROR;
}