#include "malloc.h"

// munmap
#include <sys/types.h>
#include <sys/mman.h>

// getpagesize
#include <unistd.h>

// mutex
#include <pthread.h>
pthread_mutex_t	g_mutex;

void			free(void *ptr)
{
	/* t_node	*tmp; */

	ft_putendl("-- FREE -> Start0");

	if (ptr == NULL)
		return;

	/* show_alloc_mem(); */
	pthread_mutex_lock(&g_mutex);

	/* tmp = get_node(); */
	/* ft_putendl("1"); */
	/* while (tmp->next != NULL) */
	/* { */
	/*     ft_putendl("2"); */
    /*  */
	/*     ft_putstr("ptr -> "); */
	/*     ft_puthex(ptr); */
	/*     ft_putstr("\n(void *)(tmp->next + sizeof(t_node)) -> "); */
	/*     ft_puthex((void *)(tmp->next + sizeof(t_node))); */
			/* ft_putendl(""); */
    /*  */
	/*     if (ptr == (void *)(tmp->next + sizeof(t_node))) */
	/*     { */
	/*         ft_putendl("FOUND1"); */
    /*  */
	/*         tmp->next->is_free = 1; */
	/*         // for TINY and SMALL */
	/*         if (munmap((void *)(tmp->next + sizeof(t_node)), tmp->next->size) == -1) */
	/*             ft_putendl("FREE_ERROR"); */
	/*         break; */
	/*     } */
    /*  */
	/*     tmp = tmp->next; */
	/*     ft_putendl("3"); */
	/* } */
    /*  */
	/* ft_putendl("4"); */
	/* if (tmp->next == NULL) */
	/*     ft_putendl("Not Found"); */

	pthread_mutex_unlock(&g_mutex);
	ft_putendl("-- FREE -> End0");
}
