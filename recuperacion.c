#include <stdio.h>
#include "libs/dsp.h"
#include "libs/filtros.h"
#include "libs/wav.h"

/*
* recuperación de una señal
* haciendo convolución con un filtro pasabajas
*/

int main(int argc, char *argv[]) {
  FILE *entrada, *salida;

  if (argc < 2) {
    printf("Uso: %s <entrada.wav> <salida.wav> \n", argv[0]);
    return 0;
  }

  /*Recuperación de señal muestreada - Convolución*/
  printf("\nRecuperando señal muestreada de %s\n", argv[2]);

  entrada = fopen(argv[1], "rb");
  salida = fopen(argv[2], "w+b");

  WAVHeader hEntrada = readHeaderWAV(entrada);
  // ArrayDouble filtro = obtenerMuestrasPasabajasIdeal(hEntrada.Subchunk2Size /
  // 2,
  //                                                    1000,
  //                                                    hEntrada.SampleRate);
  printf("\nMuestras Entrada: %d", hEntrada.Subchunk2Size / 2);

  ArrayDouble filtro = newArrayDouble(100);
  for (int i = 0; i < 100; i++) {
    double t = i / (hEntrada.SampleRate / 2);
    filtro.items[i] = sinc(t - i + 49);
  }
  // printf("\nFiltro pasa bajas:");
  // printArrayDouble(filtro);

  ArrayDouble conv = convolucionPorFormula(entrada, hEntrada, filtro);
  conv = mapArrayDouble(conv, -1, 1);
  printf("\nConvolucion:");
  printArrayDouble(conv);

  conv = cutArrayDouble(conv, 49, START_AND_END);

  printf("\nConvolucion:");
  printArrayDouble(conv);

  WAVHeader hSalida = newWAVHeader(1, conv.length, hEntrada.SampleRate);
  writeWAVHeader(salida, hSalida);
  writeSamplesMono(salida, conv);

  printHeaderWAV(hEntrada, argv[1]);
  printHeaderWAV(hSalida, argv[2]);
  fclose(salida);
  fclose(entrada);
  printf("\nSeñal muestreada recuperada en %s\n", argv[2]);
}
