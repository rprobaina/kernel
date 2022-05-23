/*
 *	This a simple program usefull to exemplify the concepts of VSZ and RSS.
 *	
 *	Usage: ./mem_usage <RSS INITIAL SIZE in MB> <RSS INC in MB> <TIME INTERVAL in seconds>i
 *
 *	How to monitor: $ ps -A --sort -vsize -o pid,comm,vsize,rss | head -n2
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MB(x)   ((size_t) (x) << 20)

#define DEFAULT_VSZ_SIZE MB(2000) 	/* 2 GB */
#define DEFAULT_RSS_INC MB(1)	 	/* 1 MB */	
#define DEFAULT_TIME_INC 5   		/* seconds */
#define FINAL_SLEEP 120			/* 2 minutes */

int main(int argc, char *argv[])
{
	size_t vsz_size = DEFAULT_VSZ_SIZE;
	size_t rss_inc = DEFAULT_RSS_INC; 
	size_t time = DEFAULT_TIME_INC;	
	size_t i;
	size_t rss_size = 0;

	if(argc == 4){
		vsz_size = MB(atol(argv[1]));
		rss_inc = MB(atol(argv[2]));     
		time = atoi(argv[3]);    	
	}
	printf("%s started. Press Ctrl + C to exit.\n", argv[0]);

	/* allocating (reserving) @vsz_size bytes of virtual memory starting at @array */
	void *array = malloc(vsz_size);
	if(!array){
		printf("Unable to allocate VSZ memory\n");
		return EXIT_FAILURE;
	}
	printf("%d bytes of memory have been allocated (VSZ).\n", vsz_size);
	
	/* each @time, memset @array-chunks of @rss_inc size. which makes this memory resident */
	for(i = 0; (rss_size + rss_inc) <= vsz_size; i += rss_inc){
		sleep(time);   
		void *n = memset(array + i, 0, rss_inc);
 		rss_size += rss_inc;
		printf("%d bytes of memory have been used (RSS).\n", rss_inc);
		printf("VSZ: %ld\tRSS: %ld\n", vsz_size, rss_size);
	}

	/* freeing @array should reduce both VSZ and RSS */
	free(array); 
	printf("The memory has been freed.\n", rss_inc);
	printf("VSZ: ~0\tRSS: ~0\n");
	
	sleep(FINAL_SLEEP);	

	return EXIT_SUCCESS;
}
