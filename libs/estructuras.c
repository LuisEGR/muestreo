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
#include "estructuras.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "complex.h"

/*
 * Function:  newArrayDouble
 * --------------------
 * Crea un nuevo ArrayDouble, le asigna length=size y
 * reserva sizeof(double)*size bytes de memoria
 *
 *  arguments
 *  size:  número de elementos que tendrá el ArrayDouble
 *
 *  returns: un nuevo ArrayDouble
 */
ArrayDouble newArrayDouble(int size) {
  ArrayDouble arrayDouble;
  arrayDouble.items = (double *)malloc(sizeof(double) * size);
  arrayDouble.length = size;
  return arrayDouble;
}

ArrayComplex newArrayComplex(int size) {
  ArrayComplex arrayComplex;
  arrayComplex.items = (ComplexNumber *)malloc(sizeof(ComplexNumber) * size);
  arrayComplex.length = size;
  return arrayComplex;
}

/*
 * Function:  printArrayDouble
 * --------------------
 * Imprime en la consola todos los elementos de un
 * ArrayDouble
 *
 *  arguments
 *  a:  estructura de tipo ArrayDouble, de la cual se
 *      desean imprimir todos sus elementos
 *
 *  returns: <none>
 */
void printArrayDouble(ArrayDouble a) {
  printf(" ---- %d Elementos: -----\n", a.length);
  for (int i = 0; i < a.length; i++) {
    printf("\t[%d] %f\n", i, a.items[i]);
  }
  printf("\n");
}

void printArrayComplex(ArrayComplex a) {
  printf(" ---- %d Elementos: -----\n", a.length);
  for (int i = 0; i < a.length; i++) {
    printf("\t[%d] %f + %fj\n", i, a.items[i].real, a.items[i].imag);
  }
  printf("\n");
}

/*
 * Function:  mapArrayDouble
 * --------------------
 * Realiza el mapeo de un arreglo a otro dominio siguiendo la formula:
 *  y[i] = (a[i] - menor(a)) / (mayor(a) - menor(a)) * (to - from) + from
 *
 *  arguments
 *  a:  estructura de tipo ArrayDouble
 *  from: número menor del dominio destino
 *  to:   número mayor del dominio destino
 *
 *  returns: ArrayDouble mapeado
 */
ArrayDouble mapArrayDouble(ArrayDouble a, double from, double to) {
  double input_start, input_end;
  ArrayDouble mapeado = newArrayDouble(a.length);
  input_start = getMenorDouble(a);
  input_end = getMayorDouble(a);

  for (int i = 0; i < mapeado.length; i++) {
    mapeado.items[i] =
        (a.items[i] - input_start) / (input_end - input_start) * (to - from) +
        from;
  }

  return mapeado;
}

/*
 * Function:  getMayorDouble
 * --------------------
 * Obtiene el elemento mayor de un arreglo de tipo ArrayDouble
 *
 *  arguments
 *  a:  estructura de tipo ArrayDouble, de la cual se
 *      desean obtener el mayor
 *
 *  returns: double -> número mayor del arreglo
 */
double getMayorDouble(ArrayDouble a) {
  double m = 0;
  for (int i = 0; i < a.length; i++) {
    if (a.items[i] > m) m = a.items[i];
  }
  return m;
}

/*
 * Function:  getMayorDouble
 * --------------------
 * Obtiene el elemento menor de un arreglo de tipo ArrayDouble
 *
 *  arguments
 *  a:  estructura de tipo ArrayDouble, de la cual se
 *      desean obtener el menor
 *
 *  returns: double -> número menor del arreglo
 */
double getMenorDouble(ArrayDouble a) {
  double m = 0;
  for (int i = 0; i < a.length; i++) {
    if (a.items[i] < m) m = a.items[i];
  }
  return m;
}

ArrayDouble getRealFromArrayComplex(ArrayComplex c) {
  ArrayDouble out = newArrayDouble(c.length);
  for (int i = 0; i < c.length; i++) {
    out.items[i] =
        c.items[i].real > 1 ? 1 : c.items[i].real < -1 ? -1 : c.items[i].real;
  }
  return out;
}

ArrayDouble getImagFromArrayComplex(ArrayComplex c) {
  ArrayDouble out = newArrayDouble(c.length);
  for (int i = 0; i < c.length; i++) {
    out.items[i] = c.items[i].imag;
  }
  return out;
}

ArrayDouble getMagFromArrayComplex(ArrayComplex c) {
  ArrayDouble out = newArrayDouble(c.length);
  for (int i = 0; i < c.length; i++) {
    double m = getMagnitud(c.items[i]);
    out.items[i] = m;
    // out.items[i] = m > 1 ? 1 : m < -1 ? -1 : m;
  }
  out = mapArrayDouble(out, 0, 1);
  return out;
}

ArrayDouble getAngFromArrayComplex(ArrayComplex c) {
  ArrayDouble out = newArrayDouble(c.length);
  for (int i = 0; i < c.length; i++) {
    double m = getAngulo(c.items[i]);
    out.items[i] = m;
    // out.items[i] = m > 1 ? 1 : m < -1 ? -1 : m;
  }
  // out = mapArrayDouble(out, -1, 1);
  return out;
}

ArrayDouble cutArrayDouble(ArrayDouble arr, int size_cut, int mode) {
  ArrayDouble new;
  if (mode == START_AND_END) {
    new = newArrayDouble(arr.length - size_cut * 2);
    for (int i = size_cut; i < arr.length - size_cut; i++) {
      new.items[i - size_cut] = arr.items[i];
    }
  }
  return new;
}