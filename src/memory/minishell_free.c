/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 20:12:35 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/15 18:50:27 by gbuczyns         ###   ########.fr       */
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
	int			i;
	t_execcmd	*execcmd;

	if (!node)
		return ;
	execcmd = (t_execcmd *)node;
	if (execcmd->argv)
	{
		i = 0;
		while (execcmd->argv[i])
		{
			free(execcmd->argv[i]);
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

	if (minishell->num_of_cmds < 2)
		return ;
	if (!minishell || !minishell->pipe_argv)
		return ;
	i = 0;
	while (minishell->pipe_argv[i])
	{
		free(minishell->pipe_argv[i]); // Free each row (int*)
		i++;
	}
	// Free the main array
	free(minishell->pipe_argv);
	minishell->pipe_argv = NULL;
}

void	free_global(t_data *minishell)
{
	int	i;

	if (!minishell)
		return ;
	// Free the input string
	if (minishell->input)
		free(minishell->input);
	// Free the pipe_argv using the helper function
	free_pipes(minishell);
	// Free each command in the commands array
	if (minishell->commands)
	{
		i = 0;
		while (minishell->commands[i])
		{
			free_cmd(minishell->commands[i]); // Free each command
			i++;
		}
		free(minishell->commands); // Free the commands array itself
	}
	// free(minishell);
}
