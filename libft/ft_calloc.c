/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:08:53 by habouda           #+#    #+#             */
/*   Updated: 2024/05/29 10:10:13 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t siz)
{
	void	*array;
	size_t	total;

	total = siz * nmemb;
	if (siz != 0)
	{
		if (siz && (total) / siz != nmemb)
			return (NULL);
	}
	array = malloc (nmemb * siz);
	if (!array)
		return (NULL);
	ft_bzero(array, nmemb * siz);
	return (array);
}
