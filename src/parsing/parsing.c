/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:26:01 by ssuchane          #+#    #+#             */
/*   Updated: 2024/09/17 13:43:33 by itykhono         ###   ########.fr       */
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
	t_redir	*prev_redir;

	prev_redir = ft_scroll_redir_list_to_last(cmd->redir_list_head);
	redirection = (t_redir *)malloc(sizeof(t_redir));
	if (!redirection)
		(NULL);
	redirection->type = prev_token->type;
	redirection->file_name = token->value;
	redirection->fd = NULL;
	redirection->prev = prev_redir;
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
//=======================================================================//
* @returns: t_redir	* - obj t_redir || NULL
*/
void	ft_handle_redirection(t_command_full *cmd ,t_tokens *token, t_data **minishell)
{
	t_redir *new_redirection;
	t_command_full *temp_cmd;

	new_redirection = ft_init_redir(token->prev, token, cmd);
	if (!new_redirection)
	{
		ft_handle_error(true, "malloc error - printed by ft_handle_redirection\n", 447, *minishell);
	}
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
	new_command->cmd_name = token_info->value;
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
	(*minishell)->commands = cmd_head;
	temp_command = cmd_head;
	temp_token = (*minishell)->tokens;
	while (temp_token != NULL)
	{
		if (temp_token->type == T_WORD)
		{
			// TODO:
			// append word to arg_list 
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
			temp_command = new_command;
		}
		temp_token = temp_token->next;
	}
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

// ft_list_length()
//---------------------------------------------------------------//
// returns amount of t_nds inside of given List
//---------------------------------------------------------------//
int	ft_get_list_length(t_tokens *list)
{
	t_tokens	*temp;
	int		length;

	if (!list)
		return (0);
	length = 1;
	temp = list;
	while (temp->next)
	{
		temp = temp->next;
		length++;
	}
	return (length);
}


// -------infinity loop--------
//  sad dsd ads | fsdf sdfs > a

// ---------no output----------
//	only T_WORD 
//	ls | grep A
//	echo

// ------incomplete list-------
//	cat << EOF grep test dsada

