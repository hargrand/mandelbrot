#include "support.h"
#include "test_complex.h"

#include <stdbool.h>

int main()
{
	struct result_struct results = { 0, 0 };
	test_add(&results, true);
}