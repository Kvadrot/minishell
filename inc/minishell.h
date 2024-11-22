/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/11/21 13:46:11 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

extern int last_exit_status;
# include <stdbool.h>
# include <signal.h>
# include <stdlib.h>
# include <termios.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "../lib_ft_printf/ft_printf.h"
# include "../lib_ft/libft.h"
# include "tokens.h"
# include "parsing.h"

# include "../src/common_tools/common_tools.h"
# include "../src/signals/signals.h"
# define PROMPT "Mini_hell > "
# define HEREDOC_PROMPT "> "

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
	int				stdin;
	int				stdout;
	t_tokens		*tokens;
	t_env			*env;
	t_command_full	*commands;
	struct termios	terminal;
	struct s_data	*next;
}					t_data;

# include "../src/built_in/built_in.h"
# include "../src/execution/execution.h"

// DRBUG_FIELD
// DELETE ME befor release
//========================================================================================//
# include "../src/debug_functions/debuger.h"
//========================================================================================//

// LifeCycle
void	minishell_loop(t_data **minishell);

// Validate_input
bool				ft_input_is_valid(char *input_str);

t_env	*environment_new_node(char *key, char *value);
void	environment_new_node_end(t_data *minishell, char *key, char *value);
void	init_environment(t_data **minishell, char **envir);
void	environment_free_list(t_env *head);
void	add_to_env(t_data **minishell, char *key, char *new_value);
void	delete_node(t_env **head_ref, t_env *node_to_delete);

// tester functions
void				print_environment(t_env *node);

// tokens
int					init_tokens(t_data *minishell);
void				ft_free_token_list(t_tokens **token_list);
int					validate_tokens(t_tokens *tokens);

//	new potential libft function
char				*ft_strncpy(char *dest, char *src, int num);
void				ft_skip_whitespace(char **s);
bool				ft_is_whitespace(char c);
int					ft_is_only_whitespace(char *str);


//Parsing
t_command_full *ft_parse_tokens(t_data **minishell);
void	ft_expand_input(t_data **minishell);
char	*ft_errase_quote(t_data **minishell, char **temp_arg);
int		ft_process_redirection_list(t_data **minishell);

// error handling
void	ft_free_minishell(t_data **minishell, bool is_crash);
void	ft_handle_error(bool is_crashable, char *error_text, int err_status, t_data **minishell);

#endif