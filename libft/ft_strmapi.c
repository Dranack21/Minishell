/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:03:24 by habouda           #+#    #+#             */
/*   Updated: 2024/05/20 15:41:13 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	size_t		i;
	size_t		s_len;
	char		*dest;

	i = 0;
	s_len = ft_strlen(s);
	dest = malloc(sizeof(char) * s_len + 1);
	if (!dest)
		return (NULL);
	while (s[i])
	{
		dest[i] = (*f)(i, s[i]);
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
