#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "matriz.h"

matriz_t *criaMatriz(int n) {
    matriz_t * matriz = malloc(sizeof(matriz_t));
    if(!matriz)
        return NULL;

    matriz->matriz = malloc(sizeof(double*)*n);
    if(!matriz->matriz)
        return NULL;

    for(int i=0; i<n; i++) {
        matriz->matriz[i] = malloc(sizeof(double)*n);
        if(!matriz->matriz[i])
            return NULL;
    }    
    
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            matriz->matriz[i][j] = 0;
        }
    }
    matriz->residuo = 0;

    return matriz;

}