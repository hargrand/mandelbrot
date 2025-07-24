#include "complex.h"

struct complex add(struct complex x, struct complex y)
{
	struct complex return_value = { x.re + y.re, x.im + y.im };

	return return_value;
}

struct complex sub(struct complex x, struct complex y)
{
	struct complex return_value = { x.re - y.re, x.im - y.im };

	return return_value;
}

struct complex mul(struct complex x, struct complex y)
{
	struct complex return_value = { x.re * y.re, x.im * y.im };

	return return_value;
}

struct complex div(struct complex x, struct complex y)
{
	struct complex return_value = { x.re / y.re, x.im / y.im };

	return return_value;
}