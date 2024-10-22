/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:14:58 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/10/22 11:36:46 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	// envp[i] contains "PATH=/bin:/usr/bin:/some/other/dir"
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
    // skip the "PATH=" (5 characters) and split the directories by ':'
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
    // Construct the full path to the command
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

char	**make_exec_args(t_command_full *cmd)
{
	int		arg_count;
	char	**res;
	int		i;

	arg_count = count_args(cmd);
	res = malloc(sizeof(char *) * (arg_count + 2));  // +2 for cmd_name and NULL
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
		ft_printf_full("Error: command not found in PATH\n", 2, NULL);
		exit(EXIT_FAILURE);
	}
	exec_args = make_exec_args(cmd);
	if (!exec_args)
	{
		free(path);
		ft_printf_full("Error: failed to create exec arguments\n", 2, NULL);
		exit(EXIT_FAILURE);
	}
	if (execve(path, exec_args, envp) == -1)
	{
		free(exec_args);
		free(path);
		ft_printf_full("Error executing the command", 2, NULL);
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
		ft_printf_full("some issues with file opening", 2, NULL);
	return (file);
}

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
			// Set the output of the current command to the pipe's write end
			cmd->fd_out = fd[1];
			// Set the input of the next command to the pipe's read end
			cmd->next->fd_in = fd[0];
		}
		cmd = cmd->next;
	}
}

void	child_process(t_command_full *cmd, char **envp)
{
	// Input redirection if needed
	if (cmd->fd_in != STDIN_FILENO)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	// Output redirection if needed
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
		ft_printf_full("Fork failed", 2, NULL);
		return ;
	}
	if (pid == 0)
		child_process(cmd, envp);
	else  // Parent process
		waitpid(pid, NULL, 0);
}

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
		ft_printf_full("Fork failed", 2, NULL);
		if (pid == 0)
			child_process(cmd, envp);
		// Parent process: close the pipe ends we don't need
		if (cmd->fd_out != STDOUT_FILENO)
			close(cmd->fd_out);
		if (cmd->fd_in != STDIN_FILENO)
			close(cmd->fd_in);
		waitpid(pid, NULL, 0);
		cmd = cmd->next;
	}
}