#include "malloc.h"

// mmap
#include <sys/types.h>
#include <sys/mman.h>

// getpagesize
#include <unistd.h>

t_alloc		*g_alloc = NULL;

t_alloc		*get_alloc(void)
{
	if (g_alloc == NULL)
	{
		if (MAP_FAILED == (g_alloc = mmap(NULL, 0
						+ getpagesize() * 2,
						/* + getpagesize() + (100 * sizeof(t_block)), */
						PROT_READ | PROT_WRITE,
						MAP_ANONYMOUS | MAP_PRIVATE, -1, 0)))
			return (NULL);


		g_alloc->tiny = (t_block *)(g_alloc + 1);
		g_alloc->tiny->size = 0;
		g_alloc->tiny->next = NULL;
		g_alloc->tiny->is_free = 0;

		g_alloc->small = NULL;

		g_alloc->large = NULL;
	}
	return g_alloc;
}

