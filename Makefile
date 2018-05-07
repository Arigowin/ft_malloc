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
LIBPATH =	$(ROOT)/libft
LIBHPATH =	$(LIBPATH)/include

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
LNNAME = libft_malloc.so

OFILES = $(patsubst %.c, $(OPATH)/%.o, $(SRC))

CFLAGS = -Wall -Wextra -Werror -I $(HPATH) -I $(LIBHPATH) -fPIC -g
LIBS = -L $(LIBPATH) -lft

SRC = malloc.c \
	  free.c \
	  lst.c


.PHONY: all clean fclean re lib.fclean test

all: $(OPATH) $(NAME)

$(NAME): $(OFILES)
	@$(MAKE) -C $(LIBPATH) -j
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

lib.fclean:
	@$(MAKE) fclean -C $(LIBPATH) -j

fclean: clean lib.fclean
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

