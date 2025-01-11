/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:41:36 by habouda           #+#    #+#             */
/*   Updated: 2024/07/03 19:31:10 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_hexa_upper(size_t num)
{
	char			*charset;
	char			*stash;
	int				i;
	unsigned int	n;

	n = (unsigned int)num;
	i = 8;
	charset = "0123456789ABCDEF";
	if (n == 0)
		return (ft_putstr("0"), 1);
	stash = malloc(9 * sizeof(char));
	stash[8] = '\0';
	while (n)
	{
		stash[--i] = (charset[n % 16]);
		n = n / 16;
	}
	ft_putstr(stash + i);
	return (free (stash), 8 - i);
}

int	ft_hexa_lower(size_t num)
{
	char			*charset;
	char			*stash;
	int				i;
	unsigned int	n;

	n = (unsigned int)num;
	i = 8;
	charset = "0123456789abcdef";
	if (n == 0)
		return (ft_putstr("0"), 1);
	stash = malloc(9 * sizeof(char));
	stash[8] = '\0';
	while (n)
	{
		stash[--i] = (charset[n % 16]);
		n = n / 16;
	}
	ft_putstr(stash + i);
	return (free (stash), 8 - i);
}

int	ft_chungli(size_t num)
{
	char			*charset;
	char			*stash;
	int				i;
	unsigned long	n;

	n = (unsigned long)num;
	i = 16;
	charset = "0123456789abcdef";
	if (n == 0)
		return (ft_putstr("0"), 1);
	stash = malloc(17 * sizeof(char));
	stash[16] = '\0';
	while (n)
	{
		stash[--i] = (charset[n % 16]);
		n = n / 16;
	}
	ft_putstr(stash + i);
	return (free (stash), 16 - i);
}

int	ft_pointer(void *ptr)
{
	int	i;

	if (!ptr)
		return (write(1, "(nil)", 5));
	i = 2;
	write(1, "0x", 2);
	i = i + ft_chungli((size_t)ptr);
	return (i);
}

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}
