#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "matriz.h"
#include "likwid.h"
#define N 3

int main() {

    LIKWID_MARKER_INIT;
    int tam = 0;
    int returnScanf = 0;
    returnScanf = scanf("%d", &tam);

    matriz_t *matriz = criaMatriz(tam);
    recebeEntrada(matriz);

    printf("===== MATRIZ DE ENTRADA =====");
    printaMatriz(matriz);
    printf("\n");

    /*
    3
    3 2 4 1
    1 1 2 2
    4 3 -2 3

    4
    4 -1 0 -1 3
    -1 4 -1 0 6
    0 -1 4 -1 1
    -1 0 -1 4 12

    4
    -1 4 -1 0 6
    2 -1 4 -1 1 
    4 -1 0 -1 3 
    -1 0 -1 4 12
    */

    printf("===== ELIMINAÇÃO DE GAUSS =====\n");
    
    LIKWID_MARKER_START("marker-name");
    eliminacaoGaussSemPivoteamento(matriz);
    LIKWID_MARKER_STOP("marker-name");

    printf("===== SOLUÇÕES =====\n");
    retrossubs(matriz);
    calculaResiduo(matriz);

    printf("Soluções\n");
    for(int i=0; i<matriz->tam; i++) {
        printf("%f ", matriz->X[i]);
    }
    printf("\n");

    printf("Residuo\n");
    for (int i = 0; i<matriz->tam; i++) {
        printf("%f ", matriz->residuo[i]);
    }
    printf("\n");
    LIKWID_MARKER_CLOSE;
}
