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
		if (MAP_FAILED == (g_alloc = mmap(NULL,
						getpagesize() * TINY
						+ getpagesize() * SMALL
						+ getpagesize(),
						PROT_READ | PROT_WRITE,
						MAP_ANONYMOUS | MAP_PRIVATE, -1, 0)))
			return (NULL);

		ft_putendl("TINY");
		g_alloc->tiny = (t_block *)(g_alloc + 1);
		g_alloc->tiny->size = 0; // getpagesize() * TINY;
		g_alloc->tiny->next = NULL;
		g_alloc->tiny->prev = NULL;
		g_alloc->tiny->is_free = 1;

		ft_putendl("SMALL");
		g_alloc->small = (t_block *)((void *)g_alloc->tiny + (getpagesize() * TINY));
		g_alloc->small->size = 0; // getpagesize() * SMALL;
		g_alloc->small->next = NULL;
		g_alloc->small->prev = NULL;
		g_alloc->small->is_free = 1;

		ft_putendl("LARGE");
		g_alloc->large = (t_block *)((void *)g_alloc->small + (getpagesize() * SMALL));
		g_alloc->large->size = 0; // getpagesize() - sizeof(t_alloc)
		g_alloc->large->next = NULL;
		g_alloc->large->prev = NULL;
		g_alloc->large->is_free = 1;

		ft_putendl("END INIT");
	}
	return g_alloc;
}

