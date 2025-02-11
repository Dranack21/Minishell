/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 23:06:07 by habouda           #+#    #+#             */
/*   Updated: 2025/02/10 05:56:18 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

int get_exit_str_len(int exit_status)
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
		if (position_dollar(current->str) != -1)
		{
			if (position_dollar(current->str) == -2)
				processed_str = expand_exit_status(current->str , shell->exit_code);
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


char	*expand_exit_status(char *str, int exit_status)
{
	int		i;
	int		j;
	int		in_quote;
	char	*expanded;
	char	*exit_str;

	i = 0;
	j = 0;
	in_quote = 0;
	expanded = malloc(exit_expanded_length(str, exit_status) + 1);
	if (!expanded)
		return (NULL);
	exit_str = ft_itoa(exit_status);
	if (!exit_str)
		return (free(expanded), NULL);
	expanded[0] = '\0';
	while (str[i])
	{
		if (str[i] == '\'')
			in_quote = !in_quote;
		if (!in_quote && str[i] == '$' && str[i + 1] == '?')
			handle_exit_var(expanded, exit_str, &i, &j);
		else
		{
			expanded[j] = str[i];
			expanded[j + 1] = '\0';
			j++;
		}
		i++;
	}
	return (free(exit_str), expanded[j] = '\0', expanded);
}

int	exit_expanded_length(char *str, int exit_status)
{
	int	len;
	int	i;
	int	in_quote;
	int	exit_len;

	len = 0;
	i = 0;
	in_quote = 0;
	exit_len = get_exit_str_len(exit_status);
	while (str[i])
	{
		if (str[i] == '\'')
			in_quote = !in_quote;
		else if (str[i] == '$' && str[i + 1] == '?' && !in_quote)
		{
			len += exit_len;
			i++;
		}
		else
			len++;
		i++;
	}
	return (len);
}
