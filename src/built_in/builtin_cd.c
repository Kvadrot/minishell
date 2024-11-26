/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:44:31 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/11/22 18:41:01 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*get_env_value(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key) + 1) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static int	get_current_pwd(char *current_pwd)
{
	if (getcwd(current_pwd, 1024) == NULL)
	{
		ft_putstr_fd("error getting current directory", 2);
		return (1);
	}
	return (0);
}

static char	*get_target_dir(t_data **minishell)
{
	char	*target_dir;

	if (!(*minishell)->commands->args[1])
	{
		target_dir = get_env_value((*minishell)->env, "HOME");
		if (!target_dir)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (NULL);
		}
	}
	else
		target_dir = (*minishell)->commands->args[1];
	return (target_dir);
}

int	builtin_cd(t_data **minishell)
{
	char	current_pwd[1024];
	char	new_pwd[1024];
	char	*target_dir;

	if (get_current_pwd(current_pwd))
		return (1);
	target_dir = get_target_dir(minishell);
	if (chdir(target_dir) == -1)
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
