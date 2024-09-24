/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:01:25 by itykhono          #+#    #+#             */
/*   Updated: 2024/03/18 15:01:53 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *any, int c, size_t len)
{
	size_t	counter;
	char	*casted;

	counter = 0;
	casted = (char *)any;
	while (counter < len)
	{
		casted[counter] = c;
		counter++;
	}
	return (casted);
}
