/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 04:02:48 by dolewski          #+#    #+#             */
/*   Updated: 2018/11/13 04:02:48 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <unistd.h>
#include <stdint.h>

void		ft_puthex_fd(const void *ptr, int fd)
{
	char	alpha[16];
	char	res[9];
	size_t	addr;
	int		i;

	ft_memcpy(alpha, "0123456789ABCDEF", 16);
	ft_bzero(res, 9);
	ft_memset(res, '0', 8);
	i = 7;
	addr = (size_t)ptr;
	res[i--] = alpha[addr % 16];
	while ((addr /= 16) > 0 && i > -1)
		res[i--] = alpha[addr % 16];
	ft_putstr_fd("0x", fd);
	ft_putstr_fd(res, fd);
}
