/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 20:33:18 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/07 20:33:26 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_execcmd
{
	int		type;
	char	*argv[MAXARGS];
	char	*eargv[MAXARGS];
	char	*paths;
	char	*flag;
}			t_execcmd;

char	**get_paths(char *path_env)
{
	int		paths_count;
	int		i;
	char	**paths;

	if (path_env == NULL)
		return (NULL);
	paths_count = 1;
	i = -1;
	while (path_env[++i] != '\0')
		if (path_env[i] == ':')
			paths_count++;
	paths = malloc((paths_count + 1) * sizeof(char *));
	if (paths == NULL)
		return (NULL);
	paths = ft_split(path_env, ":");
	return (paths);
}

bool	check_binary(t_cmd *cmd, char **paths)
{
	int			i;
	char		*full_path;
	int			path_len;
	int			ecmd_len;
	t_execcmd	*ecmd;

	ecmd = (t_execcmd *)cmd;
	i = 0;
	full_path = NULL;
	if (ecmd == NULL || ecmd->argv[0] == NULL || paths == NULL)
		return (false);
	while (paths[i] != NULL)
	{
		path_len = strlen(paths[i]);
		ecmd_len = strlen(ecmd->argv[0]);
		full_path = malloc(path_len + 1 + ecmd_len + 1);
		if (full_path == NULL)
			return (false);
		strcpy(full_path, paths[i]);
		strcat(full_path, "/");
		strcat(full_path, ecmd->argv[0]);
		if (access(full_path, X_OK) == 0)
		{
			free(full_path);
			return (true);
		}
		free(full_path);
		i++;
	}
	return (false);
}