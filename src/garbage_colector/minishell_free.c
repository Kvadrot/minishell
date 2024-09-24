/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 20:12:35 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/24 15:46:35 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	minishell_free(t_data *minishell, int flag)
{
	// free memory
	(void)flag;
	(void)minishell;
	exit(0);
}

void	free_cmd(t_cmd *node)
{
	int	i;

	if (!node)
		return ;
	node = node;
	if (node->argv)
	{
		i = 0;
		while (node->argv[i])
		{
			free(node->argv[i]);
			i++;
		}
	}
	// Free paths
	if (execcmd->paths)
		free(execcmd->paths);
	// Free flag
	if (execcmd->flag)
		free(execcmd->flag);
	// Finally, free the node itself
	free(node);
}

void	free_pipes(t_data *minishell)
{
	int	i;

	if (minishell->number_of_commands < 2)
		return ;
	if (!minishell || !minishell->pipe_argv)
		return ;
	i = 0;
	while (minishell->pipe_argv[i])
	{
		free(minishell->pipe_argv[i]);
		i++;
	}
	free(minishell->pipe_argv);
	minishell->pipe_argv = NULL;
}

void	free_global(t_data *minishell)
{
	int	i;

	if (!minishell)
		return ;
	if (minishell->input)
		free(minishell->input);
	free_pipes(minishell);
	if (minishell->commands)
	{
		i = 0;
		while (minishell->commands[i])
		{
			free_cmd(minishell->commands[i]);
			i++;
		}
		free(minishell->commands);
	}
}
