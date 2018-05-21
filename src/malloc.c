#include "libft.h"
#include "malloc.h"

// mmap
#include <sys/types.h>
#include <sys/mman.h>

// getpagesize
#include <unistd.h>

// mutex
#include <pthread.h>

t_node		*get_free_block(size_t size)
{
	t_node	*curr;

	curr = get_node();
	while (curr->next != NULL)
	{
		if (curr->next->is_free && curr->next->size >= size)
		{
			ft_putendl("found free");
			return curr->next;
		}
		curr = curr->next;
	}
	ft_putendl("no found free");
	return curr;
}

void		*malloc(size_t size)
{
	size_t len;
	t_node *header;
	t_node *new;

	ft_putendl_fd("-- MALLOC -> Start0", 2);
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
		return ((void *)header->next + 1);
	}

	len = size + sizeof(t_node);
	new = mmap(NULL, len,
			PROT_READ | PROT_WRITE,
			MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (new == NULL)
		return (NULL);

	header->next = new;
	header->next->size = size;
	header->next->is_free = 0;
	header->next->next = NULL;

	ft_putstr("header->next -> ");
	ft_puthex(header->next);
	ft_putstr("get_node()->next -> ");
	ft_puthex(get_node()->next);
	ft_putstr("header->next + 1 -> ");
	ft_puthex(header->next + 1);

	/* if (get_node()->next == NULL) */
	/*     get_node() = header->next; */

	show_alloc_mem();
	ft_putendl_fd("-- MALLOC -> End0", 2);
	pthread_mutex_unlock(&g_mutex);

	return ((void *)header + 1);
}

// https://arjunsreedharan.org/post/148675821737/write-a-simple-memory-allocator
// http://www.inf.udec.cl/~leo/Malloc_tutorial.pdf
