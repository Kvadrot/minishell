/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 20:12:35 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/08/21 22:09:28 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void minishel_free(t_data *minishell, int flag)
{
	t_llist *tmp;

	if (flag == YES)
	{
		ft_putendl_fd("\noutside while\n", STDOUT_FILENO);
		while (minishell->tracker)
		{
			ft_putendl_fd("\ninside while\n", STDOUT_FILENO);
			tmp = minishell->tracker;
			minishell->tracker = minishell->tracker->next;
			free(tmp->content);
			free(tmp);
		}
	}
	exit(0);
}
