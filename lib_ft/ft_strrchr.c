/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 20:34:04 by itykhono          #+#    #+#             */
/*   Updated: 2024/03/18 20:07:13 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	search_char;
	int		slen;

	search_char = (char)c;
	slen = ft_strlen(s);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	else
	{
		while (slen >= 0)
		{
			if (s[slen] == search_char)
				return ((char *)&s[slen]);
			slen--;
		}
	}
	return (NULL);
}
