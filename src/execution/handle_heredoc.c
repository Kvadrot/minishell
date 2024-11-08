/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:30:18 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/11/07 13:55:25 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	setup_heredoc(t_command_full *cmd)
{
	t_redir	*redir;
	int		pipe_fds[2];

	redir = cmd->redir_list_head;
	if (redir && redir->value != NULL)
	{
		if (pipe(pipe_fds) == -1)
		{
			perror("Failed to create heredoc pipe");
			exit(EXIT_FAILURE);
		}
		write(pipe_fds[1], redir->value, ft_strlen(redir->value));
		close(pipe_fds[1]);
		cmd->fd_in = pipe_fds[0];
	}
}