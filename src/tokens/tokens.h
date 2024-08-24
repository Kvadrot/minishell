/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 21:48:08 by marvin            #+#    #+#             */
/*   Updated: 2024/08/24 12:48:56 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# include "../../inc/minishell.h"

typedef enum e_token_type
{
	T_WORD,
	T_LESS,
	T_GREAT,
	T_DLESS,
	T_DGREAT,
	T_QUOTE,
	T_DQUOTE,
	T_PIPE,
	T_SEPARATOR,
}					t_token_type;

typedef struct s_tokens
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_tokens;

// t_tokens	*convert_input_to_tokens(t_data *minishell);

#endif
