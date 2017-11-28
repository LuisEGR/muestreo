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

#include "dsp.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "complex.h"
#include "estructuras.h"
#include "wav.h"

/*
 * Function:  convolucionPorFormula
 * --------------------
 * Realiza la convolucón de las muestras de un archivo wav con
 * un ArrayDouble y retorna el arreglo resultado de la operación
 *
 *  arguments
 *  *file_p:  apuntador a archivo wav
 *  header :  Cabecera del archivo wav
 *  g      :  ArrayDouble que contiene los valores de la función con
 *            la que se hará la convolución
 *
 *  returns: estructura ArrayDouble con el resultado de la convolución
 */
ArrayDouble convolucionPorFormula(FILE *file_p, WAVHeader header,
                                  ArrayDouble g) {
  int i, j, muestras_y, i1;
  double tmp;
  int n_muestrasWAV = (header.Subchunk2Size / 2);
  int longitud = n_muestrasWAV + g.length - 1;
  MuestraMono muestra;
  ArrayDouble y = newArrayDouble(longitud);
  printf("Y.length: %d\n", longitud);
  for (i = 0; i < longitud; i++) {
    tmp = 0.0;
    i1 = i;
    for (j = 0; j < g.length; j++) {
      if (i1 >= 0 && i1 < n_muestrasWAV) {
        muestra = readSampleMono(file_p, i1);
        tmp += (muestra.muestra * g.items[j]);
      }
      i1 -= 1;
      y.items[i] = tmp;
    }
  }
  return y;
}

/*
 * Function:  crearTrenDeImpulsos
 * --------------------
 *  Crea un tren de impulsos unitarios
 *  arguments
 *  duracion:  duración en segundos
 *  fm      :  frecuencia de muestreo
 *  fmt     : frecuencia de muestreo del tren
 *
 *  returns: estructura ArrayDouble con el tren de impulsos
 */
ArrayDouble crearTrenDeImpulsos(float duracion, int fm, int fmt) {
  int size = (int)(duracion * fm);
  ArrayDouble tren = newArrayDouble(size);
  for (int i = 0; i < size; i++) {
    tren.items[i] = 0;
  }
  for (int i = 0; i < size; i += (fm / fmt)) {
    tren.items[i] = 1;
  }
  return tren;
}

/*
 * Function:  crearSeno
 * --------------------
 *  Crea muestras de una función seno
 *  arguments
 *  items   :  número de muestras
 *  fm      :  frecuencia de muestreo
 *
 *  returns: estructura ArrayDouble con las muestras del seno
 */
ArrayDouble crearSeno(int items, float fm) {
  ArrayDouble out = newArrayDouble(items);
  for (int i = 0; i < items; i++) {
    out.items[i] = sin(2 * M_PI * i * 1.0 / fm);
  }
  return out;
}

ArrayComplex transformadaFourier(FILE *file_p, WAVHeader header) {
  int N = header.Subchunk2Size / (header.BitsPerSample / 8);
  double ang;
  ArrayComplex X = newArrayComplex(N);
  for (int k = 0; k <= N - 1; k++) {
    X.items[k] = newComplexNumber(0, 0);
    // ang = - (2 * M_PI * k) / N
    for (int n = 0; n <= N - 1; n++) {
      MuestraMono muestra = readSampleMono(file_p, n);
      ang = -(2.0 * M_PI * k * n) / N;
      X.items[k].real += muestra.muestra * cos(ang);
      X.items[k].imag += muestra.muestra * sin(ang);
    }
  }
  return X;
}

ArrayDouble transformadaFourierInversa(ArrayComplex X) {
  int N = X.length;
  double ang;
  double con;
  ComplexNumber sumTemp;
  ArrayDouble x = newArrayDouble(N);
  for (int n = 0; n <= N - 1; n++) {
    sumTemp = newComplexNumber(0,0);
    for (int k = 0; k <= N - 1; k++) {
      ang = (2 * M_PI * k * n) / N;
      ComplexNumber c = newComplexNumber(cos(ang), sin(ang));
      ComplexNumber multi = complexMulti(X.items[k], c);
      sumTemp = complexSum(sumTemp, multi);
      // sumTemp += multi.real;
          // printf("sumTemp: %f  ", sumTemp);
      // printComplex(sumTemp);
      // printf("%f", X.items[k]);
    }
    printComplex(sumTemp);

    // x.items[n] = (1.0 / N) * sumTemp.real;
    x.items[n] = getMagnitud(sumTemp);
    // printf("%f\n", x.items[n]);
  }
  return x;
}
