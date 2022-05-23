/*
 *	This is a small program to exemplify a bug of
 *	referencing a nonexistent variable.
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * alloc_stack: allocates space for a integer in the stack
 * and initiates it with @val.
 * It returns the address of the "allocated stack variable".
 *
 */
int *alloc_stack(int val)
{
	int i = val;	/* as soon as the function returns this reference is invalid */
	return &i;	/* an alloc_heep function (using malloc), would be appropriated */
}

int main(void)
{
	int *stack_var = alloc_stack(100); 
	
	printf("%d, %d\n", stack_var, *stack_var);

	return EXIT_SUCCESS;
}
