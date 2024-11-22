/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:44:31 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/11/21 15:12:19 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*get_env_value(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key) + 1) == 0)
			return env->value;
		env = env->next;
	}
	return NULL;
}

int	builtin_cd(t_data **minishell)
{
	char	current_pwd[1024];
	char	new_pwd[1024];
	char	*target_dir;

	if (getcwd(current_pwd, sizeof(current_pwd)) == NULL)
	{
		ft_putstr_fd("error getting current directory", 2);
		return (1);
	}
	if (!(*minishell)->commands->args[1])
	{
		target_dir = get_env_value((*minishell)->env, "HOME");
		if (!target_dir)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (1);
		}
	}
	else
		target_dir = (*minishell)->commands->args[1];
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
