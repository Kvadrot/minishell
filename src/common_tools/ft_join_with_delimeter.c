/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_with_delimeter.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:47:02 by ufo               #+#    #+#             */
/*   Updated: 2024/11/18 18:31:35 by itykhono         ###   ########.fr       */
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
// char    *ft_join_with_delimeter(char *s1, char *s2, char *delimiter)
// {
// 	char    *temp;
// 	char    *result_str;

// 	temp = NULL;
// 	result_str = NULL;
// 	if (s1 == NULL)
// 	{
// 		result_str = ft_strjoin(s2, delimiter);
// 	} else {
// 		temp = ft_strjoin(s1, s2);
// 		if (!temp)
// 			return (NULL);
// 		result_str = ft_strjoin(temp, delimiter);
// 		free(temp);
// 	}
// 	// if (s1)
// 	// 	free(s1);
// 	// if (s2)
// 	// 	free(s2);
// 	return (result_str);
// }
char	*ft_join_with_delimeter(char *s1, char *s2, char *delimiter)
{
    char *temp;
    char *result_str;

    if (!s2)  // No valid s2 to join
        return (s1 ? ft_strdup(s1) : NULL);  // Return a copy of s1 or NULL

    temp = NULL;
    result_str = NULL;

    if (!s1)  // Handle when s1 is NULL
        result_str = delimiter ? ft_strjoin(s2, delimiter) : ft_strdup(s2);
    else
    {
        temp = delimiter ? ft_strjoin(s1, delimiter) : ft_strdup(s1);
        if (!temp)
            return (NULL);
        result_str = ft_strjoin(temp, s2);
        free(temp);
    }

    return (result_str);
}