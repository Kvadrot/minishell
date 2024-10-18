#include "../../inc/minishell.h"

t_tokens	*init_new_node_token(char *value)
{
	t_tokens	*new_node;

	new_node = (t_tokens *)malloc(sizeof(t_tokens));
	if (!new_node)
		return (NULL);
	new_node->type = NULL;
	new_node->value = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	init_new_node_token_end(t_tokens **head, t_token_type type, char *value)
{
	t_tokens	*new_node;
	t_tokens	*current;

	new_node = init_new_node_token(value);
	if (!new_node)
		return ;
	if (*head == NULL)
		*head = new_node;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}

void	ft_skip_whitespace(char *s)
{
	if (*s)
	{
		while (*s == '\t' || *s == '\n' || *s == '\v'
			|| *s == '\f' || *s == '\r' || *s == ' ')
			*s++;
	}
}

bool	ft_is_whitespace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (true);
	return (false);
}

bool	ft_is_operator(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (true);
	return (false);
}

t_tokens	ft_get_type(char *input)
{
	t_tokens	*token;

	token = (t_tokens *)malloc(sizeof(t_tokens));
	if (*s)
	{
		if (!ft_strncmp(">>", s, 2))
			return (update_token(token, ">>", T_DGREAT));
		else if (!ft_strncmp("<<", s, 2))
			return (update_token(token, "<<", T_DLESS));
		else if (*s == '>')
			return (update_token(token, '>', T_GREAT));
		else if (*s == '<')
			return (update_token(token, '<', T_LESS));
		else if (type == '|')
			return (update_token(token, '|', T_PIPE));
		else
			return (update_token_word(token, input, T_WORD));
	}
}

t_tokens	update_token_word(t_tokens *token, char *input, int type)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (ft_is_whitespace(string[i]))
			break ;
		i++;
	}
	ft_strncpy(tokens->value, input, i);
	token->type = type;
	return (token);
}

t_tokens	update_token(t_tokens *token, char *input, int type)
{
	ft_strncpy(tokens->value, input, sizeof(input));
	token->type = type;
	return (token);
}

static t_tokens	*get_tokens(char *input, t_data *minishell)
{
	t_tokens	*tokens;
	int			error;
	int			start;
	int			i;
	int			type;
	char		*value;

	tokens = NULL;
	error = 0;
	i = 0;
	type = 6;
	while (input[i])
	{
		start = i;
		if (input[i] == '\"')
		{
			i++;
			while (input[i] != '\"')
			{
				if (input[i] == '\"')
				{
					type = T_WORD;
					value = ft_substr(input, start, i - start);
					// -----  TO DO  -----
					// if (!value)
						// error handling, tokens could be NULL
					init_new_node_token_end(tokens, type, value);
					break ;
				}
				i++;
			}
		}
		else if (input[i] == '\'')
		{
			while (input[i] != '\'')
			{
				if (input[i] == '\'')
				{
					type = T_WORD;
					value = ft_substr(input, start, i - start);
					// -----  TO DO  -----
					// if (!value)
						// error handling, tokens could be NULL
					init_new_node_token_end(tokens, type, value);
					break ;
				}
				i++;
			}
		}
		else if (input[i] == ft_is_operator(input[i])) // operator = >>, <<, >, <, |
		{
			type = ft_get_type(input[i], &i);
			if (type == 6)
				// error handling
			init_new_node_token_end(tokens, type, NULL);
			i++;
		}
		else
		{
			start = i;
			while (input[i] && !ft_is_whitespace(input[i]) && !is_operator(&input[i]))
			{
				start = i;
				i++;
			}
			type = T_WORD;
			value = ft_substr(input, start, i - start);
			init_new_node_token_end(tokens, type, value);
		}
		ft_skip_whitespace(&input[i]); // handle incrementing based on how many characters we skipped
		i++;

	}
}

// funkcja tworzy gotowa liste tokenow z inputu
// zwraca liste tokenow

t_tokens	*convert_input_to_tokens(t_data *minishell)
{
	char		*input;
	t_tokens	*tokens;

	input = minishell->input;
	tokens = get_tokens(input, minishell);
	free(input);
	minishell->input = NULL;
	return (tokens);
}
