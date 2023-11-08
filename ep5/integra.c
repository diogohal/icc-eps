#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"

#define DIFF 0.0
#define N 2
#define NRAND    ((double) rand() / RAND_MAX)  // drand48() 
#define SRAND(a) srand(a) // srand48(a)


// Integral Monte Carlo da função Styblinski-Tang de 2 variáveis
double monteCarlo(double a, double b, int namostras)
{
  double resultado;
  double soma = 0.0;
  
  printf("Metodo de Monte Carlo (x, y).\n");
  printf("a = (%f), b = (%f), n = (%d), variaveis = 2\n", a, b, namostras);
  
  double t_inicial = timestamp();
  
  // MONTE CARLO ALGORITMO para a função Styblinski-Tang

  double x , sum = 0;
  for ( int i =0; i < namostras ; i ++) {
    x = a + (( double ) random () / RAND_MAX ) * ( b - a );
    sum += (x*x*x*x - 16*x*x + 5*x)/2;
  }

  resultado = ( sum / namostras ) * ( b - a );
  
  double t_final = timestamp();
  printf("Tempo decorrido: %f seg.\n", t_final - t_inicial);
  
  return resultado;
}


double retangulos_xy(double a, double b, int namostras) {

  double h;
  double resultado;
  double x = 0.0;
  
  printf("Metodo dos Retangulos (x, y).\n");
  printf("a = (%f), b = (%f), n = (%d), h = (%lg)\n", a, b, namostras, h);
  
  double t_inicial = timestamp();

  // MÉTODO DO RETÂNGULO
  h = (b - a)/namostras;
  double soma = 0.0;
  for(int i = 0; i < namostras; ++i) {
    x = a + h*i;
    soma += (x*x*x*x - 16*x*x + 5*x)/2*h;
  }


  double t_final = timestamp();
  printf("Tempo decorrido: %f seg.\n", t_final - t_inicial);
  
  return resultado;
}


int main(int argc, char **argv) {

  if (argc < 5) {
    printf("Utilização: %s inicial final n_amostras n_variaveis\n", argv[0]);
    return 1;
  }

  srand(2023);
    
  double resultado = retangulos_xy(2, 5, 2);
  printf("RESULTADO FINAL = %f\n", resultado);
  
  return 0;
}
