/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:37:33 by itykhono          #+#    #+#             */
/*   Updated: 2024/03/20 15:49:58 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		i;
	int		is_negative;
	char	buffer[12];

	i = 0;
	is_negative = 0;
	if (n == 0)
		return (ft_putchar_fd('0', fd));
	if (n == -2147483648)
		return (ft_putstr_fd("-2147483648", fd));
	if (n < 0)
	{
		is_negative = 1;
		n *= -1;
	}
	while (n > 0)
	{
		buffer[i] = n % 10 + '0';
		n /= 10;
		i++;
	}
	if (is_negative)
		buffer[i++] = '-';
	while (--i >= 0)
		ft_putchar_fd(buffer[i], fd);
}
