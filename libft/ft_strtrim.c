/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:36:25 by habouda           #+#    #+#             */
/*   Updated: 2024/05/25 03:25:15 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ftf_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int			i;
	int			j;
	char		*buffer;
	size_t		length;

	i = 0;
	j = ft_strlen(s1);
	if (!*s1)
		return (ft_strdup(""));
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (j > i && ft_strchr(set, s1[j]))
		j--;
	length = j - i + 1;
	if (j == i && (ft_strchr(set, s1[i])))
		return (ft_strdup(""));
	buffer = ft_calloc(sizeof(char) * (length + 1), 1);
	if (!buffer)
		return (NULL);
	while (i-- > 0)
		s1++;
	ftf_strncpy(buffer, s1, length);
	return (buffer);
}
