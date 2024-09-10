/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_with_arrays.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:28:26 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/10 20:35:40 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

typedef struct s_pipe
{
	t_command	*left;
	t_command	*right;
}				t_pipe;

void parse(t_data *data)
{
	t_list		**pipe_list;
	
	look_for_pipe(data->tokens, pipe_list);
	
}