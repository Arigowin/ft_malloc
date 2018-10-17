/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 17:25:24 by dolewski          #+#    #+#             */
/*   Updated: 2018/10/17 17:25:24 by dolewski         ###   ########.fr       */
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
