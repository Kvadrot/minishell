/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:21:24 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/22 00:00:40 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

pid_t	fork1(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		panic("fork");
	return (pid);
}

void	create_pipes(t_data *minishell)
{
	int	i;
	int	pipes;

	i = 0;
	pipes = minishell->number_of_commands - 1;
	minishell->pipe_argv = (int **)malloc(sizeof(int *) * pipes);
	if (minishell->pipe_argv == NULL)
		panic("malloc");
	while (i < pipes)
	{
		minishell->pipe_argv[i] = (int *)malloc(2 * sizeof(int));
		if (minishell->pipe_argv[i] == NULL)
			panic("malloc");
		if (pipe(minishell->pipe_argv[i]) == -1)
			panic("pipe");
		i++;
	}
}

int	execute(t_data *minishell)
{
	int	commands;

	commands = minishell->number_of_commands;
	if (commands == 0)
		return (1);
	if (commands == 1 && is_builtin(*(minishell->commands)) && minishell->commands[0]->type == EXEC)
	{
		return (run_builtin_cmd(minishell->commands[0]->argv, minishell));
	}
	else if (commands == 1)
	{
		if (fork1() == 0)
			runcmd(minishell->commands[0], minishell);
		wait(NULL);
	}
	else
	{
		create_pipes(minishell);
		make_forks(minishell);
	}
	return (0);
}
