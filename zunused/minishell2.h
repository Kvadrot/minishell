/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell2.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:29:06 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/15 18:50:36 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL2_H
# define MINISHELL2_H

# include <stdio.h>
# include <stdlib.h>

typedef struct s_data
{
	char	*input;
	char	**cinput;
	int		**pipe_argv;
	int		num_of_cmds;
}			t_data;

void		do_single_comand(void);
void		create_pipes(t_data *minishell);
void		setup_pipes(t_data *minishell);

void		panic(char *str);

#endif