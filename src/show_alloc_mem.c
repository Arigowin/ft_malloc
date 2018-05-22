#include "libft.h"
#include "malloc.h"

// mutex
#include <pthread.h>
pthread_mutex_t	g_mutex;

void			show_alloc(t_node *curr)
{

	while (curr != NULL)
	{
		if (!curr->is_free)
		{
			ft_puthex(curr + sizeof(t_node));
			ft_putstr(" - ");
			ft_puthex(curr + curr->size + sizeof(t_node));
			ft_putstr(" : ");
			ft_putnbr(curr->size);
			ft_putstr(" octets");
			ft_putstr(" free : ");
			ft_putnbrendl(curr->is_free);
		}
		curr = curr->next;
	}
}

void			show_alloc_mem(void)
{

	ft_putendl("\n\nSHOW ALLOC MEM");
	pthread_mutex_lock(&g_mutex);

	ft_putstr("TINY : ");
	ft_puthex(get_alloc()->tiny);
	ft_putendl("");
	show_alloc(get_alloc()->tiny);
	ft_putstr("SMALL : ");
	ft_puthex(get_alloc()->small);
	ft_putendl("");
	show_alloc(get_alloc()->small);
	ft_putstr("LARGE : ");
	ft_puthex(get_alloc()->large);
	ft_putendl("");
	show_alloc(get_alloc()->large);

	pthread_mutex_unlock(&g_mutex);
	ft_putendl("END SHOW ALLOC MEM\n\n");
}
