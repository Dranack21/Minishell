/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 23:05:47 by habouda           #+#    #+#             */
/*   Updated: 2025/02/10 06:08:05 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	position_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
			return (-2);
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

int	is_n_arg(char *arg)
{
	int	i;

	i = 1;
	if (arg[0] == '-')
	{
		while (arg[i] == 'n')
		{
			i++;
		}
		if (arg[i] != '\0')
			return (1);
		if (arg[i] == '\0' && arg[i - 1] == 'n')
			return (0);
	}
	return (1);
}

char	*get_env_value(char *var_name, char **env)
{
	char	*env_var;
	int		i;
	int		len;

	if (!var_name || var_name[0] == '\0')
		return (NULL);
	len = 0;
	while (var_name[len] && var_name[len] != '=')
		len++;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, len) == 0 && env[i][len] == '=')
		{
			env_var = env[i] + len + 1;
			return (env_var);
		}
		i++;
	}
	return (NULL);
}

char	*extract_var_name(char *str, int dollar_pos, int str_len)
{
	int		var_end;
	char	*var_name;

	var_end = dollar_pos + 1;
	while (var_end < str_len && (ft_isalnum(str[var_end])
			|| str[var_end] == '_'))
		var_end++;
	var_name = malloc(var_end - dollar_pos);
	if (!var_name)
		return (NULL);
	ft_strncpy(var_name, str + dollar_pos + 1, var_end - dollar_pos - 1);
	var_name[var_end - dollar_pos - 1] = '\0';
	return (var_name);
}
