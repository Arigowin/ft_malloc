/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 04:02:47 by dolewski          #+#    #+#             */
/*   Updated: 2018/11/13 04:02:47 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <pthread.h>

pthread_mutex_t	g_mutex;

void			*calloc(size_t count, size_t size)
{
	void		*tmp;

	pthread_mutex_lock(&g_mutex);
	if (count == 0)
		count++;
	pthread_mutex_unlock(&g_mutex);
	if ((tmp = malloc((count * size) + 1)) == NULL)
		return (NULL);
	pthread_mutex_lock(&g_mutex);
	ft_bzero(tmp, count * size);
	pthread_mutex_unlock(&g_mutex);
	return (tmp);
}
