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
    char *path = "generate_data/";
    char filePath[35];

    sprintf(filePath, "%s%s", path, filename);

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
	printf("\nInput filename: %s\n", inputFilename);

	// counting number of elements and initializing array
	int N = power(2,k);
	int array[N];

	// loading input file
	load_file(inputFilename, array, N);

	// begin time counting
    clock_t begin = clock();

    // sort();

	// end time counting
    clock_t end = clock();

    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("\nTotal execution time: %f seconds\n", time_spent);

	// appending result to output file
	char resultFilename[35];
	char *sort = "sort"; // change this to the name of the algorithm
	sprintf(resultFilename, "%s_result_%s", sort, inputFilename);

	printf("\nOutput filename: %s\n", resultFilename);

	FILE *output = fopen(resultFilename, "a"); // append result to the file
	if(!output){
		printf("Failed to open output file");
	}

	fprintf(output, "%f\n", time_spent);
	fclose(output);

    return 0;
}
