/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 20:33:18 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/10 18:32:09 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

typedef struct s_execcmd
{
	int		type;
	char	*argv[MAXARGS];
	char	*eargv[MAXARGS];
	char	*paths;
	char	*flag;
}			t_execcmd;

char	*construct_full_path(const char *base_path, const char *cmd)
{
	char	*full_path;
	size_t	base_len;
	size_t	cmd_len;

	base_len = strlen(base_path);
	cmd_len = strlen(cmd);
	full_path = malloc(base_len + 1 + cmd_len + 1);
	if (full_path == NULL)
		return (NULL);
	strcpy(full_path, base_path);
	strcat(full_path, "/");
	strcat(full_path, cmd);
	return (full_path);
}

bool	is_executable(const char *path)
{
	return (access(path, X_OK) == 0);
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
		if (is_executable(full_path))
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}
