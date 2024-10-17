/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_string_to_array.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:38:33 by ufo               #+#    #+#             */
/*   Updated: 2024/10/03 15:39:01 by ufo              ###   ########.fr       */
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
    int old_size = ft_get_size_arr_of_str(args); // Assuming this returns the length of the array
    char **result;

    // Allocate memory for the new array
    result = (char **)malloc(sizeof(char *) * (old_size + 2)); // +1 for new string, +1 for NULL
    if (!result) {
        return NULL; // Check for allocation failure
    }

    // Copy existing strings to the new array
    while (i < old_size) {
        // Allocate memory for each string in the new array
        result[i] = (char *)malloc(ft_strlen(args[i]) + 1); // +1 for null terminator
        if (!result[i]) {
            // Free already allocated memory if any malloc fails
            while (i-- > 0)
                free(result[i]);
            free(result);
            return NULL;
        }

        // Copy the string from the old array to the new array
        ft_strlcpy(result[i], args[i], ft_strlen(args[i]) + 1); // Include null terminator
        i++;
    }

    // Add the new string
    result[i] = ft_strdup(new_str); // Duplicate the new string
    if (!result[i]) {
        free(result); // Free the new array if strdup fails
        return NULL;
    }

    // Terminate the array with NULL
    result[i + 1] = NULL;

    // Free the old args array if it was allocated
    free(args);

    return (result); // Return the new array
}