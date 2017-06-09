#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
	printf("\n-----\n");
	return;
}

int main(int argc, char * argv[]){
	if(argc != 3){
		printf("Usage: generator k type\nk refers to the number of elements 2^k in the array\ntype: 1 for crescent, 2 for decrescent, 3 for 10 percent sorted, 4 for 20 percent sorted\n");
		exit(0);
	}

	int k = atoi(argv[1]);
	if(k < 1 || k > 14){
		printf("Usage: generator k type\nk refers to the number of elements 2^k in the array\ntype: 1 for crescent, 2 for decrescent, 3 for 10 percent sorted, 4 for 20 percent sorted\n");
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
	printf("filename: %s\n", filename);
	
	int N = power(2,k);
	int array[N];
	int i;
	
	printf("N = %d\n", N);

	int percent;
	int count;
	int r;

	srand(time(NULL));
	switch(type){
		case(1):  // crescent
			for(i = 0; i < N; i++){
				array[i] = i+1;
			}
			break;
		
		case(2): // decrescent
			for(i = 0; i < N; i++){
				array[i] = N - i;
			}
			break;

		case(3): // 10 percent sorted
			percent = ((int) (0.1 * N));
			printf("elements sorted: %d\n", percent);
			for(i = 0; i < N; i++){
				array[i] = 0;
			}
			count = 0;
			while(count < percent){
				r = rand() % N;
				if(array[r] == 0){
					array[r] = r+1;
					count++;
				} 
			}
			for(i = 0; i < N; i++){
				if(array[i] == 0){
					do{
						r = rand() % N;
					}
					while(r == i);
					array[i] = r+1;
				}
			}
			break;

		case(4): // 20 percent sorted
			percent = ((int) (0.2 * N));
			printf("elements sorted: %d\n", percent);
			for(i = 0; i < N; i++){
				array[i] = 0;
			}
			count = 0;
			while(count < percent){
				r = rand() % N;
				if(array[r] == 0){
					array[r] = r+1;
					count++;
				} 
			}
			for(i = 0; i < N; i++){
				if(array[i] == 0){
					do{
						r = rand() % N;
					}
					while(r == i);
					array[i] = r+1;
				}
			}
			break;
		
		default:
			printf("Type not suported");
			exit(0);
	}

	FILE *fp = fopen (filename, "w");
	if(fp == NULL){
		printf("Failed to save file");
		exit(0);
	}

	for(i = 0; i < N; i++){
		fprintf(fp, "%d\n", array[i]);
	}

	fclose(fp);
	exit(0);
}
