/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_with_delimeter.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:47:02 by ufo               #+#    #+#             */
/*   Updated: 2024/10/03 15:53:08 by ufo              ###   ########.fr       */
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
char    *ft_join_with_delimeter(char *s1, char *s2, char *delimiter)
{
	char    *temp;
	char    *result_str;

	if (s1 == NULL)
	{
		result_str = ft_strjoin(s2, delimiter);
	} else {
		temp = ft_strjoin(s1, s2);
		if (!temp)
			return (NULL);
		result_str = ft_strjoin(temp, delimiter);
		free(temp);
	}
	return (result_str);
}