#include "malloc.h"
#include <sys/mman.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t	g_mutex;

t_block			*find_first_free(size_t size, t_block *head)
{
	if (DEBUG)
		ft_putendl_fd("find_first_free", 2);
	t_block		*tmp;

	tmp = head;
	while (tmp->next != NULL)
	{
		if (tmp->is_free && (tmp->size == size || tmp->size >= (size + sizeof(t_block) + 1)))
		{
			if (DEBUG)
				ft_putendl_fd("END1 find_first_free", 2);
			return (tmp);
		}
		tmp = tmp->next;
	}
	if (DEBUG)
		ft_putendl_fd("END find_first_free", 2);
	return (tmp);
}

void			*add_block(size_t size, t_block *head)
{
	if (DEBUG)
		ft_putendl_fd("add_block", 2);
	t_block		*curr;
	t_block		*next;

	curr = find_first_free(size, head);
	next = curr->next;
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
	}
	if (curr->size != size && (long)(curr->size - size - sizeof(t_block)) > 0/* && curr->is_free*/)
	{
		curr->next = (void *)((void *)(curr + 1) + size);
		curr->next->size = curr->size - size - sizeof(t_block);
		curr->next->is_free = 1;
		curr->next->next = next;
		curr->next->prev = curr;
		if (curr->prev != NULL)
			curr->prev->next = curr;
	}
	else if (curr->next == NULL)
	{
		if (DEBUG)
			ft_putendl_fd("END1 add_block", 2);
		return (NULL);
	}
	curr->size = size;
	curr->is_free = 0;
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
	if (DEBUG)
		ft_putendl_fd("END add_block", 2);
	return ((void *)(curr + 1));
}

void			*add_large_block(size_t size)
{
	if (DEBUG)
		ft_putendl_fd("add_large_block", 2);
	t_block		*tmp;

	tmp = get_alloc()->large;
	while (tmp->next != NULL)
		tmp = tmp->next;
	if (MAP_FAILED == (tmp->next = mmap(NULL, align_page_size(size + sizeof(t_block), getpagesize()),
					PROT_READ | PROT_WRITE,
					MAP_ANONYMOUS | MAP_PRIVATE, -1, 0)))
		return (NULL);
	tmp->next->size = size;
	tmp->next->is_free = 0;
	tmp->next->next = NULL;
	tmp->next->prev = tmp;
	return ((void *)(tmp->next + 1));
}

void			*malloc(size_t size)
{
	if (DEBUG)
	{
		ft_putstr_fd("--- Start Malloc ", 2);
		ft_putnbr_fd(size, 2);
		ft_putstr_fd(" ", 2);
		ft_putnbrendl_fd(align_page_size(size, 16), 2);
	}
	void		*ret;

	pthread_mutex_lock(&g_mutex);
	ret = NULL;
	if (size == 0)
	{
		if (DEBUG)
			ft_putendl_fd("*** END1 Malloc", 2);
		pthread_mutex_unlock(&g_mutex);
		return (ret);
	}
	size = align_page_size(size, 16);
	if (size <= (size_t)(TINY))
	{
		if (DEBUG)
			ft_putendl_fd("TINY", 2);
		ret = add_block(size, get_alloc()->tiny);
	}
	if (ret == NULL && size <= (size_t)(SMALL))
	{
		if (DEBUG)
			ft_putendl_fd("SMALL", 2);
		ret = add_block(size, get_alloc()->small);
	}
	if (ret == NULL)
		ret = add_large_block(size);
	if (DEBUG)
	{
		ft_puthex_fd((ret - sizeof(t_block)), 2);
		ft_putchar_fd('\n', 2);
		ft_puthex_fd(ret, 2);
		ft_putendl_fd(" *** END Malloc", 2);
	}
	pthread_mutex_unlock(&g_mutex);
	show_alloc_mem();
	return (ret);
}
