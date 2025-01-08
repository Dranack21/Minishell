/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 00:33:49 by habouda           #+#    #+#             */
/*   Updated: 2024/05/27 14:05:04 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr_s;
	unsigned char	ptr_c;

	i = 0;
	ptr_s = ((unsigned char *)s);
	ptr_c = ((unsigned char)c);
	while (i < n)
	{
		if (*(ptr_s + i) == ptr_c)
			return ((void *)(ptr_s + i));
		i++;
	}
	return (NULL);
}

/*Used *ptr_s and ptr_c to cast
 *s and c to unsigned char and use them since memory blocks
  opperates on unsigned char
 */