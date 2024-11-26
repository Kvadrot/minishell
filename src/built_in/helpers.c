/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:46:44 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/11/22 18:51:13 by mbudkevi         ###   ########.fr       */
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

/** TODO: sort_env_list
* @brief: to sort env list in ascending order by 'key'
* @takes: environment
//=======================================================================//
* @HOW_IT_works:
// If the list is empty or has only one element, it's already sorted
// Compare the keys and swap if necessary
// Mark that we made a swap
// Reduce the range for the next pass
//=======================================================================//
* @returns: void
*/

void	sort_env_list(t_env **head)
{
	int		swapped;
	t_env	*ptr1;
	t_env	*lptr;

	lptr = NULL;
	swapped = 1;
	if (*head == NULL || (*head)->next == NULL)
		return ;
	while (swapped)
	{
		swapped = 0;
		ptr1 = *head;
		while (ptr1->next != lptr)
		{
			if (ft_strcmp(ptr1->key, ptr1->next->key) > 0)
			{
				swap(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
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
