/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 11:20:40 by itykhono          #+#    #+#             */
/*   Updated: 2024/08/13 13:57:55 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_free_split(char **split_result, int words_amount)
{
	int	i;

	if (!split_result)
		return (NULL);
	i = 0;
	while (i < words_amount)
	{
		free(split_result[i]);
		i++;
	}
	free(split_result);
	return (NULL);
}

static int	ft_get_words_amount(const char *source, char c)
{
	int		result;
	size_t	main_counter;

	result = 0;
	main_counter = 0;
	while (source[main_counter] != '\0')
	{
		while (source[main_counter] != '\0' && source[main_counter] == c)
			main_counter++;
		if (source[main_counter] != '\0')
			result++;
		while (source[main_counter] != '\0' && source[main_counter] != c)
			main_counter++;
	}
	return (result);
}

static int	func_logic(const char *s, char c, int *main_counter)
{
	int	sub_counter;

	sub_counter = 0;
	*main_counter = 0;
	while (s[*main_counter] != '\0' && s[*main_counter] == c)
		(*main_counter)++;
	if (s[*main_counter] == '\0')
		return (-1);
	sub_counter = *main_counter;
	while (s[sub_counter] != '\0' && s[sub_counter] != c)
		sub_counter++;
	return (sub_counter);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	char	*tempstr;
	int		words_counter;
	int		main_counter;
	int		sub_counter;

	if (!s)
		return (NULL);
	result = (char **)ft_calloc(ft_get_words_amount(s, c) + 1, sizeof(char *));
	main_counter = 0;
	words_counter = 0;
	while (*s)
	{
		sub_counter = func_logic(s, c, &main_counter);
		if (sub_counter == -1)
			break ;
		tempstr = ft_substr(s, main_counter, sub_counter - main_counter);
		s += sub_counter;
		if (!tempstr)
			return (ft_free_split(result, words_counter));
		result[words_counter] = tempstr;
		words_counter++;
	}
	result[words_counter] = NULL;
	return (result);
}
