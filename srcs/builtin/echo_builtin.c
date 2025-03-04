/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 23:04:46 by habouda           #+#    #+#             */
/*   Updated: 2025/02/13 01:54:22 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	mini_echo(t_token *current, char **env, int first)
{
	while (current && (current->type == ARG || current->type == 0
			|| current->type == 727))
	{
		if (current->type == 0 || current->type == 727)
		{
			if (current->type == 0)
				printf(" ");
			current = current->next;
		}
		else
		{
			if (!first)
				printf(" ");
			if (!current->str)
			{
				current = current->next;
				continue ;
			}
			process_echo_string(current->str, env, current->quote_type);
			first = 0;
			current = current->next;
		}
	}
}

void	process_echo_string(char *str, char **env, int quote_type)
{
	int		str_len;
	char	*remaining;
	int		start;

	if (quote_type == 1)
	{
		printf("%s", str);
		return ;
	}
	str_len = ft_strlen(str);
	start = process_echo_helper(str, env);
	if (start < str_len)
	{
		remaining = malloc(str_len - start + 1);
		if (remaining)
		{
			ft_strncpy(remaining, str + start, str_len - start);
			remaining[str_len - start] = '\0';
			printf("%s", remaining);
			free(remaining);
		}
	}
}

int	process_echo_helper(char *str, char **env)
{
	int		start;
	int		dollar_pos;
	char	*before_dollar;

	start = 0;
	dollar_pos = position_dollar(str);
	while (dollar_pos != -1)
	{
		if (dollar_pos > start)
		{
			before_dollar = malloc(dollar_pos - start + 1);
			if (before_dollar)
			{
				ft_strncpy(before_dollar, str + start, dollar_pos - start);
				before_dollar[dollar_pos - start] = '\0';
				printf("%s", before_dollar);
				free(before_dollar);
			}
		}
		start = process_echo_var(str, env, start, dollar_pos);
		dollar_pos = position_dollar(str + start);
		if (dollar_pos != -1)
			dollar_pos += start;
	}
	return (start);
}

int    process_echo_var(char *str, char **env, int start, int dollar_pos)
{
    int        str_len;
    char    *var_name;
    char    *value;

    str_len = ft_strlen(str);
    if (is_single_dollar(str) == 0)
        var_name = extract_var_name(str, dollar_pos, str_len);
    else
        var_name = NULL;
    if (var_name)
    {
        value = get_env_value(var_name, env);
        if (value)
            printf("%s", value);
        start = dollar_pos + ft_strlen(var_name) + 1;
        free(var_name);
    }
    else
    {
        printf("$");
        start = dollar_pos + 1;
    }
    return (start);
}

int	ft_echo(t_token *tokens, char **env)
{
	int			print_newline;
	t_token		*current;
	int			first;

	print_newline = 1;
	current = tokens->next;
	first = 1;
	if (current && is_n_arg(current->str) == 0)
	{
		print_newline = 0;
		current = current->next;
	}
	mini_echo(current, env, first);
	if (print_newline)
		printf("\n");
	return (0);
}
