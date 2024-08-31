/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:26:01 by ssuchane          #+#    #+#             */
/*   Updated: 2024/08/31 20:32:39 by ssuchane         ###   ########.fr       */
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

t_command	*new_command(void);
t_command	*handle_redirection_token(t_tokens **tokens);
void		handle_word_token(t_command *cmd, t_tokens **tokens);
void		handle_pipe_token(t_command *cmd, t_command **cmd_list);
t_command	*parse_tokens(t_tokens *tokens);
void		free_command_args(t_command *cmd);
void		free_command_list(t_command *cmd);
void		print_command(t_command *cmd);

// Function to create a new command node
t_command	*new_command(void)
{
	t_command	*cmd;

	cmd = (t_command *)malloc(sizeof(t_command));
	if (!cmd)
	{
		perror("Failed to allocate memory for command");
		exit(EXIT_FAILURE);
	}
	cmd->args = NULL;
	cmd->input_redirection = NULL;
	cmd->output_redirection = NULL;
	cmd->heredoc_delimiter = NULL;
	cmd->output_append = NULL;
	cmd->pipe = 0;
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);
}

// Function to handle redirection tokens and return the updated command node
t_command	*handle_redirection_token(t_tokens **tokens)
{
	t_command	*cmd;

	cmd = new_command();
	if (*tokens && ((*tokens)->type == T_GREAT || (*tokens)->type == T_DGREAT))
	{
		if ((*tokens)->type == T_GREAT)
		{
			cmd->output_redirection = strdup((*tokens)->next->value);
		}
		else if ((*tokens)->type == T_DGREAT)
		{
			cmd->output_append = strdup((*tokens)->next->value);
		}
		*tokens = (*tokens)->next->next; // Move past redirection tokens
	}
	else if (*tokens && ((*tokens)->type == T_LESS
			|| (*tokens)->type == T_DLESS))
	{
		if ((*tokens)->type == T_LESS)
		{
			cmd->input_redirection = strdup((*tokens)->next->value);
		}
		else if ((*tokens)->type == T_DLESS)
		{
			cmd->heredoc_delimiter = strdup((*tokens)->next->value);
		}
		*tokens = (*tokens)->next->next; // Move past redirection tokens
	}
	return (cmd);
}

// Function to handle T_WORD tokens and build the args array in t_command
void	handle_word_token(t_command *cmd, t_tokens **tokens)
{
	int	num_args;

	num_args = 0;
	// Traverse the tokens and add T_WORD tokens to the command args
	while (*tokens && (*tokens)->type == T_WORD)
	{
		cmd->args = realloc(cmd->args, sizeof(char *) * (num_args + 2));
		if (!cmd->args)
		{
			perror("Failed to reallocate memory for args");
			exit(EXIT_FAILURE);
		}
		cmd->args[num_args] = strdup((*tokens)->value);
		if (!cmd->args[num_args])
		{
			perror("Failed to duplicate string for args");
			exit(EXIT_FAILURE);
		}
		num_args++;
		*tokens = (*tokens)->next;
	}
	// Null-terminate the args array
	cmd->args[num_args] = NULL;
}

// Function to handle T_PIPE token
void	handle_pipe_token(t_command *cmd, t_command **cmd_list)
{
	cmd->pipe = 1;
	if (*cmd_list)
	{
		(*cmd_list)->next = cmd;
		cmd->prev = *cmd_list;
	}
	*cmd_list = cmd;
}

// Function to parse the list of tokens into a list of command nodes and return the head of the list
t_command	*parse_tokens(t_tokens *tokens)
{
	t_command	*cmd_list;
	t_command	*cmd_head;
	t_command	*cmd;

	cmd_list = NULL;
	cmd_head = NULL;
	while (tokens)
	{
		cmd = NULL;
		// Handle redirection tokens first
		if (tokens->type == T_GREAT || tokens->type == T_DGREAT
			|| tokens->type == T_LESS || tokens->type == T_DLESS)
		{
			cmd = handle_redirection_token(&tokens);
		}
		// Handle command and arguments (T_WORD)
		if (tokens && tokens->type == T_WORD)
		{
			if (cmd == NULL)
			{
				cmd = new_command();
			}
			handle_word_token(cmd, &tokens);
		}
		// Handle pipe (T_PIPE)
		if (tokens && tokens->type == T_PIPE)
		{
			if (cmd == NULL)
			{
				cmd = new_command();
			}
			handle_pipe_token(cmd, &cmd_list);
			tokens = tokens->next; // Move past the pipe token
		}
		else
		{
			if (cmd != NULL)
			{
				if (cmd_list)
				{
					cmd_list->next = cmd;
					cmd->prev = cmd_list;
				}
				cmd_list = cmd;
			}
		}
		// Set the head of the list if it's the first command
		if (!cmd_head && cmd)
		{
			cmd_head = cmd;
		}
	}
	print_command(cmd_head);
	return (cmd_head);
}

// Function to free the args array in a command
void	free_command_args(t_command *cmd)
{
	if (cmd->args)
	{
		for (int i = 0; cmd->args[i] != NULL; i++)
		{
			free(cmd->args[i]);
		}
		free(cmd->args);
	}
}

// Function to free the entire command list
void	free_command_list(t_command *cmd)
{
	t_command	*temp;

	while (cmd)
	{
		temp = cmd;
		cmd = cmd->next;
		free_command_args(temp);
		free(temp->input_redirection);
		free(temp->output_redirection);
		free(temp->heredoc_delimiter);
		free(temp->output_append);
		free(temp);
	}
}

// Function to print the command structure for verification
void	print_command(t_command *cmd)
{
	printf("Command:\n");
	if (cmd->args)
	{
		for (int i = 0; cmd->args[i] != NULL; i++)
		{
			printf("  Arg[%d]: %s\n", i, cmd->args[i]);
		}
	}
	if (cmd->input_redirection)
	{
		printf("  Input Redirection: %s\n", cmd->input_redirection);
	}
	if (cmd->output_redirection)
	{
		printf("  Output Redirection: %s\n", cmd->output_redirection);
	}
	if (cmd->output_append)
	{
		printf("  Output Append: %s\n", cmd->output_append);
	}
	if (cmd->heredoc_delimiter)
	{
		printf("  Heredoc Delimiter: %s\n", cmd->heredoc_delimiter);
	}
	if (cmd->pipe)
	{
		printf("  Pipe: %d\n", cmd->pipe);
	}
	printf("\n");
}
