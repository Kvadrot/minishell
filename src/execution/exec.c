/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:23:34 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/15 14:26:59 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// #include <fcntl-linux.h>

// void	do_pipe(t_cmd *cmd, t_data *minishell)
// {
// 	int			p[2];
// 	pid_t		pid_l;
// 	pid_t		pid_r;
// 	t_pipecmd	*pcmd;

// 	cmd = malloc(sizeof(*cmd));
// 	ft_memset(cmd, 0, sizeof(*cmd));
// 	cmd->type = EXEC;
// 	return ((t_cmd *)cmd);
// }


t_cmd	*redircmd(t_cmd *subcmd, char *file, char *efile, int mode, int fd)
{
	t_redircmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = REDIR;
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
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}

t_cmd	*listcmd(t_cmd *left, t_cmd *right)
{
	t_listcmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = LIST;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}

t_cmd	*backcmd(t_cmd *subcmd)
{
	t_backcmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
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
	else if (cmd->type == REDIR)
		do_redirect(cmd, minishell);
	else if (cmd->type == LIST)
		do_list(cmd, minishell);
	else if (cmd->type == BACK)
		do_back(cmd, minishell);
	else
		exit(1);
	// printf("exit runcmd\n");
	return ;
}

void	do_redirect(t_cmd *cmd, t_data *minishell)
{
	t_redircmd	*rcmd;
	int			fd;

	// int			p[2];
	// pid_t		pid_l;
	// pid_t		pid_r;
	rcmd = (t_redircmd *)cmd;
	if (fork1() == 0)
	{
		close(rcmd->fd);
		if ((fd = open(rcmd->file, rcmd->mode, 0644)) < 0)
		// O_CREAT | O_WRONLY | O_TRUNC
		{
			panic("open");
		}
		if (fork1() == 0)
		{
			runcmd(rcmd->cmd, minishell);
			// close(fd);
			exit(0);
		}
		wait(0);
		// printf("waiting for kid to finish\n");
		close(fd);
		exit(0);
	}
}

// void	do_redirect(t_cmd *cmd, t_data *minishell)
// {
// 	int			p[2];
// 	t_redircmd	*rcmd;
// 	pid_t		pid;

// 	// pid_t		pid_l;
// 	// pid_t		pid_r;
// 	rcmd = (t_redircmd *)cmd;
// 	if (pipe(p) < 0)
// 		panic("pipe");
// 	pid = fork1();
// 	if (pid == 0)
// 	{
// 		close(rcmd->fd);
// 		if (open(rcmd->file, rcmd->mode) < 0)
// 		{
// 			printf("open %s failed\n", rcmd->file);
// 			printf("\n");
// 			exit(1);
// 		}
// 		runcmd(rcmd->cmd, minishell);
// 	}
// }

void	execute_command(char *binary_path, t_execcmd *ecmd)
{
	// need access to envlist here or somewhere else, potentially only 
	// after using export/import functions 
	// ecmd->eargv = environment_list_to_array(minishell->envlist);
	// execve(binary_path, ecmd->argv, ecmd->eargv);
	if (fork1() == 0)
	{
		execve(binary_path, ecmd->argv, 0); // to be updated with above
		handle_exec_error("execve failed for: ", binary_path);
		exit(0);
	}
	wait(0);
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
	execute_command(binary_path, ecmd);
	clean_up(binary_path, paths); // potentially replaced with gc_collector
}

// void	do_exec(t_cmd *cmd, t_data *minishell)
// {
// 	t_execcmd	*ecmd;

// 	// int			p[2];
// 	ecmd = (t_execcmd *)cmd;
// 	if (ecmd->argv[0] == 0)
// 		exit(1);
// 	ft_expand_dolar(ecmd->argv, minishell);
// 	if (is_builtin_done(ecmd->argv, minishell) == 1)
// 		return ;
// 	else
// 	{
// 		// how to pass it to this function here?
// 		execve(ecmd->argv[0], ecmd->argv, 0);
// 		printf("exec %s failed\n", ecmd->argv[0]);
// 	}
// }

void	do_list(t_cmd *cmd, t_data *minishell)
{
	pid_t		pid_l;
	t_listcmd	*lcmd;

	// int			p[2];
	// pid_t		pid_r;
	lcmd = (t_listcmd *)cmd;
	if ((pid_l = fork1()) == 0)
		runcmd(lcmd->left, minishell);
	wait(&pid_l);
	runcmd(lcmd->right, minishell);
}

void	do_back(t_cmd *cmd, t_data *minishell)
{
	t_backcmd	*bcmd;

	// int			pid;
	bcmd = (t_backcmd *)cmd;
	if (fork1() == 0)
		runcmd(bcmd->cmd, minishell);
}

pid_t	fork1(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		panic("fork");
	return (pid);
}

void	ft_expand_dolar(char **argv, t_data *minishell)
{
	int		i;
	char	*value;

	i = 0;
	while (argv[i])
	{
		if (argv[i][0] == '$')
		{
			value = ft_get_envlst_val(argv[i] + 1, minishell);
			if (value)
			{
				free(argv[i]);
				argv[i] = value;
			}
		}
		i++;
	}
}

/* void execute_pipe(t_command *command, t_data *data)
{
	int		fd[2];
	pid_t	pid;

	if (command->pipe)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			dup2(fd[1], 1);
			close(fd[0]);
			close(fd[1]);
			execve(command->args[0], command->args, data->envir);
		}
		else
		{
			waitpid(pid, NULL, 0);
			dup2(fd[0], 0);
			close(fd[0]);
			close(fd[1]);
		}
	}
	else
		execve(command->args[0], command->args, data->envir);
}

void exe

void	execute_commands(t_command *command, t_data *data)
{
	while (command)
	{
		execute_command(command, data);
		command = command->next;
	}
}

void	execute(t_data *data)
{
	t_command	*command;

	command = data->tokens->commands;
	while (command)
	{
		execute_commands(command, data);
		command = command->next;
	}
}

t_tokens *ft_tokenize (char *input)
{
	t_tokens	*token;
	t_tokens	*head;
	int			i;

	i = 0;
	head = (t_tokens *)malloc(sizeof(t_tokens));
	// if (!head)
		// return not sufficient memory error
	token = head;
	while (input[i])
	{
		if (ft_is_whitespace(input[i]))
			i++;
		else if (ft_strchr("><|", input[i]))
		{
			token = update_token(token, input + i, input[i]);
			i++;
			token->next = (t_tokens *)malloc(sizeof(t_tokens));
			// if (!token->next)
				// return not sufficient memory error
			token = token->next;
		}
		else
		{
			token = update_token_word(token, input + i, T_WORD);
			i += ft_strlen(token->value);
			token->next = (t_tokens *)malloc(sizeof(t_tokens));
			// if (!token->next)
				// return not sufficient memory error
			token = token->next;
		}
	}
	token->next = NULL;
	return (head);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	data.stdin = dup(0);
	data.stdout = dup(1);
	data.envir = envp;
	while (1)
	{
		data.input = readline(PROMPT);
		if (!data.input)
			break ;
		if (ft_input_is_valid(data.input))
		{
			data.tokens = ft_tokenize(data.input);
			execute(&data);
		}
		free(data.input);
	}
	return (0);
} */
