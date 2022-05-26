/*
 *	This small program will allocate huge pages on x86.
 *
 *	usage: ./hgpage_usage @hpq @hpt
 *	 - @hpq defines the number of huge pages allcoated.
 *	 - @hpt especifyies the type of page (0 = 2M, 1 = 1GB)
 *
 *	ps.: huge pages should be reserved before executing this program.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <errno.h>

#define KB (1UL << 10)
#define MB (1UL << 20)
#define GB (1UL << 30)

#define HPQ_DEFAULT 1
#define HPT_DEFAULT 0 /* 0 = 2M, 1 = 1GB */

#define PMD_SIZE (2 * MB)
#define PUD_SIZE GB

int main(int argc, char *argv[])
{
	size_t hpq = HPQ_DEFAULT;
	unsigned int hpt = HPT_DEFAULT;
	
	char *buf_p;
	size_t size;

	if (argc == 3){
		hpq = atol(argv[1]);
		hpt = atoi(argv[2]);
	}

	size = hpq * (hpt ? PUD_SIZE : PMD_SIZE);
	
	/* TODO add support to PUD_SIZE huge pages, based on @hpt*/
	buf_p = (char *) mmap(NULL, size, PROT_READ, 
		MAP_PRIVATE|MAP_ANON|MAP_HUGETLB, 0, 0);
	
	if(buf_p == (void *) -1){
		printf("errno: %d, message: %s\n", errno, strerror(errno));
		return EXIT_FAILURE;		
	}

	/* FIXME it segfaults */
	//memset(buf_p, 0, size);

	sleep(120);

	munmap(buf_p, size);

	return EXIT_SUCCESS;
}
