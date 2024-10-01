/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 21:25:27 by itykhono          #+#    #+#             */
/*   Updated: 2024/03/18 20:12:16 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
