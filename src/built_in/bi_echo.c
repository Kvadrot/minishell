/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:07:28 by itykhono          #+#    #+#             */
/*   Updated: 2024/11/22 18:41:33 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	is_n_flag(char *arg)
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

static void	echo_print_args(char **args, bool is_n, int fd_out)
{
	int	i;

	i = 0;
	if (!args[i])
	{
		if (!is_n)
			ft_putstr_fd("\n", fd_out);
		return ;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], fd_out);
		if (args[i + 1])
			ft_putstr_fd(" ", fd_out);
		i++;
	}
	if (!is_n)
		ft_putstr_fd("\n", fd_out);
}

int	builtin_echo(char **args, int fd_out)
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
	echo_print_args(args + i, is_n, fd_out);
	return (0);
}
