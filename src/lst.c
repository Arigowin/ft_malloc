#include "malloc.h"

// mmap
#include <sys/types.h>
#include <sys/mman.h>

// getpagesize
#include <unistd.h>

void		init_tiny(void)
{
	g_lst->size_tiny = sizeof(t_node) * TINY  * getpagesize();
	g_lst->tiny = (t_node *)(g_lst + 1);
	g_lst->tiny->end = g_lst->tiny + 2;
	g_lst->tiny->next = NULL;
}

void		init_small(void)
{
	g_lst->size_small = sizeof(t_node) * SMALL * getpagesize();
	g_lst->small = (t_node *)((char *)g_lst->tiny + g_lst->size_tiny);
	g_lst->small->end = g_lst->small + 1;
	g_lst->small->next = NULL;
}

void		init_large(void)
{
	g_lst->large = (t_node *)(g_lst->tiny + 1);
	g_lst->large->end = g_lst->large + 1;
	g_lst->large->next = NULL;
}

t_lst		*get_lst(void)
{
	if (g_lst == NULL)
	{
		write(1, "Start2\n", 7);
		if (NULL == (g_lst = mmap(NULL,
						sizeof(t_lst)
						+ sizeof(t_node) * 100 * getpagesize() * TINY
						+ sizeof(t_node) * 100 * getpagesize() * SMALL,
						PROT_READ | PROT_WRITE,
						MAP_ANONYMOUS | MAP_PRIVATE, -1, 0)))
			return NULL; // error

		init_tiny();
		init_small();
		init_large();

		write(1, "End2\n", 5);
	}

	return g_lst;
}

