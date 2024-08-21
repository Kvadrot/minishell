/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 10:47:14 by itykhono          #+#    #+#             */
/*   Updated: 2024/04/11 14:29:34 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_str(char *str)
{
	int	result;
	int	ind;

	ind = 0;
	result = 0;
	if (str == NULL)
		return (ft_put_str("(null)"));
	while (str[ind] != '\0')
	{
		ft_put_chr(str[ind]);
		result++;
		ind++;
	}
	return (result);
}

int	ft_putnbr(int n)
{
	int		i;
	int		sign;
	char	buffer[12];
	int		result;

	i = 0;
	result = 0;
	sign = 1;
	if (n == 0)
		return (ft_put_chr('0'));
	if (n == -2147483648)
		return (ft_put_str("-2147483648"));
	if (n < 0)
		sign = -1;
	while (n != 0)
	{
		buffer[i++] = (n % 10 * sign) + '0';
		n /= 10;
	}
	if (sign == -1)
		buffer[i++] = '-';
	while (--i >= 0)
		result += ft_put_chr(buffer[i]);
	return (result);
}

int	ft_unsigned_putnbr(int unsigned n)
{
	int		i;
	char	buffer[13];
	int		result;

	i = 0;
	result = 0;
	if (n == 0)
		return (ft_put_chr('0'));
	while (n > 0)
	{
		buffer[i] = n % 10 + '0';
		n /= 10;
		i++;
	}
	while (--i >= 0)
		result += ft_put_chr(buffer[i]);
	return (result);
}

int	ft_print_16_base(int unsigned n, int capitalized)
{
	int		i;
	char	buffer[13];
	int		result;
	char	*base;

	i = 0;
	result = 0;
	if (capitalized == 1)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (n == 0)
		return (ft_put_chr('0'));
	while (n > 0)
	{
		buffer[i] = base[n % 16];
		n /= 16;
		i++;
	}
	while (--i >= 0)
		result += ft_put_chr(buffer[i]);
	return (result);
}

int	ft_print_ptr(void *ptr, char *base)
{
	int			i;
	char		buffer[20];
	int			result;
	uintptr_t	converted_ptr;

	if (ptr == NULL)
	{
		result = ft_put_str("(nil)");
		return (result);
	}
	i = 0;
	result = 0;
	converted_ptr = (uintptr_t)ptr;
	while (converted_ptr > 0)
	{
		buffer[i] = base[converted_ptr % 16];
		converted_ptr /= 16;
		i++;
	}
	result += ft_put_chr('0');
	result += ft_put_chr('x');
	while (--i >= 0)
		result += ft_put_chr(buffer[i]);
	return (result);
}
