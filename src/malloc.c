/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 04:02:49 by dolewski          #+#    #+#             */
/*   Updated: 2018/11/13 04:02:49 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <sys/mman.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t	g_mutex;

t_block			*find_first_free(size_t size, t_block *head)
{
	t_block		*tmp;

	tmp = head;
	while (tmp->next != NULL)
	{
		if (tmp->is_free && (tmp->size == size
					|| tmp->size >= (size + sizeof(t_block) + 1)))
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}

void			*add_block(size_t size, t_block *head)
{
	t_block		*curr;
	t_block		*next;

	curr = find_first_free(size, head);
	next = curr->next;
	if (curr->size != size && (long)(curr->size - size - sizeof(t_block)) > 0)
	{
		curr->next = (void *)((void *)(curr + 1) + size);
		curr->next->size = curr->size - size - sizeof(t_block);
		curr->next->is_free = 1;
		curr->next->next = next;
		curr->next->prev = curr;
	}
	else if (curr->next == NULL)
		return (NULL);
	curr->size = size;
	curr->is_free = 0;
	return ((void *)(curr + 1));
}

void			*add_large_block(size_t size)
{
	t_block		*tmp;

	tmp = get_alloc()->large;
	while (tmp->next != NULL)
		tmp = tmp->next;
	if (MAP_FAILED == (tmp->next = mmap(NULL,
					align_page_size(size + sizeof(t_block), getpagesize()),
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
	void		*ret;

	pthread_mutex_lock(&g_mutex);
	ret = NULL;
	if (size == 0)
	{
		pthread_mutex_unlock(&g_mutex);
		return (ret);
	}
	size = align_page_size(size, 16);
	if (size <= (size_t)(TINY))
	{
		ret = add_block(size, get_alloc()->tiny);
	}
	if (ret == NULL && size <= (size_t)(SMALL))
	{
		ret = add_block(size, get_alloc()->small);
	}
	if (ret == NULL)
		ret = add_large_block(size);
	pthread_mutex_unlock(&g_mutex);
	return (ret);
}
