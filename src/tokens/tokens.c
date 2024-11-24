/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 19:44:17 by ssuchane          #+#    #+#             */
/*   Updated: 2024/11/24 17:42:23 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_tokens	*get_token(char *input)
{
	t_tokens	*token;

	token = (t_tokens *)malloc(sizeof(t_tokens));
	if (!token)
		return (NULL);
	token->value = NULL;
	token->type = 0;
	token->next = NULL;
	if (*input)
	{
		if (!ft_strncmp(">>", input, 2))
			return (update_token(token, ">>", T_DGREAT));
		else if (!ft_strncmp("<<", input, 2))
			return (update_token(token, "<<", T_DLESS));
		else if (*input == '>')
			return (update_token(token, ">", T_GREAT));
		else if (*input == '<')
			return (update_token(token, "<", T_LESS));
		else if (*input == '|')
			return (update_token(token, "|", T_PIPE));
		else
			return (update_token_word(token, input, T_WORD));
	}
	free(token);
	return (NULL);
}

void	append_token(t_tokens **tokens, t_tokens *new_token)
{
	t_tokens	*current;

	if (*tokens == NULL)
	{
		new_token->prev = NULL;
		*tokens = new_token;
	}
	else
	{
		current = *tokens;
		while (current->next != NULL)
			current = current->next;
		current->next = new_token;
		new_token->prev = current;
	}
	new_token->next = NULL;
}

int	ft_is_only_whitespace(char *str)
{
	while (*str)
	{
		if (!ft_is_whitespace(*str))
			return (0);
		str++;
	}
	return (1);
}

// pontentially catch syntax errors and return error message
// how to return error we want?

// check for pipe at the beginning and at the end
// check for > and >> at the end
// check for < << at the beginning
// Return: Eerror_code:
// 200 -> OK
// -404 -> KO
int	validate_tokens(t_tokens *tokens)
{
	t_tokens	*current;

	if (!tokens)
		return (200);
	current = tokens;
	while (current && current->next)
	{
		if (current->type != 0 && current->next->type != 0)
		{
			ft_printf("Mini_hell: syntax error near unexpected token `%s'\n",
				current->next->value);
			return (-404);
		}
		current = current->next;
	}
	if (current->type > 0)
	{
		printf("Mini_hell: syntax error near unexpected token `%s'\n",
			current->value);
		return (-405);
	}
	return (200);
}

int	init_tokens(t_data **minishell)
{
	char		*string;
	t_tokens	*token;

	token = NULL;
	string = (*minishell)->input;
	if (!string || ft_strlen(string) == 0 || ft_is_only_whitespace(string))
		return (200);
	while (string && *string)
	{
		ft_skip_whitespace(&string);
		token = get_token(string);
		if (token)
		{
			append_token(&((*minishell)->tokens), token);
			string += ft_strlen(token->value);
		}
	}
	return (200);
}
