/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 21:48:08 by marvin            #+#    #+#             */
/*   Updated: 2024/09/07 12:38:28 by itykhono         ###   ########.fr       */
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
	struct s_command	*next;
	struct s_command	*prev;
}						t_command;

//parsing_utils.c
t_command	*init_branch(char **args, int type, t_command *next, t_command *prev);
t_tokens	*ft_get_searchebale_token(t_tokens *start_token);

//parsing.c
t_command	*parse_tokens(t_tokens *tokens);
t_command	*init_branch(char **args, int type, t_command *next, t_command *prev);

#endif