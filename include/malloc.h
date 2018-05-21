#ifndef LIBFT_MALLOC_H
# define LIBFT_MALLOC_H

# include <stdlib.h>

// mutex
#include <pthread.h>

# define TINY 16
# define SMALL 32

typedef struct			s_node
{
	size_t				size;
	char				is_free;
	struct s_node		*next;
}						t_node;

typedef struct			s_lst
{
	// t_node			*tiny;
	// size_t			size_tiny;
	// t_node			*small;
	// size_t			size_small;
	t_node				*large;
}						t_lst;

extern t_lst			*g_lst;
extern t_node			*g_node;
extern pthread_mutex_t	g_mutex;

void					*malloc(size_t size);
void					free(void *ptr);
// void					*realloc(void *ptr, size_t size);
void					show_alloc_mem();
// t_lst					*get_lst(void);
t_node					*get_node(void);

#endif // LIBFT_MALLOC_H

