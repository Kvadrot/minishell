/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:21:24 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/14 18:08:29 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"
#include "../inc/minishell.h"



void	create_pipes(t_data *minishell)
{
	int				i;
	unsigned int	pipes;

	i = 0;
	pipes = minishell->number_of_commands - 1;
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
// void	setup_pipes(t_data *minishell)
// {
// 	unsigned int	commands;

// 	commands = minishell->number_of_commands;
// 	if (commands == 0)
// 		return ;
// 	if (commands == 1)
// 		do_single_comand();
// 	else
// 	{
// 		create_pipes(minishell);
// 		// make_pipes(minishell);
// 	}
// 	return ;
// }

// int	main(void)
// {
// 	t_data	minishell;
// 	int		i;

// 	i = 0;
// 	minishell.number_of_commands = 3;
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