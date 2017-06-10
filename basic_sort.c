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
    char *path = "..\\..\\..\\generate_data\\";
    char filePath[35];

    sprintf(filePath, "%s%s", path, filename);
    printf("FILEPATH: %s", filePath);

    FILE *fp = fopen(filePath, "r");
    if(!fp){
        printf("\nFailed to open file.");
    }

    int i;
    for(i = 0; i < N; i++){
        fscanf(fp, "%d\n", &array[i]);
    }

    fclose(fp);
}

int main(int argc, char * argv[]){
	if(argc != 3){
		printf("\nUsage: sort k type\nk refers to the number of elements 2^k in the array\ntype: 1 for crescent, 2 for decrescent, 3 for 10 percent sorted, 4 for 20 percent sorted\n");
		exit(0);
	}

	int k = atoi(argv[1]);
	if(k < 1 || k > 14){
		printf("Usage: sort k type\nk refers to the number of elements 2^k in the array\ntype: 1 for crescent, 2 for decrescent, 3 for 10 percent sorted, 4 for 20 percent sorted\n");
		printf("k should be between 1 and 14\n");
		exit(0);
	}

	int type = atoi(argv[2]);
	if(type < 1 || type > 4){
		printf("Usage: generator k type\nk refers to the number of elements 2^k in the array\ntype: 1 for crescent, 2 for decrescent, 3 for 10 percent sorted, 4 for 20 percent sorted\n");
		printf("type must be between 1 and 4\n");
		exit(0);
	}

	printf("k = %d - type = %d\n", k, type);
	char *types[] = { "crescent" , "decrescent" , "10percent" , "20percent" };
	char filename[20];

	sprintf(filename, "k%d_%s.txt", k, types[type-1]);
	printf("filename used: %s\n", filename);

	int N = power(2,k);
	int array[N];

	load_file(filename, array, N);

    clock_t begin = clock();

    // sort();

    clock_t end = clock();

    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nTotal time: %f", time_spent);

    return 0;
}
