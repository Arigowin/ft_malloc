#include "libft.h"
#include "malloc.h"

// mmap
#include <sys/types.h>
#include <sys/mman.h>

// getpagesize
#include <unistd.h>

/* t_lst		*get_lst(void) */
/* { */
/*     if (g_lst == NULL) */
/*     { */
/*         ft_putendl_fd("Start2", 2); */
/*         g_lst = mmap(NULL, sizeof(t_lst), */
/*                 PROT_READ | PROT_WRITE, */
/*                 MAP_ANONYMOUS | MAP_PRIVATE, -1, 0); */
/*         if (g_lst == NULL) */
/*             return NULL; */
/*  */
/*         g_lst->large = mmap(NULL, sizeof(t_node) + getpagesize(), */
/*                 PROT_READ | PROT_WRITE, */
/*                 MAP_ANONYMOUS | MAP_PRIVATE, -1, 0); */
/*         if (g_lst->large == NULL) */
/*             return NULL; */
/*  */
/*         g_lst->large->size = sizeof(t_node) + getpagesize(); */
/*         g_lst->large->is_free = 1; */
/*         g_lst->large->next = NULL; */
/*  */
/*         ft_putendl_fd("End2", 2); */
/*     } */
/*     return g_lst; */
/* } */

t_node			*g_node = NULL;

t_node		*get_node(void)
{
	if (g_node == NULL)
	{
		g_node = mmap(NULL, sizeof(t_node),
				PROT_READ | PROT_WRITE,
				MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
		g_node->size = sizeof(t_node);
		g_node->is_free = 0;
		g_node->next = NULL;
		ft_putendl("alloc g_node");
		ft_putstr("g_node -> ");
		ft_puthex(g_node);
	}

	return (g_node);
}

