/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_debuger.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:16:13 by ufo               #+#    #+#             */
/*   Updated: 2024/09/28 16:46:59 by ufo              ###   ########.fr       */
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
        ft_printf("-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n");
        ft_printf("for command command: %s\n", temp_cmd->cmd_name);
        ft_printf("\tredirections:\n");
        while (temp_redir)
        {
            ft_printf("\t\tredir_type = %d\n", temp_redir->type);
            ft_printf("\t\tredir_file_name = %s\n", temp_redir->file_name);
            temp_redir = temp_redir->next;
        }
        ft_printf("\targuments:\n");
        while (temp_cmd->args && temp_cmd->args[args_counter] ){
            ft_printf("\t\t%s\n", temp_cmd->args[args_counter]);
            args_counter++;
        }
        ft_printf("-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n");
        temp_cmd = temp_cmd->next;
    }
}
