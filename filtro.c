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

  if (argc < 3) {
    printf("Uso: %s <salida.wav> <frecuenciaCorte>\n", argv[0]);
    return 0;
  }

  /*Recuperación de señal muestreada - Convolución*/
  printf("\nGenerando filtro pasabajas\n");
  salida = fopen(argv[1], "w+b");

  int nmuestras = 100;
  int frecCorte = 1000;
  int frecMuest = 2000;

  // frecCorte = atoi(argv[2]);
  // frecMuest = frecCorte ;
  // ArrayDouble filtro =
  //     obtenerMuestrasPasabajasIdeal(nmuestras, frecCorte, frecMuest);
  ArrayDouble filtro = newArrayDouble(nmuestras);
  for (int i = 0; i < 100; i++) {
    double t = i / (44100 / 2);
    filtro.items[i] = sinc(t - i + 49);
  }
  printf("\nFiltro pasa bajas:");
  printArrayDouble(filtro);

  WAVHeader hSalida = newWAVHeader(1, nmuestras, frecMuest);
  writeWAVHeader(salida, hSalida);
  writeSamplesMono(salida, filtro);

  printHeaderWAV(hSalida, argv[1]);
  fclose(salida);
  printf("\n Filtro pasabajas generado en %s\n", argv[1]);
}
