/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 04:02:47 by dolewski          #+#    #+#             */
/*   Updated: 2018/11/13 04:02:47 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <sys/mman.h>
#include <pthread.h>

pthread_mutex_t	g_mutex;

void			stack_block(t_block *curr)
{
	curr->size = curr->size + (curr->next->size + sizeof(t_block));
	if (curr->next->next != NULL)
		curr->next->next->prev = curr;
	curr->next = curr->next->next;
}

void			stack_free_block(void)
{
	t_block *tmp;

	tmp = get_alloc()->tiny;
	while (tmp->next != NULL)
	{
		if (tmp->is_free && tmp->next->is_free)
		{
			stack_block(tmp);
			if (tmp->next == NULL)
				break ;
		}
		tmp = tmp->next;
	}
	tmp = get_alloc()->small;
	while (tmp->next != NULL)
	{
		if (tmp->is_free && tmp->next->is_free)
		{
			stack_block(tmp);
			if (tmp->next == NULL)
				break ;
		}
		tmp = tmp->next;
	}
}

void			free_large(t_block **large)
{
	if ((*large)->next)
		(*large)->next->prev = (*large)->prev;
	if ((*large)->prev)
		(*large)->prev->next = (*large)->next;
	munmap((*large), (*large)->size + sizeof(t_block));
}

void			free(void *ptr)
{
	t_block		*tmp;

	pthread_mutex_lock(&g_mutex);
	if (ptr == NULL)
	{
		pthread_mutex_unlock(&g_mutex);
		return ;
	}
	tmp = (t_block *)(ptr - sizeof(t_block));
	if (search_addr(tmp) == NULL || tmp->is_free == 1)
	{
		pthread_mutex_unlock(&g_mutex);
		return ;
	}
	tmp->is_free = 1;
	ptr = NULL;
	if (is_large(tmp))
		free_large(&tmp);
	else
		stack_free_block();
	pthread_mutex_unlock(&g_mutex);
}
