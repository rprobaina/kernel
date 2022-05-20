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

#define KB (1UL << 10)
#define MB (1UL << 20) 

#define DEFAULT_VSZ_SIZE (2000 * MB)
#define DEFAULT_RSS_INC (1 * MB)
#define DEFAULT_TIME_INC 5   /* seconds */

int main(int argc, char *argv[])
{
	unsigned long vsz_size = DEFAULT_VSZ_SIZE;
	unsigned long rss_inc = DEFAULT_RSS_INC; 
	int time = DEFAULT_TIME_INC;	
	int i;
	unsigned long rss_size = 0;

	if(argc == 4){
		vsz_size = (atoi(argv[1]) * MB);
		rss_inc = (atoi(argv[2]) * MB);     
		time = atoi(argv[3]);    	
	}
	printf("%s started. Press Ctrl + C to exit.\n", argv[0]);

	/* allocating (reserving) @vsz_size bytes of virtual memory starting at @array */
	void *array = malloc(vsz_size);
	if(!array){
		printf("Unable to allocate VSZ memory\n");
		return EXIT_FAILURE;
	}
	printf("%d MB of memory have been allocated (VSZ).\n", vsz_size);
	
	/* each @time, memset @array-chunks of @rss_inc size. which makes this memory resident */
	for(i = 0; (rss_size + rss_inc) <= vsz_size; i += rss_inc){
		sleep(time);   
		void *n = memset(array + i, 0, rss_inc);
 		rss_size += rss_inc;
		printf("%d (MB) of memory have been used (RSS).\n", rss_inc);
		printf("VSZ: %ld\tRSS: %ld\n", vsz_size, rss_size);
	}
	
	return EXIT_SUCCESS;
}
