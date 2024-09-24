/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:23:52 by ssuchane          #+#    #+#             */
/*   Updated: 2024/09/24 15:45:47 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// echo prints quotes

void	remove_quotes(char *str)
{
	int	len;

	len = strlen(str);
	if ((len >= 2 && str[0] == '\'' && str[len - 1] == '\'')
		|| (len >= 2 && str[0] == '"' && str[len - 1] == '"'))
	{
		ft_memmove(str, str + 1, len - 2);
		str[len - 2] = '\0';
	}
}

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
