/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:04:00 by itykhono          #+#    #+#             */
/*   Updated: 2024/09/17 16:39:53 by itykhono         ###   ########.fr       */
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
		if (minishell->input != NULL && ft_strlen(minishell->input) > 0)
		{
			//TODO: add to history
			//add input to minishell history
			if (ft_input_is_valid(minishell->input) == false) //initial validation
			{
				free(minishell->input);
				ft_printf("Mini_hell: syntax error\n");
				continue;
			}
			init_tokens(minishell);
			if (validate_tokens(minishell->tokens) < 0)
			{
				ft_handle_error(false, NULL, -400, minishell);
				continue;
			}

			// minishell->commands = parse_tokens(minishell->tokens, NULL);
			// minishell->commands = NULL;

			//Uncomment to Test Tokens
	// =================================================================================
			while (minishell->tokens != NULL)
			{
				printf("%s = %d\n", minishell->tokens->value, minishell->tokens->type);
				minishell->tokens = minishell->tokens->next;
			}
	// =================================================================================
		}
	}
}

void	init_minishell(t_data **minishell, char **env)
{
	*minishell = (t_data *)malloc(sizeof(t_data));
	if (!minishell)
		(ft_handle_error(true, "ERROR is thrown by init_minishell - malloc\n", 433, *minishell));
	(*minishell)->envir = env;
	(*minishell)->stdin = dup(0);
	(*minishell)->stdout = dup(1);
	tcgetattr(STDIN_FILENO, &(*minishell)->terminal);
	(*minishell)->tokens = NULL;
}

int	main(int argc, char **argv, char **env)
{
	t_data	*minishell;

	(void)argc;
	(void)argv;
	init_minishell(&minishell, env);
	init_environment(&minishell, minishell->envir);
		//Uncomment to CheckUp ENV
//=================================================================================
	// print_environment(minishell.env);
//=================================================================================

	environment_free_list(minishell->env);
	minishell_loop(minishell);
	return (0);
}
