/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 23:05:27 by habouda           #+#    #+#             */
/*   Updated: 2025/02/13 01:08:04 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_for_quotes(char *rl)
{
	int	i;

	i = 0;
	while (rl[i])
	{
		if (rl[i] == '\'')
		{
			i++;
			while (rl[i] && rl[i] != '\'')
				i++;
			if (!rl[i])
				return (EXIT_FAILURE);
		}
		if (rl[i] == '"')
		{
			i++;
			while (rl[i] && rl[i] != '"')
				i++;
			if (!rl[i])
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int is_single_dollar(char *str)
{
    int    i;

    if (position_dollar(str) != -1 && position_dollar(str) != -2)
        i = position_dollar(str);
    else 
        return (0);
    while (str[i])
    {
        if (str[i] == '_' || (str[i] >= 'a' && str[i] <= 'z')
                || (str[i] >= 'A' && str[i] <= 'Z') 
                || (str[i] >= '0' && str[i] <= '9'))
        {
            return (0);
        }
        i++;
    }
    return (1);
}