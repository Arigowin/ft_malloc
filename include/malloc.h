#ifndef LIBFT_MALLOC_H
# define LIBFT_MALLOC_H

# include <stdlib.h>
# include <pthread.h>

# define TINY 4096
# define SMALL 8192

typedef struct			s_block
{
	size_t				size;
	char				is_free;
	struct s_block		*next;
	struct s_block		*prev;
}						t_block;

typedef struct			s_alloc
{
	t_block				*tiny;
	t_block				*small;
	t_block				*large;
}						t_alloc;

extern t_alloc			*g_alloc;
extern pthread_mutex_t	g_mutex;

void					*malloc(size_t size);
void					free(void *ptr);
void					*realloc(void *ptr, size_t size);
void					show_alloc_mem();

t_alloc					*get_alloc(void);
t_block					*search_addr(void *ptr);

void					ft_putchar(char c);
void					ft_putendl(char const *s);
void					ft_puthex(const void *ptr);
void					ft_putstr(const char *s);
void					ft_putnbrendl(int n);
void					ft_putnbr(int n);
int						ft_strlen(const char *s);
void					*ft_memcpy(void *s1, const void *s2, size_t n);
void					ft_bzero(void *s, size_t n);
void					*ft_memset(void *b, int c, size_t len);

#endif
