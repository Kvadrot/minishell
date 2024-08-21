/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:04:43 by itykhono          #+#    #+#             */
/*   Updated: 2024/03/18 15:06:37 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	local_size;

	if (!dst || !src)
		return (0);
	local_size = 0;
	if (size < 1)
		return (ft_strlen(src));
	while (src[local_size] != '\0' && local_size < size - 1)
	{
		dst[local_size] = src[local_size];
		local_size++;
	}
	dst[local_size] = '\0';
	return (ft_strlen(src));
}
