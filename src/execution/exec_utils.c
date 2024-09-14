/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ja <ja@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:08:02 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/12 21:54:42 by ja               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// #include <fcntl-linux.h>

void setup_pipes(t_data *minishell)
{
	unsigned int commands;

	commands = minishell->number_of_commands;
	if (commands == 0)
		return;
	if (commands == 1)
		do_single_comand();
	else
		do_pipe2(minishell);
	return;
}

do_pipe2(t_data *minishell)
{
	unsigned int pipes_to_make;

	pipes_to_make = minishell->number_of_commands;
	while (pipes_to_make)
	{
		
	}
}

void do_pipe(t_cmd *cmd, t_data *minishell)
{
	int p[2];
	pid_t pid_l;
	pid_t pid_r;
	t_list *node;
	int i;
	t_execcmd *cmd1;
	t_execcmd *cmd2;
	t_execcmd *cmd3;
	t_pipecmd *pcmd;
	t_pipecmd *pcmd1;
	t_pipecmd *pcmd2;

	i = 0;
	// cmd1
	cmd1 = malloc(sizeof(*cmd1));
	ft_memset(cmd1, 0, sizeof(*cmd1));
	cmd1->type = EXEC;
	cmd1->argv[0] = "ls";
	cmd1->argv[1] = NULL;
	// cmd2
	cmd2 = malloc(sizeof(*cmd1));
	ft_memset(cmd2, 0, sizeof(*cmd1));
	cmd2->type = EXEC;
	cmd2->argv[0] = "grep";
	cmd2->argv[1] = "m";
	cmd2->argv[2] = NULL;
	// cmd3
	cmd3 = malloc(sizeof(*cmd1));
	ft_memset(cmd2, 0, sizeof(*cmd1));
	cmd3->type = EXEC;
	cmd3->argv[0] = "grep";
	cmd3->argv[1] = "s";
	cmd3->argv[2] = NULL;
	// pcmd1
	pcmd1 = malloc(sizeof(*pcmd1));
	ft_memset(pcmd1, 0, sizeof(*pcmd1));
	pcmd1->type = PIPE;
	pcmd1->index = 0;
	// asign pcmd1->pipe[] in loop
	pcmd1->left = cmd1;
	pcmd1->right = cmd2;
	minishell->pipe_list = ft_lstnew(pcmd1);

	minishell->pipe_list->next->content = ft_lstnew(cmd);
	pcmd2 = malloc(sizeof(*pcmd2));
	ft_memset(pcmd2, 0, sizeof(*pcmd2));
	pcmd2->type = PIPE;
	pcmd1->index = 0;
	pcmd2->left = cmd1;
	pcmd2->right = cmd2;
	int p1[2];

	// put pipe struct into current node
	node = minishell->pipe_list;

	while (minishell->pipe_list)
	{

		if (pipe(((t_pipecmd *)(node->content))->pipe) < 0)
			panic("pipe");
		if ((pid_l = fork1()) == 0)
		{
			close(1);
			dup(p1[1]);
			close(p1[0]);
			close(p1[1]);
			runcmd(pcmd1->left, minishell);
			exit(0);
		}
		if ((pid_r = fork1()) == 0)
		{
			close(0);
			dup(p1[0]);
			close(p1[0]);
			close(p1[1]);
			runcmd(pcmd1->right, minishell);
			exit(0);
		}
		close(p1[0]);
		close(p1[1]);
		wait(&pid_l);
		wait(&pid_r);
		minishell->pipe_list = minishell->pipe_list->next;
	}
	// minishell->pipe_list = ft_lstnew(cmd);
	if (minishell->pipe_list)
	{
		node = minishell->pipe_list;
		pcmd = (t_pipecmd *)(node->content);
	}
	while (pcmd)
	{
		if (pipe(p) < 0)
			panic("pipe");
		if ((pid_l = fork1()) == 0)
		{
			close(1);
			dup(p[1]);
			close(p[0]);
			close(p[1]);
			runcmd(pcmd->left, minishell);
			exit(0);
		}
		if ((pid_r = fork1()) == 0)
		{
			close(0);
			dup(p[0]);
			close(p[0]);
			close(p[1]);
			runcmd(pcmd->right, minishell);
			exit(0);
		}
		close(p[0]);
		close(p[1]);
		wait(&pid_l);
		wait(&pid_r);
		i++;
		node = node->next;
		pcmd = (t_pipecmd *)node->content;
	}
	pcmd = (t_pipecmd *)cmd;
	if (pipe(p) < 0)
		panic("pipe");
	if ((pid_l = fork1()) == 0)
	{
		close(1);
		dup(p[1]);
		close(p[0]);
		close(p[1]);
		runcmd(pcmd->left, minishell);
		exit(0);
	}
	if ((pid_r = fork1()) == 0)
	{
		close(0);
		dup(p[0]);
		close(p[0]);
		close(p[1]);
		runcmd(pcmd->right, minishell);
		exit(0);
	}
	close(p[0]);
	close(p[1]);
	wait(&pid_l);
	wait(&pid_r);
	return;
}

void make_pipes(t_data *minishell)
{
	while ()
}

void do_redirect(t_cmd *cmd, t_data *minishell)
{
	t_redircmd *rcmd;
	int fd;

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

void execute_command(char *binary_path, t_execcmd *ecmd)
{
	// need access to envlist here or somewhere else, potentially only
	// after using export/import functions
	// ecmd->eargv = environment_list_to_array(minishell->envlist);
	// execve(binary_path, ecmd->argv, ecmd->eargv);
	execve(binary_path, ecmd->argv, 0); // to be updated with above
	handle_exec_error("execve failed for: ", binary_path);
	clean_up(binary_path, NULL);
	exit(1);
}

void do_exec(t_cmd *cmd, t_data *minishell)
{
	t_execcmd *ecmd;
	char **paths;
	char *binary_path;

	ecmd = (t_execcmd *)cmd;
	if (ecmd->argv[0] == NULL)
		exit(1);
	ft_expand_dolar(ecmd->argv, minishell);
	if (is_builtin_done(ecmd->argv, minishell))
		return;
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

void do_list(t_cmd *cmd, t_data *minishell)
{
	pid_t pid_l;
	t_listcmd *lcmd;

	// int			p[2];
	// pid_t		pid_r;
	lcmd = (t_listcmd *)cmd;
	if ((pid_l = fork1()) == 0)
		runcmd(lcmd->left, minishell);
	wait(&pid_l);
	runcmd(lcmd->right, minishell);
}

void do_back(t_cmd *cmd, t_data *minishell)
{
	t_backcmd *bcmd;

	// int			pid;
	bcmd = (t_backcmd *)cmd;
	if (fork1() == 0)
		runcmd(bcmd->cmd, minishell);
}

pid_t fork1(void)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
		panic("fork");
	return (pid);
}

void ft_expand_dolar(char **argv, t_data *minishell)
{
	int i;
	char *value;

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
