/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:26:01 by ssuchane          #+#    #+#             */
/*   Updated: 2024/08/30 17:07:52 by ssuchane         ###   ########.fr       */
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

t_command	*create_command_node(void);
void		handle_redirection(t_command **cmd, t_tokens **token);
void		add_argument(t_command *cmd, const char *arg);
void		handle_words(t_command *cmd, t_tokens **tokens);
void		handle_input_redirection(t_command **cmd, t_tokens **token);
void		handle_pipe(t_command **cmd, t_command **prev, t_tokens **token);
void		print_commands(t_command *cmd);

// Main parsing function
t_command	*parse_tokens(t_tokens *tokens)
{
	t_command	*head;
	t_command	*current;
	t_command	*previous;
	t_tokens	*token;

	head = NULL;
	current = NULL;
	previous = NULL;
	token = tokens;
	while (token)
	{
		if (token->type == T_GREAT || token->type == T_DGREAT)
		{
			handle_redirection(&current, &token);
		}
		else if (token->type == T_WORD)
		{
			handle_words(&current, &token);
		}
		else if (token->type == T_LESS || token->type == T_DLESS)
		{
			handle_input_redirection(&current, &token);
		}
		else if (token->type == T_PIPE)
		{
			handle_pipe(&current, &previous, &token);
		}
		else
		{
			token = token->next; // Skip unknown tokens
		}
		if (current && head == NULL)
		{
			head = current; // Initialize the head if it's the first command
		}
	}
	if (current != NULL && previous != NULL)
	{
		previous->next = current;
		current->prev = previous;
	}
	print_commands(head);
	return (head);
}

// Helper function implementations
t_command	*create_command_node(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	memset(cmd, 0, sizeof(t_command));
	return (cmd);
}

void	handle_redirection(t_command **cmd, t_tokens **token)
{
	if (*cmd == NULL)
	{
		*cmd = create_command_node();
	}
	if ((*token)->type == T_GREAT)
	{
		(*cmd)->output_redirection = strdup((*token)->next->value);
		*token = (*token)->next; // Skip the next token
	}
	else if ((*token)->type == T_DGREAT)
	{
		(*cmd)->output_append = strdup((*token)->next->value);
		*token = (*token)->next; // Skip the next token
	}
	*token = (*token)->next; // Move to the next token
}

void	add_argument(t_command *cmd, const char *arg)
{
	int	count;

	count = 0;
	// Count existing arguments
	if (cmd->args)
	{
		while (cmd->args[count])
		{
			count++;
		}
	}
	// Allocate space for the new argument and NULL terminator
	cmd->args = realloc(cmd->args, (count + 2) * sizeof(char *));
	if (!cmd->args)
	{
		perror("realloc");
		exit(EXIT_FAILURE);
	}
	// Add the new argument
	cmd->args[count] = strdup(arg);
	if (!cmd->args[count])
	{
		perror("strdup");
		exit(EXIT_FAILURE);
	}
	// We do not add NULL here; it's handled in parse_word_tokens
}

void	handle_words(t_command *cmd, t_tokens **tokens)
{
	int	count;

	// Initialize args array
	cmd->args = NULL;
	// Add arguments while encountering T_WORD tokens
	while (*tokens && (*tokens)->type == T_WORD)
	{
		add_argument(cmd, (*tokens)->value);
		*tokens = (*tokens)->next;
	}
	// Null-terminate the args array
	if (cmd->args)
	{
		count = 0;
		while (cmd->args[count])
		{
			count++;
		}
		cmd->args = realloc(cmd->args, (count + 1) * sizeof(char *));
		if (!cmd->args)
		{
			perror("realloc");
			exit(EXIT_FAILURE);
		}
		cmd->args[count] = NULL; // Ensure the array is NULL-terminated
	}
}

void	handle_input_redirection(t_command **cmd, t_tokens **token)
{
	if (*cmd == NULL)
	{
		*cmd = create_command_node();
	}
	if ((*token)->type == T_LESS)
	{
		(*cmd)->input_redirection = strdup((*token)->next->value);
		*token = (*token)->next; // Skip the next token
	}
	else if ((*token)->type == T_DLESS)
	{
		(*cmd)->heredoc_delimiter = strdup((*token)->next->value);
		*token = (*token)->next; // Skip the next token
	}
	*token = (*token)->next; // Move to the next token
}

void	handle_pipe(t_command **cmd, t_command **prev, t_tokens **token)
{
	if (*cmd == NULL)
	{
		*cmd = create_command_node();
	}
	(*cmd)->pipe = 1;
	if (*prev != NULL)
	{
		(*prev)->next = *cmd;
		(*cmd)->prev = *prev;
	}
	*prev = *cmd;
	*cmd = NULL;
	*token = (*token)->next; // Move to the next token
}

void	print_commands(t_command *cmd)
{
	while (cmd)
	{
		printf("Command:\n");
		if (cmd->args)
		{
			printf("  Args: ");
			for (int i = 0; cmd->args && cmd->args[i]; i++)
			{
				printf("%s ", cmd->args[i]);
			}
			printf("\n");
		}
		if (cmd->input_redirection)
			printf("  Input Redirection: %s\n", cmd->input_redirection);
		if (cmd->output_redirection)
			printf("  Output Redirection: %s\n", cmd->output_redirection);
		if (cmd->output_append)
			printf("  Output Append: %s\n", cmd->output_append);
		if (cmd->heredoc_delimiter)
			printf("  Heredoc Delimiter: %s\n", cmd->heredoc_delimiter);
		if (cmd->pipe == 1)
			printf("  Pipe: %d\n", cmd->pipe);
		cmd = cmd->next;
	}
}