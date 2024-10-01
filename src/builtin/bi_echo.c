/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:07:28 by itykhono          #+#    #+#             */
/*   Updated: 2024/10/01 14:16:09 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int ft_bi_echo(int fd_output, char *flag, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    int result = ft_printf_full(fd_output, format, args);
	if (flag != NULL && ft_strncmp(flag, "-n", ft_strlen("-n")) == 0)
		write(1, "\n", fd_output);
    va_end(args);
    return result;
}