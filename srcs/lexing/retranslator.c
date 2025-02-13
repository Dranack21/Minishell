/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retranslator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 22:33:59 by habouda           #+#    #+#             */
/*   Updated: 2025/02/13 01:28:36 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	translate_variable(char *str, int *i, char *expanded, char **env)
{
	char	*name;
	char	*val;
	int		j;

	j = ft_strlen(expanded);
	name = is_var_name(str, i);
	if (!name)
		return (j);
	val = get_env_value(name, env);
	if (val)
	{
		ft_strlcat(expanded, val, new_expanded_length(str, env) + 1);
		j += ft_strlen(val);
	}
	free(name);
	return (j);
}

static int	copy_char(char c, char *expanded, int j)
{
	expanded[j] = c;
	expanded[j + 1] = '\0';
	return (j + 1);
}

void	new_traductor(t_token *token, char *envp[], t_shell *shell)
{
	t_token	*current;
	char	*processed_str;

	current = token;
	while (current)
	{
		if (position_dollar(current->str) != -1
			&& is_single_dollar(current->str) == 0)
		{
			if (position_dollar(current->str) == -2)
				processed_str = expand_exit_new(current->str, shell->exit_code,
						current->quote_type);
			else
				processed_str = over_translating(current->str, envp,
						current->quote_type);
			if (processed_str)
			{
				free(current->str);
				current->str = processed_str;
			}
		}
		current = current->next;
	}
}

char	*over_translating(char *str, char **env, int quote_type)
{
	int		i;
	int		j;
	char	*expanded;

	i = 0;
	j = 0;
	expanded = malloc(new_expanded_length(str, env) + 2);
	if (!expanded)
		return (NULL);
	expanded[0] = '\0';
	while (str[i])
	{
		if (str[i] == '$' && quote_type != 1)
			j = translate_variable(str, &i, expanded, env);
		else
			j = copy_char(str[i], expanded, j);
		i++;
	}
	expanded[j] = '\0';
	return (expanded);
}

int	new_expanded_length(char *str, char **env)
{
	char	*name;
	char	*val;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			name = is_var_name(str, &i);
			if (name)
			{
				val = get_env_value(name, env);
				if (val)
					len += ft_strlen(val);
				free(name);
			}
		}
		else
			len++;
		i++;
	}
	return (len);
}
