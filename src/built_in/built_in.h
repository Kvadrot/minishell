/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:21:20 by ufo               #+#    #+#             */
/*   Updated: 2024/10/13 14:51:16 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_builtins(t_data **minishell);
int 	builtin_echo(char **args);
int		builtin_pwd(void);
int		builtin_env(t_env *node);
int		builtin_cd(t_data **minishell);
int		builtin_export(t_data **minishell);
void	builtin_unset(t_data **minishell);
void	builtin_exit(void);
