/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:23:52 by ssuchane          #+#    #+#             */
/*   Updated: 2024/09/07 20:04:16 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

typedef struct s_execcmd
{
	int				type;
	char			*argv[MAXARGS];
	char			*eargv[MAXARGS];
	char			*paths;
	bool			flag;
}					t_execcmd;

char	**get_paths(char *path_env)
{
	int		paths_count;
	int		i;
	char	**paths;
	char	*path_copy;

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
	path_copy = strdup(path_env);
	if (path_copy == NULL)
	{
		free(paths);
		return (NULL);
	}
	paths = ft_split(path_copy, ":");
	free(path_copy);
	return (paths);
}

bool	check_builtin(t_cmd *execcmd, char **paths)
{
	int i = 0;
	char *full_path = NULL;
	int path_len;
	int cmd_len;

	if (cmd == NULL || cmd->value == NULL || paths == NULL)
		return (false);
	while (paths[i] != NULL)
	{
		path_len = strlen(paths[i]);
		cmd_len = strlen(cmd->value);
		full_path = malloc(path_len + 1 + cmd_len + 1);
		if (full_path == NULL)
			return (false);
		strcpy(full_path, paths[i]);
		strcat(full_path, "/");
		strcat(full_path, cmd->value);
		if (access(full_path, X_OK) == 0)
		{
			free(full_path);
			return (true);
		}
		free(full_path);
		i++;
	}
}

int	check_flags(t_execcmd builtin, bool *new_line)
{
	int	i;

	i = 0;
	if (builtin->flag)
	{
		while (builtin->flag[i])
		{
			if (hell->flags[i++] != 'n')
			{
				ft_putstr_fd("invalid flag\n", 2);
				return (1);
			}
		}
		if (builtin->flag[0] == 'n')
			*new_line = false;
	}
	return (0);
}

int	do_echo(t_execcmd builtin)
{
	int		i;
	bool	new_line;
	int		status;

	i = 0;
	new_line = true;
	status = check_flags(&builtin, &new_line);
	if (builtin.argv && builtin.argv[0] != NULL)
	{
		ft_putstr_fd(builtin.argv[i], 1);
		i++;
		while (builtin.argv[i])
		{
			ft_putstr_fd(" ", 1);
			ft_putstr_fd(builtin.argv[i], 1);
			i++;
		}
	}
	if (new_line)
		ft_putstr_fd("\n", 1);
	return (status);
}

void do_builtin(t_execcmd * builtins)
{
	// before getting into this function check if the command exists with /path
	// use function check_builtin 
	if (builtins->type == ECHO)
		do_echo(builtins);
	else if (builtins->type == CD)
		do_cd(builtins)
}