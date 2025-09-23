#include "../image_generator/mandelbrot.h"
#include "support.h"
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#define SAMPLE_COUNT 5

struct complex values[SAMPLE_COUNT] =
{
	{ 0.0,   0.0},
	{ 1.0,   1.0},
	{ 3.14, -2.71},
	{-2.71,  0.0},
	{ 0.0,   3.14}
};

void test_mandelbrot(struct result_struct* results, bool verbose)
{
	struct result_struct {
		unsigned int iterations[4]; // store results for some test points
		unsigned int num_tests;
	};

	struct complex test_points[] = {
		{0.0, 0.0},
		{2.0, 2.0},
		{-0.75, 0.25},
		{0.3, 0.5}         
	};

	unsigned int max_i = 1000;

	for (unsigned int i = 0; i < 4; i++) {

		struct complex z = { 0.0, 0.0 };
		int iters = mandelbrot(z, test_points[i], max_i);

	}

}
