/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:07:28 by itykhono          #+#    #+#             */
/*   Updated: 2024/10/02 11:22:29 by ufo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void    ft_bi_echo(t_command_full *cmd)
{
    int i;
    i = 0;
    if (cmd->args)
    {
        if (ft_strncmp(cmd->args[0], "-n", ft_strlen("-n")) == 0)
            i++;
        while (cmd->args[i] != NULL)
        {

            ft_printf_full(cmd->args[i], cmd->fd_out, NULL);
            ft_printf(" ");
            i++;
        }
    }
    if (cmd->args && ft_strncmp(cmd->args[0], "-n", ft_strlen("-n")) != 0)
    {
        ft_printf_full( "\n", cmd->fd_out, NULL);
    }
}

