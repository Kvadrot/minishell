/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 19:31:05 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/20 19:34:13 by gbuczyns         ###   ########.fr       */
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