#include "malloc.h"
#include <pthread.h>

pthread_mutex_t	g_mutex;

void		*realloc(void *ptr, size_t size)
{
	void		*newptr;
	t_block		*tmp;

	pthread_mutex_lock(&g_mutex);
	tmp = NULL;
	if (ptr != NULL)
		tmp = (t_block *)(ptr - sizeof(t_block));
	if (tmp != NULL && search_addr(tmp) == NULL)
		return (NULL);
	pthread_mutex_unlock(&g_mutex);
	newptr = malloc(size);
	pthread_mutex_lock(&g_mutex);
	if (ptr != NULL)
	{
		if (tmp->size <= size)
			newptr = ft_memcpy(newptr, ptr, tmp->size);
		else
			newptr = ft_memcpy(newptr, ptr, size);
		pthread_mutex_unlock(&g_mutex);
		free(ptr);
		pthread_mutex_lock(&g_mutex);
	}
	pthread_mutex_unlock(&g_mutex);
	return (newptr);
}
