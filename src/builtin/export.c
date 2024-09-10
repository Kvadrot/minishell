/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:23:52 by ssuchane          #+#    #+#             */
/*   Updated: 2024/09/10 17:47:27 by ssuchane         ###   ########.fr       */
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
			if (strcmp(env_array[j]->key, env_array[j + 1]->key) > 0)
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
		if (strcmp(key_value[0], env->key) == 0)
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
	int i;
	int result;

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