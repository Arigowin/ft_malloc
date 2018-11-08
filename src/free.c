#include "malloc.h"
#include <sys/mman.h>
#include <pthread.h>

pthread_mutex_t	g_mutex;

void			stack_block(t_block *curr)
{
	if (DEBUG)
		ft_putendl_fd("stack_block", 2);

	curr->size = curr->size + (curr->next->size + sizeof(t_block));
	if (curr->next->next != NULL)
		curr->next->next->prev = curr;
	curr->next = curr->next->next;
}

void			stack_free_block(void)
{
	if (DEBUG)
		ft_putendl_fd("stack_free_block", 2);

	if (DEBUG)
	{
		pthread_mutex_unlock(&g_mutex);
		show_alloc_mem();
		pthread_mutex_lock(&g_mutex);
	}
	t_block *tmp;

	tmp = get_alloc()->tiny;
	if (DEBUG)
		ft_putendl_fd("TINY", 2);
	while (tmp->next != NULL)
	{
		if (tmp->is_free && tmp->next->is_free)
		{
			stack_block(tmp);
			if (tmp->next == NULL)
				break;
		}
		tmp = tmp->next;
	}
	tmp = get_alloc()->small;
	if (DEBUG)
		ft_putendl_fd("SMALL", 2);
	while (tmp->next != NULL)
	{
		if (tmp->is_free && tmp->next->is_free)
		{
			stack_block(tmp);
			if (tmp->next == NULL)
				break;
		}
		tmp = tmp->next;
	}
	if (DEBUG)
	{
		pthread_mutex_unlock(&g_mutex);
		show_alloc_mem();
		pthread_mutex_lock(&g_mutex);
	}
}

void			free_large(t_block **large)
{
	if (DEBUG)
		ft_putendl_fd("free_large", 2);
	if ((*large)->next)
		(*large)->next->prev = (*large)->prev;
	if ((*large)->prev)
		(*large)->prev->next = (*large)->next;
	munmap((*large), (*large)->size + sizeof(t_block));
}

void			free(void *ptr)
{
	if (DEBUG)
	{
		ft_putstr_fd("--- Start free ", 2);
		ft_puthex_fd(ptr, 2);
		ft_putchar_fd('\n', 2);
	}
	t_block		*tmp;

	pthread_mutex_lock(&g_mutex);
	if (ptr == NULL)
	{
		if (DEBUG)
			ft_putendl_fd("*** END1 free NULL", 2);
		pthread_mutex_unlock(&g_mutex);
		return ;
	}
	tmp = (t_block *)(ptr - sizeof(t_block));
	if (search_addr(tmp) == NULL || tmp->is_free == 1)
	{
		if (DEBUG)
		{
			ft_puthex_fd(tmp, 2);
			ft_putendl_fd(" *** END3 free", 2);
		}
		pthread_mutex_unlock(&g_mutex);
		if (DEBUG)
			show_alloc_mem();
		return ;
	}
	tmp->is_free = 1;
	ptr = NULL;
	if (is_large(tmp))
		free_large(&tmp);
	else
		stack_free_block();
	if (DEBUG)
	{
		ft_puthex_fd(tmp, 2);
		ft_putendl_fd(" *** END free", 2);
	}
	pthread_mutex_unlock(&g_mutex);
}
