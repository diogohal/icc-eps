#include <stdio.h>
#include <stdlib.h>

float lagrange(float x, int n, float *x_values, float *y_values) {
    float result = 0.0;

    for (int i = 0; i < n; i++) {
        float term = y_values[i];
        for (int j = 0; j < n; j++) {
            if (j != i) {
                term *= (x - x_values[j]) / (x_values[i] - x_values[j]);
            }
        }
        result += term;
    }

    return result;
}

float *calculate_differences(int n, float *x_values, float *y_values, float *differences) {
    for (int j = 1; j < n; j++) {
        for (int i = n - 1; i >= j; i--) {
            differences[i] = (differences[i] - differences[i - 1]) /
                             (x_values[i] - x_values[i - j]);
           
        }
        printf("\nDiferenca %d: %f", j, differences[j]);
    }
    return differences;
}

float newton(float x, int n, float *x_values, float *y_values) {
    float *differences = malloc(n * sizeof(float));
    if (differences == NULL) {
        perror("Erro ao alocar memória");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        differences[i] = y_values[i];
    }

    calculate_differences(n, x_values, y_values, differences);
    float result = differences[0];
    float term = 1.0;

    for (int i = 1; i < n; i++) {
        term *= (x - x_values[i - 1]);
        result += differences[i] * term;
        printf("\nTermo: %f", result);
    }
    free(differences); 

    return result;
}

int main() {
    float x_values[4] = {20, 25, 30, 35};
    float y_values[4] = {0.991, 0.9985, 0.9983, 0.9982};
    float result = lagrange(2.5, 4, x_values, y_values);
    float result2 = newton(2.5, 4, x_values, y_values);
    printf("\nRESULT = %f\n", result);
    printf("RESULT 2 = %f\n", result2);
    return 0;
}