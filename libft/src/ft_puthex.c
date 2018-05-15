/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 17:34:47 by dolewski          #+#    #+#             */
/*   Updated: 2018/05/15 17:49:05 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdint.h>

char	hex_digit(int v)
{
	if (v >= 0 && v <= 9)
		return ('0' + v);
	else
		return ('A' + v - 10);
}

void	ft_puthex(const void *ptr)
{
	int			i;
	uintptr_t	p;

	p = (uintptr_t)ptr;
	i = (sizeof(p) << 3);
	ft_putstr("0x");
	while (i >= 0 && ((p >> i) & 0xF) == 0)
		i -= 4;
	if (i <= 0)
		ft_putchar('0');
	while (i >= 0)
	{
		ft_putchar(hex_digit((p >> i) & 0xF));
		i -= 4;
	}
	ft_putendl("");
}
