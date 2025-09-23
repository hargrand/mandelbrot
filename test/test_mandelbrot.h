#ifndef TEST_MANDELBROT_H
#define TEST_MANDELBROT_H

/// <summary>
/// Test the mandelbrot equation implementation and update the results struct to reflect the number of
/// passed and failed tests cases.
/// </summary>
/// <param name="results">Results struct to update after each test case</param>
/// <param name="verbose">When true display the results of all test cases;
/// when false only display this test cases which fail.</param>
extern void test_mandelbrot(struct result_struct* results, bool verbose);

#endif