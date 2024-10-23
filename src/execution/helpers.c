/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:45:19 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/10/23 11:46:05 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/** TODO: find_path
* @brief: look for path and returns it if it was found
* @takes: command and environment
//=======================================================================//
* @HOW_IT_works:
// envp[i] contains "PATH=/bin:/usr/bin:/some/other/dir"
// skip the "PATH=" (5 characters) and split the directories by ':'
// Construct the full path to the command
// If access fails, free the current path and move to the next directory
// Free the paths array if the command was not found
// Return NULL if the command was not found in any path
//=======================================================================//
* @returns: path
*/

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}

int	count_args(t_command_full *cmd)
{
	int				i;
	t_command_full	*tmp;

	i = 0;
	tmp = cmd;
	if (cmd->args == NULL)
		return (0);
	while (tmp->args[i] != NULL)
		i++;
	return (i);
}

/** TODO: make_exec_args
* @brief: builds array of strngs which we gonna use in execve func
* @takes: command
//=======================================================================//
* @HOW_IT_works:
// allocates memory for array (+2 for cmd_name and NULL)
// the first elememt is command name, the last elememt is NULL
//=======================================================================//
* @returns: array of strings for execve
*/

char	**make_exec_args(t_command_full *cmd)
{
	int		arg_count;
	char	**res;
	int		i;

	arg_count = count_args(cmd);
	res = malloc(sizeof(char *) * (arg_count + 2));
	if (!res)
		return (NULL);
	res[0] = cmd->cmd_name;
	i = 0;
	while (i < arg_count)
	{
		res[i + 1] = cmd->args[i];
		i++;
	}
	res[arg_count + 1] = NULL;
	return (res);
}

void	execute(char **envp, t_command_full *cmd)
{
	int		i;
	char	*path;
	char	**exec_args;

	i = -1;
	path = find_path(cmd->cmd_name, envp);
	if (!path)
	{
		ft_putstr_fd("Error: command not found in PATH\n", 2);
		exit(EXIT_FAILURE);
	}
	exec_args = make_exec_args(cmd);
	if (!exec_args)
	{
		free(path);
		ft_putstr_fd("Error: failed to create exec arguments\n", 2);
		exit(EXIT_FAILURE);
	}
	if (execve(path, exec_args, envp) == -1)
	{
		free(exec_args);
		free(path);
		ft_putstr_fd("Error executing the command\n", 2);
		exit(EXIT_FAILURE);
	}
}
