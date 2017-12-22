LIBS_SOURCES := $(wildcard libs/*.c) # Busco todos los archivos .c en lib/
LIBS_OBJECTS := $(LIBS_SOURCES:.c=.o) # Reemplazo las extensiones .c a .o

all: multiplicacion
multiplicacion: clibs
	gcc -Wall -c multiplicacion.c -o multiplicacion.o -w -lm
	gcc -Wall multiplicacion.o $(LIBS_OBJECTS) -o multiplicacion -lm

# recuperacion: clibs
# 	gcc -Wall -c recuperacion.c -o recuperacion.o -w -lm
# 	gcc -Wall recuperacion.o $(LIBS_OBJECTS) -o recuperacion -lm

# multiplicacion: clibs
# 	gcc -Wall -c multiplicacion.c -o multiplicacion.o -w -lm
# 	gcc -Wall multiplicacion.o $(LIBS_OBJECTS) -o multiplicacion -lm

# filtro: clibs 
# 	gcc -Wall -c filtro.c -o filtro.o -w -lm
# 	gcc -Wall filtro.o $(LIBS_OBJECTS) -o filtro -lm

# tren: clibs
# 	gcc -Wall -c tren.c -o tren.o -w -lm 
# 	gcc -Wall tren.o $(LIBS_OBJECTS) -o tren -lm


clibs: $(LIBS_OBJECTS)
	cd libs; make

clean:
	rm -f *.o tren recuperacion multiplicacion filtro
	cd libs; make clean