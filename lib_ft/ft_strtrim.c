/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:52:07 by itykhono          #+#    #+#             */
/*   Updated: 2024/03/20 16:11:51 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		s1_counter;
	char		*result;

	if (ft_strlen(set) == 0)
		return (ft_strdup(s1));
	s1_counter = 0;
	while (ft_strchr(set, s1[s1_counter]) && s1[s1_counter] != '\0')
		s1_counter++;
	s1 += s1_counter;
	if (ft_strlen(s1) == 0)
		return (ft_strdup(""));
	s1_counter = ft_strlen(s1) - 1;
	while (s1_counter > 0 && ft_strchr(set, s1[s1_counter]))
		s1_counter--;
	if (s1_counter == ft_strlen(s1) - 1)
		return (ft_strdup(s1));
	result = ft_substr(s1, 0, s1_counter + 1);
	return (result);
}
