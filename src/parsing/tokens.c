/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:30:16 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/21 21:58:17 by gbuczyns         ###   ########.fr       */
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
	ft_skip_whitespace(&s);
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
	ft_skip_whitespace(&s);
	*ps = s;
	return (ret);
}

void	handle_tokens(t_cmd *cmd, t_cmd **ret, char **ps, char *es)
{
	char	*s;

	while (!peek(ps, es, "|)&;") && **ps != 0)
	{
		s = get_string(ps);
		cmd->argv = ft_append_argv(cmd->argv, s);
		*ret = parseredirs(*ret, ps, es);
	}
}
