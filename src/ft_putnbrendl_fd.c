#include "malloc.h"

static void		ft_putunbr(unsigned int n, int fd)
{
	if (n > 9)
		ft_putunbr(n / 10, fd);
	ft_putchar_fd((n % 10) + '0', fd);
}

void			ft_putnbrendl_fd(int n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putunbr(-n, fd);
	}
	else
		ft_putunbr(n, fd);
	ft_putchar_fd('\n', fd);
}
