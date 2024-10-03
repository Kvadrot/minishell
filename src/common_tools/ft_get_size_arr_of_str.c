/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_size_arr_of_str.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:36:47 by ufo               #+#    #+#             */
/*   Updated: 2024/10/03 15:38:08 by ufo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./common_tools.h"

/** TODO: ft_get_size_arr_of_str
* @brief: Countd lrngth ARR OF STRINGS
//=======================================================================//
//=======================================================================//
* @returns: amount of strings inside: int
*/
int	ft_get_size_arr_of_str(char **arr_of_str)
{
	int	result;

	result = 0;

	if (!arr_of_str)
		return (result);
	while (arr_of_str[result] != NULL)
	{
		result++;
	}
	return (result);
}
