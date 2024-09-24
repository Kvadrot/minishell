/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:03:05 by itykhono          #+#    #+#             */
/*   Updated: 2024/09/21 21:59:58 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

	* The ft_isalpha() function checks whether the passed character
	* is an alphabetic character.
 */
int	ft_isalpha(char someChar)
{
	if ((someChar >= 'A' && someChar <= 'Z') || (someChar >= 'a'
			&& someChar <= 'z'))
		return (1);
	else
		return (0);
}
