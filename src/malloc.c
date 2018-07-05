#include "malloc.h"

// mmap
#include <sys/types.h>
#include <sys/mman.h>

// getpagesize
#include <unistd.h>

// mutex
#include <pthread.h>
pthread_mutex_t	g_mutex;

// verifier la taille qui reste dans TINY si plus de place stocker dans SMALL
// pareil pour SMALL -> LARGE
// -> utiliser les block free

void			*add_block(size_t size, t_block *head)
{
	t_block		*tmp;

	ft_putendl("add_tiny_block");
	tmp = head;

	while (tmp->next != NULL)
		tmp = tmp->next;

	tmp->next = (void *)((void *)(tmp + 1) + tmp->size);
	tmp->next->size = size;
	tmp->next->is_free = 0;
	tmp->next->next = NULL;
	tmp->next->prev = tmp;

	ft_puthex(tmp->next);
	ft_putstr(" - ");
	ft_puthex((void *)(tmp->next + 1));
	ft_putstr(" - ");
	ft_puthex((void *)((void *)(tmp->next + 1) + tmp->next->size));
	ft_putendl("");

	return ((void *)(tmp->next + 1));
}

void			*add_large_block(size_t size)
{
	t_block		*tmp;

	ft_putendl("add_tiny_block");
	tmp = get_alloc()->large;

	while(tmp->next != NULL)
		tmp = tmp->next;

	if (MAP_FAILED == (tmp->next = mmap(NULL, size + sizeof(t_block),
					PROT_READ | PROT_WRITE,
					MAP_ANONYMOUS | MAP_PRIVATE, -1, 0)))
		return (NULL);

	tmp->next->size = size;
	tmp->next->is_free = 0;
	tmp->next->next = NULL;
	tmp->next->prev = tmp;

	ft_puthex(tmp->next);
	ft_putstr(" - ");
	ft_puthex((void *)(tmp->next + 1));
	ft_putstr(" - ");
	ft_puthex((void *)((void *)(tmp->next + 1) + tmp->next->size));
	ft_putendl("");

	return ((void *)(tmp->next + 1));
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
	ft_putnbrendl((size_t)(getpagesize() * TINY) / 100);
	ft_putnbrendl((size_t)(getpagesize() * TINY) / 655);
	ft_putnbrendl((size_t)(getpagesize() * SMALL) / 100);
	ft_putnbrendl((size_t)(getpagesize() * SMALL) / 2621);

	if (size < (size_t)(getpagesize() * TINY) / 100)
		ret = add_block(size, get_alloc()->tiny);
	else if (size < (size_t)(getpagesize() * SMALL) / 100)
		ret = add_block(size, get_alloc()->small);
	else
		ret = add_large_block(size);

	ft_putendl("-- MALLOC -> End0");
	pthread_mutex_unlock(&g_mutex);

	show_alloc_mem();
	return (ret);
}

// https://arjunsreedharan.org/post/148675821737/write-a-simple-memory-allocator
// http://www.inf.udec.cl/~leo/Malloc_tutorial.pdf
