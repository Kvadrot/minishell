/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 19:45:41 by ssuchane          #+#    #+#             */
/*   Updated: 2024/09/09 19:38:47 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* 
** The strncpy() function copies at most num characters from the string pointed
** to by src (including the terminating `\0' character) to the array pointed to
** by dest. If num is less than the length of src, a null character is written
** to dest immediately after the last character written. If num is greater than
** the length of src, the destination string is padded with null characters up
** to length num. The strncpy() function returns the value of dest.
 */
char	*ft_strncpy(char *dest, char *src, int num)
{
	int	i;

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
