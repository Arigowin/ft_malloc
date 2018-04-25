#include "malloc.h"
#include <stdio.h>
#include <unistd.h>

int main(void)
{
	write(1, "abc\n", 4);

	int *tmp = (int *)malloc(8);
	/* printf("%p\n", tmp); */

	if (tmp == NULL)
		return (-1);

	*tmp = 42;
	write(1, tmp, 1);
	write(1, "\nDone\n", 5);
	free(tmp);

	return (0);
}
