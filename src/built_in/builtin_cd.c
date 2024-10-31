/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:44:31 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/10/31 14:20:22 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	builtin_cd(t_data **minishell)
{
	char	current_pwd[1024];
	char	new_pwd[1024];

	if (getcwd(current_pwd, sizeof(current_pwd)) == NULL)
	{
		ft_printf_full("error getting current directory", 2, NULL);
		return (1);
	}
	if ((*minishell)->commands->args[2])
	{
		ft_printf_full("too many arguments", 2, NULL);
		return (1);
	}
	if (chdir((*minishell)->commands->args[1]) == -1)
	{
		printf("command is: %s\n", (*minishell)->commands->args[0]);
		ft_printf_full("No such file or directory\n", 2, NULL);
		return (1);
	}
	add_to_env(minishell, "OLDPWD", current_pwd);
	if (getcwd(new_pwd, sizeof(new_pwd)) == NULL)
	{
		ft_printf_full("error getting new directory", 2, NULL);
		return (1);
	}
	add_to_env(minishell, "PWD", new_pwd);
	return (0);
}
