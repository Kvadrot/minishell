/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 19:45:41 by ssuchane          #+#    #+#             */
/*   Updated: 2024/08/24 20:05:10 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_strncpy(char *dest, char *src, int num)
{
	size_t	i;

	i = 0;
	while (i < num && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < num)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

void	ft_skip_whitespace(char **s)
{
	if (*s)
	{
		while (**s == '\t' || **s == '\n' || **s == '\v' || **s == '\f'
			|| **s == '\r' || **s == ' ')
			(*s)++;
	}
}

bool	ft_is_whitespace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r' || c == ' ')
		return (true);
	return (false);
}
