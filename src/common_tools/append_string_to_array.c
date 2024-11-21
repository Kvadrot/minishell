/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_string_to_array.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:38:33 by ufo               #+#    #+#             */
/*   Updated: 2024/11/20 15:46:36 by itykhono         ###   ########.fr       */
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
 static void free_string_array(char **arr) {
    int i = 0;

    if (!arr)
        return;

    while (arr[i]) {
        free(arr[i]);
        arr[i] = NULL;
        i++;
    }
    free(arr);
}

char **append_string_to_array(char *new_str, char **args) {
    int i = 0;
    int old_size = 0;
    char **result;

    // Calculate the size of the old array
    if (args) {
        while (args[old_size])
            old_size++;
    }

    // Allocate memory for the new array
    result = (char **)malloc(sizeof(char *) * (old_size + 2));
    if (!result)
        return NULL;

    // Copy existing strings to the new array
    while (i < old_size) {
        result[i] = ft_strdup(args[i]); // Duplicate string
        if (!result[i]) {
            while (i-- > 0) {
                free(result[i]);
                result[i] = NULL;
            }
            free(result);
            result = NULL;
            return NULL;
        }
        i++;
    }

    // Add the new string to the array
    result[i] = ft_strdup(new_str);
    if (!result[i]) {
        while (i-- > 0) {
            free(result[i]);
            result[i] = NULL;
        }
        free(result);
        result = NULL;
        return NULL;
    }

    // Null-terminate the array
    result[i + 1] = NULL;

    // Free the old array
    free_string_array(args);

    return result;
}
