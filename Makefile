LIBS_SOURCES := $(wildcard libs/*.c) # Busco todos los archivos .c en lib/
LIBS_OBJECTS := $(LIBS_SOURCES:.c=.o) # Reemplazo las extensiones .c a .o

all: muestreo recuperacion multiplicacion filtro

muestreo: clibs
	gcc -Wall -c muestreo.c -o muestreo.o -w -lm
	gcc -Wall muestreo.o $(LIBS_OBJECTS) -o muestreo -lm

recuperacion: clibs
	gcc -Wall -c recuperacion.c -o recuperacion.o -w -lm
	gcc -Wall recuperacion.o $(LIBS_OBJECTS) -o recuperacion -lm

multiplicacion: clibs
	gcc -Wall -c multiplicacion.c -o multiplicacion.o -w -lm
	gcc -Wall multiplicacion.o $(LIBS_OBJECTS) -o multiplicacion -lm

filtro: clibs 
	gcc -Wall -c filtro.c -o filtro.o -w -lm
	gcc -Wall filtro.o $(LIBS_OBJECTS) -o filtro -lm

clibs: $(LIBS_OBJECTS)
	cd libs; make

clean:
	rm -f *.o muestreo recuperacion multiplicacion
	cd libs; make clean