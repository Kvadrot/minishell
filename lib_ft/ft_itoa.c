/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 14:34:14 by itykhono          #+#    #+#             */
/*   Updated: 2024/03/18 14:51:19 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_res_len(int initial_num)
{
	int	str_len;

	str_len = 0;
	if (initial_num < 0)
	{
		str_len += 1;
		initial_num *= -1;
	}
	while (initial_num / 10 > 0)
	{
		initial_num /= 10;
		str_len++;
	}
	str_len++;
	return (str_len);
}

char	*ft_itoa(int n)
{
	char	*result_str;
	int		result_len;
	int		sign;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	result_len = ft_get_res_len(n);
	sign = 1;
	if (n < 0)
		sign = -1;
	n *= sign;
	result_str = ft_calloc(result_len + 1, sizeof(char));
	if (!result_str)
		return (NULL);
	while (result_len > 0)
	{
		result_str[result_len - 1] = (n % 10) + 48;
		result_len--;
		n /= 10;
	}
	if (sign == -1)
		result_str[0] = '-';
	return (result_str);
}
