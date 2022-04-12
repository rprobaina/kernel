/*
 *	Program: z_state
 *	Author: Ricardo Robaina <rrobaina@redhat.com>
 *	Version: 1.0
 *	Date: 2022/04/12
 *
 *	This small program will create a zombie (Z state) task.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

# define FOREVER 9999999

int main(void)
{
	pid_t pid;
	
	pid = fork(); 
/*
 * man 2 fork
 *
 *        On  success,  the  PID of the child process is returned in the parent, 
 *        and 0 is returned in the child.  
 *
 */

	if(pid > 0 ){
		printf("In the parent. child-pid: %d\n", pid);
		sleep(FOREVER);
	}else{
		printf("In the child. pid: %d\n", pid);
		exit(0);
	}
	return EXIT_SUCCESS;
}
