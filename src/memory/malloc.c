/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ja <ja@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:33:12 by ja                #+#    #+#             */
/*   Updated: 2024/09/16 20:53:41 by ja               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// void malloc_int_array(int **destination, int size)
// function that allocates memory for an array of integers
// takes a pointer to an array of integers and the size of the array
// zero out the memory
void malloc_int_array(int **destination, int size)
{
	*destination = (int *)malloc((size * sizeof(int )));
	if (!(*destination))
		panic("malloc");
    ft_bzero(*destination, (size * sizeof(int)));
}