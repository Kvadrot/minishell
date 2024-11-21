/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:04:00 by itykhono          #+#    #+#             */
/*   Updated: 2024/11/21 17:34:41 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// 1) COPY ENV
// 2) Validate input
// 3) Lexer (String -> Tokens)
// 4) Parser (Tokens -> Logical_groups -> cmd_groups)

#include "../inc/minishell.h"

int last_exit_status = 0;

// void	restore_terminal_settings(t_data *minishell)
// {
// 	termios_change(true); // Re-enable ECHOCTL
// 	tcsetattr(STDIN_FILENO, TCSANOW, &minishell->terminal);
// }

void	minishell_loop(t_data **minishell)
{
	//setup_signal_handlers();
	// if (termios_change(true) == 1)
	// {
	// 	write(STDERR_FILENO, "Error: Failed to enable terminal settings\n", 43);
	// 	return ;
	// }
	while (1)
	{
		(*minishell)->tokens = NULL;
		(*minishell)->input = readline(PROMPT);
		if (!(*minishell)->input)
		{
			ft_free_minishell(minishell, true);
			ft_printf("exit\n");
			break ;
		}
		else if ((*minishell)->input != NULL && ft_strlen((*minishell)->input) > 0)
		{
			if (ft_is_only_whitespace((*minishell)->input))
			{
				free((*minishell)->input);
				continue ;
			}
			//TODO: add to history
			if (!ft_is_only_whitespace((*minishell)->input))
				add_history((*minishell)->input);
			if (ft_input_is_valid((*minishell)->input) == false) //initial validation
			{
				free((*minishell)->input);
				ft_printf("Mini_hell: syntax error\n");
				continue;
			}
			init_tokens((*minishell));
			if (validate_tokens((*minishell)->tokens) < 0)
			{
				ft_handle_error(false, NULL, -400, (minishell));
				continue;
			}
			//Uncomment to Test Tokens
		// =================================================================================
			// while ((*minishell)->tokens != NULL)
			// {
			// 	printf("%s = %d\n", (*minishell)->tokens->value, (*minishell)->tokens->type);
			// 	(*minishell)->tokens = (*minishell)->tokens->next;
			// }
		// =================================================================================
		//TODO:
			ft_parse_tokens(minishell);
			ft_expand_input(minishell);
			if (ft_process_redirection_list(minishell) < 0)
			{
				ft_handle_error(false, NULL, -400, minishell);
				continue;
			}
			//Uncomment to Test COMMANDS
			// ==================================================================================================================================
			// ft_printf("MAIN>C Calls debuger after parsing\n");
			// ft_debug_parsing(minishell);
			//==================================================================================================================================
			if ((*minishell)->commands != NULL)
			{
				exec_pipeline((*minishell)->commands, (*minishell)->envir, minishell);
			}
			ft_free_minishell(minishell, false);

			//("MINISHELL_NEW_LOOP");
		}
	}
	//restore_terminal_settings(*minishell);
}

void	init_minishell(t_data **minishell, char **env)
{
	*minishell = (t_data *)malloc(sizeof(t_data));
	if (!minishell)
		(ft_handle_error(true, "ERROR is thrown by init_minishell - malloc\n", 433, minishell));
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
	//setup_signal_handlers();
	init_environment(&minishell, minishell->envir);
//Uncomment to CheckUp ENV
//=================================================================================

	//print_environment(minishell->env);
//=================================================================================
	
	minishell_loop(&minishell);
	//restore_terminal_settings(&minishell);
	//environment_free_list(minishell->env);
	return (0);
}
