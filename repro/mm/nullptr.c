/*
 *	This small program will derreference a null pointer.
 *
 */
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i;
	int *i_ptr = NULL;

	i = 10;
	/* i_ptr = &i; */

	printf("addr: %ld, val: %d\n", i_ptr, *i_ptr);
	
	return EXIT_SUCCESS;
}

