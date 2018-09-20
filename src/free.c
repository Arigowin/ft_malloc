#include "malloc.h"

// munmap
#include <sys/types.h>
#include <sys/mman.h>

// getpagesize
#include <unistd.h>

// mutex
#include <pthread.h>
pthread_mutex_t	g_mutex;

void			stack_free_block(t_block *curr)
{
	if (DEBUG)
	{
		ft_putstr("STACK FREE BLOCKS start ");
		ft_puthex(curr);
		ft_putendl("");
	}

	if (curr->next != NULL && curr->next->is_free)
	{
		if (DEBUG)
		{
			ft_putstr("1Stack -> ");
			ft_puthex(curr);
			ft_putstr(" - ");
			ft_puthex(curr->next);
			ft_putendl("");
		}
		if (DEBUG)
		{
			ft_putstr("1[HJLK: curr: ");
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
		}
		curr->size += curr->next->size + sizeof(t_block);
		if (curr->next->next != NULL)
			curr->next->next->prev = curr;
		curr->next = curr->next->next;
		if (DEBUG)
		{
			ft_putstr("2[HJLK: curr: ");
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
		}
	}
	if (DEBUG)
		ft_putendl("STACK FREE BLOCKS end");
}

void			free(void *ptr)
{
	t_block		*tmp;

	pthread_mutex_lock(&g_mutex);
	if (DEBUG)
	{
		ft_putstr("-- FREE -> Start0 - ");
		ft_puthex(ptr);
		ft_putendl("");
	}

	if (ptr == NULL)
	{
		pthread_mutex_unlock(&g_mutex);
		return;
	}

	tmp = (t_block *)(ptr - sizeof(t_block));
	if (search_addr(tmp) == NULL || tmp->is_free == 1)
	{
		pthread_mutex_unlock(&g_mutex);
		return;
	}

	tmp->is_free = 1;

	if (DEBUG)
	{
		ft_putstr("Free -> ptr: ");
		ft_puthex(ptr);
		ft_putstr(" - tmp: ");
		ft_puthex(tmp);
		ft_putstr(" - size: ");
		ft_putnbr(tmp->size);
		ft_putendl("");
		ft_putendl(tmp->is_free == 1 ? "Free" : "Not Free");
	}

	ptr = NULL;

	if (tmp->size > SMALL)
	{
		if (DEBUG)
			ft_putendl("Free LARGE");
		if (tmp->next)
			tmp->next->prev = tmp->prev;
		if (tmp->prev)
			tmp->prev->next = tmp->next;
		munmap(tmp, tmp->size + sizeof(t_block));
	}
	else
	{
		if (DEBUG)
			ft_putendl("Free TNY SML");
		stack_free_block(tmp);
	}

	pthread_mutex_unlock(&g_mutex);
	if (DEBUG)
		ft_putendl("-- FREE -> End0");
}
