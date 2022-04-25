/*
 *	Program: dstate
 *	Author: Ricardo Robaina <rrobaina@redhat.com>
 *	Version: 1.0
 *	Date: 2022/03/15
 *
 *	This small program to reproduce the issue:
 *	"fork cannot allocate memory"
 *	of
 *	"fork: Resource temporarily unavailable"
 *
 *	It happens when the system ran out of pids.
 *	The max of pids on a system is defined in /proc/sys/kernel/pid_max 
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#define DEFAULT 10
#define FOREVER 9999999

int main(int argc, char *argv[])
{
	int n_pids, i = 0; /* number of processes created */
	pid_t pid;

	if(argc < 2)
		n_pids = DEFAULT;
	else
		n_pids = atoi(argv[1]);

	while(i++ < n_pids){
		pid = fork();
		if(pid != 0){ /* in the parent */
			if(pid == -1){
				printf("Error: unable to fork this process.\n");
				return EXIT_FAILURE;
			}else{
				printf("Success: pid %d created.\n", pid);
			}
		}else{ /* in the child */
			sleep(FOREVER);
		}
	}
	
	return EXIT_SUCCESS;
}
