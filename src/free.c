#include "malloc.h"

// munmap
#include <sys/types.h>
#include <sys/mman.h>

// getpagesize
#include <unistd.h>

#include <stdio.h>

int			remove_ptr(void *ptr, t_node *node)
{
	int i =0;
	write(1, "SFree1\n", 7);

	while(node->next != NULL)
	{
		if (ptr == node->next)
		{
			node->next = node->next->next;
			write(1, "EFree2\n", 7);
			return (1);
		}
		/* printf("-> %p %p\n", (char *)node->next->end, (char *)ptr); */
		/* printf("%p %p\n", node->next, ptr); */
		node->next = node;
		i++;
		if (i == 10)
			return (1);
	}
	write(1, "EFree1\n", 7);
	return (0);
}

void		free(void *ptr)
{
	t_node	*tmp;
	t_node	*tmp2;

	write(1, "SFree0\n", 7);

	if (ptr == NULL)
		return;

	if (remove_ptr(ptr, get_lst()->tiny))
		return;
	if (remove_ptr(ptr, get_lst()->small))
		return;

	tmp = get_lst()->large;
	while(tmp->next != NULL)
	{
		if (ptr == tmp->next)
		{
			tmp2 = tmp->next->next;
			munmap((void *)tmp->next, (char *)tmp->next->end - (char *)tmp->next);
			tmp->next = tmp;
			break;
		}
		tmp = tmp->next;
	}
	write(1, "EFree0\n", 7);
}
