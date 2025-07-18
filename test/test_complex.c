#include "../math/complex.h"
#include "support.h"

#include <stdbool.h>
#include <stdio.h>

void test_add(struct result_struct* results, bool verbose)
{
	double re_values[5] = { 0.0, 0.0, 1.0, 3.14, -2.71 };
	double im_values[5] = { 0.0, 1.0, 0.0, -2.71, 3.14 };

	for (int x_index = 0; x_index < 5; ++x_index)
	{
		double x_re = re_values[x_index];
		double x_im = im_values[x_index];
		struct complex x = { x_re, x_im };
		for (int y_index = 0; y_index < 4; ++y_index)
		{
			double y_re = re_values[y_index];
			double y_im = im_values[y_index];
			struct complex y = { y_re, y_im };

			struct complex act = add(x, y);
			struct complex exp = { x_re + y_re, x_im + y_im };

			bool outcome = evalutate(act, exp);
			update_results(results, outcome);
			if (verbose || !outcome)
			{
				printf("(%lf, %lf) + (%lf, %lf) != (%lf, %lf): %s\n", x_re, x_im, y_re, y_im, act.re, act.im, outcome ? PASS : FAIL);
			}
		}
	}
}
