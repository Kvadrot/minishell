/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:27:53 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/17 19:00:05 by ssuchane         ###   ########.fr       */
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

int	gettoken(char **ps, char *es, char **q, char **eq)
{
	char *s;
	int ret;

	s = *ps;
	while (s < es && strchr(" \t\r\n\v", *s))
		s++;
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

	while (s < es && !strchr(" \t\r\n\v", *s) && !strchr("<|>&;()", *s))
		s++;
	if (eq)
		*eq = s;

	while (s < es && strchr(" \t\r\n\v", *s))
		s++;
	*ps = s;
	return (ret);
}
