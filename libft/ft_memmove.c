/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:14:32 by habouda           #+#    #+#             */
/*   Updated: 2024/05/22 12:21:41 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*p_dest;
	char	*p_src;

	p_src = (char *)src;
	p_dest = (char *)dest;
	if (p_src == p_dest || n == 0)
		return (dest);
	if (p_src < p_dest && p_src + n > p_dest)
	{
		i = n;
		while (i > 0)
		{
			i--;
			p_dest[i] = p_src[i];
		}
		return (dest);
	}
	i = 0;
	while (i < n)
	{
		p_dest[i] = p_src[i];
		i++;
	}
	return (dest);
}
