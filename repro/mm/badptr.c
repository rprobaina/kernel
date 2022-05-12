/*
 *	This small program wil derreference a bad pointer.
 *
 */
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int age_var;

	printf("type your age: ");
	scanf("%d", age_var); /* should be &age_var */

	printf("you are %d-years old.\n", age_var);
	
	return EXIT_SUCCESS;
}

