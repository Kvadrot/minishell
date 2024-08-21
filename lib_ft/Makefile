# Compiler
CC = gcc
# Compiler flags
CFLAGS = -Wall -Wextra -Werror
# Source files
SRCS = ft_memset.c \
       ft_bzero.c \
       ft_memcpy.c \
       ft_memmove.c \
       ft_memchr.c  \
       ft_memcmp.c  \
       ft_strlen.c  \
       ft_isalpha.c \
       ft_isdigit.c \
       ft_isalnum.c \
       ft_isascii.c \
       ft_isprint.c \
       ft_toupper.c \
       ft_tolower.c \
       ft_strchr.c  \
       ft_striteri.c \
       ft_strrchr.c \
       ft_strncmp.c \
       ft_strlcpy.c \
       ft_strlcat.c \
       ft_strnstr.c \
       ft_atoi.c    \
       ft_calloc.c  \
       ft_strdup.c  \
       ft_substr.c  \
       ft_strjoin.c \
       ft_strtrim.c \
       ft_split.c   \
       ft_itoa.c    \
       ft_strmapi.c \
       ft_putchar_fd.c  \
       ft_putstr_fd.c   \
       ft_putendl_fd.c  \
       ft_putnbr_fd.c

# Object files
OBJS = $(SRCS:.c=.o)

# Name of the library
NAME = libft.a

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
.PHONY: all clean fclean re bonus