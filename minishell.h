/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 21:48:08 by marvin            #+#    #+#             */
/*   Updated: 2024/08/21 15:33:55 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./lib_ft/libft.h"
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

// DRBUG_FIELD
// DELETE ME befor release
//========================================================================================//
# include "./lib_ft_printf/ft_printf.h"
//========================================================================================//
typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_data
{
	char				**envir;
	char				*environment;
	struct s_minishell	*next;
	t_env				*env;
}						t_data;

t_env					*environment_new_node(char *key, char *value);
void					environment_new_node_end(t_env **head, char *key,
							char *value);
void					init_environment(t_env **environment, char **env);
void					environment_free_list(t_env *head);



// tester functions
void					print_environment(t_env *node);

#endif