/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 21:48:08 by marvin            #+#    #+#             */
/*   Updated: 2024/08/29 13:36:38 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define MAX_TOKENS 100

# include "minishell.h"

typedef struct s_command
{
	char				**args;
	char				*input_redirection;
	char				*output_redirection;
	char				*heredoc_delimiter;
	char				*output_append;
	struct s_command	*next;
}						t_command;

#endif
