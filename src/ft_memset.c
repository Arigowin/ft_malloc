/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 17:25:22 by dolewski          #+#    #+#             */
/*   Updated: 2018/10/17 17:25:22 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void			*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	char			*tmp;

	i = 0;
	tmp = b;
	while ((i < len) && (b != NULL))
	{
		*tmp = c;
		i++;
		tmp++;
	}
	return (b);
}
