#include <stdio.h>
#include "libs/dsp.h"

int main(int argc, char *argv[]) {
  FILE *entrada, *salida;
  float duracion;

  entrada = fopen("./audio/cos16.wav", "rb");
  salida = fopen("./audio/tren_impulsos.wav", "w+b");

  WAVHeader hEntrada = readHeaderWAV(entrada);
  duracion = getDuracionWAV(hEntrada);
  printf("Duración: %f", getDuracionWAV(hEntrada));

  ArrayDouble tren = crearTrenDeImpulsos(duracion, hEntrada.SampleRate, 1000);
  printArrayDouble(tren);

  WAVHeader hSalida = newWAVHeader(1, tren.length, hEntrada.SampleRate);
  writeWAVHeader(salida, hSalida);

  for (int i = 0; i < tren.length; i++) {
    MuestraMono m = readSampleMono(entrada, i);  // Se lee una muestra
    double multip = tren.items[i] * m.muestra;   // Se multiplica por el tren
    writeSampleMono(salida, newMuestraMono(multip));  // Se escribe el resultado
  }

  fclose(salida);
  fclose(entrada);
}
