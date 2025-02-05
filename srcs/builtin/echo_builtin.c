#include "minishell.h"

char	*extract_var_name(char *str, int dollar_pos, int str_len)
{
	int		var_end;
	char	*var_name;

	var_end = dollar_pos + 1;
	while (var_end < str_len && (isalnum(str[var_end]) || str[var_end] == '_'))
		var_end++;
	var_name = malloc(var_end - dollar_pos);
	if (!var_name)
		return (NULL);
	strncpy(var_name, str + dollar_pos + 1, var_end - dollar_pos - 1);
	var_name[var_end - dollar_pos - 1] = '\0';
	return (var_name);
}

void process_echo_string(char *str, char **env, int quote_type)
{
	int		str_len;
	int		start;
	int		dollar_pos;
	char	*before_dollar;
	char	*var_name;
	char	*value;
	char	*remaining;

    if (quote_type == 1)
    {
        printf("%s", str);
        return;
    }
    str_len = strlen(str);
    start = 0;
    dollar_pos = position_dollar(str);
    while (dollar_pos != -1)
    {
        if (dollar_pos > start)
        {
            before_dollar = malloc(dollar_pos - start + 1);
            if (before_dollar)
            {
                strncpy(before_dollar, str + start, dollar_pos - start);
                before_dollar[dollar_pos - start] = '\0';
                printf("%s", before_dollar);
                free(before_dollar);
            }
        }
        var_name = extract_var_name(str, dollar_pos, str_len);
        if (var_name)
        {
            value = get_env_value(var_name, env);
            if (value)
                printf("%s", value);
            start = dollar_pos + strlen(var_name) + 1;
            free(var_name);
        }
        else
        {
            printf("$");
            start = dollar_pos + 1;
        }
        dollar_pos = position_dollar(str + start);
        if (dollar_pos != -1)
            dollar_pos += start;
    }
    if (start < str_len)
    {
        remaining = malloc(str_len - start + 1);
        if (remaining)
        {
            strncpy(remaining, str + start, str_len - start);
            remaining[str_len - start] = '\0';
            printf("%s", remaining);
            free(remaining);
        }
    }
}

int	ft_echo(t_token *tokens, char **env)
{
	int		print_newline;
	t_token	*current;
	int		first;

    print_newline = 1;
    current = tokens->next;
    first = 1;
    if (current && is_n_arg(current->str) == 0)
    {
        print_newline = 0;
        current = current->next;
    }
    while (current && current->type == ARG)
    {
        if (!first)
            printf(" ");

        if (!current->str)
        {
            current = current->next;
            continue;
        }
        process_echo_string(current->str, env, current->quote_type);
        first = 0;
        current = current->next;
    }
    if (print_newline)
        printf("\n");
    return (0);
}

int	position_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

int	is_n_arg(char *arg)
{
	int	i;

	i = 1;
	if (arg[0] == '-')
	{
		while (arg[i] == 'n')
		{
			i++;
		}
		if (arg[i] != '\0')
			return (1);
		if (arg[i] == '\0')
			return (0);
	}
	return (1);
}

char	*get_env_value(char *var_name, char **env)
{
	char	*env_var;
	int		i;
	int		len;

	if (!var_name || var_name[0] == '\0')
		return (NULL);
	len = 0;
	while (var_name[len] && var_name[len] != '=')
		len++;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, len) == 0 && env[i][len] == '=')
		{
			env_var = env[i] + len + 1;
			return (env_var);
		}
		i++;
	}
	return (NULL);
}
