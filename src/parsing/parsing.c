/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:26:01 by ssuchane          #+#    #+#             */
/*   Updated: 2024/09/07 12:27:06 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief: looks for the given token type inside tokens list
 * starting from the givven token
 * 
 * @input: t_tokens **Tokens_list, token_type that we are looking for
 * @return: Bool does the list contain the searchable type of node or not
*/
bool	ft_check_token_exists(t_tokens *tokens, t_token_type searchable_token)
{
	t_tokens	*temp_token;

	temp_token = tokens;
	while (temp_token)
	{
		if (temp_token->type == searchable_token)
		{
			return (true);
		}
		temp_token = temp_token->next;
	}
	return (false);
}



t_command	*ft_find_root(t_tokens *tokens);

/**
 * @brief: looks for the first token due to prioritization:
 * 1) | left right
 * 2) > < >> << : left right
 * 3) Word : char **args
 * 
 * there are some special rules for filling left and right in redirections cases
 * @input: t_tokens **Tokens_list
 * @return: initialize CMD_node
*/
t_command	*ft_find_root(t_tokens *start_token)
{
	t_command		*branch;
	// t_tokens		*temp_token;
	t_tokens	*searchable_token;

	searchable_token = ft_get_searchebale_token(start_token);

	//TODO: switch initializing properties due to retured type
	// if (searchable_token == T_WORD)
	// {
	// 	while (searchable_token)
	// }

	branch = init_branch(NULL, searchable_token->type, NULL, NULL);
	return (branch);
}

/**
 * @brief: Recursive func that converts list of tokens into AST
 * each AST_node = t_command
 * Tokens are divided via prioritization:
 * 1) | left right
 * 2) > < >> << : left right
 * 3) Word : char **args
 * 
 * TODO: think about condition that will terminate our loop
 * for now main Idia is to limit our loop with node limiter
 * 
 * there are some special rules for filling left and right in redirections cases
 * @input: t_tokens **Tokens_list, pointer to the node that limits our func
 * @return: AST - tree made from t_commands nods 
*/
t_command	*parse_tokens(t_tokens *tokens)
{
	// t_tokens	*temp_token;
	t_command	*root_branch;

	// temp_token = tokens;
	//TODO: ft_find_root(tokens )
	// func that searches for root token keeping prioritized sequence: 1) PIPE 2) first redir 3) WORD
	root_branch = ft_find_root(tokens);
	ft_printf("%i", root_branch->type);
	//
	return (root_branch);
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

