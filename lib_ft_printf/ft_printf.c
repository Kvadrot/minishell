/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:21:02 by itykhono          #+#    #+#             */
/*   Updated: 2024/08/05 23:16:41 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_chr(char ch)
{
	write(1, &ch, 1);
	return (1);
}

int	ft_detect_param(va_list args, char ch)
{
	if (ch == 'c')
		return (ft_put_chr((char)va_arg(args, int)));
	else if (ch == 's')
		return (ft_put_str((char *)va_arg(args, char *)));
	else if (ch == 'd')
		return (ft_putnbr(va_arg(args, int)));
	else if (ch == 'i')
		return (ft_putnbr(va_arg(args, int)));
	else if (ch == 'u')
		return (ft_unsigned_putnbr((int unsigned)va_arg(args, int unsigned)));
	else if (ch == 'x')
		return (ft_print_16_base((int unsigned)va_arg(args, int unsigned), 0));
	else if (ch == 'X')
		return (ft_print_16_base((int unsigned)va_arg(args, int unsigned), 1));
	else if (ch == '%')
		return (ft_put_chr('%'));
	else if (ch == 'p')
		return (ft_print_ptr(va_arg(args, void *), "0123456789abcdef"));
	else
		return (0);
}

int	ft_is_param_letter(char ch)
{
	int		ind;
	char	*param_arr;

	param_arr = "cspdiuxX%";
	ind = 0;
	while (param_arr[ind] != '\0')
	{
		if (param_arr[ind] == ch)
			return (200);
		ind++;
	}
	return (-404);
}

int	ft_printf(const char *format, ...)
{
	int				i;
	int long long	sym_sum;
	va_list			args;

	i = 0;
	sym_sum = 0;
	va_start(args, format);
	if (format[0] == '\0')
		return (0);
	while (format[i] != '\0')
	{
		if (format[i] == '%' && ft_is_param_letter(format[i + 1]) == 200)
		{
			i++;
			sym_sum += ft_detect_param(args, format[i]);
		}
		else
		{
			ft_put_chr(format[i]);
			sym_sum++;
		}
		i++;
	}
	va_end(args);
	return (sym_sum);
}
