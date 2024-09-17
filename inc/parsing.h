/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 21:48:08 by marvin            #+#    #+#             */
/*   Updated: 2024/09/17 13:37:43 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define MAX_TOKENS 100

# include "minishell.h"


//parsing_utils.c
enum redir_type
{
	IN,
	OUT,
	EDIT,
	HERE_DOC
};

typedef struct s_command_full t_command_full;  // Forward declaration

typedef struct s_redir
{
	int		type;
	char	file_name;
	int		fd;
} t_redir;

typedef struct s_command_full
{
	char				*cmd_name;
	char				**args;
	t_redir				*redir;
	t_command_full		*next;
	t_command_full		*prev;
}						t_command_full;

#endif