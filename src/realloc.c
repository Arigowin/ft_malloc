#include "malloc.h"

// mutex
#include <pthread.h>
pthread_mutex_t	g_mutex;

void		*realloc(void *ptr, size_t size)
{
	void		*newptr;
	t_block		*tmp;

	/* pthread_mutex_lock(&g_mutex); */
	ft_putstr("-- REALLOC -> Start0 - ");
	ft_puthex(ptr);
	ft_putstr(" - ");
	ft_putnbrendl(size);

	tmp = NULL;
	if (ptr != NULL)
	{
		tmp = (t_block *)(ptr - sizeof(t_block));
	}
	ft_puthex(tmp);
	ft_putendl(" - tmp");
	if (tmp != NULL && search_addr(tmp) == NULL)
	{
		ft_putendl("FUCK2");
		pthread_mutex_unlock(&g_mutex);
		return (NULL);
	}

	ft_putendl("fuvgbhjrvbfyurjkfdhyukjrtgyugfuhik");
	newptr = malloc(size);
	if (ptr != NULL)
	{
		if (tmp->size <= size)
			newptr = ft_memcpy(newptr, ptr, tmp->size);
		else
			newptr = ft_memcpy(newptr, ptr, size);
		free(ptr);
	}

	show_alloc_mem();
	ft_putendl("-- REALLOC -> End0 RRRRRRRRRRRRRRRRRRRRRRRRRR");
	/* pthread_mutex_unlock(&g_mutex); */
	return (newptr);
}
