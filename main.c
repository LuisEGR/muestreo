#include <stdio.h>
#include "libs/dsp.h"
#include "libs/wav.h"
#include "libs/filtros.h"

/*
* Muestreo y recuperación de una señal
* haciendo convolución con un filtro pasabajas
*/

int main(int argc, char *argv[]) {
  FILE *entrada, *salida;

  if(argc < 3 || argv[1][0] != '-'){
    printf("Uso: %s <opcion> <entrada.wav> <salida.wav> \n", argv[0]);
    printf("Opciones disponibles:\n");
    printf("\t -m \t Muestrear una señal\n");
    printf("\t -r \t Recuperar una señal muestreada\n");
    printf("\t -g \t Generar una señal seno de prueba\n\n");
    return 0;
  }

  if(argv[1][1] == 'r'){
    /*Recuperación de señal muestreada - Convolución*/
    printf("\nRecuperando señal muestreada de %s\n", argv[2]);   
    
    entrada = fopen(argv[2], "rb");
    salida = fopen(argv[3], "w+b");

    WAVHeader hEntrada = readHeaderWAV(entrada);
    ArrayDouble filtro = obtenerMuestrasPasabajasIdeal(40, 1000, 44100);
    printf("\nFiltro pasa bajas:");
    printArrayDouble(filtro);

    ArrayDouble conv = convolucionPorFormula(entrada, hEntrada,filtro);
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
    

  }else if(argv[1][1] == 'm'){
    /* Muestreo de una señal */
    printf("\nMuestreando señal de %s\n", argv[2]);   
    float duracion;
    entrada = fopen(argv[2], "rb");
    salida = fopen(argv[3], "w+b");

    WAVHeader hEntrada = readHeaderWAV(entrada);
    duracion = getDuracionWAV(hEntrada);
    printf("Duración: %f", getDuracionWAV(hEntrada));

    ArrayDouble tren = crearTrenDeImpulsos(duracion, hEntrada.SampleRate, hEntrada.SampleRate / 2);
    // printArrayDouble(tren);

    WAVHeader hSalida = newWAVHeader(1, tren.length, hEntrada.SampleRate);
    writeWAVHeader(salida, hSalida);

    for (int i = 0; i < tren.length; i++) {
      MuestraMono m = readSampleMono(entrada, i);  // Se lee una muestra
      m.muestra *= tren.items[i];   // Se multiplica por el tren
      writeSampleMono(salida, m);  // Se escribe en la salida
    }

    printHeaderWAV(hEntrada);
    printHeaderWAV(hSalida);
    fclose(salida);
    fclose(entrada);
    printf("\nSeñal muestreada guardada en %s\n", argv[3]);   
    

  }else if(argv[1][1] == 'g'){
    if(argc != 3){
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
  }else{
    printf("Opción no válida \n", argv[0]);
  }
 
  
}
