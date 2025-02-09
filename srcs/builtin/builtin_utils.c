/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 23:04:40 by habouda           #+#    #+#             */
/*   Updated: 2025/02/09 23:05:57 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_home_dir(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "HOME=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

static char	*create_env_string(const char *name, const char *value)
{
	int		i;
	int		len;
	char	*new_var;

	i = 0;
	len = 0;
	new_var = malloc(ft_strlen(name) + ft_strlen(value) + 2);
	if (!new_var)
		return (NULL);
	while (name[i])
		new_var[len++] = name[i++];
	new_var[len++] = '=';
	i = 0;
	while (value[i])
		new_var[len++] = value[i++];
	new_var[len] = '\0';
	return (new_var);
}

static int	update_existing_env(char **envp, const char *name, char *new_var)
{
	int	i;
	int	name_len;

	i = 0;
	name_len = ft_strlen(name);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, name_len) == 0
			&& envp[i][name_len] == '=')
		{
			free(envp[i]);
			envp[i] = new_var;
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_setenv(char **envp, char *name, char *value)
{
	char	*new_var;
	int		i;

	i = 0;
	new_var = create_env_string(name, value);
	if (!new_var)
		return (-1);
	if (update_existing_env(envp, name, new_var))
		return (0);
	while (envp[i])
		i++;
	envp[i] = new_var;
	envp[i + 1] = NULL;
	return (0);
}

void	update_pwd_vars(char **env)
{
	char	*oldpwd;
	char	current_dir[1024];

	oldpwd = getenv("PWD");
	if (oldpwd)
		ft_setenv(env, "OLDPWD", oldpwd);
	if (getcwd(current_dir, sizeof(current_dir)))
		ft_setenv(env, "PWD", current_dir);
}
