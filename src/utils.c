#include "malloc.h"

t_block			*search_in_head(char buff_addr[9], t_block *head)
{
	char		buff[9];

	while (head != NULL)
	{
		ft_address(head, &buff);
		if (ft_strcmp(buff_addr, buff) == 0)
			return (head);
		head = head->next;
	}
	return (NULL);
}

t_block			*search_addr(void *addr)
{
	t_block		*tmp;
	char		buff_addr[9];

	ft_address(addr, &buff_addr);
	if ((tmp = search_in_head(buff_addr, get_alloc()->tiny)) != NULL)
		return (tmp);
	if ((tmp = search_in_head(buff_addr, get_alloc()->small)) != NULL)
		return (tmp);
	if ((tmp = search_in_head(buff_addr, get_alloc()->large)) != NULL)
		return (tmp);
	return (NULL);
}

int				is_large(void *addr)
{
	t_block		*tmp;

	tmp = get_alloc()->large;
	while (tmp != NULL)
	{
		if (addr == tmp)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

size_t			align_page_size(size_t size, size_t mul)
{
	if (size % mul != 0)
		return ((((size - 1) / mul) * mul) + mul);
	return (size);
}
