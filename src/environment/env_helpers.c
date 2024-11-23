/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:17:46 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/11/23 18:21:32 by mbudkevi         ###   ########.fr       */
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
		ft_handle_error(true, "Malloc_error, in environment_new_node_end\n",
			433, &minishell);
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