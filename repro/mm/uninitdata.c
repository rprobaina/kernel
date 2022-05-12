/*
 *	This small program wil derreference a null pointer.
 *
 */
#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000000

int a[SIZE]; /* the loader init gobal vars with zeros */

int main()
{
	int a_sum, b_sum;
	
	a_sum = 0;
	for(int i = 0; i < SIZE; i++){
		a_sum += a[i];
	}
	printf("a_sum = %d\n", a_sum);

	/* heep memory is not initialized, should use calloc in this case */
	int *b = (int *) malloc(SIZE * sizeof(int));
	b_sum = 0;
	for(int i = 0; i < SIZE; i++){
		b_sum += b[i];
	}
	printf("b_sum = %d\n", b_sum);
	
	return EXIT_SUCCESS;
}

