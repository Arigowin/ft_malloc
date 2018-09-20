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

t_block			*find_first_free(size_t size, t_block *head)
{
	t_block		*tmp;

	if (DEBUG)
		ft_putendl("find_first_free start");
	tmp = head;
	while (tmp->next != NULL)
	{
		/* ft_putstr("2 - "); */
		/* ft_putnbr(i++); */
		/* ft_putstr(" - "); */
		/* ft_puthex(tmp); */
		/* ft_putstr(" - "); */
		/* ft_putnbr(tmp->is_free); */
		/* ft_putstr(" - "); */
		/* ft_putnbr(tmp->size); */
		/* ft_putstr(" - "); */
		/* ft_puthex(tmp->next); */
		/* ft_putendl(""); */
		if (tmp->is_free && tmp->size >= size + sizeof(t_block))
		{
			if (DEBUG)
				ft_putendl("find_first_free end2");
			return tmp;
		}
		/* ft_putendl("3"); */
		tmp = tmp->next;
	}
	if (DEBUG)
		ft_putendl("find_first_free end");
	return (tmp);
}

void			*add_block(size_t size, t_block *head)
{
	t_block		*curr;
	t_block		*next;

	if (DEBUG)
		ft_putendl("add_block");
	curr = find_first_free(size, head);
	next = curr->next;

	if ((long)(curr->size - size - sizeof(t_block)) >= 0)
	{
		if (DEBUG)
			ft_putendl("FUCK");
		curr->next = (void *)((void *)(curr + 1) + size);
		curr->next->size = curr->size - size - sizeof(t_block);
		curr->next->is_free = 1;
		curr->next->next = next;
		curr->next->prev = curr;
		if (curr->prev != NULL)
		{
			if (DEBUG)
				ft_putendl("FUHA");
			curr->prev->next = curr;
		}
	}
	else if (curr->next == NULL)
	{
		if (DEBUG)
			ft_putendl("XXX");
		return (NULL);
	}
	curr->size = size;
	curr->is_free = 0;

	if (DEBUG)
	{
		ft_putstr("[FIRST: curr: ");
		ft_puthex(curr);
		ft_putstr(" - ->prev: ");
		ft_puthex(curr->prev);
		ft_putstr(" - ->next: ");
		ft_puthex(curr->next);
		ft_putstr(" - ->prev->next: ");

		if (curr->prev != NULL)
			ft_puthex(curr->prev->next);
		ft_putstr(" - ->next->prev: ");
		if (curr->next != NULL)
			ft_puthex(curr->next->prev);
		ft_putstr(" - ->prev->prev: ");
		if (curr->prev != NULL)
			ft_puthex(curr->prev->prev);
		ft_putstr(" - ->next->next: ");
		if (curr->next != NULL)
			ft_puthex(curr->next->next);
		ft_putendl("]");

		ft_putendl("add_block end");
	}
	return ((void *)(curr + 1));
}

void			*add_large_block(size_t size)
{
	t_block		*tmp;

	if (DEBUG)
		ft_putendl("add_large_block");
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

	if (DEBUG)
	{
		ft_puthex(tmp->next);
		ft_putstr(" - ");
		ft_puthex((void *)(tmp->next + 1));
		ft_putstr(" - ");
		ft_puthex((void *)((void *)(tmp->next + 1) + tmp->next->size));
		ft_putendl("");
	}

	return ((void *)(tmp->next + 1));
}

void			*malloc(size_t size)
{
	void		*ret;

	ret = NULL;

	pthread_mutex_lock(&g_mutex);
	if (DEBUG)
	{
		ft_putendl("-- MALLOC -> Start0");
		ft_putstr("size -> ");
		ft_putnbrendl(size);
	}

	if (size <= 0)
	{
		pthread_mutex_unlock(&g_mutex);
		return (ret);
	}

	if (size <= (size_t)(TINY))
	{
		if (DEBUG)
			ft_putendl("TINY");
		ret = add_block(size, get_alloc()->tiny);
	}
	if (ret == NULL && size <= (size_t)(SMALL))
	{
		if (DEBUG)
			ft_putendl("SMALL");
		ret = add_block(size, get_alloc()->small);
	}
	if (ret == NULL)
	{
		if (DEBUG)
			ft_putendl("LARGE");
		ret = add_large_block(size);
	}

	if (DEBUG)
		ft_putendl("-- MALLOC -> End0");
	pthread_mutex_unlock(&g_mutex);

	if (DEBUG)
		show_alloc_mem();
	return (ret);
}

// OPTI
// 	- stack free
// 	- pointer on the last node
// 	- set TINY and SMALL correctly
// 	- realloc

// https://arjunsreedharan.org/post/148675821737/write-a-simple-memory-allocator
// http://www.inf.udec.cl/~leo/Malloc_tutorial.pdf
