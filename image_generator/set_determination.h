#ifndef SET_DETERMINATION_H
#define SET_DETERMINATION_H

#include <math.h>

/// <summary>
/// Determines if the value is in the Mandelbrot set
/// </summary>
/// <param name="z">The complex value in the Mandelbrot equation</param>
/// <param name="c">The constant in the Mandelbrot equation</param>
/// <param name="max_i">The maximum iterations when determining a 
/// valid Mandelbrot set value</param>
/// <returns>A determination if the complex value is determined to be
/// outside of the Mandelbrot set</returns>
extern struct complex determine(struct complex z, double c, double max_i);

#endif