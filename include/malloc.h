#ifndef LIBFT_MALLOC_H
# define LIBFT_MALLOC_H

# include <stdlib.h>

# define TINY 16
# define SMALL 32

typedef struct		s_node
{
	size_t			size;
	char			is_free;
	char			data[1];
	struct s_node	*next;
}					t_node;

typedef struct		s_lst
{
	t_node			*tiny;
	size_t			size_tiny; // TINY * getpagesize()
	t_node			*small;
	size_t			size_small; // SMALL * getpagesize()
	t_node			*large;
}					t_lst;

static t_lst		*g_lst = NULL;

void				*malloc(size_t size);
// void				free(void *ptr);
// void				*realloc(void *ptr, size_t size);
// void				show_alloc_mem();
t_lst				*get_lst(void);

#endif // LIBFT_MALLOC_H
