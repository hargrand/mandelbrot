#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image_generator/mandelbrot.h"

int main(int argc, char* argv[])
{
    struct mandelbrot_config cfg;
    int result = parse_mandelbrot_args(argc, argv, &cfg);

    // If parse function has the -help flag called
    if (result == 1) {
        return 0;
    }

    // If parse function returns an error
    if (result < 0) {
        return 1;
    }

    generate_mandelbrot_image_custom(
        cfg.out_file,
        cfg.min_re, cfg.max_re,
        cfg.min_im, cfg.max_im,
        cfg.max_iters,
        cfg.img_w, cfg.img_h
    );

    printf("Wrote to %s\n", cfg.out_file);
    return 0;
}
