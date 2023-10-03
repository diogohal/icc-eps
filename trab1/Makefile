CFLAGS = -O3 -mavx -march=native -lm

all: ajustePol.o intervaloOp.o matriz.o
	gcc -o ajustePol ajustePol.o matriz.o intervaloOp.o $(CFLAGS) 

matriz.o: matriz.c
	gcc $(CFLAGS) -c matriz.c

intervaloOp.o: intervaloOp.c
	gcc $(CFLAGS) -c intervaloOp.c

ajustePol.o: ajustePol.c
	gcc $(CFLAGS) -c ajustePol.c

run: all
	./ajustePol

clean:
	rm -f *.o

purge: clean
	rm -f ajustePol
