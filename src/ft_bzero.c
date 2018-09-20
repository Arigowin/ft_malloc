#include <string.h>

void			ft_bzero(void *s, size_t n)
{
	size_t			i;
	char			*tmp;

	i = 0;
	tmp = s;
	while (tmp && i < n)
	{
		*tmp = '\0';
		i++;
		tmp++;
	}
}
