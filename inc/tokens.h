/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 21:48:08 by marvin            #+#    #+#             */
/*   Updated: 2024/09/03 15:57:29 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# define MAX_ARGS 128

# include "minishell.h"

typedef enum e_token_type
{
	T_WORD,
	T_LESS,
	T_GREAT,
	T_DLESS,
	T_DGREAT,
	T_PIPE,
}					t_token_type;

typedef struct s_tokens
{
	t_token_type	type;
	char			*value;
	t_command		*commands;
	struct s_tokens	*next;
}					t_tokens;

typedef enum e_parse_err
{
	E_MEMORY = 1,
	E_SYNTAXERR
}					t_parse_err;

typedef struct s_parse_error
{
	t_parse_err		type;
	char			*str;
}					t_parse_error;

#endif
