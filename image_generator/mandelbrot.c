#include "mandelbrot.h"
#include "complex.h"

static struct complex iterate(struct complex z, struct complex c)
{
    return complex_add(complex_mul(z, z), c);
}

unsigned int mandelbrot(struct complex z, struct complex c, unsigned int max_i)
{
	unsigned int i = 0;
    struct complex val = z;
    while (i < max_i && complex_mag2(val) < 4.0) {
        val = iterate(val, c);
        i++;
    }
    return i;
}
