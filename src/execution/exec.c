/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:23:34 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/09 20:31:53 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_cmd	*ft_init_exec_cmd(void)
{
	t_execcmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = EXEC;
	return ((t_cmd *)cmd);
}


void take_input(t_heredoc_cmd *cmd, char **ps, char *es)
{
    char *q;
    char *eq;
    char *token;
    char *line;

    if (peek(ps, es, "<|>&;()"))
        panic("parse error");
    gettoken(ps, es, &q, &eq);
    token = ft_strncpy(malloc(eq - q + 1), q, eq - q);
    token[eq - q] = '\0';  // Ensure null-termination

    // Initialize cmd->argv if it's NULL
    if (cmd->argv == NULL) {
        cmd->argv = malloc(sizeof(char *));
        cmd->argv[0] = strdup("");
    }

    while (1) {
        line = readline("heredoc> ");
        if (line == NULL) {
            // EOF reached
            break;
        }
        if (strcmp(line, token) == 0) {
            // Delimiter found, exit loop
            free(line);
            break;
        }
        // Append the line to cmd->argv[0]
        char *temp = ft_strjoin(cmd->argv[0], line);
        free(cmd->argv[0]);
        cmd->argv[0] = temp;
        
        temp = ft_strjoin(cmd->argv[0], "\n");
        free(cmd->argv[0]);
        cmd->argv[0] = temp;

        free(line);
    }

    free(token);
}

t_cmd	*here_doc_cmd(char **ps, char *es)
{
	t_heredoc_cmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = HERE_DOC;
	take_input(cmd, ps, es);
	printf("%s\n", cmd->argv[0]);
	return ((t_cmd *)cmd);
}

t_cmd	*redircmd(t_cmd *subcmd, char *file, char *efile, int mode, int fd)
{
	t_redircmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = OUTREDIR;
	cmd->cmd = subcmd;
	cmd->file = file;
	cmd->efile = efile;
	cmd->mode = mode;
	cmd->fd = fd;
	return ((t_cmd *)cmd);
}

t_cmd	*pipecmd(t_cmd *left, t_cmd *right)
{
	t_pipecmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}

t_cmd	*listcmd(t_cmd *left, t_cmd *right)
{
	t_listcmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = LIST;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}

t_cmd	*backcmd(t_cmd *subcmd)
{
	t_backcmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = BACK;
	cmd->cmd = subcmd;
	return ((t_cmd *)cmd);
}

void	runcmd(struct s_cmd *cmd, t_data *minishell)
{
	// printf("in run cmd\n");
	if (cmd == 0)
		exit(1);
	if (cmd->type == 0)
		exit(1);
	if (cmd->type == EXEC)
		do_exec(cmd, minishell);
	else if (cmd->type == OUTREDIR)
		do_redirect(cmd, minishell);
	else if (cmd->type == INREDIR)
		do_redirect(cmd, minishell);
	else if (cmd->type == LIST)
		do_list(cmd, minishell);
	else if (cmd->type == PIPE)
		do_pipe(cmd, minishell);
	else if (cmd->type == BACK)
		do_back(cmd, minishell);
	else
		exit(1);
	// printf("exit runcmd\n");
	return ;
} 
// fcntl-linux.h