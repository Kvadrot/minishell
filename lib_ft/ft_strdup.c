/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:02:29 by itykhono          #+#    #+#             */
/*   Updated: 2024/09/03 17:49:01 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Allocates sufficient memory for a copy of the string s1, does the copy,
	and returns a pointer to it. The pointer may subsequently be used as an 
	argument to the function free(3). If insufficient memory is available,
	NULL is returned and errno is set to ENOMEM.*/
char	*ft_strdup(const char *s)
{
	char	*newstr;
	char	*start;

	newstr = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!newstr)
		return (NULL);
	start = newstr;
	while (*s)
	{
		*newstr++ = *s++;
	}
	*newstr = '\0';
	return (start);
}
