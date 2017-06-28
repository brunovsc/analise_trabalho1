#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "vetor.h"

int main(int argc, char *argv[]){
  double * v;
  double * w;
  int i, n;
  int minimo, maximo;
  int p;

  n = 10;
  minimo = 1;
  maximo = 10;
  p = 10;

  switch (argc) {
  case 2:
    n = atoi(argv[1]);
    break;
  case 4:
    n = atoi(argv[1]);
    minimo = atoi(argv[2]);
    maximo = atoi(argv[3]);
    break;
  case 5:
    n = atoi(argv[1]);
    minimo = atoi(argv[2]);
    maximo = atoi(argv[3]);
    p = atoi(argv[4]);
    break;
  default: CONFIRME(false, "Número errado de argumentos\n");
  }
  
  printf("percentual = %d\n",p);
  v = gera_vetor_double(n, PARCIALMENTE, CRESCENTE, p, minimo, maximo);
  escreva_vetor_double(v,n,"vetor.dat");
  
  w = leia_vetor_double("vetor.dat", &n);
  
  for(i=0;i<n;i++)
    printf("v[%d] = %f\n",i,v[i]);
  printf("\n");

  for(i=0;i<n;i++)
    printf("w[%d] = %f\n",i,w[i]);
  printf("\n");

  free(v);
  free(w);
  exit(0);
}
