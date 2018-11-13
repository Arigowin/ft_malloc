/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 04:02:48 by dolewski          #+#    #+#             */
/*   Updated: 2018/11/13 04:02:48 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		ft_putunbr(unsigned int n, int fd)
{
	if (n > 9)
		ft_putunbr(n / 10, fd);
	ft_putchar_fd((n % 10) + '0', fd);
}

void			ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putunbr(-n, fd);
	}
	else
		ft_putunbr(n, fd);
}
