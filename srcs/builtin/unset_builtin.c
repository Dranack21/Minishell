/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 23:04:51 by habouda           #+#    #+#             */
/*   Updated: 2025/02/10 01:58:37 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_token *tokens, char **env)
{
	t_token	*curr;
	int		i;
	int		j;
	int		len;

	curr = tokens->next;
	while (curr)
	{
		i = 0;
		while (env[i])
		{
			len = ft_strlen(curr->str);
			if (ft_strncmp(env[i], curr->str, len) == 0 && env[i][len] == '=')
			{
				free(env[i]);
				j = i - 1;
				while (env[++j])
					env[j] = env[j + 1];
				break ;
			}
			i++;
		}
		curr = curr->next;
	}
	return (EXIT_SUCCESS);
}
