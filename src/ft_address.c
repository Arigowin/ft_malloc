#include "malloc.h"
#include <unistd.h>
#include <stdint.h>

void		ft_address(const void *ptr, char (*res)[9])
{
	char	alpha[16];
	size_t	addr;
	int		i;

	ft_memcpy(alpha, "0123456789ABCDEF", 16);
	ft_bzero(res, 9);
	ft_memset(res, '0', 8);
	i = 7;
	addr = (size_t)ptr;
	(*res)[i--] = alpha[addr % 16];
	while ((addr /= 16) > 0 && i > -1)
		(*res)[i--] = alpha[addr % 16];
}
