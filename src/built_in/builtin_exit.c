/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:44:05 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/10/13 14:33:39 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// write exit at the very end as we need to free lots of things
void	builtin_exit(void)
{
	// int condition = 1;

	// if (condition)
	// {
	// 	printf("Exiting the program due to a condition.\n");
	// 	exit(1);
	// }
	// printf("This line will not be executed.\n");
	exit(0);
}