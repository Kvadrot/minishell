# Compiler
CC = gcc

# Compiler flags
WARNFLAGS = -Wall -Wextra -Werror
RLFLAG = -lreadline -lm -g
CFLAGS = -g
HEADERS = -I./lib_ft -I./inc
LDFLAGS = -L./lib_ft -l:libft.a $(RLFLAG)


# Object directory
OBJ_DIR = obj/

# src/builtin/ft_append.c 

#src/cmd/cmd.c \
# Source files
SRCS =	src/main.c \
		src/builtin/cd.c \
		src/builtin/builtin_utils.c \
		src/builtin/echo.c \
		src/builtin/exit.c \
		src/builtin/pwd.c \
		src/builtin/export_utils.c \
		src/builtin/export.c \
		src/builtin/unset.c \
		src/execution/pipes.c \
		src/execution/forks.c \
		src/execution/exec_init.c \
		src/execution/exec.c \
		src/execution/find_bin_cmd.c \
		src/execution/find_bin_cmd_utils.c \
		src/execution/expand_dollar.c \
		src/error/error.c \
		src/env/env_utils.c \
		src/env/env.c \
		src/env/envlist_to_array.c \
		src/garbage_colector/garbage_colector.c \
		src/garbage_colector/minishell_free.c \
		src/parsing/argv_utils.c \
		src/parsing/heredoc.c \
		src/parsing/parsing_init.c\
		src/parsing/parsing_utils.c\
		src/parsing/parsing.c \
		src/parsing/tokens.c \

OBJS = $(SRCS:.c=.o)

# Program Name
NAME = minishell

# Libft src
LIBFT = ./lib_ft/libft.a

# Default rule
all: $(LIBFT) $(FTPRINTF) $(NAME)

#print:
#	clear
#	@echo $(OBJS)
#	@echo "\n"
#	@echo $(SRCS)


	
#$(LIBFT) $(FTPRINTF) $(NAME)
$(NAME): $(OBJS)
#	clear
	@echo "Linking objects into executable..."
	$(CC) $(WARNFLAGS) $(CFLAGS) $(HEADERS) $(OBJS) -o $(NAME) $(LDFLAGS)

%.o: %.c
	$(CC) $(WARNFLAGS) $(CFLAGS) $(HEADERS) -c $< -o $@ 

# Make lib_ft
$(LIBFT):
	make -C lib_ft

# Clean up obj files
clean:
	make -C lib_ft clean
	rm -f $(OBJS)

# Full clean up
fclean: clean
	rm -f $(NAME)
	make -C lib_ft fclean

# Rebuild
re: fclean all

# Ensure that 'all', 'clean', 'fclean', 're', and 'bonus' are not interpreted as file names
.PHONY: all clean fclean re bonus

# Test

test: test.c
	rm -f test
	sleep 1
	cc test.c -o test -I./inc -L./lib_ft -l:libft.a -lreadline -lm -g
