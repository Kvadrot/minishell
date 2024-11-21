/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:31:38 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/11/21 17:34:26 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_sigint(int sig)
{
	(void) sig;
	write(1, "\n", 1);
	rl_on_new_line();
	// MARK: UNCOMMENT ME
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigquit(int sig)
{
	(void) sig;
	rl_on_new_line();
	rl_redisplay();
}

void	setup_signal_handlers(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = handle_sigquit;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

// int	termios_change(bool echo_ctl_chr)
// {
// 	struct termios	terminos_p;
// 	int				status;

// 	status = tcgetattr(STDIN_FILENO, &terminos_p);
// 	if (status == -1)
// 		return (1);
// 	if (echo_ctl_chr)
// 		terminos_p.c_lflag |= ECHOCTL;
// 	else
// 		terminos_p.c_lflag &= ~(ECHOCTL);
// 	status = tcsetattr(STDIN_FILENO, TCSANOW, &terminos_p);
// 	if (status == -1)
// 		return (1);
// 	return (0);
// }