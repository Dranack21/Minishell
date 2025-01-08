/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:48:43 by habouda           #+#    #+#             */
/*   Updated: 2025/01/04 19:01:33 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	char_pos(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
	{
		i++;
	}
	return (i);
}

static void	ft_free(char **split)
{
	int		k;

	k = 0;
	while (split[k])
	{
		free(split[k]);
		k++;
	}
	free (split);
}

static char	*array(const char *s, char c)
{
	int		i;
	char	*split;

	i = char_pos (s, c);
	split = malloc(sizeof(char) * (i + 1));
	if (!split)
	{
		free (split);
		return (NULL);
	}
	ft_strlcpy(split, s, i + 1);
	split[i] = '\0';
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		j;

	split = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	j = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			split[j] = array(s, c);
			if (!split[j++])
			{
				ft_free(split);
				return (NULL);
			}
			s = s + char_pos(s, c);
		}
	}
	split[j] = NULL;
	return (split);
}
