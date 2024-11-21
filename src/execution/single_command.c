/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:53:20 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/11/20 15:17:39 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	execute_single_command(t_command_full *cmd, char **envp)
{
	pid_t	pid;
	int		status;

	printf("%s\n", cmd->cmd_name);
	int i = 0;
	while (cmd->args != NULL)
	{
		printf("arg is %s\n", cmd->args[i]);
		i++;
	}
	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Fork failed\n", 2);
		return ;
	}
	if (pid == 0)
		child_process(cmd, envp);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			last_exit_status = WEXITSTATUS(status);
	}
}

void	handle_1_cmd(t_command_full *cmd, char **envp, t_data **minishell)
{
	if (is_builtin(cmd))
		last_exit_status = handle_builtins(minishell);
	else
	{
		setup_heredoc(cmd);
		execute_single_command(cmd, envp);
	}
}
