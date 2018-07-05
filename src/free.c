#include "malloc.h"

// munmap
#include <sys/types.h>
#include <sys/mman.h>

// getpagesize
#include <unistd.h>

// mutex
#include <pthread.h>
pthread_mutex_t	g_mutex;

/* void			stack_free_block(t_block *curr) */
/* { */
/*     if (curr->next != NULL && curr->next->is_free) */
/*     { */
/*         ft_putstr("1Stack -> "); */
/*         ft_puthex(curr); */
/*         ft_putstr(" - "); */
/*         ft_puthex(curr->next); */
/*         ft_putendl(""); */
/*         curr->size += curr->next->size + sizeof(t_block); */
/*         curr->next = curr->next->next; */
/*     } */
/*     if (curr->prev != NULL && curr->prev->is_free) */
/*     { */
/*         ft_putstr("2Stack -> "); */
/*         ft_puthex(curr); */
/*         ft_putstr(" - "); */
/*         ft_puthex(curr->prev); */
/*         ft_putendl(""); */
/*         curr->prev->size += curr->size + sizeof(t_block); */
/*         curr->prev->next = curr->next; */
/*     } */
/* } */

void			free(void *ptr)
{
	t_block		*tmp;

	ft_putendl("-- FREE -> Start0");

	if (ptr == NULL)
		return;

	tmp = (t_block *)(ptr - sizeof(t_block));

	ft_putstr("Free -> ptr: ");
	ft_puthex(ptr);
	ft_putstr(" - tmp: ");
	ft_puthex(tmp);
	ft_putendl("");
	tmp->is_free = 1;
	ft_putendl(tmp->is_free == 1 ? "Free" : "Not Free");

	/* stack_free_block(tmp); */

	pthread_mutex_lock(&g_mutex);

	pthread_mutex_unlock(&g_mutex);
	ft_putendl("-- FREE -> End0");
}
