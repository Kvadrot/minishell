/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:30:16 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/17 19:10:07 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_cmd	*ft_init_exec_cmd(void)
{
	t_execcmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = EXEC;
	return ((t_cmd *)cmd);
}

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

char	*substring(const char *start, const char *end)
{
	size_t	length;
	char	*result;

	length = end - start;
	result = malloc(length + 1);
	if (result == NULL)
		return (NULL);
	strncpy(result, start, length);
	result[length] = '\0';
	return (result);
}

t_cmd	*parseexec(char **ps, char *es)
{
	t_execcmd	*cmd;
	t_cmd		*ret;

	char *q, *eq;
	int tok, argc;
	ret = ft_init_exec_cmd(); /* ret is general return type */
	cmd = (t_execcmd *)ret;
	/* need to be casted to specific type cmd stores current command */
	argc = 0;
	ret = parseredirs(ret, ps, es);
	/* parse redirections takes previous command and put it to redirections comand if redirection found  */
	cmd->argv = malloc(sizeof(char *) * 10 + 1);
	bzero(cmd->argv, 11 * sizeof(char *));
	while (!peek(ps, es, "|)&;")) /* while there is no pipe, end of block,
		semicolon or ampersand */
	{
		if ((tok = gettoken(ps, es, &q, &eq)) == 0)
			break ;
		if (tok != 'a')
			panic("syntax");
		cmd->argv[argc] = substring(q, eq);
		cmd->argv[argc + 1] = 0;
		argc++;
		if (argc >= MAXARGS)
			panic("too many args");
		ret = parseredirs(ret, ps, es);
	}
	return (ret);
}

t_cmd	*parseredirs(t_cmd *cmd, char **ps, char *es)
{
	int tok;
	char *q, *eq;

	while (peek(ps, es, "<>"))
	{
		tok = gettoken(ps, es, 0, 0);
		if (gettoken(ps, es, &q, &eq) != 'a')
			panic("missing file for redirection");
		if (tok == '<')
			cmd = redircmd(cmd, q, eq, O_RDONLY, 0);
		else if (tok == '>')
			cmd = redircmd(cmd, q, eq, O_CREAT | O_WRONLY | O_TRUNC, 1);
		else if (tok == '+')
			cmd = redircmd(cmd, q, eq, O_WRONLY | O_CREAT | O_APPEND, 1);
		else if (tok == '-')
			cmd = here_doc_cmd(cmd, q, eq);
	}
	return (cmd);
}