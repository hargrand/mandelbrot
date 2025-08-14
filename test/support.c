#include "support.h"

void update_results(struct result_struct* results, bool outcome)
{
	if (outcome)
	{
		results->pass += 1;
	}
	else
	{
		results->fail += 1;
	}
}

bool evaluate_complex(struct complex actual, struct complex expected)
{
	return actual.re == expected.re && actual.im == expected.im;
}

bool evaluate_double(double actual, double expected)
{
	return actual == expected;
}
