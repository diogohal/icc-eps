# PROGRAMA
        PROG = matmult
        OBJS = $(PROG).o matriz.o

# Compilador
           CC = gcc -Wall

       CFLAGS = -O3 -mavx -march=native
       LFLAGS = -lm

# Lista de arquivos para distribuição
DISTFILES = *.c *.h README.md Makefile perfctr
DISTDIR = `basename ${PWD}`

.PHONY: all debug clean purge dist

%.o: %.c %.h
	$(CC) $(CFLAGS) -DLIKWID_PERFMON -I${LIKWID_INCLUDE} -c $<

all: $(PROG)

debug:         CFLAGS += -g -D_DEBUG_
debug:         $(PROG)

$(PROG): $(OBJS) 
	$(CC) -o $(PROG) $(OBJS) $ -L${LIKWID_LIB} -llikwid $(CFLAGS)


clean:
	@echo "Limpando ...."
	@rm -f *~ *.bak *.tmp core 

purge:   clean
	@echo "Faxina ...."
	@rm -f  $(PROG) *.o a.out $(DISTDIR) $(DISTDIR).tar
	@rm -f *.png marker.out

dist: purge
	@echo "Gerando arquivo de distribuição ($(DISTDIR).tar) ..."
	@ln -s . $(DISTDIR)
	@tar -cvf $(DISTDIR).tar $(addprefix ./$(DISTDIR)/, $(DISTFILES))
	@rm -f $(DISTDIR)

