/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:45:00 by itykhono          #+#    #+#             */
/*   Updated: 2024/11/23 18:01:45 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_free_token_list(t_tokens **token_list)
{
	t_tokens	*temp;
	t_tokens	*temp_next;

	if (*token_list)
	{
		temp = *token_list;
		temp_next = NULL;
		while (temp)
		{
			temp_next = temp->next;
			if (temp->value)
			{
				free(temp->value);
				temp->value = NULL;
			}
			free(temp);
			temp = NULL;
			temp = temp_next;
		}
		*token_list = NULL;
	}
}

void	ft_free_minishell(t_data **minishell, bool is_crash)
{
	if (*minishell == NULL)
		return ;
	if ((*minishell)->input)
		(*minishell)->input = NULL;
	if ((*minishell)->tokens)
		ft_free_token_list(&((*minishell)->tokens));
	if ((*minishell)->env && is_crash)
	{
		environment_free_list((*minishell)->env);
		(*minishell)->env = NULL;
	}
	if ((*minishell)->commands)
		ft_free_commands(minishell);
	if (is_crash == true)
	{
		free(*minishell);
		*minishell = NULL;
	}
}

void	ft_handle_error(bool is_crashable, char *error_text,
	int err_status, t_data **minishell)
{
	if (error_text)
		ft_printf("ERROR: %s ERR_status: %d\n", error_text, err_status);
	if (is_crashable)
	{
		ft_free_minishell(minishell, is_crashable);
		free(*minishell);
		*minishell = NULL;
		exit(1);
	}
	else
		ft_free_minishell(minishell, is_crashable);
}
