/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:51:34 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/15 16:39:20 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// 1) COPY ENV
// 2) Validate input
// 3) Lexer (String -> Tokens)
// 4) Parser (Tokens -> Logical_groups -> cmd_groups)

// ------------------------------TO DO------------------------------
// Signal for CTRL + C
// Parsing
// Handling $? for last error code
// Norminette

#include "../inc/minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	minishell_loop(t_data *minishell)
{
	// char *buff;
	while (1)
	{
		// minishell->tokens = NULL;
		// printf("before prompt\n");
		minishell->input = readline(PROMPT);
		if (minishell->input == NULL)
		{
			ft_putendl_fd("\nCaught EOF (Ctrl+D)\n", STDOUT_FILENO);
			// diagnostics only delete before realase EOF
			// minishell_free(minishell, YES);
			break ;
		}
		if (minishell->input)
			add_history(minishell->input);
		alloc_mem_for_commands(minishell);
		parsecmd(minishell);
		run_with_pipes(minishell);
		// free_global(minishell);
		minishell->input = NULL;
		minishell->pipe_argv = NULL;
		minishell->number_of_commands = 0;
		minishell->commands = NULL;
		// char buff[] = "echo tav > ztest"; //>> tak.txt | ls > ls";
		// printf("after prompt\n");
		// char buff[] = "echo tav > ztest"; //>> tak.txt | ls > ls";
		// runcmd(parsecmd(buff));
		// init_tokens(minishell);
		// check_syntax(minishell->tokens);
		// break ;
		// minishell->commands = parse_tokens(minishell->tokens);
		// while (minishell->tokens != NULL)
		// {
		// 	printf("%s = %d\n", minishell->tokens->value,
		// minishell->tokens->type);
		// 	minishell->tokens = minishell->tokens->next;
		// }
		// seg fault here (no input given)
		// ft_input_is_valid(minishell->input);
		// if (minishell->commands && minishell->commands->args[0]) // cd
			/nfs/homes/gbuczyns/Documents/CommonCore/level_4 >> asdas
		// {
		// 	buff = minishell->commands->args[0];
		// 	if (ft_strcmp(buff, "cd") == 0)
		// 		md_cd(minishell->commands->args[1], minishell);
		// }
		// print_environment(minishell->envlist);
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
	// char buff[] = "echo tav > test"; //>> tak.txt | ls > ls";
	signal(SIGINT, handle_sigint);
	init_minishell(&minishell, env);
	init_environment(&minishell.envlist, minishell.envir);
	// print_environment(minishell.envlist);
	minishell_loop(&minishell);
	// environment_free_list(minishell.envlist);
	return (0);
}
