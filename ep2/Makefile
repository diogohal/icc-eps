CFLAGS = -O3 -mavx -march=native

all: perfEG.o matriz.o
	gcc $(CFLAGS) perfEG.o matriz.o -o perfEG

matriz.o: matriz.c
	gcc $(CFLAGS) matriz.c -c matriz.o

perfEG.o: perfEG.c
	gcc $(CFLAGS) perfEG.c -c perfEG.o

run: all
	./perfEG

clean:
	rm -f *.o

purge: clean
	rm -f perfEG