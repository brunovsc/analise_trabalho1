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
//Bigger
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
//Counting sort
void countingSort(int *A, int n, int k){
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
  
  //Search the bigger number in array
  int K = bigger(array, N);
  
  printf("\nK:%d\n",K);
  // begin time counting
  clock_t begin = clock();
  
  countingSort(array,N,K+1);
  
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
