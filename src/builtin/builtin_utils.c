/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 16:04:01 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/10 18:17:48 by ssuchane         ###   ########.fr       */
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
	{
		if (!minishell->envlist)
			return (0);
		print_environment(minishell->envlist);
		return (1);
	}
	else if (strcmp(argv[0], "export") == 0)
		ret = ft_export(argv, minishell);
	else if (strcmp(argv[0], "pwd") == 0)
		ret = ft_pwd(argv);
	else if (strcmp(argv[0], "unset") == 0)
		ret = ft_unset(argv, minishell);
	else if (strcmp(argv[0], "exit") == 0)
		ret = ft_exit();
	return (ret);
}
