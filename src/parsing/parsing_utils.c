/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:52:49 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/11/24 18:00:38 by mbudkevi         ###   ########.fr       */
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
t_redir	*ft_scroll_redir_list_to_last(t_redir *redir_list_head)
{
	t_redir	*temp;

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
void	ft_handle_word(t_command_full **temp_command, t_tokens *temp_token,
		t_data **minishell)
{
	char	**new_args;

	new_args = NULL;
	if ((*temp_command)->cmd_name == NULL)
	{
		(*temp_command)->cmd_name = ft_strdup(temp_token->value);
	}
	new_args = append_string_to_array(temp_token->value, (*temp_command)->args);
	if (new_args == NULL)
	{
		ft_handle_error(true, "malloc error - printed by ft_parse_tokens\n",
			444, minishell);
		return ;
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

static void	ft_handle_handle_here_doc_helper(char **here_doc_next_line,
		char **result_text, char **temp_copy)
{
	if (*here_doc_next_line)
	{
		free(*here_doc_next_line);
		*here_doc_next_line = NULL;
	}
	if (*result_text)
		free(*result_text);
	*result_text = ft_strdup(*temp_copy);
	if (*temp_copy)
	{
		free(*temp_copy);
		*temp_copy = NULL;
	}
}

char	*ft_handle_here_doc(t_redir *current_redir)
{
	char	*here_doc_next_line;
	char	*result_text;
	char	*temp_copy;

	here_doc_next_line = NULL;
	result_text = ft_strdup("");
	if (!result_text)
		return (NULL);
	while (1)
	{
		here_doc_next_line = readline(HEREDOC_PROMPT);
		if (here_doc_next_line == NULL || ft_strcmp(current_redir->file_name,
				here_doc_next_line) == 0)
		{
			if (here_doc_next_line != NULL)
				here_doc_next_line = NULL;
			break ;
		}
		temp_copy = ft_join_with_delimeter(result_text, here_doc_next_line,
				"\n");
		ft_handle_handle_here_doc_helper(&here_doc_next_line, &result_text,
			&temp_copy);
	}
	return (result_text);
}

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
t_redir	*ft_init_redir(void)
{
	t_redir	*redirection;

	redirection = (t_redir *)malloc(sizeof(t_redir));
	if (!redirection)
		return (NULL);
	redirection->type = 0;
	redirection->file_name = NULL;
	redirection->fd = NULL;
	redirection->prev = NULL;
	redirection->next = NULL;
	redirection->value = NULL;
	return (redirection);
}
