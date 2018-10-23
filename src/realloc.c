#include "malloc.h"
#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>
#include <stdint.h>
#include <pthread.h>

pthread_mutex_t	g_mutex;

void		*realloc(void *ptr, size_t size)
{
	if (DEBUG)
	{
		ft_putstr_fd("--------------------- Start Realloc ", 2);
		ft_puthex_fd(ptr, 2);
		ft_putchar_fd(' ', 2);
		ft_putnbrendl_fd(size, 2);
	}
	void		*newptr;
	t_block		*tmp;

	pthread_mutex_lock(&g_mutex);
	tmp = NULL;
	if (ptr != NULL)
		tmp = (t_block *)(ptr - sizeof(t_block));
	if (tmp != NULL && search_addr(tmp) == NULL)
	{
		if (DEBUG)
			ft_putendl_fd("*** END1 Realloc", 2);
		return (NULL);
	}
	pthread_mutex_unlock(&g_mutex);
	newptr = malloc(size);
	pthread_mutex_lock(&g_mutex);
	if (ptr != NULL)
	{
		if (DEBUG)
		{
			ft_putstr_fd("ABC ptr: ", 2);
			ft_puthex_fd(ptr, 2);
			ft_putstr_fd(" newptr: ", 2);
			ft_puthex_fd(newptr, 2);
			ft_putstr_fd(" tmp: ", 2);
			ft_puthex_fd(tmp, 2);
			ft_putchar_fd('\n', 2);
		}
		if (tmp->size <= size)
		{
			newptr = ft_memcpy(newptr, ptr, tmp->size);
		}
		else
		{
			newptr = ft_memcpy(newptr, ptr, size);
		}
		if (DEBUG)
		{
			ft_putstr_fd("DEF ptr: ", 2);
			ft_puthex_fd(ptr, 2);
			ft_putstr_fd(" newptr: ", 2);
			ft_puthex_fd(newptr, 2);
			ft_putstr_fd(" tmp: ", 2);
			ft_puthex_fd(tmp, 2);
			ft_putchar_fd('\n', 2);
		}
		pthread_mutex_unlock(&g_mutex);
		free(ptr);
		pthread_mutex_lock(&g_mutex);
	}
	if (DEBUG)
		ft_putendl_fd("******************** END Realloc", 2);
	pthread_mutex_unlock(&g_mutex);
	return (newptr);
}
