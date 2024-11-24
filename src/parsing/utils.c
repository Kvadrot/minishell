/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:51:26 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/11/24 18:02:45 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/** TODO: ft_handle_less
* @brief: Handles input redirection from a file (< redirection).
* @takes: filename - name of the file to read from
//=======================================================================//
* @HOW_IT_WORKS:
1) Checks if the file exists (access F_OK)
2) Verifies read access (access R_OK)
3) Opens the file for reading if accessible
* Returns file descriptor if successful;
//=======================================================================//
* @returns: fd - file descriptor for reading, or -1 if error occurs
*/
int	ft_handle_less(char *filename)
{
	int	fd_result;

	fd_result = -1;
	if (access(filename, F_OK) == -1)
	{
		return (-1);
	}
	if (access(filename, R_OK) == -1)
	{
		return (-1);
	}
	fd_result = open(filename, O_RDONLY);
	if (fd_result == -1)
	{
		return (-1);
	}
	return (fd_result);
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

void	ft_helper_handle_redirection(t_command_full **cmd, t_redir **redir,
		t_data **minishell)
{
	char	*temp_str;

	if ((*redir)->type != T_DLESS)
		return ;
	temp_str = ft_handle_here_doc(*redir);
	if (!temp_str)
	{
		if ((*redir)->prev)
			(*redir)->prev->next = NULL;
		else
			(*cmd)->redir_list_head = NULL;
		free((*redir)->file_name);
		*redir = NULL;
		free(redir);
		ft_handle_error(true, "Failed to handle here-document redirection\n",
			4041, minishell);
		return ;
	}
	(*redir)->value = temp_str;
}

int	ft_set_redirection_properties(t_redir *redir, t_tokens *token,
		t_data **shell)
{
	if (token->prev)
		redir->type = token->prev->type;
	else
		return (ft_handle_error(true, "Token has no prev node\n", 448, shell),
			0);
	if (token->value)
		redir->file_name = ft_strdup(token->value);
	else
		return (ft_handle_error(true, "Token value is NULL\n", 449, shell), 0);
	return (1);
}
