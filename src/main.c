/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:51:34 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/19 18:49:17 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ------------------------------TO DO------------------------------
// 1) Validate input (quotes etc)
// 2) Update here_doc

#include "../inc/minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	reset_minishell(t_data *minishell)
{
	minishell->input = NULL;
	minishell->pipe_argv = NULL;
	minishell->number_of_commands = 0;
	minishell->commands = NULL;
}

void	minishell_loop(t_data *minishell)
{
	while (1)
	{
		minishell->input = readline(PROMPT);
		if (minishell->input == NULL)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			exit(0);
		}
		if (minishell->input)
			add_history(minishell->input);
		alloc_mem_for_commands(minishell);
		parsecmd(minishell);
		run_with_pipes(minishell);
		reset_minishell(minishell);
	}
}

void	init_minishell(t_data *minishell, char **env)
{
	minishell->envir = env;
	tcgetattr(STDIN_FILENO, &minishell->terminal);
	minishell->number_of_commands = 0;
}

int	main(int argc, char **argv, char **env)
{
	t_data	minishell;

	(void)argc;
	(void)argv;
	(void)env;
	signal(SIGINT, handle_sigint);
	init_minishell(&minishell, env);
	init_environment(&minishell.envlist, minishell.envir);
	minishell_loop(&minishell);
	return (0);
}
