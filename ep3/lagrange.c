#include <stdio.h>
#include <stdlib.h>

float lagrange(float xe, int n, float *x, float *y) {
    float resultado = 0.0;

    for (int i = 0; i < n; i++) {
        float mult = y[i];
        for (int j = 0; j < n; j++) {
            if (j != i) {
                mult *= (xe - x[j]) / (x[i] - x[j]);
            }
        }
        resultado += mult;
    }

    return resultado;
}

float *calcular_d(int n, float *x, float *y, float *diff) {
    for (int j = 1; j < n; j++) {
        for (int i = n - 1; i >= j; i--) {
            diff[i] = (diff[i] - diff[i - 1]) /
                             (x[i] - x[i - j]);
           
        }
    }
    return diff;
}

float newton(float xe, int n, float *x, float *y) {
    float *diff = malloc(n * sizeof(float));
    if (diff == NULL) {
        perror("Erro ao alocar memória");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        diff[i] = y[i];
    }

    calcular_d(n, x, y, diff);
    
    float resultado = diff[0];
    float mult = 1.0;

    for (int i = 1; i < n; i++) {
        mult *= (xe - x[i - 1]);
        resultado += diff[i] * mult;
    }
    free(diff); 

    return resultado;
}

int main(int argc, char** argv) {
    int n;
    float xe;
    scanf("%d", &n);
    float x[n];
    float y[n];

    xe = atoi(argv[1]);

    for(int i = 0; i < n; i++){
        scanf("%f %f", &x[i], &y[i]);
    }
    // float x[4] = {20, 25, 30, 35};
    // float y[4] = {0.9991, 0.9985, 0.9983, 0.9982};
    float resultado = lagrange(xe, n, x, y);
    float resultado2 = newton(xe, n, x, y);
    printf("\nresultado = %f\n", resultado);
    printf("resultado 2 = %f\n", resultado2);
    return 0;
}