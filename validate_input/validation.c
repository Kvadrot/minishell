/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:52:26 by itykhono          #+#    #+#             */
/*   Updated: 2024/08/21 16:16:51 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	ft_quotes_are_closed(char *str, int *i)
{
	bool	result;
	char	searchable_quote;

	result = true;
	while (ft_strlen(str) > i)
	{
		if (str[*i] == '\'' || str[*i] == '\"' )
		{
			result = false;
			searchable_quote = str[*i];
			while (ft_strlen(str) > *i)
			{
				if (str[*i] == searchable_quote)
				{
					result = true;
					break;
				}
				(*i)++;
			}
		} else
			(*i)++;
	}
	
	return (result); 
}

/** TODO: ft_input_is_valid
* @brief: returns wether the input to minishell is valid 
//=======================================================================//
* @HOW_IT_works:
	// check if first element is | or ; returns false
	// look through the entire input for " or ' signs
	// until the first met sign is met again the status is false
	// repeat until the end of input.
	// check if last element is | or ; returns false
//=======================================================================//
* @returns: 
*/
bool	ft_input_is_valid(char **argv, int argc)
{
	int		i;
	bool	result;
	char	searchable_quote;

	i = 0;
	
	if (ft_quotes_are_closed(argv[1], &i) == false)
		return (false);
	
	return (result);
}