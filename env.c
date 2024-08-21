/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 21:24:45 by marvin            #+#    #+#             */
/*   Updated: 2024/08/20 21:24:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// pass minishell->environment

t_env *environment_new_node(char *key, char *value)
{
    t_env *new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
    if (!new_node)
        return (NULL);
    new_node->key = ft_strdup(key);
    new_node->value = ft_strdup(value);
    new_node->next = NULL;
    
    return (new_node);
}

void environment_new_node_end(t_env **head, char *key, char *value)
{
    t_env *new_node;
	t_env *current;

	new_node = environment_new_node(key, value);
    if (!new_node)
        return ;
    if (*head == NULL)
        *head = new_node;
    else
    {
        current = *head;
        while (current->next != NULL)
            current = current->next;
        current->next = new_node;
    }
}

void	init_environment(char **env)
{
	t_env	*environment;
    char	*key;
    char	*value;
	char	*delimiter_pos;
	int		i;

	environment = NULL;
	i = 0;
	while (env[i])
	{
        delimiter_pos = ft_strchr(env[i], '=');
        if (delimiter_pos != NULL)
        {
            key = strndup(env[i], delimiter_pos - env[i]);
			if (!key)
				//
            value = strdup(delimiter_pos + 1);
			if (!value)
				//
            environment_new_node_end(&environment, key, value);
            free(key);
            free(value);
        }
        i++;
	}
}


// function to free the list
void environment_free_list(t_env *head)
{
    t_env *tmp;
    
    while (head)
    {
        tmp = head;
        head = head->next;
        free(tmp->key);
        free(tmp->value);
        free(tmp);
    }
}