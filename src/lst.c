#include "libft.h"
#include "malloc.h"

// mmap
#include <sys/types.h>
#include <sys/mman.h>

// getpagesize
#include <unistd.h>

t_alloc		*g_alloc = NULL;

void		init_tiny(void)
{
	int		i;
	t_node	*tmp;

	i = -1;
	g_alloc->size_tiny = TINY * getpagesize();
	if (NULL == (g_alloc->tiny = mmap(NULL, sizeof(t_node) * g_alloc->size_tiny,
					PROT_READ | PROT_WRITE,
					MAP_ANONYMOUS | MAP_PRIVATE, -1, 0)))
		return ;
	g_alloc->tiny->size = 0;
	g_alloc->tiny->is_free = 1;
	tmp = g_alloc->tiny;
	while (++i < 100)
	{
		if (NULL == (tmp->next = mmap(NULL, sizeof(t_node) * g_alloc->size_tiny,
						PROT_READ | PROT_WRITE,
						MAP_ANONYMOUS | MAP_PRIVATE, -1, 0)))
			return ;
		tmp->next->size = 0;
		tmp->next->is_free = 1;
		tmp = tmp->next;
	}
	tmp->next = NULL;
}

void		init_small(void)
{
	int		i;
	t_node	*tmp;

	i = -1;
	g_alloc->size_small = SMALL * getpagesize();
	if (NULL == (g_alloc->small = mmap(NULL, sizeof(t_node) * g_alloc->size_small,
					PROT_READ | PROT_WRITE,
					MAP_ANONYMOUS | MAP_PRIVATE, -1, 0)))
		return ;
	g_alloc->small->size = 0;
	g_alloc->small->is_free = 0;
	g_alloc->small->next = NULL;
	tmp = g_alloc->small;
	while (++i < 100)
	{
		if (NULL == (tmp->next = mmap(NULL, sizeof(t_node) * g_alloc->size_small,
						PROT_READ | PROT_WRITE,
						MAP_ANONYMOUS | MAP_PRIVATE, -1, 0)))
			return ;
		tmp->next->size = 0;
		tmp->next->is_free = 1;
		tmp = tmp->next;
	}
	tmp->next = NULL;
}

t_alloc		*get_alloc(void)
{
	if (g_alloc == NULL)
	{
		if (NULL == (g_alloc = mmap(NULL, sizeof(t_alloc),
						PROT_READ | PROT_WRITE,
						MAP_ANONYMOUS | MAP_PRIVATE, -1, 0)))
		{
			ft_putendl_fd("----------------------------------------- MMAP FAILED", 2);
			return NULL;
		}
		init_tiny();
		init_small();

		g_alloc->large = NULL;
	}
	return g_alloc;
}

t_node		*g_node = NULL;

t_node		*get_node(void)
{
	if (g_node == NULL)
	{
		if (NULL == (g_node = mmap(NULL, sizeof(t_node),
						PROT_READ | PROT_WRITE,
						MAP_ANONYMOUS | MAP_PRIVATE, -1, 0)))
		{
			ft_putendl_fd("----------------------------------------- MMAP FAILED", 2);
			return NULL;
		}
		g_node->size = -sizeof(t_node);
		g_node->is_free = 0;
		g_node->next = NULL;
		ft_putendl("alloc g_node");
	}

	return (g_node);
}

