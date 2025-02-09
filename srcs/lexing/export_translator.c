#include "minishell.h"

char	*expanded_var(char *str, char **env)
{
	int		i;
	int		j;
	int		in_single_quote;
	char	*expanded;
	char	*name;
	char	*val;

	i = 0;
	j = 0;
	in_single_quote = 0;
	expanded = malloc(calculate_expanded_length(str, env) + 1);
	if (!expanded)
		return (NULL);
	expanded[0] = '\0';
	while (str[i])
	{
		if (str[i] == '\'')
			in_single_quote = !in_single_quote;
		if (str[i] == '$' && !in_single_quote)
		{
			name = is_var_name(str, &i);
			if (name)
			{
				val = get_env_value(name, env);
				if (val)
				{
					ft_strlcat(expanded, val, calculate_expanded_length(str,
							env) + 1);
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

int	calculate_expanded_length(char *str, char **env)
{
	char	*name;
	char	*val;
	int		len;
	int		i;
	int		in_single_quote;

	len = 0;
	in_single_quote = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			in_single_quote = !in_single_quote;
		if (str[i] == '$' && !in_single_quote)
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
	strncpy(name, &str[start], len);
	name[len] = '\0';
	*i += len;
	return (name);
}
