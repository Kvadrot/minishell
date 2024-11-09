/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:19:59 by ufo               #+#    #+#             */
/*   Updated: 2024/11/09 19:52:01 by ufo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/** TODO: ft_close_redirections_before
* @brief: Closes file descriptors for redirections in the provided redirection list.
* @takes: redirect - Pointer to the head of the redirection list.
* =======================================================================
* @HOW_IT_WORKS:
1) Iterates through the redirection list in reverse order (using the `prev` pointer).
2) For each redirection, checks if the file descriptor (fd) is valid (greater than zero).
3) Closes the file descriptor if valid.
* =======================================================================
* @returns: void
*/
static void    ft_close_redirections_before(t_redir *redirect)
{
    t_redir *temp_redir;
    
    temp_redir = redirect;
    while (temp_redir)
    {
        if (temp_redir->fd && *(temp_redir->fd) > 0) 
            close(*(temp_redir->fd));
        temp_redir = temp_redir->prev;
    }
    return ;
}

/** TODO: ft_close_all_redirections
* @brief: Closes all file descriptors for redirections in a command chain, starting with the current command and working backwards.
* @takes: cmd - Pointer to the current command whose redirection list should be processed first.
*         redirect_list - Pointer to the head of the redirection list of the current command.
* =======================================================================
* @HOW_IT WORKS:
1) First, calls `ft_close_redirections_before` to close redirections for the current command.
2) Then, iterates through the previous commands in the pipeline (using the `prev` pointer).
3) For each previous command, processes its redirection list and closes any valid file descriptors (fd).
4) Continues until all commands in the pipeline have been processed.
* =======================================================================
* @returns: void
*/
void    ft_close_all_redirections(t_command_full *cmd, t_redir *redirect_list)
{
    t_command_full *temp_cmd;
    t_redir *temp_redir;

    ft_close_redirections_before(redirect_list);
    temp_cmd = cmd->prev;
    while (temp_cmd)
    {
        temp_redir = temp_cmd->redir_list_head;
        while (temp_redir)
        {
            if (temp_redir->fd && *(temp_redir->fd) > 0) 
                close(*(temp_redir->fd));
            temp_redir = temp_redir->next;
        }
        temp_cmd = temp_cmd->prev;
    }
}

/** TODO: ft_handle_dgreat
* @brief: Opens a file for appending if it exists or creates it if not (>> redirection).
* @takes: filename - name of the file to open or create
//=======================================================================//
* @HOW_IT_WORKS:
1) Opens or creates the file with write and append permissions
2) Sets file permissions to 0644 if created
* If successful, returns file descriptor;
//=======================================================================//
* @returns: fd - file descriptor for appending, or -1 if error occurs
*/
int ft_handle_dgreat(char *filename)
{
    int fd;

    fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
    {
        perror("Error opening file for appending");
        return -1;
    }

    return fd;
}

/** TODO: ft_handle_great
* @brief: Handles file redirection (>) for overwriting or creating a file.
* @takes: filename - name of the file to open or create
//=======================================================================//
* @HOW_IT_WORKS:
1) Checks if file exists (access F_OK)
2) If no file, creates it with write and truncation permissions
3) If file exists, truncates and opens it with write permissions
* Returns file descriptor for writing;
//=======================================================================//
* @returns: fd - file descriptor, or -1 if error occurs
*/
int ft_handle_great(char *filename)
{
    int fd;

    if (access(filename, F_OK) == -1)
    {
        fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1)
        {
            perror("Error creating file");
            return -1;
        }
    }
    else
    {
        fd = open(filename, O_WRONLY | O_TRUNC);
        if (fd == -1)
        {
            perror("Error opening file for writing");
            return -1;
        }
    }

    return fd;
}

/** TODO: ft_handle_output
* @brief: Manages output redirection based on redirection type.
* @takes: redir - pointer to t_redir structure with file name and redirection type
//=======================================================================//
* @HOW_IT_WORKS:
1) Checks redirection type:
*  - T_GREAT: handles '>' redirection
*  - T_DGREAT: handles '>>' redirection
2) Returns the file descriptor to the caller;
//=======================================================================//
* @returns: fd - file descriptor based on redirection type, or -1 if error
*/
int ft_handle_output(t_redir *redir)
{
    int fd_result;

    if (redir->type == T_GREAT)
        fd_result = ft_handle_great(redir->file_name);
    else
        fd_result = ft_handle_dgreat(redir->file_name);

    return fd_result;
}

/** TODO: ft_handle_less
* @brief: Handles input redirection from a file (< redirection).
* @takes: filename - name of the file to read from
//=======================================================================//
* @HOW_IT_WORKS:
1) Checks if the file exists (access F_OK)
2) Verifies read access (access R_OK)
3) Opens the file for reading if accessible
* Returns file descriptor if successful;
//=======================================================================//
* @returns: fd - file descriptor for reading, or -1 if error occurs
*/
static int ft_handle_less(char *filename)
{
    int fd_result;
    fd_result = -1;

    if (access(filename, F_OK) == -1)
    {
        perror("File does not exist !!!!");
        return -1;
    }

    if (access(filename, R_OK) == -1)
    {
        perror("File is not accessible");
        return -1;
    }

    fd_result = open(filename, O_RDONLY);
    if (fd_result == -1)
    {
        perror("Error opening file");
        return -1;
    } 
    return fd_result;
}

/** TODO: ft_handle_input
* @brief: Manages input redirection based on redirection type.
* @takes: redir - pointer to t_redir structure containing redirection details
//=======================================================================//
* @HOW_IT_WORKS:
1) Checks if redirection type is input (T_LESS):
*   - Calls ft_handle_less for file reading
2) Handles T_DLESS (Heredoc) separately as a future TODO
* Returns the file descriptor;
//=======================================================================//
* @returns: fd - file descriptor, or -1 if error occurs
*/
int ft_handle_input(t_redir *redir)
{
    int fd_result;

    if (redir->type == T_LESS)
        fd_result = ft_handle_less(redir->file_name);
    else
        return -666; // Placeholder for future HEREDOC handling

    return fd_result;
}

/** TODO: ft_handle_redirections
* @brief: Processes all redirections (input and output) for each command.
* @takes: minishell - pointer to the minishell data structure
//=======================================================================//
* @HOW_IT_WORKS:
1) Iterates over each command in the minishell command list
2) For each command, processes its redirection list:
*   - Output redirection (T_GREAT, T_DGREAT): updates cmd->fd_out
*   - Input redirection (T_LESS, T_DLESS): updates cmd->fd_in
3) Iterates through next redirection for each command;
//=======================================================================//
* @returns: void
*/

int ft_handle_redirections(t_data **minishell)
{
    t_command_full *cmd_head;
    t_command_full *temp_cmd;
    t_redir *temp_redir;

    cmd_head = (*minishell)->commands;
    temp_cmd = cmd_head;
    while (temp_cmd != NULL)
    {
        if (temp_cmd->redir_list_head != NULL)
        {
            temp_redir = temp_cmd->redir_list_head;
            while (temp_redir)
            {
                if (temp_redir->type == T_GREAT || temp_redir->type == T_DGREAT)
                {
                    temp_cmd->fd_out = ft_handle_output(temp_redir);
                    if (temp_cmd->fd_out == -1)
                    {
                        ft_close_all_redirections(temp_cmd, temp_redir);
                        return (-400);
                    }
                }
                else if (temp_redir->type == T_LESS || temp_redir->type == T_DLESS)
                {
                    temp_cmd->fd_in = ft_handle_input(temp_redir);
                    if (temp_cmd->fd_in == -1)
                    {
                        ft_close_all_redirections(temp_cmd, temp_redir);
                        return (-401);
                    }
                }
                temp_redir = temp_redir->next;
            }
        }
        temp_cmd = temp_cmd->next;
    }
    return (200);
}