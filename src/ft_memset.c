#include <string.h>

void			*ft_memset(void *b, int c, int len)
{
	int				i;
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
