/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:45:22 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/11/20 15:37:33 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	builtin_unset(t_data **minishell)
{
	int i;
	t_env *tmp;

	if (!(*minishell)->commands->args || !(*minishell)->commands->args[1])
		return (0);
	i = 1;
	while ((*minishell)->commands->args[i])
	{
		tmp = (*minishell)->env;
		while (tmp != NULL)
		{
			if (ft_strncmp(tmp->key, (*minishell)->commands->args[i],
					ft_strlen((*minishell)->commands->args[i]) + 1) == 0)
			{
				delete_node(&(*minishell)->env, tmp);
				break ;
			}
			tmp = tmp->next;
		}
		i++;
	}
	return (0);
}
