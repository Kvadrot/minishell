/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:02:50 by ssuchane          #+#    #+#             */
/*   Updated: 2024/09/03 16:12:17 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_syntax_error(t_parse_err error_type, const char *near_token)
{
	if (error_type == E_MEMORY)
		perror("Memory allocation failed");
	else if (error_type == E_SYNTAXERR)
		printf("bash: syntax error near unexpected token `%s'\n", near_token);
	else
		printf("bash: unknown error\n");
}

/* int	check_syntax(t_tokens *tokens)
{
	t_tokens	*current = tokens;
	t_tokens	*prev = NULL;

	while (current)
	{
		if ((current->type == T_PIPE || current->type == T_LESS
				|| current->type == T_GREAT || current->type == T_DLESS
				|| current->type == T_DGREAT) && (prev == NULL
				|| prev->type == T_PIPE || prev->type == T_LESS
				|| prev->type == T_GREAT || prev->type == T_DLESS
				|| prev->type == T_DGREAT))
		{
			print_syntax_error(E_SYNTAXERR, current->value);
			return (-1);
		}
		if (prev != NULL && (prev->type == T_PIPE || prev->type == T_LESS
				|| prev->type == T_GREAT || prev->type == T_DLESS
				|| prev->type == T_DGREAT) && (current->type != T_WORD))
		{
			print_syntax_error(E_SYNTAXERR, current->value);
			return (-1);
		}
		prev = current;
		current = current->next;
	}
	if (prev != NULL && (prev->type == T_PIPE || prev->type == T_LESS
			|| prev->type == T_GREAT || prev->type == T_DLESS
			|| prev->type == T_DGREAT))
	{
		print_syntax_error(E_SYNTAXERR, "newline");
		return (-1);
	}

	return (0);
} */
