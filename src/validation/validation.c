/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:52:26 by itykhono          #+#    #+#             */
/*   Updated: 2024/11/23 18:08:50 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	ft_quotes_are_closed(char *str, int *i)
{
	bool	result;
	char	searchable_quote;

	result = true;
	while (str[*i])
	{
		if (str[*i] == '\'' || str[*i] == '\"')
		{
			result = false;
			searchable_quote = str[*i];
			(*i)++;
			while (str[*i])
			{
				if (str[*i] == searchable_quote)
				{
					result = true;
					break ;
				}
				(*i)++;
			}
		}
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
bool	ft_input_is_valid(char *input_str)
{
	int	i;

	i = 0;
	if (input_str[0] == '|')
		return (false);
	else if (ft_quotes_are_closed(input_str, &i) == false)
		return (false);
	else
		return (true);
}
