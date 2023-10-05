#include <fenv.h>
#include <float.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intervaloOp.h"

intervalo_t multiplica(intervalo_t inter1, intervalo_t inter2) {
    intervalo_t res;
    fesetround(FE_DOWNWARD);
    res.min = fminf(fminf(inter1.min * inter2.min, inter1.min * inter2.max),
                    fminf(inter1.max * inter2.min, inter1.max * inter2.max));
    fesetround(FE_UPWARD);
    res.max = fmaxf(fmaxf(inter1.min * inter2.min, inter1.min * inter2.max),
                    fmaxf(inter1.max * inter2.min, inter1.max * inter2.max));
    return res;
}

intervalo_t soma(intervalo_t inter1, intervalo_t inter2) {
    intervalo_t res;
    fesetround(FE_DOWNWARD);
    res.min = inter1.min + inter2.min;
    fesetround(FE_UPWARD);
    res.max = inter1.max + inter2.max;
    return res;
}

intervalo_t subtracao(intervalo_t inter1, intervalo_t inter2) {
    intervalo_t res;
    fesetround(FE_DOWNWARD);
    res.min = inter1.min - inter2.min;
    fesetround(FE_UPWARD);
    res.max = inter1.max - inter2.max;
    return res;
}

intervalo_t divisao(intervalo_t inter1, intervalo_t inter2) {
    intervalo_t result;
    double aux;
    if (inter2.min == 0.0 || inter2.max == 0.0) {
        result.min = -INFINITY;
        result.max = INFINITY;
    } else {
        result.min = 1 / inter2.max;
        result.max = 1 / inter2.min;
        result = multiplica(inter1, result);
    }

    if(result.max < result.min) {
        aux = result.min;
        result.min = result.max;
        result.max = aux;
        printf("entrou!\n");
    }
    return result;
}

intervalo_t power(intervalo_t interval, int p) {
    intervalo_t result;
    double aux = 0;
    if (p == 0) {
        result.min = 1;
        result.max = 1;
    } else if (p % 2 == 1) {
        result.min = pow(interval.min, p);
        result.max = pow(interval.max, p);
    } else if (p % 2 == 0 && interval.min >= 0) {
        result.min = pow(interval.min, p);
        result.max = pow(interval.max, p);
    } else if (p % 2 == 0 && interval.max < 0) {
        result.min = pow(interval.max, p);
        result.max = pow(interval.min, p);
    } else if (p % 2 == 0 && interval.min < 0 && interval.max >= 0) {
        result.min = 0;
        result.max = fmax(pow(interval.min, p), pow(interval.max, p));
    }

    if(result.max < result.min) {
        aux = result.min;
        result.min = result.max;
        result.max = aux;
    }

    return result;
}

void transformaIntervalo(intervalo_t *intervalo, double num) {
    intervalo->min = nextafterf(num, -INFINITY);
    intervalo->max = nextafterf(num, +INFINITY);
}

void printaIntervalo(intervalo_t* intervalo) {
    printf("[%1.8e, %1.8e]", intervalo->min, intervalo->max);
}