/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:04:00 by itykhono          #+#    #+#             */
/*   Updated: 2024/08/21 15:01:49 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

//1) COPY ENV
//2) Validate input
//3) Lexer (String -> Tokens)
//4) Parser (Tokens -> Logical_groups -> cmd_groups)
int	main (int argc, char **argv)
{
	ft_input_is_valid(argv, argc);
	while (1)
	{
	}
	return (0);
}
