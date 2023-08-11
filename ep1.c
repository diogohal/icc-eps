#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdint.h>
#include <float.h>

void calcula(float num1, float num2, char op) {
    printf("======= %1.9e %c %1.9e =======\n", num1, op, num2);
    float num1_next = nextafterf(num1, DBL_MAX);
    float num1_before = nextafterf(num1, DBL_MIN);
    printf("%1.9e   %1.9e\n", num1_next, num1_before);

    float num2_next = nextafterf(num2, DBL_MAX);
    float num2_before = nextafterf(num2, DBL_MIN);
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

}

int main() {
    
    float teste = 2.0;
    calcula(teste, teste+1, '+');

    return 0;
}
