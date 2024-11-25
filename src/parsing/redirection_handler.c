/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:19:59 by ufo               #+#    #+#             */
/*   Updated: 2024/11/24 17:51:44 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/** TODO: ft_handle_input
* @brief: Manages input redirection based on redirection type.
* @takes: redir - pointer to t_redir structure containing redirection details
//=======================================================================//
* @HOW_IT_WORKS:
1) Checks if redirection type is input (T_LESS):
*   - Calls ft_handle_less for file reading
2) Handles T_DLESS (Heredoc) separately as a future TODO
* Returns the file descriptor;
3) if heredoc is our redir, we retrun 0 stdin,
	as here doc is separate property in struct
//=======================================================================//
* @returns: fd - file descriptor, or -1 if error occurs
*/
int	ft_handle_input(t_redir *redir)
{
	int	fd_result;

	if (redir->type == T_LESS)
		fd_result = ft_handle_less(redir->file_name);
	else
		return (0);
	return (fd_result);
}

/** TODO: ft_process_redirection_list
* @brief: Processes all redirections (input and output) for each command.
* @takes: minishell - pointer to the minishell data structure
//=======================================================================//
* @HOW_IT_WORKS:
1) Iterates over each command in the minishell command list
2) For each command, processes its redirection list:
*   - Output redirection (T_GREAT, T_DGREAT): updates cmd->fd_out
*   - Input redirection (T_LESS, T_DLESS): updates cmd->fd_in
3) Iterates through next redirection for each command;
//=======================================================================//
* @returns: void
*/
// Function to process redirection for output
int	ft_process_output_redirection(t_command_full *temp_cmd, t_redir *temp_redir)
{
	temp_cmd->fd_out = ft_handle_output(temp_redir);
	if (temp_cmd->fd_out == -1)
	{
		ft_close_all_redirections(temp_cmd, temp_redir);
		return (-400);
	}
	return (0);
}

// Function to process redirection for input
int	ft_process_input_redirection(t_command_full *temp_cmd, t_redir *temp_redir)
{
	temp_cmd->fd_in = ft_handle_input(temp_redir);
	if (temp_cmd->fd_in == -1)
	{
		ft_close_all_redirections(temp_cmd, temp_redir);
		return (-401);
	}
	if (temp_redir->type == T_LESS)
	{
		if (temp_cmd->here_doc)
		{
			free(temp_cmd->here_doc);
			temp_cmd->here_doc = NULL;
		}
		temp_cmd->here_doc = NULL;
	}
	else if (temp_redir->type == T_DLESS)
	{
		temp_cmd->here_doc = ft_strdup(temp_redir->value);
	}
	return (0);
}

// Function to handle the redirection processing for each command
int	ft_process_redirection_for_command(t_command_full *temp_cmd)
{
	t_redir	*temp_redir;
	int		ret;

	if (temp_cmd->redir_list_head != NULL)
	{
		temp_redir = temp_cmd->redir_list_head;
		while (temp_redir)
		{
			if (temp_redir->type == T_GREAT || temp_redir->type == T_DGREAT)
			{
				ret = ft_process_output_redirection(temp_cmd, temp_redir);
				if (ret != 0)
					return (ret);
			}
			else if (temp_redir->type == T_LESS || temp_redir->type == T_DLESS)
			{
				ret = ft_process_input_redirection(temp_cmd, temp_redir);
				if (ret != 0)
					return (ret);
			}
			temp_redir = temp_redir->next;
		}
	}
	return (0);
}

int	ft_process_redirection_list(t_data **minishell)
{
	t_command_full	*cmd_head;
	t_command_full	*temp_cmd;
	int				ret;

	cmd_head = (*minishell)->commands;
	temp_cmd = cmd_head;
	while (temp_cmd != NULL)
	{
		ret = ft_process_redirection_for_command(temp_cmd);
		if (ret != 0)
			return (ret);
		temp_cmd = temp_cmd->next;
	}
	return (200);
}
