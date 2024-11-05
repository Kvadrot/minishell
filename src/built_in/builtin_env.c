/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:25:18 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/10/12 13:20:31 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// with no options or args

int		builtin_env(t_env *node)
{
	t_env	*current;

	current = node;
	if (!current)
	{
		ft_printf_full("some issues with env", 2, NULL);
		return (-1);
	}
	while (current != NULL)
	{
		printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	return (0);
}