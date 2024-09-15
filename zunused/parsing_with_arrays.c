/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_with_arrays.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ja <ja@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:28:26 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/10 23:19:57 by ja               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void init_pipe(char **cinput, t_list **pipe_list, t_cmd *cmd);

typedef struct s_pipe
{
	t_command *left;
	t_command *right;
} t_pipe;

void parse(t_data *data)
{
	t_cmd *cmd;
	int status;

	cmd = look_for_cmd(data->cinput);
	if (!cmd)
	{
		printf("parse_error");
		return;
	}
	while (data->cinput[0][0] == '|' && data->cinput[0][0] != '\0')
	{
		add_pipe(data->cinput, data->pipe_list, cmd);
		cmd = look_for_cmd(data->cinput, data->pipe_list);
		if (!cmd)
		{
			printf("parse_error");
			return;
		}
	}

	look_for_cmd(data->cinput, data->pipe_list);
}

void init_pipe(char **cinput, t_list **pipe_list, t_cmd *cmd)
{
	t_pipe *pipe;

	if (cinput[0][0] != '|')
		return;
	pipe = malloc(sizeof(t_pipe));
	if (!pipe)
		panic("Malloc failed");
	pipe->left = cmd;
	pipe->right = NULL;
	ft_lstadd_back(pipe_list, ft_lstnew(pipe));
}

look_for_pipe(char **cinput, t_list **pipe_list)

{
