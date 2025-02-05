#include "minishell.h"

int	get_path(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	if (!envp[i])
		return (-1);
	return (i);
}

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

void export_traductor(t_token *token, char *envp[])
{
    t_token *current;
    char *processed_str;

    current = token;
    while (current)
    {
		if (current->prev && (!ft_strcmp("export", current->prev->str) || !ft_strcmp("unset", current->prev->str)))
		{
				current = current->next;
				continue;
		}
        if (position_dollar(current->str) != -1)
        {
            processed_str = process_dollar_string(current->str, envp, current->quote_type);
            if (processed_str)
            {
            free(current->str);
            current->str = processed_str;
            }
        }
		current = current->next;
    }
}

int calculate_expanded_length(char *str, char **env)
{
    int     pos;
    int     len;
    char    *var;
    char    *val;

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

char *process_dollar_string(char *str, char **env, int quote_type)
{
    int     i;
    int     pos;
    char    *result;
    char    *var_name;
    char    *value;

    if (quote_type == 1)
        return (ft_strdup(str));
    
    result = malloc(calculate_expanded_length(str, env) + 1);
    if (!result)
        return (NULL);
    
    i = 0;
    while ((pos = position_dollar(str)) != -1)
    {
        ft_strncpy(result + i, str, pos);
        i += pos;
        var_name = extract_var_name(str, pos, ft_strlen(str));
        if (var_name)
        {
            value = get_env_value(var_name, env);
            if (value)
            {
				printf("%s", value);
                ft_strncpy(result + i, value, ft_strlen(value));
                i += ft_strlen(value);
            }
            str = str + pos + ft_strlen(var_name) + 1;
			printf("%s", str);
            free(var_name);
        }
        else
        {
            result[i++] = '$';
            str += pos + 1;
        }
    }
      if (*str)
    {
        ft_strncpy(result + i, str, ft_strlen(str));
        i += ft_strlen(str);
    }
    result[i] = '\0';
    return (result);
}

char* my_strcpy(char* dest, const char* src) 
{
    char* original_dest; 

	original_dest = dest; 
    while (*src != '\0') 
	{
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0'; 
    return original_dest;
}