#ifndef _ORDENA_H
#define _ORDENA_H

/*
 * Função: ordena_por_bolha
 * ------------------------
 * Ordena em ordem crescente um vetor de inteiros usando o método da bolha
 *
 * A - o vetor de inteiros a ser ordenado.
 * n - o número de elementos de A.
 * 
 * SAÍDA: o vetor A reorganizado em ordem crescente.
 *
 */
//void ordena_por_bolha(int *A, int n);


/*
 * Função: ordena_por_shell
 * ------------------------
 * Ordena em ordem crescente um vetor de inteiros usando o método de Shell
 *
 * A - o vetor de inteiros a ser ordenado.
 * n - o número de elementos de A.
 * 
 * SAÍDA: o vetor A reorganizado em ordem crescente.
 *
 */
//void ordena_por_shell(int *A, int n);

int bigger(int *array, int N);

void insertion_sort(int *array, int N);
void merge_sort(int *A, int p, int r);
void heap_sort(int *array, int N);
void quick_sort(int *array, int p, int r);
void counting_sort(int *array, int N, int K);
void radix_sort(int *array, int N, int K);
void bucket_sort(int *array, int N);

#endif
