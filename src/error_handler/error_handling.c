/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:45:00 by itykhono          #+#    #+#             */
/*   Updated: 2024/11/18 13:35:36 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// void ft_free_redir_list(t_command_full **cmd)
// {
// 	t_redir	*temp_redir;
// 	t_redir	*pt_holder;

// 	if ((*cmd)->redir_list_head)
// 	{
// 		temp_redir = (*cmd)->redir_list_head;
// 		while (temp_redir)
// 		{
// 			pt_holder = temp_redir->next;
// 			if (temp_redir->file_name)
// 				free(temp_redir->file_name);
// 			if (temp_redir->fd)
// 				free(temp_redir->fd);
// 			if (temp_redir->value)
// 				free(temp_redir->value);
// 			free(temp_redir);
// 			temp_redir = pt_holder;
// 		}
// 		(*cmd)->redir_list_head = NULL;
// 		ft_printf("redir clean up\n");
// 	}
// }


// void free_command_args(t_command_full *cmd)
// {
//     if (cmd->args)
//     {
//         for (int i = 0; cmd->args[i] != NULL; i++)
//         {
//             free(cmd->args[i]);
//         }
//         free(cmd->args);
// 		cmd->args = NULL;
//     }
// 	ft_printf("free_command_args clean up\n");
// }

// void ft_free_token_list(t_tokens **token_list)
// {
//     t_tokens *temp;
//     t_tokens *temp_next;

//     if (*token_list)
//     {
//         temp = *token_list;
//         temp_next = NULL;
//         while (temp)
//         {
//             temp_next = temp->next;
//             free(temp->value);
//             free(temp);
//             temp = temp_next;
//         }
//     }
// 	// free(token_list);
// 	token_list = NULL;
// 	ft_printf("token list clean up\n");
// }

// void	ft_free_commands(t_data **minishell)
// {
// 	t_command_full *temp_cmd;
// 	t_command_full *cmd_pt_holder;

// 	temp_cmd = (*minishell)->commands;
// 	while (temp_cmd != NULL)
// 	{
// 		cmd_pt_holder = temp_cmd->next;
// 		ft_free_redir_list(&temp_cmd);
// 		free_command_args(temp_cmd);
// 		if (temp_cmd->here_doc)
// 			free(temp_cmd->here_doc);
// 		if (temp_cmd->cmd_name)
// 			free(temp_cmd->cmd_name);
// 		temp_cmd = cmd_pt_holder; 
// 	}
// 	// free((*minishell)->commands);
// 	// (*minishell)->commands = NULL;
// }

// void ft_free_minishell(t_data **minishell, bool is_crash)
// {
//     if (*minishell == NULL)
//         return;

//     // Free input if it exists
//     if ((*minishell)->input)
// 	{
//         // free((*minishell)->input);
// 		(*minishell)->input = NULL;
// 	}

// 	// Free tokens
//     if ((*minishell)->tokens)
//         ft_free_token_list(&((*minishell)->tokens));

//     // Free environment variables
//     if ((*minishell)->env && is_crash)
//         environment_free_list((*minishell)->env);

//     // Free envir if required
//     if ((*minishell)->envir)
//         ft_printf("TODO: free envir\n");

//     // Free commands if required
//     if ((*minishell)->commands)
// 	{
// 		ft_free_commands(minishell);	
// 	}
// }

// void ft_handle_error(bool is_crashable, char *error_text, int err_status, t_data **minishell)
// {
//     if (error_text)
//         ft_printf("ERROR: %s ERR_status: %d\n", error_text, err_status);

//     // Free minishell resources before exit if needed
//     if (is_crashable)
//     {
//         ft_free_minishell(minishell, is_crashable);
//     	free(*minishell);
//         exit(1);
//     }
//     else
//     {
//         ft_free_minishell(minishell, is_crashable);
// 		ft_printf("freeeing ___ \n");
//         // Return or continue to next operation
//     }
// }


#include "../inc/minishell.h"

void ft_free_redir_list(t_command_full **cmd)
{
    t_redir *temp_redir;
    t_redir *pt_holder;

    if ((*cmd)->redir_list_head)
    {
        temp_redir = (*cmd)->redir_list_head;
        while (temp_redir)
        {
            pt_holder = temp_redir->next;
            if (temp_redir->file_name)
                free(temp_redir->file_name);
            if (temp_redir->fd)
                free(temp_redir->fd);  // Only free if `fd` was dynamically allocated
            if (temp_redir->value)
                free(temp_redir->value);
            free(temp_redir);
            temp_redir = pt_holder;
        }
        (*cmd)->redir_list_head = NULL;
        ft_printf("redir clean up\n");
    }
}

void free_command_args(t_command_full *cmd)
{
    if (cmd->args)
    {
        for (int i = 0; cmd->args[i] != NULL; i++)
        {
            free(cmd->args[i]);
        }
        free(cmd->args);
        cmd->args = NULL;
    }
    ft_printf("free_command_args clean up\n");
}

void ft_free_commands(t_data **minishell)
{
    t_command_full *temp_cmd;
    t_command_full *cmd_pt_holder;

    temp_cmd = (*minishell)->commands;
    while (temp_cmd != NULL)
    {
        cmd_pt_holder = temp_cmd->next;
        ft_free_redir_list(&temp_cmd);
        free_command_args(temp_cmd);
        if (temp_cmd->here_doc)
            free(temp_cmd->here_doc);
        if (temp_cmd->cmd_name)
            free(temp_cmd->cmd_name);
        free(temp_cmd);
        temp_cmd = cmd_pt_holder; 
    }
    // Free commands list pointer if dynamically allocated
    free((*minishell)->commands);
    (*minishell)->commands = NULL;
    ft_printf("commands clean up\n");
}

void ft_free_token_list(t_tokens **token_list)
{
    t_tokens *temp;
    t_tokens *temp_next;

    if (*token_list)
    {
        temp = *token_list;
        temp_next = NULL;
        while (temp)
        {
            temp_next = temp->next;
            if (temp->value)  // Check if value exists before freeing
                free(temp->value);
            free(temp);
            temp = temp_next;
        }
        *token_list = NULL;  // Nullify the list pointer
    }
}




void ft_free_minishell(t_data **minishell, bool is_crash)
{
    if (*minishell == NULL)
        return;

    // Free input if it exists and was dynamically allocated
    if ((*minishell)->input)
    {
        free((*minishell)->input);
		(*minishell)->input = NULL;
	}

	// Free tokens if they exist
    if ((*minishell)->tokens)
        ft_free_token_list(&((*minishell)->tokens));

    // Free environment variables if required
    if ((*minishell)->env && is_crash)
        environment_free_list((*minishell)->env);

    // Free envir if required (TODO: Implement this part)
    if ((*minishell)->envir)
        ft_printf("TODO: free envir\n");

    // Free commands if required
    if ((*minishell)->commands)
	{
		ft_free_commands(minishell);
	}
}

void ft_handle_error(bool is_crashable, char *error_text, int err_status, t_data **minishell)
{
    if (error_text)
        ft_printf("ERROR: %s ERR_status: %d\n", error_text, err_status);

    // Free minishell resources before exit if needed
    if (is_crashable)
    {
        ft_free_minishell(minishell, is_crashable);
        free(*minishell);  // Free the minishell structure itself
        *minishell = NULL;  // Null the pointer to avoid dangling references
        exit(1);
    }
    else
    {
        ft_free_minishell(minishell, is_crashable);
		ft_printf("freeeing ___ \n");
        // Return or continue to next operation
    }
}
