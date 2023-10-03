#ifndef MATRIZ_H
#define MATRIZ_H
#include "intervaloOp.h"

typedef struct matriz {
    intervalo_t **A;
    intervalo_t *B;
    intervalo_t *X;
    intervalo_t *residuo;
    int tam;
} matriz_t;

typedef struct indice {
    int i;
    int j;
} indice_t;

matriz_t *criaMatriz(int n);
void recebeEntrada(matriz_t *matriz);
void printaMatriz(matriz_t *matriz);
void retrossubs(matriz_t *matriz);
void eliminacaoGauss(matriz_t *matriz);
void eliminacaoGaussSemMultiplicador(matriz_t *matriz);
void eliminacaoGaussSemPivoteamento(matriz_t *matriz);
void calculaResiduo(matriz_t *matriz);
void libera(matriz_t *matriz);
void copiaMatriz(matriz_t *m1, matriz_t *m2);

#endif
