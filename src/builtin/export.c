/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:23:52 by ssuchane          #+#    #+#             */
/*   Updated: 2024/09/19 18:43:25 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**get_key_and_value(char *argument)
{
	char	*delimiter_pos;
	char	**key_value;

	delimiter_pos = ft_strchr(argument, '=');
	if (!delimiter_pos)
		return (NULL);
	key_value = (char **)malloc(sizeof(char *) * 2);
	if (!key_value)
		return (NULL);
	key_value[0] = ft_strndup(argument, delimiter_pos - argument);
	if (!key_value[0])
	{
		free(key_value);
		return (NULL);
	}
	key_value[1] = ft_strdup(delimiter_pos + 1);
	if (!key_value[1])
	{
		free(key_value[0]);
		free(key_value);
		return (NULL);
	}
	return (key_value);
}

void	free_key_value(char **key_value)
{
	if (key_value)
	{
		free(key_value[0]);
		free(key_value[1]);
		free(key_value);
	}
}

int	update_or_add_env_var(t_data *minishell, char **key_value)
{
	t_env	*env;
	int		updated;

	env = minishell->envlist;
	updated = 0;
	while (env != NULL)
	{
		if (ft_strcmp(key_value[0], env->key) == 0)
		{
			free(env->value);
			env->value = ft_strdup(key_value[1]);
			if (!env->value)
				return (0);
			updated = 1;
			return (1);
		}
		env = env->next;
	}
	if (!updated)
	{
		environment_new_node_end(&minishell->envlist, key_value[0],
			key_value[1]);
		return (1);
	}
	return (0);
}

int	process_export_argument(char *arg, t_data *minishell)
{
	char	**key_value;
	int		result;

	key_value = get_key_and_value(arg);
	if (!key_value)
		return (1);
	result = update_or_add_env_var(minishell, key_value);
	free_key_value(key_value);
	return (result);
}

int	ft_export(char **argv, t_data *minishell)
{
	int	i;
	int	result;

	if (argv[1] == NULL)
	{
		print_environment_sorted(minishell->envlist);
		return (1);
	}
	i = 1;
	while (argv[i] != NULL)
	{
		result = process_export_argument(argv[i], minishell);
		if (result != 0)
			return (result);
		i++;
	}
	return (0);
}
