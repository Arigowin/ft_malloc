#include "malloc.h"
#include <pthread.h>

pthread_mutex_t	g_mutex;

void			*calloc(size_t count, size_t size)
{
	if (DEBUG)
	{
		ft_putstr_fd("|||||||||||||||||||||||||||||||||||||||||||||||||||--- Start calloc ", 2);
		ft_putnbr_fd(count, 2);
		ft_putstr_fd(" ", 2);
		ft_putnbrendl_fd(size, 2);
	}
	void		*tmp;

	if (count == 0)
		count++;
	if ((tmp = malloc((count * size) + 1)) == NULL)
		return (NULL);
	pthread_mutex_lock(&g_mutex);
	ft_bzero(tmp, count * size);
	pthread_mutex_unlock(&g_mutex);
	if (DEBUG)
		ft_putendl_fd("*** END calloc", 2);
	return (tmp);
}
