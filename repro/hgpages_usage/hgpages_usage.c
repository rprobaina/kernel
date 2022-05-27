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
#include <linux/mman.h>
#include <string.h>
#include <errno.h>

#define MB (1UL << 20)
#define GB (1UL << 30)

#define HPQ_DEFAULT 1
#define HPT_DEFAULT 0 /* 0 = 2M, 1 = 1GB */

#define PMD_SIZE (2 * MB)
#define PUD_SIZE GB

#define SLEEP_TIME 120

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
	
	if (!hpt){ 
		/* 2M hugepage */
		buf_p = (char *) mmap(NULL, size, PROT_READ, 
			MAP_PRIVATE|MAP_ANON|MAP_HUGETLB|MAP_HUGE_2MB, 0, 0); 
	}else{ 
		/* 1GB hugepage */
		buf_p = (char *) mmap(NULL, size, PROT_READ, 
			MAP_PRIVATE|MAP_ANON|MAP_HUGETLB|MAP_HUGE_1GB, 0, 0); 
	}

	if(buf_p == (void *) -1){
		printf("errno: %d, message: %s\n", errno, strerror(errno));
		return EXIT_FAILURE;		
	}

	sleep(SLEEP_TIME);

	munmap(buf_p, size);

	return EXIT_SUCCESS;
}
