#include "Complex.h"

#include <math.h>

Complex Complex_add(Complex& a, Complex& b)
{
	Complex num;
	num.re = a.re + b.re;
	num.im = a.im + b.im;
	return num;
}

Complex Complex_multiply(Complex& a, Complex& b)
{
	Complex num;
	num.re = a.re * b.re - a.im * b.im;
	num.im = a.re * b.im + a.im * b.re;
	return num;
}

double Complex_abs(Complex& z)
{
	return sqrt(z.re * z.re + z.im * z.im);
}