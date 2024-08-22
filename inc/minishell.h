/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */


#ifndef MINISHELL_H
# define MINISHELL_H


# include "../lib_ft/libft.h"
# include "tokens.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdlib.h>
# include <termios.h>
# include <unistd.h>

# define PROMPT "MDshell > "
#define YES 1
#define NO 0

// DRBUG_FIELD
// DELETE ME befor release
//========================================================================================//
# include "../lib_ft_printf/ft_printf.h"
//========================================================================================//

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;


typedef struct s_llist
{
	char				*content;
	struct s_llist		*next;
} 						t_llist;


typedef struct s_data
{
	char				*input;
	char				**envir;
	char				*environment;
	int					stdin;
	int					stdout;
	t_tokens			*tokens;
	t_env				*env;
	struct termios		terminal;
	struct s_minishell	*next;
	t_llist				*tracker;
}						t_data;

// Validate_input
bool	ft_input_is_valid(char *input_str);

void					minishell_loop(t_data *minishell);

t_env					*environment_new_node(char *key, char *value);
void					environment_new_node_end(t_env **head, char *key,
							char *value);
void					init_environment(t_env **environment, char **env);
void					environment_free_list(t_env *head);

void					environment_free_list(t_env *head);

void minishell_free(t_data *minishell, int flag);





t_tokens	*convert_input_to_tokens(t_data *minishell);

// tester functions
void					print_environment(t_env *node);

#endif