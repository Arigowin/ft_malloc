#include "malloc.h"

// munmap
#include <sys/types.h>
#include <sys/mman.h>

// getpagesize
#include <unistd.h>

int			remove(void *ptr, t_node *node)
{
	while(node->next != NULL)
	{
		if (ptr == node->next)
		{
			node->next = node->next->next;
			return (1);
		}
		node->next = node;
	}
	return (0);
}

void		free(void *ptr)
{
	t_node	*tmp;
	t_node	*tmp2;

	if (ptr == NULL)
		return;

	if (remove(ptr, get_lst()->tiny))
		return;
	if (remove(ptr, get_lst()->small))
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
}
