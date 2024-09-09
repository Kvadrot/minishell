/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_delete_it.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 14:42:33 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/09 16:41:17 by gbuczyns         ###   ########.fr       */
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

void	runcmd(t_cmd *cmd)
{
	int			p[2];
	pid_t		pid_l;
	pid_t		pid_r;
	t_backcmd	*bcmd;
	t_execcmd	*ecmd;
	t_listcmd	*lcmd;
	t_pipecmd	*pcmd;
	t_redircmd	*rcmd;
	int			fd;

	if (cmd == 0)
		exit(1);
	//
	if (cmd->type == EXEC)
	{
		ecmd = (t_execcmd *)cmd;
		if (ecmd->argv[0] == 0)
			exit(1);
		if ((pid_l = fork1()) == 0)
			execve(ecmd->argv[0], ecmd->argv, 0);
		wait(0);
		execve(ecmd->argv[0], ecmd->argv, 0);
		printf("exec %s failed\n", ecmd->argv[0]);
	}
	else if (cmd->type == BUILTIN)
	{
		if (fork() == 0)
			;
		// function executing builtins
	}
	else if (cmd->type == OUTREDIR)
	{
		rcmd = (t_redircmd *)cmd;
		close(rcmd->fd);
		if ((fd = open(rcmd->file, O_WRONLY | O_CREAT, 0644)) < 0)
		{
			printf("open %s failed\n", rcmd->file);
			exit(1);
		}
		dup2(fd, rcmd->fd);
		runcmd(rcmd->cmd);
		close(fd);
	}
	else if (cmd->type == INREDIR)
	{
		rcmd = (t_redircmd *)cmd;
		close(rcmd->fd);
		if ((fd = open(rcmd->file, O_WRONLY | O_CREAT | O_APPEND, 0644)) < 0)
		{
			printf("open %s failed\n", rcmd->file);
			exit(1);
		}
		dup2(fd, rcmd->fd);
		runcmd(rcmd->cmd);
		close(fd);
	}
	else if (cmd->type == LIST)
	{
		lcmd = (t_listcmd *)cmd;
		if ((pid_l = fork1()) == 0)
			runcmd(lcmd->left);
		wait(&pid_l);
		runcmd(lcmd->right);
	}
	else if (cmd->type == PIPE)
	{
		pcmd = (t_pipecmd *)cmd;
		if (pipe(p) < 0)
			panic("pipe");
		if ((pid_l = fork1()) == 0)
		{
			close(1);
			dup(p[1]);
			close(p[0]);
			close(p[1]);
			runcmd(pcmd->left);
		}
		if ((pid_r = fork1()) == 0)
		{
			close(0);
			dup(p[0]);
			close(p[0]);
			close(p[1]);
			runcmd(pcmd->right);
		}
		close(p[0]);
		close(p[1]);
		wait(&pid_l);
		wait(&pid_r);
	}
	else if (cmd->type == BACK)
	{
		bcmd = (t_backcmd *)cmd;
		if (fork1() == 0)
			runcmd(bcmd->cmd);
	}
	else
	{
		panic("runcmd");
	}
	exit(0);
}
