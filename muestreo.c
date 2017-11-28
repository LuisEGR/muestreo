#include <stdio.h>
#include "libs/dsp.h"
#include "libs/filtros.h"
#include "libs/wav.h"

/*
* Muestreo de una señal
*/

int main(int argc, char *argv[]) {
  FILE *entrada, *salida;

  if (argc < 3) {
    printf("Uso: %s <frecuenciaMuestreo> <entrada.wav> <salida.wav> \n",
           argv[0]);
    return 0;
  }

  int frecMuestreo = atoi(argv[1]);

  /* Muestreo de una señal */
  printf("\nMuestreando señal de %s\n", argv[2]);
  float duracion;
  entrada = fopen(argv[2], "rb");
  salida = fopen(argv[3], "w+b");

  if (entrada == NULL || salida == NULL) {
    printf("\n Error al abrir los archivos!");
    return 0;
  }

  printf("\n Frecuencia de muestreo: %d", frecMuestreo);

  WAVHeader hEntrada = readHeaderWAV(entrada);
  duracion = getDuracionWAV(hEntrada);
  printf("Duración: %f", getDuracionWAV(hEntrada));

  ArrayDouble tren =
      crearTrenDeImpulsos(duracion, hEntrada.SampleRate, frecMuestreo);
  // printArrayDouble(tren);

  WAVHeader hSalida = newWAVHeader(1, tren.length, hEntrada.SampleRate);
  writeWAVHeader(salida, hSalida);

  for (int i = 0; i < tren.length; i++) {
    MuestraMono m = readSampleMono(entrada, i);  // Se lee una muestra
    m.muestra *= tren.items[i];                  // Se multiplica por el tren
    writeSampleMono(salida, m);                  // Se escribe en la salida
  }

  printHeaderWAV(hEntrada, argv[2]);
  printHeaderWAV(hSalida, argv[3]);
  fclose(salida);
  fclose(entrada);
  printf("\nSeñal muestreada guardada en %s\n", argv[3]);
  return 1;
}
