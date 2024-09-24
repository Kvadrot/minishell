/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:30:16 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/24 15:46:59 by ssuchane         ###   ########.fr       */
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
	t_cmd	*temp;
	char	*es;
	char	*ps;

	i = 0;
	cmd = NULL;
	temp = NULL;
	ps = minishell->input;
	es = minishell->input + ft_strlen(minishell->input);
	while (ps <= es)
	{
		cmd = parseredirs(cmd, &ps, es);
		if (cmd)
			cmd->sub_cmd = parseexec(&ps);
		else
		{
			cmd = parseexec(&ps);
			temp = parseredirs(cmd, &ps, es);
			if (temp)
				cmd = temp;
		}
		if (cmd)
		{
			handle_quotes_dollar(cmd->argv, minishell);
			minishell->commands[i] = cmd;
			minishell->number_of_commands++;
		}
		peek(&ps, "|");
		ps++;
		i++;
	}
}

// t_cmd	*parseline(char **ps, char *es)
// {
// 	t_cmd	*cmd;

// 	cmd = parsepipe(ps, es);
// 	while (peek(ps, es, "&"))
// 	{
// 		gettoken(ps, es, 0, 0);
// 		cmd = backcmd(cmd);
// 	}
// 	if (peek(ps, es, ";"))
// 	{
// 		gettoken(ps, es, 0, 0);
// 		cmd = listcmd(cmd, parseline(ps, es));
// 	}
// 	return (cmd);
// }

// t_cmd	*parsepipe(char **ps, char *es)
// {
// 	t_cmd	*cmd;

// 	cmd = parseexec(ps, es);
// 	if (peek(ps, es, "|"))
// 	{
// 		gettoken(ps, es, 0, 0);
// 		cmd = pipecmd(cmd, parsepipe(ps, es));
// 	}
// 	return (cmd);
// }

/*
* 1 function look for block to parse
* 2 function creaate execcmd struct
* 3 function look for redirections and add previous execcmd as subcmd if redirection is found
* 4 while there is no end of block pipe expander or semicolon,
	look for next string to put to argv
* 4a add string to argv
* 4b check if there is too many args in argv
* 4c look for redirections and add previous execcmd as subcmd if redirection is found
* 5 function put 0 terminate argv and eargv tables
* 6 return general cmd struct independly of type
*/

char	*substring(const char *start, const char *end)
{
	size_t	length;
	char	*result;

	// Calculate the length of the substring
	length = end - start;
	// Allocate memory for the substring (+1 for null terminator)
	result = malloc(length + 1);
	if (result == NULL)
	{
		// Memory allocation failed
		return (NULL);
	}
	// Copy the substring between start and end
	strncpy(result, start, length);
	// Null-terminate the new string
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

// t_cmd	*parseblock(char **ps, char *es)
// {
// 	t_cmd	*cmd;

// 	if (!peek(ps, es, "("))
// 		panic("parseblock");
// 	gettoken(ps, es, 0, 0);
// 	cmd = parseline(ps, es);
// 	if (!peek(ps, es, ")"))
// 		panic("syntax - missing )");
// 	gettoken(ps, es, 0, 0);
// 	cmd = parseredirs(cmd, ps, es);
// 	return (cmd);
// }

t_cmd	*parseredirs(t_cmd *cmd, char **ps, char *es)
{
	int tok;
	char *q, *eq;

	while (peek(ps, es, "<>")) /*  szuka czy jest < lub > w stringu */
	{
		tok = gettoken(ps, es, 0, 0);
		file = get_word(ps);
		if (file == NULL)
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
	return (ret_cmd);
}
