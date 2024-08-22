/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:04:00 by itykhono          #+#    #+#             */
/*   Updated: 2024/08/22 14:08:51 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//1) COPY ENV
//2) Validate input
//3) Lexer (String -> Tokens)
//4) Parser (Tokens -> Logical_groups -> cmd_groups)

#include "minishell.h"

void	minishell_loop(t_data *minishell)
{
	while (1)
	{
		minishell->input = readline(PROMPT);
		ft_input_is_valid(minishell->input);
	}
}

void	init_minishell(t_data *minishell, char **env)
{
	minishell->envir = env;
	minishell->stdin = dup(0);
	minishell->stdout = dup(1);
	tcgetattr(STDIN_FILENO, &minishell->terminal);
}

int	main(int argc, char **argv, char **env)
{
	t_data	minishell;

	init_minishell(&minishell, env);
	init_environment(&minishell.env, minishell.envir);
	// print_environment(minishell.env);
	environment_free_list(minishell.env);
	minishell_loop(&minishell);
	return (0);
}
