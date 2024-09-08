/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:04:00 by itykhono          #+#    #+#             */
/*   Updated: 2024/09/08 16:40:03 by itykhono         ###   ########.fr       */
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
		minishell->tokens = NULL;
		minishell->input = readline(PROMPT);
		if (ft_input_is_valid(minishell->input) == false) //initial valisdation
		{
			//ERROR Occured
			//TODO: free alocated mem, continue reading from line
			printf("Mini_hell: syntax error\n");
		}
		init_tokens(minishell);
		if (validate_tokens(minishell->tokens) < 0)
		{
			//ERROR Occured
			// printing is inside the validate_tokens func
			//TODO: free alocated mem, continue reading from line
			//free()
			// break;
		}

		minishell->commands = parse_tokens(minishell->tokens, NULL);
		minishell->commands = NULL;

		//Uncomment to Test Tokens
// =================================================================================
		// while (minishell->tokens != NULL)
		// {
		// 	printf("%s = %d\n", minishell->tokens->value, minishell->tokens->type);
		// 	minishell->tokens = minishell->tokens->next;
		// }
// =================================================================================
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
		//Uncomment to CheckUp ENV
//=================================================================================
	// print_environment(minishell.env);
//=================================================================================

	environment_free_list(minishell.env);
	minishell_loop(&minishell);
	return (0);
}
