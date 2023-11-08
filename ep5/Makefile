all: integra.o utils.o
	gcc integra.o utils.o -o integra  

integra.o: integra.c
	gcc -c integra.c

utils.o: utils.c
	gcc -c utils.c

clean:
	rm -f *.o

purge: clean
	rm -f integra
