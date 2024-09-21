/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:46:30 by itykhono          #+#    #+#             */
/*   Updated: 2024/09/21 18:06:15 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*

	* The ft_isalnum() function checks whether the passed character is an
	alphanumeric character.
 */
int	ft_isalnum(char  s)
{
	if (ft_isalpha(s) || ft_isdigit(s))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
