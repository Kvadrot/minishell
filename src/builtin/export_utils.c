/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:23:52 by ssuchane          #+#    #+#             */
/*   Updated: 2024/09/19 18:32:35 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_environment_sorted(t_env *node)
{
	size_t	count;
	t_env	**env_array;

	count = count_env_vars(node);
	if (count == 0)
		return ;
	env_array = collect_env_vars(node, count);
	if (!env_array)
		return ;
	sort_env_vars(env_array, count);
	print_sorted_env_vars(env_array, count);
	free(env_array);
}

void	print_sorted_env_vars(t_env **env_array, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		printf("%s=%s\n", env_array[i]->key, env_array[i]->value);
		i++;
	}
}

size_t	count_env_vars(t_env *node)
{
	size_t	count;

	count = 0;
	while (node != NULL)
	{
		count++;
		node = node->next;
	}
	return (count);
}

t_env	**collect_env_vars(t_env *node, size_t count)
{
	t_env	**env_array;
	size_t	i;

	env_array = (t_env **)malloc(sizeof(t_env *) * count);
	if (!env_array)
		return (NULL);
	i = 0;
	while (node != NULL)
	{
		env_array[i++] = node;
		node = node->next;
	}
	return (env_array);
}

void	sort_env_vars(t_env **env_array, size_t count)
{
	size_t	i;
	size_t	j;
	t_env	*temp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(env_array[j]->key, env_array[j + 1]->key) > 0)
			{
				temp = env_array[j];
				env_array[j] = env_array[j + 1];
				env_array[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}
