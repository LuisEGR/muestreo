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
    printf("Uso: %s <entrada.wav> <salida.wav> <fm> \n", argv[0]);
    return 0;
  }

  /*Recuperación de señal muestreada - Convolución*/
  printf("\nRecuperando señal muestreada de %s\n", argv[2]);

  entrada = fopen(argv[1], "rb");
  salida = fopen(argv[2], "w+b");

  if (entrada == NULL || salida == NULL) {
    printf("\n Error al abrir los archivos!");
    return 0;
  }

  WAVHeader hEntrada = readHeaderWAV(entrada);
  printf("\nMuestras Entrada: %d", hEntrada.Subchunk2Size / 2);

  int frecCorteFiltro = atoi(argv[3]);
  printf("\nFiltro pasa bajas (%dHz):", frecCorteFiltro);
  int numMuestrasFiltroPasabajas = 100;
  ArrayDouble filtro = obtenerMuestrasPasabajasIdeal(
      numMuestrasFiltroPasabajas, frecCorteFiltro, hEntrada.SampleRate);
  printf("\nFiltro pasa bajas:");
  printArrayDouble(filtro);
  ArrayDouble conv = convolucionPorFormula(entrada, hEntrada, filtro);
  conv = mapArrayDouble(conv, -1, 1);
  // Se cortan las muestras extras generadas por el filtro pasabajas
  conv = cutArrayDouble(conv, (numMuestrasFiltroPasabajas / 2) - 1, START_AND_END);

  WAVHeader hSalida = newWAVHeader(1, conv.length, hEntrada.SampleRate);
  writeWAVHeader(salida, hSalida);
  writeSamplesMono(salida, conv);

  printHeaderWAV(hEntrada, argv[1]);
  printHeaderWAV(hSalida, argv[2]);
  fclose(salida);
  fclose(entrada);
  printf("\nSeñal muestreada recuperada en %s\n", argv[2]);
}
