/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 00:27:49 by habouda           #+#    #+#             */
/*   Updated: 2024/05/27 12:41:17 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ptr;
	t_list	*newnode;

	if (!lst || !(*f) || !(*del))
		return (NULL);
	ptr = NULL;
	while (lst)
	{
		newnode = ft_lstnew((*f)(lst->content));
		if (!newnode)
		{
			ft_lstclear(&ptr, del);
			return (NULL);
		}
		ft_lstadd_back (&ptr, newnode);
		lst = lst->next;
	}
	return (ptr);
}
