/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:30:12 by itykhono          #+#    #+#             */
/*   Updated: 2024/03/17 16:35:21 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result_str;
	unsigned int	i;

	if (!s)
		return (NULL);
	result_str = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!result_str)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		result_str[i] = f(i, s[i]);
		i++;
	}
	return (result_str);
}
