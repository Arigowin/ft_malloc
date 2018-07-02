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

	pthread_mutex_lock(&g_mutex);

	pthread_mutex_unlock(&g_mutex);
	ft_putendl("-- FREE -> End0");
}
