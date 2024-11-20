/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 21:24:45 by marvin            #+#    #+#             */
/*   Updated: 2024/11/20 13:18:54 by itykhono         ###   ########.fr       */
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
		ft_handle_error(true, "Malloc_error, printed in environment_new_node_end", 433, &minishell);
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
				ft_handle_error(true , "unexpected ERROR dup_is_faild, printed by init_environment\n", 422, minishell);
			value = ft_strdup(delimiter_pos + 1);
			if (!value)
				ft_handle_error(true , "unexpected ERROR dup_is_faild, printed by init_environment\n", 423, minishell);

			environment_new_node_end(*minishell, key, value);
			free(key);
			free(value);
		}
		i++;
	}
}

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

void	delete_node(t_env **head, t_env *node_to_delete)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *head;
	prev = NULL;
	// Case 1: If the node to be deleted is the head node
	if (tmp != NULL && tmp == node_to_delete)
	{
		*head = tmp->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		return;
	}
	// Case 2: Search for the node in the rest of the list
	while (tmp != NULL && tmp != node_to_delete)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	// If the node was not found
	if (tmp == NULL)
		return;
	// Unlink the node from the list
	prev->next = tmp->next;
	free(tmp->key);
	free(tmp->value);
	free(tmp);
}

void	add_to_env(t_data **minishell, char *key, char *new_value)
{
	t_env	*tmp;

	tmp = (*minishell)->env;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key)) == 0)
			delete_node(&(*minishell)->env, tmp);
		tmp = tmp->next;
	}
	environment_new_node_end(*minishell, key, new_value);
}