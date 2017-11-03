#include <stdio.h>
#include "libs/dsp.h"
#include "libs/filtros.h"
#include "libs/wav.h"

/*
* Muestreo y recuperación de una señal
* haciendo convolución con un filtro pasabajas
*/

int main(int argc, char *argv[]) {
  if (argc != 4) {
    printf("Uso: %s <archivo1.wav> <archivo2.wav> <salida.wav> \n", argv[0]);
    return 0;
  }

  FILE *entrada = fopen(argv[1], "rb");
  FILE *entrada2 = fopen(argv[2], "rb");
  FILE *salida = fopen(argv[3], "w+b");

  WAVHeader hEntrada1 = readHeaderWAV(entrada);
  WAVHeader hEntrada2 = readHeaderWAV(entrada2);
  int n_muestras = hEntrada1.Subchunk2Size / (hEntrada1.NumChannels * 2);

  WAVHeader hSalida =
      newWAVHeader(hEntrada1.NumChannels, n_muestras, hEntrada1.SampleRate);
  writeWAVHeader(salida, hSalida);

  printf("\n Número de canales: %d", hEntrada1.NumChannels);
  printf("\n Número de muestras: %d", n_muestras);
  if (hEntrada1.NumChannels == MONO) {
    for (int i = 0; i < n_muestras; i++) {
      MuestraMono m = readSampleMono(entrada, i);    // Se lee una muestra
      MuestraMono m2 = readSampleMono(entrada2, i);  // Se lee una muestra
      m.muestra *= m2.muestra;                       // Se multiplican
      writeSampleMono(salida, m);                    // Se escribe en la
    }
  } else {
    for (int i = 0; i < n_muestras; i++) {
      MuestraEstereo m = readSampleEstereo(entrada, i);    // Se lee una
      MuestraEstereo m2 = readSampleEstereo(entrada2, i);  // Se lee una
      m.left *= m2.left;                                   // Se multiplican
      m.right *= m2.right;                                 // Se multiplican
      writeSampleEstereo(salida, m);  // Se escribe en la salida
    }
  }

  printHeaderWAV(hEntrada1, argv[1]);
  printHeaderWAV(hEntrada2, argv[2]);
  printHeaderWAV(hSalida, argv[3]);
  fclose(salida);
  fclose(entrada);
  fclose(entrada2);
  printf("\nMultiplicación de señales guardada en %s\n", argv[3]);
  return 0;
}
