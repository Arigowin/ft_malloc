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
	ft_putendl("STACK FREE BLOCKS start");

	if (curr->next != NULL && curr->next->is_free)
	{
		ft_putstr("1Stack -> ");
		ft_puthex(curr);
		ft_putstr(" - ");
		ft_puthex(curr->next);
		ft_putendl("");
		curr->size += curr->next->size + sizeof(t_block);
		ft_putendl("FUCK1");
		curr->next = curr->next->next;
	}
	/* if (curr->prev != NULL && curr->prev->is_free) */
	/* { */
	/*     ft_putstr("2Stack -> "); */
	/*     ft_puthex(curr); */
	/*     ft_putstr(" - "); */
	/*     ft_puthex(curr->prev); */
	/*     ft_putendl(""); */
	/*     curr->prev->size += curr->size + sizeof(t_block); */
	/*     curr->prev->next = curr->next; */
	/* } */
	ft_putendl("STACK FREE BLACKS end");
}

void			free(void *ptr)
{
	t_block		*tmp;

	pthread_mutex_lock(&g_mutex);
	ft_putstr("-- FREE -> Start0 - ");
	ft_puthex(ptr);
	ft_putendl("");

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

	ft_putstr("Free -> ptr: ");
	ft_puthex(ptr);
	ft_putstr(" - tmp: ");
	ft_puthex(tmp);
	ft_putstr(" - size: ");
	ft_putnbr(tmp->size);
	ft_putendl("");
	ft_putendl(tmp->is_free == 1 ? "Free" : "Not Free");

	ptr = NULL;

	if (tmp > get_alloc()->large)
	{
		ft_putendl("Free LARGE");
		if (tmp->next)
			tmp->next->prev = tmp->prev;
		if (tmp->prev)
			tmp->prev->next = tmp->next;
		munmap(tmp, tmp->size + sizeof(t_block));
	}
	else
	{
		ft_putendl("Free TNY SML");
		stack_free_block(tmp);
	}

	pthread_mutex_unlock(&g_mutex);
	ft_putendl("-- FREE -> End0");
}
