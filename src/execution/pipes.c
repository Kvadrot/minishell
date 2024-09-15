/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:21:24 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/15 19:11:01 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	create_pipes(t_data *minishell)
{
	int	i;
	int	pipes;

	i = 0;
	pipes = minishell->num_of_cmds - 1;
	minishell->pipe_argv = (int **)malloc(sizeof(int *) * (pipes + 1));
	if (minishell->pipe_argv == NULL)
		panic("malloc");
	minishell->pipe_argv[pipes] = NULL;
	while (i < pipes)
	{
		minishell->pipe_argv[i] = (int *)malloc(2 * sizeof(int));
		if (minishell->pipe_argv[i] == NULL)
			panic("malloc");
		i++;
	}
}
void	run_with_pipes(t_data *minishell)
{
	unsigned int	commands;

	commands = minishell->num_of_cmds;
	if (commands == 0)
		return ;
	if (commands == 1)
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
	return ;
}

void	ft_read_fd(t_command *command, t_data *minishell, int i)
{
	int	j;

	j = 0;
	if ((i == 0) && (command->redirs.input_redir > 0))
		if (dup2(command->redirs.input_redir, 0) == -1)
			perror("Error!");
	if (i > 0)
		if (dup2(gen->pipes[i - 1][0], 0) == -1)
			perror("Error!");
	while (j < gen->num_of_cmds - 1)
	{
		if (j != (i - 1))
			close(gen->pipes[j][0]);
		j++;
	}
}

void	ft_write_fd(t_command *command, t_gen *gen, int i)
{
	int	j;

	if (i < gen->num_of_cmds - 1)
		if (dup2(gen->pipes[i][1], 1) == -1)
			perror("Error!");
	if ((i == gen->num_of_cmds - 1) && (command->redirs.output_redir > 0))
		if (dup2(command->redirs.output_redir, 1) == -1)
			perror("Error!");
	j = 0;
	while (j < gen->num_of_cmds - 1)
	{
		if (j != i)
			close(gen->pipes[j][1]);
		j++;
	}
}

// int	main(void)
// {
// 	t_data	minishell;
// 	int		i;

// 	i = 0;
// 	minishell.num_of_cmds = 3;
// 	setup_pipes(&minishell);
// 	if (minishell.pipe_argv != NULL)
// 	{
// 		printf("pipe_argv is not NULL\n");
// 		while (minishell.pipe_argv[i] != NULL)
// 		{
// 			printf("pipe_argv[%d] is not NULL\n", i);
// 			i++;
// 		}
// 	}
// 	return (0);
// }

// void	panic(char *str)
// {
// 	printf("panic: %s\n", str);
// 	exit(1);
// }

void	do_single_comand(void)
{
	printf("do_single_comand\n");
}