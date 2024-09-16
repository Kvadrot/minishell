/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ja <ja@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:21:24 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/16 21:11:01 by ja               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	create_pipes(t_data *minishell)
{
	int	i;
	int	pipes;

	i = 0;
	pipes = minishell->num_of_cmds - 1;
	minishell->pipe_argv = (int **)malloc(sizeof(int *) * (pipes + 1));
	if (minishell->pipe_argv == NULL)
		panic("malloc");
	minishell->pipe_argv[pipes] = NULL;
	while (i < pipes)
	{
		minishell->pipe_argv[i] = (int *)malloc(2 * sizeof(int));
		if (minishell->pipe_argv[i] == NULL)
			panic("malloc");
		i++;
	}
	while (i > 0)
	{
		pipe(minishell->pipe_argv[i - 1]);
		i--;
	}
}
void	run_with_pipes(t_data *minishell)
{
	unsigned int	commands;

	commands = minishell->num_of_cmds;
	if (commands == 0)
		return ;
	if (commands == 1)
	{
		if (fork1() == 0)
			runcmd(minishell->commands[0], minishell);
		wait(NULL);
	}
	else
	{
		create_pipes(minishell);
		make_forks(minishell);
	}
	return ;
}




// // To implement the command `ls | grep a > text.txt` using your structures,
// 	you'll need to handle:

// // 1. **Pipes (`|`)**: You need to create a pipe between `ls` and `grep`.
// // 2. **Forks**: Fork two child processes to handle each command in the pipeline.
// // 3. **Redirection (`>`)**: Redirect the output of `grep` to a file (`text.txt`).

// // Here's a breakdown of how to handle it:

// // ### Steps:

// // 1. **Create Pipes**:
// //    For a single pipe (`ls | grep`), create a pipe before forking.

// // 2. **Fork and Execute**:
// //    Fork the process twice:
// //    - The first child will handle `ls` and write its output to the pipe.
// //    - The second child will handle `grep a`, read from the pipe,
// 	and then redirect its output to `text.txt`.

// // 3. **Redirection**:
// //    In the second child process (for `grep`),
// 	handle the redirection by opening `text.txt` in write mode,
// 	then use `dup2` to redirect `stdout` to the file descriptor for `text.txt`.

// // 4. **Wait for Children**:
// //    The parent process should wait for both children to finish executing.

// // ### Pseudocode for Execution Flow:

// // ```c
// // void execute_pipeline(t_data *data) {
// //     int pipe_fd[2];
// //     pipe(pipe_fd);

// //     pid_t pid1 = fork();
// //     if (pid1 == 0) {
// //         // First child: execute 'ls'
// //         close(pipe_fd[0]); // Close reading end
// //         dup2(pipe_fd[1], STDOUT_FILENO); // Redirect stdout to pipe
// //         close(pipe_fd[1]);

// //         execvp(data->commands[0]->argv[0], data->commands[0]->argv);
// 	// Execute ls
// //         perror("execvp failed");
// //         exit(1);
// //     }

// //     pid_t pid2 = fork();
// //     if (pid2 == 0) {
// //         // Second child: execute 'grep a > text.txt'
// //         close(pipe_fd[1]); // Close writing end
// //         dup2(pipe_fd[0], STDIN_FILENO); // Redirect stdin to pipe
// //         close(pipe_fd[0]);

// //         // Open the output file for redirection
// //         int fd = open("text.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
// //         if (fd == -1) {
// //             perror("open failed");
// //             exit(1);
// //         }
// //         dup2(fd, STDOUT_FILENO); // Redirect stdout to file
// //         close(fd);

// //         execvp(data->commands[1]->argv[0], data->commands[1]->argv);
// 	// Execute grep
// //         perror("execvp failed");
// //         exit(1);
// //     }

// //     // Parent process: close pipe and wait for both children
// //     close(pipe_fd[0]);
// //     close(pipe_fd[1]);

// //     waitpid(pid1, NULL, 0); // Wait for 'ls' to finish
// //     waitpid(pid2, NULL, 0); // Wait for 'grep' to finish
// // }
// // ```

// // ### Key Points:
// // - **Pipe creation** (`pipe(pipe_fd)`): This creates a unidirectional pipe.
// //
// 	- **Redirection** (`dup2`): You redirect the output/input by replacing `STDOUT` and `STDIN`.
// // - **Forking**: Each child process handles one part of the pipeline.
// // - **Waiting**: The parent waits for both child processes to terminate.

// // You can use the `t_execcmd` structure to represent each command (`ls` and `grep`) and store them in `data->commands`:

// // ```c
// // data->commands[0] = &ls_command;
// // data->commands[1] = &grep_command;
// // ```

// // This should give you the basics for implementing command execution with pipes and redirection. Let me know if you need help with further implementation details!

// // int	main(void)
// 	// {
// 	// 	t_data	minishell;
// 	// 	int		i;

// 	// 	i = 0;
// 	// 	minishell.num_of_cmds = 3;
// 	// 	setup_pipes(&minishell);
// 	// 	if (minishell.pipe_argv != NULL)
// 	// 	{
// 	// 		printf("pipe_argv is not NULL\n");
// 	// 		while (minishell.pipe_argv[i] != NULL)
// 	// 		{
// 	// 			printf("pipe_argv[%d] is not NULL\n", i);
// 	// 			i++;
// 	// 		}
// 	// 	}
// 	// 	return (0);
// 	// }

// 	// void	panic(char *str)
// 	// {
// 	// 	printf("panic: %s\n", str);
// 	// 	exit(1);
// 	// }

// 	void do_single_comand(void)
// 	{
// 		printf("do_single_comand\n");
// 	}