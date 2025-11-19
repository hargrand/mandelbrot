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

/// <summary>
/// Generate the PNG with args
/// </summary>
/// <param name="out_path">The path where the mandelbrot png image will save to</param>
/// <param name="min_re">Minimum real value on the complex plane</param>
/// <param name="max_re">Maximum real value on the complex plane</param>
/// <param name="min_im">Minimum imaginary value on the complex plane</param>
/// <param name="max_im">Maximum imaginary value on the complex plane</param>
/// <param name="max_iters">The maximum iterations when determining a 
/// valid Mandelbrot set value</param>
/// <param name="img_w">PNG image size width by pixels</param>
/// <param name="img_w">PNG image size height by pixels</param>
/// <returns>N/A</returns>
int generate_mandelbrot_image_custom(
    const char* out_path,
    double min_re, double max_re,
    double min_im, double max_im,
    unsigned int max_iters,
    int img_w, int img_h
);

/// <summary>
/// Mandelbrot config variables for generating images
/// </summary>
/// <param name="out_file">The path where the mandelbrot png image will save to</param>
/// <param name="min_re">Minimum real value on the complex plane</param>
/// <param name="max_re">Maximum real value on the complex plane</param>
/// <param name="min_im">Minimum imaginary value on the complex plane</param>
/// <param name="max_im">Maximum imaginary value on the complex plane</param>
/// <param name="max_iters">The maximum iterations when determining a 
/// valid Mandelbrot set value</param>
/// <param name="img_w">PNG image size width by pixels</param>
/// <param name="img_w">PNG image size height by pixels</param>
struct mandelbrot_config {
    const char* out_file;
    double min_re, max_re;
    double min_im, max_im;
    unsigned int max_iters;
    int img_w, img_h;
};

/// <summary>
/// Parses args when running the mandelbrot program
/// </summary>
/// <param name="argc">Argument flags</param>
/// <param name="argv">Argumet values</param>
/// <param name="mandelbrot_config">Mandelbrot config with default values</param>
/// <returns>Result</returns>
int parse_mandelbrot_args(int argc, char* argv[], struct mandelbrot_config* cfg);

#endif