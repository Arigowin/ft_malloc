#include "malloc.h"
#include <sys/mman.h>
#include <unistd.h>

void		free(void *ptr)
{
	munmap(ptr, 8 * getpagesize());
}
