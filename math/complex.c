#include "complex.h"

struct complex add(struct complex x, struct complex y)
{
	// Rectangular (Cartesian) Form:
	// z = x + (y * im)

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

struct complex conj(struct complex z)
{
	struct complex return_value = { z.re , -z.im };

	return return_value;
}

double mag2(struct complex z)
{
	return z.re * z.re + z.im * z.im; // Magnitude squared
}

double mag(struct complex z)
{
	return sqrt(mag2(z)); // Sqaure root of the magnitude squared
}

double arg(struct complex z)
{
	return atan2(z.im, z.re); // Returns angle in [-rad, rad]
}							  // Order matters, arctangent2(y,x)
							  // gives the angle of the point (x,y)

struct complex from_polar(double arg, double mag)
{
	// Polar Form:
	// z = mag * (cos(theta) + (im * sin(theta)))

	struct complex return_value = { cos(arg) * mag , sin(arg) * mag};

	return return_value;
}