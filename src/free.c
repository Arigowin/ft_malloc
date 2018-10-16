#include "malloc.h"
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t	g_mutex;

void			stack_free_block(t_block *curr)
{
	if (curr->next != NULL && curr->next->is_free)
	{
		curr->size += curr->next->size + sizeof(t_block);
		if (curr->next->next != NULL)
			curr->next->next->prev = curr;
		curr->next = curr->next->next;
	}
}

void			free(void *ptr)
{
	t_block		*tmp;

	pthread_mutex_lock(&g_mutex);
	if (ptr == NULL)
	{
		pthread_mutex_unlock(&g_mutex);
		return ;
	}
	tmp = (t_block *)(ptr - sizeof(t_block));
	if (search_addr(tmp) == NULL || tmp->is_free == 1)
	{
		pthread_mutex_unlock(&g_mutex);
		return ;
	}
	tmp->is_free = 1;
	ptr = NULL;
	if (tmp->size > SMALL)
	{
		if (tmp->next)
			tmp->next->prev = tmp->prev;
		if (tmp->prev)
			tmp->prev->next = tmp->next;
		munmap(tmp, tmp->size + sizeof(t_block));
	}
	else
		stack_free_block(tmp);
	pthread_mutex_unlock(&g_mutex);
}
