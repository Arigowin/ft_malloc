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

t_node			*get_free_block(t_node *head, size_t size, size_t max)
{
	t_node		*tmp;

	tmp = head;
	while (tmp->next != NULL)
	{
		if (tmp->next->is_free && tmp->next->size >= size)
		{
			ft_putendl("found free");
			ft_puthex(tmp->next);
			ft_putendl("");
			tmp->next->is_free = 0;
			tmp->next->size = size;
			return (tmp->next);
		}
		tmp = tmp->next;
	}
	ft_putstr("tmp -> ");
	ft_puthex(tmp);
	ft_putendl("");

	ft_putstr("total -> ");
	ft_puthex(tmp + tmp->size + sizeof(t_node));
	ft_putendl("");

	ft_putstr("max -> ");
	ft_puthex((t_node *)((char *)head + max));
	ft_putendl("");

	if (tmp + sizeof(t_node) + tmp->size > (t_node *)((char *)head + max))
	{
		ft_putendl("******************************************************************* ERROR");
		return NULL;
	}
	tmp->next = (t_node *)(tmp + tmp->size + sizeof(t_node));
	tmp->next->is_free = 0;
	tmp->next->size = size;
	tmp->next->next = NULL;
	return (tmp->next);
}

void			*malloc(size_t size)
{
	t_node		*header;
	t_node		*ret;

	if (size <= 0)
		return NULL;

	pthread_mutex_lock(&g_mutex);
	ft_putendl_fd("-- MALLOC -> Start0", 2);
	ft_putstr("size -> ");
	ft_putnbrendl(size);

	if (size <= TINY)
	{
		ft_putendl("TINY");
		ret = get_free_block(get_alloc()->tiny, size, get_alloc()->size_tiny);
		ft_puthex(ret);
		ft_putendl("");
		ft_puthex((void *)(ret + sizeof(t_node)));
		ft_putendl("");
		show_alloc_mem();
		return ((void *)(ret + sizeof(t_node)));
	}
	if (size <= SMALL)
	{
		ft_putendl("SMALL");
		ret = get_free_block(get_alloc()->small, size, get_alloc()->size_small);
		ft_puthex(ret);
		ft_putendl("");
		ft_puthex((void *)(ret + sizeof(t_node)));
		ft_putendl("");
		show_alloc_mem();
		return ((void *)(ret + sizeof(t_node)));
	}

	ft_putendl("LARGE");
	header = get_free_block(get_alloc()->large, size, -1); //  CHANGE MAX

	if (header != NULL)
	{
		header->is_free = 0;
		ft_putendl_fd("-- MALLOC NOT NULL -> End0", 2);
		pthread_mutex_unlock(&g_mutex);
		return ((void *)(header + sizeof(t_node)));
	}

	if (NULL == (header = mmap(NULL, size + sizeof(t_node),
					PROT_READ | PROT_WRITE,
					MAP_ANONYMOUS | MAP_PRIVATE, -1, 0)))
	{
		pthread_mutex_unlock(&g_mutex);
		ft_putendl_fd("----------------------------------------- MMAP FAILED", 2);
		return (NULL);
	}

	header->size = size;
	header->is_free = 0;
	header->next = NULL;

	ft_putstr("header -> ");
	ft_puthex(header);
	ft_putstr("\n(void *)(header + sizeof(t_node)) -> ");
	ft_puthex((void *)(header + sizeof(t_node)));
	ft_putendl("");

	ft_putendl_fd("-- MALLOC -> End0", 2);
	pthread_mutex_unlock(&g_mutex);

	show_alloc_mem();
	return ((void *)(header + sizeof(t_node)));
}

// https://arjunsreedharan.org/post/148675821737/write-a-simple-memory-allocator
// http://www.inf.udec.cl/~leo/Malloc_tutorial.pdf
