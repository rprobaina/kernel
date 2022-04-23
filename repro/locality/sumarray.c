#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10000000

unsigned long sumarray_rows(unsigned long a[SIZE][SIZE]);
unsigned long sumarray_cols(unsigned long a[SIZE][SIZE]);
void init_vec(unsigned long a[SIZE][SIZE]);
void print_vec(unsigned long a[SIZE][SIZE]);

int main(void)
{
	unsigned long v[SIZE][SIZE];

	//printf("Unitialized vector:\n");	
	//print_vec(v);
	
	init_vec(v);

	//printf("Initialized vector:\n");	
	//print_vec(v);
	
	unsigned long sum = 0;
	sum = sumarray_rows(v);

	printf("%ld\n", sum);
	
	return EXIT_SUCCESS;
}

unsigned long sumarray_rows(unsigned long a[SIZE][SIZE])
{
	unsigned long i, j, sum = 0;
	
	for(i = 0; i < SIZE; i++)
		for(j = 0; j < SIZE; j++)
			sum += a[i][j];

	return sum;
}

unsigned long sumarray_cols(unsigned long a[SIZE][SIZE])
{
	unsigned long i, j, sum = 0;
	
	for(j = 0; j < SIZE; j++)
		for(i = 0; i < SIZE; i++)
			sum += a[i][j];

	return sum;
}

void init_vec(unsigned long a[SIZE][SIZE])
{
	srand(time(NULL));
	unsigned long i, j;

	for(i = 0; i < SIZE; i++)
		for(j = 0; j < SIZE; j++)
			a[i][j] = rand();
}

void print_vec(unsigned long a[SIZE][SIZE])
{
	unsigned long i, j, index = 0;
	
	for(i = 0; i < SIZE; i++){
		for(j = 0; j < SIZE; j++){
			printf("%ld: %ld\t", index++, a[i][j]);
		}
		printf("\n");
	}
}

