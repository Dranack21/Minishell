/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:50:30 by habouda           #+#    #+#             */
/*   Updated: 2024/05/22 22:25:58 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	character;

	character = c;
	i = ft_strlen(s);
	if (character == '\0')
	{
		while (*s)
			s++;
		return ((char *)s);
	}
	while (*s)
		s++;
	s--;
	while (i > 0)
	{
		if (*s == character)
			return ((char *)s);
		s--;
		i--;
	}
	return (0);
}
