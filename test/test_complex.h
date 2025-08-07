#ifndef TEST_COMPLEX_H
#define TEST_COMPLEX_H

/// <summary>
/// Test the complex addition implementation and update the results struct to reflect the number of
/// passed and failed tests cases.
/// </summary>
/// <param name="results">Results struct to update after each test case</param>
/// <param name="verbose">When true display the results of all test cases;
/// when false only display this test cases which fail.</param>
extern void test_add(struct result_struct* results, bool verbose);

/// <summary>
/// Test the complex subtraction implementation and update the results struct to reflect the number of
/// passed and failed tests cases.
/// </summary>
/// <param name="results">Results struct to update after each test case</param>
/// <param name="verbose">When true display the results of all test cases;
/// when false only display this test cases which fail.</param>
extern void test_sub(struct result_struct* results, bool verbose);

/// <summary>
/// Test the complex multiplication implementation and update the results struct to reflect the number of
/// passed and failed tests cases.
/// </summary>
/// <param name="results">Results struct to update after each test case</param>
/// <param name="verbose">When true display the results of all test cases;
/// when false only display this test cases which fail.</param>
extern void test_mul(struct result_struct* results, bool verbose);

/// <summary>
/// Test the complex division implementation and update the results struct to reflect the number of
/// passed and failed tests cases.
/// </summary>
/// <param name="results">Results struct to update after each test case</param>
/// <param name="verbose">When true display the results of all test cases;
/// when false only display this test cases which fail.</param>
extern void test_div(struct result_struct* results, bool verbose);

#endif