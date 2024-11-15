/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:44:31 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/11/11 16:19:47 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	builtin_cd(t_data **minishell)
{
	char	current_pwd[1024];
	char	new_pwd[1024];

	if (getcwd(current_pwd, sizeof(current_pwd)) == NULL)
	{
		ft_putstr_fd("error getting current directory", 2);
		return (1);
	}
	if ((*minishell)->commands->args[2])
		return (1);
	if (chdir((*minishell)->commands->args[1]) == -1)
	{
		ft_putstr_fd("No such file or directory\n", 2);
		return (1);
	}
	add_to_env(minishell, "OLDPWD", current_pwd);
	if (getcwd(new_pwd, sizeof(new_pwd)) == NULL)
	{
		ft_putstr_fd("error getting new directory", 2);
		return (1);
	}
	add_to_env(minishell, "PWD", new_pwd);
	return (0);
}
