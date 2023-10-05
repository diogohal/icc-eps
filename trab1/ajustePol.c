#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matriz.h"
#include "intervaloOp.h"

int main(){  
    int n, k, returnScanf;
    returnScanf = fscanf(stdin, "%d %d", &n, &k);

    pontos_t *pontos = malloc(sizeof(pontos_t)*k);
    
    for(int i=0; i<k; i++) {
        returnScanf = fscanf(stdin, "%lf %lf", &pontos[i].x, &pontos[i].y);
    }
    
    matriz_t *SL = criaMatriz(n+1);
    criaSL(pontos, SL, k, n);
    printf("Matriz criada!\n");
    printaMatriz(SL);

    printf("\nEliminação de Gauss!\n");
    eliminacaoGauss(SL);
    printaMatriz(SL);
    retrossubs(SL);
    
    printf("\nRespostas!\n");
    for(int i=0; i<SL->tam; i++) {
        printf("a%d = ", i);
        printaIntervalo(&SL->X[i]);
        printf("\n");
    }

    intervalo_t* residuo = calculaResiduo(SL, pontos, k);
    printf("\nResíduos!\n");
    for(int i=0; i<k; i++) {
        printf("r%d = ", i);
        printaIntervalo(&residuo[i]);
        printf("\n");
    }


    libera(SL, residuo);
}