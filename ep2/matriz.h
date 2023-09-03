#ifndef MATRIZ_H
#define MATRIZ_H

typedef struct matriz {
    double **A;
    double *B;
    double *X;
    double *residuo;
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
void calculaResiduo(matriz_t *matriz);

#endif