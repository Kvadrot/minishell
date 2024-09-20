/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:03:45 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/20 18:59:40 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void init_cmd_argv(t_cmd *cmd)
{
	if (cmd->argv == NULL)
	{
		cmd->argv = malloc(sizeof(char *));
		cmd->argv[0] = ft_strdup("");
	}
}

static int is_matching_token(char *line, char *token)
{
	if (strcmp(line, token) == 0)
	{
		free(line);
		return 1;
	}
	return 0;
}

void append_to_argv(t_cmd *cmd, char *line)
{
	char *temp;

	temp = ft_strjoin(cmd->argv[0], line);
	free(cmd->argv[0]);
	cmd->argv[0] = temp;
	temp = ft_strjoin(cmd->argv[0], "\n");
	free(cmd->argv[0]);
	cmd->argv[0] = temp;
}

void take_input(t_cmd *cmd, char *token)
{
	char *line;

	init_cmd_argv(cmd);

	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (is_matching_token(line, token))
			break ;
		free(line);
	}

	free(token);
}

t_cmd *here_doc_cmd(t_cmd *sub_cmd, char *q, char *eq)
{
	t_cmd *cmd;
	char *token;

	cmd = ft_init_cmd(HERE_DOC);
	token = ft_strncpy(malloc(eq - q + 1), q, eq - q);
	token[eq - q] = '\0';

	cmd->sub_cmd = sub_cmd;
	take_input(cmd, token);

	return cmd;
}

void	do_heredoc(t_cmd *cmd, t_data *minishell)
{
	int p[2];

	pipe(p);
	if (fork1() == 0)
	{
		dup2(p[1], 1);
		close(p[1]);
		close(p[0]);
		printf("%s", cmd->argv[0]);
		exit(0);
	}
	if (fork1() == 0)
	{
		dup2(p[0], 0);
		close(p[1]);
		close(p[0]);
		runcmd(cmd->sub_cmd, minishell);
		exit(0);
	}
	close(p[1]);
	close(p[0]);
	wait(0);
	wait(0);
	exit(0);
}