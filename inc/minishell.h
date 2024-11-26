/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:40:15 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/11/26 16:03:50 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

# define PROMPT "Mini_hell > "
# define HEREDOC_PROMPT "> "

# ifndef ECHOCTL
#  define ECHOCTL 0001000
# endif

extern int	g_last_exit_status;

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

// common tools
char			**append_string_to_array(char **new_str, char **args);
char			*ft_join_with_delimeter(char *s1, char *s2, char *delimiter);
int				ft_strcmp(const char *str1, const char *str2);

// LifeCycle
void			reset_echoctl(void);
bool			handle_empty_input(t_data **minishell);
bool			handle_whitespace_or_syntax(t_data **minishell);
bool			process_tokens(t_data **minishell);
void			execute_commands(t_data **minishell);
void			minishell_loop(t_data **minishell);

// signals
void			setup_signal_handlers(void);
int				termios_change(bool echo_ctl_chr);

// Validate_input
bool			ft_input_is_valid(char *input_str);

// environment
t_env			*environment_new_node(char *key, char *value);
void			environment_new_node_end(t_data *minishell, char *key,
					char *value);
void			init_environment(t_data **minishell, char **envir);
void			environment_free_list(t_env *head);
void			add_to_env(t_data **minishell, char *key, char *new_value);
void			delete_node(t_env **head_ref, t_env *node_to_delete);

//tokens
t_tokens		*update_token_word(t_tokens *token, char *input, int type);
t_tokens		*update_token(t_tokens *token, char *input, int type);
int				init_tokens(t_data **minishell);
void			ft_free_token_list(t_tokens **token_list);
int				validate_tokens(t_tokens *tokens);

//	new potential libft function
char			*ft_strncpy(char *dest, char *src, int num);
void			ft_skip_whitespace(char **s);
bool			ft_is_whitespace(char c);
int				ft_is_only_whitespace(char *str);

//Parsing
int				ft_handle_less(char *filename);
void			ft_helper_handle_redirection(t_command_full **cmd,
					t_redir **redir, t_data **minishell);
int				ft_get_arg_len(char *string);
int				ft_set_redirection_properties(t_redir *redir, t_tokens *token,
					t_data **shell);
char			*ft_insert_str(char *src, int old_part_len,
					char *insertable_str, int insert_ind);
char			*create_arg_duplicate(char **full_arg, int start_index);
int				handle_exit_status_substitution(char **full_arg,
					int start_index);
t_redir			*ft_scroll_redir_list_to_last(t_redir *redir_list_head);
void			ft_handle_word(t_command_full **temp_command,
					t_tokens **temp_token, t_data **minishell);
char			*ft_handle_here_doc(t_redir *current_redir);
int				ft_handle_output(t_redir *redir);
void			ft_close_all_redirections(t_command_full *cmd,
					t_redir *redirect_list);
t_redir			*ft_init_redir(void);
t_command_full	*ft_parse_tokens(t_data **minishell);
void			ft_expand_input(t_data **minishell);
char			*ft_errase_quote(t_data **minishell, char **temp_arg);
int				ft_process_redirection_list(t_data **minishell);

//error handling
void			ft_free_commands(t_data **minishell);
void			ft_free_token_list(t_tokens **token_list);
void			ft_free_minishell(t_data **minishell, bool is_crash);
void			ft_handle_error(bool is_crashable, char *error_text,
					int err_status, t_data **minishell);

//convert environment
char			**convert_env_to_array(t_env *env);

//built-ins
bool			is_builtin(t_command_full *cmd);
int				handle_builtins(t_data **minishell);
int				builtin_echo(char **args, int fd_out);
int				builtin_pwd(void);
int				builtin_env(t_env *node);
int				builtin_cd(t_data **minishell);
int				builtin_export(t_data **minishell);
int				builtin_unset(t_data **minishell);
int				builtin_exit(t_data **minishell);
void			swap(t_env *a, t_env *b);
void			sort_env_list(t_env **head);
char			*format_env_entry(t_env *node);

// execution
void			execute(char **envp, t_command_full *cmd);
void			child_process(t_command_full *cmd, char **envp);
void			handle_1_cmd(t_command_full *cmd, char **envp,
					t_data **minishell);
void			exec_pipeline(t_command_full *cmd_list, char **envp,
					t_data **minishell);
void			setup_heredoc(t_command_full *cmd);

#endif