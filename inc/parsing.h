/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 21:48:08 by marvin            #+#    #+#             */
/*   Updated: 2024/09/05 18:27:51 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define MAX_TOKENS 100


typedef struct s_command
{
	char				**args;
	char				*input_redirection;
	char				*output_redirection;
	char				*heredoc_delimiter;
	char				*output_append;
	int					pipe;
	struct s_command	*next;
	struct s_command	*prev;
}						t_command;

#endif
