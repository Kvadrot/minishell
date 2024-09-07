# Compiler
CC = gcc

# Compiler flags
WARNFLAGS = -Wall -Wextra #-Werror
RLFLAG = -lreadline -lm -g
CFLAGS = -g
HEADERS = -I./lib_ft -I./lib_ft_printf -I./inc
LDFLAGS = -L./lib_ft -l:libft.a -L./lib_ft_printf -lftprintf $(RLFLAG)


# Object directory
OBJ_DIR = obj/

# src/builtin/ft_append.c 

#src/cmd/cmd.c \
# Source files
SRCS = src/main.c \
		src/builtin/cd.c \
		src/execution/exec.c \
		src/execution/exec_utils.c \
		src/error/error.c \
		src/env/env_utils.c src/env/env.c \
		src/garbage_colector/garbage_colector.c src/garbage_colector/minishell_free.c \
		src/parsing/parsing.c src/parsing/parsing_utils.c\
		src/tokens/error_handling.c src/tokens/tokens_semi_tested.c src/tokens/tokens_utils.c \
		src/validation/validation.c

OBJS = $(SRCS:.c=.o)

# Program Name
NAME = minishell

# Libft src
LIBFT = ./lib_ft/libft.a

# ft_printf
FTPRINTF = ./lib_ft_printf/libftprintf.a

# Default rule
all: $(LIBFT) $(FTPRINTF) $(NAME)

#print:
#	clear
#	@echo $(OBJS)
#	@echo "\n"
#	@echo $(SRCS)


	
#$(LIBFT) $(FTPRINTF) $(NAME)
$(NAME): $(OBJS)
	clear
	@echo "Linking objects into executable..."
	$(CC) $(WARNFLAGS) $(CFLAGS) $(HEADERS) $(OBJS) -o $(NAME) $(LDFLAGS)

%.o: %.c
	$(CC) $(WARNFLAGS) $(CFLAGS) $(HEADERS) -c $< -o $@ 

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
	rm -f $(NAME)
	make -C lib_ft fclean
	make -C lib_ft_printf fclean

# Rebuild
re: fclean all

# Ensure that 'all', 'clean', 'fclean', 're', and 'bonus' are not interpreted as file names
.PHONY: all clean fclean re bonus
