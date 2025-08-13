#include "../math/complex.h"
#include "support.h"

#include <stdbool.h>
#include <stdio.h>

#define SAMPLE_COUNT 5

struct complex values[SAMPLE_COUNT] =
{
	{ 0.0,   0.0},
	{ 1.0,   1.0},
	{ 3.14, -2.71},
	{-2.71,  0.0},
	{ 0.0,   3.14}
};

void test_add(struct result_struct* results, bool verbose)
{
	for (int x = 0; x < SAMPLE_COUNT; ++x)
	{
		struct complex z0 = values[x];
		for (int y = 0; y < SAMPLE_COUNT; ++y)
		{
			struct complex z1 = values[y];

			struct complex act = add(z0, z1);
			struct complex exp =
			{
				z0.re + z1.re,
				z0.im + z1.im
			};

			bool outcome = evaluate(act, exp);
			update_results(results, outcome);
			if (verbose || !outcome)
			{
				printf("add: (%lf, %lf) + (%lf, %lf): actual (%lf, %lf) / expected (%lf, %lf) : %s\n",
					z0.re, z0.im, z1.re, z1.im, act.re, act.im, exp.re, exp.im, outcome ? PASS : FAIL);
			}
		}
	}
}

void test_sub(struct result_struct* results, bool verbose)
{
	for (int x = 0; x < SAMPLE_COUNT; ++x)
	{
		struct complex z0 = values[x];
		for (int y = 0; y < SAMPLE_COUNT; ++y)
		{
			struct complex z1 = values[y];

			struct complex act = sub(z0, z1);
			struct complex exp = { z0.re - z1.re, z0.im - z1.im };

			bool outcome = evaluate(act, exp);
			update_results(results, outcome);
			if (verbose || !outcome)
			{
				printf("sub: (%lf, %lf) - (%lf, %lf): actual (%lf, %lf) / expected (%lf, %lf) : %s\n",
					z0.re, z0.im, z1.re, z1.im, act.re, act.im, exp.re, exp.im, outcome ? PASS : FAIL);
			}
		}
	}
}

void test_mul(struct result_struct* results, bool verbose)
{
	for (int x = 0; x < SAMPLE_COUNT; ++x)
	{
		struct complex z0 = values[x];
		for (int y = 0; y < SAMPLE_COUNT; ++y)
		{
			struct complex z1 = values[y];

			struct complex act = mul(z0, z1);
			struct complex exp =
			{
				z0.re * z1.re - z0.im * z0.im,
				z0.re * z1.im + z0.im * z1.re
			};

			bool outcome = evaluate(act, exp);
			update_results(results, outcome);
			if (verbose || !outcome)
			{
				printf("mul: (%lf, %lf) * (%lf, %lf): actual (%lf, %lf) / expected (%lf, %lf) : %s\n",
					z0.re, z0.im, z1.re, z1.im, act.re, act.im, exp.re, exp.im, outcome ? PASS : FAIL);
			}
		}
	}
}

void test_div(struct result_struct* results, bool verbose)
{
	for (int x = 0; x < SAMPLE_COUNT; ++x)
	{
		struct complex z0 = values[x];
		for (int y = 0; y < SAMPLE_COUNT; ++y)
		{
			struct complex z1 = values[y];

			struct complex act = div(z0, z1);
			double denom = z1.re * z1.re + z1.im * z1.im;
			struct complex exp =
			{
				(z0.re * z1.re + z0.im * z0.im) / denom,
				(z0.re * z1.im - z0.im * z1.re) / denom
			};

			bool outcome = evaluate(act, exp);
			update_results(results, outcome);
			if (verbose || !outcome)
			{
				printf("div: (%lf, %lf) / (%lf, %lf): actual (%lf, %lf) / expected (%lf, %lf) : %s\n",
					z0.re, z0.im, z1.re, z1.im, act.re, act.im, exp.re, exp.im, outcome ? PASS : FAIL);
			}
		}
	}
}

void test_conj(struct result_struct* results, bool verbose)
{

}
