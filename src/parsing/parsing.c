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

t_command_full *init_cmd(t_command_full *prev_cmd, t_tokens *token_info)
{
	t_command_full *new_command;
	new_command = (t_command_full *)malloc(sizeof(t_command_full));
	if (!new_command)
	{
		
		return (NULL);
	}

	return (new_command);
}

t_command_full *ft_parse(t_tokens *tokens)
{
	t_command_full	*list_head;
	t_command_full	*temp_node;
	t_tokens	*temp_token;
	
	if (!list_head)
	{
		list_head = init_cmd(NULL, tokens);
		if (!list_head)
		{
			// ft_throw_error();
			// return (NULL);
		}
		temp_node = list_head;
	} else {
		// temp_node = init_cmd();
	}
	temp_token = tokens;
	while (temp_token)
	{
		if (temp_token == T_PIPE)
		{
			
		} else if (temp_token == T_DGREAT || temp_token == T_DLESS || temp_token == T_GREAT || temp_token == T_LESS)
		{
			
		} else {
			// ft_append(temp_node->args, temp_token); appends cuurent token to 
		}
		temp_token = temp_token->next;
	}
	return (list_head);
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

