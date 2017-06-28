#include <stdio.h>
#include <stdlib.h>

#include "vetor.h"

static void inline troca(int *A, int i, int j){
  int temp;
  temp = A[i];
  A[i] = A[j];
  A[j] = temp;
}

int bigger(int *array, int N){
  int i;
  int bigger = 0;
  for(i = 0; i < N; i++){
    if(array[i] > bigger){
      bigger = array[i];
    }
  }
  return bigger;
}

// INSERTION SORT
void insertion_sort(int *array, int N){
	int i, j;
	int key;
	int aux;
	for(j = 1; j < N; j++){
		key = array[j];
		i =  j - 1;
		while(i >= 0 && array[i] > key){
			array[i+1] = array[i];
			i = i-1;
		}
		array[i+1] = key;
	}
}

// MERGE SORT

void intercalate(int *A, int p, int q, int r) {
  int p1 = p, q2 = q+1, aux = 0;
  int vetAux[r-p+1];
  
  while(p1<=q && q2<=r){
    if(A[p1] <= A[q2]){
      vetAux[aux] = A[p1];
      p1++;
    }else{
      vetAux[aux] = A[q2];
      q2++;
    }
    aux++;
  }
  
  while(p1<=q){  //If there are elements in the first half
    vetAux[aux] = A[p1];
    aux++;p1++;
  }
  
  while(q2<=r){   //If there are still elements in the second half
    vetAux[aux] = A[q2];
    aux++;q2++;
  }
  
  for(aux=p;aux<=r;aux++){    //Move the elements back to the original vector
    A[aux] = vetAux[aux-p];
  }
}

void merge_sort(int *A, int p, int r){
  if (p < r) {
    int q = (p+r)/2;
    merge_sort(A, p, q);
    merge_sort(A, q+1, r);
    intercalate(A, p, q, r);
  }
}

// HEAP SORT

void max_heapify(int *array, int N, int i){
	int e = 2*i + 1;
	int d = 2*i + 2;
	int maior;
	int aux;
	if(e < N && array[e] > array[i]){
		maior = e;
	} else {
		maior = i;
	}
	
	if(d < N && array[d] > array[maior]){
		maior = d;
	}
	
	if(i != maior){
		aux = array[maior];
		array[maior] = array[i];
		array[i] = aux;
		max_heapify(array, N, maior);
	}
}


void build_max_heap(int *array, int N){
	int i;
	for(i = N/2 - 1; i >= 0; --i){
		max_heapify(array, N, i);
	}
}

void heap_sort(int *array, int N){
	build_max_heap(array, N);
	int m = N;
	int i = 0;
	int aux;
	for(i = N-1; i >= 0; i--){
		aux = array[0];
		array[0] = array[i];
		array[i] = aux;
		//m = m-1;
		max_heapify(array, i, 0);
	}
}

// QUICK SORT

int partition(int *array, int p, int r){
	int pivot = array[r];
	int j, aux;
	int i = p - 1;
	for(j = p; j <= r-1; j++){
		if(array[j] <= pivot){
			i++;
			aux = array[i];
			array[i] = array[j];
			array[j] = aux;
		}
	}
	aux = array[i+1];
	array[i+1] = array[r];
	array[r] = aux;
	return i+1;
}

void quick_sort(int *array, int p, int r){
	int q;
	if(p < r){
		q = partition(array, p, r);
		quick_sort(array, p, q-1);
		quick_sort(array, q+1, r);
	}
}


// COUNTING SORT
void counting_sort(int *A, int n, int k){
  int i;
  int j;
  //Create B[N]
  int * B = calloc(n, sizeof(int));
  //Create C[K]
  int * C = calloc(k, sizeof(int));
  for (i=0;i<k;i++){
    C[i]=0;
  }
  //Step 1
  for(j=0;j<n;j++){
    C[A[j]] = C[A[j]] + 1;
  }
  //Step 2
  for(i=1;i<k;i++) {
    C[i] = C[i] + C[i-1];
  }
  //Step 3
  for(j=n-1;j>=0;j--) {
    C[A[j]] = C[A[j]] - 1;
    B[C[A[j]]] = A[j];
  }
  //Step 4
  for(i=0;i<n;i++) {
    A[i] = B[i];
  }
  free(B);
  free(C);
}


void print_array(int *array, int N){
	int i;
	printf("\n-----\n");
	for(i = 0; i < N; i++){
		printf("ARRAY[%d] = %d\n", i, array[i]);
	}
	printf("-----\n");
	return;
}

// RADIX SORT

void countSort(int *arr, int n, int exp)
{
  int output[n]; // output array
  int i, count[10] = {0};
  
  // Store count of occurrences in count[]
  for (i = 0; i < n; i++)
    count[ (arr[i]/exp)%10 ]++;
  
  // Change count[i] so that count[i] now contains actual
  //  position of this digit in output[]
  for (i = 1; i < 10; i++)
    count[i] += count[i - 1];
  
  // Build the output array
  for (i = n - 1; i >= 0; i--)
  {
    output[count[ (arr[i]/exp)%10 ] - 1] = arr[i];
    count[ (arr[i]/exp)%10 ]--;
  }
  
  // Copy the output array to arr[], so that arr[] now
  // contains sorted numbers according to current digit
  for (i = 0; i < n; i++)
    arr[i] = output[i];
}

void radix_sort(int *arr, int n, int m)
{
  // Do counting sort for every digit. Note that instead
  // of passing digit number, exp is passed. exp is 10^i
  // where i is current digit number

  int exp;
  for (exp = 1; m/exp > 0; exp *= 10){
    countSort(arr, n, exp);
  }
}

// BUCKET SORT
typedef struct bucket{
	int count;
	int *values;
} Bucket;

void add_value(Bucket *bucket, int value){
	int i, j, top;
	top = bucket->count;
	int newValues[top+1];
	newValues[0] = value;
	
	for(i = 1; i < top + 1; i++){
		newValues[i] = bucket->values[i-1]; 
	}
	
	bucket->values = newValues;
	(bucket->count)++;
}

void print_bucket(Bucket bucket){
	int j;
	printf(" Count %d: ", bucket.count);
	for(j = 0; j < bucket.count; j++){
		printf("%d ", bucket.values[j]);
	}
}

void bucket_sort(int *array, int N){
	Bucket buckets[N];
	int i, j, k, *aux;
	Bucket *bucket;
	for(i = 0; i < N; i++){
		buckets[i].count = 0;
	}
	
	for(i = 0; i < N; i++){
		bucket = &buckets[array[i]-1];
		bucket->count = bucket->count + 1;
		
		aux = (int*)malloc((bucket->count + 1) * sizeof(int));
		aux[0] = array[i];
		for(k = 1; k < bucket->count; k++){
			aux[k] = bucket->values[k-1];
		}
		bucket->values = aux;
	}
	
	for(i = 0; i < N; i++){
		insertion_sort(buckets[i].values, buckets[i].count);
	}
	
	for(i = 0, k = 0; i < N; i++){
		aux = buckets[i].values;
		for(j = 0; j < buckets[i].count; j++, k++){
			array[k] = aux[j];
		}
	}
	
}

