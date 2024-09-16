/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ja <ja@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:59:52 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/16 20:58:05 by ja               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	close_pipes(int **pipe_argv, int commands);
static void	ft_child_process(t_cmd *cmd, t_data *minishell, int i);
static void	ft_write_fd(t_cmd *cmd, t_data *minishell, int i);
static void	ft_read_fd(t_cmd *cmd, t_data *minishell, int i);

void	make_forks(t_data *minishell)
{
	int		i;
	int		status;
	int		**pipe_argv;
	int		num_of_cmds;
	int		j;
	t_cmd	*cmd;

	i = 0;
	num_of_cmds = minishell->num_of_cmds;
	pipe_argv = minishell->pipe_argv;
	malloc_int_array(&(minishell->pids), num_of_cmds);
	while (i < num_of_cmds)
	{
		cmd = minishell->commands[i];
		minishell->pids[i] = fork();
		if (minishell->pids[i] == 0)
		{
			ft_child_process(cmd, minishell, i);
			exit(0);
		}
		i++;
	}
	j = 0;
	while (j < num_of_cmds)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			minishell->exit_status = WEXITSTATUS(status);
		j++;
	}
	close_pipes(pipe_argv, num_of_cmds);
}

static void	ft_child_process(t_cmd *cmd, t_data *minishell, int i)
{
	t_execcmd	*execcmd;

	ft_read_fd(cmd, minishell, i);
	ft_write_fd(cmd, minishell, i);
	if (runcmd(cmd, minishell) == -1)
	{
		execcmd = (t_execcmd *)cmd;
		write(2, execcmd->argv[0], ft_strlen(execcmd->argv[0]));
		write(2, ": command not found\n", 20);
		exit(127);
	}

}

static void	ft_read_fd(t_cmd *cmd, t_data *minishell, int i)
{
	int	j;

	j = 0;
	if ((i == 0) && (cmd->fd_to_read > 0))
	{
		if (dup2(cmd->fd_to_read, 0) == -1)
			perror("Error!");
		close(cmd->fd_to_read);
	}
	if (i > 0)
		if (dup2(minishell->pipe_argv[i - 1][0], 0) == -1)
			perror("Error!");
	while (j < minishell->num_of_cmds - 1)
	{
		if (j != (i - 1))
			close(minishell->pipe_argv[j][0]);
		j++;
	}
}

static void	ft_write_fd(t_cmd *cmd, t_data *minishell, int i)
{
	int	j;

	if (i < minishell->num_of_cmds - 1)
		if (dup2(minishell->pipe_argv[i][1], 1) == -1)
			perror("Error!");
	if (cmd->fd_to_write > 0)
		if (dup2(cmd->fd_to_write, 1) == -1)
			perror("Error!");
	j = 0;
	while (j < minishell->num_of_cmds - 1)
	{
		// if (j != i)
		close(minishell->pipe_argv[j][1]);
		j++;
	}
}
static void	close_pipes(int **pipe_argv, int commands)
{
	int i;

	i = 0;
	while (i < commands - 1)
	{
		close(pipe_argv[i][0]);
		close(pipe_argv[i][1]);
		i++;
	}
}