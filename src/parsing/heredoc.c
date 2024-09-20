/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:03:45 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/20 17:56:55 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	take_input(t_cmd *cmd, char *token)
{
	char	*line;
	char	*temp;

	if (cmd->argv == NULL)
	{
		cmd->argv = malloc(sizeof(char *));
		cmd->argv[0] = ft_strdup("");
	}
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			break ;
		}
		if (strcmp(line, token) == 0)
		{
			free(line);
			break ;
		}
		temp = ft_strjoin(cmd->argv[0], line);
		free(cmd->argv[0]);
		cmd->argv[0] = temp;
		temp = ft_strjoin(cmd->argv[0], "\n");
		free(cmd->argv[0]);
		cmd->argv[0] = temp;
		free(line);
	}
	free(token);
}



t_cmd	*here_doc_cmd(t_cmd *subcmd, char *q, char *eq)
{
	t_cmd	*cmd;
	char	*token;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = HERE_DOC;
	token = ft_strncpy(malloc(eq - q + 1), q, eq - q);
	token[eq - q] = '\0';
	(void)subcmd;
	take_input(cmd, token);
	printf("%s\n", cmd->argv[0]);
	return ((t_cmd *)cmd);
}
