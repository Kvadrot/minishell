/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:56:21 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/10/13 14:52:35 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_builtins(t_data **minishell)
{
	if (ft_strncmp((*minishell)->commands->cmd_name, "echo", ft_strlen("echo")) == 0)
		builtin_echo((*minishell)->commands->args);
	if (ft_strncmp((*minishell)->commands->cmd_name, "cd", ft_strlen("cd")) == 0)
		builtin_cd(minishell);
	if (ft_strncmp((*minishell)->commands->cmd_name, "env", ft_strlen("env")) == 0)
		builtin_env((*minishell)->env);
	if (ft_strncmp((*minishell)->commands->cmd_name, "pwd", ft_strlen("pwd")) == 0)
		builtin_pwd();
	if (ft_strncmp((*minishell)->commands->cmd_name, "export", ft_strlen("export")) == 0)
		builtin_export(minishell);
	if (ft_strncmp((*minishell)->commands->cmd_name, "unset", ft_strlen("unset")) == 0)
		builtin_unset(minishell);
	if (ft_strncmp((*minishell)->commands->cmd_name, "exit", ft_strlen("exit")) == 0)
		builtin_exit();
}