/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:21:20 by ufo               #+#    #+#             */
/*   Updated: 2024/10/12 20:58:00 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_builtins(t_data **minishell);
void	ft_bi_echo(t_command_full *cmd);
int		builtin_pwd(void);
int		builtin_env(t_env *node);
int		builtin_cd(t_data **minishell);
int		builtin_export(t_data **minishell);
void	delete_node(t_env **head_ref, t_env *node_to_delete);
void	add_to_env(t_data **minishell, char *key, char *new_value);