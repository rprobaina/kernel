/*
 *	Program: r_state
 *	Author: Ricardo Robaina <rrobaina@redhat.com>
 *	Version: 1.0
 *	Date: 2022/04/11
 *
 *	This small program will create a blocked (S state) task.
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define FOREVER 9999999

int main(void)
{
	printf("Blocked-interruptible process started! Press Ctrl+C to finish it.\n");

	sleep(FOREVER);

	return EXIT_SUCCESS;
}
