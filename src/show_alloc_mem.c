#include "malloc.h"
#include <pthread.h>

pthread_mutex_t	g_mutex;

int				show_alloc(t_block *curr)
{
	int			total;

	total = 0;
	while (curr != NULL)
	{
		if (!curr->is_free)
		{
			ft_puthex((void *)(curr + 1));
			ft_putstr(" - ");
			ft_puthex((void *)((void *)(curr + 1) + curr->size));
			ft_putstr(" : ");
			ft_putnbr(curr->size);
			ft_putendl(" octets");
			total += curr->size;
		}
		curr = curr->next;
	}
	return (total);
}

void			show_alloc_mem(void)
{
	int total;

	pthread_mutex_lock(&g_mutex);
	ft_putstr("TINY : ");
	ft_puthex(get_alloc()->tiny);
	ft_putendl("");
	total = show_alloc(get_alloc()->tiny);
	ft_putstr("SMALL : ");
	ft_puthex(get_alloc()->small);
	ft_putendl("");
	total += show_alloc(get_alloc()->small);
	ft_putstr("LARGE : ");
	ft_puthex(get_alloc()->large);
	ft_putendl("");
	total += show_alloc(get_alloc()->large);
	ft_putstr("Total : ");
	ft_putnbr(total);
	ft_putendl(" octets");
	pthread_mutex_unlock(&g_mutex);
}
