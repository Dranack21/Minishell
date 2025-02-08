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
	ft_strncpy(var_name, str + dollar_pos + 1, var_end - dollar_pos - 1);
	var_name[var_end - dollar_pos - 1] = '\0';
	return (var_name);
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

int	process_echo_var(char *str, char **env, int start, int dollar_pos)
{
	int		str_len;
	char	*var_name;
	char	*value;

	str_len = ft_strlen(str);
	var_name = extract_var_name(str, dollar_pos, str_len);
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
			continue ;
		}
		process_echo_string(current->str, env, current->quote_type);
		first = 0;
		current = current->next;
	}
	if (print_newline)
		printf("\n");
	return (0);
}

