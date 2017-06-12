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
// A function to do counting sort of arr[] according to
// the digit represented by exp.
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

// Radix Sort
void radixSort(int *arr, int n, int m)
{
  // Do counting sort for every digit. Note that instead
  // of passing digit number, exp is passed. exp is 10^i
  // where i is current digit number
  for (int exp = 1; m/exp > 0; exp *= 10)
    countSort(arr, n, exp);
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
  //Search the bigger number in array
 
  // loading input file
  load_file(inputFilename, array, N);
  int K = bigger(array, N);
  // begin time counting
  
  clock_t begin = clock();
  
  radixSort(array,N,K);
  
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
