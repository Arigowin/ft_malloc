#include "libft.h"
#include "malloc.h"

// mmap
#include <sys/types.h>
#include <sys/mman.h>

// getpagesize
#include <unistd.h>

t_alloc		*g_alloc = NULL;

t_alloc		*get_alloc(void)
{
	int			max_tiny;
	int			max_small;

	if (g_alloc == NULL)
	{
		max_tiny = (((100 * (TINY + sizeof(t_node))) / getpagesize()) + 1) * getpagesize();
		max_small = (((100 * (SMALL + sizeof(t_node))) / getpagesize())  + 1) * getpagesize();

		if (NULL == (g_alloc = mmap(NULL, sizeof(t_alloc)
						+ max_tiny + max_small + sizeof(t_node),
						PROT_READ | PROT_WRITE,
						MAP_ANONYMOUS | MAP_PRIVATE, -1, 0)))
		{
			ft_putendl_fd("----------------------------------------- MMAP FAILED", 2);
			return NULL;
		}

		ft_putstr("g_alloc -> ");
		ft_puthex(g_alloc);
		ft_putendl("");

		g_alloc->size_tiny = max_tiny;
		g_alloc->tiny = (t_node *)(g_alloc + sizeof(t_alloc));
		g_alloc->tiny->size = SMALL;
		g_alloc->tiny->is_free = 1;
		g_alloc->tiny->next = NULL;

		ft_putstr("g_alloc->tiny -> ");
		ft_puthex(g_alloc->tiny);
		ft_putendl("");

		g_alloc->size_small = max_small;
		g_alloc->small = (t_node *)((char *)g_alloc->tiny + g_alloc->size_tiny);
		g_alloc->small->size = SMALL;
		g_alloc->small->is_free = 1;
		g_alloc->small->next = NULL;

		ft_putstr("g_alloc->small -> ");
		ft_puthex(g_alloc->small);
		ft_putendl("");

		g_alloc->large = (t_node *)((char *)g_alloc->small + g_alloc->size_small);
		g_alloc->large->size = SMALL;
		g_alloc->large->is_free = 1;
		g_alloc->large->next = NULL;

		ft_putstr("g_alloc->large -> ");
		ft_puthex(g_alloc->large);
		ft_putendl("");
	}
	return g_alloc;
}

