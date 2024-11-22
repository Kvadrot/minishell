/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:47:26 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/11/22 18:35:29 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	execute(char **envp, t_command_full *cmd);
void	child_process(t_command_full *cmd, char **envp);
void	handle_1_cmd(t_command_full *cmd, char **envp, t_data **minishell);
void	exec_pipeline(t_command_full *cmd_list, char **envp,
			t_data **minishell);
void	setup_heredoc(t_command_full *cmd);