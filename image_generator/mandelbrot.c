#include "mandelbrot.h"

unsigned int mandelbrot(struct complex z, struct complex c, unsigned int max_i)
{
	unsigned int i = 0;
    while (i < max_i) {
        // Mandelbrot equation: z = z^2 + c
        double re2 = z.x * z.x - z.y * z.y;   // Real part of z^2
        double im2 = 2.0 * z.x * z.y;         // Imaginary part of z^2

        z.x = re2 + c.x;
        z.y = im2 + c.y;

        // Escape check: z^2 > 4 means it diverges
        if ((z.x * z.x + z.y * z.y) > 100.0) {
            break;
        }
        i++;
    }
    return i;
}
