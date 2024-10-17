/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:24:51 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/10/13 12:12:36 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	builtin_pwd(void)
{
	char	cwd[13286];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_putstr_fd(cwd, 1);
	else
	{
		ft_putstr_fd("getcwd() in ft_bi_pwd error\n", 2);
		return (1);
	}
	return (0);
}