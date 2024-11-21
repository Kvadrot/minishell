/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:21:20 by ufo               #+#    #+#             */
/*   Updated: 2024/11/20 15:39:58 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_builtin(t_command_full *cmd);
int		handle_builtins(t_data **minishell);
int		builtin_echo(char **args, int fd_out);
int		builtin_pwd(void);
int		builtin_env(t_env *node);
int		builtin_cd(t_data **minishell);
int		builtin_export(t_data **minishell);
int		builtin_unset(t_data **minishell);
int		builtin_exit(t_data **minishell);
