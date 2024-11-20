/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 21:48:08 by marvin            #+#    #+#             */
/*   Updated: 2024/11/18 15:01:46 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define MAX_TOKENS 100

# include "minishell.h"

// Forward declaration of struct
typedef struct s_command_full t_command_full;
typedef struct s_redir t_redir;


// Struct for redirection
struct s_redir
{
	t_token_type type;      // Use correct type name for enum
	char *file_name;        // Changed to pointer to store file name as a string
	int *fd;
	char *value;            //only for HEREDOC !!!
	t_redir *next;
	t_redir *prev;
};

// Struct for command
struct s_command_full
{
	char	*cmd_name;
	char	**args;
	int		fd_out;
	int		fd_in;
	char	*here_doc;
	t_redir *redir_list_head;
	t_command_full *next;
	t_command_full *prev;
};

#endif


// Expander: