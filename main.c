#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image_generator/mandelbrot.h"

int main(int argc, char* argv[])
{
    // Default values
    double min_re = -2.0, max_re = 2.0;
    double min_im = -2.0, max_im = 2.0;
    unsigned int max_iters = 256;
    int img_w = 256, img_h = 256;
    const char* out_file = "mandelbrot.png";

    // If no args, just run default generator
    if (argc == 1) {
        printf("No arguments given. Using default Mandelbrot settings.\n");
        generate_mandelbrot_image_default(out_file);
        printf("Wrote to %s\n", out_file);
        return 0;
    }

    // Parse CLI args
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-region") == 0 && i + 4 < argc) {
            min_re = atof(argv[++i]);
            max_re = atof(argv[++i]);
            min_im = atof(argv[++i]);
            max_im = atof(argv[++i]);
        }
        else if (strcmp(argv[i], "-iters") == 0 && i + 1 < argc) {
            max_iters = (unsigned int)atoi(argv[++i]);
        }
        else if (strcmp(argv[i], "-res") == 0 && i + 2 < argc) {
            img_w = atoi(argv[++i]);
            img_h = atoi(argv[++i]);
        }
        else if (strcmp(argv[i], "-out") == 0 && i + 1 < argc) {
            out_file = argv[++i];
        }
        else if (strcmp(argv[i], "-help") == 0) {
            printf("Usage:\n");
            printf("  mandelbrot.exe [options]\n\n");
            printf("Options:\n");
            printf("  -region <minRe> <maxRe> <minIm> <maxIm>   Set complex plane region\n");
            printf("  -res <width> <height>                     Set image resolution\n");
            printf("  -iters <n>                                Set max iterations\n");
            printf("  -out <filename>                           Set output PNG filename\n");
            printf("  -help                                     Show this help message\n");
            return 0;
        }
        else {
            fprintf(stderr, "Unknown or incomplete argument: %s\n", argv[i]);
            return 1;
        }
    }

    // Run generator with user-specified settings
    printf("Generating Mandelbrot image...\n");
    printf("Region: Re[%.3f, %.3f], Im[%.3f, %.3f]\n", min_re, max_re, min_im, max_im);
    printf("Resolution: %dx%d\n", img_w, img_h);
    printf("Max Iterations: %u\n", max_iters);
    printf("Output: %s\n", out_file);

    generate_mandelbrot_image_custom(out_file, min_re, max_re, min_im, max_im, max_iters, img_w, img_h);

    printf("Wrote to %s\n", out_file);
    return 0;
}
