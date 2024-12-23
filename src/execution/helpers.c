/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:45:19 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/11/27 13:22:01 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

/** TODO: find_path
* @brief: looks for the executable file in directories listed in the PATH envir
* @takes: command and environment
//=======================================================================//
* @HOW_IT_WORKS:
// Searches through the directories in the PATH environment variable.
// Splits the PATH string into individual directories using ft_split.
// Joins each directory with the command (cmd) to form a potential full path.
// Uses access() to check if the command exists in the directory.
// If the command is found, frees the paths array and returns the full path.
// If no command is found, frees the paths array and returns NULL.
//=======================================================================//
* @returns: full path to the command if found,
// or NULL if the command is not found
*/

static char	**get_paths_from_env(char **envp)
{
	char	**paths;
	int		i;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	if (!envp[i])
	{
		ft_putstr_fd("Error: PATH envir var not found\n", 2);
		return (NULL);
	}
	paths = ft_split(envp[i] + 5, ':');
	if (!paths || !paths[0])
	{
		ft_putstr_fd("Error: PATH envir var is empty or invalid\n", 2);
		free_array(paths);
		return (NULL);
	}
	return (paths);
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	paths = get_paths_from_env(envp);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
		{
			free_array(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_array(paths);
	return (NULL);
}

void	execute(char **envp, t_command_full *cmd)
{
	char	*path;
	char	**exec_args;

	path = find_path(cmd->cmd_name, envp);
	if (!path)
	{
		ft_putstr_fd("Error: command not found\n", 2);
		exit(EXIT_FAILURE);
	}
	exec_args = cmd->args;
	if (execve(path, exec_args, envp) == -1)
	{
		free_array(exec_args);
		free(path);
		ft_putstr_fd("Error executing the command\n", 2);
		exit(EXIT_FAILURE);
	}
}
