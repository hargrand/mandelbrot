#ifndef MANDELBROT
#define MANDELBROT

#include <complex.h>

/// <summary>
/// Determines if the value is in the Mandelbrot set
/// </summary>
/// <param name="z">The complex value as the starting value for the Mandelbrot equation</param>
/// <param name="c">The constant in the Mandelbrot equation</param>
/// <param name="max_i">The maximum iterations when determining a 
/// valid Mandelbrot set value</param>
/// <returns>Number of iterations</returns>
extern unsigned int mandelbrot(struct complex z, struct complex c, unsigned int max_i);

#endif