/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/09/17 16:09:43 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib_ft/libft.h"
# include "tokens.h"
# include "parsing.h"
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdlib.h>
# include <termios.h>
# include <unistd.h>

# define PROMPT "Mini_hell > "

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
	t_command_full		*commands;
	struct termios	terminal;
	struct s_data	*next;
}					t_data;

// LifeCycle
void	minishell_loop(t_data **minishell);

// Validate_input
bool				ft_input_is_valid(char *input_str);

t_env				*environment_new_node(char *key, char *value);
void				environment_new_node_end(t_data *minishell, char *key, char *value);
void				init_environment(t_data **minishell, char **envir);
void				environment_free_list(t_env *head);

// tester functions
void				print_environment(t_env *node);

// tokens
int					init_tokens(t_data *minishell);
void				ft_free_token_list(t_tokens *token_list);
int					validate_tokens(t_tokens *tokens);

//	new potential libft function
char				*ft_strncpy(char *dest, char *src, int num);
void				ft_skip_whitespace(char **s);
bool				ft_is_whitespace(char c);


//Parsing
t_command_full *ft_parse_tokens(t_data **minishell);

// error handling
void	ft_handle_error(bool is_crashable, char *error_text, int err_status, t_data *minishell);



#endif