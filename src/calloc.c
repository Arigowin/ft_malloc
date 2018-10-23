#include "malloc.h"
#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>
#include <stdint.h>
#include <pthread.h>

pthread_mutex_t	g_mutex;

void			*calloc(size_t count, size_t size)
{
	if (DEBUG)
		ft_putendl_fd("--- Start calloc", 2);
	void		*tmp;

	tmp = malloc(count * size);
	pthread_mutex_lock(&g_mutex);
	ft_bzero(tmp, count * size);
	pthread_mutex_unlock(&g_mutex);
	if (DEBUG)
		ft_putendl_fd("*** END calloc", 2);
	return (tmp);
}
