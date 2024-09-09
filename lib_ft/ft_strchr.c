/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:55:38 by itykhono          #+#    #+#             */
/*   Updated: 2024/09/09 19:30:40 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

/* 
** The strchr() function locates the first occurrence of c (converted to a char)
** in the string pointed to by s. The terminating null character is considered
** to be part of the string; therefore if c is `\0', the functions locate the
** terminating `\0'.
 */
char	*ft_strchr(const char *s, int c)
{
	int		ind;
	char	search_char;

	ind = 0;
	search_char = (char)c;
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	else
	{
		while (s[ind] != '\0')
		{
			if (s[ind] == search_char)
				return ((char *)&s[ind]);
			ind++;
		}
	}
	return (NULL);
}
