#include "../image_generator/mandelbrot.h"
#include "support.h"
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

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

	int expected_iters[] = {
		max_i,
		1,
		13,
		max_i
	};

	for (unsigned int i = 0; i < 4; i++) {

		struct complex z = { 0.0, 0.0 };
		int iters = mandelbrot(z, test_points[i], max_i);

		bool outcome = iters == expected_iters[i];

		update_results(results, outcome);
		if (verbose || !outcome)
		{
			printf("expected iters: %d; actual iters: %d - %s \n",
				expected_iters[i],
				iters,
				outcome ? PASS : FAIL);
		}

	}

}
