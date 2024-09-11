/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:03:45 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/11 20:15:54 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	take_input(t_heredoc_cmd *cmd, char *token)
{
	char	*line;
	char	*temp;

	// Initialize cmd->argv if it's NULL
	if (cmd->argv == NULL)
	{
		cmd->argv = malloc(sizeof(char *));
		cmd->argv[0] = ft_strdup("");
	}
	while (1)
	{
		line = readline("our_heredoc> ");
		if (line == NULL)
		{
			// EOF reached
			break ;
		}
		if (strcmp(line, token) == 0)
		{
			// Delimiter found, exit loop
			free(line);
			break ;
		}
		// Append the line to cmd->argv[0]
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
	t_heredoc_cmd	*cmd;
	char			*token;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = HERE_DOC;
	token = ft_strncpy(malloc(eq - q + 1), q, eq - q);
	token[eq - q] = '\0'; // Ensure null-termination
	(void)subcmd;
	take_input(cmd, token);
	// cmd->cmd = subcmd;
	printf("%s\n", cmd->argv[0]);
	return ((t_cmd *)cmd);
}

/*
	t
	printf("%s\n", cmd->argv[0]);
	return ((t_cmd *)cmd);
 */