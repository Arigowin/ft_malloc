#ifndef LIBFT_MALLOC_H
# define LIBFT_MALLOC_H

#include <stdlib.h>

void	*malloc(size_t size);
void	free(void *ptr);
void	*realloc(void *ptr, size_t size);

#endif // LIBFT_MALLOC_H
