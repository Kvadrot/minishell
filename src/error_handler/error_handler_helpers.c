/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:01:04 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/11/23 18:03:25 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	free_redir_node(t_redir *node)
{
	if (node->file_name)
	{
		free(node->file_name);
		node->file_name = NULL;
	}
	if (node->fd)
	{
		free(node->fd);
		node->fd = NULL;
	}
	if (node->value)
	{
		free(node->value);
		node->value = NULL;
	}
	free(node);
	node = NULL;
}

static void	ft_free_redir_list(t_command_full **cmd)
{
	t_redir	*temp_redir;
	t_redir	*pt_holder;

	if ((*cmd)->redir_list_head)
	{
		temp_redir = (*cmd)->redir_list_head;
		while (temp_redir)
		{
			pt_holder = temp_redir->next;
			free_redir_node(temp_redir);
			temp_redir = pt_holder;
		}
		(*cmd)->redir_list_head = NULL;
	}
}

static void	free_command_args(t_command_full **cmd)
{
	int	i;

	if ((*cmd)->args)
	{
		i = 0;
		while ((*cmd)->args[i] != NULL)
		{
			free((*cmd)->args[i]);
			(*cmd)->args[i] = NULL;
			i++;
		}
		free((*cmd)->args);
		(*cmd)->args = NULL;
	}
}

static void	free_single_command(t_command_full *cmd)
{
	ft_free_redir_list(&cmd);
	free_command_args(&cmd);
	if (cmd->here_doc)
	{
		free(cmd->here_doc);
		cmd->here_doc = NULL;
	}
	if (cmd->cmd_name)
	{
		free(cmd->cmd_name);
		cmd->cmd_name = NULL;
	}
	free(cmd);
	cmd = NULL;
}

void	ft_free_commands(t_data **minishell)
{
	t_command_full	*temp_cmd;
	t_command_full	*cmd_pt_holder;

	temp_cmd = (*minishell)->commands;
	while (temp_cmd != NULL)
	{
		cmd_pt_holder = temp_cmd->next;
		free_single_command(temp_cmd);
		temp_cmd = cmd_pt_holder;
	}
	if ((*minishell)->commands)
		(*minishell)->commands = NULL;
}
