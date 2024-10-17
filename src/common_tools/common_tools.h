/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_tools.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:34:37 by ufo               #+#    #+#             */
/*   Updated: 2024/10/17 12:48:04 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int     ft_get_size_arr_of_str(char **arr_of_str);
char    **append_string_to_array(char *new_str, char **args);
char    *ft_join_with_delimeter(char *s1, char *s2, char *delimiter);
int     ft_strcmp(const char *str1, const char *str2);


