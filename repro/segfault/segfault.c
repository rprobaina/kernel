/*
 *	Program: segfault
 *	Author: Ricardo Robaina <rrobaina@redhat.com>
 *	Version: 1.0
 *	Date: 2022/04/11
 *
 *	This small program will trigger a segemntation fault, by acessing an unmaped aread.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>

#define LEN 4096

int main()
{
	void *addr;
	
	/* mapping a LEN-byte area */
	addr = mmap(NULL, LEN, PROT_WRITE|PROT_READ, MAP_PRIVATE|MAP_ANON, 0, 0);
	if(!addr)
		return EXIT_FAILURE;

	printf("A %d-byte memory area was created in %p\n", LEN, addr);
	
	/* unmapping the area */
	int err = munmap(addr, LEN);
	if(err)
		return EXIT_FAILURE;

	/* acessing the area after it was unmaped will generate a segfault */
	printf("Acessing a %d-byte unmaped area starting at: %p\n", LEN, addr);
	memset(addr, 0, LEN);

	return EXIT_SUCCESS;
}
