#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "complex.h"


ComplexNumber newComplexNumber(double real, double imag){
  ComplexNumber c;
  c.real = real;
  c.imag = imag;
  return c;
}

double getMagnitud(ComplexNumber c){
  return sqrt(pow(c.real, 2) + pow(c.imag, 2)) * (c.imag < 0 ? -1 : 1);
}

double getAngulo(ComplexNumber c){
  return atan2(c.imag,c.real);
}
