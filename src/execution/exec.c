/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:14:58 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/10/23 17:12:47 by mbudkevi         ###   ########.fr       */
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

// void	execute_pipeline(t_command_full *cmd_list, char **envp)
// {
// 	t_command_full	*cmd;
// 	pid_t			pid;

// 	cmd = cmd_list;
// 	if (cmd != NULL && cmd->next == NULL)
// 	{
// 		execute_single_command(cmd, envp);
// 		return ;
// 	}
// 	setup_pipes_and_fds(cmd_list);
// 	while (cmd != NULL)
// 	{
// 		pid = fork();
// 		if (pid == -1)
// 			ft_putstr_fd("Fork failed\n", 2);
// 		if (pid == 0)
// 			child_process(cmd, envp);
// 		if (cmd->fd_out != STDOUT_FILENO)
// 			close(cmd->fd_out);
// 		if (cmd->fd_in != STDIN_FILENO)
// 			close(cmd->fd_in);
// 		waitpid(pid, NULL, 0);
// 		cmd = cmd->next;
// 	}
// }

void	handle_single_command(t_command_full *cmd, char **envp, t_data **minishell)
{
	if (is_builtin(cmd))
		handle_builtins(minishell);
	else
		execute_single_command(cmd, envp);
}

/** TODO: handle_command_execution
* @brief: handle_command_execution
* @takes: list of commands, environment, minishell
//=======================================================================//
* @HOW_IT_works:
// Handle built-in in the current process with redirection if needed
// Fork a child process for non-built-in commands
//=======================================================================//
* @returns: void
*/

void	handle_command_execution(t_command_full *cmd, char **envp, t_data **minishell)
{
	pid_t	pid;

	if (is_builtin(cmd))
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
		handle_builtins(minishell);
	}
	else
	{
		pid = fork();
		if (pid == -1)
		{
			ft_putstr_fd("Fork failed\n", 2);
			return ;
		}
		if (pid == 0)
			child_process(cmd, envp);
		waitpid(pid, NULL, 0);
	}
}

void	execute_pipeline_loop(t_command_full *cmd_list, char **envp, t_data **minishell)
{
	t_command_full	*cmd;

	cmd = cmd_list;
	while (cmd != NULL)
	{
		handle_command_execution(cmd, envp, minishell);
		if (cmd->fd_out != STDOUT_FILENO)
			close(cmd->fd_out);
		if (cmd->fd_in != STDIN_FILENO)
			close(cmd->fd_in);
		cmd = cmd->next;
	}
}

/** TODO: execute_pipeline
* @brief: execute commands in a pipeline
* @takes: list of commands, environment, minishell
//=======================================================================//
* @HOW_IT_WORKS:
// 1. If only one command is present, handle it directly without setting up pipes.
// 2. If there are multiple commands in the pipeline:
//    - Set up pipes for each command.
//    - For built-in commands: handle them in the current process with proper redirection.
//    - For non-built-in commands: fork a child process and execute them.
// 3. Close unused file descriptors to avoid file descriptor leaks.
//=======================================================================//
* @returns: void
*/

void	execute_pipeline(t_command_full *cmd_list, char **envp, t_data **minishell)
{
	if (cmd_list == NULL)
		return ;
	if (cmd_list->next == NULL)
	{
		handle_single_command(cmd_list, envp, minishell);
		return ;
	}
	setup_pipes_and_fds(cmd_list);
	execute_pipeline_loop(cmd_list, envp, minishell);
}