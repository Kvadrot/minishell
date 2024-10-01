/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 21:24:45 by marvin            #+#    #+#             */
/*   Updated: 2024/09/17 16:24:44 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_env	*environment_new_node(char *key, char *value)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	return (new_node);
}

void	environment_new_node_end(t_data *minishell, char *key, char *value)
{
	t_env	*new_node;
	t_env	*current;

	new_node = environment_new_node(key, value);
	if (!new_node)
	{
		ft_handle_error(true, "Malloc_error, printed in environment_new_node_end", 433, minishell);
	}
	if (minishell->env == NULL)
		minishell->env = new_node;
	else
	{
		current = minishell->env;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}

void	init_environment(t_data **minishell, char **envir)
{
	char	*key;
	char	*value;
	char	*delimiter_pos;
	int		i;

	(*minishell)->env = NULL;
	i = 0;

	while (envir[i])
	{
		delimiter_pos = ft_strchr(envir[i], '=');
		if (delimiter_pos != NULL)
		{
			key = ft_strndup(envir[i], delimiter_pos - envir[i]);
			if (!key)
				ft_handle_error(true , "unexpected ERROR dup_is_faild, printed by init_environment\n", 422, *minishell);
			value = ft_strdup(delimiter_pos + 1);
			if (!value)
				ft_handle_error(true , "unexpected ERROR dup_is_faild, printed by init_environment\n", 423, *minishell);
			// environment_new_node_end((*minishell)->env, key, value);

			environment_new_node_end(*minishell, key, value);

			free(key);
			free(value);
		}
		i++;
	}
}

// function to free the list
void	environment_free_list(t_env *head)
{
	t_env	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

// tester function
void	print_environment(t_env *node)
{
	t_env	*current;

	current = node;
	while (current != NULL)
	{
		printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}