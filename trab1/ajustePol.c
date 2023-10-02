#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matriz.h"

struct xy {
    float x;
    float y;
};
typedef struct xy xy_t;

void criaSL(xy_t *xy, float **SL, float *indep, int p, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < p; k++)
                SL[i][j] += pow(xy[k].x, i) * pow(xy[k].x, j);
        }
        for(int k = 0; k < p; k++)
            indep[i] += xy[k].y * pow(xy[k].x, i);
    }
}

int main(){
    int n, p;
    matriz_t *SL = criaMatriz(n);

    return 0;
}