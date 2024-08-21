/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 21:48:08 by marvin            #+#    #+#             */
/*   Updated: 2024/08/21 14:28:10 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


# include "./lib_ft/libft.h"
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>

// DRBUG_FIELD
// DELETE ME befor release
//========================================================================================//
# include "./lib_ft_printf/ft_printf.h"
//========================================================================================//
typedef struct s_env
{
	char			*key;
	char			*value;
	struct t_env	*next;
}					t_env;

#endif