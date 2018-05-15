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
	show_alloc_mem();

	if (ptr == NULL)
		return;

	pthread_mutex_lock(&g_mutex);
	ft_putstr("ptr -> ");
	ft_puthex(ptr);
	ft_putstr("ptr - 1 -> ");
	ft_puthex((t_node *)ptr - 1);

	tmp = get_node()->next;
	while (tmp != NULL)
	{
		if (ptr == (void *)(tmp + 1))
		{
			ft_putendl("Found");
			tmp->is_free = 1;
			if (munmap((void *)tmp, tmp->size + sizeof(t_node)) == -1)
				ft_putendl("FREE_ERROR");
			break;
		}
		tmp = tmp->next;
	}

	pthread_mutex_unlock(&g_mutex);
	ft_putendl_fd("-- FREE -> End0", 2);
}
