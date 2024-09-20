/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:23:52 by ssuchane          #+#    #+#             */
/*   Updated: 2024/09/20 18:53:51 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_echo(char **argv)
{
	int		i;
	bool	new_line;

	i = 1;
	new_line = true;
	if (argv[i] && argv[i][0] == '-' && argv[i][1] == 'n')
	{
		new_line = false;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		i++;
		if (argv[i])
			ft_putstr_fd(" ", 1);
	}
	if (new_line)
		ft_putstr_fd("\n", 1);
	return (1);
}
