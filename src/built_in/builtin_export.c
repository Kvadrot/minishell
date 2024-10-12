/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:44:57 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/10/12 21:20:13 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_valid_for_env(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			if (i > 0 && str[i - 1] != ' ')
				return (1);
			else
				return (0);
		}
		i++;
	}
	return (0);
}

int	key_size(char *str)
{
	int	i;
	
	i = 0;
	while (str[i] != '=')
		i++;
	return (i);
}

int	builtin_export(t_data **minishell)
{
	int		i;
	char	*key;
	int		key_s;

	i = 0;
	if ((*minishell)->commands->args == NULL)
	{
		//declare -x + env
		// return
	}
	while ((*minishell)->commands->args[i])
	{
		if (!ft_isalpha((*minishell)->commands->args[i][0]))
		{
			// ft_printf_full("not a valid identifier", 2, NULL); // zla funkcja
			ft_putstr_fd("not a valid identifier\n", 2);
			return (1);
		}
		if (is_valid_for_env((*minishell)->commands->args[i]))
		{
			key_s = key_size((*minishell)->commands->args[i]);
			key = ft_substr((*minishell)->commands->args[i], 0, key_s);
			add_to_env(minishell, key, ((*minishell)->commands->args[i]) + key_s + 1);
			free(key);
		}
		i++;
	}
	return (0);
}