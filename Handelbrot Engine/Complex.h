#ifndef COMPLEX_H
#define COMPLEX_H

struct Complex
{
	double re, im;
};

Complex Complex_add(Complex& a, Complex& b);
Complex Complex_multiply(Complex& a, Complex& b);
double Complex_abs(Complex& z);


#endif
