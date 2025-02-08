#include "minishell.h"

int    calculate_expanded_length(char *str, char **env)
{
    int        pos;
    int        len;
    char    *var;
    char    *val;

    len = 0;
    pos = position_dollar(str + len);
    while (pos != -1)
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
        pos = position_dollar(str + len);
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

char    *mini_process_dollar(char *str, char *result, char **env)
{
    int        i;
    int        pos;

    i = 0;
    pos = position_dollar(str);
    while (pos != -1)
    {
        ft_strncpy(result + i, str, pos);
        i += pos;
        str = mini_mini_process_dollar(str, env, result, &i);
        pos = position_dollar(str);
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
	return (str);
}