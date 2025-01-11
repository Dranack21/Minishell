/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 00:01:02 by habouda           #+#    #+#             */
/*   Updated: 2024/05/26 00:21:42 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*ptr;
	t_list	*temp;

	ptr = *lst;
	while (ptr != NULL)
	{
		temp = ptr->next;
		(*del)(ptr->content);
		free (ptr);
		ptr = temp;
	}
	*lst = NULL;
}
