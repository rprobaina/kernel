/*
 *	This small program will leak memory.
 *
 */
#include <stdio.h>
#include <stdlib.h>

void leak();

int main()
{
	for(;;)
		leak();

	return EXIT_SUCCESS;
}

void leak()
{
	int *a = (int *) malloc(sizeof(int));
	return;
}
