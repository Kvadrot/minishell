/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:30:16 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/19 19:17:15 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	handle_greater_than(char **s)
{
	int	ret;

	ret = '>';
	(*s)++;
	if (**s == '>')
	{
		ret = '+';
		(*s)++;
	}
	return (ret);
}

static int	handle_less_than(char **s, char **ps)
{
	int	ret;

	ret = '<';
	(*s)++;
	if (**s == '<')
	{
		ret = '-';
		(*s)++;
	}
	*ps = *s;
	return (ret);
}

static int	handle_normal_token(char **s, char *es, char **eq)
{
	advance_to_end_of_token(s, es);
	if (eq)
		*eq = *s;
	return ('a');
}

int	gettoken(char **ps, char *es, char **q, char **eq)
{
	char	*s;
	int		ret;

	s = *ps;
	skip_whitespace(&s, es);
	if (q)
		*q = s;
	ret = *s;
	if (*s == 0)
		return (0);
	if (peek(&s, es, "|();&"))
		s++;
	else if (*s == '>')
		ret = handle_greater_than(&s);
	else if (*s == '<')
		ret = handle_less_than(&s, ps);
	else
		ret = handle_normal_token(&s, es, eq);
	skip_trailing_whitespace(&s, es);
	*ps = s;
	return (ret);
}

void	handle_tokens(t_execcmd *cmd, t_cmd **ret, char **ps, char *es)
{
	int		tok;
	int		argc;
	char	*q;
	char	*eq;

	argc = 0;
	init_cmd_args(cmd);
	while (!peek(ps, es, "|)&;"))
	{
		tok = gettoken(ps, es, &q, &eq);
		if (tok == 0)
			break ;
		if (tok != 'a')
			panic("syntax");
		add_argument(cmd, q, eq, &argc);
		*ret = parseredirs(*ret, ps, es);
	}
}
