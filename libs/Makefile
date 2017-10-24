SRCS	= 	$(wildcard *.c) #Buscar todos los archivos fuente .c
OBJS	= 	$(SRCS:%.c=%.o)
CFLAGS	=	-Wall -lm

all: $(OBJS)

%.o:%.c
	gcc -c $< -o $@  $(CFLAGS)

clean: 
	rm -f *.o