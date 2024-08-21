/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:55:38 by itykhono          #+#    #+#             */
/*   Updated: 2024/03/18 20:09:19 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

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
