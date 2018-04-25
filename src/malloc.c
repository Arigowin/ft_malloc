#include "malloc.h"
#include <sys/mman.h>
#include <unistd.h>

void		*malloc(size_t size)
{
	void *ret;
	write(1, "Start\n", 6);

	ret = mmap(NULL, size * getpagesize(), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE,
			-1, 0);

	write(1, "End\n", 4);

	return ret;
}
