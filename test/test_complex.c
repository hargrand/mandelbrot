#include "../image_generator/complex.h"
#include "support.h"
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

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

			struct complex act = complex_add(z0, z1);
			struct complex exp =
			{
				z0.x + z1.x,
				z0.y + z1.y
			};

			bool outcome = evaluate_complex(act, exp);
			update_results(results, outcome);
			if (verbose || !outcome)
			{
				printf("add: (%lf, %lf) + (%lf, %lf): actual (%lf, %lf) / expected (%lf, %lf) : %s \n",
					z0.x, z0.y,
					z1.x, z1.y,
					act.x, act.y,
					exp.x, exp.y,
					outcome ? PASS : FAIL);
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

			struct complex act = complex_sub(z0, z1);
			struct complex exp = { z0.x - z1.x, z0.y - z1.y };

			bool outcome = evaluate_complex(act, exp);
			update_results(results, outcome);
			if (verbose || !outcome)
			{
				printf("sub: (%lf, %lf) - (%lf, %lf): actual (%lf, %lf) / expected (%lf, %lf) : %s \n",
					z0.x, z0.y,
					z1.x, z1.y,
					act.x, act.y,
					exp.x, exp.y,
					outcome ? PASS : FAIL);
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

			struct complex act = complex_mul(z0, z1);
			struct complex exp =
			{
				z0.x * z1.x - z0.y * z1.y,
				z0.x * z1.y + z0.y * z1.x
			};

			bool outcome = evaluate_complex(act, exp);
			update_results(results, outcome);
			if (verbose || !outcome)
			{
				printf("mul: (%lf, %lf) * (%lf, %lf): actual (%lf, %lf) / expected (%lf, %lf) : %s \n",
					z0.x, z0.y,
					z1.x, z1.y,
					act.x, act.y,
					exp.x, exp.y,
					outcome ? PASS : FAIL);
			}
		}
	}
}

void test_div(struct result_struct* results, bool verbose)
{
	for (int x = 0; x < SAMPLE_COUNT; ++x)
	{
		struct complex z0 = values[x];
		for (int y = 1; y < SAMPLE_COUNT; ++y)
		{
			struct complex z1 = values[y];

			struct complex act = complex_div(z0, z1);
			double denom = z1.x * z1.x + z1.y * z1.y;
			struct complex exp =
			{
				(z0.x * z1.x + z0.y * z1.y) / denom,
				(z0.y * z1.x - z0.x * z1.y) / denom
			};

			bool outcome = evaluate_complex(act, exp);
			update_results(results, outcome);
			if (verbose || !outcome)
			{
				printf("div: (%lf, %lf) / (%lf, %lf): actual (%lf, %lf) / expected (%lf, %lf) : %s \n",
					z0.x, z0.y,
					z1.x, z1.y,
					act.x, act.y,
					exp.x, exp.y,
					outcome ? PASS : FAIL);
			}
		}
	}
}

void test_conj(struct result_struct* results, bool verbose)
{
	for (int z = 0; z < SAMPLE_COUNT; ++z)
	{
		struct complex z0 = values[z];

		struct complex act = complex_conj(z0);
		struct complex exp = { z0.x, -z0.y };

		bool outcome = evaluate_complex(act, exp);
		update_results(results, outcome);
		if (verbose || !outcome)
		{
			printf("conj: (%lf), (%lf) : actual (%lf), (%lf) / expected (%lf), (%lf) : %s \n",
				z0.x, z0.y,
				act.x, act.y,
				exp.x, exp.y,
				outcome ? PASS : FAIL);
		}
	}
}

void test_mag2(struct result_struct* results, bool verbose)
{
	for (int z = 0; z < SAMPLE_COUNT; ++z)
	{
		struct complex z0 = values[z];

		double act = complex_mag2(z0);
		double exp = z0.x * z0.x + z0.y * z0.y;

		bool outcome = act == exp;
		update_results(results, outcome);
		if (verbose || !outcome)
		{
			printf("mag2: (%lf), (%lf) : actual (%lf) / expected (%lf) : %s \n",
				z0.x, z0.y,
				act, exp,
				outcome ? PASS : FAIL);
		}
	}
}

void test_mag(struct result_struct* results, bool verbose)
{
	for (int z = 0; z < SAMPLE_COUNT; ++z)
	{
		struct complex z0 = values[z];

		double act = complex_mag(z0);
		double exp = sqrt(complex_mag2(z0));

		bool outcome = act == exp;
		update_results(results, outcome);
		if (verbose || !outcome)
		{
			printf("mag: (%lf), (%lf) : actual (%lf) / expected (%lf) : %s \n",
				z0.x, z0.y,
				act, exp,
				outcome ? PASS : FAIL);
		}
	}
}

void test_arg(struct result_struct* results, bool verbose)
{
	for (int z = 0; z < SAMPLE_COUNT; ++z)
	{
		struct complex z0 = values[z];

		double act = complex_arg(z0);
		double exp = atan2(z0.y, z0.x);

		bool outcome = act == exp;
		update_results(results, outcome);
		if (verbose || !outcome)
		{
			printf("arg: (%lf), (%lf) : actual (%lf) / expected (%lf) : %s \n",
				z0.x, z0.y,
				act, exp,
				outcome ? PASS : FAIL);
		}
	}
}

void test_from_polar(struct result_struct* results, bool verbose)
{
	for (int z = 0; z < SAMPLE_COUNT; ++z)
	{
		struct complex z0 = values[z];

		double mag = complex_mag(z0);
		double arg = complex_arg(z0);

		struct complex act = complex_from_polar(arg, mag);
		struct complex exp = { cos(arg) * mag, sin(arg) * mag };

		bool outcome = evaluate_complex(act, exp);
		update_results(results, outcome);
		if (verbose || !outcome)
		{
			printf("from_polar: (%lf), (%lf), mag: (%lf), arg: (%lf) : actual (%lf), (%lf) / expected (%lf), (%lf) : %s \n",
				z0.x, z0.y,
				mag, arg,
				act.x, act.y,
				exp.x, exp.y,
				outcome ? PASS : FAIL);
		}

	}
}
