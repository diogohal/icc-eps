#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#define PONTOS 10000000

// Calcula o tempo atual em milissegundos
double timestamp(void){
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return((double)(tp.tv_sec+tp.tv_usec/1000000.0))*1000;
}

// Integral Monte Carlo da função Styblinski-Tang de 2 variáveis
double monteCarlo(double a, double b)
{
  double resultado;
  double soma = 0.0;  
  
  // Monte Carlo algoritmo para a função Styblinski-Tang
  double x , sum = 0;
  for ( int i =0; i < PONTOS ; i ++) {
    x = a + (( double ) random () / RAND_MAX ) * ( b - a );
    sum += (x*x*x*x - 16*x*x + 5*x)/2;
  }
  resultado = ( sum / PONTOS ) * ( b - a );

  if(resultado < 0)
    resultado = resultado * -1;
  return resultado;
}


double retangulos_xy(double a, double b) {

  double h;
  double x = 0.0;
  double soma = 0.0;
  
  // MÉTODO DO RETÂNGULO
  h = (b - a)/PONTOS;
  printf("%f\n", h);
  for(int i = 0; i < PONTOS; ++i) {
    x = a + h*i;
    soma += (x*x*x*x - 16*x*x + 5*x)/2*h;
  }
  
  if(soma < 0)
    soma = soma*-1;
  return soma;
}


int main(int argc, char **argv) {
  if (argc < 4) {
    printf("Utilização: %s inicial final n_dimensoes\n", argv[0]);
    return 1;
  }

  double inicial = atof(argv[1]);
  double final = atof(argv[2]);
  double n_dimensoes = atoi(argv[3]);

  srand(20232);
    
  double resultadoRet = retangulos_xy(inicial, final);
  double resultadoMont = monteCarlo(inicial, final);

  printf("Resultado Método Retângulo = %f\n", resultadoRet);
  printf("Resultado Método Monte Carlo = %f\n", resultadoMont);
  printf("Resultado aproximado = 136.53\n"); 
  return 0;
}
