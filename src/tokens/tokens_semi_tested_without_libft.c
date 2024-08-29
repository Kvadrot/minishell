/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_semi_tested_without_libft.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 19:44:17 by ssuchane          #+#    #+#             */
/*   Updated: 2024/08/29 21:40:54 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// first two inputs always give wrong values

// in case of >>> or any other combination other than desired we should
// return an error -
// ------------------------------EXAMPLE------------------------------
// ssuchane@c3r13s3:~$ |>
// bash: syntax error near unexpected token `|'
// ssuchane@c3r13s3:~$ |<
// bash: syntax error near unexpected token `|'
// ssuchane@c3r13s3:~$ >><
// bash: syntax error near unexpected token `<'

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
		}
		else if (ft_is_whitespace(input[i]))
			break ;
		else
			i++;
	}
	token->value = (char *)malloc(i + 1);
	// if (!token->value)
	// return not sufficient memory error
	ft_strncpy(token->value, input, i);
	token->value[i] = '\0';
	token->type = type;
	return (token);
}

t_tokens	*update_token(t_tokens *token, char *input, int type)
{
	// updated from
	// token->value = (char *)malloc(3);
	token->value = (char *)malloc(ft_strlen(input) + 1);
	// if (!token->value)
	// return not sufficient memory error
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
		// added ft_strlen(input) >= X && // add handling to echo "dads test">> test.txt phrase -> should be splited
		// split tokens if there is no space between T_WORD and operator
		// echo tytyt"dads 'test' das">> test.txt
		// echo tytyt"dads 'test' das" 44444>> test.txt
		// echo tytyt"dads 'test' das" 44444 >> test.txt
		if (strlen(input) >= 2 && !strncmp(">>", input, 2))
			return (update_token(token, ">>", T_DGREAT));
		else if (strlen(input) >= 2 && !strncmp("<<", input, 2))
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
			string += strlen(token->value);
		}
	}
}

int	main(int ac, char **av)
{
	t_data	minishell;

	minishell.tokens = NULL;
	(void)ac;
	minishell.input = av[1];
	init_tokens(&minishell);
	if (validate_tokens(minishell.tokens) != 0)
		return (0);
	while (minishell.tokens != NULL)
	{
		printf("%s = %d\n", minishell.tokens->value, minishell.tokens->type);
		minishell.tokens = minishell.tokens->next;
	}
	return (0);
}

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