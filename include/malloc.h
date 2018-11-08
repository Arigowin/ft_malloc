#ifndef LIBFT_MALLOC_H
# define LIBFT_MALLOC_H

# include <pthread.h>

# define TINY 4096
# define SMALL 8192

#define DEBUG 0

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
void					*calloc(size_t count, size_t size);

t_alloc					*get_alloc(void);
t_block					*search_addr(void *ptr);
int						is_large(void *addr);
size_t					align_page_size(size_t size, size_t mul);

void					ft_putchar_fd(char c, int fd);
void					ft_putendl_fd(char const *s, int fd);
void					ft_puthex_fd(const void *ptr, int fd);
void					ft_putstr_fd(const char *s, int fd);
void					ft_putnbrendl_fd(int n, int fd);
void					ft_putnbr_fd(int n, int fd);
int						ft_strlen(const char *s);
void					*ft_memcpy(void *s1, const void *s2, size_t n);
void					ft_bzero(void *s, size_t n);
void					*ft_memset(void *b, int c, size_t len);
int						ft_strcmp(const char *s1, const char *s2);
void					ft_address(const void *ptr, char (*res)[9]);

#endif
