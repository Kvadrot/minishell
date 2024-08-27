/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_semi_tested.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 19:44:17 by ssuchane          #+#    #+#             */
/*   Updated: 2024/08/25 16:38:35 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_tokens	*update_token_word(t_tokens *token, char *input, int type)
{
	int		i;
	char	quote;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\"' || input[i] == '\'')
		{
			quote = input[i];
			i++;
			while (input[i] && input[i] != quote)
				i++;
			if (input[i])
				i++;
		}
		else if (ft_is_whitespace(input[i]))
			break ;
		else
			i++;
	}
	token->value = (char *)malloc(i + 1);
	strncpy(token->value, input, i);
	token->value[i] = '\0';
	token->type = type;
	return (token);
}

t_tokens	*update_token(t_tokens *token, char *input, int type)
{
	token->value = (char *)malloc(3);
	ft_strncpy(token->value, input, strlen(input));
	token->type = type;
	return (token);
}

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
	return (NULL);
}

void	append_token(t_tokens **tokens, t_tokens *new_token)
{
	t_tokens	*current;

	if (*tokens == NULL)
		*tokens = new_token;
	else
	{
		current = *tokens;
		while (current->next != NULL)
			current = current->next;
		current->next = new_token;
	}
	new_token->next = NULL;
}

void	init_tokens(t_data *minishell)
{
	char		*string;
	t_tokens	*token;

	token = NULL;
	string = minishell->input;
	while (string && *string)
	{
		ft_skip_whitespace(&string);
		token = get_token(string);
		if (token)
		{
			append_token(&minishell->tokens, token);
			string += ft_strlen(token->value);
		}
	}
}

// int	main(int ac, char **av)
// {
// 	t_data minishell;
// 	minishell.tokens = NULL;

// 	(void)ac;
// 	minishell.input = av[1];
// 	tokens(&minishell);

// 	while (minishell.tokens != NULL)
// 	{
// 		printf("%s = %d\n", minishell.tokens->value, minishell.tokens->type);
// 		minishell.tokens = minishell.tokens->next;
// 	}
// 	return (0);
// }
