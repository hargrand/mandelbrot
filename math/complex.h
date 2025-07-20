#ifndef COMPLEX_MATH_H
#define COMPLEX_MATH_H

/// <summary>
/// Structure representing a complex number comprised of a real and
/// imaginary part
/// </summary>
struct complex {
	/// <summary>
	/// Real component of the complex number
	/// </summary>
	double re;

	/// <summary>
	/// Imaginary component of the complex number
	/// </summary>
	double im;
};

/// <summary>
/// Add two complex values and return the sum
/// </summary>
/// <param name="x">Left operand of the addition operation</param>
/// <param name="y">Right operand of the addition operation</param>
/// <returns>Complex value representing the sum of x and y</returns>
extern struct complex add(struct complex x, struct complex y);

/// <summary>
/// Subtract one complex value from another and return the difference
/// </summary>
/// <param name="x">Left operand of the subtraction operation</param>
/// <param name="y">Right operand of the subtraction operation</param>
/// <returns>Complex value representing the difference of x and y</returns>
extern struct complex sub(struct complex x, struct complex y);

/// <summary>
/// Multiply two complex values and return the product
/// </summary>
/// <param name="x">Left operand of the multiplication operation</param>
/// <param name="y">Right operand of the multiplication operation</param>
/// <returns>Complex value representing the product of x and y</returns>
extern struct complex mul(struct complex x, struct complex y);

/// <summary>
/// Divide one complex value by another and return the quotient
/// </summary>
/// <param name="x">Left operand (numerator) of the division operation</param>
/// <param name="y">Right operand (denominator) of the division operation
/// </param>
/// <returns>Complex value representing the qutient when x is divided by y
/// </returns>
extern struct complex div(struct complex x, struct complex y);

/// <summary>
/// Compute and return the complex conjugate of the given value
/// </summary>
/// <param name="z">Number to compute the complex conjugate of</param>
/// <returns>Complex conjugate of z</returns>
extern struct complex conj(struct complex z);

/// <summary>
/// Compute the square of the magnitude of the given complex value
/// </summary>
/// <param name="z"></param>
/// <returns></returns>
extern double mag2(struct complex z);

/// <summary>
/// Compute and return the magnitude of the given complex number
/// </summary>
/// <param name="z">Complex value to compute the magnitude of</param>
/// <returns>Magnitude of the given complex number</returns>
extern double mag(struct complex z);

/// <summary>
/// Compute and return the argument of the given complex number, which is
/// the angle in radians in the comlplex plane of the number relative to
/// the positive real axis.
/// </summary>
/// <param name="z">Number to compute the argument of</param>
/// <returns>Argument of the complex number given</returns>
extern double arg(struct complex z);

/// <summary>
/// Construct a complex number from its arg and mag values
/// </summary>
/// <param name="arg">Angle in radians of the position of the complex value
/// relative to the positive real axis</param>
/// <param name="mag">Distance the complex is from the origin of the complex
/// plane</param>
/// <returns>The complex value derived from the given arg (angle in radians)
/// and mag (distance from the origin) </returns>
extern struct complex from_polar(double arg, double mag);

#endif