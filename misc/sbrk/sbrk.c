/* 
 *	It is a VERY simple dynamic memory allocator.
 *	limitation: the allocations and frees should be nested.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define VEC_SIZE 100

void *alloc_mem(size_t size);
void *free_mem(size_t size);

int main()
{
	/* usage example */
	void *brk_addr;
	unsigned long size_after, size_before; /* used to compute size */
	
	brk_addr = sbrk(0); /* getting the program break */
	printf("program break addr: 0x%lx\n", brk_addr);
	size_before = (unsigned long) brk_addr;

	/* allocating memory for an unsigned long */
	unsigned long *lv = (unsigned long *) alloc_mem(sizeof(unsigned long));	
	
	brk_addr = sbrk(0);
	printf("program break addr: 0x%lx\n", brk_addr);
	size_after = (unsigned long) brk_addr;

	/* using the dynamic allocated memory */
	*lv = 1;
	printf("addr: 0x%lx, val: %ld, size: %ld (bytes)\n", lv, *lv, size_after - size_before);

	/* freeing the allocated heep area */
	brk_addr = free_mem(sizeof(unsigned long));

	brk_addr = sbrk(0);
	printf("program break addr: 0x%lx\n", brk_addr);
	
	return EXIT_SUCCESS;
}

/* alloc_mem allocates size-bytes of memory in the heep  */
void *alloc_mem(size_t size)
{
	void *addr = sbrk(size);
	if (addr == (void *) 1)
		return NULL;
	
	return addr;
}

/* free_mem deallocates size-bytes of memory in the heep */
void *free_mem(size_t size)
{
	size = -1 * size;

	void *addr = sbrk(size);
	if (addr == (void *) 1)
		return NULL;
	
	return addr;
}
