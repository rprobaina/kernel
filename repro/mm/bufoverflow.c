/*
 *	This small program will allow a buffer overflow.
 *
 */
#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 10

int main()
{	
	char buf[BUFSIZE];
	gets(buf);	/* use fgets instead */

	return EXIT_SUCCESS;
}

