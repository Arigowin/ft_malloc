#include "malloc.h"

// mmap
#include <sys/types.h>
#include <sys/mman.h>

// getpagesize
#include <unistd.h>

void		*add(t_node *node, size_t size, size_t max)
{
	write(1, "Start1\n", 7);

	t_node *curr;
	t_node *tmp;

	curr = node;
	while(curr->next != NULL)
	{
		if ((size_t)((char *)curr->next - (char *)curr->end) >= size)
			break;
		curr = curr->next;
	}
	if (((char *)curr->end + size) > ((char *)node + max))
	{
		return NULL;
	}
	tmp = curr->next;
	curr->next = curr->end;
	curr->next->end = (t_node *)((char *)curr->next + size);
	curr->next->next = tmp;

	write(1, "End1\n", 5);
	return curr->next;
}


void		*malloc(size_t size)
{
	size_t		len;
	t_node		*tmp;

	write(1, "Start0\n", 7);

	if (size <= 0)
		return NULL;

	len = size + sizeof(t_node);
	if (len <= (size_t)(TINY * getpagesize()))
	{
		write(1, "TINY\n", 5);
		return add(get_lst()->tiny, len, get_lst()->size_tiny);
	}
	if (len <= (size_t)(SMALL * getpagesize()))
	{
		write(1, "SMALL\n", 6);
		return add(get_lst()->small, len, get_lst()->size_small);
	}

	write(1, "LARGE\n", 6);
	tmp = get_lst()->large;
	while(tmp->next != NULL)
		tmp = tmp->next;

	if (NULL == (tmp->next = mmap(NULL, len,
					PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0)))
		return NULL;

	tmp->next->end = (t_node *)((char *)tmp->next + len);
	tmp->next->next = NULL;

	write(1, "End0\n", 5);

	return (void*)(tmp->next + 1);
}
