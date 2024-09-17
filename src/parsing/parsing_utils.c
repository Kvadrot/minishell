/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:27:53 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/17 19:20:53 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	peek(char **ps, char *es, char *toks)
{
	char	*s;

	s = *ps;
	while (s < es && strchr(" \t\r\n\v", *s))
		s++;
	*ps = s;
	return (*s && strchr(toks, *s));
}

void	skip_whitespace(char **s, char *es)
{
	while (*s < es && strchr(" \t\r\n\v", **s))
		(*s)++;
}

void	skip_trailing_whitespace(char **s, char *es)
{
	while (*s < es && strchr(" \t\r\n\v", **s))
		(*s)++;
}

void	advance_to_end_of_token(char **s, char *es)
{
	while (*s < es && !strchr(" \t\r\n\v", **s) && !strchr("<|>&;()", **s))
		(*s)++;
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
	else if (peek(&s, es, "|();&"))
		s++;
	else if (*s == '>')
	{
		s++;
		if (*s == '>')
		{
			ret = '+';
			s++;
		}
	}
	else if (*s == '<')
	{
		s++;
		if (*s == '<')
		{
			ret = '-';
			s++;
			*ps = s;
		}
	}
	else
		ret = 'a';
	advance_to_end_of_token(&s, es);
	if (eq)
		*eq = s;
	skip_trailing_whitespace(&s, es);
	*ps = s;
	return (ret);
}
