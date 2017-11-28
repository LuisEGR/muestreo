#include <stdio.h>
#include <stdlib.h>
#include "libs/dsp.h"
#include "libs/wav.h"

/*
* Tren de impulsos
*/

int main(int argc, char *argv[]) {
  FILE *salida;

  if (argc < 4) {
    printf("Uso: %s <salida.wav> <duracion(seg)> <fm>\n", argv[0]);
    return 0;
  }

  float duracion = atof(argv[2]);
  int frecMuestreo = 44100;
  int frecMuestreoTren = atoi(argv[3]);

  printf("\n Duracion: %f", duracion);
  printf("\n frecMuestreo: %d", frecMuestreo);
  printf("\n frecMuestreoTren: %d", frecMuestreoTren);
  salida = fopen(argv[1], "w+b");

  ArrayDouble tren =
      crearTrenDeImpulsos(duracion, frecMuestreo, frecMuestreoTren);
  // printArrayDouble(tren);

  WAVHeader hSalida = newWAVHeader(1, tren.length, frecMuestreo);
  writeWAVHeader(salida, hSalida);

  writeSamplesMono(salida, tren);

  printHeaderWAV(hSalida, argv[1]);
  fclose(salida);
  printf("\nTren de impulsos guardado en %s\n", argv[1]);
  return 1;
}
