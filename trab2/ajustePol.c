#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#include "intervaloOp.h"
#include "likwid.h"
#include "matriz.h"

double timestamp(void) {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return ((double)(tp.tv_sec + tp.tv_usec / 1000000.0)) * 1000;
}

int main() {
    LIKWID_MARKER_INIT;
    double start, stop, tgeraSL, tsolSL, tResiduo = 0.0;
    long long int n, k;
    fscanf(stdin, "%lld %lld", &n, &k);

    pontos_t *pontos = malloc(sizeof(pontos_t) * k);

    for (long long int i = 0; i < k; i++) {
        fscanf(stdin, "%lf %lf", &pontos[i].x, &pontos[i].y);
    }

    matriz_t *SL = criaMatriz(n + 1);
    start = timestamp();
    LIKWID_MARKER_START("geraSL");
    criaSL(pontos, SL, k, n);
    LIKWID_MARKER_STOP("geraSL");
    stop = timestamp();
    tgeraSL = stop - start;

    start = timestamp();
    LIKWID_MARKER_START("solSL");
    eliminacaoGauss(SL);
    retrossubs(SL);
    LIKWID_MARKER_STOP("solSL");
    stop = timestamp();
    tsolSL = stop - start;
    // for (int i = 0; i < SL->tam; i++) {
    //     printaIntervalo(&SL->X[i]);
    //     printf(" ");
    // }
    printf("\n");

    start = timestamp();
    intervalo_t *residuo = calculaResiduoNaive(SL, pontos, k);
    stop = timestamp();
    tResiduo = stop - start;
    // for (int i = 0; i < k; i++) {
    //     printaIntervalo(&residuo[i]);
    //     printf(" ");
    // }
    // printf("\n%f\n", tResiduo);

    printf("\n%f\n", tgeraSL);
    // printf("%f\n", tsolSL);
    LIKWID_MARKER_CLOSE;

    libera(SL, residuo);
}
