/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_string_to_array.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:38:33 by ufo               #+#    #+#             */
/*   Updated: 2024/11/15 15:48:09 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./common_tools.h"

/** TODO: ft_append_argument
* @brief: appends new str to the end of arr
//=======================================================================//
* @HOW_IT_works:
	coppies new_string, allocates mem for it
	allocates mem for result: [[Str]], at the end +2 for new element & NULL
	
//=======================================================================//
* @returns: t_redir	* - obj t_redir || NULL
*/
 char **append_string_to_array(char *new_str, char **args)
{
    int i = 0;
    int old_size = ft_get_size_arr_of_str(args); // Get size of old array
    char **result;

    // Allocate memory for the new array
    result = (char **)malloc(sizeof(char *) * (old_size + 2)); // +1 for new string, +1 for NULL
    if (!result)
        return NULL;

    // Copy existing strings to the new array
    while (i < old_size) {
        result[i] = (char *)malloc(ft_strlen(args[i]) + 1);
        if (!result[i]) {
            while (i-- > 0) // Free previously allocated strings
                free(result[i]);
            free(result);
            return NULL;
        }
        ft_strlcpy(result[i], args[i], ft_strlen(args[i]) + 1); // Copy string
        i++;
    }

    // Add the new string
    result[i] = ft_strdup(new_str);
    if (!result[i]) {
        while (i-- > 0) // Free previously allocated strings
            free(result[i]);
        free(result);
        return NULL;
    }

    // Terminate the array with NULL
    result[i + 1] = NULL;

    // Free old args array and its strings
    if (args) {
        for (int j = 0; args[j]; j++)
            free(args[j]);
        free(args);
    }

    return result;
}
