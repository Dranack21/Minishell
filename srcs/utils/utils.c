/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 23:06:07 by habouda           #+#    #+#             */
/*   Updated: 2025/02/13 01:43:09 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	get_exit_str_len(int exit_status)
{
	char	*exit_str;
	int		len;

	exit_str = ft_itoa(exit_status);
	if (!exit_str)
		return (0);
	len = ft_strlen(exit_str);
	free(exit_str);
	return (len);
}

int	handle_exit_var(char *expanded, char *exit_str, int *i, int *j)
{
	int	exit_len;

	exit_len = ft_strlen(exit_str);
	ft_strlcat(expanded, exit_str, ft_strlen(expanded) + exit_len + 1);
	*j += exit_len;
	*i += 1;
	return (1);
}

void	export_traductor(t_token *token, char *envp[], t_shell *shell)
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
				processed_str = expand_exit_status(current->str,
						shell->exit_code);
			else
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

char	*is_var_name(char *str, int *i)
{
	int		start;
	int		len;
	char	*name;

	start = *i + 1;
	len = 0;
	if (str[start] == '\0' || !(str[start] == '_' || (str[start] >= 'a'
				&& str[start] <= 'z') || (str[start] >= 'A'
				&& str[start] <= 'Z')))
		return (NULL);
	while (str[start + len] == '_' || (str[start + len] >= 'a' && str[start
			+ len] <= 'z') || (str[start + len] >= 'A' && str[start
			+ len] <= 'Z') || (str[start + len] >= '0' && str[start
			+ len] <= '9'))
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
