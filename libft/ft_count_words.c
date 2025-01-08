/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 18:55:12 by habouda           #+#    #+#             */
/*   Updated: 2025/01/04 18:55:54 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_words(const char *str, char c)
{
	int	word;
	int	counter;

	word = 0;
	counter = 0;
	while (*str)
	{
		if (*str != c && !word)
		{
			word = 1;
			counter++;
		}
		if (*str == c && word)
			word = 0;
		str++;
	}
	return (counter);
}
