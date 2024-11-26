/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:30:18 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/11/22 18:34:19 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	setup_heredoc(t_command_full *cmd)
{
	int		pipe_fds[2];

	if (cmd->here_doc != NULL)
	{
		if (pipe(pipe_fds) == -1)
		{
			perror("Failed to create heredoc pipe");
			exit(EXIT_FAILURE);
		}
		write(pipe_fds[1], cmd->here_doc, ft_strlen(cmd->here_doc));
		close(pipe_fds[1]);
		cmd->fd_in = pipe_fds[0];
	}
}
