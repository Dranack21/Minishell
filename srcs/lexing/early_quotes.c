/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   early_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 23:05:13 by habouda           #+#    #+#             */
/*   Updated: 2025/02/12 04:44:40 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_special_token(char *str)
{
	int	i;
	int	len;

	if (!str)
		return (0);
	i = 0;
	if (str[0] == '"' || str[0] == '\'')
		i = 1;
	len = 0;
	while (str[i + len] && str[i + len] != str[0])
		len++;
	if (len == 1 && (str[i] == '|' || str[i] == '<' || str[i] == '>'))
		return (1);
	if (len == 2 && str[i] == str[i + 1] && (str[i] == '<' || str[i] == '>'))
		return (1);
	return (0);
}

void	update_all_tokens_quotes(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (!is_special_token(current->str))
			update_token_quotes(current);		
		current = current->next;
	}
}
void	new_traductor(t_token *token, char *envp[], t_shell	*shell)
{
	t_token	*current;
	char	*processed_str;

	current = token;
	while (current)
	{
		fprintf(stderr, "%s\n", current->str);
		if (position_dollar(current->str) != -1)
		{
			if (position_dollar(current->str) == -2)
				processed_str = expand_exit_new(current->str , shell->exit_code, current->quote_type);
			else
				processed_str = over_translating(current->str, envp, current->quote_type);
			if (processed_str)
			{
				free(current->str);
				current->str = processed_str;
			}
		}
		current = current->next;
	}
}
int    get_clean_size(char *str)
{
    int        i;
    int        size;
    char    quote_type;

    i = 0;
    size = 0;
    quote_type = 0;
    while (str[i])
    {
        if (ft_isquote(str[i]))
        {
            if (!quote_type)
                quote_type = str[i];
            else if (str[i] == quote_type)
                quote_type = 0;
            else
                size++;
        }
        else
            size++;
        i++;
    }
    return (size);
}

char	*clean_quotes(char *str)
{
	char	*result;
	int		i;
	int		j;
	char	quote_type;

	result = malloc(sizeof(char) * (get_clean_size(str) + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	quote_type = 0;
	while (str[i])
	{
		if (ft_isquote(str[i]) && !quote_type)
			quote_type = str[i];
		else if (str[i] == quote_type)
			quote_type = 0;
		else
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

void	update_token_quotes(t_token *token)
{
	char	*cleaned;
	char	*old_str;
	int		i;

	if (!token || !token->str)
		return ;
	token->quote_type = 0;
	i = 0;
	while (token->str[i])
	{
		if (token->str[i] == '"' && token->quote_type == 0)
			token->quote_type = 2;
		else if (token->str[i] == '\'' && token->quote_type == 0)
			token->quote_type = 1;
		i++;
	}
	old_str = token->str;
	cleaned = clean_quotes(token->str);
	if (cleaned)
	{
		token->str = cleaned;
		free(old_str);
	}
}
char	*over_translating(char *str, char **env, int quote_type)
{
	int		i;
	int		j;
	char	*expanded;
	char	*name;
	char	*val;

	i = 0;
	j = 0;
	expanded = malloc(new_expanded_length( str, env) + 2);
	if (!expanded)
		return (NULL);
	expanded[0] = '\0';
	while (str[i])
	{
		if (str[i] == '$' && quote_type != 1)
		{
			name = is_var_name(str, &i);
			if (name)
			{
				val = get_env_value(name, env);
				if (val)
				{
					ft_strlcat(expanded, val, new_expanded_length(str, env) + 1);
					j += ft_strlen(val);
				}
				free(name);
			}
		}
		else
		{
			expanded[j] = str[i];
			expanded[j + 1] = '\0';
			j++;
		}
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
char	*expand_exit_new(char *str, int exit_status, int quote_type)
{
	int		i;
	int		j;
	char	*expanded;
	char	*exit_str;

	i = 0;
	j = 0;
	expanded = malloc(exit_new_length(str, exit_status) + 3);
	if (!expanded)
		return (NULL);
	exit_str = ft_itoa(exit_status);
	if (!exit_str)
		return (free(expanded), NULL);
	expanded[0] = '\0';
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?' && quote_type != 1)
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

int	exit_new_length(char *str, int exit_status)
{
	int	len;
	int	i;
	int	exit_len;

	len = 0;
	i = 0;
	exit_len = get_exit_str_len(exit_status);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			len += exit_len;
			i++;
		}
		else
			len++;
		i++;
	}
	fprintf(stderr, "LEN %d\n", len);
	return (len);
}
