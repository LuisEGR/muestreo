#include <stdio.h>
#include "libs/dsp.h"
#include "libs/wav.h"

/*
* Muestreo y recuperación de una señal
* haciendo convolución con un filtro pasabajas
*/

int main(int argc, char *argv[]) {
  FILE *entrada, *salida;
  MuestraEstereo muestra_estereo;
  MuestraMono muestra_mono;
  char *gaes = "Generar archivo estéreo con ";

  if (argc < 4 || argv[1][0] != '-') {
    printf("Uso: %s <opcion> <entrada.wav> <salida.wav> \n", argv[0]);
    printf("Opciones disponibles:\n");
    printf("\t-1 \t %s señal original y magnitud de la TDF\n", gaes);
    printf("\t-2 \t %s parte real y parte imaginaria de la TDF\n", gaes);
    printf("\t-3 \t %s con la magnitud y la fase de la TDF\n", gaes);
    printf("\t-4 \t realizar TDF Inversa sobre la salida de opción 2, retorna MONO\n\n");
    printf("\t-p \t Imprimir TDF\n\n", gaes);
    return 0;
  }

  entrada = fopen(argv[2], "rb");
  salida = fopen(argv[3], "w+b");
  WAVHeader hEntrada = readHeaderWAV(entrada);
  WAVHeader hSalida;
  printHeaderWAV(hEntrada, argv[2]);
  

  if (argv[1][1] == '1') {
    /* Señal original y magnitud de la TDF */
    printf("\n Señal original y magnitud de la TDF\n");
    ArrayComplex tdf = transformadaFourier(entrada, hEntrada);
    hSalida = newWAVHeader(2, tdf.length, hEntrada.SampleRate);
    writeWAVHeader(salida, hSalida);
    ArrayDouble magnitudTdf = getMagFromArrayComplex(tdf);

    for (int i = 0; i < magnitudTdf.length; i++) {
      MuestraMono muestra_mono = readSampleMono(entrada, i);

      muestra_estereo =
          newMuestraEstereo(muestra_mono.muestra, magnitudTdf.items[i]);
      writeSampleEstereo(salida, muestra_estereo);
    }

    // printArrayComplex(tdf);
    printf("\nMagnitud: \n");
    printArrayDouble(magnitudTdf);

    printf("\nArchivo %s generado!\n", argv[3]);

  } else if (argv[1][1] == '2') {
    /*  Se genera archivo estéreo con la parte real en el
   *   canal izquierdo y la parte real en el canal derecho */
    printf("\n Parte real e imaginaria de la TDF\n");
    ArrayComplex tdf = transformadaFourier(entrada, hEntrada);
    hSalida = newWAVHeader(2, tdf.length, hEntrada.SampleRate);
    writeWAVHeader(salida, hSalida);
    for (int i = 0; i < tdf.length; i++) {
      MuestraEstereo mE =
          newMuestraEstereo(tdf.items[i].real, tdf.items[i].imag);
      writeSampleEstereo(salida, mE);
    }
    printArrayComplex(tdf);

    printf("\nArchivo %s generado!\n", argv[3]);

  } else if (argv[1][1] == '3') {
    /*  Se genera archivo estéreo con la magnitud en el
    *   canal izquierdo y la fase en el canal derecho */
    printf("\n Magnitud y fase de la TDF\n");
    ArrayComplex tdf = transformadaFourier(entrada, hEntrada);
    hSalida = newWAVHeader(2, tdf.length, hEntrada.SampleRate);
    writeWAVHeader(salida, hSalida);

    ArrayDouble magnitudTDF = getMagFromArrayComplex(tdf);
    ArrayDouble faseTDF = getAngFromArrayComplex(tdf);
    // faseTDF = mapArrayDouble(faseTDF, -1, 1);
    printf("\nFase:");
    printArrayDouble(faseTDF);

    printf("\nMagnitud:");
    printArrayDouble(magnitudTDF);
    for (int i = 0; i < tdf.length; i++) {
      muestra_estereo.left = magnitudTDF.items[i];
      muestra_estereo.right = faseTDF.items[i];
      writeSampleEstereo(salida, muestra_estereo);
    }
    printf("\nArchivo %s generado!\n", argv[3]);
  } else if (argv[1][1] == '4') {
    printf("\nRealizando TDF Inversa de un archivo estéreo");
    printf("\nSe toma el canal derecho como la parte REAL");

    int numMuestras = hEntrada.Subchunk2Size / (hEntrada.BitsPerSample / 8);
    ArrayComplex muestrasTDF = newArrayComplex(numMuestras);
    for (int i = 0; i < numMuestras; i++){
      MuestraEstereo m = readSampleEstereo(entrada, i);
      ComplexNumber muestra = newComplexNumber(m.left, m.right);
      muestrasTDF.items[i] = muestra;
    }
    // printArrayComplex(muestrasTDF);
    ArrayDouble tdfi = transformadaFourierInversa(muestrasTDF);
    // printArrayDouble(tdfi);
    printf("Size: %d\n", tdfi.length);
    // printHeaderWAV(hEntrada, "Entrada");
    hSalida = newWAVHeader(1, tdfi.length, hEntrada.SampleRate);
    writeWAVHeader(salida, hSalida);
    writeSamplesMono(salida, tdfi);


  } else if (argv[1][1] == 'p') {
    // printArrayComplex(tdf);
  } else {
    printf("Opción no válida \n", argv[0]);
  }
  fclose(salida);
  fclose(entrada);
  printHeaderWAV(hSalida, argv[3]);
}
