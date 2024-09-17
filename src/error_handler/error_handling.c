/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:45:00 by itykhono          #+#    #+#             */
/*   Updated: 2024/09/17 13:51:05 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_handle_error(bool is_crashable, char *error_text, int err_status)
{
	char *path;

	ft_printf("ERROR: %s, ERR_status: %d", error_text, err_status);
}

void	ft_free_minishell(t_data *entire_data)
{
	if (entire_data->input)
		free(entire_data->input);
	if (entire_data->envir)
		environment_free_list(entire_data->env);

	free(entire_data->input);
	free(entire_data->input);
	free(entire_data->input);
	free(entire_data->input);
	free(entire_data->input);

}

// typedef struct s_data
// {
// 	char			*input;
// 	char			**envir;
// 	char			*environment;
// 	int				stdin;
// 	int				stdout;
// 	t_tokens		*tokens;
// 	t_env			*env;
// 	t_command_full		*commands;
// 	struct termios	terminal;
// 	struct s_data	*next;
// }					t_data;