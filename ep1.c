#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdint.h>
#include <float.h>

void calcula(float num1, float num2, char op) {
    printf("======= %1.9e %c %1.9e =======\n", num1, op, num2);
    float num1_next = nextafterf(num1, DBL_MAX);
    float num1_before = nextafterf(num1, -DBL_MAX);
    printf("%1.9e   %1.9e\n", num1_next, num1_before);

    float num2_next = nextafterf(num2, DBL_MAX);
    float num2_before = nextafterf(num2, -DBL_MAX);
    printf("%1.9e   %1.9e\n", num2_next, num2_before);

    if(op == '+') {
        float sum_minor = num1_before + num2_before;
        float sum_max = num1_next + num2_next;
        printf("Intervalo = [%1.9e, %1.9e]\n", sum_minor, sum_max);
    }
    else if(op == '-') {
        float sub_minor = num1_before - num2_before;
        float sub_max = num1_next - num2_next;
        printf("Intervalo = [%1.9e, %1.9e]\n", sub_minor, sub_max);

    }
    else if(op == '*'){
        float multi[4] = {num1_before * num2_before, num1_before * num2_next, num1_next * num2_before, num1_next * num2_next};
        float menor = multi[0];
        float maior = multi[0];
        printf("%1.8e\n", num1_before * num2_before);
        printf("%1.8e\n", num1_before * num2_next);
        printf("%1.8e\n", num1_next * num2_before);
        printf("%1.8e\n", num1_next * num2_next);
        for(int i = 1; i < 4; i++){
            printf("MULTI: %1.8e\n", multi[i]);
            if (menor > multi[i])
                menor = multi[i];
            if (maior < multi[i])
                maior = multi[i];
        }
        printf("Intervalo = [%1.8e, %1.8e]\n", menor, maior);
    }

}

int main() {
    
    float teste = 2.347e-40f;
    float teste2 = 0.001f;
    calcula(teste, teste2, '*');

    return 0;
}
