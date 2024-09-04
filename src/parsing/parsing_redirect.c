/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:26:01 by ssuchane          #+#    #+#             */
/*   Updated: 2024/09/04 15:19:11 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../inc/minishell.h"

// t_command	*init_command(void)
// {
// 	t_command	*cmd;

// 	cmd = (t_command *)malloc(sizeof(t_command));
// 	cmd->args = (char **)malloc(MAX_ARGS * sizeof(char *));
// 	cmd->args[0] = NULL; // Initialize the args array to NULL
// 	cmd->input_redirection = NULL;
// 	cmd->output_redirection = NULL;
// 	cmd->heredoc_delimiter = NULL;
// 	cmd->output_append = NULL;
// 	cmd->pipe = 0;
// 	cmd->next = NULL;
// 	cmd->prev = NULL;
// 	return (cmd);
// }

// // Helper function to link the new command to the command list
// void	link_command(t_command **head, t_command *current)
// {
// 	t_command	*tmp;

// 	if (*head == NULL)
// 	{
// 		*head = current;
// 	}
// 	else
// 	{
// 		tmp = *head;
// 		while (tmp->next)
// 			tmp = tmp->next;
// 		tmp->next = current;
// 		current->prev = tmp;
// 	}
// 	char *temp = *current->args[0];
// 	ft_peintf("%s\n is added to command", temp);
// }

// // Helper function to handle redirection tokens (T_GREAT, T_DGREAT)
// t_command	*handle_output_redirection(t_tokens **token)
// {
// 	t_command	*current;

// 	current = init_command();
// 	if ((*token)->type == T_GREAT)
// 	{
// 		*token = (*token)->next;
// 		if (*token && (*token)->type == T_WORD)
// 		{
// 			current->output_redirection = strdup((*token)->value);
// 		}
// 	}
// 	else if ((*token)->type == T_DGREAT)
// 	{
// 		*token = (*token)->next;
// 		if (*token && (*token)->type == T_WORD)
// 		{
// 			current->output_append = strdup((*token)->value);
// 		}
// 	}
// 	return (current);
// }

// Helper function to handle input redirection (T_LESS) and heredoc (T_DLESS)
// t_command	*handle_input_redirection(t_tokens **token)
// {
// 	t_command	*current;

// 	current = init_command();
// 	if ((*token)->type == T_LESS)
// 	{
// 		*token = (*token)->next;
// 		if (*token && (*token)->type == T_WORD)
// 		{
// 			current->input_redirection = strdup((*token)->value);
// 		}
// 	}
// 	else if ((*token)->type == T_DLESS)
// 	{
// 		*token = (*token)->next;
// 		if (*token && (*token)->type == T_WORD)
// 		{
// 			current->heredoc_delimiter = strdup((*token)->value);
// 		}
// 	}
// 	return (current);
// }

// Function to parse the tokens and construct the command list
// t_command	*parse_tokens(t_tokens *tokens)
// {
// 	t_command	*head;
// 	t_tokens	*token;
// 	t_command	*current;

// 	head = NULL;
// 	token = tokens;
// 	while (token)
// 	{
// 		current = NULL;
// 		if (token->type == T_GREAT || token->type == T_DGREAT)
// 		{
// 			current = handle_output_redirection(&token);
// 		}
// 		// else if (token->type == T_WORD)
// 		// {
// 		// 	current = init_command();
// 		// 	handle_word_token(current, &token);
// 		// }
// 		else if (token->type == T_LESS || token->type == T_DLESS)
// 		{
// 			current = handle_input_redirection(&token);
// 		}
// 		else if (token->type == T_PIPE)
// 		{
// 			current = handle_pipe(current);
// 			token = token->next;
// 			continue ; // Continue to avoid linking a NULL command
// 		}
// 		// Link the command to the list
// 		if (current != NULL)
// 		{
// 			link_command(&head, current);
// 		}
// 		// Move to the next token
// 		token = token->next;
// 	}
// 	print_commands(head);
// 	return (head);
// }
