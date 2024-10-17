/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:21:02 by itykhono          #+#    #+#             */
/*   Updated: 2024/10/17 12:16:51 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_chr(char ch, int fd_out)
{
	write(1, &ch, fd_out);
	return (1);
}

int	ft_detect_param(va_list args, char ch, int fd_out)
{
	if (ch == 'c')
		return (ft_put_chr((char)va_arg(args, int), fd_out));
	else if (ch == 's')
		return (ft_put_str((char *)va_arg(args, char *), fd_out));
	else if (ch == 'd')
		return (ft_putnbr(va_arg(args, int), fd_out));
	else if (ch == 'i')
		return (ft_putnbr(va_arg(args, int), fd_out));
	else if (ch == 'u')
		return (ft_unsigned_putnbr((int unsigned)va_arg(args, int unsigned), fd_out));
	else if (ch == 'x')
		return (ft_print_16_base((int unsigned)va_arg(args, int unsigned), 0, fd_out));
	else if (ch == 'X')
		return (ft_print_16_base((int unsigned)va_arg(args, int unsigned), 1, fd_out));
	else if (ch == '%')
		return (ft_put_chr('%', 1));
	else if (ch == 'p')
		return (ft_print_ptr(va_arg(args, void *), "0123456789abcdef", 1));
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

int ft_printf_full(const char *format, int output_fd, va_list args)
{
    int i;
    long long sym_sum; // Corrected data type for sym_sum
    i = 0;
    sym_sum = 0;

    if (format == NULL || format[0] == '\0') // Check for NULL and empty format
        return (0);

    while (format[i] != '\0')
    {
        if (format[i] == '%' && ft_is_param_letter(format[i + 1]) == 200)
        {
            i++;
            sym_sum += ft_detect_param(args, format[i], output_fd); // Use the next character after '%'
        }
        else
        {
            ft_put_chr(format[i], output_fd);
            sym_sum++;
        }
        i++;
    }
    return (sym_sum);
}

int ft_printf(const char *format, ...)
{
    va_list args;
    va_start(args, format); // Correctly start va_list for ft_printf
    int result = ft_printf_full(format, 1, args); // Pass the arguments correctly
    va_end(args);
    return result;
}

// int	ft_printf(const char *format, ...)
// {
// 	int				i;
// 	int long long	sym_sum;
// 	va_list			args;

// 	i = 0;
// 	sym_sum = 0;
// 	va_start(args, format);
// 	if (format[0] == '\0')
// 		return (0);
// 	while (format[i] != '\0')
// 	{
// 		if (format[i] == '%' && ft_is_param_letter(format[i + 1]) == 200)
// 		{
// 			i++;
// 			sym_sum += ft_detect_param(args, format[i], 1);
// 		}
// 		else
// 		{
// 			ft_put_chr(format[i], 1);
// 			sym_sum++;
// 		}
// 		i++;
// 	}
// 	va_end(args);
// 	return (sym_sum);
// }

