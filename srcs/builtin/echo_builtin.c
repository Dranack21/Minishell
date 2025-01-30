#include "minishell.h"

int	ft_echo(t_token *tokens, t_shell *shell, char **env)
{
	int		print_newline;
	t_token	*current;
	int		first;
	int i;
	char	*value;
	char    *before_dollar;

	shell->export = 1;
	print_newline = 1;
	current = tokens->next;
	i = 0;
	quote(current);
	if (current && is_n_arg(current->str) == 0)
	{
		print_newline = 0;
		current = current->next;
	}
	first = 1;
	while (current)
	{
		if (!first && current->has_trailing_spaces == 1)
			printf(" ");
		if (shell->export && position_dollar(current->str) != -1)
		{
			i = position_dollar(current->str) + 1;
			before_dollar = ft_substr(current->str, 0, i - 1);
            if (before_dollar)
            {
                printf("%s", before_dollar);
                free(before_dollar);
            }
			value = get_env_value(current->str + i, env);
			if (value)
				printf("%s", value);
			else
				printf("%s",current->str);
		}
		else
			printf("%s", current->str);
		first = 0;
		current = current->next;
	}
	if (print_newline)
		printf("\n");
	return (0);
}

void	quote(t_token *token)
{
	t_token	*current;

	current = token;
	while (current && (current->type == ARG || current->type == CMD))
	{
		current->str = strip_quote_plus_plus(current->str);
		current = current->next;
	}
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
	}
	else 
		return (1);
	return (0);
}
char *strip_quote_plus_plus(const char *str)
{
    char    *new_str;
    int     len;
    int     count = 0;
    int     i = 0;
    int     j = 0;
	char quote_char;

    if (!str)
        return (NULL);
    len = ft_strlen(str);
    if (len < 2)
        return (ft_strdup(str));
    if (str[0] != '"' && str[0] != '\'')
        return (ft_strdup(str));
    quote_char = str[0];
    if (str[len - 1] != quote_char)
        return (ft_strdup(str));
    while (i < len)
    {
        if (str[i] == quote_char)
            count++;
        i++;
    }
    if (count != 2)
        return (ft_strdup(str));
    new_str = malloc(sizeof(char) * (len - 1)); 
    if (!new_str)
        return (NULL);
    i = 1; 
    j = 0;
    while (i < len - 1) 
    {
        new_str[j] = str[i];
        i++;
        j++;
    }
    new_str[j] = '\0';
    return (new_str);
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
