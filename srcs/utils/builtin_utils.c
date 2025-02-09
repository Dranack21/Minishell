/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 23:05:45 by habouda           #+#    #+#             */
/*   Updated: 2025/02/09 23:05:57 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handle_export_issue(t_token *token, char ***env, t_shell *data)
{
	char	**env_copy;
	int		i;

	i = 0;
	if (token && !token->next)
	{
		env_copy = copy_env(*env);
		if (!env_copy)
		{
			data->exit_code = 1;
			return ;
		}
		while (env_copy[i])
		{
			printf("export ");
			printf("%s\n", env_copy[i]);
			free(env_copy[i]);
			i++;
		}
		free(env_copy);
		data->exit_code = 0;
	}
}
