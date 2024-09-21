/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:27:53 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/21 22:00:36 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
** Returns 1 if the character is in the toks string, 0 otherwise.
*/
int	peek(char **ps, char *es, char *toks)
{
	char	*s;

	s = *ps;
	while (s < es && strchr(" \t\r\n\v", *s))
		s++;
	*ps = s;
	return (*s && strchr(toks, *s));
}

void	ft_skip_whitespace(char **s)
{
	while (*s && **s && ft_strchr(" \t\r\n\v", **s))
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

char	*get_block(char **ps)
{
	char	*ret;
	char	*s;
	size_t	length;
	char	*start;
	char	quote;

	s = *ps;
	quote = *s;
	length = 0;
	start = s;
	s++;
	while (s && *s && *s != quote)
		s++;
	length = s - start + 1;
	ret = malloc(length + 1);
	if (ret == NULL)
		return (NULL);
	strncpy(ret, start, length);
	ret[length] = '\0';
	if (quote)
		s++;
	*ps = s;
	return (ret);
}

char	*get_word(char **ps)
{
	char	*ret;
	char	*s;
	size_t	length;
	char	*start;

	s = *ps;
	length = 0;
	start = s;
	while (s && *s && !ft_iswhitespace(*s))
		s++;
	length = s - start;
	ret = malloc(length + 1);
	if (ret == NULL)
		return (NULL);
	strncpy(ret, start, length);
	ret[length] = '\0';
	*ps = s;
	return (ret);
}

/*
 * Returns a string from the input string.
 * The string can be a block or a word.
 * A block is a string between two quotes.
 * A word is a string between two whitespaces.
 */
char	*get_string(char **ps)
{
	if (*ps == NULL || **ps == '\0')
		return (NULL);
	ft_skip_whitespace(ps);
	if (**ps == '"' || **ps == '\'')
		return (get_block(ps));
	else
		return (get_word(ps));
}
