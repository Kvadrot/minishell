/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:07:28 by itykhono          #+#    #+#             */
/*   Updated: 2024/10/13 16:26:34 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_n_flag(char *arg)
{
	int		i;
	bool	n_flag;

	n_flag = false;
	i = 0;
	if (arg[i] != '-')
		return (false);
	i++;
	while (arg[i] && arg[i] == 'n')
		i++;
	if (arg[i] == '\0')
		n_flag = true;
	return (n_flag);
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
		else if (!args[i + 1] && !is_n)
			ft_putstr_fd("\n", 1);
		i++;
	}
}

int	builtin_echo(char **args)
{
	int		i;
	bool	is_n;

	is_n = false;
	i = 0;
	while (args[i] && is_n_flag(args[i]))
	{
		is_n = true;
		i++;
	}
	echo_print_args(args + i, is_n);
	return (0);
}

