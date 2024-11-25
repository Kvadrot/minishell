/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:04:00 by itykhono          #+#    #+#             */
/*   Updated: 2024/11/24 18:32:06 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_last_exit_status = 0;

void	minishell_loop(t_data **minishell)
{
	while (1)
	{
		ft_free_token_list(&(*minishell)->tokens);
		ft_free_commands(minishell);
		reset_echoctl();
		(*minishell)->input = readline(PROMPT);
		if (handle_empty_input(minishell))
			break ;
		if (handle_whitespace_or_syntax(minishell))
			continue ;
		if (process_tokens(minishell))
			execute_commands(minishell);
	}
}

static void	init_minishell(t_data **minishell, char **env)
{
	*minishell = (t_data *)malloc(sizeof(t_data));
	if (!minishell)
		(ft_handle_error(true, "ERROR is thrown by init_minishell - malloc\n",
				433, minishell));
	(*minishell)->envir = env;
	(*minishell)->stdin = dup(0);
	(*minishell)->stdout = dup(1);
	tcgetattr(STDIN_FILENO, &(*minishell)->terminal);
	(*minishell)->tokens = NULL;
	(*minishell)->commands = NULL;
	(*minishell)->input = NULL;
}

/** disable_echoctl
 * @brief: Disables the echoing of control characters in the terminal.
 * @takes: void - This function does not take any arguments.
 * //=======================================================================//
 * @HOW_IT_works:
 * - Retrieves the current terminal settings using `tcgetattr`.
 * - Modifies the local terminal flags (`c_lflag`)
 *   to disable the `ECHOCTL` behavior.
 *   - `ECHOCTL` is responsible for displaying control characters
 *     (e.g., ^C) when typed.
 * - Applies the updated terminal settings immediately using
 *  `tcsetattr` with the `TCSANOW` option.
 * //=======================================================================//
 * @returns: void - No return value.
 */

void	disable_echoctl(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
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
