/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:04:00 by itykhono          #+#    #+#             */
/*   Updated: 2024/08/29 20:18:33 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// 1) COPY ENV
// 2) Validate input
// 3) Lexer (String -> Tokens)
// 4) Parser (Tokens -> Logical_groups -> cmd_groups)

#include "../inc/minishell.h"

void	minishell_loop(t_data *minishell)
{
	while (1)
	{
		minishell->input = readline(PROMPT);
		init_tokens(minishell);
		check_syntax(minishell->tokens);
		// break ;
		parse_tokens(minishell);
		// while (minishell->tokens != NULL)
		// {
		// 	printf("%s = %d\n", minishell->tokens->value, minishell->tokens->type);
		// 	minishell->tokens = minishell->tokens->next;
		// }
		// seg fault here (no input given)
		ft_input_is_valid(minishell->input);
	}
}

void	init_minishell(t_data *minishell, char **env)
{
	minishell->envir = env;
	minishell->stdin = dup(0);
	minishell->stdout = dup(1);
	tcgetattr(STDIN_FILENO, &minishell->terminal);
	minishell->tokens = NULL;
}

int	main(int argc, char **argv, char **env)
{
	t_data	minishell;

	(void)argc;
	(void)argv;
	init_minishell(&minishell, env);
	init_environment(&minishell.env, minishell.envir);
	// print_environment(minishell.env);
	environment_free_list(minishell.env);
	minishell_loop(&minishell);
	return (0);
}
