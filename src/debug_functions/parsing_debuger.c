/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_debuger.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:16:13 by ufo               #+#    #+#             */
/*   Updated: 2024/09/27 17:09:42 by ufo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
// #include "../../inc/parsing.h"


void ft_debug_parsing(t_data **minishell)
{
    t_command_full *temp_cmd = (*minishell)->commands;
    int i = 0;
    int redir_counter = 0;



    while (temp_cmd)
    {
        int args_counter = 0;
        t_redir *temp_redir = temp_cmd->redir_list_head;
        ft_printf("for command command: %s\n", temp_cmd->cmd_name);
        ft_printf("-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n");
        while (temp_redir)
        {
            ft_printf("redir %d\n", redir_counter);
            ft_printf("redir_type = %d\n", temp_redir->type);
            ft_printf("redir_file_name = %s\n", temp_redir->file_name);
            redir_counter++;
            temp_redir = temp_redir->next;
        }
        
        ft_printf("-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n");
        ft_printf("arguments:\n");
        while (temp_cmd->args[i]){
            ft_printf("%s\n", temp_cmd->args[i]);
            i++;
        }
        ft_printf("==================================\n");
        i++;
        temp_cmd = temp_cmd->next;
    }
}
