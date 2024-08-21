# Compiler
CC = gcc

# Compiler flags
WARNFLAGS = -Wall -Wextra -Werror
CFLAGS = -I./lib_ft -I./lib_ft_printf
LDFLAGS = -L./lib_ft -l:libft.a -L./lib_ft_printf -lftprintf

# Default sources
SRCS = main.c env.c
OBJS = $(SRCS:.c=.o)

# Program Name
NAME = minishell

# Libft src
LIBFT = ./lib_ft/libft.a

# ft_printf
FTPRINTF = ./lib_ft_printf/libftprintf.a

# Default rule
all: $(LIBFT) $(FTPRINTF) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(WARNFLAGS) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

# Make lib_ft
$(LIBFT):
	make -C lib_ft

# Make lib_ft_printf
$(FTPRINTF):
	make -C lib_ft_printf

# Clean up obj files
clean:
	make -C lib_ft clean
	make -C lib_ft_printf clean
	rm -f $(OBJS)

# Full clean up
fclean: clean
	rm $(NAME)
	make -C lib_ft fclean
	make -C lib_ft_printf fclean

# Rebuild
re: fclean all

# Ensure that 'all', 'clean', 'fclean', 're', and 'bonus' are not interpreted as file names
.PHONY: all clean fclean re bonus
