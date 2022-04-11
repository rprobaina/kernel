/*
 *	Program: d_state
 *	Author: Ricardo Robaina <rrobaina@redhat.com>
 *	Version: 1.0
 *	Date: 2022/03/10
 *
 *	This small program will create a blocked (D state) task
 *	for N seconds.
 *
 *	The time (in seconds) is passed as the first arguement.
 *	If no parameter is passed, the time will be as define in DEFAULT.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#define DEFAULT 120

int main(int argc, char *argv[])
{
	int time = 0;
	pid_t pid;

	if(argc < 2)
		time = DEFAULT;
	else
		time = atoi(argv[1]);

	printf("Task blocked for %d seconds, press Ctrl + C to terminate.\n", time);
	
	pid = vfork(); // vfork - create a child process and block parent
	if(pid == -1){
		printf("Error: unable to fork this process.\n");
		return EXIT_FAILURE;
	}
	
	sleep(time);
	kill(pid, SIGKILL);

	return EXIT_SUCCESS;
}
