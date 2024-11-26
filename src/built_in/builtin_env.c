/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:25:18 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/11/20 15:22:31 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	builtin_env(t_env *node)
{
	t_env	*current;

	current = node;
	if (!current)
	{
		ft_putstr_fd("some issues with env", 2);
		return (1);
	}
	while (current != NULL)
	{
		ft_printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	return (0);
}
