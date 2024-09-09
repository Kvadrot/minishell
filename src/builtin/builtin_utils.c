/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 16:04:01 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/09 21:01:00 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_builtin_done(char **argv, t_data *minishell)
{
	int ret;

	(void)minishell;
	ret = 0;
	if (strcmp(argv[0], "cd") == 0)
		return (1);
	else if (strcmp(argv[0], "echo") == 0)
		ret = ft_echo(argv);
	else if (strcmp(argv[0], "env") == 0)
		// ret = ft_env();
		ret = 1;
	else if (strcmp(argv[0], "export") == 0)
		ret = ft_export(argv, minishell);
	else if (strcmp(argv[0], "pwd") == 0)
		ret = ft_pwd(argv);
	else if (strcmp(argv[0], "unset") == 0)
		ret = ft_unset(argv, minishell);
	return (ret);
}