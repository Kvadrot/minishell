/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:45:22 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/11/25 17:09:12 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	builtin_unset(t_data **minishell)
{
	int		i;
	t_env	*tmp;

	i = 1;
	if (!(*minishell)->commands->args || !(*minishell)->commands->args[1])
		return (0);
	while ((*minishell)->commands->args[i])
	{
		tmp = (*minishell)->env;
		while (tmp != NULL)
		{
			if (ft_strncmp(tmp->key, (*minishell)->commands->args[i],
					ft_strlen((*minishell)->commands->args[i])) == 0)
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
