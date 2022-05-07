/*
 *	Program: oom
 *	Author: Ricardo Robaina <rrobaina@redhat.com>
 *	Version: 1.0
 *	Date: 2022/05/06
 *
 *	This small program will trigger a out-of-memory killer, by hogging all the system's memory.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define DEFAULT_SIZE 4096 /* bytes */
#define DEFAULT_TIME 10 /* seconds */
 
int main(int argc, char *argv[])
{
	size_t size, time;
	void *mem_chunk;

	if(argc < 3){
		size = DEFAULT_SIZE;
		time = DEFAULT_TIME;
	}
	else{
		size = atoi(argv[1]);
		time = atoi(argv[2]);
	}

	printf("memory hogger started! hit Ctrl+C to finish it\n");
	for(;;){	
		mem_chunk = malloc(size);
		if(!mem_chunk)
			return EXIT_FAILURE;	
		memset(mem_chunk, 1, size);
		sleep(time);
	}

	return EXIT_SUCCESS;
}
