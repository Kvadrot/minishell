/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_argv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 15:04:13 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/21 21:59:02 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Append a line to the argv array
*/
char	**ft_append_argv(char **argv, char *line)
{
	char	**new_argv;
	int		i;

	i = 0;
	while (argv && argv[i])
		i++;
	new_argv = malloc(sizeof(char *) * (i + 2));
	if (new_argv == NULL)
		ft_panic("malloc");
	i = 0;
	while (argv && argv[i])
	{
		new_argv[i] = ft_strdup(argv[i]);
		i++;
	}
	new_argv[i] = ft_strdup(line);
	new_argv[i + 1] = NULL;
	return (new_argv);
}
