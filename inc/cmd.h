/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:08:04 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/21 15:12:51 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# define MAXARGS 100

# define EXEC 1
# define HERE_DOC 11
# define BUILTIN 2
# define INREDIR 21
# define REDIR 22
# define PIPE 3
# define LIST 4
# define BACK 5

# define ECHO 31
# define CD 32

typedef struct s_cmd
{
	int				type;
	char			**argv;
	char			*paths;
	char			*flag;
	char			*file;
	int				mode;
	int				fd;
	struct s_cmd	*sub_cmd;
	struct s_cmd	*left;
	struct s_cmd	*right;
}					t_cmd;

#endif