/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_bin_cmd_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 20:33:18 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/19 18:36:54 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_exec_error(const char *msg, const char *arg)
{
	write(2, msg, ft_strlen(msg));
	write(2, arg, ft_strlen(arg));
	write(2, "\n", 1);
}

// potentially replace by gc_collector
void	clean_up(char *binary_path, char **paths)
{
	int	i;

	i = 0;
	if (binary_path)
		free(binary_path);
	if (paths)
	{
		while (paths[i] != NULL)
		{
			free(paths[i]);
			i++;
		}
		free(paths);
	}
}
