/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_erraser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:44:48 by ufo               #+#    #+#             */
/*   Updated: 2024/11/24 16:41:44 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Function prototypes (declarations)
char	*ft_malloc_cleaned_arg(char *temp_arg, t_data **minishell);
void	ft_process_arg(char **temp_arg, char *cleaned_arg, int *old_counter,
			int *clean_counter);
void	ft_toggle_quote(char *temp_arg, char *cleaned_arg, int *old_counter,
			int *clean_counter);

// Function definitions

char	*ft_errase_quote(t_data **minishell, char **temp_arg)
{
	char	*cleaned_arg;
	int		old_counter;
	int		clean_counter;

	old_counter = 0;
	clean_counter = 0;
	cleaned_arg = ft_malloc_cleaned_arg(*temp_arg, minishell);
	ft_process_arg(temp_arg, cleaned_arg, &old_counter, &clean_counter);
	cleaned_arg[clean_counter] = '\0';
	free(*temp_arg);
	return (cleaned_arg);
}

char	*ft_malloc_cleaned_arg(char *temp_arg, t_data **minishell)
{
	char	*cleaned_arg;

	cleaned_arg = (char *)malloc(ft_strlen(temp_arg) + 1);
	if (!cleaned_arg)
		ft_handle_error(true, "Malloc_error in ft_errase_quote", 433,
			minishell);
	return (cleaned_arg);
}

void	ft_process_arg(char **temp_arg, char *cleaned_arg, int *old_counter,
		int *clean_counter)
{
	while ((*temp_arg)[*old_counter] != '\0')
	{
		if ((*temp_arg)[*old_counter] == '\''
			|| (*temp_arg)[*old_counter] == '\"')
			ft_toggle_quote(*temp_arg, cleaned_arg, old_counter, clean_counter);
		else
		{
			cleaned_arg[*clean_counter] = (*temp_arg)[*old_counter];
			(*clean_counter)++;
			(*old_counter)++;
		}
	}
}

void	ft_toggle_quote(char *temp_arg, char *cleaned_arg, int *old_counter,
		int *clean_counter)
{
	static char	quote_char = '\0';

	if (quote_char == '\0')
		quote_char = temp_arg[*old_counter];
	else if (quote_char == temp_arg[*old_counter])
		quote_char = '\0';
	else
	{
		cleaned_arg[*clean_counter] = temp_arg[*old_counter];
		(*clean_counter)++;
	}
	(*old_counter)++;
}
