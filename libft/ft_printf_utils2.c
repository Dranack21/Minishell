/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:57:22 by habouda           #+#    #+#             */
/*   Updated: 2024/07/03 19:31:18 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr(int n)
{
	int	i;

	i = 0;
	if (n == -2147483648)
		return ((write(1, "-2147483648", 11)), 11);
	else
	{
		if (n < 0)
		{
			write(1, "-", 1);
			i = 1;
			n = -n;
		}
		while (n >= 10)
		{
			i = i + ft_putnbr(n / 10);
			n = n % 10;
		}
		i = i + ft_putchar(n + 48);
	}
	return (i);
}

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		return (ft_putstr("(null)"));
	}
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
	return (i);
}

int	ft_putunbr(int n)
{
	int					i;
	static unsigned int	k;

	i = 0;
	if (n >= 0)
		return (ft_putnbr(n));
	if (n < 0)
	{
		k = (unsigned int)n;
	}
	while (k >= 10)
	{
		i = i + ft_putnbr(k / 10);
		k = k % 10;
	}
	ft_putchar(k + 48);
	i++;
	return (i);
}
