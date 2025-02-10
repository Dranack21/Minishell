/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 23:05:51 by habouda           #+#    #+#             */
/*   Updated: 2025/02/10 18:40:07 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_env(char **envp)
{
	char	**env;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	env = malloc((i + 2) * sizeof(char *));
	if (!env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		if (!env[i])
		{
			while (i--)
				free(env[i]);
			free(env);
			return (NULL);
		}
		i++;
	}
	env[i] = NULL;
	env[i + 1] = NULL;
	return (env);
}

// char	**copy_env2(char **envp, t_shell)
// {
// 	char	**env;
// 	int		i;

// 	i = 0;
// 	while (envp[i])
// 		i++;
// 	env = malloc((i + 1) * sizeof(char *));
// 	if (!env)
// 		return (NULL);
// 	i = 0;
// 	while (envp[i])
// 	{
// 		env[i] = ft_strdup(envp[i]);
// 		if (!env[i])
// 		{
// 			while (i--)
// 				free(env[i]);
// 			free(env);
// 			return (NULL);
// 		}
// 		i++;
// 	}
// 	env[i] = NULL;
// 	return (env);
// }

int	get_path(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	if (!envp[i])
		return (-1);
	return (i);
}
