/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:26:01 by ssuchane          #+#    #+#             */
/*   Updated: 2024/09/29 12:45:45 by ufo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/** TODO: ft_scroll_redir_list_to_last
* @brief: returns last node from t_redir * list
//=======================================================================//
* @HOW_IT_works: simply
//=======================================================================//
* @returns: t_redir	* - obj t_redir || NULL
*/
t_redir *ft_scroll_redir_list_to_last(t_redir *redir_list_head)
{
	t_redir *temp;
	
	if (!redir_list_head)
		return (NULL);
	temp = redir_list_head;
	while (temp->next)
		temp = temp->next;
	return (temp);
}


/** TODO: ft_get_size_arr_of_str
* @brief: Countd lrngth ARR OF STRINGS
//=======================================================================//
//=======================================================================//
* @returns: amount of strings inside: int
*/
int	ft_get_size_arr_of_str(char **arr_of_str)
{
	int	result;

	result = 0;

	if (!arr_of_str)
		return (result);
	while (arr_of_str[result] != NULL)
	{
		result++;
	}
	return (result);
}

/** TODO: ft_append_argument
* @brief: appends new str to the end of arr
//=======================================================================//
* @HOW_IT_works:
	coppies new_string, allocates mem for it
	allocates mem for result: [[Str]], at the end +2 for new element & NULL
	
//=======================================================================//
* @returns: t_redir	* - obj t_redir || NULL
*/
 char **append_string_to_array(char *new_str, char **args)
{
    int i = 0;
    int old_size = ft_get_size_arr_of_str(args); // Assuming this returns the length of the array
    char **result;

    // Allocate memory for the new array
    result = (char **)malloc(sizeof(char *) * (old_size + 2)); // +1 for new string, +1 for NULL
    if (!result) {
        return NULL; // Check for allocation failure
    }

    // Copy existing strings to the new array
    while (i < old_size) {
        // Allocate memory for each string in the new array
        result[i] = (char *)malloc(ft_strlen(args[i]) + 1); // +1 for null terminator
        if (!result[i]) {
            // Free already allocated memory if any malloc fails
            while (i-- > 0)
                free(result[i]);
            free(result);
            return NULL;
        }

        // Copy the string from the old array to the new array
        ft_strlcpy(result[i], args[i], ft_strlen(args[i]) + 1); // Include null terminator
        i++;
    }

    // Add the new string
    result[i] = ft_strdup(new_str); // Duplicate the new string
    if (!result[i]) {
        free(result); // Free the new array if strdup fails
        return NULL;
    }

    // Terminate the array with NULL
    result[i + 1] = NULL;

    // Free the old args array if it was allocated
    free(args);

    return (result); // Return the new array
}


void	ft_handle_word(t_command_full **temp_command, t_tokens *temp_token, t_data **minishell)
{
	if ((*temp_command)->cmd_name == NULL)
	{
		(*temp_command)->cmd_name = ft_strdup(temp_token->value);
	}
	else
	{
		char **new_args = append_string_to_array(temp_token->value ,(*temp_command)->args);
		if (new_args == NULL)
		{
			ft_handle_error(true, "malloc error1 - printed by ft_parse_tokens\n", 444, *minishell);
			return; // Early return to avoid using NULL pointer
		}
		(*temp_command)->args = new_args; // Update args only after successful append
	}
	
}
	

/** TODO: ft_init_redir
* @brief: Initialize obj type t_redir 
* @location: t_redir --> parsing.h
//=======================================================================//
* @HOW_IT_works:
	// takes previous token to set redirection type.
	// takes current token to set redirection_file_name
//=======================================================================//
* @returns: t_redir	* - obj t_redir || NULL
*/
t_redir	*ft_init_redir(t_tokens *prev_token, t_tokens *token, t_command_full *cmd)
{
	t_redir *redirection;

	redirection = (t_redir *)malloc(sizeof(t_redir));
	if (!redirection)
		(NULL);
	redirection->type = 0;
	redirection->file_name = NULL;
	redirection->fd = NULL;
	redirection->prev = NULL;
	redirection->next = NULL;

	return (redirection);
}

/** TODO: ft_handle_redirection
* @brief: initialize + adds any type of reidrecrtion into cmd_redir_list
//=======================================================================//
* @HOW_IT_works:
	// takes temp_token to init redir obj
	// takes cmd for adding redir into rediretion list;
	// takes head_cmd to be able to free memmory
	// if prev_redir is null it means it is first redirection for this cmd
//=======================================================================//
* @returns: t_redir	* - obj t_redir || NULL
*/
void	ft_handle_redirection(t_command_full *cmd ,t_tokens *token, t_data **minishell)
{
	t_redir *new_redirection;
	t_redir	*prev_redir;

	prev_redir = ft_scroll_redir_list_to_last(cmd->redir_list_head);
	new_redirection = ft_init_redir(token->prev, token, cmd);
	if (!new_redirection)
	{
		ft_handle_error(true, "malloc error - printed by ft_handle_redirection\n", 447, *minishell);
	}
	new_redirection->type = token->prev->type;
	new_redirection->file_name = token->value;
	new_redirection->prev = prev_redir;
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
* @returns: new_cmd conected to the cmd_list
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
	return (new_command);
}

t_command_full *ft_parse_tokens(t_data **minishell)
{
	t_command_full	*cmd_head;
	t_command_full	*temp_command;
	t_command_full	*new_command;
	t_tokens		*temp_token;

	cmd_head = init_cmd(NULL, (*minishell)->tokens);
	if (!cmd_head)
		ft_handle_error(true, "malloc error - printed by ft_parse_tokens\n", 444, *minishell);
	temp_command = cmd_head;
	temp_token = (*minishell)->tokens;
	(*minishell)->commands = cmd_head;
	while (temp_token != NULL)
	{
		if (temp_token->type == T_WORD)
		{
			ft_handle_word(&temp_command, temp_token, minishell);
		}
		else if (temp_token->type == T_LESS || temp_token->type == T_GREAT 
			|| temp_token->type == T_DLESS || temp_token->type == T_DGREAT )
		{
			temp_token = temp_token->next;
			ft_handle_redirection(temp_command, temp_token, minishell);
		} else if (temp_token->type == T_PIPE) {
			new_command = init_cmd(temp_command, temp_token);
			if (!new_command)
				ft_handle_error(true, "malloc error1 - printed by ft_parse_tokens\n", 444, *minishell);
			temp_command->next = new_command;
			temp_command = temp_command->next;
		}
		temp_token = temp_token->next;
	}

	ft_debug_parsing(minishell);
	return (cmd_head);
}

// Function to free the args array in a command
void	free_command_args(t_command_full *cmd)
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

