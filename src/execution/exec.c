/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:14:58 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/10/23 11:46:14 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/** TODO: setup_pipes_and_fds
* @brief: setup_pipes_and_fds
* @takes: command
//=======================================================================//
* @HOW_IT_works:
// Set the output of the current command to the pipe's write end
// Set the input of the next command to the pipe's read end
//=======================================================================//
* @returns: void
*/

void	setup_pipes_and_fds(t_command_full *command)
{
	int				fd[2];
	t_command_full	*cmd;

	cmd = command;
	while (cmd != NULL)
	{
		if (cmd->next != NULL)
		{
			pipe(fd);
			cmd->fd_out = fd[1];
			cmd->next->fd_in = fd[0];
		}
		cmd = cmd->next;
	}
}

/** TODO: child_process
* @brief: child_process
* @takes: command and environment
//=======================================================================//
* @HOW_IT_works:
// Input redirection if needed
// Output redirection if needed
// execute
//=======================================================================//
* @returns: void
*/

void	child_process(t_command_full *cmd, char **envp)
{
	if (cmd->fd_in != STDIN_FILENO)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	if (cmd->fd_out != STDOUT_FILENO)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
	execute(envp, cmd);
}

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

/** TODO: execute_pipeline
* @brief: execute_pipeline
* @takes: list of commands, environment
//=======================================================================//
* @HOW_IT_works:
// Checks if there is only 1 command, 
// in this case calls execute_single_command func
// if not, setup_pipes_and_fds
// execute
// child process
// Parent process: close the pipe ends we don't need
//=======================================================================//
* @returns: void
*/

void	execute_pipeline(t_command_full *cmd_list, char **envp)
{
	t_command_full	*cmd;
	pid_t			pid;

	cmd = cmd_list;
	if (cmd != NULL && cmd->next == NULL)
	{
		execute_single_command(cmd, envp);
		return ;
	}
	setup_pipes_and_fds(cmd_list);
	while (cmd != NULL)
	{
		pid = fork();
		if (pid == -1)
			ft_putstr_fd("Fork failed\n", 2);
		if (pid == 0)
			child_process(cmd, envp);
		if (cmd->fd_out != STDOUT_FILENO)
			close(cmd->fd_out);
		if (cmd->fd_in != STDIN_FILENO)
			close(cmd->fd_in);
		waitpid(pid, NULL, 0);
		cmd = cmd->next;
	}
}
