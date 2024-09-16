/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:59:52 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/15 19:13:10 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	close_pipes(int **pipe_argv, int commands);

void	make_forks(t_data *minishell)
{
	int		i;
	int		pid;
	int		status;
	int		**pipe_argv;
	int		commands;
	int		j;
	t_cmd	*cmd;

	minishell->pids = malloc((minishell->num_of_cmds + 1) * sizeof(int));
	i = 0;
	commands = minishell->num_of_cmds;
	pipe_argv = minishell->pipe_argv;
	while (i < commands)
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
	while (j < commands)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			minishell->exit_status = WEXITSTATUS(status);
		j++;
	}
	// close_pipes(pipe_argv, commands);
}

void	ft_child_process(t_cmd *cmd, t_data *minishell, int i)
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
	free(execcmd->argv);
}

 		// if (i != 0)
		// 	if (pid == 0)
		// 	{
		// 		if (i != 0)
		// 			dup2(pipe_argv[i - 1][0], STDIN_FILENO); /*
		// 				// zamieniamy wejscie na wyjscie z pipe
		// 				// dla wszystkich oprocz pierwszego
		// 				// czytamy z pipe */
		// 		if (i != commands - 1)                       //
		// 			dup2(pipe_argv[i][1], STDOUT_FILENO);    /*
		// 					// zamykamy wyjscie stdout i podmieniamy na wyjscie do pipe
		// 					// piszemy do pipe dla wszystkich oprocz ostatniego*/
		// 		close_pipes(pipe_argv, commands);
		// 		runcmd(cmd, minishell);
		// 	} 

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