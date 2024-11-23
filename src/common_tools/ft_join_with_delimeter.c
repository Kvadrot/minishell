/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_with_delimeter.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:47:02 by ufo               #+#    #+#             */
/*   Updated: 2024/11/23 17:12:28 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./common_tools.h"

/** TODO: ft_join_with_delimeter
* @brief: merges s1 + delimiter + s2 + delimiter
//=======================================================================//
* @HOW_IT_works:
	1) result = s1 + delim
    2) result = result + s2
	3) result = result + delim
	in case s1 = NULL:
    result = s2 + delim
//=======================================================================//
* @returns: char * - pointer to the new merged str
*/

static char	*handle_null_s1_or_s2(char *s1, char *s2, char *delimiter)
{
	if (!s2)
	{
		if (s1)
			return (ft_strdup(s1));
		return (NULL);
	}
	if (!s1)
	{
		if (delimiter)
			return (ft_strjoin(s2, delimiter));
		return (ft_strdup(s2));
	}
	return (NULL);
}

char	*ft_join_with_delimeter(char *s1, char *s2, char *delimiter)
{
	char	*temp;
	char	*result_str;

	result_str = handle_null_s1_or_s2(s1, s2, delimiter);
	if (result_str)
		return (result_str);
	temp = NULL;
	if (delimiter)
		temp = ft_strjoin(s1, delimiter);
	else
		temp = ft_strdup(s1);
	if (!temp)
		return (NULL);
	result_str = ft_strjoin(temp, s2);
	free(temp);
	temp = NULL;
	if (!result_str)
		return (NULL);
	return (result_str);
}
