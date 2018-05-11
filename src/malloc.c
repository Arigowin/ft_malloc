#include "libft.h"
#include "malloc.h"

// mmap
#include <sys/types.h>
#include <sys/mman.h>

// getpagesize
#include <unistd.h>

void		*add(t_node *node, size_t size, size_t max)
{
	ft_putendl_fd("Start1\n", 2);

	t_node *curr;
	t_node *tmp;

	curr = node;
	while(curr->next != NULL)
	{
		ft_putendl_fd("While\n", 2);
		if ((size_t)(char *)curr->next - (size_t)(char *)curr->end >= size)
		{
			ft_putendl_fd("x\n", 2);
			break;
		}
		curr = curr->next;
	}
	if (((char *)curr->end + size) > ((char *)node + max))
	{
		ft_putendl_fd("y\n", 2);
		return NULL;
	}
	tmp = curr->next;
	curr->next = curr->end;
	curr->next->end = (t_node *)((char *)curr->next + size);
	curr->next->next = tmp;

	ft_putendl_fd("End1\n", 3);
	return curr->next;
}

void		*malloc(size_t size)
{
	size_t		len;
	t_node		*tmp;

	ft_putendl_fd("Start0\n", 2);

	if (size <= 0)
		return NULL;

	len = size + sizeof(t_node);
	if (len <= get_lst()->size_tiny)
	{
		ft_putendl_fd("TINY\n", 2);
		return add(get_lst()->tiny, len, get_lst()->size_tiny);
	}
	if (len <= get_lst()->size_small)
	{
		ft_putendl_fd("SMALL\n", 2);
		return add(get_lst()->small, len, get_lst()->size_small);
	}

	ft_putendl_fd("LARGE\n", 2);
	tmp = get_lst()->large;
	while(tmp->next != NULL)
		tmp = tmp->next;

	if (NULL == (tmp->next = mmap(NULL, len,
					PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0)))
		return NULL;

	tmp->next->end = (t_node *)((char *)tmp->next + len);
	tmp->next->next = NULL;

	ft_putendl_fd("End0\n", 2);

	return (void*)(tmp->next + 1);
}

// https://arjunsreedharan.org/post/148675821737/write-a-simple-memory-allocator
// http://www.inf.udec.cl/~leo/Malloc_tutorial.pdf
