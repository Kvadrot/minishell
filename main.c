/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:04:00 by itykhono          #+#    #+#             */
/*   Updated: 2024/08/21 13:46:58 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//1) COPY ENV
//2) Validate input
//3) Lexer (String -> Tokens)
//4) Parser (Tokens -> Logical_groups -> cmd_groups)

#include "minishell.h"

void	init_minishell(t_data *minishell, char **env)
{
	minishell->envir = env;
}

int	main(int argc, char **argv, char **env)
{
	t_data	minishell;

	init_minishell(&minishell, env);
	init_environment(minishell.environment);
	while (1)
	{
	}
	return (0);
}
