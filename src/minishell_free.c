/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 20:12:35 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/08/22 21:04:57 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void minishell_free(t_data *minishell, int flag)
{
	t_llist *tmp;

	if (flag == YES)
	{
		ft_putendl_fd("\noutside while loop, ready to free memory\n", STDOUT_FILENO);
		while (minishell->tracker)
		{
			ft_putendl_fd("\ninside while, freeing pointer\n", STDOUT_FILENO);
			tmp = minishell->tracker;
			minishell->tracker = minishell->tracker->next;
			free(tmp->content);
			free(tmp);
		}
	}
	exit(0);
}
