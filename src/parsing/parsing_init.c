/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:27:53 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/19 18:21:51 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_cmd	*ft_init_exec_cmd(void)
{
	t_execcmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = EXEC;
	return ((t_cmd *)cmd);
}

void	init_cmd_args(t_execcmd *cmd)
{
	cmd->argv = malloc(sizeof(char *) * 11);
	if (!cmd->argv)
		panic("malloc");
	bzero(cmd->argv, 11 * sizeof(char *));
}

void	add_argument(t_execcmd *cmd, char *q, char *eq, int *argc)
{
	cmd->argv[*argc] = ft_substring(q, eq);
	(*argc)++;
	if (*argc >= MAXARGS)
		panic("too many args");
	cmd->argv[*argc] = NULL;
}
