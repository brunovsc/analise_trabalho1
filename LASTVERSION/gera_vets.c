#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "vetor.h"

#define POT2(n) (1 << (n))


void gera_e_salva_vet(int n, Modificador m, Ordem o, Percentual p){
  int * v = NULL;
  char nome_do_arquivo[64];
  char sufixo[10];

  switch (o){
    case ALEATORIO: 
      sprintf(nome_do_arquivo, "vIntAleatorio_%06d", n);
      break;
    case CRESCENTE:
      sprintf(nome_do_arquivo, "vIntCrescente_%06d", n);
      break;
    case DECRESCENTE:
      sprintf(nome_do_arquivo, "vIntDecrescente_%06d", n);
      break;
    default: CONFIRME(false, 
                      "gera_e_salva_vet: Ordenação desconhecida");
  }
  
  if (p > 0)
    sprintf(sufixo, "_P%2d.dat", p);
  else
    strcpy(sufixo, ".dat");
    
  v = gera_vetor_int(n, m, o, p, 1, n);    
  strcat(nome_do_arquivo, sufixo);
  escreva_vetor_int(v, n, nome_do_arquivo);
  free(v);
}


int main(int argc, char *argv[]){
  int n = 0;
  int p = 0;
  char diretorio[256];
  
  struct stat st = {0};

  
  if (argc == 2)
    strcpy(diretorio, argv[1]);
  else
    strcpy(diretorio, "./vetores");

  if (stat(diretorio, &st) == -1) { // se o diretorio não existir,
    mkdir(diretorio, 0700);         // crie um
  }

  CONFIRME(chdir(diretorio) == 0, "Erro ao mudar de diretório");
  
  for(n = POT2(4); n <= POT2(17); n <<= 1){
    gera_e_salva_vet(n, TOTALMENTE, ALEATORIO,   0);
    gera_e_salva_vet(n, TOTALMENTE, CRESCENTE,   0);
    gera_e_salva_vet(n, TOTALMENTE, DECRESCENTE, 0);
    
    for(p=10; p <= 50; p += 10){
      gera_e_salva_vet(n, PARCIALMENTE, CRESCENTE,   p);    
      gera_e_salva_vet(n, PARCIALMENTE, DECRESCENTE, p);
    }
    printf("Vetores para n = %d gerados.\n", n);
  }
  
  CONFIRME(chdir("..") == 0, "Erro ao mudar de diretório");
  
  exit(0);
}

