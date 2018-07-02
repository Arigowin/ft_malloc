#include "malloc.h"

// mmap
#include <sys/types.h>
#include <sys/mman.h>

// getpagesize
#include <unistd.h>

// mutex
#include <pthread.h>
pthread_mutex_t	g_mutex;

void			*add_tiny_block(size_t size)
{
	t_block		*tmp;

	ft_putendl("add_tiny_block");
	tmp = get_alloc()->tiny;

	while (tmp->next != NULL)
		tmp = tmp->next;

	tmp->next = (t_block *)(tmp->data + tmp->size);
	tmp->next->size = size;
	tmp->next->is_free = 0;
	tmp->next->next = NULL;
	size_t i = 0;
	while(i < size + 1)
	{
		tmp->next->data[i] = '\0';
		i++;
	}
	return (tmp->next->data);
}

void			*malloc(size_t size)
{
	void		*ret;

	if (size <= 0)
		return NULL;

	pthread_mutex_lock(&g_mutex);
	ft_putendl("-- MALLOC -> Start0");
	ft_putstr("size -> ");
	ft_putnbrendl(size);

	ret = add_tiny_block(size);

	ft_putendl("-- MALLOC -> End0");
	pthread_mutex_unlock(&g_mutex);

	show_alloc_mem();
	return (ret);
}

// https://arjunsreedharan.org/post/148675821737/write-a-simple-memory-allocator
// http://www.inf.udec.cl/~leo/Malloc_tutorial.pdf
