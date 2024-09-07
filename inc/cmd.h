/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:08:04 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/07 17:42:53 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# define MAXARGS 100

# define EXEC 1
# define BUILTIN 2
# define INREDIR 21
# define OUTREDIR 22
# define PIPE 3
# define LIST 4
# define BACK 5


# define ECHO 31
# define CD 32

typedef struct s_cmd
{
	int				type;
}					t_cmd;

typedef struct s_execcmd
{
	int				type;
	char			*argv[MAXARGS];
	char			*eargv[MAXARGS];
}					t_execcmd;

typedef struct s_redircmd
{
	int				type;
	struct s_cmd	*cmd;
	char			*file;
	char			*efile;
	int				mode;
	int				fd;
}					t_redircmd;

typedef struct s_pipecmd
{
	int				type;
	struct s_cmd	*left;
	struct s_cmd	*right;
}					t_pipecmd;

typedef struct s_listcmd
{
	int				type;
	struct s_cmd	*left;
	struct s_cmd	*right;
}					t_listcmd;

typedef struct s_backcmd
{
	int				type;
	struct s_cmd	*cmd;
}					t_backcmd;

void				do_pipe(t_cmd *cmd);
void				do_redirect(t_cmd *cmd);
void				do_exec(t_cmd *cmd);
void				do_list(t_cmd *cmd);
void				do_back(t_cmd *cmd);

#endif