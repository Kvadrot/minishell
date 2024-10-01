/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:21:02 by itykhono          #+#    #+#             */
/*   Updated: 2024/10/01 14:06:04 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_chr(char ch, int fd_output)
{
	write(1, &ch, fd_output);
	return (1);
}

int	ft_detect_param(va_list args, char ch, int output_fd)
{
	if (ch == 'c')
		return (ft_put_chr((char)va_arg(args, int), output_fd));
	else if (ch == 's')
		return (ft_put_chr((char)va_arg(args, int), output_fd));
	else if (ch == 'd')
		return (ft_put_chr((char)va_arg(args, int), output_fd));
	else if (ch == 'i')
		return (ft_putnbr(va_arg(args, int), output_fd));
	else if (ch == 'u')
		return (ft_unsigned_putnbr((int unsigned)va_arg(args, int unsigned), output_fd));
	else if (ch == 'x')
		return (ft_print_16_base((int unsigned)va_arg(args, int unsigned), 0, output_fd));
	else if (ch == 'X')
		return (ft_print_16_base((int unsigned)va_arg(args, int unsigned), 1, output_fd));
	else if (ch == '%')
		return (ft_put_chr('%', output_fd));
	else if (ch == 'p')
		return (ft_print_ptr(va_arg(args, void *), "0123456789abcdef", output_fd));
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

int	ft_printf_full(int output_fd, const char *format, ...)
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
			sym_sum += ft_detect_param(args, format[i], output_fd);
		}
		else
		{
			ft_put_chr(format[i], output_fd);
			sym_sum++;
		}
		i++;
	}
	va_end(args);
	return (sym_sum);
}

int ft_printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    int result = ft_printf_full(1, format, args);
    va_end(args);
    return result;
}
