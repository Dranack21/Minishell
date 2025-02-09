/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_translator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 23:05:15 by habouda           #+#    #+#             */
/*   Updated: 2025/02/09 23:05:57 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_regular_char(t_expand *exp)
{
	exp->expanded[*exp->j] = exp->str[*exp->i];
	exp->expanded[*exp->j + 1] = '\0';
	(*exp->j)++;
}

static void	process_string(t_expand *exp)
{
	int	in_single_quote;

	in_single_quote = 0;
	while (exp->str[*exp->i])
	{
		if (exp->str[*exp->i] == '\'')
			in_single_quote = !in_single_quote;
		if (exp->str[*exp->i] == '$' && !in_single_quote)
			handle_dollar_sign(exp);
		else
			handle_regular_char(exp);
		(*exp->i)++;
	}
}

static int	handle_env_var(char *str, int *i, char **env)
{
	char	*name;
	char	*val;
	int		len;

	len = 0;
	name = is_var_name(str, i);
	if (name)
	{
		val = get_env_value(name, env);
		if (val)
			len = ft_strlen(val);
		free(name);
	}
	return (len);
}

char	*expanded_var(char *str, char **env)
{
	t_expand	exp;
	int			i;
	int			j;

	i = 0;
	j = 0;
	exp.str = str;
	exp.i = &i;
	exp.j = &j;
	exp.env = env;
	exp.expanded = malloc(calculate_expanded_length(str, env) + 1);
	if (!exp.expanded)
		return (NULL);
	exp.expanded[0] = '\0';
	process_string(&exp);
	exp.expanded[j] = '\0';
	return (exp.expanded);
}

int	calculate_expanded_length(char *str, char **env)
{
	int	len;
	int	i;
	int	in_single_quote;

	len = 0;
	i = 0;
	in_single_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			in_single_quote = !in_single_quote;
		if (str[i] == '$' && !in_single_quote)
			len += handle_env_var(str, &i, env);
		else
			len++;
		i++;
	}
	return (len);
}
