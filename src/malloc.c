#include "libft.h"
#include "malloc.h"

// mmap
#include <sys/types.h>
#include <sys/mman.h>

// getpagesize
#include <unistd.h>

// mutex
#include <pthread.h>
pthread_mutex_t	g_mutex;

t_node		*get_free_block(size_t size)
{
	t_node	*curr;

	curr = get_node();
	while (curr->next != NULL)
	{
		if (curr->next->is_free && curr->next->size >= size)
		{
			ft_putendl("found free");
			return curr;
		}
		curr = curr->next;
	}
	return curr;
}

void		*malloc(size_t size)
{
	size_t		len;
	t_node		*header;
	t_alloc		*tmp = get_alloc();
	(void)tmp;

	if (size == 0)
		return NULL;

	pthread_mutex_lock(&g_mutex);
	ft_putendl_fd("-- MALLOC -> Start0", 2);

	header = get_free_block(size);

	if (header->next != NULL)
	{
		header->next->is_free = 0;
		ft_putendl_fd("-- MALLOC NOT NULL -> End0", 2);
		pthread_mutex_unlock(&g_mutex);
		return ((void *)(header->next + sizeof(t_node)));
	}

	len = size + sizeof(t_node);
	if (NULL == (header->next = mmap(NULL, len,
					PROT_READ | PROT_WRITE,
					MAP_ANONYMOUS | MAP_PRIVATE, -1, 0)))
	{
		pthread_mutex_unlock(&g_mutex);
		ft_putendl_fd("----------------------------------------- MMAP FAILED", 2);
		return (NULL);
	}

	header->next->size = size;
	header->next->is_free = 0;
	header->next->next = NULL;

	ft_putstr("header->next -> ");
	ft_puthex(header->next);
	ft_putstr("(void *)(header->next + sizeof(t_node)) -> ");
	ft_puthex((void *)(header->next + sizeof(t_node)));

	ft_putendl_fd("-- MALLOC -> End0", 2);
	pthread_mutex_unlock(&g_mutex);

	return ((void *)(header->next + sizeof(t_node)));
}

// https://arjunsreedharan.org/post/148675821737/write-a-simple-memory-allocator
// http://www.inf.udec.cl/~leo/Malloc_tutorial.pdf
