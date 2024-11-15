/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:44:05 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/11/15 15:53:52 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// write exit at the very end as we need to free lots of things
void	builtin_exit(t_data **minishell)
{
	// int condition = 1;

	// if (condition)
	// {
	// 	printf("Exiting the program due to a condition.\n");
	// 	exit(1);
	// }
	// printf("This line will not be executed.\n");
	ft_free_minishell(minishell, true);
	exit(0);
}