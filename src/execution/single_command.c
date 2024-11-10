/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:53:20 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/11/09 20:01:55 by ufo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	execute_single_command(t_command_full *cmd, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Fork failed\n", 2);
		return ;
	}
	if (pid == 0)
		child_process(cmd, envp);
	else
		waitpid(pid, NULL, 0);
}

void	handle_1_cmd(t_command_full *cmd, char **envp, t_data **minishell)
{
	if (is_builtin(cmd))
		handle_builtins(minishell);
	else
	{
		setup_heredoc(cmd);
		execute_single_command(cmd, envp);
	}
}