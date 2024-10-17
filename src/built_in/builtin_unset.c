/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:45:22 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/10/13 14:17:53 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	builtin_unset(t_data **minishell)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = (*minishell)->env;
	if ((*minishell)->commands->args)
	{
		while ((*minishell)->commands->args[i])
		{
			while (tmp != NULL)
			{
				if (ft_strncmp(tmp->key, (*minishell)->commands->args[i], ft_strlen(tmp->key)) == 0)
				{
					delete_node(&(*minishell)->env, tmp);
					break ;
				}
			tmp = tmp->next;
			}
			tmp = (*minishell)->env;
			i++;
		}
	}
}