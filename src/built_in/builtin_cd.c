/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:44:31 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/10/11 12:26:46 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// with only a relative or absolute path

#include "../../inc/minishell.h"

void	add_to_env(t_data **minishell, char *key, char *new_value) {
	t_env *tmp = (*minishell)->env;

	// Check if the key exists and update if it does
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key)) == 0) {
			tmp->value = new_value; // Update the value
			printf("Updated: key = %s, value = %s\n", tmp->key, tmp->value);
			return; // Exit after updating
		}
		tmp = tmp->next;
	}

	// If we reach here, the key does not exist, so we add it
	environment_new_node_end(*minishell, key, new_value);
	printf("Added: key = %s, value = %s\n", key, new_value);
}

int	builtin_cd(t_data **minishell)
{
	char	current_pwd[1024]; // Buffer to hold the current working directory
	char	new_pwd[1024];

	if (getcwd(current_pwd, sizeof(current_pwd)) == NULL)
	{
		ft_printf_full("error getting current directory", 2, NULL);
		return (-1);
	}
	printf("current pwd is %s\n", current_pwd);
	if ((*minishell)->commands->args[1])
	{
		ft_printf_full("too many arguments", 2, NULL);
		return (-1);
	}
	if (chdir((*minishell)->commands->args[0]) == -1)
	{
		ft_printf_full("error with chdir", 2, NULL);
		return (-1);
	}
	add_to_env(minishell, "OLDPWD", current_pwd);
	if (getcwd(new_pwd, sizeof(new_pwd)) == NULL)
	{
		ft_printf_full("error getting new directory", 2, NULL);
		return (-1);
	}
	add_to_env(minishell, "PWD", new_pwd);
	return (0);
}