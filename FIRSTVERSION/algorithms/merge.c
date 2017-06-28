#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int power(int base, int exp){
	int result = base;
	for(exp; exp > 1; exp--){
		result = result * base;
	}
	return result;
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

void load_file(char *filename, int *array, int N){
    char *path = "../generate_data/";
    char filePath[35];

    sprintf(filePath, "%s%s", path, filename);
	printf("\nInput file: %s\n", filePath);

    FILE *fp = fopen(filePath, "r");
    if(!fp){
        printf("\nFailed to open input file.");
    }

    int i;
    for(i = 0; i < N; i++){
        fscanf(fp, "%d\n", &array[i]);
    }

    fclose(fp);
}

int verify_sorted(int *array, int N){
	int i;
	for(i = 0; i < N-1; i++){
		if(array[i] > array[i+1]){
			return 0;
		}
	}
	return 1;
}
//Intercalate
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
//Merge
void mergeSort(int *A, int p, int r){
  if (p < r) {
    int q = (p+r)/2;
    mergeSort(A, p, q);
    mergeSort(A, q+1, r);
    intercalate(A, p, q, r);
  }
}

int main(int argc, char * argv[]){
	// analyzing input arguments
	if(argc != 3){ // invalid number of arguments
		printf("\nUsage: sort k type\nk refers to the number of elements 2^k in the array\ntype: 1 for crescent, 2 for decrescent, 3 for 10 percent sorted, 4 for 20 percent sorted\n");
		exit(0);
	}

	int k = atoi(argv[1]);
	if(k < 1 || k > 14){ // invalid number of elements 2^k
		printf("Usage: sort k type\nk refers to the number of elements 2^k in the array\ntype: 1 for crescent, 2 for decrescent, 3 for 10 percent sorted, 4 for 20 percent sorted\n");
		printf("k should be between 1 and 14\n");
		exit(0);
	}

	int type = atoi(argv[2]);
	if(type < 1 || type > 4){ // invalid type of input array
		printf("Usage: generator k type\nk refers to the number of elements 2^k in the array\ntype: 1 for crescent, 2 for decrescent, 3 for 10 percent sorted, 4 for 20 percent sorted\n");
		printf("type must be between 1 and 4\n");
		exit(0);
	}

	char *describedTypes[] = { "Ordem Crescente" , "Ordem Decrescente" , "10 porcento ordenado" , "20 porcento ordenado" };
	printf("Arguments: \n --- k = %d\n --- Input array type: %s\n", k, describedTypes[type-1]);
	char *types[] = { "crescent" , "decrescent" , "10percent" , "20percent" };
	char inputFilename[20];

	sprintf(inputFilename, "k%d_%s.txt", k, types[type-1]);

	// counting number of elements and initializing array
	int N = power(2,k);
	int array[N];

	// loading input file
	load_file(inputFilename, array, N);

	// begin time counting
    clock_t begin = clock();

    mergeSort(array,0,N-1);

	// end time counting
    clock_t end = clock();

    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("\nTotal execution time: %f seconds\n", time_spent);

	// appending result to output file
	char resultFilename[35];
	char *sort = argv[0];

	// editing file name
	sprintf(sort, "%s", sort + 2); // removing "./" in the argv string
	sprintf(resultFilename, "%s_%s", sort, inputFilename);
	char resultPath[50];
	sprintf(resultPath, "../results/%s", resultFilename);

	printf("\nOutput file: %s\n", resultPath);

	FILE *output = fopen(resultPath, "a"); // append result to the file
	if(!output){
		printf("\nFailed to open output file\n");
	}

	fprintf(output, "%f\n", time_spent);
	fclose(output);

	//print_array(array, N);
	int verified = verify_sorted(array, N);
	if(verified){
		printf("\nSorted\n");
	} else{
		printf("\nNot sorted\n");
	}

    return 0;
}
