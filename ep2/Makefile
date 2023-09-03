CFLAGS = -O3 -mavx -march=native

all: perfEG.o matriz.o
	gcc $(CFLAGS) perfEG.o matriz.o -o perfEG

matriz.o: matriz.c
	gcc $(CFLAGS) -c matriz.c

perfEG.o: perfEG.c
	gcc $(CFLAGS) -c perfEG.c

run: all
	./perfEG

clean:
	rm -f *.o

purge: clean
	rm -f perfEG