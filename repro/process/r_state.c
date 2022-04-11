/*
 *	Program: r_state
 *	Author: Ricardo Robaina <rrobaina@redhat.com>
 *	Version: 1.0
 *	Date: 2022/04/11
 *
 *	This small program will create a runnable (R state) task.
 *
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	printf("Runnable process started! Press Ctrl+C to finish it.\n");
	for(;;){
		// idle	
	}
	return EXIT_SUCCESS;
}
