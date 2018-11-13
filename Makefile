CC =		/usr/bin/clang
RM =		/bin/rm
MAKE =		/usr/bin/make
MKDIR =		/bin/mkdir
AR =		/usr/bin/ar
RANLIB =	/usr/bin/ranlib
LN =		/bin/ln

ROOT =		$(shell /bin/pwd)
OPATH =		$(ROOT)/obj
CPATH =		$(ROOT)/src
HPATH =		$(ROOT)/include

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
LNNAME = libft_malloc.so

OFILES = $(patsubst %.c, $(OPATH)/%.o, $(SRC))

CFLAGS = -Wall -Wextra -Werror -I $(HPATH) -fPIC -g

SRC = malloc.c \
	  free.c \
	  realloc.c \
	  calloc.c \
	  show_alloc_mem.c \
	  alloc.c \
	  utils.c \
	  ft_putchar_fd.c \
	  ft_putendl_fd.c \
	  ft_puthex_fd.c \
	  ft_putstr_fd.c \
	  ft_putnbrendl_fd.c \
	  ft_putnbr_fd.c \
	  ft_strlen.c \
	  ft_bzero.c \
	  ft_memcpy.c \
	  ft_memset.c \
	  ft_strcmp.c \
	  ft_address.c


.PHONY: all clean fclean re test

all: $(OPATH) $(NAME)

$(NAME): $(OFILES)
	@echo "$(LNNAME) - Building $@"
	@$(CC) $(CFLAGS) -o $@ $^ -shared
	@$(RM) -f $(LNNAME)
	@$(LN) -s $(NAME) $(LNNAME)
	@echo "\033[34m$(LNNAME) - All is done!\033[0m"

$(OPATH)/%.o: $(CPATH)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(OPATH):
	@$(MKDIR) $@

clean:
	@echo "$(LNNAME) - Deleting OBJ"
	@$(RM) -Rf $(OPATH)

fclean: clean
	@echo "$(LNNAME) - Deleting $(NAME)"
	@$(RM) -f $(NAME)
	@$(RM) -f $(LNNAME)
	@echo "\033[34m$(LNNAME) - All clear!\033[0m"

re: fclean all

norm: all
	norminette **/*.[ch]

test: all
	@$(RM) -f ./test/test
	@$(CC) $(CFLAGS) -L. -lft_malloc ./test/test.c -o ./test/test
	@/usr/bin/time -l ./test/run.sh ./test/test

# lil memo
# $@ = rule's name
# $^ = all the rule dependecies
# $< = only the first dependence

