#include <stdio.h>
#include <stdlib.h>    /* exit, malloc, calloc, etc. */
#include <string.h>
#include <getopt.h>    /* getopt */
#include <time.h>
#include <sys/time.h>

#include "matriz.h"
// #include "likwid.h"


/**
 * Exibe mensagem de erro indicando forma de uso do programa e termina
 * o programa.
 */

static void usage(char *progname)
{
  fprintf(stderr, "Forma de uso: %s [ <ordem> ] \n", progname);
  exit(1);
}

double timestamp(void) {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return ((double)(tp.tv_sec + tp.tv_usec / 1000000.0)) * 1000;
}



/**
 * Programa principal
 * Forma de uso: matmult [ -n <ordem> ]
 * -n <ordem>: ordem da matriz quadrada e dos vetores
 *
 */

int main (int argc, char *argv[]) 
{
  int n=DEF_SIZE;
  double start, stop, tMatVet, tMatMat;
  
  MatRow mRow_1, mRow_2, resMat;
  Vetor vet, res;
  
  /* =============== TRATAMENTO DE LINHA DE COMANDO =============== */

  if (argc < 2)
    usage(argv[0]);

  n = atoi(argv[1]);
  
  /* ================ FIM DO TRATAMENTO DE LINHA DE COMANDO ========= */
 
  srandom(20232);
      
  res = geraVetor (n, 0); // (real_t *) malloc (n*sizeof(real_t));
  resMat = geraMatRow(n, n, 1);
    
  mRow_1 = geraMatRow (n, n, 0);
  mRow_2 = geraMatRow (n, n, 0);

  vet = geraVetor (n, 0);

  if (!res || !resMat || !mRow_1 || !mRow_2 || !vet) {
    fprintf(stderr, "Falha em alocação de memória !!\n");
    liberaVetor ((void*) mRow_1);
    liberaVetor ((void*) mRow_2);
    liberaVetor ((void*) resMat);
    liberaVetor ((void*) vet);
    liberaVetor ((void*) res);
    exit(2);
  }
    
#ifdef _DEBUG_
    prnMat (mRow_1, n, n);
    prnMat (mRow_2, n, n);
    prnVetor (vet, n);
    printf ("=================================\n\n");
#endif 
  start = timestamp();
  multMatVet (mRow_1, vet, n, n, res);
  stop = timestamp();
  tMatVet = stop - start;

  start = timestamp();
  multMatMat (mRow_1, mRow_2, n, resMat);
  stop = timestamp();
  tMatMat = stop - start;

  printf("Tempo matriz vetor: %f\n", tMatVet);
  printf("Tempo matriz matriz: %f\n", tMatMat);

#ifdef _DEBUG_
    prnVetor (res, n);
    prnMat (resMat, n, n);
#endif /* _DEBUG_ */

  liberaVetor ((void*) mRow_1);
  liberaVetor ((void*) mRow_2);
  liberaVetor ((void*) resMat);
  liberaVetor ((void*) vet);
  liberaVetor ((void*) res);

  return 0;
}

