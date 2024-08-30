/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_semi_tested.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 19:44:17 by ssuchane          #+#    #+#             */
/*   Updated: 2024/08/30 13:59:47 by ssuchane         ###   ########.fr       */
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
		{
			i++;
			if (ft_strchr("><|", input[i]))
				break ;
		}
	}
	token->value = (char *)malloc(i + 1);
	// if (!token->value)
		// return not sufficient memory error
	strncpy(token->value, input, i);
	token->value[i] = '\0';
	token->type = type;
	return (token);
}

t_tokens	*update_token(t_tokens *token, char *input, int type)
{
	token->value = (char *)malloc(3);
	// if (!token->value)
		// return not sufficient memory error
	ft_strncpy(token->value, input, ft_strlen(input));
	token->value[ft_strlen(input)] = '\0';
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

// pontentially catch syntax errors and return error message
// how to return error we want?

// check for pipe at the beginning and at the end
// check for > and >> at the end
// check for < << at the beginning 
int	validate_tokens(t_tokens *tokens)
{
	t_tokens	*current;

	current = tokens;
	while (current && current->next)
	{
		if (current->type >= 1 && current->type <= 5 && current->next->type != 0)
		{
			// need actual error code to handle it
			printf("bash: syntax error near unexpected token `%s'\n",
				current->next->value);
			return (1);
		}
		current = current->next;
	}
	return (0);
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

// abcd 42
// "Abcd 42" = 0

// ' Abcd 42 '
// ' Abcd 42 ' = 0

// "$Arg 1"42'some_text' >> <
// "$Arg 1"42'some_text' = 0

// < < '<<< >> '"ARG">
// <��U = 1
// <<��U = 3
// '"ARG"> = 0