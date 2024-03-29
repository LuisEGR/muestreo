/****************************************************************************
Copyright (c) 2017, Luis E. González R., ESCOM, Instituto Politécnico Nacional.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to
deal in the Software without restriction, including without limitation the
rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
IN THE SOFTWARE.
****************************************************************************/

#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#define START_AND_END 1

#include "complex.h"

typedef struct ArrayDouble {
  unsigned int length;
  double* items;
} ArrayDouble;

typedef struct ArrayComplex {
  unsigned int length;
  ComplexNumber* items;
} ArrayComplex;

ArrayDouble newArrayDouble(int size);
ArrayDouble mapArrayDouble(ArrayDouble a, double from, double to);

double getMayorDouble(ArrayDouble a);
double getMenorDouble(ArrayDouble a);

void printArrayDouble(ArrayDouble a);

ArrayComplex newArrayComplex(int size);
void printArrayComplex(ArrayComplex a);

ArrayDouble getRealFromArrayComplex(ArrayComplex c);
ArrayDouble getImagFromArrayComplex(ArrayComplex c);
ArrayDouble getMagFromArrayComplex(ArrayComplex c);
ArrayDouble getAngFromArrayComplex(ArrayComplex c);
double mapNumberDouble(double num, double min, double max);


ArrayDouble cutArrayDouble(ArrayDouble arr, int size_cut, int mode);
#endif
