/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:14:58 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/10/19 18:44:59 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_commands(t_command_full *cmd)
{
	t_command_full	*tmp;
	int				i;

	tmp = cmd;
	i = 0;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
    // envp[i] contains "PATH=/bin:/usr/bin:/some/other/dir"
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
    // skip the "PATH=" (5 characters) and split the directories by ':'
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
    // Construct the full path to the command
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}

void	execute(char *argv, char **envp)
{
	char	**split;
	int 	i;
	char	*path;
	
	i = -1;
	split = ft_split(argv, ' ');
	path = find_path(split[0], envp);
	if (!path)	
	{
		while (split[++i])
			free(split[i]);
		free(split);
		error_handling("something is wrong with PATH");
	}
	if (execve(path, split, envp) == -1)
		error_handling("something is wrong with execve");
}

int	open_file(char *argv, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 2)
		file = open(argv, O_RDONLY, 0777);
	if (file == -1)
		error_handling("some issues with file opening");
	return (file);
}

// struct s_command_full
// {
// 	char	*cmd_name;
// 	char	**args;
// 	int		fd_out;
// 	int		fd_in;
// 	t_redir *redir_list_head;         // This should be a pointer to an array or a single redirection struct
// 	t_command_full *next;
// 	t_command_full *prev;
// };

void	child_process()
{
	
}

// void	child_process(char *argv, char **envp)
// {
// 	pid_t	pid;
// 	int		fd[2];

// 	if (pipe(fd) == -1)
// 		error_handling("some issues with pipe");
// 	pid = fork();
// 	if (pid == -1)
// 		error_handling("some issues with forking");
// 	if (pid == 0)
// 	{
// 		close(fd[0]);
// 		dup2(fd[1], STDOUT_FILENO);
// 		execute(argv, envp);
// 	}
// 	else
// 	{
// 		close(fd[1]);
// 		dup2(fd[0], STDIN_FILENO);
// 		waitpid(pid, NULL, 0);
// 	}
// }

void	here_doc(char *limiter)
{
	pid_t	pid;
	int		fd[2];
	char	*line;

	// if (argc < 6)
	// 	error_handling("Please check your arguments!");
	if (pipe(fd) == -1)
		error_handling("something is wrong with the pipe (heredoc)");
	pid = fork();
	if (pid == 0) // Child process
	{
		close(fd[0]);  // Close the read end of the pipe
		while (1)
		{
			line = get_next_line(STDIN_FILENO);
			if (!line)
				error_handling("Error reading input");
			// If the line matches the limiter, exit
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0 && line[ft_strlen(limiter)] == '\n')
			{
				free(line);
				exit(EXIT_SUCCESS);
			}
			// Write the line to the pipe (to be used by the next process)
			write(fd[1], line, ft_strlen(line));
			free(line);  // Free the line after it's written to the pipe
		}
	}
	else // Parent process
	{
		close(fd[1]);  // Close the write end of the pipe
		dup2(fd[0], STDIN_FILENO);  // Redirect pipe read end to stdin
		wait(NULL);  // Wait for the child process to finish
	}
}

int exec(t_command_full *cmd)
{
	t_command_full	*tmp;
	pid_t	pid;

	tmp = cmd;
	while (tmp != NULL)
	{
		
	}
}
