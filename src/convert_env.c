/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:50:44 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/11/25 17:56:48 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	get_env_list_size(t_env *env)
{
	int	size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

static char	*join_key_value(const char *key, const char *value)
{
	char	*joined;
	int		len;

	len = strlen(key) + strlen(value) + 2;
	joined = malloc(len);
	if (!joined)
		return (NULL);
	return (joined);
}

char	**convert_env_to_array(t_env *env)
{
	int		size;
	char	**env_array;
	int		i;

	i = 0;
	size = get_env_list_size(env);
	env_array = malloc((size + 1) * sizeof(char *));
	if (!env_array)
		return (NULL);
	while (env)
	{
		env_array[i] = join_key_value(env->key, env->value);
		if (!env_array[i])
		{
			while (i > 0)
				free(env_array[--i]);
			free(env_array);
			return (NULL);
		}
		env = env->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}
