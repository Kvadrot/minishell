/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:04:00 by itykhono          #+#    #+#             */
/*   Updated: 2024/11/22 15:18:22 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// 1) COPY ENV
// 2) Validate input
// 3) Lexer (String -> Tokens)
// 4) Parser (Tokens -> Logical_groups -> cmd_groups)

#include "../inc/minishell.h"

int	last_exit_status = 0;

void	minishell_loop(t_data **minishell)
{
	struct termios term;
	
	while (1)
	{
		(*minishell)->tokens = NULL;
		tcgetattr(STDIN_FILENO, &term);
		if (!(term.c_lflag & ECHOCTL))
		{
			term.c_lflag |= ECHOCTL;
			tcsetattr(STDIN_FILENO, TCSANOW, &term);
		}
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
			if ((*minishell)->commands != NULL)
				exec_pipeline((*minishell)->commands, (*minishell)->envir, minishell);
			ft_free_minishell(minishell, false);
		}
	}
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

void	disable_echoctl(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term); // Get current terminal settings
	term.c_lflag &= ~ECHOCTL;       // Disable echoing of control characters
	tcsetattr(STDIN_FILENO, TCSANOW, &term); // Apply changes immediately
}

int	main(int argc, char **argv, char **env)
{
	t_data	*minishell;

	(void)argc;
	(void)argv;
	init_minishell(&minishell, env);
	setup_signal_handlers();
	disable_echoctl();
	init_environment(&minishell, minishell->envir);
	minishell_loop(&minishell);
	return (0);
}
