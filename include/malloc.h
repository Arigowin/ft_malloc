#ifndef LIBFT_MALLOC_H
# define LIBFT_MALLOC_H

# include <stdlib.h>

// mutex
#include <pthread.h>

# define TINY 32
# define SMALL 64

typedef struct			s_node
{
	size_t				size;
	char				is_free;
	struct s_node		*next;
}						t_node;

typedef struct			s_alloc
{
	t_node				*tiny;
	size_t				size_tiny;
	t_node				*small;
	size_t				size_small;
	t_node				*large;
}						t_alloc;

extern t_alloc			*g_alloc;
extern pthread_mutex_t	g_mutex;

void					*malloc(size_t size);
void					free(void *ptr);
// void					*realloc(void *ptr, size_t size);
void					show_alloc_mem();
t_alloc					*get_alloc(void);

void	ft_putchar(char c);
void	ft_putendl(char const *s);
void	ft_puthex(const void *ptr);
void	ft_putstr(const char *s);
void			ft_putnbrendl(int n);
void			ft_putnbr(int n);
int				ft_strlen(const char *s);

#endif // LIBFT_MALLOC_H

