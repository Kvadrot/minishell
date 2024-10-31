/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:07:28 by itykhono          #+#    #+#             */
/*   Updated: 2024/10/31 14:15:21 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_n_flag(char *arg)
{
	int		i;

	if (arg[0] != '-')
		return (false);
	i = 1;
	while (arg[i] == 'n')
		i++;
	if (arg[i] != '\0')
		return (false);
	return (true);
}

void	echo_print_args(char **args, bool is_n)
{
	int	i;

	i = 0;
	if (!args[i])
	{
		if (!is_n)
			ft_putstr_fd("\n", 1);
		return ;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!is_n)
		ft_putstr_fd("\n", 1);
}

int	builtin_echo(char **args)
{
	int		i;
	bool	is_n;

	is_n = false;
	i = 1;
	while (args[i] && is_n_flag(args[i]))
	{
		is_n = true;
		i++;
	}
	echo_print_args(args + i, is_n);
	return (0);
}
