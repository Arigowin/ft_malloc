/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 04:02:47 by dolewski          #+#    #+#             */
/*   Updated: 2018/11/13 04:02:47 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <sys/mman.h>
#include <unistd.h>

t_alloc			*g_alloc = NULL;

void			init_tiny(int tny)
{
	g_alloc->tiny = (t_block *)(g_alloc + 8);
	g_alloc->tiny->size = tny - sizeof(t_block);
	g_alloc->tiny->next = NULL;
	g_alloc->tiny->prev = NULL;
	g_alloc->tiny->is_free = 1;
}

void			init_small(int sml)
{
	g_alloc->small = (t_block *)((void *)g_alloc->tiny
			+ (g_alloc->tiny->size + sizeof(t_block)));
	g_alloc->small->size = sml - sizeof(t_block);
	g_alloc->small->next = NULL;
	g_alloc->small->prev = NULL;
	g_alloc->small->is_free = 1;
}

void			init_large(void)
{
	g_alloc->large = (t_block *)((void *)g_alloc->small
			+ g_alloc->small->size + sizeof(t_block));
	g_alloc->large->size = 0;
	g_alloc->large->next = NULL;
	g_alloc->large->prev = NULL;
	g_alloc->large->is_free = 1;
}

t_alloc			*get_alloc(void)
{
	int			tny;
	int			sml;

	tny = 0;
	sml = 0;
	if (g_alloc == NULL)
	{
		tny = ((((TINY + sizeof(t_block)) * 100) / getpagesize()) + 1)
			* getpagesize() + sizeof(t_block);
		sml = ((((SMALL + sizeof(t_block)) * 100) / getpagesize()) + 1)
			* getpagesize() + sizeof(t_block);
		if (MAP_FAILED == (g_alloc = mmap(NULL,
						tny
						+ sml
						+ sizeof(t_alloc) + 8,
						PROT_READ | PROT_WRITE,
						MAP_ANONYMOUS | MAP_PRIVATE, -1, 0)))
			return (NULL);
		init_tiny(tny);
		init_small(sml);
		init_large();
	}
	return (g_alloc);
}
