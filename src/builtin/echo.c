/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:23:52 by ssuchane          #+#    #+#             */
/*   Updated: 2024/09/07 20:33:08 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// builtins functionality
int	check_flags(t_cmd *cmd, bool *new_line)
{
	int			i;
	t_bcmd	*bcmd;

	bcmd = (t_execcmd *)cmd;
	i = 0;
	if (builtin->flag)
	{
		while (builtin->flag[i])
		{
			if (hell->flags[i++] != 'n')
			{
				ft_putstr_fd("invalid flag\n", 2);
				return (1);
			}
		}
		if (builtin->flag[0] == 'n')
			*new_line = false;
	}
	return (0);
}
// builtin echo
int	do_echo(t_execcmd builtin)
{
	int		i;
	bool	new_line;
	int		status;

	i = 0;
	new_line = true;
	status = check_flags(&builtin, &new_line);
	if (builtin.argv && builtin.argv[0] != NULL)
	{
		ft_putstr_fd(builtin.argv[i], 1);
		i++;
		while (builtin.argv[i])
		{
			ft_putstr_fd(" ", 1);
			ft_putstr_fd(builtin.argv[i], 1);
			i++;
		}
	}
	if (new_line)
		ft_putstr_fd("\n", 1);
	return (status);
}

void	do_builtin(t_execcmd *builtins)
{
	// before getting into this function check if the command exists
	// use function check_builtin();
	if (builtins->type == ECHO)
		do_echo(builtins);
	else if (builtins->type == CD)
		do_cd(builtins)
}