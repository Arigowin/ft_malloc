/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 04:02:49 by dolewski          #+#    #+#             */
/*   Updated: 2018/11/13 04:02:49 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "malloc.h"

int				ft_strlen(const char *s)
{
	int				cpt;

	cpt = 0;
	if (s)
	{
		while (*s != '\0')
		{
			cpt++;
			s++;
		}
	}
	return (cpt);
}
