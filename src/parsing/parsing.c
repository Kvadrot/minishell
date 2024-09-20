/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:30:16 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/20 18:27:14 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	alloc_mem_for_commands(t_data *minishell)
{
	char	*input;
	int		pipe_count;

	pipe_count = 0;
	input = minishell->input;
	while (*input)
	{
		if (*input == '|')
			pipe_count++;
		input++;
	}
	minishell->commands = (t_cmd **)malloc(sizeof(t_cmd *) * (pipe_count + 2));
	if (minishell->commands == NULL)
		panic("malloc");
	minishell->commands[pipe_count + 1] = NULL;
}

void	parsecmd(t_data *minishell)
{
	int		i;
	t_cmd	*cmd;
	char	*es;
	char	*ps;

	i = 0;
	ps = minishell->input;
	es = minishell->input + ft_strlen(minishell->input);
	while (ps <= es)
	{
		cmd = parseexec(&ps, es);
		if (cmd)
		{
			minishell->commands[i] = cmd;
			minishell->number_of_commands++;
		}
		peek(&ps, es, "|");
		ps++;
		i++;
	}
}

t_cmd	*parseexec(char **ps, char *es)
{
	t_cmd	*cmd;
	t_cmd	*ret;

	ret = ft_init_cmd(EXEC);
	cmd = ret;
	ret = parseredirs(ret, ps, es);
	handle_tokens(cmd, &ret, ps, es);
	return (ret);
}

t_cmd	*parseredirs(t_cmd *cmd, char **ps, char *es)
{
	int		tok;
	char	*q;
	char	*eq;

	while (peek(ps, es, "<>"))
	{
		tok = gettoken(ps, es, 0, 0);
		if (gettoken(ps, es, &q, &eq) != 'a')
			panic("missing file for redirection");
		if (tok == '<')
			cmd = redircmd(cmd, q, O_RDONLY, 0);
		else if (tok == '>')
			cmd = redircmd(cmd, q, O_CREAT | O_WRONLY | O_TRUNC, 1);
		else if (tok == '+')
			cmd = redircmd(cmd, q, O_WRONLY | O_CREAT | O_APPEND, 1);
		else if (tok == '-')
			cmd = here_doc_cmd(cmd, q, eq);
	}
	return (cmd);
}
