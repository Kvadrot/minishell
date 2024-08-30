/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:26:01 by ssuchane          #+#    #+#             */
/*   Updated: 2024/08/30 22:40:50 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_syntax(t_tokens *tokens)
{
	t_tokens	*current;
	t_tokens	*previous;

	current = tokens;
	previous = NULL;
	while (current)
	{
		if (current->type == T_PIPE)
		{
			if (!previous || previous->type == T_PIPE)
			{
				printf("minishell: syntax error near unexpected token `%s'\n",
					current->value);
				return (0);
			}
		}
		else if (current->type == T_GREAT || current->type == T_DGREAT
			|| current->type == T_LESS || current->type == T_DLESS)
		{
			if (!current->next || current->next->type == T_PIPE)
			{
				if (current->next)
					printf("minishell: syntax error near unexpected token `newline'\n");
				else
					printf("minishell: syntax error near unexpected token `newline'\n");
				return (0);
			}
		}
		previous = current;
		current = current->next;
	}
	if (previous && (previous->type == T_PIPE || previous->type == T_GREAT
			|| previous->type == T_DGREAT || previous->type == T_LESS
			|| previous->type == T_DLESS))
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (0);
	}
	return (1);
}

t_command	*init_command(void)
{
	t_command	*cmd;
	int	i;

	i = -1;
	cmd = (t_command *)malloc(sizeof(t_command));
	cmd->args = (char **)malloc(MAX_ARGS * sizeof(char *));
	while (++i > MAX_ARGS)
		cmd->args[i] = NULL;
	cmd->args[0] = NULL;
	cmd->input_redirection = NULL;
	cmd->output_redirection = NULL;
	cmd->heredoc_delimiter = NULL;
	cmd->output_append = NULL;
	cmd->pipe = 0;
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);
}

// Helper function to link the new command to the command list
void	link_command(t_command **head, t_command *current)
{
	t_command	*tmp;

	if (*head == NULL)
	{
		*head = current;
	}
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = current;
		current->prev = tmp;
	}
}

// Helper function to handle T_WORD tokens and populate the args array
void	handle_word_token(t_command *current, t_tokens *token)
{
	int	arg_count;

	arg_count = 0;
	while (token && token->type == T_WORD)
	{
		current->args[arg_count++] = strdup(token->value);
		token = token->next;
	}
	current->args[arg_count] = NULL;
}

// Helper function to handle redirection tokens (T_GREAT, T_DGREAT)
t_command	*handle_output_redirection(t_tokens **token)
{
	t_command	*current;

	current = init_command();
	if ((*token)->type == T_GREAT)
	{
		*token = (*token)->next;
		if (*token && (*token)->type == T_WORD)
		{
			current->output_redirection = strdup((*token)->value);
		}
	}
	else if ((*token)->type == T_DGREAT)
	{
		*token = (*token)->next;
		if (*token && (*token)->type == T_WORD)
		{
			current->output_append = strdup((*token)->value);
		}
	}
	return (current);
}

// Helper function to handle input redirection (T_LESS) and heredoc (T_DLESS)
t_command	*handle_input_redirection(t_tokens **token)
{
	t_command	*current;

	current = init_command();
	if ((*token)->type == T_LESS)
	{
		*token = (*token)->next;
		if (*token && (*token)->type == T_WORD)
		{
			current->input_redirection = strdup((*token)->value);
		}
	}
	else if ((*token)->type == T_DLESS)
	{
		*token = (*token)->next;
		if (*token && (*token)->type == T_WORD)
		{
			current->heredoc_delimiter = strdup((*token)->value);
		}
	}
	return (current);
}

// Helper function to link the current command with the previous one if a pipe is encountered
t_command	*handle_pipe(t_command *current)
{
	if (current)
		current->pipe = 1;
	return (NULL);
	// Return NULL to indicate a new command should be initialized
}

void	print_commands(t_command *command)
{
	int	i;

	while (command)
	{
		printf("Command:\n");
		printf("  Args: ");
		i = 0;
		if (command->args)
		{
			while (command->args[i])
			{
				printf("%s ", command->args[i]);
				i++;
			}
			printf("\n");
		}
		if (command->input_redirection)
			printf("  Input Redirection: %s\n", command->input_redirection);
		if (command->output_redirection)
			printf("  Output Redirection: %s\n", command->output_redirection);
		if (command->heredoc_delimiter)
			printf("  Heredoc Delimiter: %s\n", command->heredoc_delimiter);
		if (command->output_append)
			printf("  Output Append: %s\n", command->output_append);
		if (command->pipe)
			printf("  Pipe: Yes\n");
		command = command->next;
	}
}

void free_commands(t_command *command)
{
	t_command	*current;
	t_command	*next;

	current = command;
	while (current != NULL)
	{
		// Free args and its elements
		if (current->args != NULL)
		{
			for (int i = 0; i < MAX_ARGS; ++i)
			{
				if (current->args[i] != NULL)
				{
					free(current->args[i]);
				}
			}
			free(current->args);
		}
		// Free other allocated strings
		if (current->input_redirection != NULL)
		{
			free(current->input_redirection);
		}
		if (current->output_redirection != NULL)
		{
			free(current->output_redirection);
		}
		if (current->heredoc_delimiter != NULL)
		{
			free(current->heredoc_delimiter);
		}
		if (current->output_append != NULL)
		{
			free(current->output_append);
		}
		// Move to the next node
		next = current->next;
		// Free the current node
		free(current);
		// Move to the next node in the list
		current = next;
	}
}

// Function to parse the tokens and construct the command list
t_command	*parse_tokens(t_tokens *tokens)
{
	t_command	*head;
	t_tokens	*token;
	t_command	*current;

	head = NULL;
	token = tokens;
	while (token)
	{
		current = NULL;
		if (token->type == T_GREAT || token->type == T_DGREAT)
		{
			current = handle_output_redirection(&token);
		}
		else if (token->type == T_WORD)
		{
			current = init_command();
			handle_word_token(current, token);
		}
		else if (token->type == T_LESS || token->type == T_DLESS)
		{
			current = handle_input_redirection(&token);
		}
		else if (token->type == T_PIPE)
		{
			current = handle_pipe(current);
			token = token->next;
			continue ; // Continue to avoid linking a NULL command
		}
		// Link the command to the list
		if (current != NULL)
		{
			link_command(&head, current);
		}
		// Move to the next token
		token = token->next;
	}
	print_commands(head);
	return (head);
}
