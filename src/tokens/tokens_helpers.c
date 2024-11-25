/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:41:52 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/11/24 17:48:54 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	skip_quotes(const char *input, int i)
{
	char	quote;

	quote = input[i];
	i++;
	while (input[i] && input[i] != quote)
		i++;
	if (input[i])
		i++;
	return (i);
}

static int	process_word(const char *input, int i)
{
	while (input[i])
	{
		if (input[i] == '\"' || input[i] == '\'')
			return (skip_quotes(input, i));
		else if (ft_is_whitespace(input[i]) || ft_strchr("><|", input[i]))
			break ;
		i++;
	}
	return (i);
}

static t_tokens	*allocate_token_value(t_tokens *token, const char *input,
		int length)
{
	token->value = (char *)malloc(length + 1);
	if (!token->value)
		return (NULL);
	ft_strncpy(token->value, (char *)input, length);
	token->value[length] = '\0';
	return (token);
}

t_tokens	*update_token_word(t_tokens *token, char *input, int type)
{
	int	i;

	i = 0;
	i = process_word(input, i);
	if (!allocate_token_value(token, input, i))
		return (NULL);
	token->type = type;
	return (token);
}

t_tokens	*update_token(t_tokens *token, char *input, int type)
{
	if (token->value)
		free(token->value);
	token->value = (char *)malloc(ft_strlen(input) + 1);
	if (!token->value)
		return (NULL);
	ft_strncpy(token->value, input, ft_strlen(input));
	token->value[ft_strlen(input)] = '\0';
	token->type = type;
	return (token);
}
