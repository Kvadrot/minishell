/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:50:44 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/11/25 18:58:41 by mbudkevi         ###   ########.fr       */
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

static char	*join_key_value(char *key, char *value)
{
	int		key_len;
	int		value_len;
	char	*joined;

	key_len = ft_strlen(key);
	value_len = ft_strlen(value);
	joined = malloc(key_len + value_len + 2);
	if (!joined)
		return (NULL);
	ft_strncpy(joined, key, key_len);
	joined[key_len] = '=';
	joined[key_len + 1] = '\0';
	ft_strlcat(joined, value, key_len + value_len + 2);
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
