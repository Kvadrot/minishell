#include "../../inc/minishell.h"

t_tokens	*init_new_node_token(char *value)
{
	t_tokens	*new_node;

	new_node = (t_tokens *)malloc(sizeof(t_tokens));
	if (!new_node)
		return (NULL);
	// we need a function that will extract the type of token
	//new_node->type = ;
	// we need a function that will extract the value of token
	//new_node->value = ;
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



//MDShell >
// "Hello  42"""



static t_tokens	*init_tokens(char *input, t_data *minishell)
{
	t_tokens	*tokens;
	int			error;

	tokens = NULL;
	error = 0;
	while (*input)
	{
	//	if (*input == )
			

	}
}



// Everything inbetween " " is one word
// Everything inbetween ' ' is one word
// Everything inbetween ( ) is one word









// funkcja tworzy gotowa liste tokenow z inputu
// zwraca liste tokenow

t_tokens	*convert_input_to_tokens(t_data *minishell)
{
	char		*input;
	t_tokens	*tokens;

	input = minishell->input;
	tokens = init_token(input, minishell);
	free(input);
	minishell->input = NULL;
	return (tokens);
}
