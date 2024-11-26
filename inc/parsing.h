/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 21:48:08 by marvin            #+#    #+#             */
/*   Updated: 2024/11/24 16:30:56 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define MAX_TOKENS 100

typedef struct s_command_full	t_command_full;
typedef struct s_redir			t_redir;

struct	s_redir
{
	t_token_type	type;
	char			*file_name;
	int				*fd;
	char			*value;
	t_redir			*next;
	t_redir			*prev;
};

struct	s_command_full
{
	char			*cmd_name;
	char			**args;
	int				fd_out;
	int				fd_in;
	char			*here_doc;
	t_redir			*redir_list_head;
	t_command_full	*next;
	t_command_full	*prev;
};

#endif
