#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	skip_string_in_quotes(char *rl, int i)
{
	i++;
	while (rl[i] && rl[i] != '"')
		i++;
	if (rl[i] == '"')
		i++;
	return (i);
}

int	skip_string_in_single_quotes(char *rl, int i)
{
	i++;
	while (rl[i] && rl[i] != '\'')
		i++;
	if (rl[i] == '\'')
		i++;
	return (i);
}
void	export_traductor(t_token *token, char *envp[], t_shell *shell)
{
	t_token	*current;
	char	*processed_str;

	current = token;
	while (current)
	{
		special_cases_export_traductor(current, shell);
		if (position_dollar(current->str) != -1 && handle_exit_code(token,
				shell) == 1)
		{
			processed_str = process_dollar_string(current->str, envp,
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

void	special_cases_export_traductor(t_token *current, t_shell *shell)
{
	if (current->prev && !ft_strcmp("unset", current->prev->str))
	{
		current = current->next;
	}
	if (handle_exit_code(current, shell) == 0)
	{
		current = current->next;
	}
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

int	calculate_expanded_length(char *str, char **env)
{
	int		pos;
	int		len;
	char	*var;
	char	*val;

	len = 0;
	while ((pos = position_dollar(str + len)) != -1)
	{
		var = extract_var_name(str + len, pos, ft_strlen(str));
		if (var)
		{
			val = get_env_value(var, env);
			len += pos;
			if (val)
			{
				len += ft_strlen(val);
			}
			len += ft_strlen(var) + 1;
			free(var);
		}
		else
			len += pos + 1;
	}
	return (len + ft_strlen(str + len));
}

char	*process_dollar_string(char *str, char **env, int quote_type)
{
	char	*result;

	if (quote_type == 1)
		return (ft_strdup(str));
	result = malloc(calculate_expanded_length(str, env) + 1);
	if (!result)
		return (NULL);
	result = mini_process_dollar(str, result, env);
	return (result);
}

char	*mini_process_dollar(char *str, char *result, char **env)
{
	int		i;
	int		pos;

	i = 0;
	while ((pos = position_dollar(str)) != -1)
	{
		ft_strncpy(result + i, str, pos);
		i += pos;
		str = mini_mini_process_dollar(str, env, result, &i);
	}
	if (*str)
	{
		ft_strncpy(result + i, str, ft_strlen(str));
		i += ft_strlen(str);
	}
	result[i] = '\0';
	return (result);
}

char	*mini_mini_process_dollar(char *str, char **env, char *result, int *i)
{
	char *var_name;
	char *value;

    var_name = extract_var_name(str, 0, ft_strlen(str));
    if (var_name)
    {
        value = get_env_value(var_name, env);
        if (value)
        {
            ft_strncpy(result + *i, value, ft_strlen(value));
            *i += ft_strlen(value);
        }
        str += ft_strlen(var_name) + 1;
        free(var_name);
    }
    else
    {
        result[(*i)++] = '$';
        str++;
    }
    return str;
}
