/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:14:58 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/10/22 14:20:47 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/** TODO: find_path
* @brief: look for path and returns it if it was found
* @takes: command and environment
//=======================================================================//
* @HOW_IT_works:
// envp[i] contains "PATH=/bin:/usr/bin:/some/other/dir"
// skip the "PATH=" (5 characters) and split the directories by ':'
// Construct the full path to the command
// If access fails, free the current path and move to the next directory
// Free the paths array if the command was not found
// Return NULL if the command was not found in any path
//=======================================================================//
* @returns: path
*/

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}

int	count_args(t_command_full *cmd)
{
	int				i;
	t_command_full	*tmp;

	i = 0;
	tmp = cmd;
	if (cmd->args == NULL)
		return (0);
	while (tmp->args[i] != NULL)
		i++;
	return (i);
}

/** TODO: make_exec_args
* @brief: builds array of strngs which we gonna use in execve func
* @takes: command
//=======================================================================//
* @HOW_IT_works:
// allocates memory for array (+2 for cmd_name and NULL)
// the first elememt is command name, the last elememt is NULL
//=======================================================================//
* @returns: array of strings for execve
*/

char	**make_exec_args(t_command_full *cmd)
{
	int		arg_count;
	char	**res;
	int		i;

	arg_count = count_args(cmd);
	res = malloc(sizeof(char *) * (arg_count + 2));
	if (!res)
		return NULL;
	res[0] = cmd->cmd_name;
	i = 0;
	while (i < arg_count)
	{
		res[i + 1] = cmd->args[i];
		i++;
	}
	res[arg_count + 1] = NULL;
	return (res);
}

void	execute(char **envp, t_command_full *cmd)
{
	int 	i;
	char	*path;
	char	**exec_args;
	
	i = -1;
	path = find_path(cmd->cmd_name, envp);
	if (!path)
	{
		// free cmd here
		//free(exec_args);
		ft_putstr_fd("Error: command not found in PATH\n", 2);
		exit(EXIT_FAILURE);
	}
	exec_args = make_exec_args(cmd);
	if (!exec_args)
	{
		free(path);
		ft_putstr_fd("Error: failed to create exec arguments\n", 2);
		exit(EXIT_FAILURE);
	}
	if (execve(path, exec_args, envp) == -1)
	{
		free(exec_args);
		free(path);
		ft_putstr_fd("Error executing the command\n", 2);
		exit(EXIT_FAILURE);
	}
	free(exec_args);
	free(path);
}

int	open_file(char *argv, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 2)
		file = open(argv, O_RDONLY, 0777);
	if (file == -1)
		ft_putstr_fd("some issues with file opening\n", 2);
	return (file);
}

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
// Checks if there is only 1 command, in this case calls execute_single_command func
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
