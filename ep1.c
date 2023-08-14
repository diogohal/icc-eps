#include <fenv.h>
#include <float.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct intervalo {
    float min;
    float max;
};
typedef struct intervalo intervalo_t;

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
    res.min = inter1.min + inter2.min;
    res.max = inter1.max + inter2.max;
    return res;
}

intervalo_t subtracao(intervalo_t inter1, intervalo_t inter2) {
    intervalo_t res;
    res.min = inter1.min - inter2.min;
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

intervalo_t performOperation(intervalo_t a, char operator, intervalo_t b) {
    intervalo_t result;
    switch (operator) {
        case '+':
            result = soma(a, b);
            break;
        case '-':
            result = subtracao(a, b);
            break;
        case '*':
            result = multiplica(a, b);
            break;
        case '/':
            result = divisao(a, b);
            break;
    }
    return result;
}

// void calcula(float num1, float num2, char op) {
//     printf("======= %1.8e %c %1.8e =======\n", num1, op, num2);
//     float num1_next = nextafterf(num1, INFINITY);
//     float num1_before = nextafterf(num1, -INFINITY);
//     printf("%1.9e   %1.9e\n", num1_next, num1_before);

//     float num2_next = nextafterf(num2, INFINITY);
//     float num2_before = nextafterf(num2, -INFINITY);
//     printf("%1.9e   %1.9e\n", num2_next, num2_before);

//     if (op == '+') {
//         float sum_minor = num1_before + num2_before;
//         float sum_max = num1_next + num2_next;
//         printf("Intervalo = [%1.9e, %1.9e]\n", sum_minor, sum_max);
//     } else if (op == '-') {
//         float sub_minor = num1_before - num2_before;
//         float sub_max = num1_next - num2_next;
//         printf("Intervalo = [%1.9e, %1.9e]\n", sub_minor, sub_max);

//     } else if (op == '*') {
//         // float multi[4] = {num1_before * num2_before, num1_before *
//         num2_next,
//         // num1_next * num2_before, num1_next * num2_next}; float menor =
//         // multi[0]; float maior = multi[0]; printf("%1.8e\n", num1_before *
//         // num2_before); printf("%1.8e\n", num1_before * num2_next);
//         // printf("%1.8e\n", num1_next * num2_before);
//         // printf("%1.8e\n", num1_next * num2_next);
//         // for(int i = 1; i < 4; i++){
//         //     printf("MULTI: %1.8e\n", multi[i]);
//         //     if (menor > multi[i])
//         //         menor = multi[i];
//         //     if (maior < multi[i])
//         //         maior = multi[i];
//         // }
//         // printf(%)
//         printf("%1.8e\n",
//                nextafterf(num1, -INFINITY) * nextafterf(num2, -INFINITY));
//         printf("%1.8e\n",
//                nextafterf(num1, INFINITY) * nextafterf(num2, -INFINITY));
//         fesetround(FE_DOWNWARD);
//         float menor =
//             fminf(fminf(num1_before * num2_before, num1_before * num2_next),
//                   fminf(num1_next * num2_before, num1_next * num2_next));
//         fesetround(FE_UPWARD);
//         float maior =
//             fmaxf(fmaxf(num1_before * num2_before, num1_before * num2_next),
//                   fmaxf(num1_next * num2_before, num1_next * num2_next));
//         // resultado.min = min_intervalo(resultado.min);
//         // resultado.max = max_intervalo(resultado.max);

//         printf("Intervalo = [%1.8e, %1.8e]\n", menor, maior);
//         // printf("Intervalo = [%1.8le, %1.8le]\n", nextafterf(menor,
//         // -INFINITY), nextafterf(maior, INFINITY));
//     }
// }

int main() {
    // float teste = 2.347e-40;
    // float teste2 = 0.001;
    // calcula(teste, teste2, '*');

    intervalo_t result, x1, x2, x3, x4, x5;
    char o1, o2, o3, o4;

    printf("Digite a expressão no formato X1 O1 X2 O2 X3 O3 X4 O4 X5: ");
    scanf("%f %c %f %c %f %c %f %c %f", &x1.min, &o1, &x2.min, &o2, &x3.min, &o3, &x4.min, &o4, &x5.min);

    x1.max = x1.min;
    x2.max = x2.min;
    x3.max = x3.min;
    x4.max = x4.min;
    x5.max = x5.min;

    result = performOperation(performOperation(performOperation(performOperation(x1, o1, x2), o2, x3), o3, x4), o4, x5);

    printf("Resultado: [%1.8e, %1.8e]\n", result.min, result.max);

    return 0;
}
