/**
 *	write a program that uses mmap to copy an arbitrary-size file to stdout.
 *	the filename should be passed as an cmdline argument.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

void mmapcopy(int fd, int size);

int main(int argc, char **argv)
{
	char *filename;
	int fd;
	struct stat stat; /* will hold details about a file */
	
	if(argc < 2){
		printf("usage: %s <filename>\n", argv[0]);
		return EXIT_FAILURE;
	}
	
	filename = argv[1];
	fd = open(filename, O_RDONLY);
	
	fstat(fd, &stat); /* getting details about fd */
	
	mmapcopy(fd, stat.st_size);

	return EXIT_SUCCESS;
}

/*
 *	mmapcopy will copy te contents of fd to stdout, using mmap.
 */
void mmapcopy(int fd, int size)
{
	char *buf_p; /* ptr to mamory-mapped VM area */

	buf_p =  mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
	write(1, buf_p, size);

	munmap(buf_p, size);
	return;
}
