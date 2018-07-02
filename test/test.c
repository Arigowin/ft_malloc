#include "malloc.h"
#include <stdio.h>
#include <unistd.h>

// getrlimit
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/types.h>

int main(void)
{
	/* struct rlimit lim; */
	write(1, "abc\n", 4);

	/* getrlimit(RLIMIT_MEMLOCK | RLIMIT_DATA, &lim); */
	/* printf("%lu\n", lim.rlim_cur); */
	/* printf("%lu\n", lim.rlim_max); */

	/* printf("%d\n", getpagesize()); */

	/* char *tmp = (char *)malloc(32 * 4096 + 1); */
	/* printf("%p\n", tmp); */

	/* if (tmp == NULL) */
	/*     return (-1); */
	/*  */
	/* int i = 0; */
	/* while(i < 32 * 4096) */
	/* { */
	/*     tmp[i] = '*'; */
	/*     i++; */
	/* } */
	/* tmp[32 * 4096] = '\0'; */

	int i = 1;
	while(i < 21)
	{
		char *tmp = (char *)malloc(i);
		int j = 0;
		while (j < i)
		{
			tmp[j] = 42;
			j++;
		}
		i++;
	}

	write(1, "\nDone\n", 5);
	/* free(tmp); */

	return (0);
}
