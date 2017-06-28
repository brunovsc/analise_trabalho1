#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <float.h>

#include "vetor.h"
#include "ordena.h"

#define POT2(n) (1 << (n))

void nome_arquivo(int n, Modificador modificador, Ordem ordem, Percentual p, char *nome_do_arquivo){

  	char sufixo[10];
	switch (ordem){
		case ALEATORIO: 
		  sprintf(nome_do_arquivo, "vIntAleatorio_%06d", n);
		  break;
		case CRESCENTE:
		  sprintf(nome_do_arquivo, "vIntCrescente_%06d", n);
		  break;
		case DECRESCENTE:
		  sprintf(nome_do_arquivo, "vIntDecrescente_%06d", n);
		  break;
		default:
			break;
	}

	if (p > 0)
    	sprintf(sufixo, "_P%2d.dat", p);
  	else
    	strcpy(sufixo, ".dat");
    
  	strcat(nome_do_arquivo, sufixo);
}

void nome_output(int k, int algoritmo, int ord, Percentual p, char *output_file){
  	char sufixo[10];
  	char algor[10];
  	char ordem[12];
  	char elems[4];
  	
  	//sprintf(elems, "k%d", k);
  	switch(algoritmo){
  		case 0:
  			sprintf(algor, "INSERTION");
  			break;
  		case 1:
  			sprintf(algor, "MERGE");
  			break;
  		case 2:
  			sprintf(algor, "HEAP");
  			break;
  		case 3:
  			sprintf(algor, "QUICK");
  			break;
  		case 4:
  			sprintf(algor, "COUNTING");
  			break;
  		case 5:
  			sprintf(algor, "RADIX");
  			break;
  		case 6:
  			sprintf(algor, "BUCKET");
  			break;
  		default:
  			break;
  	}
	switch (ord){
		case 0: 
		  sprintf(ordem, "Aleatorio");
		  break;
		case 1:
		  sprintf(ordem, "Crescente");
		  break;
		case 2:
		  sprintf(ordem, "Decrescente");
		  break;
		default:
			break;
	}

	if (p > 0)
    	sprintf(sufixo, "_P%2d.txt", p);
  	else
    	strcpy(sufixo, ".txt");
    
    sprintf(output_file, "resultados/%s_%s%s", algor, ordem, sufixo);
}

int main(int argc, char *argv[]){
	int * v = NULL;
  	int n = 0;
  	clock_t inicio, fim;
  	double tempo_de_cpu = 0.0;
  	char msg[256];
  	char nome_do_arquivo[128];
	char caminho_arquivo[150];
	char output_file[70];

	int big;
	int algoritmo = atoi(argv[1]); // 7 algoritmos
	int gerados = 0;
  	int ordem, p, i, k;
  	int N_EXP = 5;
  	double media;
  	FILE *fp = NULL;



		for(ordem = 0; ordem < 3; ordem++){
	  		for(n = POT2(4), k = 4; n <= POT2(17); n <<= 1, k++){
				switch(ordem){
					case 0:
						nome_arquivo(n, TOTALMENTE, ALEATORIO, 0, nome_do_arquivo);
						break;
					case 1:
						nome_arquivo(n, TOTALMENTE, CRESCENTE, 0, nome_do_arquivo);
						break;
					case 2:
						nome_arquivo(n, TOTALMENTE, DECRESCENTE, 0, nome_do_arquivo);
						break;
					default:
						break;
				}
				sprintf(caminho_arquivo, "vetores/%s", nome_do_arquivo);
			
				// Leia o vetor a partir do arquivo
	  			v = leia_vetor_int(caminho_arquivo, &n);
	  			media = 0.0;
	  			for(i = 0; i < N_EXP; i++){
	  				switch(algoritmo){
	  					case 0: // insertion
		  					inicio = clock();
			  				insertion_sort(v,n); 
			  				fim = clock();
	  						break;
	  					case 1: // merge
		  					inicio = clock();
    						merge_sort(v,0,n-1);
			  				fim = clock();
	  						break;
	  					case 2: // heap
		  					inicio = clock();
			  				heap_sort(v,n); 
			  				fim = clock();
	  						break;
	  					case 3: // quick
		  					inicio = clock();
    						quick_sort(v, 0, n-1);
			  				fim = clock();
	  						break;
	  					case 4: // counting
	  						big = bigger(v,n);
		  					inicio = clock();
  							counting_sort(v,n,big+1);
			  				fim = clock();
	  						break;
	  					case 5: // radix
  							big = bigger(v,n);
		  					inicio = clock();
			  				radix_sort(v,n,big); 
			  				fim = clock();
	  						break;
	  					case 6: // bucket
		  					inicio = clock();
			  				bucket_sort(v,n); 
			  				fim = clock();
	  						break;
	  					default:
	  						break;
	  				}
			  		tempo_de_cpu = (((double) (fim - inicio)) / CLOCKS_PER_SEC) * 1000000;
						printf("\n%lf", tempo_de_cpu);
				 	media += tempo_de_cpu;
		  		}
		  		nome_output(k, algoritmo, ordem, 0, output_file);
		  		fp=fopen(output_file, "a");
		  		fprintf(fp, "%d %lf\n", n, media / N_EXP);
		  		fclose(fp);
	  			free(v);
			}
		}



		for(ordem = 0; ordem < 2; ordem++){
	  		for(n = POT2(4), k = 4; n <= POT2(17); n <<= 1, k++){
	  			for(p = 10; p <= 50; p += 10){
					switch(ordem){
						case 0:
							nome_arquivo(n, TOTALMENTE, CRESCENTE, p, nome_do_arquivo);
							break;
						case 1:
							nome_arquivo(n, TOTALMENTE, DECRESCENTE, p, nome_do_arquivo);
							break;
						default:
							break;
					}
					sprintf(caminho_arquivo, "vetores/%s", nome_do_arquivo);

					// Leia o vetor a partir do arquivo
		  			v = leia_vetor_int(caminho_arquivo, &n);
		  			media = 0.0;
		  			for(i = 0; i < N_EXP; i++){
		  				switch(algoritmo){
		  					case 0: // insertion
			  					inicio = clock();
				  				insertion_sort(v,n); 
				  				fim = clock();
		  						break;
		  					case 1: // merge
			  					inicio = clock();
	    						merge_sort(v,0,n-1);
				  				fim = clock();
		  						break;
		  					case 2: // heap
			  					inicio = clock();
				  				heap_sort(v,n); 
				  				fim = clock();
		  						break;
		  					case 3: // quick
			  					inicio = clock();
	    						quick_sort(v, 0, n-1);
				  				fim = clock();
		  						break;
		  					case 4: // counting
		  						big = bigger(v,n);
			  					inicio = clock();
	  							counting_sort(v,n,big+1);
				  				fim = clock();
		  						break;
		  					case 5: // radix
	  							big = bigger(v,n);
			  					inicio = clock();
				  				radix_sort(v,n,big); 
				  				fim = clock();
		  						break;
		  					case 6: // bucket
			  					inicio = clock();
				  				bucket_sort(v,n); 
				  				fim = clock();
		  						break;
		  					default:
		  						break;
		  				}
				  		tempo_de_cpu = (((double) (fim - inicio)) / CLOCKS_PER_SEC) * 1000000;
						printf("\n%lf", tempo_de_cpu);
					 	media += tempo_de_cpu;
			  		}
			  		nome_output(k, algoritmo, ordem+1, p, output_file);
			  		fp=fopen(output_file, "a");
			  		fprintf(fp, "%d %lf\n", n, (media / N_EXP));
			  		fclose(fp);
		  			free(v);					



				}
			}
		}

  
  	exit(0);
}

