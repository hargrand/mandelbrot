#include <stdio.h>
#include <stdlib.h>
#include "image_generator/mandelbrot.h"

int main(void)
{
    printf("Generating Mandelbrot image...\n");
    if (generate_mandelbrot_image("mandelbrot.png") != 0) {
        fprintf(stderr, "Error: Mandelbrot generation failed.\n");
        return 1;
    }
    printf("Done! Wrote mandelbrot.png\n");
    return 0;
}