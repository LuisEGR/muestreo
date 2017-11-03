#include <stdio.h>
#include "libs/dsp.h"
#include "libs/filtros.h"
#include "libs/wav.h"

/*
* Muestreo y recuperación de una señal
* haciendo convolución con un filtro pasabajas
*/

int main(int argc, char *argv[]) {
  FILE *entrada, *salida;

  if (argc < 3 || argv[1][0] != '-') {
    printf("Uso: %s <opcion> <entrada.wav> <salida.wav> \n", argv[0]);
    printf("Opciones disponibles:\n");
    printf("\t -m \t Muestrear una señal\n");
    printf("\t -r \t Recuperar una señal muestreada\n");
    printf("\t -g \t Generar una señal seno de prueba\n\n");
    printf("\t -p \t Multiplicar 2 archivos de entrada\n\n");
    return 0;
  }

  if (argv[1][1] == 'r') {
    /*Recuperación de señal muestreada - Convolución*/
    printf("\nRecuperando señal muestreada de %s\n", argv[2]);

    entrada = fopen(argv[2], "rb");
    salida = fopen(argv[3], "w+b");

    WAVHeader hEntrada = readHeaderWAV(entrada);
    ArrayDouble filtro = obtenerMuestrasPasabajasIdeal(
        hEntrada.Subchunk2Size / 2, 1000, hEntrada.SampleRate);
    printf("\nFiltro pasa bajas:");
    printArrayDouble(filtro);

    ArrayDouble conv = convolucionPorFormula(entrada, hEntrada, filtro);
    conv = mapArrayDouble(conv, -1, 1);
    // printf("\nConvolucion:");
    // printArrayDouble(conv);

    WAVHeader hSalida = newWAVHeader(1, conv.length, hEntrada.SampleRate);
    writeWAVHeader(salida, hSalida);
    writeSamplesMono(salida, conv);

    printHeaderWAV(hEntrada);
    printHeaderWAV(hSalida);
    fclose(salida);
    fclose(entrada);
    printf("\nSeñal muestreada recuperada en %s\n", argv[3]);

  } else if (argv[1][1] == 'm') {
    /* Muestreo de una señal */
    printf("\nMuestreando señal de %s\n", argv[2]);
    float duracion;
    entrada = fopen(argv[2], "rb");
    salida = fopen(argv[3], "w+b");

    WAVHeader hEntrada = readHeaderWAV(entrada);
    duracion = getDuracionWAV(hEntrada);
    printf("Duración: %f", getDuracionWAV(hEntrada));

    ArrayDouble tren = crearTrenDeImpulsos(duracion, hEntrada.SampleRate, 2000);
    // printArrayDouble(tren);

    WAVHeader hSalida = newWAVHeader(1, tren.length, hEntrada.SampleRate);
    writeWAVHeader(salida, hSalida);

    for (int i = 0; i < tren.length; i++) {
      MuestraMono m = readSampleMono(entrada, i);  // Se lee una muestra
      m.muestra *= tren.items[i];                  // Se multiplica por el tren
      writeSampleMono(salida, m);                  // Se escribe en la salida
    }

    printHeaderWAV(hEntrada);
    printHeaderWAV(hSalida);
    fclose(salida);
    fclose(entrada);
    printf("\nSeñal muestreada guardada en %s\n", argv[3]);

  } else if (argv[1][1] == 'p') {
    // Multiplicar 2 archivos de audio
    if (argc != 5) {
      printf("Uso: %s -p <archivo1.wav> <archivo2.wav> <salida.wav> \n",
             argv[0]);
      return 0;
    }

    entrada = fopen(argv[2], "rb");
    FILE *entrada2 = fopen(argv[3], "rb");
    salida = fopen(argv[4], "w+b");

    WAVHeader hEntrada1 = readHeaderWAV(entrada);
    WAVHeader hEntrada2 = readHeaderWAV(entrada2);
    int n_muestras = hEntrada1.Subchunk2Size / 2;

    WAVHeader hSalida = newWAVHeader(MONO, n_muestras, hEntrada1.SampleRate);
    writeWAVHeader(salida, hSalida);

    for (int i = 0; i < n_muestras; i++) {
      MuestraMono m = readSampleMono(entrada, i);    // Se lee una muestra
      MuestraMono m2 = readSampleMono(entrada2, i);  // Se lee una muestra
      m.muestra *= m2.muestra;                       // Se multiplican
      writeSampleMono(salida, m);                    // Se escribe en la salida
    }

    printHeaderWAV(hEntrada1);
    printHeaderWAV(hEntrada2);
    printHeaderWAV(hSalida);
    fclose(salida);
    fclose(entrada);
    fclose(entrada2);
    printf("\nSeñal muestreada guardada en %s\n", argv[3]);

  } else if (argv[1][1] == 'g') {
    if (argc != 3) {
      printf("Uso: %s -g <salida.wav> \n", argv[0]);
      return 0;
    }
    printf("\nGenerando señal seno en %s\n", argv[2]);

    /* Generación de señal seno*/
    salida = fopen(argv[2], "w+b");
    ArrayDouble seno = crearSeno(300, 100);
    WAVHeader hSalida = newWAVHeader(1, seno.length, 44100);
    writeWAVHeader(salida, hSalida);
    writeSamplesMono(salida, seno);
    fclose(salida);
  } else if (argv[1][1] == 'b') {
    /*Generar filtro parabajas ideal y guardarlo en el archivo*/
    salida = fopen(argv[2], "w+b");
    ArrayDouble pasabajas = obtenerMuestrasPasabajasIdeal(32, 1000, 2000 * 2.5);
    WAVHeader hSalida = newWAVHeader(MONO, pasabajas.length, 44100);
    // pasabajas = mapArrayDouble(pasabajas, -1, 1);
    writeWAVHeader(salida, hSalida);
    writeSamplesMono(salida, pasabajas);
    printArrayDouble(pasabajas);
    fclose(salida);
  } else {
    printf("Opción no válida \n", argv[0]);
  }
}
