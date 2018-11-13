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
