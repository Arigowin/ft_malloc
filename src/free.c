#include "libft.h"
#include "malloc.h"

// munmap
#include <sys/types.h>
#include <sys/mman.h>

// getpagesize
#include <unistd.h>

// mutex
#include <pthread.h>

void		free(void *ptr)
{
	t_node	*tmp;

	ft_putendl_fd("-- FREE -> Start0", 2);

	if (ptr == NULL)
		return;

	pthread_mutex_lock(&g_mutex);

	tmp = get_node();
	ft_putendl("1");
	while (tmp->next != NULL)
	{
		ft_putendl("2");

		ft_putstr("ptr -> ");
		ft_puthex(ptr);
		ft_putstr("(void *)(tmp->next + sizeof(t_node)) -> ");
		ft_puthex((void *)(tmp->next + sizeof(t_node)));

		if (ptr == (void *)(tmp->next + sizeof(t_node)))
		{
			ft_putendl("FOUND1");

			tmp->next->is_free = 1;
			// for TINY and SMALL
			if (munmap((void *)(tmp->next + sizeof(t_node)), tmp->next->size) == -1)
				ft_putendl("FREE_ERROR");
			break;
		}

		tmp = tmp->next;
		ft_putendl("3");
	}

	ft_putendl("4");
	if (tmp->next == NULL)
		ft_putendl("Not Found");

	pthread_mutex_unlock(&g_mutex);
	show_alloc_mem();
	ft_putendl_fd("-- FREE -> End0", 2);
}
