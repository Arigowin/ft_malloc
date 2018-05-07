#include <stdlib.h>

int      main()
{
	int   i;
	char  *addr;

	i = 0;
	while (i < 1024)
	{
		write(1, "a\n", 2);
		addr = (char*)malloc(1024);
		addr[0] = 42;
		i++;
	}
	return (0);
}
