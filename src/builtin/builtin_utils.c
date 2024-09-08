/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 16:04:01 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/08 17:56:20 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* void	do_builtin(char **argv)
{
	(void)argv;
	if (strcmp(argv[0], "echo") == 0)
		ft_echo(argv);
	 	if (strcmp(argv[0], "cd") == 0)
			ft_cd(argv);
		if (strcmp(argv[0], "env") == 0)
			ft_env();
		if (strcmp(argv[0], "export") == 0)
			ft_export(argv);
		if (strcmp(argv[0], "pwd") == 0)
			ft_pwd();
		if (strcmp(argv[0], "unset") == 0)
			ft_unset(argv); 
	return ;
}

int	is_builtin(char **argv)
{
	if (strcmp(argv[0], "cd") == 0)
		return (1);
	if (strcmp(argv[0], "echo") == 0)
		return (1);
	if (strcmp(argv[0], "env") == 0)
		return (1);
	if (strcmp(argv[0], "export") == 0)
		return (1);
	if (strcmp(argv[0], "pwd") == 0)
		return (1);
	if (strcmp(argv[0], "unset") == 0)
		return (1);
	return (0);
} */

int	is_builtin_done(char **argv)
{
	int ret;

	ret = 0;
	if (strcmp(argv[0], "cd") == 0)
		return (1);
	if (strcmp(argv[0], "echo") == 0)
		ret = ft_echo(argv);
	if (strcmp(argv[0], "env") == 0)
		return (1);
	if (strcmp(argv[0], "export") == 0)
		return (1);
	if (strcmp(argv[0], "pwd") == 0)
		return (1);
	if (strcmp(argv[0], "unset") == 0)
		return (1);
	return (ret);
}