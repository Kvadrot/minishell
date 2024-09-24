/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:44:56 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/19 19:15:50 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next;
	t_list	*curr;

	if (!lst || !*lst || !del)
		return ;
	curr = *lst;
	next = curr -> next;
	while (curr && next)
	{
		del(curr -> content);
		free(curr);
		curr = next;
		next = curr -> next;
	}
	del(curr -> content);
	free(curr);
	*lst = NULL;
}
