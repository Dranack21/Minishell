/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_digit_or_float.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 22:53:19 by habouda           #+#    #+#             */
/*   Updated: 2025/01/04 15:38:55 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_digit_or_float(char *str)
{
	int	i;
	int	dot;

	dot = 0;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			i++;
		else if (str[i] == '.')
		{
			if (dot == 1)
				return (write(2, "not a correct float\n", 20), 0);
			dot = 1;
			i++;
		}
		else
			return (write(2, "invalid character\n", 18), 0);
	}
	return (1);
}
