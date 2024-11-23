/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 21:24:45 by marvin            #+#    #+#             */
/*   Updated: 2024/11/23 18:18:49 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
				ft_handle_error(true, "dup failed init_env\n", 422, minishell);
			value = ft_strdup(delimiter_pos + 1);
			if (!value)
				ft_handle_error(true, "dup failed init_env\n", 423, minishell);
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
	if (tmp != NULL && tmp == node_to_delete)
	{
		*head = tmp->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		return ;
	}
	while (tmp != NULL && tmp != node_to_delete)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return ;
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
