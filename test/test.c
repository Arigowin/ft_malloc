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

	char *tmp1 = (char *)malloc(100000);
	char *tmp2 = (char *)malloc(1140000);
	char *tmp3 = (char *)malloc(1000000);
	free(tmp2);
	char *tmp4 = (char *)malloc(250000);
	char *tmp5 = (char *)malloc(250000);

	free(tmp1);
	free(tmp3);
	free(tmp4);
	free(tmp5);

	write(1, "\nDone\n", 5);
	/* free(tmp); */

	return (0);
}
