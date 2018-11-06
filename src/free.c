#include "malloc.h"
#include <sys/mman.h>
#include <pthread.h>

pthread_mutex_t	g_mutex;

void			stack_free_block(t_block *curr)
{
	if (DEBUG)
		ft_putendl_fd("stack_free", 2);
	if (DEBUG)
	{
		ft_putstr_fd("curr -> ", 2);
		ft_puthex_fd((void *)(curr), 2);
		ft_putstr_fd(" - ", 2);
		ft_puthex_fd((void *)(curr + 1), 2);
		ft_putstr_fd(" - ", 2);
		ft_puthex_fd((void *)((void *)(curr + 1) + curr->size), 2);
		ft_putstr_fd(" : ", 2);
		ft_putnbr_fd(curr->size, 2);
		ft_putstr_fd(" octets free: ", 2);
		ft_putnbrendl_fd(curr->is_free, 2);

		if (curr->next != NULL)
		{
			ft_putstr_fd("next -> ", 2);
			ft_puthex_fd((void *)(curr->next), 2);
			ft_putstr_fd(" - ", 2);
			ft_puthex_fd((void *)(curr->next + 1), 2);
			ft_putstr_fd(" - ", 2);
			ft_puthex_fd((void *)((void *)(curr->next + 1) + curr->next->size), 2);
			ft_putstr_fd(" : ", 2);
			ft_putnbr_fd(curr->next->size, 2);
			ft_putstr_fd(" octets free: ", 2);
			ft_putnbrendl_fd(curr->next->is_free, 2);
		}
		if (curr->next->next != NULL)
		{
			ft_putstr_fd("next->next -> ", 2);
			ft_puthex_fd((void *)(curr->next->next), 2);
			ft_putstr_fd(" - ", 2);
			ft_puthex_fd((void *)(curr->next->next + 1), 2);
			ft_putstr_fd(" - ", 2);
			ft_puthex_fd((void *)((void *)(curr->next->next + 1) + curr->next->next->size), 2);
			ft_putstr_fd(" : ", 2);
			ft_putnbr_fd(curr->next->next->size, 2);
			ft_putstr_fd(" octets free: ", 2);
			ft_putnbrendl_fd(curr->next->next->is_free, 2);
		}
	}
	if (curr != NULL && curr->is_free && curr->next != NULL && curr->next->is_free)
	{
		curr->size = curr->size + (curr->next->size + sizeof(t_block));
		if (curr->next->next != NULL)
			curr->next->next->prev = curr;
		curr->next = curr->next->next;
		if (DEBUG)
		{
			ft_putendl_fd("BONJOUR", 2);
			ft_putstr_fd("curr -> ", 2);
			ft_puthex_fd((void *)(curr), 2);
			ft_putstr_fd(" - ", 2);
			ft_puthex_fd((void *)(curr + 1), 2);
			ft_putstr_fd(" - ", 2);
			ft_puthex_fd((void *)((void *)(curr + 1) + curr->size), 2);
			ft_putstr_fd(" : ", 2);
			ft_putnbr_fd(curr->size, 2);
			ft_putstr_fd(" octets free: ", 2);
			ft_putnbrendl_fd(curr->is_free, 2);

			if (curr->next != NULL)
			{
				ft_putstr_fd("next -> ", 2);
				ft_puthex_fd((void *)(curr->next), 2);
				ft_putstr_fd(" - ", 2);
				ft_puthex_fd((void *)(curr->next + 1), 2);
				ft_putstr_fd(" - ", 2);
				ft_puthex_fd((void *)((void *)(curr->next + 1) + curr->next->size), 2);
				ft_putstr_fd(" : ", 2);
				ft_putnbr_fd(curr->next->size, 2);
				ft_putstr_fd(" octets free: ", 2);
				ft_putnbrendl_fd(curr->next->is_free, 2);
			}
		}
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
		stack_free_block(tmp);
	if (DEBUG)
	{
		ft_puthex_fd(tmp, 2);
		ft_putendl_fd(" *** END free", 2);
	}
	pthread_mutex_unlock(&g_mutex);
}
