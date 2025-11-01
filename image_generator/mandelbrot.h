#ifndef MANDELBROT_H
#define MANDELBROT_H

#include "complex_math.h"

/// <summary>
/// Determines if the value is in the Mandelbrot set
/// </summary>
/// <param name="z">The complex value as the starting value for the Mandelbrot equation</param>
/// <param name="c">The constant in the Mandelbrot equation</param>
/// <param name="max_i">The maximum iterations when determining a 
/// valid Mandelbrot set value</param>
/// <returns>Number of iterations</returns>
extern unsigned int mandelbrot(struct complex z, struct complex c, unsigned int max_i);

// Generate the PNG; returns 0 on success
int generate_mandelbrot_image_default(const char* out_path);

// Generate the PNG with args
int generate_mandelbrot_image_custom(
    const char* out_path,
    double min_re, double max_re,
    double min_im, double max_im,
    unsigned int max_iters,
    int img_w, int img_h
);

#endif