# Compiler
CC = gcc
# Compiler flags
CFLAGS = -Wall -Wextra -Werror
# Source files
SRCS = ft_printf.c\
		param_functions.c\

# Object files
OBJS = $(SRCS:.c=.o)

# Name of the library
NAME = libftprintf.a

# Main rule to build the library
all: $(NAME)

# Compile object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Build the library
$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

# Clean up object files and library
clean:
	rm -f $(OBJS)

# Full cleanup
fclean: clean
	rm -f $(NAME)

# Rebuild
re: fclean all

# Ensure that 'all', 'clean', 'fclean', 're', and 'bonus' are not interpreted as file names
.PHONY: all clean fclean re