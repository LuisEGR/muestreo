#include "complex.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

ComplexNumber newComplexNumber(double real, double imag) {
  ComplexNumber c;
  c.real = real;
  c.imag = imag;
  return c;
}

double getMagnitud(ComplexNumber c) {
  return sqrt(pow(c.real, 2) + pow(c.imag, 2));
}

double getAngulo(ComplexNumber c) {
  if (c.real > 0.0001) {
    printf("\nCalculando angulo: arctg(%.15f/%.15f)", c.imag, c.real);
    return atan2(c.imag, c.real);
  }
  // printf("\nNo se puede calcular");
  return 0;
  // printf("\nCalculando angulo: arctg(%f/%f)", c.imag, c.real);
  // return atan2(c.imag, c.real);
}

ComplexNumber complexMulti(ComplexNumber a, ComplexNumber b) {
  ComplexNumber res;
  res.real = a.real * b.real - (a.imag * b.imag);
  res.imag = a.imag * b.real + a.real * b.imag;
  return res;
}

ComplexNumber complexSum(ComplexNumber a, ComplexNumber b) {
  ComplexNumber res;
  res.real = a.real + b.real;
  res.imag = a.imag + b.imag;
  return res;
}

void printComplex(ComplexNumber a) { printf("\t %f + %fj\n", a.real, a.imag); }
