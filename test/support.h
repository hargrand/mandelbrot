
#ifndef TEST_SUPPORT_H
#define TEST_SUPPORT_H

#include "../math/complex.h"

#include <stdbool.h>

#define PASS "\x1B[32mPASS\x1B[0m"
#define FAIL "\x1B[31mFAIL\x1B[0m"

struct result_struct
{
	int pass;
	int fail;
};

extern void update_results(struct result_struct* results, bool outcome);
extern bool evalutate(struct complex actual, struct complex expected);

#endif