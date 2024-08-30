/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/08/30 21:00:59 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib_ft/libft.h"
# include "parsing.h"
# include "tokens.h"
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdlib.h>
# include <termios.h>
# include <unistd.h>

# define PROMPT "MDshell > "

// DRBUG_FIELD
// DELETE ME befor release
//========================================================================================//
# include "../lib_ft_printf/ft_printf.h"
//========================================================================================//

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_data
{
	char			*input;
	char			**envir;
	char			*environment;
	int				stdin;
	int				stdout;
	t_tokens		*tokens;
	t_env			*env;
	t_command		*commands;
	struct termios	terminal;
	struct s_data	*next;
}					t_data;

// Validate_input
bool				ft_input_is_valid(char *input_str);

void				minishell_loop(t_data *minishell);

t_env				*environment_new_node(char *key, char *value);
void				environment_new_node_end(t_env **head, char *key,
						char *value);
void				init_environment(t_env **environment, char **env);
void				environment_free_list(t_env *head);

void				environment_free_list(t_env *head);

// tester functions
void				print_environment(t_env *node);

// tokens
void				init_tokens(t_data *minishell);

//	new potential libft function
char				*ft_strncpy(char *dest, char *src, int num);
void				ft_skip_whitespace(char **s);
bool				ft_is_whitespace(char c);

t_command			*parse_tokens(t_tokens *tokens);
int					check_syntax(t_tokens *tokens);

void				free_commands(t_command *command);

#endif