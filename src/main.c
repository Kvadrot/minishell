/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:51:34 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/08 15:36:47 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// 1) COPY ENV
// 2) Validate input
// 3) Lexer (String -> Tokens)
// 4) Parser (Tokens -> Logical_groups -> cmd_groups)

#include "../inc/minishell.h"

void minishell_loop(t_data *minishell)
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
			minishell_free(minishell, YES);
			break;
		}
		// printf("after prompt\n");
		
		// char buff[] = "echo tav > ztest"; //>> tak.txt | ls > ls";
		runcmd(parsecmd(minishell->input), minishell); //
		// runcmd(parsecmd(buff));
		free(minishell->input);
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
		// if (minishell->commands && minishell->commands->args[0]) // cd /nfs/homes/gbuczyns/Documents/CommonCore/level_4 >> asdas
		// {
		// 	buff = minishell->commands->args[0];
		// 	if (ft_strcmp(buff, "cd") == 0)
		// 		md_cd(minishell->commands->args[1], minishell);
		// }
		// print_environment(minishell->envlist);
	}
}


void init_minishell(t_data *minishell, char **env)
{
	minishell->envir = env;
	minishell->stdin = dup(0);
	minishell->stdout = dup(1);
	tcgetattr(STDIN_FILENO, &minishell->terminal);
	minishell->tracker = NULL;
	minishell->tokens = NULL;
}

int main(int argc, char **argv, char **env)
{
	t_data	minishell;

	(void)argc;
	(void)argv;
	(void)env;
	// char buff[] = "echo tav > test"; //>> tak.txt | ls > ls";

	init_minishell(&minishell, env);
	// init_environment(&minishell.envlist, minishell.envir);
	// print_environment(minishell.envlist);
	minishell_loop(&minishell);
	// environment_free_list(minishell.envlist);
	return (0);
}
