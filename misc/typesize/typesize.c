/*
 *	This program prints the basic C data types' sizes (in bytes) 
 *	on the running architecture.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	printf("Type\tSize (bytes)\n");
	printf("--------------------\n");
	printf("short\t%d\n", sizeof(short));
	printf("int\t%d\n", sizeof(int));
	printf("long\t%d\n", sizeof(long));
	printf("ptr\t%d\n", sizeof(void *));
	printf("float\t%d\n", sizeof(float));
	printf("double\t%d\n", sizeof(double));
	printf("uint\t%d\n", sizeof(unsigned int));	/* should be the same size as int */
	printf("ulong\t%d\n", sizeof(unsigned long));	/* should be the same size as long */

	return EXIT_SUCCESS;
}
