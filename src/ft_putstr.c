#include <unistd.h>
#include "malloc.h"

void	ft_putstr(const char *s)
{
	if (s != NULL)
		write(1, s, ft_strlen(s));
}
