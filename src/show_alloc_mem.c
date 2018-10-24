#include "malloc.h"
#include <pthread.h>

pthread_mutex_t	g_mutex;

int				show_alloc(t_block *curr)
{
	int			total;

	total = 0;
	while (curr != NULL)
	{
		/* if (!curr->is_free) */
		/* { */
			if (DEBUG)
			{
				ft_puthex_fd((void *)(curr), 2);
				ft_putstr_fd(" - ", 2);
			}
			ft_puthex_fd((void *)(curr + 1), 2);
			ft_putstr_fd(" - ", 2);
			ft_puthex_fd((void *)((void *)(curr + 1) + curr->size), 2);
			ft_putstr_fd(" : ", 2);
			ft_putnbr_fd(curr->size, 2);
			if (DEBUG)
			{
				ft_putstr_fd(" octets free: ", 2);
				ft_putnbrendl_fd(curr->is_free, 2);
			}
			else
				ft_putendl_fd(" octets", 2);
			total += curr->size;
		/* } */
		curr = curr->next;
	}
	return (total);
}

void			show_alloc_mem(void)
{
	int total;

	pthread_mutex_lock(&g_mutex);
	ft_putstr_fd("TINY : ", 2);
	ft_puthex_fd(get_alloc()->tiny, 2);
	ft_putendl_fd("", 2);
	total = show_alloc(get_alloc()->tiny);
	ft_putstr_fd("SMALL : ", 2);
	ft_puthex_fd(get_alloc()->small, 2);
	ft_putendl_fd("", 2);
	total += show_alloc(get_alloc()->small);
	ft_putstr_fd("LARGE : ", 2);
	ft_puthex_fd(get_alloc()->large, 2);
	ft_putendl_fd("", 2);
	total += show_alloc(get_alloc()->large);
	ft_putstr_fd("Total : ", 2);
	ft_putnbr_fd(total, 2);
	ft_putendl_fd(" octets", 2);
	pthread_mutex_unlock(&g_mutex);
}
