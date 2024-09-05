/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/09/05 20:22:45 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib_ft/libft.h"
# include "cmd.h"
# include "parsing.h"
# include "tokens.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# define PROMPT "MDshell > "
# define YES 1
# define NO 0
# define ERROR -1
# define SUCCESS 0

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

typedef struct s_llist
{
	char			*content;
	struct s_llist	*next;
}					t_llist;

typedef struct s_data
{
	char			*input;
	char			**envir;
	char			*environment;
	int				stdin;
	int				stdout;
	t_tokens		*tokens;
	t_env			*envlist;
	t_command		*commands;
	t_llist			*tracker;
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

void				minishell_free(t_data *minishell, int flag);

t_tokens			*convert_input_to_tokens(t_data *minishell);

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
int					md_cd(char *path, t_data *minishell);
void				ft_update_env_list(char *key, char *value, bool yes,
						t_data *minishell);
char				*ft_get_envlst_val(char *key, t_data *minishell);
void				*gc_collector(void *list, bool free);
void				ft_envlstadd_back(t_env *new, t_data *minishell);
void				ft_lstclear(t_list **lst, void (*del)(void *));
int					peek(char **ps, char *es, char *toks);
void				panic(char *s);
t_cmd		*nulterminate(t_cmd *cmd);
int					gettoken(char **ps, char *es, char **q, char **eq);

// execution
t_cmd		*execcmd(void);
t_cmd		*redircmd(t_cmd *subcmd, char *file, char *efile,
						int mode, int fd);
t_cmd	*pipecmd(t_cmd *left, t_cmd *right);
t_cmd	*listcmd(t_cmd *left, t_cmd *right);
t_cmd	*backcmd(t_cmd *subcmd);


#endif