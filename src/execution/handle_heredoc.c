/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:30:18 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/11/11 15:00:29 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	setup_heredoc(t_command_full *cmd)
{
	//t_redir	*redir;
	int		pipe_fds[2];

	//redir = cmd->redir_list_head;
	if (cmd->here_doc != NULL)
	{
		printf("heredoc is: %s\n", cmd->here_doc);
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