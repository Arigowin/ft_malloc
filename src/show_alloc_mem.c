#include "libft.h"
#include "malloc.h"

void		show_alloc_mem()
{
	t_node		*tmp;

	ft_putendl("\n\nSHOW ALLOC MEM");
	pthread_mutex_lock(&g_mutex);

	ft_putstr("get_node() -> ");
	ft_puthex(get_node());
	tmp = get_node();
	while (tmp != NULL)
	{
		ft_putstr("tmp -> ");
		ft_puthex(tmp);
		ft_putstr("tmp + 1 -> ");
		ft_puthex(tmp + 1);
		tmp = tmp->next;
	}

	pthread_mutex_unlock(&g_mutex);
	ft_putendl("END SHOW ALLOC MEM\n\n");
}
