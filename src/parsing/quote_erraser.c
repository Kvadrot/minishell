/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_erraser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:44:48 by ufo               #+#    #+#             */
/*   Updated: 2024/10/31 16:31:24 by ufo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char    *ft_errase_quote(t_data **minishell, char **temp_arg)
{
    char    *cleaned_arg;
    int     old_counter;
    int     clean_counter;
    char    quote_char; // Track which quote we're in (if any)

    old_counter = 0;
    clean_counter = 0;
    quote_char = '\0';
    cleaned_arg = (char *)malloc(ft_strlen(*temp_arg) + 1);
    if (!cleaned_arg)
        ft_handle_error(true, "Malloc_error in ft_errase_quote", 433, *minishell);

    while ((*temp_arg)[old_counter] != '\0')
    {
        // '"wefwef defwef '$das'"'
        if ((*temp_arg)[old_counter] == '\'' || (*temp_arg)[old_counter] == '\"')
        {
            if (quote_char == '\0')
                quote_char = (*temp_arg)[old_counter];
            else if (quote_char == (*temp_arg)[old_counter])
                quote_char = '\0';
            else
            {
                cleaned_arg[clean_counter] = (*temp_arg)[old_counter];
                clean_counter++;
            }
            old_counter++;
            continue ;
        }
        cleaned_arg[clean_counter] = (*temp_arg)[old_counter];
        clean_counter++;
        old_counter++;
    }

    cleaned_arg[clean_counter] = '\0';
    free(*temp_arg);
    // *temp_arg = cleaned_arg; // Update the string in-place
    return (cleaned_arg);
}
