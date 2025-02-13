/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 23:04:50 by habouda           #+#    #+#             */
/*   Updated: 2025/02/12 23:01:46 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**mini_update_env(char ***env, char *var, char *name)
{
	int		i;
	char	**new_env;

	i = 0;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], name, ft_strlen(name)) == 0
			&& ((*env)[i][ft_strlen(name)] == '='
				|| (*env)[i][ft_strlen(name)] == '\0'))
		{
			free((*env)[i]);
			(*env)[i] = ft_strdup(var);
			free(name);
			return (NULL);
		}
		i++;
	}
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
	{
		free(name);
		return (NULL);
	}
	return (new_env);
}

int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !*str || !ft_isdigit(*str))
		return (1);
	i = 0;
	while (str[i])
	{
		if (!str[i])
			return (0);
		if (ft_isalpha(str[i]) == 1 && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

char	*get_var_name(char *str)
{
	int		i;
	char	*name;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (i > 0 && str[i] == '=' && str[i - 1])
		name = ft_strndup(str, i);
	else
		return (NULL);
	return (name);
}

void	update_env_var(char ***env, char *var)
{
	int		i;
	char	*name;
	char	**new_env;

	name = get_var_name(var);
	if (!name)
		return ;
	new_env = mini_update_env(env, var, name);
	if (!new_env)
		return ;
	i = 0;
	while ((*env)[i])
	{
		new_env[i] = (*env)[i];
		i++;
	}
	new_env[i] = ft_strdup(var);
	new_env[i + 1] = NULL;
	free(*env);
	*env = new_env;
	free(name);
}

int	ft_export(t_token *token, char ***env, t_shell *data)
{
	char	*name;

	if (!token || !token->next)
		return (handle_export_issue(token, env, data), 0);
	token = token->next;
	name = get_var_name(token->str);
	if (name == NULL)
	{
		if (token->next)
			token = token->next;
		printf("export: `%s': not a valid identifier \n", token->str);
		return (data->exit_code = 1, EXIT_FAILURE);
	}
	while (token)
	{
		if (is_valid_identifier(name) == 0)
			update_env_var(env, token->str);
		else
		{
			printf("no, write better %s\n", token->str);
			data->exit_code = 1;
		}
		token = token->next;
	}
	return (free(name), data->exit_code = 0, EXIT_SUCCESS);
}
