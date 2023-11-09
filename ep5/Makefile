all: integra.o
	gcc integra.o -o integra  

integra.o: integra.c
	gcc -c integra.c

clean:
	rm -f *.o

purge: clean
	rm -f integra
