/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 19:31:05 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/21 21:33:54 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	append_to_argv(t_cmd *cmd, char *line)
{
	char	*temp;

	temp = ft_strjoin(cmd->argv[0], line);
	free(cmd->argv[0]);
	cmd->argv[0] = temp;
	temp = ft_strjoin(cmd->argv[0], "\n");
	free(cmd->argv[0]);
	cmd->argv[0] = temp;
}

void	init_cmd_argv(t_cmd *cmd)
{
	if (cmd->argv == NULL)
	{
		cmd->argv = malloc(sizeof(char *));
		cmd->argv[0] = ft_strdup("");
	}
}
/*
** Append a line to the argv array
*/
char	**ft_append_argv(char **argv, char *line)
{
	char	**new_argv;
	int		i;

	i = 0;
	while (argv && argv[i])
		i++;
	new_argv = malloc(sizeof(char *) * (i + 2));
	if (new_argv == NULL)
		panic("malloc");
	i = 0;
	while (argv && argv[i])
	{
		new_argv[i] = argv[i];
		i++;
	}
	new_argv[i] = ft_strdup(line);
	new_argv[i + 1] = NULL;
	return (new_argv);
}
