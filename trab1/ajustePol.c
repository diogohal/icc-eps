#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matriz.h"
#include "intervaloOp.h"

struct xy {
    double x;
    double y;
};
typedef struct xy xy_t;

// void criaSL(xy_t *xy, matriz_t *SL, int p, int n){
//     for(int i = 0; i < p+1; i++){
//         for(int j = 0; j < p+1; j++){
//             for(int k = 0; k < n; k++)
//                 SL->A[i][j] += pow(xy[k].x, i) * pow(xy[k].x, j);
//         }
//         for(int k = 0; k < n; k++)
//             SL->B[i] += xy[k].y * pow(xy[k].x, i);
//     }
// }

int main(){
    // int n, k;
    // fscanf(stdin, "%d %d", &n, &k);

    // xy_t *pontos = malloc(sizeof(xy_t)*n);
    
    // for(int i=0; i<n; i++) {
    //     fscanf(stdin, "%lf %lf", &pontos[i].x, &pontos[i].y);
    // }
    
    // criaSL(pontos, SL, k, n);
    // printaMatriz(SL);
    // libera(SL);

    matriz_t *SL = criaMatriz(2);
     if (!SL) {
        printf("Falha na alocação de memória.\n");
        return 1;
    }
    printaMatriz(SL);
    libera(SL);
}