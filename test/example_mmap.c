#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av)
{
	int		i;
	int		nb;
	char	c;
	char	*str;

	(void)ac;

	nb = atoi(av[2]);
	c = av[1][0];
	str = (char *)mmap(NULL, nb + 1, PROT_READ | PROT_WRITE,
			MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

	i = 0;
	while(i < nb)
	{
		str[i] = c;
		i++;
	}
	str[i] = '\0';

	printf("%s", str);
	return (0);
}
