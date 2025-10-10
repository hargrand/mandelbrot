#include "complex_math.h"

struct complex complex_add(struct complex x, struct complex y)
{
	// Rectangular (Cartesian) Form:
	// z = x + (y * im)

	struct complex return_value = { x.x + y.x, x.y + y.y };

	return return_value;
}

struct complex complex_sub(struct complex x, struct complex y)
{
	struct complex return_value = { x.x - y.x, x.y - y.y };

	return return_value;
}

struct complex complex_mul(struct complex x, struct complex y)
{
	struct complex return_value = { 
		x.x * y.x - x.y * y.y,   // (ac - bd)
		x.x * y.y + x.y * y.x    // (ad + bc)i
	};

	return return_value;
}

struct complex complex_div(struct complex x, struct complex y)
{
	double denom = y.x * y.x + y.y * y.y;  // c^2 + d^2
	struct complex return_value = { 
		(x.x * y.x + x.y * y.y) / denom,   // (ac + bd)  /denom
		(x.y * y.x - x.x * y.y) / denom    // (bc - ad)i /denom
	};

	return return_value;
}

struct complex complex_conj(struct complex z)
{
	struct complex return_value = { z.x , -z.y };

	return return_value;
}

double complex_mag2(struct complex z)
{
	return z.x * z.x + z.y * z.y; // Magnitude squared
}

double complex_mag(struct complex z)
{
	return sqrt(complex_mag2(z)); // Sqaure root of the magnitude squared
}

double complex_arg(struct complex z)
{
	return atan2(z.y, z.x); // Returns angle in [-rad, rad]
}							  // Order matters, arctangent2(y,x)
							  // gives the angle of the point (x,y)

struct complex complex_from_polar(double arg, double mag)
{
	// Polar Form:
	// z = mag * (cos(theta) + (im * sin(theta)))

	struct complex return_value = { cos(arg) * mag , sin(arg) * mag };

	return return_value;
}