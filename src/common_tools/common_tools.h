/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_tools.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:34:37 by ufo               #+#    #+#             */
/*   Updated: 2024/11/23 16:52:21 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**append_string_to_array(char *new_str, char **args);
char	*ft_join_with_delimeter(char *s1, char *s2, char *delimiter);
int		ft_strcmp(const char *str1, const char *str2);