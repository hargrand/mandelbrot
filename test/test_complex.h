#ifndef TEST_COMPLEX_H
#define TEST_COMPLEX_H

/// <summary>
/// Test the complex addition implementation and update the results struct to reflect the number of
/// passed and failed tests cases.
/// </summary>
/// <param name="results">Results struct to update after each test case</param>
/// <param name="verbose">When true display the results of all test cases;
/// when false only display thise test cases which fail.</param>
extern void test_add(struct result_struct* results, bool verbose);

#endif