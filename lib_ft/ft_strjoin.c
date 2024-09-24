/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 20:52:10 by itykhono          #+#    #+#             */
/*   Updated: 2024/09/09 19:46:42 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* 
* Allocates (with malloc(3)) and returns a new string, which is the result of the
* concatenation of ’s1’ and ’s2’.
* Returns NULL if the allocation fails.
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;

	if (!s1 && s2)
		return (ft_strdup(s2));
	else if (s1 && !s2)
		return (ft_strdup(s1));
	else if (!s1 && !s2)
		return ("");
	newstr = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!newstr)
		return (NULL);
	ft_strlcpy(newstr, s1, ft_strlen(s1) + 1);
	ft_strlcat(newstr + ft_strlen(s1), s2, ft_strlen(s2) + 1);
	return (newstr);
}
