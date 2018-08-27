#include "malloc.h"

// mmap
#include <sys/types.h>
#include <sys/mman.h>

// getpagesize
#include <unistd.h>

t_alloc		*g_alloc = NULL;

t_alloc		*get_alloc(void)
{
	int tny;
	int sml;

	tny = 0;
	sml = 0;
	if (g_alloc == NULL)
	{
		tny = ((((TINY + sizeof(t_block)) * 100) / getpagesize()) + 1) * getpagesize();
		sml = ((((SMALL + sizeof(t_block)) * 100) / getpagesize()) + 1) * getpagesize();
		if (MAP_FAILED == (g_alloc = mmap(NULL,
						tny
						+ sml
						+ getpagesize(),
						PROT_READ | PROT_WRITE,
						MAP_ANONYMOUS | MAP_PRIVATE, -1, 0)))
			return (NULL);

		// ((((TINY + sizeof(t_block)) * 100) / getpagesize()) + 1) * getpagesize()

		ft_putstr("TINY - ");
		ft_putnbr((((TINY + sizeof(t_block)) * 100) / getpagesize()) + 1);
		ft_putstr(" - ");
		ft_putnbrendl(tny);
		g_alloc->tiny = (t_block *)(g_alloc + 1);
		g_alloc->tiny->size = tny;
		g_alloc->tiny->next = NULL;
		g_alloc->tiny->prev = NULL;
		g_alloc->tiny->is_free = 1;

		ft_putstr("SMALL - ");
		ft_putnbr((((SMALL + sizeof(t_block)) * 100) / getpagesize()) + 1);
		ft_putstr(" - ");
		ft_putnbrendl(sml);
		g_alloc->small = (t_block *)((void *)g_alloc->tiny + (g_alloc->tiny->size));
		g_alloc->small->size = sml;
		g_alloc->small->next = NULL;
		g_alloc->small->prev = NULL;
		g_alloc->small->is_free = 1;

		ft_putendl("LARGE");
		g_alloc->large = (t_block *)((void *)g_alloc->small + g_alloc->small->size);
		g_alloc->large->size = 0; // getpagesize() - sizeof(t_alloc)
		g_alloc->large->next = NULL;
		g_alloc->large->prev = NULL;
		g_alloc->large->is_free = 1;

		ft_putendl("END INIT");
	}
	return g_alloc;
}

t_block			*search_addr(void *addr)
{
	ft_putendl("SEARCH ADDR");
	t_block		*tmp;

	tmp = get_alloc()->tiny;
	while (tmp != NULL)
	{
		if (addr == tmp)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = get_alloc()->small;
	while (tmp != NULL)
	{
		if (addr == tmp)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = get_alloc()->large;
	while (tmp != NULL)
	{
		if (addr == tmp)
			return (tmp);
		tmp = tmp->next;
	}
	return NULL;
}
