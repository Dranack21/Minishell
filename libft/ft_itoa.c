/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:10:23 by habouda           #+#    #+#             */
/*   Updated: 2024/05/29 10:18:58 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	n_size(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*s;
	long	nb;
	int		k;

	k = n_size(n);
	nb = n;
	s = malloc (sizeof(char) * (k + 1));
	if (!s)
		return (NULL);
	if (nb < 0)
	{
		s[0] = '-';
		nb = -nb;
	}
	s[k] = '\0';
	while (nb >= 0)
	{
		s[--k] = (nb % 10) + ('0');
		nb = nb / 10;
		if (nb == 0)
			break ;
	}
	return (s);
}
