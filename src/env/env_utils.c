/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:18:13 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/19 19:14:32 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_env	*ft_envlist_new(char *key, char *value)
{
	t_env	*new;

	new = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = gc_collector(ft_strdup(key), false);
	if (value)
		new->value = gc_collector(ft_strdup(value), false);
	new->next = NULL;
	return (new);
}

void	ft_update_env_list(char *key, char *value, bool yes,
		t_data *minishell)
{
	t_env	*envlist;

	envlist = minishell->envlist;
	while (envlist)
	{
		if (!ft_strcmp(key, envlist->key))
		{
			if (value)
				envlist->value = gc_collector(ft_strdup(value), false);
			return ;
		}
		envlist = envlist->next;
	}
	if (yes)
		ft_envlstadd_back(ft_envlist_new(key, value), minishell);
}

bool	ft_env_entry_exists(char *key, t_data *minishell)
{
	t_env	*envlst;

	envlst = minishell->envlist;
	while (envlst)
	{
		if (!ft_strcmp(key, envlst->key))
			return (true);
		envlst = envlst->next;
	}
	return (false);
}

char	*ft_get_envlst_val(char *key, t_data *minishell)
{
	t_env	*envlst;

	envlst = minishell->envlist;
	while (envlst)
	{
		if (!ft_strcmp(key, envlst->key))
			return (envlst->value);
		envlst = envlst->next;
	}
	return (NULL);
}

void	ft_envlstadd_back(t_env *new, t_data *minishell)
{
	t_env	*curr;

	if (!minishell->envlist)
	{
		minishell->envlist = new;
		return ;
	}
	curr = minishell->envlist;
	while (curr && curr->next)
		curr = curr->next;
	curr->next = new;
}
