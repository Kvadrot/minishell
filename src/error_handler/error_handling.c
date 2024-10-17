/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:45:00 by itykhono          #+#    #+#             */
/*   Updated: 2024/10/17 12:15:23 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Function to free the args array in a command
void	free_command_args(t_command_full *cmd)
{
	if (cmd->args)
	{
		for (int i = 0; cmd->args[i] != NULL; i++)
		{
			free(cmd->args[i]);
		}
		free(cmd->args);
	}
}

void				ft_free_token_list(t_tokens *token_list)
{
	t_tokens *temp;
	t_tokens *temp_next;

	if (token_list)
	{
		temp = token_list;
		temp_next = NULL;
		while (temp)
		{
			temp_next = temp->next;
			free(temp->value);
			free(temp);
			temp = temp_next;
		}
	}
	// ft_printf("debug ft_free_token_list is done \n");
}

void	ft_free_minishell(t_data *entire_data)
{
	if (entire_data->input)
		free(entire_data->input);
	if (entire_data->env)
		environment_free_list(entire_data->env);
	if (entire_data->envir)
		ft_printf("TODO: free envir\n");
	if (entire_data->commands)
		ft_printf("TODO: free commands\n");
	if (entire_data->tokens)
		ft_free_token_list(entire_data->tokens);
}

void	ft_handle_error(bool is_crashable, char *error_text, int err_status, t_data *minishell)
{
	char *path;

	if (error_text)
		ft_printf("ERROR: %sERR_status: %d", error_text, err_status);
	if (is_crashable == true)
	{
		ft_free_minishell(minishell);
		exit(1);
	}
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