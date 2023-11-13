#include "matriz.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Cria uma estrutura matriz_t dinamicamente e inicializa os valores com 0
matriz_t *criaMatriz(int tam) {
    matriz_t *matriz = malloc(sizeof(matriz_t));
    if (!matriz) return NULL;

    // Inicializa A
    matriz->A = malloc(sizeof(intervalo_t *) * tam);
    if (!matriz->A) return NULL;

    for (int i = 0; i < tam; i++) {
        matriz->A[i] = malloc(sizeof(intervalo_t) * tam);
        if (!matriz->A[i]) return NULL;
    }

    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            transformaIntervalo(&matriz->A[i][j], 0);
        }
    }

    // Inicializa B, X e resíduo
    matriz->B = malloc(sizeof(intervalo_t) * tam);
    if (!matriz->B) return NULL;
    matriz->X = malloc(sizeof(intervalo_t) * tam);
    if (!matriz->X) return NULL;

    for (int i = 0; i < tam; i++) {
        transformaIntervalo(&matriz->B[i], 0);
        transformaIntervalo(&matriz->X[i], 0);
    }

    // Inicializa outras variáveis
    matriz->tam = tam;
    return matriz;
}

// Printa a matriz
void printaMatriz(matriz_t *matriz) {
    for (int i = 0; i < matriz->tam; i++) {
        for (int j = 0; j < matriz->tam; j++) printaIntervalo(&matriz->A[i][j]);
        printf("| ");
        printaIntervalo(&matriz->B[i]);
        printf("\n");
    }
}

// Usa o método da retrossubistituição em uma matriz após a elminação de gauss
void retrossubsNaive(matriz_t *matriz) {
    for (int i = matriz->tam - 1; i >= 0; i--) {
        matriz->X[i] = matriz->B[i];
        for (int j = matriz->tam - 1; j > i; j--) {
            matriz->X[i] = subtracao(matriz->X[i],
                                     multiplica(matriz->X[j], matriz->A[i][j]));
        }
        matriz->X[i] = divisao(matriz->X[i], matriz->A[i][i]);
    }
}
// nao funciona
void retrossubsUnroll(matriz_t *matriz) {
    int save = matriz->tam - 1;
    for (int i = (matriz->tam - 1); i >= 0; i--) {
        matriz->X[i] = matriz->B[i];
        for (int j = matriz->tam - 1; j-UF > i; j -= UF) {
            matriz->X[i] = subtracao(matriz->X[i],
                                     multiplica(matriz->X[j], matriz->A[i][j]));
            matriz->X[i] = subtracao(matriz->X[i],
                                     multiplica(matriz->X[j-1], matriz->A[i][j-1]));
            matriz->X[i] = subtracao(matriz->X[i],
                                     multiplica(matriz->X[j-2], matriz->A[i][j-2]));
            matriz->X[i] = subtracao(matriz->X[i],
                                     multiplica(matriz->X[j-3], matriz->A[i][j-3]));
            save = j-UF;
        }
        // Resíduo
        for(int j = save; j>i; j--) {
            matriz->X[i] = subtracao(matriz->X[i],
                                     multiplica(matriz->X[j], matriz->A[i][j]));
        }
        matriz->X[i] = divisao(matriz->X[i], matriz->A[i][i]);
    }
}

void retrossubs(matriz_t *matriz) {
    int istart, iend;
    int save;
    for (int ii = (matriz->tam-1)/BF; ii>=0; ii--) {
        istart = (matriz->tam-1) * BF;
        iend = istart + BF;
        save = matriz->tam - 1;
        for (int i = istart; i >= iend; i--) {
            matriz->X[i] = matriz->B[i];
            for (int j = matriz->tam - 1; j-UF > i; j -= UF) {
                matriz->X[i] = subtracao(matriz->X[i],
                                        multiplica(matriz->X[j], matriz->A[i][j]));
                matriz->X[i] = subtracao(matriz->X[i],
                                        multiplica(matriz->X[j-1], matriz->A[i][j-1]));
                matriz->X[i] = subtracao(matriz->X[i],
                                        multiplica(matriz->X[j-2], matriz->A[i][j-2]));
                matriz->X[i] = subtracao(matriz->X[i],
                                        multiplica(matriz->X[j-3], matriz->A[i][j-3]));
                save = j-UF;
            }
            // Resíduo do unroll
            for(int j = save; j>i; j--) {
                matriz->X[i] = subtracao(matriz->X[i],
                                        multiplica(matriz->X[j], matriz->A[i][j]));
            }
            matriz->X[i] = divisao(matriz->X[i], matriz->A[i][i]);
        }
    }
    // Resíduo do loop tilling
    for(int i=(matriz->tam-1)%BF; i>=0; i--) {
        matriz->X[i] = matriz->B[i];
        for (int j = matriz->tam - 1; j > i; j--) {
            matriz->X[i] = subtracao(matriz->X[i],
                                     multiplica(matriz->X[j], matriz->A[i][j]));
        }
        matriz->X[i] = divisao(matriz->X[i], matriz->A[i][i]);
    }
}

// Função auxiliar do pivoteamento parcial para encontrar o máximo
int encontraMaxParcial(matriz_t *matriz, int i) {
    int iMax = i;
    int save = i+1;
    for (int j = i + 1; j < matriz->tam - (matriz->tam % UF); j+= UF){
        if (abs(matriz->A[j][i].max) > abs(matriz->A[iMax][i].max)) iMax = j;
        if (abs(matriz->A[j+1][i].max) > abs(matriz->A[iMax][i].max)) iMax = j+1;
        if (abs(matriz->A[j+2][i].max) > abs(matriz->A[iMax][i].max)) iMax = j+2;
        if (abs(matriz->A[j+3][i].max) > abs(matriz->A[iMax][i].max)) iMax = j+3;
        save = j+UF;
    }
    
    for(int j = save; j < matriz->tam; j++)
        if (abs(matriz->A[j][i].max) > abs(matriz->A[iMax][i].max)) iMax = j;
    return iMax;
}

int encontraMaxParcialNaive(matriz_t *matriz, int i) {
    int iMax = i;
    for (int j = i + 1; j < matriz->tam; j++)
        if (abs(matriz->A[j][i].max) > abs(matriz->A[iMax][i].max)) iMax = j;
    return iMax;
}

// Função auxiliar do pivoteamento parcial e total para trocar as linhas
void trocaLinhas(matriz_t *matriz, int iMax, int i) {
    if (iMax == i) return;
    intervalo_t aux;
    for (int j = 0; j < matriz->tam; j++) {
        aux = matriz->A[i][j];
        matriz->A[i][j] = matriz->A[iMax][j];
        matriz->A[iMax][j] = aux;
    }
    aux = matriz->B[iMax];
    matriz->B[iMax] = matriz->B[i];
    matriz->B[i] = aux;
}

// Pivoteamento parcial de uma matriz a partir de um índice i
void pivoteamentoParcial(matriz_t *matriz, int i) {
    int iMax = encontraMaxParcial(matriz, i);
    trocaLinhas(matriz, iMax, i);
}

// Aplica o método da eliminação gaussiana
void eliminacaoGaussNaive(matriz_t *matriz) {
    intervalo_t m, sub, mul;
    int iMax = 0;
    // Para cada linha
    for (int i = 0; i < matriz->tam; i++) {
        pivoteamentoParcial(matriz, i);
        // Para cada linha subsequente
        for (int k = i + 1; k < matriz->tam; k++) {
            m = divisao(matriz->A[k][i], matriz->A[i][i]);
            matriz->A[k][i].max = 0;
            matriz->A[k][i].min = 0;
            // Para cada coluna da linha subsequente
            for (int j = i + 1; j < matriz->tam; j++) {
                mul = multiplica(matriz->A[i][j], m);
                sub = subtracao(matriz->A[k][j], mul);
                matriz->A[k][j] = sub;
            }
            matriz->B[k] = subtracao(matriz->B[k], multiplica(matriz->B[i], m));
        }
    }
}

void eliminacaoGauss(matriz_t *matriz) {
    intervalo_t m, sub, mul;
    int iMax = 0;
    int iStart, iEnd = 0;
    // Para cada linha
    for(int ii=0; ii< matriz->tam/BF; ii++) {
        iStart = ii*BF;
        iEnd = iStart + BF;
        for (int i = iStart; i < iEnd; i++) {
            pivoteamentoParcial(matriz, i);
            // Para cada linha subsequente
            for (int k = i + 1; k < matriz->tam; k++) {
                m = divisao(matriz->A[k][i], matriz->A[i][i]);
                matriz->A[k][i].max = 0;
                matriz->A[k][i].min = 0;
                // Para cada coluna da linha subsequente
                for (int j = i + 1; j < matriz->tam; j++) {
                    mul = multiplica(matriz->A[i][j], m);
                    sub = subtracao(matriz->A[k][j], mul);
                    matriz->A[k][j] = sub;
                }
                matriz->B[k] = subtracao(matriz->B[k], multiplica(matriz->B[i], m));
            }
        }
    }
    // Resíduo de I
    for(int i = iEnd; i < matriz->tam; i++) {
        pivoteamentoParcial(matriz, i);
        // Para cada linha subsequente
        for (int k = i + 1; k < matriz->tam; k++) {
            m = divisao(matriz->A[k][i], matriz->A[i][i]);
            matriz->A[k][i].max = 0;
            matriz->A[k][i].min = 0;
            // Para cada coluna da linha subsequente
            for (int j = i + 1; j < matriz->tam; j++) {
                mul = multiplica(matriz->A[i][j], m);
                sub = subtracao(matriz->A[k][j], mul);
                matriz->A[k][j] = sub;
            }
            matriz->B[k] = subtracao(matriz->B[k], multiplica(matriz->B[i], m));
        }
    }
}

void criaSL(pontos_t *xy, matriz_t *SL, int k, int n) {
    intervalo_t aux;
    intervalo_t aux2;
    for (int i = 0; i < n + 1; i++) {
        for (int j = 0; j < n + 1; j++) {
            for (int sum = 0; sum < k; sum++) {
                transformaIntervalo(&aux, xy[sum].x);
                aux = multiplica(power(aux, i), power(aux, j));
                SL->A[i][j] = soma(SL->A[i][j], aux);
            }
        }
        for (int sum = 0; sum < k; sum++) {
            transformaIntervalo(&aux, xy[sum].x);
            transformaIntervalo(&aux2, xy[sum].y);
            aux = multiplica(aux2, power(aux, i));
            SL->B[i] = soma(SL->B[i], aux);
        }
    }
}

// Calcula o resíduo de uma matriz
intervalo_t *calculaResiduo(matriz_t *matriz, pontos_t *xy, int k) {
    intervalo_t aux, fx;
    intervalo_t *ret = malloc(sizeof(intervalo_t) * k);
    if (!ret) return NULL;

    for (int i = 0; i < k; i++) {
        transformaIntervalo(&aux, xy[i].x);
        fx.max = 0;
        fx.min = 0;
        for (int j = 0; j < matriz->tam; j++) {
            fx = soma(fx, multiplica(matriz->X[j], power(aux, j)));
        }
        transformaIntervalo(&aux, xy[i].y);
        ret[i] = subtracao(aux, fx);
    }
    return ret;
}

void libera(matriz_t *matriz, intervalo_t *residuo) {
    for (int i = 0; i < matriz->tam; i++) {
        free(matriz->A[i]);
    }
    free(matriz->A);
    free(matriz->B);
    free(matriz->X);
    free(residuo);
    free(matriz);
}
