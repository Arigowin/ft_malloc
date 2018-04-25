#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	char *str = (char *)malloc(-1);

	printf("%p", str);

	free(str);
	return (0);
}
