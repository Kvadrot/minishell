/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop_helpers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 19:09:05 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/11/26 16:07:07 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	reset_echoctl(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	if (!(term.c_lflag & ECHOCTL))
	{
		term.c_lflag |= ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}
}

bool	handle_empty_input(t_data **minishell)
{
	if (!(*minishell)->input)
	{
		ft_free_minishell(minishell, true);
		ft_printf("exit\n");
		return (true);
	}
	return (false);
}

bool	handle_whitespace_or_syntax(t_data **minishell)
{
	if (ft_is_only_whitespace((*minishell)->input))
	{
		free((*minishell)->input);
		return (true);
	}
	if (!ft_is_only_whitespace((*minishell)->input))
		add_history((*minishell)->input);
	if (ft_input_is_valid((*minishell)->input) == false)
	{
		free((*minishell)->input);
		ft_printf("Mini_hell: syntax error\n");
		return (true);
	}
	return (false);
}

bool	process_tokens(t_data **minishell)
{
	init_tokens(minishell);
	if (validate_tokens((*minishell)->tokens) < 0)
	{
		ft_handle_error(false, NULL, -400, minishell);
		return (false);
	}
	ft_parse_tokens(minishell);
	ft_expand_input(minishell);
	if (ft_process_redirection_list(minishell) < 0)
	{
		ft_handle_error(false, NULL, -400, minishell);
		return (false);
	}
	return (true);
}

void	execute_commands(t_data **minishell)
{
	char	**res;

	res = convert_env_to_array((*minishell)->env);
	if ((*minishell)->commands != NULL)
	{
		exec_pipeline((*minishell)->commands, res, minishell);
		free_array(res);
	}
}
