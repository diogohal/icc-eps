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
    intervalo_t aux;
    if (inter2.min == 0.0 || inter2.max == 0.0) {
        aux.min = -INFINITY;
        aux.max = INFINITY;
    } else {
        aux.min = 1 / inter2.max;
        aux.max = 1 / inter2.min;
        aux = multiplica(inter1, aux);
    }
    return aux;
}

intervalo_t power(intervalo_t interval, int p) {
    intervalo_t result;
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
    return result;
}
