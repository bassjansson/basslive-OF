
#pragma once

#include <vector>


struct Complex
{
	float real;
	float imag;
};

typedef std::vector<Complex> ComplexVector;


Complex newComplex (float real, float imag);

Complex operator+ (Complex left, Complex right);
Complex operator- (Complex left, Complex right);
Complex operator* (Complex left, Complex right);
Complex operator/ (Complex left, Complex right);

Complex carToPol (Complex car);
Complex polToCar (Complex pol);

Complex complexPow (Complex input, int power);
float   complexAbs (Complex input);
