/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:30:16 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/21 23:43:01 by gbuczyns         ###   ########.fr       */
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
	if (peek(&s, "|();&"))
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

void	get_argv(t_cmd *cmd, char **ps)
{
	while (!peek(ps, "<>|)&;") && **ps != 0)
		cmd->argv = ft_append_argv(cmd->argv, get_string(ps));
}
