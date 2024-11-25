/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:54:44 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/11/25 17:20:02 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/** TODO: ft_get_arg_len
* @brief: counts len of given $ARG ($ + amount of signs after it)
* @takes: char * = $ start pointer of our ->$<- ARG
//=======================================================================//
* @HOW_IT_works:
1) iterates while char is alphabetical or numeric + underline
//=======================================================================//
* @returns: (length - $) exmp: $ARG = 3
*/
int	ft_get_arg_len(char *string)
{
	int	len;

	len = 0;
	string++;
	if (string[len++] == '?')
		return (len);
	while (string[len] != '\0' && (ft_isdigit(string[len])
			|| ft_isalpha(string[len]) || string[len] == '_'))
		len++;
	return (len);
}

static char	*ft_prepare_lef_part(int insert_ind,
				char *src, char *insertable_str)
{
	char	*left_part;
	char	*result;

	left_part = NULL;
	result = NULL;
	if (insert_ind > 0)
	{
		left_part = ft_strndup(src, insert_ind);
		if (!left_part)
			return (NULL);
	}
	result = ft_strjoin(left_part, insertable_str);
	if (left_part)
		free(left_part);
	if (!result)
		return (NULL);
	return (result);
}

/** TODO: ft_insert_str
* @brief: inserts strings into dest string according to insert start_index
* @takes: dest - string where to insert,
			int old_part_len lengt of part we are going to crop
			insertable_str - string to insert,
			insert_ind
//=======================================================================//
* @HOW_IT_WORKS:
1) Copies everything to the left from our insert_index if is able to do it
2) Counts the right side (_something)
*  right side = src (******_$ARG_something) - insert_ind(pointer on $)
	- old_part_len
3) Joins left whith insertable_part = result
4) Joins result with right_part
//=======================================================================//
* @returns: new string
*/
char	*ft_insert_str(char *src, int old_part_len, char *insertable_str,
		int insert_ind)
{
	char	*left_part;
	char	*right_part;
	int		right_part_len;
	char	*final_result;

	left_part = ft_prepare_lef_part(insert_ind, src, insertable_str);
	right_part = NULL;
	right_part_len = ft_strlen(src) - insert_ind - old_part_len;
	right_part = ft_strndup(src + insert_ind + old_part_len, right_part_len);
	if (!right_part)
	{
		free(left_part);
		return (NULL);
	}
	final_result = ft_strjoin(left_part, right_part);
	if (!final_result)
	{
		free(left_part);
		free(right_part);
		return (NULL);
	}
	free(left_part);
	free(right_part);
	return (final_result);
}

/** TODO: ft_substitude
* @brief: substitudes values from environment instead of $ARG
* @takes: minishell, source, index - start of substitution
//=======================================================================//
* @HOW_IT_WORKS:
1) Creates duplicate of our $arg
2) iterates through the env list of minishell comparing the keys
3)
* if key matches to the $arg
*  inserts its value instead of $arg
* else if there is no matche
*   cuts out $arg from our full_arg and
//=======================================================================//
* @returns: length of substituted string / or 0 in no match case
*/

char	*create_arg_duplicate(char **full_arg, int start_index)
{
	return (ft_strndup(*full_arg + start_index, ft_get_arg_len(*full_arg
				+ start_index) + 1));
}

int	handle_exit_status_substitution(char **full_arg, int start_index)
{
	char	*insertable_str;
	int		insertable_str_len;
	char	*result;

	result = NULL;
	insertable_str = ft_itoa(g_last_exit_status);
	insertable_str_len = ft_strlen(insertable_str);
	result = ft_insert_str(*full_arg, ft_get_arg_len(*full_arg + start_index)
			+ 1, insertable_str, start_index);
	free(insertable_str);
	if (*full_arg)
		free(*full_arg);
	*full_arg = result;
	return (insertable_str_len);
}
