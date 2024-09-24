/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 21:25:27 by itykhono          #+#    #+#             */
/*   Updated: 2024/09/09 19:32:31 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* 
** The strncmp() function compares not more than n characters. Because strncmp()
** is designed for comparing strings rather than binary data, characters that
** appear after a `\0' character are not compared.
** The strncmp() function returns an integer greater than, equal to, or less than
** 0, according as the string s1 is greater than, equal to, or less than the
** string s2. The comparison is done using unsigned characters, so that `\200' is
** greater than `\0'.
 */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	ind;
	size_t	s1len;
	size_t	s2len;

	ind = 0;
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	if (n == 0)
		return (0);
	while (((char *)s1)[ind] != '\0'
		&& ((char *)s2)[ind] != '\0' && ind < n)
	{
		if (((unsigned char *)s1)[ind] != ((unsigned char *)s2)[ind])
			return (((unsigned char *)s1)[ind] - ((unsigned char *)s2)[ind]);
		ind++;
	}
	if (s1len > s2len && ind < n)
		return (0 + ((unsigned char *)s1)[ind]);
	else if (s1len < s2len && ind < n)
		return (0 - ((unsigned char *)s2)[ind]);
	return (0);
}
