/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 23:05:27 by habouda           #+#    #+#             */
/*   Updated: 2025/02/10 19:05:01 by habouda          ###   ########.fr       */
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

char	**copy_env2(t_shell *shell, char **env)
{
	int		i;
	char	**new;
	char	*exit;
	char	*new_exit;

	exit = ft_itoa(shell->exit_code);
	new_exit = ft_strjoin("?=", exit);
	i = 0;
	new = copy_env(env);
	while (new[i])
		i++;
	free (new[i - 1]);
	new[i - 1] = ft_strdup(new_exit);
	if (!new[i - 1])
		ft_free_array(new);
	free(new_exit);
	return (new);
}
