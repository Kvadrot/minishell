/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:26:01 by ssuchane          #+#    #+#             */
/*   Updated: 2024/11/19 17:56:14 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


/** TODO: ft_scroll_redir_list_to_last
* @brief: returns last node from t_redir * list
//=======================================================================//
* @HOW_IT_works: simply
//=======================================================================//
* @returns: t_redir * - obj t_redir || NULL
*/
t_redir *ft_scroll_redir_list_to_last(t_redir *redir_list_head)
{
	t_redir *temp;

	temp = NULL;
	if (!redir_list_head)
		return (NULL);
	temp = redir_list_head;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

/** TODO: ft_handle_word
* @brief: Adds the token value to the command's name or arguments
//=======================================================================//
* @HOW_IT_works:
	// If command name is NULL, initializes it with the token value.
	// Otherwise, appends the token value to the argument list.
//=======================================================================//
*/
void ft_handle_word(t_command_full **temp_command, t_tokens *temp_token, t_data **minishell)
{
	if ((*temp_command)->cmd_name == NULL)
	{
		(*temp_command)->cmd_name = ft_strdup(temp_token->value);
	}
	char **new_args = append_string_to_array(temp_token->value, (*temp_command)->args);
	if (new_args == NULL)
	{
		ft_handle_error(true, "malloc error - printed by ft_parse_tokens\n", 444, minishell);
		return;
	}
	(*temp_command)->args = new_args;
}

/** TODO: ft_handle_here_doc
* @brief: Handles heredoc input for the given redirection
//=======================================================================//
* @HOW_IT_works:
	// Reads input line by line until EOF or delimiter match.
	// Appends lines to the result string, separated by newlines.
//=======================================================================//
* @returns: char * - heredoc content || NULL
*/
char	*ft_handle_here_doc(t_command_full *current_cmd, t_redir *current_redir)
{
	bool	continue_reading;
	char	*here_doc_next_line;
	char	*result_text;
	char	*temp_copy;

	continue_reading = true;
	here_doc_next_line = NULL;
	result_text = ft_strdup("");
	if (!result_text)
		return (NULL);

	while (continue_reading == true)
	{
		// Get next line from readline
		here_doc_next_line = readline(HEREDOC_PROMPT);

		// Exit loop if EOF or delimiter match
		if (here_doc_next_line == NULL || ft_strcmp(current_redir->file_name, here_doc_next_line) == 0)
		{
			if (here_doc_next_line != NULL)
			{
				// free(here_doc_next_line);
				here_doc_next_line = NULL; // Reset to avoid invalid free
			}
			break ;
		}

		// Append next line to the result
		temp_copy = ft_join_with_delimeter(result_text, here_doc_next_line, "\n");

		// free(here_doc_next_line); // Free current line after use

		here_doc_next_line = NULL; // Reset pointer

		if (!temp_copy) // Handle memory allocation failure
		{
			free(result_text);
			return (NULL);
		}
		if (result_text)
			free(result_text); // Free old result

		result_text = temp_copy; // Update with new result
	}

	return (result_text);
}

// char *ft_handle_here_doc(t_command_full *current_cmd, t_redir *current_redir)
// {
// 	bool continue_reading;
// 	char *here_doc_next_line;
// 	char *result_text;
// 	char *temp_copy;

// 	continue_reading = true;
// 	result_text = ft_strdup(""); // Start with an empty string
// 	if (!result_text)
// 		return (NULL);

// 	while (continue_reading == true)
// 	{
// 		here_doc_next_line = readline(HEREDOC_PROMPT);
// 		if (here_doc_next_line == NULL || ft_strcmp(current_redir->file_name, here_doc_next_line) == 0)
// 		{
// 			free(here_doc_next_line);
// 			break;
// 		}
// 		temp_copy = ft_join_with_delimeter(result_text, here_doc_next_line, "\n");
// 		free(here_doc_next_line);
// 		if (!temp_copy)
// 		{
// 			free(result_text);
// 			return (NULL);
// 		}
// 		free(result_text);
// 		result_text = temp_copy;
// 	}

// 	ft_printf("here %s\n", result_text);
// 	return (result_text);
// }

/** TODO: ft_init_redir
* @brief: Initialize obj type t_redir
* @location: t_redir --> parsing.h
//=======================================================================//
* @HOW_IT_works:
	// takes previous token to set redirection type.
	// takes current token to set redirection_file_name
//=======================================================================//
* @returns: t_redir * - obj t_redir || NULL
*/
t_redir *ft_init_redir(t_tokens *prev_token, t_tokens *token, t_command_full *cmd)
{
	t_redir *redirection;

	redirection = (t_redir *)malloc(sizeof(t_redir));
	if (!redirection)
		return (NULL);
	redirection->type = 0;
	redirection->file_name = NULL;
	redirection->fd = NULL;
	redirection->prev = NULL;
	redirection->next = NULL;
	redirection->value = NULL; // Initialize value to NULL for HEREDOC

	return (redirection);
}

/** TODO: ft_handle_redirection
* @brief: initialize + adds any type of redirection into cmd_redir_list
//=======================================================================//
* @HOW_IT_works:
	// takes temp_token to init redir obj
	// takes cmd for adding redir into redirection list;
	// takes head_cmd to be able to free memory
	// if prev_redir is null it means it is first redirection for this cmd
//=======================================================================//
* @returns: t_redir * - obj t_redir || NULL
*/
void ft_handle_redirection(t_command_full *cmd, t_tokens *token, t_data **minishell)
{
	t_redir *new_redirection;
	t_redir *prev_redir;
	char *tempstr;

	prev_redir = ft_scroll_redir_list_to_last(cmd->redir_list_head);
	new_redirection = ft_init_redir(token->prev, token, cmd);
	if (!new_redirection)
	{
		ft_handle_error(true, "malloc error - printed by ft_handle_redirection\n", 447, minishell);
		return;
	}
	new_redirection->type = token->prev->type;
	new_redirection->file_name = ft_strdup(token->value);
	new_redirection->prev = prev_redir;
	ft_printf("filename = %s\n", new_redirection->file_name);
	if (new_redirection->type == T_DLESS)
	{
		tempstr = ft_handle_here_doc(cmd, new_redirection);
		if (!tempstr)
		{
			free(new_redirection->file_name);
			new_redirection = NULL;
			free(new_redirection);
			ft_handle_error(true, "error, printed by ft_handle_redirection\n", 4041, minishell);
			return;
		}
		new_redirection->value = tempstr;
	}

	if (prev_redir)
		prev_redir->next = new_redirection;
	else
		cmd->redir_list_head = new_redirection;
}

/** TODO: init_cmd
* @brief: initialize cmd
* @location: t_redir --> parsing.h
//=======================================================================//
* @HOW_IT_works:
	// takes token_info to init name of cmd
	// takes prev_cmd to connect new cmd to the list
//=======================================================================//
* @returns: new_cmd connected to the cmd_list
*/
t_command_full *init_cmd(t_command_full *prev_cmd, t_tokens *token_info)
{
	t_command_full *new_command;

	new_command = (t_command_full *)malloc(sizeof(t_command_full));
	if (!new_command)
		return (NULL);
	new_command->prev = prev_cmd;
	new_command->next = NULL;
	new_command->args = NULL;
	new_command->redir_list_head = NULL;
	new_command->cmd_name = NULL;
	new_command->fd_in = 0;
	new_command->fd_out = 1;
	new_command->here_doc = NULL;
	return (new_command);
}

/** TODO: ft_parse_tokens
* @brief: parses tokens and initializes commands
//=======================================================================//
* @HOW_IT_works:
	// Processes tokens to construct a command list with redirections.
	// Handles words, redirections, and pipes appropriately.
//=======================================================================//
* @returns: t_command_full * - the head of the command list
*/
t_command_full *ft_parse_tokens(t_data **minishell)
{
	t_command_full *cmd_head;
	t_command_full *temp_command;
	t_command_full *new_command;
	t_tokens *temp_token;

	cmd_head = init_cmd(NULL, (*minishell)->tokens);
	if (!cmd_head)
		ft_handle_error(true, "malloc error - printed by ft_parse_tokens\n", 444, minishell);
	temp_command = cmd_head;
	temp_token = (*minishell)->tokens;
	(*minishell)->commands = cmd_head;
	while (temp_token != NULL)
	{
		if (temp_token->type == T_WORD)
		{
			ft_handle_word(&temp_command, temp_token, minishell);
		}
		else if (temp_token->type == T_LESS || temp_token->type == T_GREAT || 
		         temp_token->type == T_DLESS || temp_token->type == T_DGREAT)
		{
			temp_token = temp_token->next;
			ft_handle_redirection(temp_command, temp_token, minishell);
		}
		else if (temp_token->type == T_PIPE)
		{
			new_command = init_cmd(temp_command, temp_token);
			if (!new_command)
				ft_handle_error(true, "malloc error1 - printed by ft_parse_tokens\n", 444, minishell);
			temp_command->next = new_command;
			temp_command = temp_command->next;
		}
		temp_token = temp_token->next;
	}
	temp_command->next = NULL;
	return (cmd_head);
}
