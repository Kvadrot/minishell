/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 21:48:08 by marvin            #+#    #+#             */
/*   Updated: 2024/09/08 16:40:34 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define MAX_TOKENS 100

# include "minishell.h"

typedef struct s_command
{
	char				**args;
	int					type;
	struct s_command	*left;
	struct s_command	*right;
}						t_command;

//parsing_utils.c
t_command	*init_branch(char **args, int type, t_command *left, t_command *right);
t_tokens	*ft_find_root_token(t_tokens *start_token, t_tokens *end_token);

//parsing.c
t_command	*parse_tokens(t_tokens *start_token, t_tokens *end_token);

#endif