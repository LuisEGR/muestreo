LIBS_SOURCES := $(wildcard libs/*.c) # Busco todos los archivos .c en lib/
LIBS_OBJECTS := $(LIBS_SOURCES:.c=.o) # Reemplazo las extensiones .c a .o

all: muestreo recuperacion multiplicacion filtro tren tdf

muestreo: clibs
	gcc -Wall -c muestreo.c -o muestreo.o -w -lm
	gcc -Wall muestreo.o $(LIBS_OBJECTS) -o muestreo -lm

recuperacion: clibs
	gcc -Wall -c recuperacion.c -o recuperacion.o -w -lm
	gcc -Wall recuperacion.o $(LIBS_OBJECTS) -o recuperacion -lm

multiplicacion: clibs
	gcc -Wall -c multiplicacion.c -o multiplicacion.o -w -lm
	gcc -Wall multiplicacion.o $(LIBS_OBJECTS) -o multiplicacion -lm

tdf: clibs
	gcc -Wall -c tdf.c -o tdf.o -w -lm
	gcc -Wall tdf.o $(LIBS_OBJECTS) -o tdf -lm

filtro: clibs 
	gcc -Wall -c filtro.c -o filtro.o -w -lm
	gcc -Wall filtro.o $(LIBS_OBJECTS) -o filtro -lm

tren: clibs
	gcc -Wall -c tren.c -o tren.o -w -lm 
	gcc -Wall tren.o $(LIBS_OBJECTS) -o tren -lm

clibs: $(LIBS_OBJECTS)
	cd libs; make

clean:
	rm -f *.o muestreo recuperacion multiplicacion filtro
	cd libs; make clean