/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:47:39 by itykhono          #+#    #+#             */
/*   Updated: 2024/09/07 12:44:25 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief: initialize object of type t_command with givven parameters
 * 
 * @input: t_command properties
 * @return: t_command object or Null if malloc has gone wrong
*/

t_command	*init_branch(char **args, int type, t_command *next, t_command *prev)
{
	t_command *branch;

	branch = (t_command *)malloc(sizeof(t_command));
	if (!branch)
		return (NULL);
	branch->args = args;
	branch->type = type;
	branch->next = next;
	branch->prev = prev;

	return (branch);
}

/**
 * @brief: iterates through tokens_list, returns The highest prioritized first met token:
 * 1) Pipe if there is no Pipe -> looks for next prioritized token_type
 * 2) Any kind of redirection >> > < <<  if there is no  >> > < << -> looks for next
 * prioritized token_type
 * 3) Word. 
 * 
 * @input: t_tokens *start_token
 * @return: t_token_type - returns The highest prioritized first met token
*/
t_tokens	*ft_get_searchebale_token(t_tokens *start_token)
{
	t_tokens	*temp_token;
	t_tokens	*token_with_highest_priority;

	temp_token = start_token;
	while (temp_token)
	{
		if (temp_token->type == T_PIPE)
		{
			token_with_highest_priority = temp_token;
			return (token_with_highest_priority);
		}
		temp_token = temp_token->next;
	}
	temp_token = start_token;
	while (temp_token)
	{
		if (temp_token->type == T_GREAT || temp_token->type == T_LESS 
			|| temp_token->type == T_DGREAT || temp_token->type == T_DLESS)
		{
			token_with_highest_priority = temp_token;
			return (token_with_highest_priority);
		}
		temp_token = temp_token->next;
	}
	return (start_token);
}