/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_semi_tested.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 19:44:17 by ssuchane          #+#    #+#             */
/*   Updated: 2024/11/19 18:01:37 by itykhono         ###   ########.fr       */
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
	ft_strncpy(token->value, input, i);
	token->value[i] = '\0';
	token->type = type;
	return (token);
}

t_tokens *update_token(t_tokens *token, char *input, int type)
{
    // Free existing value if already allocated
    if (token->value)
        free(token->value);

    // Allocate memory dynamically based on the input length
    token->value = (char *)malloc(ft_strlen(input) + 1); // +1 for null terminator
    if (!token->value)
        return NULL; // Handle memory allocation failure

    // Copy input to the token's value
    ft_strncpy(token->value, input, ft_strlen(input));
    token->value[ft_strlen(input)] = '\0'; // Null-terminate the string

    // Update the token type
    token->type = type;

    return token;
}

t_tokens *get_token(char *input)
{
    t_tokens *token;

    // Allocate memory for the token struct
    token = (t_tokens *)malloc(sizeof(t_tokens));
    if (!token)
        return NULL; // Handle memory allocation failure

    // Initialize the token fields
    token->value = NULL;
    token->type = 0;
    token->next = NULL;

    // Update the token based on input
    if (*input)
    {
        if (!ft_strncmp(">>", input, 2))
            return update_token(token, ">>", T_DGREAT);
        else if (!ft_strncmp("<<", input, 2))
            return update_token(token, "<<", T_DLESS);
        else if (*input == '>')
            return update_token(token, ">", T_GREAT);
        else if (*input == '<')
            return update_token(token, "<", T_LESS);
        else if (*input == '|')
            return update_token(token, "|", T_PIPE);
        else
            return update_token_word(token, input, T_WORD); // Assuming `update_token_word` is defined
    }

    // Free the token if no valid input was found
    free(token);
    return NULL;
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

	current = tokens;
	while (current && current->next)
	{
		if (current->type != 0 && current->next->type != 0)
		{
			// need actual error code to handle it
			ft_printf("Mini_hell: syntax error near unexpected token `%s' - printed by: validate_tokens\n",
				current->next->value);
			return (-404);
		}
		current = current->next;
	}
	if (current->type > 0)
	{
		printf("Mini_hell: syntax error near unexpected token `%s' - printed by: validate_tokens\n",
				current->value);
		return (-405); 
	}
	return (200);
}

int	init_tokens(t_data *minishell)
{
	char		*string;
	t_tokens	*token;

	token = NULL;
	string = minishell->input;
	if (!string)
		return (200);
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
	return (200);
}