/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:26:01 by ssuchane          #+#    #+#             */
/*   Updated: 2024/11/25 15:37:40 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_handle_redirection(t_command_full *cmd, t_tokens *token,
		t_data **shell)
{
	t_redir	*new_redir;
	t_redir	*prev_redir;

	prev_redir = ft_scroll_redir_list_to_last(cmd->redir_list_head);
	new_redir = ft_init_redir();
	if (!new_redir)
		return (ft_handle_error(true, "Malloc error\n", 447, shell));
	if (!ft_set_redirection_properties(new_redir, token, shell))
		return ;
	new_redir->prev = prev_redir;
	ft_helper_handle_redirection(&cmd, &new_redir, shell);
	if (prev_redir)
		prev_redir->next = new_redir;
	else
		cmd->redir_list_head = new_redir;
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
t_command_full	*init_cmd(t_command_full *prev_cmd)
{
	t_command_full	*new_command;

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

void	ft_process_pipe(t_command_full **temp_cmd, t_data **minishell)
{
	t_command_full	*new_command;

	new_command = init_cmd(*temp_cmd);
	if (!new_command)
	{
		ft_handle_error(true, "malloc error\n", 444, minishell);
		return ;
	}
	(*temp_cmd)->next = new_command;
	*temp_cmd = (*temp_cmd)->next;
}

int	ft_process_token(t_command_full **temp_cmd, t_tokens **temp_token,
		t_data **minishell)
{
	if ((*temp_token)->type == T_WORD)
		ft_handle_word(temp_cmd, temp_token, minishell);
	else if ((*temp_token)->type == T_LESS || (*temp_token)->type == T_GREAT
		|| (*temp_token)->type == T_DLESS || (*temp_token)->type == T_DGREAT)
	{
		*temp_token = (*temp_token)->next;
		if (!*temp_token)
		{
			ft_handle_error(true, "Unexpected end of tokens\n", 445, minishell);
			return (0);
		}
		ft_handle_redirection(*temp_cmd, *temp_token, minishell);
	}
	else if ((*temp_token)->type == T_PIPE)
		ft_process_pipe(temp_cmd, minishell);
	return (1);
}

t_command_full	*ft_parse_tokens(t_data **minishell)
{
	t_command_full	*cmd_head;
	t_command_full	*temp_command;
	t_tokens		*temp_token;

	cmd_head = init_cmd(NULL);
	if (!cmd_head)
		ft_handle_error(true, "malloc error - printed by ft_parse_tokens\n",
			444, minishell);
	temp_command = cmd_head;
	temp_token = (*minishell)->tokens;
	(*minishell)->commands = cmd_head;
	while (temp_token != NULL)
	{
		if (!ft_process_token(&temp_command, &temp_token, minishell))
			break ;
		temp_token = temp_token->next;
	}
	temp_command->next = NULL;
	return (cmd_head);
}
