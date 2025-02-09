/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 23:06:07 by habouda           #+#    #+#             */
/*   Updated: 2025/02/10 19:07:56 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	export_traductor(t_token *token, char *envp[])
{
	t_token	*current;
	char	*processed_str;

	current = token;
	while (current)
	{
		if (position_dollar(current->str) != -1)
		{
			processed_str = expanded_var(current->str, envp);
			if (processed_str)
			{
				free(current->str);
				current->str = processed_str;
			}
		}
		current = current->next;
	}
}

void	special_cases_export_traductor(t_token *current, t_shell *shell)
{
	if (handle_exit_code(current, shell) == 0)
		current = current->next;
}

int	handle_exit_code(t_token *token, t_shell *shell)
{
	char	*exit_str;

	if (ft_strcmp("$?", token->str) == 0)
	{
		exit_str = ft_itoa(shell->exit_code);
		if (exit_str)
		{
			free(token->str);
			token->str = exit_str;
			return (0);
		}
	}
	return (1);
}

char	*is_var_name(char *str, int *i)
{
	int		start;
	int		len;
	char	*name;

	start = *i + 1;
	len = 0;
	if (str[start] == '?')
		len = len + 0;
	else if (str[start] == '\0' || !(str[start] == '_' || (str[start] >= 'a'
				&& str[start] <= 'z') || (str[start] >= 'A'
				&& str[start] <= 'Z')))
		return (NULL);
	while (str[start + len] == '_' || (str[start + len] >= 'a' && str[start
				+ len] <= 'z') || (str[start + len] >= 'A' && str[start
				+ len] <= 'Z') || (str[start + len] >= '0' && str[start
				+ len] <= '9') || str[start + len] == '?')
		len++;
	name = malloc(len + 1);
	if (!name)
		return (NULL);
	ft_strncpy(name, &str[start], len);
	name[len] = '\0';
	*i += len;
	return (name);
}

void	handle_dollar_sign(t_expand *exp)
{
	char	*name;
	char	*val;

	name = is_var_name(exp->str, exp->i);
	if (name)
	{
		val = get_env_value(name, exp->env);
		if (val)
		{
			ft_strlcat(exp->expanded, val, calculate_expanded_length(exp->str,
					exp->env) + 1);
			*exp->j += ft_strlen(val);
		}
		free(name);
	}
}
