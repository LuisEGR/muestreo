#include <math.h>
#include <stdio.h>
#include "libs/complex.h"
#include "libs/dsp.h"
#include "libs/filtros.h"
#include "libs/wav.h"

/*
* recuperación de una señal
* haciendo convolución con un filtro pasabajas
*/

int main(int argc, char *argv[]) {
  FILE *salida;

  if (argc < 4) {
    printf("Uso: %s <salida.wav> <frecuenciaCorte> <frecuenciaMuestreo>\n",
           argv[0]);
    return 0;
  }

  /*Recuperación de señal muestreada - Convolución*/
  printf("\nGenerando filtro pasabajas\n");
  salida = fopen(argv[1], "w+b");

  int nmuestras = 100;
  int frecCorte = 1000;
  int frecMuest = 44100;

  frecCorte = atoi(argv[2]);
  frecMuest = atoi(argv[3]);
  // frecMuest = frecCorte ;
  // ArrayDouble filtro =
  //     obtenerMuestrasPasabajasIdeal(nmuestras, frecCorte, frecMuest);
  int offset = (nmuestras / 2) - 1;
  printf("\nOffset: %d", offset);
  ArrayDouble filtro = newArrayDouble(nmuestras);
  filtro = obtenerMuestrasPasabajasIdeal(nmuestras, frecCorte, frecMuest);
  // for (int i = 0; i < nmuestras; i++) {
  //   double t = (double)i / (double)frecMuest;
  //   double ang = 2 * M_PI * frecCorte * t;
  //   printf("\nFrecCorte: %d", frecCorte);
  //   printf("\nt: %d", t);
  //   printf("\nAngulo: %f", ang);

  //   filtro.items[i] = sinc(ang - 4.5 * M_PI);
  //   // filtro.items[i] = sinc(t - i + offset);
  // }
  printf("\nFiltro pasa bajas:");
  printArrayDouble(filtro);

  WAVHeader hSalida = newWAVHeader(1, nmuestras, frecMuest);
  writeWAVHeader(salida, hSalida);
  writeSamplesMono(salida, filtro);

  printHeaderWAV(hSalida, argv[1]);
  fclose(salida);
  printf("\n Filtro pasabajas generado en %s\n", argv[1]);
}
