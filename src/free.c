/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 17:25:20 by dolewski          #+#    #+#             */
/*   Updated: 2018/10/17 17:25:20 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t	g_mutex;

void			stack_free_block(t_block *curr)
{
	if (curr->next != NULL && curr->next->is_free)
	{
		curr->size += curr->next->size + sizeof(t_block);
		if (curr->next->next != NULL)
			curr->next->next->prev = curr;
		curr->next = curr->next->next;
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
	if (tmp->size > SMALL)
		free_large(&tmp);
	else
		stack_free_block(tmp);
	pthread_mutex_unlock(&g_mutex);
}
