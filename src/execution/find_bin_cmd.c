/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_bin_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 20:33:18 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/19 19:12:48 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**get_paths(char *path_env)
{
	int		paths_count;
	int		i;
	char	**paths;

	paths_count = 1;
	i = -1;
	if (path_env == NULL)
		return (NULL);
	while (path_env[++i] != '\0')
		if (path_env[i] == ':')
			paths_count++;
	paths = malloc((paths_count + 1) * sizeof(char *));
	if (paths == NULL)
		return (NULL);
	paths = ft_split(path_env, ':');
	return (paths);
}

char	*construct_full_path(const char *base_path, const char *cmd)
{
	char	*full_path;
	size_t	base_len;
	size_t	cmd_len;
	size_t	total_len;

	base_len = ft_strlen(base_path);
	cmd_len = ft_strlen(cmd);
	total_len = base_len + 1 + cmd_len + 1;
	full_path = malloc(total_len);
	if (full_path == NULL)
		return (NULL);
	ft_strlcpy(full_path, base_path, total_len);
	ft_strlcat(full_path, "/", total_len);
	ft_strlcat(full_path, cmd, total_len);
	return (full_path);
}

char	*find_binary_path(t_cmd *cmd, char **paths)
{
	int			i;
	char		*full_path;
	t_execcmd	*ecmd;

	ecmd = (t_execcmd *)cmd;
	if (ecmd == NULL || ecmd->argv[0] == NULL || paths == NULL)
		return (NULL);
	i = 0;
	while (paths[i] != NULL)
	{
		full_path = construct_full_path(paths[i], ecmd->argv[0]);
		if (full_path == NULL)
			return (NULL);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	**retrieve_paths(void)
{
	char	*path_env;
	char	**paths;

	path_env = getenv("PATH");
	if (path_env == NULL)
	{
		handle_exec_error("PATH environment variable not found", "");
		exit(1);
	}
	paths = get_paths(path_env);
	if (paths == NULL)
	{
		handle_exec_error("Failed to get paths", "");
		exit(1);
	}
	return (paths);
}

char	*find_executable_path(t_execcmd *ecmd, char **paths)
{
	char	*binary_path;

	binary_path = find_binary_path((t_cmd *)ecmd, paths);
	if (binary_path == NULL)
	{
		handle_exec_error("command not found: ", ecmd->argv[0]);
		clean_up(NULL, paths);
		exit(1);
	}
	return (binary_path);
}
