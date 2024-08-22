/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */


//1) COPY ENV
//2) Validate input
//3) Lexer (String -> Tokens)
//4) Parser (Tokens -> Logical_groups -> cmd_groups)

#include "../inc/minishell.h"

void	minishell_loop(t_data *minishell)
{
	while (1)
	{
		minishell->input = readline(PROMPT);
		if (minishell->input == NULL) {
            ft_putendl_fd("\nCaught EOF (Ctrl+D)\n", STDOUT_FILENO); // diagnostics only delete before realase EOF
			minishell_free(minishell, YES);
            break;
        }
		ft_input_is_valid(minishell->input);
	}
}

void	init_minishell(t_data *minishell, char **env)
{
	minishell->envir = env;
	minishell->stdin = dup(0);
	minishell->stdout = dup(1);
	tcgetattr(STDIN_FILENO, &minishell->terminal);
	minishell->tracker = NULL;
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
