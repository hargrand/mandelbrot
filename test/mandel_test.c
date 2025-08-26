#include "support.h"
#include "test_complex.h"

#include <stdbool.h>

int main()
{
	struct result_struct results = { 0, 0 };

	test_add(&results, true);
	test_sub(&results, true);
	test_mul(&results, true);
	test_div(&results, true);
	test_conj(&results, true);
	test_mag2(&results, true);
	test_mag(&results, true);
	test_arg(&results, true);
	test_from_polar(&results, true);
}