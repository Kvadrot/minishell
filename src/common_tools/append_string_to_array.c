/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_string_to_array.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:38:33 by ufo               #+#    #+#             */
/*   Updated: 2024/11/24 16:31:51 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/** TODO: ft_append_argument
* @brief: appends new str to the end of arr
//=======================================================================//
* @HOW_IT_works:
	coppies new_string, allocates mem for it
	allocates mem for result: [[Str]], at the end +2 for new element & NULL
	
//=======================================================================//
* @returns: t_redir	* - obj t_redir || NULL
*/
static void	free_string_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
}

static int	get_array_size(char **args)
{
	int	size;

	size = 0;
	if (args)
	{
		while (args[size])
			size++;
	}
	return (size);
}

static char	**allocate_and_copy(char **args, int old_size)
{
	char	**result;
	int		i;

	result = (char **)malloc(sizeof(char *) * (old_size + 2));
	if (!result)
		return (NULL);
	i = 0;
	while (i < old_size)
	{
		result[i] = ft_strdup(args[i]);
		if (!result[i])
		{
			while (i-- > 0)
			{
				free(result[i]);
				result[i] = NULL;
			}
			free(result);
			result = NULL;
			return (NULL);
		}
		i++;
	}
	return (result);
}

static int	append_new_string(char **result, char *new_str, int old_size)
{
	result[old_size] = ft_strdup(new_str);
	if (!result[old_size])
	{
		while (old_size-- > 0)
		{
			free(result[old_size]);
			result[old_size] = NULL;
		}
		free(result);
		result = NULL;
		return (0);
	}
	result[old_size + 1] = NULL;
	return (1);
}

char	**append_string_to_array(char *new_str, char **args)
{
	int		old_size;
	char	**result;

	old_size = get_array_size(args);
	result = allocate_and_copy(args, old_size);
	if (!result)
		return (NULL);
	if (!append_new_string(result, new_str, old_size))
		return (NULL);
	free_string_array(args);
	return (result);
}
