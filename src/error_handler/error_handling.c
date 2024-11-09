/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:45:00 by itykhono          #+#    #+#             */
/*   Updated: 2024/11/09 18:05:09 by ufo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void free_command_args(t_command_full *cmd)
{
    if (cmd->args)
    {
        for (int i = 0; cmd->args[i] != NULL; i++)
        {
            free(cmd->args[i]);
        }
        free(cmd->args);
    }
}

void ft_free_token_list(t_tokens *token_list)
{
    t_tokens *temp;
    t_tokens *temp_next;

    if (token_list)
    {
        temp = token_list;
        temp_next = NULL;
        while (temp)
        {
            temp_next = temp->next;
            free(temp->value);
            free(temp);
            temp = temp_next;
        }
    }
}

void ft_free_minishell(t_data **minishell, bool is_crash)
{
    if (*minishell == NULL)
        return;

    // Free input if it exists
    if ((*minishell)->input)
	{
        // free((*minishell)->input);
		(*minishell)->input = NULL;
	}

    // Free environment variables
    if ((*minishell)->env && is_crash)
        environment_free_list((*minishell)->env);

    // Free envir if required
    if ((*minishell)->envir)
        ft_printf("TODO: free envir\n");

    // Free commands if required
    if ((*minishell)->commands)
        ft_printf("TODO: free commands\n");

    // Free tokens
    if ((*minishell)->tokens)
        ft_free_token_list((*minishell)->tokens);
}

void ft_handle_error(bool is_crashable, char *error_text, int err_status, t_data **minishell)
{
    if (error_text)
        ft_printf("ERROR: %s ERR_status: %d\n", error_text, err_status);

    // Free minishell resources before exit if needed
    if (is_crashable)
    {
        ft_free_minishell(minishell, is_crashable);
    	free(*minishell);
   		*minishell = NULL; // Nullify pointer to avoid dangling pointer
        exit(1);  // If crashable, exit the program after freeing
    }
    else
    {
        ft_free_minishell(minishell, is_crashable);
		ft_printf("freeeing ___ \n");
        // Return or continue to next operation
    }
}
