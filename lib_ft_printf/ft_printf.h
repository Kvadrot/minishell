/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:20:55 by itykhono          #+#    #+#             */
/*   Updated: 2024/10/17 12:15:52 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>

#define FDOUT 13242

int ft_printf_full(const char *format, int output_fd, va_list args);
int	ft_printf(const char *format, ...);
int	ft_putnbr(int n, int fd_out);
int	ft_put_chr(char ch, int fd_out);
int	ft_put_str(char *str, int fd_out);
int	ft_unsigned_putnbr(int unsigned n, int fd_out);
int	ft_is_param_letter(char ch);
int	ft_detect_param(va_list args, char ch, int fd_out);
int	ft_print_ptr(void *ptr, char *base, int fd_out);
int	ft_print_16_base(int unsigned n, int capitalized, int fd_out);

#endif