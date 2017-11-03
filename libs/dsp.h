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

#ifndef DSP_H
#define DSP_H

#include "estructuras.h"
#include "wav.h"

ArrayDouble convolucionPorFormula(FILE *file_p, WAVHeader header,
                                  ArrayDouble g);

ArrayDouble crearTrenDeImpulsos(float duracion, int fm, int intervalo);
ArrayDouble crearSeno(int items, float fm);

// Transformada Discreta de Fourier
ArrayComplex transformadaFourier(FILE *file_p, WAVHeader header);
ArrayDouble transformadaFourierInversa(ArrayComplex X);
// ArrayComplex transformadaFourier(ArrayDouble x);
// ArrayComplex transformadaFourierInversa(ArrayComplex x);

#endif
