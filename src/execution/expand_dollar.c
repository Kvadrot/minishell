/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 19:27:50 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/21 22:00:23 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	remove_quotes(char **str)
{
	int	len;

	if (!str || !*str)
		return ;
	len = ft_strlen(*str);
	if ((len >= 2 && (*str)[0] == '\'' && (*str)[len - 1] == '\'') || (len >= 2
			&& (*str)[0] == '"' && (*str)[len - 1] == '"'))
	{
		ft_memmove(*str, *str + 1, len - 2);
		(*str)[len - 2] = '\0';
	}
}

void	ft_expand_dollar(char **argv, t_data *minishell)
{
	char	*value;

	if (!argv || !*argv)
		return ;
	if (ft_strncmp(*argv, "$?", 2) == 0)
	{
		value = ft_itoa(minishell->exit_status);
		if (value)
		{
			free(*argv);
			*argv = value;
		}
	}
	else if (*argv[0] == '$')
	{
		value = ft_get_envlst_val(*argv + 1, minishell);
		if (value)
		{
			free(*argv);
			*argv = value;
		}
	}
}

void	handle_quotes_dollar(char **argv, t_data *minishell)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		if (argv[i][0] == '"' && argv[i][ft_strlen(argv[i]) - 1] == '"')
		{
			remove_quotes(&argv[i]);
			ft_expand_dollar(&argv[i], minishell);
		}
		else if (argv[i][0] == '\'' && argv[i][ft_strlen(argv[i]) - 1] == '\'')
		{
			remove_quotes(&argv[i]);
		}
		else if (ft_strchr(argv[i], '$'))
		{
			ft_expand_dollar(&argv[i], minishell);
		}
		i++;
	}
}
