/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:59:52 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/14 18:28:06 by gbuczyns         ###   ########.fr       */
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

	(void)minishell;
	i = 0;
	commands = minishell->number_of_commands;
	pipe_argv = minishell->pipe_argv;
	while (i < commands)
	{
		cmd = minishell->commands[i];
		if (i == 0)
			pid = fork();
		if (pid == 0)
		{
			if (i != 0)
				dup2(pipe_argv[i - 1][0], STDIN_FILENO); /*
					// zamieniamy wejscie na wyjscie z pipe
					// dla wszystkich oprocz pierwszego
					// czytamy z pipe */
			if (i != commands - 1)                       //
				dup2(pipe_argv[i][1], STDOUT_FILENO);    /*
						// zamykamy wyjscie stdout i podmieniamy na wyjscie do pipe
						// piszemy do pipe dla wszystkich oprocz ostatniego*/
			close_pipes(pipe_argv, commands);
			runcmd(cmd, minishell);
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