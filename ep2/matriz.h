#ifndef MATRIZ_H
#define MATRIZ_H

typedef struct matriz {
    double **matriz;
    double residuo;
} matriz_t;

matriz_t *criaMatriz(int n);

#endif