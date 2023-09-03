#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "matriz.h"
#define N 3

typedef struct indice {
    int i;
    int j;
} indice_t;

void printaMatriz(double A[N][N], double B[N]) {
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++)
            printf("%f ", A[i][j]);
        printf("| %f\n", B[i]);
    }
}

void retrossubs(double A[N][N], double B[N], double X[N]) {
    for(int i=N-1; i>=0; i--) {
        X[i] = B[i];
        for(int j=N-1; j>i; j--) {
            X[i] -= X[j]*A[i][j];
        }
        X[i] = X[i] / A[i][i];
    }
}

int encontraMaxParcial(double A[N][N], int i) {
    int iMax = i;
    for(int j=i+1; j<N; j++)
        if(abs(A[j][i]) > abs(A[iMax][i]))
            iMax = j;
    return iMax;
}

indice_t encontraMaxTotal(double A[N][N], int i) {
    indice_t indice;
    indice.i = i;
    indice.j = i;
    for(int j=i; j<N; j++) {
        for(int k=i; k<N; k++) {
            if(A[j][k] > A[indice.i][indice.j]) {
                indice.i = j;
                indice.j = k;
            }
        }
    }
    return indice;
}

void trocaColunas(double A[N][N], double B[N], int jMax, int j) {
    // Troca colunas
    double aux = 0;
    for(int i=0; i<N; i++) {
        aux = A[i][jMax];
        A[i][jMax] = A[i][j];
        A[i][j] = aux;
    }
}

void trocaLinhas(double A[N][N], double B[N], int iMax, int i) {
    if(iMax == i)
        return;
    double aux = 0;
    for(int j=0; j<N; j++) {
        aux = A[i][j];
        A[i][j] = A[iMax][j];
        A[iMax][j] = aux;
    }
    aux = B[iMax];
    B[iMax] = B[i];
    B[i] = aux;
}

void pivoteamentoParcial(double A[N][N], double B[N], int i) {
    int iMax = encontraMaxParcial(A, i);
    trocaLinhas(A, B, iMax, i);
}

void pivoteamentoTotal(double A[N][N], double B[N], int i) {
    indice_t indiceMax = encontraMaxTotal(A, i);
    trocaColunas(A, B, indiceMax.j, i);
    trocaLinhas(A, B, indiceMax.i, i);
}

void eliminacaoGauss(double A[N][N], double B[N]) {
    double m = 0;
    int iMax = 0;
    // Para cada linha
    for(int i=0; i<N; i++) {
        printaMatriz(A, B);
        printf("\n");
        pivoteamentoParcial(A, B, i);
        printaMatriz(A, B);
        printf("\n");
        // Para cada linha subsequente 
        for(int k=i+1; k<N; k++) {
            m = A[k][i] / A[i][i];   // m retirado da fórmula para evitar divisões
            A[k][i] = 0;
            // Para cada coluna da linha subsequente
            for(int j=i+1; j<N; j++)
                A[k][j] -= m*A[i][j];
            B[k] -= m*B[i];
        }
    }
}

void calculaResiduo(double A[N][N], double B[N], double X[N], double residuo[N]) {
    double valor = 0;
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            valor += A[i][j]*X[j]; 
        }
        residuo[i] = valor - B[i];
        valor = 0;
    }
}   

int main() {

    int n = 3;

    matriz_t *matriz = criaMatriz(n);
    printf("residuo = %f\n", matriz->residuo);

    double A[N][N] = {{3, 2, 4}, {1, 1, 2}, {4, 3, -2}};
    // double A[N][N] = {{3.32e-32, 3.32e32, 4333.32e32}, {13.32e-32, 13.32e-32, 2}, {43.32e-42, 33.32e12, -3.32e-32}};
    double B[N] = {1, 2, 3};
    double X[N] = {0, 0, 0};

    eliminacaoGauss(A,B);
    printf("Resultado da eliminação:\n");
    printaMatriz(A, B);
    retrossubs(A,B,X);

    double res[N];
    calculaResiduo(A, B, X, res);

    printf("Soluções\n");
    for(int i=0; i<N; i++) {
        printf("%f ", X[i]);
    }
    printf("\n");

    printf("Residuo\n");
    for (int i = 0; i < N; i++) {
        printf("%f ", res[i]);
    }
    printf("\n");
    
}