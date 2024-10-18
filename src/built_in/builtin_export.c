/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:44:57 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/10/17 12:54:12 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	swap(t_env *a, t_env *b)
{
	char	*temp_key;
	char	*temp_value;

	temp_key = a->key;
	temp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = temp_key;
	b->value = temp_value;
}

// Function to sort the environment list in ascending order by 'key'
void	sort_env_list(t_env **head)
{
	int		swapped;
	t_env	*ptr1;
	t_env	*lptr;
	
	lptr = NULL;
	swapped = 1;
	// If the list is empty or has only one element, it's already sorted
	if (*head == NULL || (*head)->next == NULL)
		return;
	while (swapped)
	{
		swapped = 0; // Reset swapped for this iteration
		ptr1 = *head;
		while (ptr1->next != lptr)
		{
			// Compare the keys and swap if necessary
			if (ft_strcmp(ptr1->key, ptr1->next->key) > 0)
			{
				swap(ptr1, ptr1->next);
				swapped = 1; // Mark that we made a swap
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1; // Reduce the range for the next pass
	}
}

char	*format_env_entry(t_env *node)
{
	char	*prefix;
	char	*equal_sign;
	char	*temp1;
	char	*temp2;
	char	*result;

	prefix = "declare -x ";
	equal_sign = "=";
	temp1 = ft_strjoin(prefix, node->key);
	temp2 = ft_strjoin(temp1, equal_sign);
	free(temp1);
	result = ft_strjoin(temp2, node->value);
	free(temp2);
	return (result);
}

void	export_no_args(t_data **minishell)
{
	t_env	*tmp;
	char	*key_value;
	char	*formatted;

	sort_env_list(&((*minishell)->env));
	tmp = (*minishell)->env;
	while (tmp != NULL)
	{
		formatted = format_env_entry(tmp);
		if (formatted)
		{
			printf("%s\n", formatted);
			free(formatted);
		}
		tmp = tmp->next;
	}
}

bool	is_valid_for_env(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			if (i > 0 && str[i - 1] != ' ')
				return (1);
			else
				return (0);
		}
		i++;
	}
	return (0);
}

int	key_size(char *str)
{
	int	i;
	
	i = 0;
	while (str[i] != '=')
		i++;
	return (i);
}

int	builtin_export(t_data **minishell)
{
	int		i;
	char	*key;
	int		key_s;

	i = 0;
	if ((*minishell)->commands->args == NULL)
	{
		export_no_args(minishell);
		return (0);
	}
	while ((*minishell)->commands->args[i])
	{
		if (!ft_isalpha((*minishell)->commands->args[i][0]))
		{
			//ft_printf_full("not a valid identifier", 2, NULL); // zla funkcja
			ft_putstr_fd("not a valid identifier\n", 2);
			return (1);
		}
		if (is_valid_for_env((*minishell)->commands->args[i]))
		{
			key_s = key_size((*minishell)->commands->args[i]);
			key = ft_substr((*minishell)->commands->args[i], 0, key_s);
			add_to_env(minishell, key, ((*minishell)->commands->args[i]) + key_s + 1);
			free(key);
		}
		i++;
	}
	return (0);
}