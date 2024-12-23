# Compiler
CC = gcc

# Compiler flags
WARNFLAGS = -Wall -Wextra -Werror
RLFLAG = -lreadline -lm -g
CFLAGS = -g
HEADERS = -I./lib_ft -I./lib_ft_printf -I./inc

#Linux flags
LDFLAGS = -L./lib_ft -l:libft.a -L./lib_ft_printf -lftprintf $(RLFLAG)

SRC_DIR = src/
OBJ_DIR = obj/
OBJ_DIR2 = obj/tokens/
OBJ_DIR3 = obj/validation/
OBJ_DIR4 = obj/parsing/
OBJ_DIR5 = obj/error_handler/
OBJ_DIR7 = obj/built_in/
OBJ_DIR8 = obj/common_tools/
OBJ_DIR9 = obj/execution/
OBJ_DIR10 = obj/signals/
OBJ_DIR11 = obj/environment/


# Default sources
SRC = main.c \
	convert_env.c \
	environment/env_helpers.c \
	environment/env.c \
	minishell_loop_helpers.c \
	built_in/bi_echo.c \
	built_in/builtin_env.c \
	built_in/builtin_pwd.c \
	built_in/builtin_cd.c \
	built_in/builtin_export.c \
	built_in/builtin_unset.c \
	built_in/builtin_exit.c \
	built_in/helpers.c \
	built_in/handle_builtins.c \
	execution/single_command.c \
	execution/exec.c \
	execution/helpers.c \
	execution/handle_heredoc.c \
	signals/signals.c \
	parsing/expander_helpers.c \
	parsing/parsing_utils.c \
	parsing/redir_helper.c \
	parsing/utils.c \
	parsing/parsing.c \
	parsing/quote_erraser.c \
	parsing/expander.c \
	parsing/redirection_handler.c \
	tokens/tokens_helpers.c \
	tokens/tokens.c \
	tokens/tokens_utils.c \
	validation/validation.c \
	error_handler/error_handler_helpers.c \
	error_handler/error_handling.c \
	common_tools/append_string_to_array.c \
	common_tools/ft_join_with_delimeter.c \
	common_tools/ft_strcmp.c \


SRCS = $(addprefix ${SRC_DIR}, ${SRC})
#OBJS = $(SRCS:.c=.o)
 OBJS = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))
# Rule to compile .c files into .o files.
$(OBJ_DIR)%.o:  $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR2)
	@mkdir -p $(OBJ_DIR3)
	@mkdir -p $(OBJ_DIR4)
	@mkdir -p $(OBJ_DIR5)
	@mkdir -p $(OBJ_DIR7)
	@mkdir -p $(OBJ_DIR8)
	@mkdir -p $(OBJ_DIR9)
	@mkdir -p $(OBJ_DIR10)
	@mkdir -p $(OBJ_DIR11)

	@echo "Compiling $< with $(WARNFLAGS) $(CFLAGS) $(HEADERS)"
	$(CC) $(WARNFLAGS) $(CFLAGS) $(HEADERS) $< -c -o $@

# Program Name
NAME = minishell

# Libft src
LIBFT = ./lib_ft/libft.a

# ft_printf
FTPRINTF = ./lib_ft_printf/libftprintf.a

# Default rule
all: $(LIBFT) $(FTPRINTF) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(WARNFLAGS) $(CFLAGS) $(HEADERS) $(OBJS) -o $(NAME) $(LDFLAGS)

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
