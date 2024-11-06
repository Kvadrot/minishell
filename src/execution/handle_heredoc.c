/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:30:18 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/11/06 14:01:16 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	setup_heredoc(t_command_full *cmd)
{
	t_redir	*redir;
	int		pipe_fds[2];

	redir = cmd->redir_list_head;
	// while (redir)
	// {
		if (redir->value != NULL)
		{
			if (pipe(pipe_fds) == -1)
			{
				perror("Failed to create heredoc pipe");
				exit(EXIT_FAILURE);
			}
			// Write the heredoc content to the write end of the pipe
			write(pipe_fds[1], redir->value, ft_strlen(redir->value));
			close(pipe_fds[1]);
			// Assign heredoc pipe read end as fd_in for this command
			cmd->fd_in = pipe_fds[0];
			// Exit the loop after setting up the first detected heredoc
			//break;
		}
	// 	redir = redir->next;
	// }
}