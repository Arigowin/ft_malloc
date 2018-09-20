#include "malloc.h"

// getrlimit
#include <sys/time.h>
#include <sys/resource.h>

#include <stdio.h>
#include <stdint.h>
// mutex
/* #include <pthread.h> */
/* pthread_mutex_t	g_mutex; */

void		*realloc(void *ptr, size_t size)
{
	void		*newptr;
	t_block		*tmp;

	if (DEBUG)
	{
		ft_putstr("-- REALLOC -> Start0 - ");
		ft_puthex(ptr);
		ft_putstr(" - ");
		ft_putnbrendl(size);
	}

	tmp = NULL;
	if (ptr != NULL)
	{
		tmp = (t_block *)(ptr - sizeof(t_block));
	}
	if (DEBUG)
	{
		ft_puthex(tmp);
		ft_putendl(" - tmp");
	}
	if (tmp != NULL && search_addr(tmp) == NULL)
	{
		if (DEBUG)
			ft_putendl("FUCK2");
		return (NULL);
	}

	newptr = malloc(size);
	if (ptr != NULL)
	{
		if (tmp->size <= size)
			newptr = ft_memcpy(newptr, ptr, tmp->size);
		else
			newptr = ft_memcpy(newptr, ptr, size);
		free(ptr);
	}

	if (DEBUG)
	{
		show_alloc_mem();
		ft_putendl("-- REALLOC -> End0 RRRRRRRRRRRRRRRRRRRRRRRRRR");
	}
	return (newptr);
}
