/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:23:34 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/05 15:27:03 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	runcmd(struct s_cmd *cmd)
{
	if (cmd == 0)
		exit(1);
	if (cmd->type == 0)
		exit(1);
	if (cmd->type == EXEC)
		do_exec(cmd);
	else if (cmd->type == REDIR)
		do_redirect(cmd);
	else if (cmd->type == LIST)
		do_list(cmd);
	else if (cmd->type == PIPE)
		do_pipe(cmd);
	else if (cmd->type == BACK)
		do_back(cmd);
	else
		exit(1);
	exit(0);
}