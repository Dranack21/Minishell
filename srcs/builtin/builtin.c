/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 23:04:43 by habouda           #+#    #+#             */
/*   Updated: 2025/02/09 23:05:57 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_shell *shell)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("getcwd");
		shell->exit_code = 2;
		return (EXIT_FAILURE);
	}
	printf("%s\n", cwd);
	free(cwd);
	shell->exit_code = 0;
	return (EXIT_SUCCESS);
}

int	ft_envp(char **envp, t_shell *shell)
{
	while (*envp)
	{
		printf("%s\n", *envp);
		envp++;
	}
	shell->exit_code = 0;
	return (EXIT_SUCCESS);
}
