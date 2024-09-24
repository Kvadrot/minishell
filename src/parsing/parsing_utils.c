/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:27:53 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/19 18:21:57 by ssuchane         ###   ########.fr       */
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

char	*ft_substring(const char *start, const char *end)
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
