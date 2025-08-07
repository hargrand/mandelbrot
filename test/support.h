
#ifndef TEST_SUPPORT_H
#define TEST_SUPPORT_H

#include "../math/complex.h"

#include <stdbool.h>

#define PASS "\x1B[32mPASS\x1B[0m"
#define FAIL "\x1B[31mFAIL\x1B[0m"

/// <summary>
/// Stucture containing a summary of the results of a series of tests
/// </summary>
struct result_struct
{
	/// <summary>
	/// Number of tests that pass during the run of the tests
	/// </summary>
	int pass;

	/// <summary>
	/// Number of tests that fail during the run of the tests
	/// </summary>
	int fail;
};

/// <summary>
/// Given an outcome, where true is a pass and false is a fail, update the results
/// struct
/// </summary>
/// <param name="results">Results struct to update</param>
/// <param name="outcome">Outcome to use in determining how to update the results struct</param>
extern void update_results(struct result_struct* results, bool outcome);

/// <summary>
/// Compare a complex value with its expected results and return true if and only if the two
/// values are the same.
/// </summary>
/// <param name="actual">Value to compare against the expected value</param>
/// <param name="expected">Value that actual is expected to hold</param>
/// <returns>True exactly when the actual value is as expected</returns>
extern bool evaluate(struct complex actual, struct complex expected);

#endif