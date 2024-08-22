/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 21:48:08 by marvin            #+#    #+#             */
/*   Updated: 2024/08/22 21:44:16 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

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

#endif
