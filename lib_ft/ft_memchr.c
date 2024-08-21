/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:51:00 by itykhono          #+#    #+#             */
/*   Updated: 2024/03/08 13:36:09 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			counter;
	unsigned char	searchchr;

	counter = 0;
	searchchr = (unsigned char)c;
	while (counter < n)
	{
		if (((unsigned char *)s)[counter] == searchchr)
		{
			return ((void *)&((const unsigned char *)s)[counter]);
		}
		counter++;
	}
	return (NULL);
}
