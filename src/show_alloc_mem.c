#include "libft.h"
#include "malloc.h"

void		show_alloc_mem()
{
	t_node		*tmp;

	ft_putendl("\n\nSHOW ALLOC MEM");
	pthread_mutex_lock(&g_mutex);

	tmp = get_node();
	while (tmp != NULL)
	{
		ft_putstr("tmp -> ");
		ft_puthex(tmp);
		ft_putstr("tmp->size -> ");
		ft_putnbrendl(tmp->size);
		ft_putstr("tmp->is_free -> ");
		ft_putnbrendl(tmp->is_free);
		ft_putstr("tmp + sizeof(t_node) -> ");
		ft_puthex(tmp + sizeof(t_node));
		tmp = tmp->next;
	}

	pthread_mutex_unlock(&g_mutex);
	ft_putendl("END SHOW ALLOC MEM\n\n");
}
