/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:23:52 by ssuchane          #+#    #+#             */
/*   Updated: 2024/09/09 19:53:24 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*extract_key_from_argument(char *argument)
{
	char	**key_value;
	char	*key;

	key_value = get_key_and_value(argument);
	if (!key_value)
		return (NULL);
	key = key_value[0];
	free(key_value[1]);
	free(key_value);
	return (key);
}

int	find_and_remove_env(t_env **env_list, const char *key)
{
	t_env	*env;
	t_env	*prev;

	env = *env_list;
	prev = NULL;
	while (env != NULL)
	{
		if (strcmp(key, env->key) == 0)
		{
			if (prev)
				prev->next = env->next;
			else
				*env_list = env->next;
			free(env->key);
			free(env->value);
			free(env);
			return (0);
		}
		prev = env;
		env = env->next;
	}
	return (1);
}

int	ft_unset(char **argv, t_data *minishell)
{
	char	*key;
	int		result;

	if (!argv || !argv[0])
	{
		printf("unset: not enough arguments\n");
		return (1);
	}
	key = extract_key_from_argument(argv[0]);
	if (!key)
		return (0);
	result = find_and_remove_env(&minishell->envlist, key);
	free(key);
	return (result);
}
