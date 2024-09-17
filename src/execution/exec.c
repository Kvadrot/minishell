/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:23:34 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/17 19:09:16 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	do_redirect(t_cmd *cmd, t_data *minishell)
{
	t_redircmd	*rcmd;
	int			fd;

	rcmd = (t_redircmd *)cmd;
	if (fork1() == 0)
	{
		close(rcmd->fd);
		if ((fd = open(rcmd->file, rcmd->mode, 0644)) < 0)
			panic("open");
		if (fork1() == 0)
		{
			runcmd(rcmd->cmd, minishell);
			exit(0);
		}
		wait(0);
		close(fd);
		exit(0);
	}
}

void	run_in_background_or_list(t_cmd *cmd, t_data *minishell)
{
	t_listcmd	*lcmd;
	pid_t		pid_l;
	t_backcmd	*bcmd;

	if (cmd->type == LIST)
	{
		lcmd = (t_listcmd *)cmd;
		pid_l = fork1();
		if (pid_l == 0)
			runcmd(lcmd->left, minishell);
		waitpid(pid_l, NULL, 0);          
		runcmd(lcmd->right, minishell);
	}
	else if (cmd->type == BACK)
	{
		bcmd = (t_backcmd *)cmd;
		if (fork1() == 0)
			runcmd(bcmd->cmd, minishell);
	}
}

void	execute_command(char *binary_path, t_execcmd *ecmd, t_data *minishell)
{
	char	**envp;

	envp = environment_list_to_array(minishell->envlist);
	if (fork1() == 0)
	{
		execve(binary_path, ecmd->argv, envp);
		handle_exec_error("execve failed for: ", binary_path);
		free(envp);
		exit(EXIT_FAILURE);
	}
	wait(0);
	free(envp);
}

void	do_exec(t_cmd *cmd, t_data *minishell)
{
	t_execcmd	*ecmd;
	char		**paths;
	char		*binary_path;

	ecmd = (t_execcmd *)cmd;
	if (ecmd->argv[0] == NULL)
		return ;
	ft_expand_dolar(ecmd->argv, minishell);
	if (is_builtin_done(ecmd->argv, minishell))
		return ;
	paths = retrieve_paths();
	binary_path = find_executable_path(ecmd, paths);
	execute_command(binary_path, ecmd, minishell);
	clean_up(binary_path, paths); // Free resources (or call garbage collector)
}

void	runcmd(struct s_cmd *cmd, t_data *minishell)
{
	if (cmd == 0)
		exit(1);
	if (cmd->type == 0)
		exit(1);
	if (cmd->type == EXEC)
		do_exec(cmd, minishell);
	else if (cmd->type == REDIR)
		do_redirect(cmd, minishell);
	else if (cmd->type == LIST || cmd->type == BACK)
		run_in_background_or_list(cmd, minishell);
	else
		exit(1);
	return ;
}
