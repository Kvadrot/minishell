/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:30:02 by ufo               #+#    #+#             */
/*   Updated: 2024/10/19 14:43:00 by ufo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


int    ft_strcmp(const char *str1, const char *str2)
{
    while (*str1 && *str2 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}