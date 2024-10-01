/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:20:55 by itykhono          #+#    #+#             */
/*   Updated: 2024/10/01 13:54:15 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>

int ft_printf(const char *format, ...);


int	ft_detect_param(va_list args, char ch, int output_fd);
int	ft_put_chr(char ch, int fd_output);
int	ft_put_str(char *str, int output_fd);
int	ft_is_param_letter(char ch);
int	ft_putnbr(int n, int output_fd);
int	ft_unsigned_putnbr(int unsigned n, int output_fd);
int	ft_print_16_base(int unsigned n, int capitalized, int output_fd);
int	ft_print_ptr(void *ptr, char *base, int output_fd);

#endif