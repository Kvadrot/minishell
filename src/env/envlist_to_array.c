/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist_to_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:18:13 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/11 20:00:46 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	environment_list_size(t_env *environment)
{
	int		size;
	t_env	*current;

	size = 0;
	current = environment;
	while (current != NULL)
	{
		size++;
		current = current->next;
	}
	return (size);
}

char	*environment_create_key_value(t_env *node)
{
	char	*temp;
	char	*key_value;

	if (!node || !node->key || !node->value)
		return (NULL);
	temp = ft_strjoin(node->key, "=");
	key_value = ft_strjoin(temp, node->value);
	free(temp);
	return (key_value);
}

int	environment_fill_array(t_env *environment, char **env_array)
{
	t_env	*current;
	int		i;

	current = environment;
	i = 0;
	while (current != NULL)
	{
		env_array[i] = environment_create_key_value(current);
		if (!env_array[i])
		{
			while (i > 0)
				free(env_array[--i]);
			return (0);
		}
		i++;
		current = current->next;
	}
	env_array[i] = NULL;
	return (1);
}

char	**environment_list_to_array(t_env *environment)
{
	char	**env_array;
	int		list_size;

	list_size = environment_list_size(environment);
	if (list_size == 0)
		return (NULL);
	env_array = (char **)malloc(sizeof(char *) * (list_size + 1));
	if (!env_array)
		return (NULL);
	if (!environment_fill_array(environment, env_array))
	{
		free(env_array);
		return (NULL);
	}
	return (env_array);
}
